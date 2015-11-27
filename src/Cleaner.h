#ifndef CLEANER_H
#define CLEANER_H

#include "WindowInformation.hpp"

#define CLUSTERING_MEANSHIFT 0
#define CLUSTERING_RDBSCAN 1
#define WINDOWS_CSV "~windows.csv"
#define CLUSTERS_CSV "~cluster.csv"
#define DEFAUTLT_QUANTILE 0.2

using namespace std;
class Cleaner
{
    public:
        Cleaner(vector <WindowInformation> * faceWindows);
        virtual ~Cleaner();
        void process();
        void SetQuantile(float quantile);
    protected:
    private:
		vector <WindowInformation> * faceWindows;
		float quantile;
		unsigned int clusteringAlgorithm;
		void write_to_csv();
		vector<WindowInformation>* read_from_csv();
};

#endif // CLEANER_H
