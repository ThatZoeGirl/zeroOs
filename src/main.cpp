#include <wiringPi.h>

#include <ST7789.h>
#include <ST7789CONF.h>

#include <zGfx.h>
#include <stdint.h>

int main() {
    wiringPiSetupGpio();
    initST7789();
    
    FrameBuffer fb(TFT_WIDTH, TFT_HEIGHT);
    showBuf(0,0,fb.width,fb.height,fb.buffer);

    return 0;
}