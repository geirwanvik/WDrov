#ifndef PCA9685_H
#define PCA9685_H

#include <inttypes.h>

class Pca9685
{
public:
    Pca9685();

    void setPWM(uint8_t led, int on_value, int off_value);
    void setPWM(uint8_t, int value);
    int getPWM(uint8_t led);

private:
    void setPWMFreq(int freq);
    void reset(void);
};

#endif // PCA9685_H
