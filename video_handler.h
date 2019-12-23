#include <iostream>
#include <math.h>
#include <vector>
#include <string>


#include "opencv2/opencv.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class VideoHandler{
    public:
        VideoHandler(bool activate_camera);//Constructor
        int StreamHandler();
    private:
        bool activate_camera;//Boolean that decides if input is from camera or video file
        char filename[100];//Filename of video file if chosen
};
