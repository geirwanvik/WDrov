#include "imu.h"
#include "imuhelperfunctions.h"
#include <wiringPi.h>
#include <unistd.h>
#include <QDebug>

Imu::Imu(QThread &thread, QMutex &_i2cMutex) :
    QObject(0)
{
    i2cMutex = &_i2cMutex;
    mpu.Init();
    memset(&imu,0,sizeof(imu_t));
    memset(&att,0,sizeof(att_t));

    connect (&thread, SIGNAL(started()), this, SLOT(Calculate()));
}

void Imu::Calculate()
{
    int gyroADCprevious[3] = {0,0,0};
    int gyroADCp[3];
    int gyroADCinter[3];

    while (1)
    {
        i2cMutex->tryLock(-1);

        mpu.GetMagData(imu.magADC);

        mpu.GetAccData(imu.accADC);

        GetEstimatedAttitude();

        mpu.GetGyroData(imu.gyroADC);

        for (uint8_t axis = 0; axis < 3; axis++)
        {
            gyroADCp[axis] =  imu.gyroADC[axis];
        }

        delayMicroseconds(650); //empirical, interleaving delay between 2 consecutive reads
        mpu.GetGyroData(imu.gyroADC);

        i2cMutex->unlock();

        for (uint8_t axis = 0; axis < 3; axis++)
        {
            gyroADCinter[axis] =  imu.gyroADC[axis]+gyroADCp[axis];
            // empirical, we take a weighted value of the current and the previous values
            imu.gyroData[axis] = (gyroADCinter[axis]+gyroADCprevious[axis])/3;
            gyroADCprevious[axis] = (gyroADCinter[axis]>>1);
        }
        usleep(5000);
    }
}

void Imu::NewMessageItem(QString cmd, QString value)
{
    float data;
    if (value == "READ")
    {
        if (cmd == "ROLL")
        {
            data = (float)att.angle[ROLL] / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
        else if (cmd == "PITCH")
        {
            data = (float)att.angle[PITCH] / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
        else if (cmd == "HEADING")
        {
            data = (float)att.heading / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
    }
}

void Imu::GetEstimatedAttitude()
{
    static int accLPF32[3]    = {0, 0, 1};
    static float invG; // 1/|G|

    static t_fp_vector EstG;
    static t_int32_t_vector EstG32;
    static t_int32_t_vector EstM32;
    static t_fp_vector EstM;

    uint8_t axis;
    int accMag = 0;
    float scale, deltaGyroAngle[3];
    uint8_t validAcc;
    static unsigned int previousT;
    unsigned int currentT = micros();

    scale = (currentT - previousT) * GYRO_SCALE; // GYRO_SCALE unit: radian/microsecond
    previousT = currentT;

    // Initialization
    for (axis = 0; axis < 3; axis++)
    {
        deltaGyroAngle[axis] = imu.gyroADC[axis]  * scale; // radian

        accLPF32[axis]    -= accLPF32[axis]>>ACC_LPF_FACTOR;
        accLPF32[axis]    += imu.accADC[axis];
        imu.accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;

        accMag += imu.accSmooth[axis]*imu.accSmooth[axis] ;
    }

    rotateV(&EstG.V,deltaGyroAngle);
    rotateV(&EstM.V,deltaGyroAngle);

    accMag = accMag*100/(ACC_1G*ACC_1G);
    validAcc = (72 < accMag) && (accMag < 133);
    // Apply complimentary filter (Gyro drift correction)
    // If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
    // To do that, we just skip filter, as EstV already rotated by Gyro
    for (axis = 0; axis < 3; axis++)
    {
        if ( validAcc )
        EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + imu.accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
        EstG32.A[axis] = EstG.A[axis]; //int32_t cross calculation is a little bit faster than float
        EstM.A[axis] = (EstM.A[axis] * GYR_CMPFM_FACTOR  + imu.magADC[axis]) * INV_GYR_CMPFM_FACTOR;
        EstM32.A[axis] = EstM.A[axis];
    }

    // Attitude of the estimated vector
    int sqGX_sqGZ = sq(EstG32.V.X) + sq(EstG32.V.Z);
    invG = InvSqrt(sqGX_sqGZ + sq(EstG32.V.Y));
    att.angle[ROLL]  = _atan2(EstG32.V.X , EstG32.V.Z);
    att.angle[PITCH] = _atan2(EstG32.V.Y , InvSqrt(sqGX_sqGZ)*sqGX_sqGZ);

    att.heading = _atan2(
    EstM32.V.Z * EstG32.V.X - EstM32.V.X * EstG32.V.Z,
    (EstM.V.Y * sqGX_sqGZ  - (EstM32.V.X * EstG32.V.X + EstM32.V.Z * EstG32.V.Z) * EstG.V.Y)*invG );
}
