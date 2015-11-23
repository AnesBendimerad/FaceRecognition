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
    private :
    MyPixel originalStartingPixel;
    Size originalSize;
};
#endif
