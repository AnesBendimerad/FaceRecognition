#define CPU_ONLY
#define USE_OPENCV
#include <caffe/caffe.hpp>
#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "FaceFinder.hpp"
#include "MeanShift.h"

using namespace std;


int main(int argc, char *argv[])
{
    /*if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0]
                  << " deploy.prototxt network.caffemodel"
                  << " mean.binaryproto labels.txt img.jpg" << std::endl;
        return 1;
    }
    ::google::InitGoogleLogging(argv[0]);
    string model_file   = argv[1];
    string trained_file = argv[2];
    Classifier classifier(model_file, trained_file);
    string file = argv[3];
    std::cout << "---------- Prediction for "
              << file << " ----------" << std::endl;
    cv::Mat img = cv::imread(file, -1);
    CHECK(!img.empty()) << "Unable to decode image " << file;
    std::vector<float> predictions = classifier.Classify(img);
    for (size_t i = 0; i < predictions.size(); ++i)
    {
        std::cout << std::fixed << std::setprecision(4) << predictions[i] << std::endl;
    }*/
    /*Mat img = cv::imread("cat.jpg", -1);
    //string name="window_sample_1.pgm";

    //imwrite(name.c_str(),image2);
    WindowsIterator * windowsIterator=new WindowsIterator(&img);
    Size windowSize(350,350);
    windowsIterator->SetWindowSize(windowSize);
    Window *window;
    int i=0;
    string name="window_sample";
    string num="";
    while ((window=windowsIterator->GetNextWindow())!=NULL){
        cout<<"col="<<window->GetWindowInformation()->GetOriginalStartingPixel().col<<endl;
        cout<<"row="<<window->GetWindowInformation()->GetOriginalStartingPixel().row<<endl;
        cout<<"width="<<window->GetWindowInformation()->GetOriginalSize().width<<endl;
        cout<<"height="<<window->GetWindowInformation()->GetOriginalSize().height<<endl;
        cout<<i<<endl;
        //imwrite(name.c_str(),(window->GetWindowImage()));
        i++;
    }*/
    FaceFinder *faceFinder=new FaceFinder("facenet_train_test.prototxt","facenet.caffemodel");
    faceFinder->FindFace("images/Picture2.png","results/Picture2Cluster.png");

  // MeanShift MeanShift;
   //MeanShift.process();
    //faceFinder->FindFace("example_png.png","example_png_face_found.pgm");

}
