#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp> 

using namespace std;
using namespace cv;

namespace fs =  std::experimental::filesystem;

class Image {
    private:
        string category;
        cv::Mat image;
    
    public:
        Image(cv::Mat, string = "empty");

};

class Classifier { 
    private:
        string imagesPath;
        cv::Mat image;
        vector<vector<string>> trainImagesPath;

    public:
        Classifier(string);
        void loadData();
        void predict(string);
        int calculateDistance(cv::Mat, cv::Mat);
        void printTrainImagesPath();
        vector<string> split(string cad, char sep);
};