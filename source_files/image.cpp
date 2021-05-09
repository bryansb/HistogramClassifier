#include "../header_files/header.hpp"

Image::Image(string imagePath, string category){
    this->imagePath = imagePath;
    this->category = category;
};

cv::Mat Image::readImage(){
    return cv::imread(imagePath);
}

vector<cv::Mat> Image::calcBGRHist(){
    Mat b_hist;
    Mat g_hist; 
    Mat r_hist;
    vector<cv::Mat> bgrResult;
    vector<cv::Mat> bgr;

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false; 

    cv::split(readImage(), bgr);
    
    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    bgrResult.push_back(b_hist);
    bgrResult.push_back(g_hist);
    bgrResult.push_back(r_hist);

    return bgrResult;
}

vector<cv::Mat> Image::calcHSVHist(){
    Mat h_hist;
    Mat s_hist; 
    Mat v_hist;
    vector<Mat> hsvResult;
    vector<Mat> histBase;

    int h_bins = 180; 
    int s_bins = 256;
    int v_bins = 256;
    int histSize[] = { h_bins, s_bins, v_bins };

    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    float v_ranges[] = { 0, 256 };

    const float* rangesH = {h_ranges};
    const float* rangesS = {s_ranges};
    const float* rangesV = {v_ranges};

    cv::split(getImageHSV(), histBase);
    calcHist(&histBase[0], 1, 0, Mat(), h_hist, 1, &h_bins, &rangesH, true, false );
    calcHist(&histBase[1], 1, 0, Mat(), s_hist, 1, &s_bins, &rangesS, true, false );
    calcHist(&histBase[2], 1, 0, Mat(), v_hist, 1, &v_bins, &rangesV, true, false );

    hsvResult.push_back(h_hist);
    hsvResult.push_back(s_hist);
    hsvResult.push_back(v_hist);

    return hsvResult;
}

vector<cv::Mat> Image::calcYCrCbHist(){
    vector<Mat> YCrCbResult;
    vector<Mat> ycrcb;
    cv::split(getImageYCbCr(), ycrcb);

    Mat y_hist;
    Mat cr_hist; 
    Mat cb_hist;

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false; 

    cv::split(readImage(), ycrcb);
    
    calcHist( &ycrcb[0], 1, 0, Mat(), y_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &ycrcb[1], 1, 0, Mat(), cr_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &ycrcb[2], 1, 0, Mat(), cb_hist, 1, &histSize, &histRange, uniform, accumulate );

    YCrCbResult.push_back(y_hist);
    YCrCbResult.push_back(cr_hist);
    YCrCbResult.push_back(cb_hist);
    Mat tmp = getImageYCbCr();
    return YCrCbResult;
}

vector<cv::Mat> Image::calcGrayHist(){
    vector<Mat> grayResult;
    Mat g_hist;
    Mat gray = getImageGray();

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false; 
    
    calcHist( &gray, 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    grayResult.push_back(g_hist);
    return grayResult;
}

string Image::getCategory() {
    return category;
}

string Image::getImage(){
    return imagePath;
}

cv::Mat Image::getImageHSV(){
    cv::Mat imageHSV;
    cvtColor(readImage(), imageHSV, COLOR_BGR2HSV);
    return imageHSV;
}

cv::Mat Image::getImageYCbCr(){
    cv::Mat imageYCbCr;
    cvtColor(readImage(), imageYCbCr, COLOR_BGR2YCrCb);
    return imageYCbCr;
}

cv::Mat Image::getImageGray(){
    cv::Mat imageGray;
    cvtColor(readImage(), imageGray, COLOR_BGR2GRAY);
    return imageGray;
}

void Image::toString(){
    cout << "Cat=" << category
            << " | Image="  << imagePath << endl;
}


    /**
     * Normalizar el histograma Para mostrar en pantalla
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }
    imshow("Source image", image);
    imshow("calcHist Demo", histImage);
    */
