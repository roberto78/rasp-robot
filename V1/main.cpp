#include <iostream>
#include <unistd.h>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <proc/readproc.h>
#include <opencv2/opencv.hpp>


const bool debugon=true;


#include "roboti2c.cpp"
#include "robotservo.cpp"
#include "robotarduino.cpp"

#include "fonc.cpp"
#include "webcam.cpp"




using namespace std;
using namespace cv;
char key;
CvCapture* webcam1;
cv::Mat* framem;
bool graphique=false;

const int hauteur=480;
const int largeur=640;







void init()
{
if (!getenv("DISPLAY")){system("echo mode console");}else{system("echo mode graphique");graphique=true;}

if (graphique){ cvNamedWindow("Fenetre", 1);    //Create window
                cvResizeWindow("Fenetre",hauteur,largeur);
                }

  if(webcam_init()!=0)
    {
    exit(1);
  }else{
system("echo webcam initialisée");}


robotarduinoalim(3,1);
robotarduinoalim(2,1);
sleep(1);
servoinit();

}

void fin()
{
if (graphique){cvDestroyWindow("Fenetre");} //Destroy Window
system("echo fin du programme");
 }










int main()
{cv::Mat tmp[10];
cv::Mat* framem1;
int nbdecalc=0;
bool first=true;
int cumulx=0;
int cumuly=0;
    init();
    int cptptrframe=0;
    int cptptrframe1=0;
    while(1){

robotarduinoalim(3,1);
robotarduinoalim(2,1);
        robotarduinoread();



     cptptrframe++;
     if (cptptrframe>9){cptptrframe=0;cptptrframe1=9;}else{cptptrframe1=cptptrframe-1;}
    framem1=&tmp[cptptrframe1];
    framem=&tmp[cptptrframe];
    camera >> *framem;
    if (!first){score=compare_multiple_mat_webcam(*framem,300,220,*framem1,300,220,80,80,100,40,20);cumulx+=coordimageresx;cumuly+=coordimageresy;}

nbdecalc++;
char tmp[10];

/*sprintf(tmp,"echo x0:%d y0:%d score:%d nb de calcul:%d",cumulx,cumuly,score,nbdecalc);
system(tmp);*/
printf("x0:%d y0:%d score:%d nb de calcul:%d",cumulx,cumuly,score,nbdecalc);

if (!first){
  if (graphique){cv::imshow("Fenetre", *framem);}
        key = ((cvWaitKey(10))&0xff);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
        if (char(key) == 'a'){robotarduinomoteur(2,1,0x5f);}
        if (char(key) == 'q'){robotarduinomoteur(2,0,0);}
        if (char(key) == 'w'){robotarduinomoteur(2,2,0x5f);}
        if (char(key) == 'z'){robotarduinomoteur(1,1,0x5f);}
        if (char(key) == 's'){robotarduinomoteur(1,0,0);}
        if (char(key) == 'x'){robotarduinomoteur(1,2,0x5f);}
        if (char(key) == 'e'){cumulx=0;robotarduinomoteur(1,1,0x7f);robotarduinomoteur(2,2,0x7f);//sleep(1);robotarduinomoteur(2,1,0xff);
        }//rotation auto
       // if ((abs(cumulx))>200){robotarduinomoteur(2,0,0);robotarduinomoteur(1,0,0);}
        }
           first=false;
    }
   fin();
   return 0;
}













