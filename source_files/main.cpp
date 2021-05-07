#include "../header_files/header.hpp"

int main(int argc, char *argv[]) {

    // Mat image = imread("../images/animals/8143.jpg");
    string ROOT_PATH = "../";
    Mat imageHSV;
    // Mat imageYCbCr;
    // Mat imageGray;

    // cvtColor(image, imageHSV, COLOR_BGR2HSV);
    // cvtColor(image, imageYCbCr, COLOR_BGR2YCrCb);
    // cvtColor(image, imageGray, COLOR_BGR2GRAY);

    // namedWindow("Original", WINDOW_AUTOSIZE);
    // imshow("Original", image);

    // namedWindow("HSV", WINDOW_AUTOSIZE);
    // imshow("HSV", imageHSV);
    // namedWindow("YCbCr", WINDOW_AUTOSIZE);
    // imshow("YCbCr", imageYCbCr);
    
    // namedWindow("Escala Grises", WINDOW_AUTOSIZE);
    // imshow("Escala Grises", imageGray);

    // cv::calcHist([image], [0], None, [256], [0, 256]);
    Classifier classifier(ROOT_PATH + "images/");
    // Image image(imageHSV, "");
    classifier.loadData();
    classifier.printTrainImagesPath();

    waitKey(0); 
    destroyAllWindows();

    return 0;
}
