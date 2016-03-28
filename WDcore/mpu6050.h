#ifndef MPU6050_H
#define MPU6050_H
#include <inttypes.h>

class Mpu6050
{
public:
    Mpu6050();
    void Init();
    void GetMagData(int* magData);
    void GetAccData(int* accData);
    void GetGyroData(int* gyroData);

private:
    void InitGyro();
    void InitMag();
    void InitAcc();
    void ReadRawGyro(int* rawData);
    void ReadRawMag(int* rawData);
    void ReadRawAcc(int* rawData);
    void readBytes(int fd, uint8_t reg, uint8_t length, uint8_t *data);
};

#endif // MPU6050_H
