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
#include "RepositoryFaceFinder.hpp"
#include "FaceFinder.hpp"

using namespace std;


int main(int argc, char** argv)
{

   // RepositoryFaceFinder * repFaceFinder=new RepositoryFaceFinder(new FaceFinder("facenet_train_test.prototxt","facenet.caffemodel"));
    //repFaceFinder->run("images2","results2","resultText.txt");

    FaceFinder *faceFinder=new FaceFinder("facenet_train_test.prototxt","facenet.caffemodel");
   // faceFinder->setMaxInitialSize(200);
    faceFinder->SetMaxInitialSize(150);

    faceFinder->FindFace("images/faceface.jpg","results/lwjehkbir.jpg");

}
