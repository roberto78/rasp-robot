void robotarduinoalim(char numeroalim,char cmd);
void robotarduinread(void);

//necessite roboti2c.cpp
const int addr_ard=0x08;
short int Ubat;

short int U1;
short int U2;
short int U3;
short int distance;

void robotarduinomoteur(char moteur,char sens,char valeur)
{
//1avance 2recule 0 arret
//1droite 2gauche
unsigned char reg;
unsigned char data;
if (moteur==1){reg=10;}else{reg=20;}
if (sens==0){reg=reg+2;}else {if (sens==1){reg=reg;}else{reg=reg+1;}}
data=valeur;

roboti2cwrite(addr_ard,reg,data);

}



void robotarduinoalim(char numeroalim,char cmd)
{
unsigned char reg;
unsigned char data;
if (numeroalim<=3){
reg=numeroalim;
if (cmd==0){data=0;}else{data=255;}
roboti2cwrite(addr_ard,reg,data);
}
}




void robotarduinoread(void)
{

unsigned char buf[10] = {0,0,0,0,0,0,0,0,0,0};
roboti2cread(addr_ard,10,buf);
Ubat=buf[1]*256+buf[0];

U1=buf[3]*256+buf[2];
U2=buf[5]*256+buf[4];
U3=buf[7]*256+buf[6];
distance=buf[9]*256+buf[8];
if (debugon){       printf("Ubat:%d U1:%d U2:%d U3:%d distance:%d\n",Ubat,U1,U2,U3,distance);}
  }

