#include <iostream>
#include <tensorflow/c/c_api.h>

#include "opencv2/opencv.hpp"

#include "video_handler.h"
#include "object_detection.h"
using namespace cv;
using namespace std;

int main(int argc,char** argv){
    VideoHandler input(true);
    input.StreamHandler();
    return 0;
}

