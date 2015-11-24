#include "FaceFinder.hpp"


FaceFinder::FaceFinder(const string& model_file,const string& trained_file)
{
    classifier=new Classifier(model_file,trained_file);
    maxInitialSize=-1;
    faceThreshold=FACE_THRESHOLD;
}
vector<string> FaceFinder::Find(Mat* img,string fileName)
{
    WindowsIterator * windowsIterator;
    if (maxInitialSize==-1)
    {
        windowsIterator=new WindowsIterator(img);
    }
    else
    {
        windowsIterator=new WindowsIterator(img,maxInitialSize);
    }
    vector<WindowInformation> faceWindows;
    Window *window;
    vector<float> scores;
    while ((window=windowsIterator->GetNextWindow())!=NULL){
        scores=classifier->Classify(window->GetWindowImage());
        if (GetWindowLabel(scores)==1)
        {
            window->GetWindowInformation()->SetScore(scores[1]);
            faceWindows.push_back(*(window->GetWindowInformation()));
        }
    }
    //CleanFaceWindows(&faceWindows);
    Drawer *drawer=new Drawer();
    drawer->DrawFaceWindows(img,&faceWindows);
    vector<string> resultTexts;
    for (unsigned int i=0;i<faceWindows.size();i++)
    {
        std::ostringstream myStringStream;
        myStringStream<<fileName<<" ";
        myStringStream<<faceWindows[i].GetScore()<<" ";
        myStringStream<<faceWindows[i].GetOriginalStartingPixel().col<<" ";
        myStringStream<<faceWindows[i].GetOriginalStartingPixel().row<<" ";
        myStringStream<<faceWindows[i].GetOriginalSize().width<<" ";
        myStringStream<<faceWindows[i].GetOriginalSize().height;
        string myString(myStringStream.str());
        resultTexts.push_back(myString);
    }
    return resultTexts;
}

vector<string> FaceFinder::FindFace(const string& inputImgFile,const string& outputImgFile)
{
    Mat image= imread(inputImgFile, -1);
    int lastindex = inputImgFile.find_last_of(".");
    string fileName;
    if (lastindex<=inputImgFile.size())
    {
        fileName=inputImgFile.substr(0, lastindex);
    }
    else
    {
        fileName=inputImgFile;
    }
    lastindex = fileName.find_last_of("/");
    if (lastindex<=fileName.size())
    {
        fileName=fileName.substr(lastindex+1, fileName.size());
    }

    vector<string> resultTexts=Find(&image,fileName);
    imwrite(outputImgFile.c_str(),image);
    return resultTexts;
}
int FaceFinder::GetWindowLabel(vector<float> scores)
{
    if (scores.size()!=2){
        return -1;
    }
    if (scores[1]>faceThreshold){
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
void FaceFinder::SetMaxInitialSize(int maxInitialSize){
    FaceFinder::maxInitialSize=maxInitialSize;
}
void FaceFinder::SetFaceThreshold(float faceThreshold)
{
    FaceFinder::faceThreshold=faceThreshold;
}
void FaceFinder::CleanFaceWindows(vector <WindowInformation> *faceWindows)
{
    cout<<"Cleaning..."<<endl;
    MeanShift meanShift(faceWindows);
    meanShift.process();
}
