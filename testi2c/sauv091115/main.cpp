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

//init
int file;
char *filename = "/dev/i2c-1";//port num1 sur rasp 2
if ((file = open(filename, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
}
while(1){sleep(1);
//connection à l'esclave
int addr = 0x08;          // The I2C slave address
if (ioctl(file, I2C_SLAVE, addr) < 0) {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
}



char buf[10] = {0,0,0,0,0,0,0,0};
read(file,buf,8);
short int Ubat=buf[1]*256+buf[0];
short int U1=buf[3]*256+buf[2];
short int U2=buf[5]*256+buf[4];
short int U3=buf[7]*256+buf[6];
char bufa[10] = {'3','2','1','0',0,0,0,0};
write(file,bufa,8);
       printf("Ubat:%d U1: %d U2: %d U3: %d\n",Ubat,U1,U2,U3);
  }

  return 0;
}
