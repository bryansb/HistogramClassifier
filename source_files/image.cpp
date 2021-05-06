#include "../header_files/header.hpp"

Image::Image(cv::Mat image, string category){
    this->image = image;
    this->category = category;
};

