#ifndef Drawer_hpp
#define Drawer_hpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "WindowInformation.hpp"
using namespace std;

class Drawer {
 public:
    static void DrawFaceWindows(Mat* img,vector<WindowInformation> * faceWindows);

 private:
    static void DrawFaceWindow(Mat* img, WindowInformation * faceWindow);
 };
#endif
