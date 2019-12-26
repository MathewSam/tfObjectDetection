#include "video_handler.h"
using namespace std;
using namespace cv;

/**
* \brief StreamHandler meant to stream frames to object Detection module from either camera or file
*/
int VideoHandler::StreamHandler(){
    if(activate_camera){
    	VideoCapture cap;
	    if(!cap.open(0)){
	        return 0;
	    }
	    for(;;){
	        Mat frame;
	        cap>>frame;
	        if(frame.empty()) return 0;
	        imshow("Video Display",frame);
	        if(waitKey(10)== 27) return 0;
	        }
    }
    return 0;
}
