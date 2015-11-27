#ifndef Window_hpp
#define Window_hpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "WindowInformation.hpp"
using namespace cv;
class Window {
    public :
        Window(WindowInformation * windowInformation,Mat&  windowImage);
        WindowInformation *  GetWindowInformation();
        Mat & GetWindowImage();

    private :
    WindowInformation * windowInformation;
    Mat  windowImage;
};
#endif
