void i2cwrite(unsigned int addr_comp,unsigned char adr,unsigned char val);
// printf
#include <stdio.h>
/*#include <iostream>

*/
//O_RDWR
#include <fcntl.h>

// I2C_SLAVE
#include <linux/i2c-dev.h>

// __u8
#include <iostream>
#include <linux/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
/*#include <glib.h>
#include <math.h>*/


const int taillemaxireadi2c=10;

//fonction pour librairie i2c
void roboti2cwrite(unsigned int addr_comp,unsigned char adr,unsigned char val)
{


unsigned char bufa[2] = {0,0};

   int file;
char *filename = "/dev/i2c-1";//port num1 sur rasp 2
if ((file = open(filename, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
}

//connection à l'esclave

if (ioctl(file, I2C_SLAVE, addr_comp) < 0) {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
}



bufa[0] =adr;
bufa[1] =val;

write(file,bufa,2);
usleep(1000);
close(file) ;
}


void roboti2cread(unsigned int addr_comp,char longueur,unsigned char* buf){

//init
int file;
char *filename = "/dev/i2c-1";//port num1 sur rasp 2
if ((file = open(filename, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
}
//connection à l'esclave

if (ioctl(file, I2C_SLAVE, addr_comp) < 0) {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
    }




if (longueur>taillemaxireadi2c){longueur=taillemaxireadi2c;}
read(file,buf,longueur);
usleep(1000);
close(file) ;
}



