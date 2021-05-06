#include "../header_files/header.hpp"

int main(int, char**) {
    // std::cout << "Hello, world!\n";

    Mat image = imread("../images/animals/8143.jpg");

    Mat imageHSV;
    Mat imageYCbCr;
    Mat imageGray;

    cvtColor(image, imageHSV, COLOR_BGR2HSV);
    cvtColor(image, imageYCbCr, COLOR_BGR2YCrCb);
    cvtColor(image, imageGray, COLOR_BGR2GRAY);

    // imshow("Original", image);
    // imshow("HSV", imageHSV);
    // imshow("YCbCr", imageYCbCr);
    // imshow("Escala Grises", imageGray);

    calcHist([image], [0], None, [256], [0, 256]);



    waitKey(0); 
    destroyAllWindows();

    return 0;
}
