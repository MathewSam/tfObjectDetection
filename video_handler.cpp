#include "video_handler.h"

using namespace std;
using namespace cv;

/**
* \brief Video Handler meant to specifically utilize default camera as input
* \param camera_status: Input which enables camera from system to acquire frames for detection  
*/
VideoHandler::VideoHandler(bool camera_status){
    activate_camera = camera_status;
    if(!activate_camera){
        cout<<"Please enter filename of video :\n";
        cin >> filename;
    }
}

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
