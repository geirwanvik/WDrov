#include "imuhelperfunctions.h"

#define abs(x) ((x)>0?(x):-(x))

att_t att;
imu_t imu;

int _atan2(int y, int x)
{
    float z = (float)y / x;
    int a;
    if ( abs(y) < abs(x) )
    {
        a = (573 * z / (1.0f + 0.28f * z * z));
        if (x<0)
        {
            if (y<0)
                a -= 1800;
            else
                a += 1800;
        }
    }
    else
    {
        a =(900 - 573 * z / (z * z + 0.28f));
        if (y<0)
            a -= 1800;
    }
    return a;
}

float InvSqrt (float x)
{
    union{
        int i;
        float   f;
    } conv;
    conv.f = x;
    conv.i = 0x5f3759df - (conv.i >> 1);
    return 0.5f * conv.f * (3.0f - x * conv.f * conv.f);
}

// Rotate Estimated vector(s) with small angle approximation, according to the gyro data
void rotateV(struct fp_vector *v,float* delta)
{
    fp_vector v_tmp = *v;
    v->Z -= delta[ROLL]  * v_tmp.X + delta[PITCH] * v_tmp.Y;
    v->X += delta[ROLL]  * v_tmp.Z - delta[YAW]   * v_tmp.Y;
    v->Y += delta[PITCH] * v_tmp.Z + delta[YAW]   * v_tmp.X;
}
