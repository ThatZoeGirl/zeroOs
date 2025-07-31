#include <zGfx.h>

Canvas::Canvas(int cWidth, int cHeight){
    width = cWidth;
    height = cHeight;
    buffer = new uint16_t[width*height];
    return;
}

int Canvas::coord(int x, int y){
    return (width*y)+x;
}

void Canvas::setPixel(int x, int y, uint16_t color){
    if (x<width && y<height){
        buffer[coord(x, y)] = color;
    }
    return;
}

void Canvas::drawLine(int x1, int y1, int x2, int y2, uint16_t color){
    float dx = x2-x1;
    float dy = y2-y1;

    float len = sqrt(abs(dx)*abs(dx) + abs(dy)*abs(dy));

    float straightLength;
    if(dx>dy){straightLength = dx;} else {straightLength = dy;};

    float ux = dx/straightLength;
    float uy = dy/straightLength;

    for(int i = 1; i<straightLength; i++){
        int x = (int)(i*ux) + x1;
        int y = (int)(i*uy) + y1;
        if (x<width && y<height){
            buffer[coord(x, y)] = color;
        } else {
            return;
        }
    }

    return;
}