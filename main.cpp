#include <iostream>
#include <tensorflow/c/c_api.h>

#include "opencv2/opencv.hpp"

#include "video_handler.h"

using namespace cv;
using namespace std;

int main(int argc,char** argv){
    float confidence_threshold;
    int max_detections;
    std::string graph;
    std::cout << "Please enter location of inference graph : ";
    std::cin >> graph;
    std::cout << "Please enter confidence threshold : ";
    std::cin>> confidence_threshold;
     std::cout << "Please enter maximum number of objects detected per frame : ";
    std::cin>> max_detections;   
    VideoHandler input(graph,confidence_threshold,max_detections);
    input.StreamHandler();
    return 0;
}

