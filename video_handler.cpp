#include "video_handler.h"
using namespace std;
using namespace cv;

/**
* \brief StreamHandler meant to stream frames to object Detection module from either camera or file
*/
void VideoHandler::StreamHandler(){
	this->set_graph();
    if(activate_camera){
    	VideoCapture cap;
	    if(!cap.open(0)){
	        return;
	    }
	    while(true){
			Mat frame;
	        cap>>frame;
			cvtColor(frame,frame,COLOR_BGR2RGB);
			OD_Result prediction = this->sess_run(frame);
			this->postprocessing(prediction,frame);
	        if(frame.empty()) break;
	        cv::cvtColor(frame,frame,cv::COLOR_RGB2BGR);
    		cv::imshow("Video Display",frame);
	        if(waitKey(10)== 27) break;
	        }
    }

}

/**
 * \brief carries out post precessing of input frame using detection result from sess_run and uses it to mark region of interest in image
 * \param od_result: output from sess_run
 * \param frame: input image to mark area of interest for
 */ 
void VideoHandler::postprocessing(const OD_Result od_result,cv::Mat& frame) {
  int img_width = frame.cols;
  int img_height = frame.rows;
  int img_channel = frame.channels();  
  int num_detections = (int)od_result.num_detections[0];
  int box_cnt = 0; 
  for (int i=0; i<num_detections; i++) {
    if (od_result.scores[i] >= 0.5) {
      int xmin = (int)(od_result.boxes[i*4+1] * img_width);
      int ymin = (int)(od_result.boxes[i*4+0] * img_height);
      int xmax = (int)(od_result.boxes[i*4+3] * img_width);
      int ymax = (int)(od_result.boxes[i*4+2] * img_height);      
      cv::rectangle(frame, cv::Point(xmin, ymin), cv::Point(xmax, ymax), CV_RGB(0, 0, 255));

    }
  }

  
}