#ifndef CLEANER_H
#define CLEANER_H
#include<vector>
#include "WindowInformation.hpp"

class Cleaner
{
    public:
        Cleaner(vector <WindowInformation> * faceWindows);
        virtual ~Cleaner();
        void process();
    protected:
    private:
    vector <WindowInformation> * faceWindows;
    void write_to_csv();
    vector<WindowInformation>* read_from_csv();
};

#endif // CLEANER_H
