#include "RepositoryFaceFinder.hpp"
#include "FaceFinder.hpp"

using namespace std;


int main(int argc, char** argv)
{
    if (argc==2)
    {
        string configFileName=argv[1];
        string inputFileName="",outputFileName="",resultFileName="",modelFileName="",trainedFileName="";
        int maxInitialSize=-1;
        float faceThreshold=-1,quantile=-1;
        string element;
        ifstream configFile(configFileName.c_str());
        if (configFile.is_open())
        {
            while (configFile>>element)
            {
                if (element.compare("inputFile")==0)
                {
                    configFile>>inputFileName;
                }
                else if (element.compare("outputFile")==0)
                {
                    configFile>>outputFileName;
                }
                else if (element.compare("resultFile")==0)
                {
                    configFile>>resultFileName;
                }
                else if (element.compare("modelFile")==0)
                {
                    configFile>>modelFileName;
                }
                else if (element.compare("trainedModelFile")==0)
                {
                    configFile>>trainedFileName;
                }
                else if (element.compare("maxInitialSize")==0)
                {
                    configFile>>maxInitialSize;
                }
                else if (element.compare("faceThreshold")==0)
                {
                    configFile>>faceThreshold;
                }
                else if (element.compare("quantile")==0)
                {
                    configFile>>quantile;
                }
                else {
                    cout<<"error :"<<element<<" doesn't exist as a parameter"<<endl;
                    return -1;
                }
            }
            cout<<"input :"<<inputFileName<<endl;
            cout<<"output :"<<outputFileName<<endl;
            cout<<"result :"<<resultFileName<<endl;
            cout<<"model :"<<modelFileName<<endl;
            cout<<"trained :"<<trainedFileName<<endl;
            cout<<"max size :"<<maxInitialSize<<endl;
            cout<<"threshold :"<<faceThreshold<<endl;
            cout<<"quantile"<<quantile<<endl;
            if ((inputFileName.compare("")==0) ||
                (outputFileName.compare("")==0) ||
                (resultFileName.compare("")==0) ||
                (modelFileName.compare("")==0) ||
                (trainedFileName.compare("")==0)){
                    cout<<"required parameters are missing"<<endl;
                    return -1;
                }
            FaceFinder *faceFinder=new FaceFinder(modelFileName,trainedFileName);
            if (maxInitialSize!=-1)
            {
                faceFinder->SetMaxInitialSize(maxInitialSize);
            }
            if (faceThreshold!=-1)
            {
                faceFinder->SetFaceThreshold(faceThreshold);
            }
            if (quantile!=-1)
            {
                faceFinder->SetQuantile(quantile);
            }
            DIR *inputDirectory = opendir(inputFileName.c_str());
            if (inputDirectory!=NULL){
                cout<<"repository face finding"<<endl;
                closedir(inputDirectory);
                RepositoryFaceFinder * repFaceFinder=new RepositoryFaceFinder(faceFinder);
                repFaceFinder->run(inputFileName,outputFileName,resultFileName);

            }
            else {
                cout<<"face finding for only one image"<<endl;
                string inputImageDirectName=inputFileName;
                unsigned int lastindex = inputFileName.find_last_of("/");
                if (lastindex<=inputFileName.size()){
                    inputImageDirectName=inputFileName.substr(lastindex+1, inputFileName.size());
                }
                DIR *outputDirectory = opendir(outputFileName.c_str());
                if (outputDirectory!=NULL)
                {
                    closedir(outputDirectory);
                }
                else
                {
                    mkdir(outputFileName.c_str(),0700);
                }
                vector<string> resultsText=faceFinder->FindFace(inputFileName,outputFileName+ "/" + inputImageDirectName);
                ofstream resultsFile (resultFileName.c_str(), ofstream::out);
                for (unsigned int j=0;j<resultsText.size();j++){
                    resultsFile<<resultsText[j]<<endl;
                }
                resultsFile.close();
            }
        }
    }
    else {
        cout<<"error : you must specify a configuration file"<<endl;
    }
}
