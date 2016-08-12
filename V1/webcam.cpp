#include <iostream>
#include <unistd.h>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <proc/readproc.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

cv::VideoCapture camera(0);
int score=0;

int coordimageresx=0;
int coordimageresy=0;

int webcam_init (void)
{
   if(!camera.isOpened())
  {
    std::cerr << "ERROR: Could not open camera" << std::endl;
 return 1;
  } else
  {
      return 0;
  }

}




inline int compare_mat_webcam(cv::Mat nouveau,int posnouveaux,int posnouveauy,cv::Mat ancien,int posancienx,int posancieny,int taillex,int tailley,int scoremax)
{

    int cptx=0;
    int cpty=0;
    int score1=0;
    int seuil1=0;
    int tmp=0;
    while (cptx<taillex){cptx++;cpty=0;
        while(cpty<tailley){
            tmp=nouveau.at<Vec3b>((cpty+posnouveauy),(posnouveaux+cptx)).val[0]-ancien.at<Vec3b>((posancieny+cpty),(posancienx+cptx)).val[0];
            tmp=abs(tmp);
               if (tmp<seuil1){tmp=0;}
               score1+=tmp;
               if (score1>scoremax){return score1;}
                cpty++;
                }
            }
            return score1;
}






inline int compare_multiple_mat_webcam(cv::Mat nouveau,int posnouveaux,int posnouveauy,cv::Mat ancien,int posancienx,int posancieny,int taillex,int tailley,int cherchex,int cherchey,int pas)
{int cptcherchex=-cherchex;
int cptcherchey=-cherchey;
int resmemx=0;
int resmemy=0;
int meilleurscore;
meilleurscore=compare_mat_webcam(nouveau,posnouveaux,posnouveauy,ancien,(posancienx),(posancieny),taillex,tailley,10000000);
int scoreactuel=0;
while (cptcherchex<cherchex){
    if ((abs(cptcherchex)<pas)){cptcherchex+=5;}else{cptcherchex+=pas;}

    cptcherchey=-cherchey;
    {while (cptcherchey<cherchey){
        scoreactuel=compare_mat_webcam(nouveau,posnouveaux,posnouveauy,ancien,(posancienx+cptcherchex),(posancieny+cptcherchey),taillex,tailley,meilleurscore);

        if (scoreactuel<=meilleurscore)
            {resmemx=cptcherchex;resmemy=cptcherchey;meilleurscore=scoreactuel;}
        if ((abs(cptcherchey)<pas)&(abs(cptcherchex)<pas)){cptcherchey+=5;}else{cptcherchey+=pas;}
        }

    }}

coordimageresx=resmemx;
coordimageresy=resmemy;
return (meilleurscore);
}
