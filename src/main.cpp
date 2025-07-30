#include <ST7789.h>
#include <ST7789CONF.h>

#include <zGfx.h>
#include <stdint.h>

int main() {
    
    wiringPiSetupGpio();

    initST7789();
    
    uint16_t *buffer = new uint16_t[TFT_WIDTH*TFT_HEIGHT];
    float hue=0.0f;

    while(true){
        if(hue>360.0f){hue=0.0f;};
        for(int y=0; y<TFT_HEIGHT; y++){
            for(int x=0; x<TFT_WIDTH; x++){
                buffer[(y*TFT_WIDTH)+x] = hsv(hue, ((1.0f/(float)(TFT_WIDTH))*x), 1.0f-((1.0f/(float)(TFT_HEIGHT))*y));
            }
        }
        showBuf(0,0,TFT_WIDTH,TFT_HEIGHT,buffer);
        hue+=5.0f;
    }

    return 0;
}