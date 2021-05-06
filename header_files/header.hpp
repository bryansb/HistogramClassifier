#include <iostream>
#include <cstdlib>
#include <cstring>

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp> 

using namespace std;
using namespace cv; 

class Image {
    private:
        string category;
        cv::Mat image;
    
    public:
        Image(cv::Mat, string = "empty");

};

class Classifier { 
    private:
        cv::Mat image;
        cv::Mat images[30];

    public:
        Classifier(cv::Mat[]);
        void predict(string);
        int calculateDistance(cv::Mat, cv::Mat);
};