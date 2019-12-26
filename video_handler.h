#include <iostream>
#include <math.h>
#include <vector>
#include <string>


#include "opencv2/opencv.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "object_detection.h"

class VideoHandler : private ObjectDetection
{
        private:
        bool activate_camera = true;//Boolean that decides if input is from camera or video file
    public:
        VideoHandler(std::string frozen_graph_path, float confidence_score_threshold, int max_detections):ObjectDetection(frozen_graph_path, confidence_score_threshold, max_detections){};//Constructor
        int StreamHandler();

};
