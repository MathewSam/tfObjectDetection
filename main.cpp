#include <iostream>
#include <tensorflow/c/c_api.h>

#include "opencv2/opencv.hpp"

#include "video_handler.h"

using namespace cv;
using namespace std;

int main(int argc,char** argv){

    VideoHandler input("./models/frozen_inference_graph.pb",0.8,5);
    input.StreamHandler();
    return 0;
}

