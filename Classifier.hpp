#ifndef Classifier_hpp
#define Classifier_hpp
#define CPU_ONLY
#define USE_OPENCV
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>


using namespace caffe;
using std::string;

class Classifier {
 public:
  Classifier(const string& model_file,const string& trained_file);

  /* return for each class its score. The vector is
   * ordered by class name (ex : "0", "1" for face recognizer)
   */
  std::vector<float> Classify(const cv::Mat& img);

 private:

  std::vector<float> Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,std::vector<cv::Mat>* input_channels);

 private:

  shared_ptr<Net<float> > net_;

  cv::Size input_geometry_;
};
#endif
