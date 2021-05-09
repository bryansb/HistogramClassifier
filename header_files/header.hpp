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
        string imagePath;
    
    public:
        Image(string, string = "empty");
        cv::Mat readImage();
        vector<cv::Mat> calcBGRHist();
        vector<cv::Mat> calcHSVHist();
        vector<cv::Mat> calcYCrCbHist();
        vector<cv::Mat> calcGrayHist();
        string getCategory();
        string getImage();
        cv::Mat getImageHSV();
        cv::Mat getImageYCbCr();
        cv::Mat getImageGray();

        void toString();

};

class Classifier { 
    private:
        cv::Mat image;
        vector<Image> trainImages;
        vector<Image> testImages;
        int nTrainImages;
        int nTestImages;

        vector<vector<string>> doPredict(char);
        vector<Mat> getCalcHistById(Image, char);

    public:
        Classifier(string, string);
        vector<Image> loadData(string);
        void predict();
        vector<vector<string>> predictBGR();
        vector<vector<string>> predictHSV();
        vector<vector<string>> predictYCrCb();
        vector<vector<string>> predictGray();
        double calculateTotalDistance(vector<Mat>, vector<Mat>);
        double calculateDistance(cv::Mat, cv::Mat);
        bool generateCSV(vector<vector<vector<string>>>, string);
        void printImages(vector<Image>);
        vector<string> split(string cad, char sep);

        cv::Mat getImage();
        vector<Image> getTrainImages();
        vector<Image> getTestImages();
};