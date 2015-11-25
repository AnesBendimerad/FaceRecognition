#include "Cleaner.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Cleaner::Cleaner(vector<WindowInformation>* faceWindows)
{
this->faceWindows = faceWindows;
}

Cleaner::~Cleaner()
{
}
void Cleaner::write_to_csv()
{
      ofstream myfile;
      myfile.open ("input.csv");

      myfile <<"x,y,width,height,score\n";

      for(unsigned int i=0;i<faceWindows->size();i++) {
        myfile <<faceWindows->at(i).GetOriginalStartingPixel().row;
        myfile <<",";
        myfile <<faceWindows->at(i).GetOriginalStartingPixel().col;
        myfile <<",";
        myfile <<faceWindows->at(i).GetOriginalSize().width;
        myfile <<",";
        myfile <<faceWindows->at(i).GetOriginalSize().height;
        myfile <<",";
        myfile <<faceWindows->at(i).GetScore();
        myfile <<"\n";
      }

      myfile.close();
}

vector<WindowInformation>* Cleaner::read_from_csv()
{
     ifstream myfile;
     string line,cell;
     myfile.open ("output.csv");
     vector<WindowInformation> *result = new vector<WindowInformation> ();
     Size originalSize;
     MyPixel originalPixel;
     float score;

      //read headers
      getline(myfile,line);

      while(getline(myfile,line))
      {
        stringstream  lineStream(line);
        getline(lineStream,cell,',');
        getline(lineStream,cell,',');
        originalPixel.row = atoi(cell.c_str());
        getline(lineStream,cell,',');
        originalPixel.col = atoi(cell.c_str());
        getline(lineStream,cell,',');
        originalSize.width = atof(cell.c_str());
        getline(lineStream,cell,',');
        originalSize.height = atof(cell.c_str());
        getline(lineStream,cell,',');
        score = atof(cell.c_str());
        WindowInformation windowInformation(originalPixel,originalSize);
        windowInformation.SetScore(score);
        result->push_back(windowInformation);
      }

     return result;
}

void Cleaner::process()
{
   std::stringstream stream;
   string algorithm;
   string quantile;
   string cmd ="python clean.py";

   cout<<"Choose clustering algorithm, 0 for MeanShift and 1 for DBSCAN:"<<endl;
   cin>>algorithm;

   cout<<"Choose quantile between 0 and 1:"<<endl;
   cin>>quantile;

   cmd.append(" ").append(algorithm).append(" ").append("input.csv").append(" ").append("output.csv").append(" ").append(quantile);

   cout<<"Cleaning..."<<endl;

   //export data
   write_to_csv();

   // execute Clustering algorithm
   stream <<cmd;

   system(stream.str().c_str());

    //import data
   vector<WindowInformation> *clusters = read_from_csv();

   faceWindows->clear();

   for(unsigned int i=0;i<clusters->size();i++) {
        faceWindows->push_back(clusters->at(i));
    }

   delete clusters;
}
