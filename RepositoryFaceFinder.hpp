#ifndef RepositoryFaceFinder_hpp
#define RepositoryFaceFinder_hpp
#include "FaceFinder.hpp"
#include <dirent.h>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;
class RepositoryFaceFinder
{
public:
    RepositoryFaceFinder(FaceFinder * faceFinder);
    void run(string inputRepositoryPath,string outputRepositoryPath,string resultTextFilePath);
private:

private:
    FaceFinder * faceFinder;
};
#endif
