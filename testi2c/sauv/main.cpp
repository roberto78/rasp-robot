// printf
#include <stdio.h>

//O_RDWR
#include <fcntl.h>

// I2C_SLAVE
#include <linux/i2c-dev.h>

// __u8
#include <linux/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <glib.h>
int main(void){


int file;
char *filename = "/dev/i2c-1";
if ((file = open(filename, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
}


int addr = 0x08;          // The I2C address of the ADC
if (ioctl(file, I2C_SLAVE, addr) < 0) {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
}



char buf[10] = {0};
//char buffer[10] = {0};

/*
for (int i = 0; i<8; i++) {
    // Using I2C Read
    if (read(file,buf,2) != 2) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to read from the i2c bus.\n");
       // buffer = g_strerror(errno);
       // printf(buffer);
        printf("\n\n");
    } else {
       /* data = (float)((buf[0] & 0b00001111)<<8)+buf[1];
        data = data/4096*5;
        channel = ((buf[0] & 0b00110000)>>4);*/
        printf("%s \n",buf);
    }
}*/
read(file,buf,8);
        printf("%s \n",buf);
  return 0;
}
