#include <inttypes.h>
#ifndef IMUHELPERFUNCTIONS_H
#define IMUHELPERFUNCTIONS_H

#define MPU6050_ADDRESS 0x68
#define MAG_ADDRESS 0x1E

#define PI 3.141592653
#define GYRO_SCALE (4 / 16.4 * PI / 180.0 / 1000000.0)   //MPU6050 16.4 LSB/(deg/s) and we ignore the last 2 bits
#define ACC_LPF_FACTOR 4 // that means a LPF of 16
#define ACC_1G 512
#define GYR_CMPF_FACTOR 600
#define GYR_CMPFM_FACTOR 250
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))

#define sq(x) ((x)*(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
//#define abs(x) ((x)>0?(x):-(x))

enum Axis { ROLL, PITCH, YAW };

typedef struct
{
    int accSmooth[3]; // Filtered
    int gyroData[3]; // Avg from two readings
    int magADC[3]; // After offset and scale
    int gyroADC[3]; // After offset and scale
    int accADC[3]; // After offset and scale
} imu_t;
extern imu_t imu;

typedef struct
{
    int angle[2];            // absolute angle inclination in multiple of 0.1 degree 180 deg = 1800. [0] = ROLL , [1] = PITCH
    int heading;             // variometer in cm/s
} att_t;
extern att_t att;


typedef struct fp_vector
{
    float X,Y,Z;
} t_fp_vector_def;

typedef union
{
    float A[3];
    t_fp_vector_def V;
} t_fp_vector;

typedef struct int32_t_vector
{
    int32_t X,Y,Z;
} t_int32_t_vector_def;

typedef union
{
    int32_t A[3];
    t_int32_t_vector_def V;
} t_int32_t_vector;


void rotateV(struct fp_vector *v,float* delta);
float InvSqrt (float x);
int _atan2(int y, int x);

#endif // IMUHELPERFUNCTIONS_H
