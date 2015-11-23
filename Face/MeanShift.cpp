#include "MeanShift.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

MeanShift::MeanShift(vector<WindowInformation>* faceWindows)
{
this->faceWindows = faceWindows;
}

MeanShift::MeanShift()
{
}

MeanShift::~MeanShift()
{
}
void MeanShift::write_to_csv()
{

      ofstream myfile;
      myfile.open ("python/input.csv");

      myfile <<"row,col,width,height,row_center,col_center\n";

      for(unsigned int i=0;i<faceWindows->size();i++) {
        myfile <<faceWindows->at(i).GetOriginalStartingPixel().row;
        myfile <<",";
        myfile <<faceWindows->at(i).GetOriginalStartingPixel().col;
        myfile<<",";
        myfile <<faceWindows->at(i).GetOriginalSize().width;
        myfile<<",";
        myfile <<faceWindows->at(i).GetOriginalSize().height;
        myfile<<",";
        myfile <<(faceWindows->at(i).GetOriginalStartingPixel().row+ (faceWindows->at(i).GetOriginalStartingPixel().row+faceWindows->at(i).GetOriginalSize().width))/2;
        myfile<<",";
        myfile<<(faceWindows->at(i).GetOriginalStartingPixel().col+(faceWindows->at(i).GetOriginalStartingPixel().col+faceWindows->at(i).GetOriginalSize().height))/2;
        myfile <<"\n";
      }
      myfile.close();
}

vector<WindowInformation>* MeanShift::read_from_csv(double threshold)
{
      ifstream myfile;
      string line;
      string actual,previous="cluster0";
      vector<WindowInformation> cluster;
      vector<vector<WindowInformation> > clusters;
      vector<WindowInformation> *result = new vector<WindowInformation> ();
      MyPixel originalPixel;
      double N=0;

      myfile.open ("output.csv");
      //read headers
      getline(myfile,line);

      while(getline(myfile,line))
      {
        stringstream  lineStream(line);
        string        cell;
        Size originalSize;
        getline(lineStream,cell,',');
        getline(lineStream,cell,',');
        originalPixel.row = atoi(cell.c_str());
        getline(lineStream,cell,',');
        originalPixel.col = atoi(cell.c_str());
        getline(lineStream,actual,',');
        getline(lineStream,cell,',');
        originalSize.width = atof(cell.c_str());;
        getline(lineStream,cell,',');
        originalSize.height = atof(cell.c_str());;

        WindowInformation windowInformation(originalPixel,originalSize);
        cout<<windowInformation.GetOriginalSize()<<" ";
        cout<<windowInformation.GetOriginalStartingPixel().row<<" ";
        cout<<windowInformation.GetOriginalStartingPixel().col<<" ";
        cout<<actual<<" ";
        if(actual.compare(previous) ==0)
        {
        cluster.push_back(windowInformation);
        }
        else
        {
        clusters.push_back(cluster);
        cluster.clear();
        cluster.push_back(windowInformation);
        }
        previous = actual;
      }

      clusters.push_back(cluster);
      cluster.clear();
      myfile.close();

       for(unsigned int i=0;i<clusters.size();i++)
      {
      N = N + clusters.at(i).size();
      }

      for(unsigned int i=0;i<clusters.size();i++)
      {
      if(clusters.at(i).size() >= N*threshold)
      {
      result->push_back(clusters.at(i).at(0));
      }
      }

     return result;
}

void MeanShift::process()
{
   std::stringstream stream;
   double threshold;
   cout<<"Starting MeanShift"<<endl;
   cout<<"Enter value of threshold between 0 and 1"<<endl;
   cin>>threshold;

   //export data
   write_to_csv();

   // execute Mean_Shift algorithm
   stream << "python"
       << " "
       << "main.py";
   system(stream.str().c_str());

    //import data
    vector<WindowInformation> *clusters = read_from_csv(threshold);

    for(unsigned int i=0;i<clusters->size();i++) {
        cout<<clusters->at(i).GetOriginalStartingPixel().row<<" ";
        cout<<clusters->at(i).GetOriginalStartingPixel().col<<" ";
        cout<<clusters->at(i).GetOriginalSize()<<endl;
    }

    faceWindows->clear();
   for(unsigned int i=0;i<clusters->size();i++) {
        faceWindows->push_back(clusters->at(i));
    }
delete clusters;
}
