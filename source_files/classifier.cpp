#include "../header_files/header.hpp"

Classifier::Classifier(string trainImagesPath, string testImagesPath){
    this->trainImages = loadData(trainImagesPath);
    this->testImages = loadData(testImagesPath);
    this->nTestImages = testImages.size();
    this->nTrainImages = trainImages.size();
}

vector<Image> Classifier::loadData(string rootPath){
    vector<Image> imageList;
    for (auto & p : fs::directory_iterator(rootPath)){
        vector<string> catPath = split(p.path().string(), '/');
        string cat = catPath[catPath.size() - 1];
        for (auto & pInside : fs::directory_iterator(rootPath + "/" + cat)){
            Image image(pInside.path().string(), cat);
            imageList.push_back(image);
        }
    }
    return imageList;
}

void Classifier::predict(){
    vector<vector<vector<string>>> predictList;
    predictList.push_back(predictBGR());
    predictList.push_back(predictHSV());
    predictList.push_back(predictYCrCb());
    predictList.push_back(predictGray());
    generateCSV(predictList, "predicts.csv");
}

vector<vector<string>> Classifier::doPredict(char id){
    vector<vector<string>> predict;
    double minDistance;
    int minTrainDistanceImage;
    for (int i = 0; i < nTestImages; i++) {
        vector<Mat> bgrHistTest = getCalcHistById(testImages[i], id);
        int minTrainDistanceImage = 0;
        for (int j = 0; j < nTrainImages; j++) {
            vector<Mat> bgrHistTrain = getCalcHistById(trainImages[j], id);
            double distance = calculateTotalDistance(bgrHistTest, bgrHistTrain);
            if (j == 0){
                minDistance = distance;
                minTrainDistanceImage = j;
            }
            if (distance < minDistance) { 
                minDistance = distance;
                minTrainDistanceImage = j;
            }
        }
        int predictValue = trainImages[minTrainDistanceImage].getCategory() 
            == testImages[i].getCategory() ? 1 : 0;
        vector<string> item;
        item.push_back(testImages[i].getCategory());
        item.push_back(to_string(predictValue));
        predict.push_back(item);
    }
    return predict;
}

vector<Mat> Classifier::getCalcHistById(Image image, char id) {
    switch (id) {
    case 'b':
        return image.calcBGRHist();
        break;
    case 'h':
        return image.calcHSVHist();
        break;
    case 'y':
        return image.calcYCrCbHist();
        break;
    case 'g':
        return image.calcGrayHist();
        break;
    default:
        return image.calcGrayHist();
        break;
    }
}

vector<vector<string>> Classifier::predictBGR(){
    return doPredict('b');
}

vector<vector<string>> Classifier::predictHSV(){
    return doPredict('h');
}

vector<vector<string>> Classifier::predictYCrCb(){
    return doPredict('y');
}

vector<vector<string>> Classifier::predictGray(){
    return doPredict('g');
}

double Classifier::calculateTotalDistance(vector<Mat> hist1, vector<Mat> hist2){
    double totalDistance = 0.0;
    if (hist1.size() == hist2.size()) {
        int nHist = hist1.size();
        totalDistance = 0.0;
        for (int i = 0; i < nHist; i++) {
            totalDistance += calculateDistance(hist1[i], hist2[i]);
        }
    } else{
        cout << "\nERROR >>> Classifier::calculateTotalDistance(vector<Mat> hist1, "
        "vector<Mat> hist2) >> hist1 y hist2 Deben ser del mismo tamaño" << endl;
    }
    return totalDistance;
}

double Classifier::calculateDistance(cv::Mat hist1, cv::Mat hist2){
    double distance = 0.0;
    if (hist1.size() == hist2.size()) {
        int nRows = hist1.rows;
        for (int i = 0; i < nRows; i++){
            distance += distance 
                + pow((double)hist2.at<float>(i) - (double)hist1.at<float>(i), 2.0);
        }
        distance = sqrt(distance);
    } else {
        cout << "\nERROR >>> Classifier::calculateDistance(cv::Mat hist1,"
            << "cv::Mat hist2) >> hist1 y hist2 Deben ser del mismo tamaño" << endl;
    }
    return distance;
}

/**
 * hist1 = [1,2,31,1,12,2,3]
 * hist2 = [1,2,31,1,12,2,3]
 * 
 * 
 * 
 */

bool Classifier::generateCSV(vector<vector<vector<string>>> data, string name) {
    fs::create_directory("../reports");
    ofstream _buffer("../reports/" + name, ios::out);
    _buffer << "image,category,bgr,hsv,ycrcb,gray" << endl;
    for (int i = 0; i < data[0].size(); i++) {
        _buffer << testImages[i].getImage();
        for (int j = 0; j < data.size(); j ++) { 
            if (j== 0)
                _buffer << "," << data[j][i][0];
            _buffer << "," << data[j][i][1];
        }
        _buffer << endl;
    }
    _buffer.close();
    return true;
}

vector<string> Classifier::split(string cad, char sep){
    stringstream ss;
    ss << cad;
    vector<string> data;

    string token = "";
    while((getline(ss,token,sep))){
        data.push_back(token);
    }

    return data;
}

void Classifier::printImages(vector<Image> imagesList){
    int n = imagesList.size();
    cout << "\n\tTamaño: " << n << endl;
    for (int i = 0; i< n; i++) {
        imagesList[i].toString();
    }
}

/**
 * Getters and Setters
 **/

cv::Mat Classifier::getImage(){
    return image;
}

vector<Image> Classifier::getTrainImages(){
    return trainImages;
}

vector<Image> Classifier::getTestImages(){
    return testImages;
}