#include "mpu6050.h"
#include "imuhelperfunctions.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QtGlobal>

int MPU_FD;
int MAG_FD;

int accOffset[3];
int magOffset[3]; // {81,45,206}; // Calibrated values

uint8_t accDoCalibrate;
uint8_t magDoCalibrate;

// Mag Sensor Variables
static float magGain[3] = {1.0, 1.0, 1.0}; // gain for each axis, populated at sensor init
static uint8_t magInit = 0;
// Mag Sensor End

// MPU Sensor Variables
int gyroZero[3] = {0, 0, 0};
unsigned int calibratingA = 0; // The calibration is done in the main loop,
unsigned int calibratingG = 512; // calibrating decreases at each cycle down to 0, then we enter in a normal mode.
// MPU Sensor End


Mpu6050::Mpu6050()
{
}

void Mpu6050::Init() {
    MPU_FD = wiringPiI2CSetup(MPU6050_ADDRESS);
    MAG_FD = wiringPiI2CSetup(MAG_ADDRESS);

    InitGyro();
    InitMag();
    InitAcc();

    int gyroADC[3];
    int accADC[3];
    accDoCalibrate = 1;

    //Calibration
    for (int i = 0; i < 600; i++) {
        GetGyroData(gyroADC);
        GetAccData(accADC);
        delay(1);
    }
}

void Mpu6050::InitGyro(void) {
    //PWR_MGMT_1    -- DEVICE_RESET 1

    wiringPiI2CWriteReg8(MPU_FD, 0x6B, 0x80);
    delay(5);

    //PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (PLL with Z Gyro reference)
    wiringPiI2CWriteReg8(MPU_FD, 0x6B, 0x03);

    //CONFIG        -- DLPF_CFG = 3 => ACC bandwidth = 44Hz GYRO bandwidth = 42Hz)
    wiringPiI2CWriteReg8(MPU_FD, 0x1A, 0x03);

    //GYRO_CONFIG   -- FS_SEL = 3: Full scale set to 2000 deg/sec
    wiringPiI2CWriteReg8(MPU_FD, 0x1B, 0x18);

    // enable I2C bypass for AUX I2C
    //INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=1 ; CLKOUT_EN=0
    wiringPiI2CWriteReg8(MPU_FD, 0x37, 0x02);
}

void Mpu6050::InitMag(void) {
    int magADC[3];
    int xyz_total[3] = {0, 0, 0}; // 32 bit totals so they won't overflow.
    bool bret = true; // Error indicator

    delay(50); //Wait before start
    wiringPiI2CWriteReg8(MAG_FD, 0x00, 0x010 + 0x01); // Reg A DOR=0x010 + MS1,MS0 set to pos bias

    // Note that the  very first measurement after a gain change maintains the same gain as the previous setting.
    // The new gain setting is effective from the second measurement and on.

    wiringPiI2CWriteReg8(MAG_FD, 0x01, 2 << 5); //Set the Gain
    wiringPiI2CWriteReg8(MAG_FD, 0x02, 1);
    delay(100);
    ReadRawMag(magADC); //Get one sample, and discard it

    for (uint8_t i = 0; i < 10; i++) { //Collect 10 samples
        wiringPiI2CWriteReg8(MAG_FD, 0x02, 1);
        delay(100);
        ReadRawMag(magADC); // Get the raw values in case the scales have already been changed.

        // Since the measurements are noisy, they should be averaged rather than taking the max.
        xyz_total[0] += magADC[0];
        xyz_total[1] += magADC[1];
        xyz_total[2] += magADC[2];

        // Detect saturation.
        if (-(1 << 12) >= qMin(magADC[0], qMin(magADC[1], magADC[2]))) {
            bret = false;
            break; // Breaks out of the for loop.  No sense in continuing if we saturated.
        }
    }

    // Apply the negative bias. (Same gain)
    wiringPiI2CWriteReg8(MAG_FD, 0x00, 0x010 + 0x02); // Reg A DOR=0x010 + MS1,MS0 set to negative bias.
    for (uint8_t i = 0; i < 10; i++) {
        wiringPiI2CWriteReg8(MAG_FD, 0x02, 1);
        delay(100);
        ReadRawMag(magADC); // Get the raw values in case the scales have already been changed.

        // Since the measurements are noisy, they should be averaged.
        xyz_total[0] -= magADC[0];
        xyz_total[1] -= magADC[1];
        xyz_total[2] -= magADC[2];

        // Detect saturation.
        if (-(1 << 12) >= qMin(magADC[0], qMin(magADC[1], magADC[2]))) {
            bret = false;
            break; // Breaks out of the for loop.  No sense in continuing if we saturated.
        }
    }

    magGain[0] = qAbs(820.0 * (+1.16)*2.0 * 10.0 / xyz_total[0]);
    magGain[1] = qAbs(820.0 * (+1.16)*2.0 * 10.0 / xyz_total[1]);
    magGain[2] = qAbs(820.0 * (+1.08)*2.0 * 10.0 / xyz_total[2]);

    // leave test mode
    wiringPiI2CWriteReg8(MAG_FD, 0x00, 0x70); //Configuration Register A  -- 0 11 100 00  num samples: 8 ; output rate: 15Hz ; normal measurement mode
    wiringPiI2CWriteReg8(MAG_FD, 0x01, 0x20); //Configuration Register B  -- 001 00000    configuration gain 1.3Ga
    wiringPiI2CWriteReg8(MAG_FD, 0x02, 0x00); //Mode register             -- 000000 00    continuous Conversion Mode
    delay(10);
    magInit = 1;

    if (!bret) { //Something went wrong so get a best guess
        magGain[0] = 1.0;
        magGain[1] = 1.0;
        magGain[2] = 1.0;
    }
}

void Mpu6050::InitAcc(void) {
    //ACCEL_CONFIG  -- AFS_SEL=2 (Full Scale = +/-8G)  ; ACCELL_HPF=0
    wiringPiI2CWriteReg8(MPU_FD, 0x1C, 0x10);

    //at this stage, the MAG is configured via the original MAG init function in I2C bypass mode
    //now we configure MPU as a I2C Master device to handle the MAG via the I2C AUX port (done here for HMC5883)

    //USER_CTRL     -- DMP_EN=0 ; FIFO_EN=0 ; I2C_MST_EN=1 (I2C master mode) ; I2C_IF_DIS=0 ; FIFO_RESET=0 ; I2C_MST_RESET=0 ; SIG_COND_RESET=0
    wiringPiI2CWriteReg8(MPU_FD, 0x6A, 0b00100000);

    //INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=0 ; CLKOUT_EN=0
    wiringPiI2CWriteReg8(MPU_FD, 0x37, 0x00);

    //I2C_MST_CTRL  -- MULT_MST_EN=0 ; WAIT_FOR_ES=0 ; SLV_3_FIFO_EN=0 ; I2C_MST_P_NSR=0 ; I2C_MST_CLK=13 (I2C slave speed bus = 400kHz)
    wiringPiI2CWriteReg8(MPU_FD, 0x24, 0x0D);

    //I2C_SLV0_ADDR -- I2C_SLV4_RW=1 (read operation) ; I2C_SLV4_ADDR=MAG_ADDRESS
    wiringPiI2CWriteReg8(MPU_FD, 0x25, 0x80 | MAG_ADDRESS);

    //I2C_SLV0_REG  -- 6 data bytes of MAG are stored in 6 registers. First register address is MAG_DATA_REGISTER
    wiringPiI2CWriteReg8(MPU_FD, 0x26, 0x03);

    //I2C_SLV0_CTRL -- I2C_SLV0_EN=1 ; I2C_SLV0_BYTE_SW=0 ; I2C_SLV0_REG_DIS=0 ; I2C_SLV0_GRP=0 ; I2C_SLV0_LEN=3 (3x2 bytes)
    wiringPiI2CWriteReg8(MPU_FD, 0x27, 0x86);
}

void Mpu6050::GetGyroData(int* gyroData)
{
    ReadRawGyro(gyroData);

    static int previousGyroADC[3] = {0, 0, 0};
    static int g[3];
    uint8_t axis;

    if (calibratingG > 0)
    {
        for (axis = 0; axis < 3; axis++)
        {
            // Reset g[axis] at start of calibration
            if (calibratingG == 512)
            {
                g[axis] = 0;
            }
            // Sum up 512 readings
            g[axis] += gyroData[axis];
            // Clear global variables for next reading
            gyroData[axis] = 0;
            gyroZero[axis] = 0;
            if (calibratingG == 1)
            {
                gyroZero[axis] = (g[axis] + 256) >> 9;
            }
        }
        calibratingG--;
    }

    for (axis = 0; axis < 3; axis++)
    {
        gyroData[axis] -= gyroZero[axis];
        //anti gyro glitch, limit the variation between two consecutive readings
        gyroData[axis] = constrain(gyroData[axis], previousGyroADC[axis] - 800, previousGyroADC[axis] + 800);

        previousGyroADC[axis] = gyroData[axis];
    }
}

void Mpu6050::ReadRawGyro(int* rawData) {
    uint8_t data[6];

    readBytes(MPU_FD, 0x43, 6, data);

    rawData[PITCH] = ((int16_t)((data[0] << 8) | data[1]) >> 2);
    rawData[ROLL] = (-1)*((int16_t)((data[2] << 8) | data[3]) >> 2);
    rawData[YAW] = (-1) * ((int16_t)((data[4] << 8) | data[5]) >> 2);
}

void Mpu6050::GetMagData(int* magData)
{
    static unsigned int t, tCal = 0;
    static unsigned int currentTime = 0;
    static int magZeroTempMin[3];
    static int magZeroTempMax[3];
    uint8_t axis;

    currentTime = millis();

    if (currentTime < t)
        return;
    t = currentTime + 100;

    ReadRawMag(magData);

    magData[ROLL] = magData[ROLL] * magGain[ROLL];
    magData[PITCH] = magData[PITCH] * magGain[PITCH];
    magData[YAW] = magData[YAW] * magGain[YAW];

    if (magDoCalibrate)
    {
        tCal = t;
        for (axis = 0; axis < 3; axis++)
        {
            magOffset[axis] = 0;
            magZeroTempMin[axis] = magData[axis];
            magZeroTempMax[axis] = magData[axis];
        }
        magDoCalibrate = false;

    }

    if (magInit)
    { // we apply offset only once mag calibration is done
        magData[ROLL] -= magOffset[ROLL];
        magData[PITCH] -= magOffset[PITCH];
        magData[YAW] -= magOffset[YAW];
    }

    if (tCal != 0)
    {
        if ((t - tCal) < 30000)
        { // 30s: you have 30s to turn the multi in all directions

            for (axis = 0; axis < 3; axis++)
            {
                if (magData[axis] < magZeroTempMin[axis]) magZeroTempMin[axis] = magData[axis];
                if (magData[axis] > magZeroTempMax[axis]) magZeroTempMax[axis] = magData[axis];
            }
        }
        else
        {
            tCal = 0;
            for (axis = 0; axis < 3; axis++)
            {
                magOffset[axis] = (magZeroTempMin[axis] + magZeroTempMax[axis]) >> 1;
            }
        }
    }
}

void Mpu6050::ReadRawMag(int* rawData)
{
    uint8_t data[6];

    if (magInit)
    {
        readBytes(MPU_FD, 0x49, 6, data);
    }
    else
    {
        readBytes(MAG_FD, 0x03, 6, data);
    }

    rawData[ROLL] = (int16_t)((data[0] << 8) | data[1]);
    rawData[YAW] = (-1)*(int16_t)((data[2] << 8) | data[3]);
    rawData[PITCH] = (int16_t)((data[4] << 8) | data[5]);
}

void Mpu6050::GetAccData(int* accData)
{
    static int a[3];
    ReadRawAcc(accData);

    if (accDoCalibrate)
    {
        calibratingA = 512;
        accDoCalibrate = 0;
    }
    if (calibratingA > 0)
    {
        for (uint8_t axis = 0; axis < 3; axis++)
        {
            // Reset a[axis] at start of calibration
            if (calibratingA == 512) a[axis] = 0;
            // Sum up 512 readings
            a[axis] += accData[axis];
            // Clear global variables for next reading
            accData[axis] = 0;
            accOffset[axis] = 0;
        }
        // Calculate average, shift Z down by ACC_1G ( 512 ) and store values
        if (calibratingA == 1) {
            accOffset[ROLL] = (a[ROLL] + 256) >> 9;
            accOffset[PITCH] = (a[PITCH] + 256) >> 9;
            accOffset[YAW] = ((a[YAW] + 256) >> 9) - (512);
            //SaveMemory();
        }
        calibratingA--;
    }

    accData[ROLL] -= accOffset[ROLL];
    accData[PITCH] -= accOffset[PITCH];
    accData[YAW] -= accOffset[YAW];
}

void Mpu6050::ReadRawAcc(int* rawData)
{
    uint8_t data[6];

    readBytes(MPU_FD, 0x3B, 6, data);

    rawData[ROLL] = ((int16_t)((data[0] << 8) | data[1]) >> 3);
    rawData[PITCH] = ((int16_t)((data[2] << 8) | data[3]) >> 3);
    rawData[YAW] = (int16_t)((data[4] << 8) | data[5]) >> 3;
}

void Mpu6050::readBytes(int fd, uint8_t reg, uint8_t length, uint8_t *data)
{
    for (uint8_t i = 0; i < length; i++)
    {
        data[i] = wiringPiI2CReadReg8(fd,reg + i);

    }
}
