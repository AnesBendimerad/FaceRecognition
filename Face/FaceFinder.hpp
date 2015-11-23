#ifndef FaceFinder_hpp
#define FaceFinder_hpp
#include "Window.hpp"
#include "Classifier.hpp"
#include "WindowsIterator.hpp"
#include "Drawer.hpp"
class FaceFinder
{
public:
    FaceFinder(const string& model_file,const string& trained_file);
    void FindFace(const string& inputImgFile,const string& outputImgFile);

private:
    void Find(Mat* img);
    int GetWindowLabel(vector<float> scores);
    void CleanFaceWindows(vector <WindowInformation> * faceWindows);

private:

    Classifier * classifier;

};
#endif
