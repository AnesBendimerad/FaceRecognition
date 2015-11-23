#include "Drawer.hpp"
void Drawer::DrawFaceWindows(Mat* img,vector<WindowInformation> * faceWindows)
{
    for (int i=0;i<faceWindows->size();i++){
        DrawFaceWindow(img,&((*faceWindows)[i]));
    }
}
void Drawer::DrawFaceWindow(Mat* img, WindowInformation * faceWindow)
{

    Point pt1(faceWindow->GetOriginalStartingPixel().col,faceWindow->GetOriginalStartingPixel().row);
    Point pt2(faceWindow->GetOriginalStartingPixel().col+faceWindow->GetOriginalSize().width,faceWindow->GetOriginalStartingPixel().row+faceWindow->GetOriginalSize().height);
    if (*img->data != NULL)
    {
        cv::rectangle(
            *img,
            pt1,
            pt2,
            cv::Scalar(126, 213, 239),
            1
        );
    }
}
