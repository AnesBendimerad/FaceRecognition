#include "RepositoryFaceFinder.hpp"
RepositoryFaceFinder::RepositoryFaceFinder(FaceFinder * faceFinder)
{
    RepositoryFaceFinder::faceFinder=faceFinder;
}
void RepositoryFaceFinder::run(string inputRepositoryPath,string outputRepositoryPath,string resultTextFilePath)
{
    struct dirent *fileEntity;
    vector<string> pathList;
    DIR *inputDirectory = opendir(inputRepositoryPath.c_str());
    if (inputDirectory == NULL) {
		throw runtime_error("Failed when openning input directory");
	}
    while ((fileEntity = readdir(inputDirectory)) != NULL) {
        if (strcmp(fileEntity->d_name, ".") != 0 && strcmp(fileEntity->d_name, "..") != 0)
        {
            pathList.push_back(string(fileEntity->d_name));
        }
    }
    DIR *outputDirectory = opendir(outputRepositoryPath.c_str());
    if (outputDirectory==NULL)
    {
        mkdir(outputRepositoryPath.c_str(),0700);
    }
    ofstream resultsFile (resultTextFilePath.c_str(), ofstream::out);
    vector<string> results;
    for (int i=0;i<pathList.size();i++)
    {
        try {
            results=faceFinder->FindFace(inputRepositoryPath + "/" + pathList[i],outputRepositoryPath+ "/" + pathList[i]);
            for (int j=0;j<results.size();j++){
                resultsFile<<results[j]<<endl;
            }
        } catch (Exception exception) {
            cout << exception.msg<<" with "<< inputRepositoryPath + "/" + pathList[i] << endl;
        }
    }
    resultsFile.close();
    closedir(inputDirectory);
    closedir(outputDirectory);
}
