#include "FaceFinder.hpp"


FaceFinder::FaceFinder(const string& model_file,const string& trained_file)
{
    classifier=new Classifier(model_file,trained_file);
}
void FaceFinder::Find(Mat* img)
{
    WindowsIterator * windowsIterator=new WindowsIterator(img);
    vector<WindowInformation> faceWindows;
    Window *window;
    vector<float> scores;
    while ((window=windowsIterator->GetNextWindow())!=NULL){
        scores=classifier->Classify(window->GetWindowImage());
        if (GetWindowLabel(scores)==1)
        {
            faceWindows.push_back(*(window->GetWindowInformation()));
        }
    }
    CleanFaceWindows(&faceWindows);
    Drawer *drawer=new Drawer();
    drawer->DrawFaceWindows(img,&faceWindows);

}

void FaceFinder::FindFace(const string& inputImgFile,const string& outputImgFile)
{
    Mat image= imread(inputImgFile, -1);
    Find(&image);
    imwrite(outputImgFile.c_str(),image);
    // imwrite : write the image in the outputImgFile
}
int FaceFinder::GetWindowLabel(vector<float> scores)
{
    if (scores.size()!=2){
        return -1;
    }
    if (scores[1]>0.6){
        return 1;
    }
    else {
        return 0;
    }
/*
    if (scores[0]>scores[1])
    {
        return 0;
    }
    else
    {
        return 1;
    }*/
}

void FaceFinder::CleanFaceWindows(vector <WindowInformation> * faceWindows)
{
    // choose the most relevant windows in the vector
}
