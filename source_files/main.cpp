#include "../header_files/header.hpp"

int main(int argc, char *argv[]) {

    Classifier classifier("../images/train", "../images/test");
    classifier.predict();
    
    return 0;
}
