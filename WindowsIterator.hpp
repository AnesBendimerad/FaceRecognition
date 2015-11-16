#ifndef WindowsIterator_hpp
#define WindowsIterator_hpp
#define CPU_ONLY
#define USE_OPENCV
#include <caffe/caffe.hpp>
#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Window.hpp"
using namespace std;
class WindowsIterator {
    public :
    WindowsIterator (Mat * originalImage);
    void SetResizingRatio(double resizingRatio);
    void SetStep(int step);
    void SetWindowSize(Size windowSize);
    Window * GetNextWindow();

    private :
    void Reshape();
    cv::Mat  GetWindowFromImage();
    void IncrementPixel();
    bool IsRowIncrementable();
    bool IsColIncrementable();
    bool IsImageReshabable();

    Mat image;
    Size imageInitialSize;
    double resizingRatio;
    int step;
    Size windowSize;
    MyPixel currentStartingPixel;
    Size windowOriginalSize;
};
#endif
