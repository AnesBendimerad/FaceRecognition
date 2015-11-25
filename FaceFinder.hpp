#ifndef FaceFinder_hpp
#define FaceFinder_hpp
#include <string>
#include "Window.hpp"
#include "Classifier.hpp"
#include "WindowsIterator.hpp"
#include "Drawer.hpp"
#include "Cleaner.h"
#define FACE_THRESHOLD 0.6
using namespace std;
class FaceFinder
{
public:
    FaceFinder(const string& model_file,const string& trained_file);
    vector<string> FindFace(const string& inputImgFile,const string& outputImgFile);
    void SetMaxInitialSize(int maxInitialSize);
    void SetFaceThreshold(float faceThreshold);

private:
    vector<string> Find(Mat* img,string fileName);
    int GetWindowLabel(vector<float> scores);
    void CleanFaceWindows(vector <WindowInformation> * faceWindows);

private:

    Classifier * classifier;
    int maxInitialSize;
    float faceThreshold;

};
#endif
