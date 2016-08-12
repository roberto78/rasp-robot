// printf
#include <stdio.h>

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
#include <glib.h>
//#include <i2c.h>
void i2cwrite(int addr_comp,int reg,int data)
{


char bufa[2] = {0,0};

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




bufa[0] =reg;
bufa[1] =data;

write(file,bufa,2);

close(file) ;
}



int main(void){
const int addr_pca=0x40;
const int addr_ard=0x08;
while(1){
i2cwrite(addr_ard,'a','b');
printf("aa\n");
//sleep(1);
}

//en dessous pour servo moteur

/*
i2cwrite(addr_pca,0,0);
i2cwrite(addr_pca,0,16);//reset
i2cwrite(addr_pca,254,150);//prescal
i2cwrite(addr_pca,0,0);
sleep(5);
//i2cwrite(addr_pca,0,128);
i2cwrite(addr_pca,6,0);
i2cwrite(addr_pca,7,0);
//205 à 410
i2cwrite(addr_pca,8,0);
i2cwrite(addr_pca,9,1);






while (1){
i2cwrite(addr_pca,6,0);//6lsb 7msb temps jusqu'a allumage
i2cwrite(addr_pca,7,0);
i2cwrite(0x40,8,210);//8lsb 8msb temps jusqu'a extinction
i2cwrite(0x40,9,0);
sleep(1);
i2cwrite(addr_pca,6,0);
i2cwrite(addr_pca,7,0);
i2cwrite(0x40,8,0x9a);
i2cwrite(0x40,9,1);
sleep(1);
}
//       printf("Ubat:%d U1: %d U2: %d U3: %d\n",Ubat,U1,U2,U3);


*/
  return 0;
}
