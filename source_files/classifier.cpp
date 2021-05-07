#include "../header_files/header.hpp"

Classifier::Classifier(string imagesPath){
    this->imagesPath = imagesPath;
}

void Classifier::loadData(){
    for (auto & p : fs::directory_iterator(imagesPath)){
        vector<String> imagePath;
        // string fileName = p.path();
        // vector<string> token = split(fileName, '/');
        // imagePath.push_back(token[1]);
        // imagePath.push_back(token[2]);
        // trainImagesPath.push_back(imagePath);

        vector<string> catPath = split(p.path().string(), '/');

        string cat = catPath[catPath.size() - 1];

        for (auto & pInside : fs::directory_iterator(imagesPath + "/" + cat)){
            // vector<string> imagePathFile = split(pInside.path(), '/');
            // string imageFile = imagePathFile[imagePathFile.size() - 1];
            imagePath.push_back(cat);
            imagePath.push_back(pInside.path().string());
            trainImagesPath.push_back(imagePath);
        }
    }
}

void Classifier::predict(string path){

}

int Classifier::calculateDistance(cv::Mat image1, cv::Mat image2){

    return 0;
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

void Classifier::printTrainImagesPath(){
    int n = trainImagesPath.size();
    cout << "tamaño: " << n << endl;
    for (int i = 0; i< trainImagesPath.size(); i++) {
        cout << "Cat=" << trainImagesPath[i][0] 
            << " | image="  << trainImagesPath[i][1] << endl;
    }
}