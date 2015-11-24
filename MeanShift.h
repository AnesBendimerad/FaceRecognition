#ifndef MEANSHIFT_H
#define MEANSHIFT_H
#include<vector>
#include "WindowInformation.hpp"

class MeanShift
{
    public:
        MeanShift(vector <WindowInformation> * faceWindows);
        MeanShift();
        virtual ~MeanShift();
        void process();
    protected:
    private:
    vector <WindowInformation> * faceWindows;
    void write_to_csv();
    vector<WindowInformation>* read_from_csv(double);
};

#endif // MEANSHIFT_H
