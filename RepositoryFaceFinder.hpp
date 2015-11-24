#ifndef RepositoryFaceFinder_hpp
#define RepositoryFaceFinder_hpp
#include "FaceFinder.hpp"
#include <dirent.h>
#include <fstream>
#include <string>

using namespace std;
class RepositoryFaceFinder
{
public:
    RepositoryFaceFinder(const string& model_file,const string& trained_file);
    void run(string inputRepositoryPath,string outputRepositoryPath,string resultTextFilePath);
private:

private:
    FaceFinder * faceFinder;
};
#endif
