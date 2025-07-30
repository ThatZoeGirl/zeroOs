#include <ST7789.h>
#include <ST7789CONF.h>

int spi_fd = open("/dev/spidev0.0", O_WRONLY);

void sendCommand(uint8_t cmd){
    digitalWrite(DC_PIN, LOW);
    write(spi_fd, &cmd, 1);
}

void sendData(uint8_t data){
    digitalWrite(DC_PIN, HIGH);
    write(spi_fd, &data, 1);
}

void resetDisplay() {
    digitalWrite(RST_PIN, LOW);
    delay(50);
    digitalWrite(RST_PIN, HIGH);
    delay(50);
}

void initST7789() {
    //SPI stuff - tbh idk what this shit does except speed and bits
    int mode = SPI_MODE_0;
    int speed = 125000000; // 80 MHz 
    int bits = 8;

    pinMode(DC_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);

    resetDisplay();

    sendCommand(0x36); //MADCTL
    // Rotations
    #ifdef DEG0
        #ifdef RGB_ORDER
            sendData(0x00); //0 degrees normal
        #endif
        #ifdef BGR_ORDER
            sendData(0x00 | 0x08); //0 degrees inverted
        #endif
    #endif
    #ifdef DEG90
        #ifdef RGB_ORDER
            sendData(0x60); //90 degrees normal
        #endif
        #ifdef BGR_ORDER
            sendData(0x60 | 0x08); //90 degrees inverted
        #endif
    #endif
    #ifdef DEG180
        #ifdef RGB_ORDER
            sendData(0xC0); //180 degrees normal
        #endif
        #ifdef BGR_ORDER
            sendData(0xC0 | 0x08); //180 degrees inverted
        #endif
    #endif
    #ifdef DEG270
        #ifdef RGB_ORDER
            sendData(0xA0); //270 degrees normal
        #endif
        #ifdef BGR_ORDER
            sendData(0xA0 | 0x08); //270 degrees inverted
        #endif
    #endif

    sendCommand(0x3A); //COLMOD
    sendData(0x05); // 16-bit color

    #ifdef INVERTED_COLORS
        sendCommand(0x20); // Inversion on
    #else
        sendCommand(0x21); // Inversion off
    #endif

    
    sendCommand(0xA0);
    sendCommand(0x11); // exit sleep
    delay(120);

    sendCommand(0x29); // Display on

    
    if (spi_fd < 0) {
        perror("SPI open failed");
        exit(-1);
    }

    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
}

void setAddrWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end){
    sendCommand(0x2A);  // Column address set
    sendData(x_start >> 8);
    sendData(x_start & 0xFF);
    sendData(x_end >> 8);
    sendData(x_end & 0xFF);

    sendCommand(0x2B); // Row adress set
    sendData(y_start >> 8);
    sendData(y_start & 0xFF);
    sendData(y_end >> 8);
    sendData(y_end & 0xFF);

    sendCommand(0x2C);
}

void pushColor(uint16_t color){
    uint8_t data[2];
    data[0] = color >> 8;
    data[1] = color & 0xFF;
    digitalWrite(DC_PIN, HIGH);
    write(spi_fd, data, 2);
}

void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){
    setAddrWindow(x, x+w-1, y, y+h-1);

    int numPixels = w*h;
    uint8_t *writeBuffer = new uint8_t[DATA_CHUNK_SIZE];

    for(int i=0; i< DATA_CHUNK_SIZE; i ++){
        writeBuffer[i*2] = color >> 8;
        writeBuffer[i*2+1] = color & 0xFF;
    }

    digitalWrite(DC_PIN, HIGH);

    while(numPixels > 0){
        int chunkPixels = (numPixels > DATA_CHUNK_SIZE/2) ? DATA_CHUNK_SIZE/2 : numPixels;
        write(spi_fd, writeBuffer, chunkPixels*2);
        numPixels -= chunkPixels;
    }

    delete[] writeBuffer;
}

void showBuf(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *buffer){
    setAddrWindow(x, x+w-1, y, y+h-1);

    int numPixels = w*h;
    int offset = 0;
    uint8_t *writeBuffer = new uint8_t[DATA_CHUNK_SIZE];

    digitalWrite(DC_PIN, HIGH);
    while(numPixels > 0){
        int chunkPixels = (numPixels > DATA_CHUNK_SIZE/2) ? DATA_CHUNK_SIZE/2 : numPixels;

        for(int i=0; i < chunkPixels; i ++){
            writeBuffer[i*2] = buffer[offset+i] >> 8;
            writeBuffer[i*2+1] = buffer[offset+i] & 0xFF;
        }

        write(spi_fd, writeBuffer, chunkPixels*2);
        offset += chunkPixels;
        numPixels -= chunkPixels;
    }
    
    delete[] writeBuffer;
}