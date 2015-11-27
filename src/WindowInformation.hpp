#ifndef WindowInformation_hpp
#define WindowInformation_hpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "MyPixel.hpp"
using namespace cv;
class WindowInformation {
    public :
        WindowInformation(MyPixel originalStartingPixel,Size originalSize);
        MyPixel GetOriginalStartingPixel();
        Size GetOriginalSize();
        float GetScore();
        void SetScore(float score);
    private :
    MyPixel originalStartingPixel;
    Size originalSize;
    float score;
};
#endif
