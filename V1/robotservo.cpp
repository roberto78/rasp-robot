void servocmd(signed char angle,unsigned char numeropwm);
void servoinit(void);



//necessite roboti2c.cpp
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

#include <math.h>
//constante pour librairie servo
const unsigned char addr_pca=0x40;
const unsigned char prescal_pca=121;
//const unsigned char prescal_pca=128;
const int pwm_centre_pca[16]={0x139,0x118,0x180,0x130,0x139,0x139,0x139,0x139,0x139,0x139,0x139,0x139,0x139,0x139,0x139,0x139};
const double pwm_angle_ratio_pca[16]={2.12,2.12,0.3,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12,2.12};
int pwminitvalue[16]={0,-70,-90,40,-30,0,0,0,0,0,0,0,0,0};
//servo2




//fonction pour librairie servo


//numeropwm commence à 0
void servocmd(signed char angle,unsigned char numeropwm)
{
unsigned int cmd;
unsigned char cmdl;
unsigned char cmdh;
int tmp;
tmp=round(pwm_centre_pca[numeropwm]+pwm_angle_ratio_pca[numeropwm]*angle);
cmd=tmp;
cmdl=cmd&0xff;
cmdh=(cmd>>8)&0x0f;
char addr_reg_pwm=6+(4*numeropwm);
roboti2cwrite(addr_pca,addr_reg_pwm,0);
roboti2cwrite(addr_pca,(addr_reg_pwm+1),0);
roboti2cwrite(addr_pca,(addr_reg_pwm+2),cmdl);
roboti2cwrite(addr_pca,(addr_reg_pwm+3),cmdh);
}


void servoinit(void)
{
roboti2cwrite(addr_pca,0,128);//reset
usleep(10000);
roboti2cwrite(addr_pca,0,0);
roboti2cwrite(addr_pca,0,16);
roboti2cwrite(addr_pca,254,prescal_pca);//prescal 50hz
usleep(10000);
roboti2cwrite(addr_pca,0,0);
//i2cwrite(addr_pca,0,0xa1);
usleep(10000);
//i2cwrite(addr_pca,1,0x04);
//usleep(10000);
//pwm0 =0
int cptpwm=0;
while (cptpwm<15){
servocmd(pwminitvalue[cptpwm],cptpwm);
cptpwm++;
}
}

