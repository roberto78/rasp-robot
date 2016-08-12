
void aff_text(char buffer[25],CvArr* fenet)
{
CvFont font;
cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);
cvPutText(fenet, buffer, cvPoint(30, 30), &font, cvScalar(255,255,255));
}
