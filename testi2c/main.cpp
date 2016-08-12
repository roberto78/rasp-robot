// printf
#include <stdio.h>
#include <iostream>


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
#include <math.h>


const bool debugon=true;


#include "roboti2c.cpp"
#include "robotservo.cpp"
#include "robotarduino.cpp"



int main(void){


robotarduinoalim(3,1);
robotarduinoalim(2,1);
sleep(1);
servoinit();
sleep(1);
//while (1){

/*i2cwrite(addr_pca,6,1);//6lsb 7msb temps jusqu'a allumage
i2cwrite(addr_pca,7,0);
i2cwrite(0x40,8,0X88);//8lsb 8msb temps jusqu'a extinction
i2cwrite(0x40,9,0);*/
servocmd(-90,6);
robotarduinomoteur(2,1,255);
robotarduinomoteur(1,1,255);
sleep(1);
robotarduinomoteur(2,0,255);
robotarduinomoteur(1,0,255);

/*i2cwrite(addr_pca,6,1);
i2cwrite(addr_pca,7,0);
//i2cwrite(0x40,8,0x9a);
/*i2cwrite(0x40,8,0x39);
i2cwrite(0x40,9,1);*/
servocmd(0,6);
sleep(1);
/*
i2cwrite(0x40,8,0xF8);
i2cwrite(0x40,9,1);*/
servocmd(90,6);
sleep(1);
robotarduinoalim(3,0);
robotarduinoalim(2,0);
while(1){robotarduinoread();
}
//       printf("Ubat:%d U1: %d U2: %d U3: %d\n",Ubat,U1,U2,U3);



  return 0;
}

