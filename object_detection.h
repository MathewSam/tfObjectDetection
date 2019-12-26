#include <iostream>

#include <string>

#include "opencv2/opencv.hpp"
#include "tensorflow/c/c_api.h"

  struct OD_Result {
  float* boxes;
  float* scores;
  float* label_ids;
  float* num_detections;
};

class ObjectDetection {
  private:

    std::string frozen_graph_path="";
    float confidence_score_threshold;
    int max_detections;
    
    TF_Graph* graph;
    TF_Buffer* graph_def;
    TF_ImportGraphDefOptions* graph_opts;
    TF_Status* graph_status;
    TF_SessionOptions* sess_opts = TF_NewSessionOptions();
    TF_Status* sess_status;
    TF_Session* sess;  
    TF_Operation* input_op;
    TF_Output input_opout;
    std::vector<TF_Output> input_ops;
    std::vector<TF_Tensor*> input_values;
    TF_Operation* boxes_op;
    TF_Operation* scores_op;
    TF_Operation* classes_op;
    TF_Operation* num_detections_op;
    TF_Output boxes_opout, scores_opout, classes_opout, num_detections_opout;
    std::vector<TF_Output> output_ops;
    std::vector<TF_Tensor*> output_values;
    OD_Result od_result;
    bool verbose = false;
    bool visible = false;
  public:
    ObjectDetection(std::string frozen_graph_path, float confidence_score_threshold, int max_detections):frozen_graph_path(frozen_graph_path),confidence_score_threshold(confidence_score_threshold),max_detections(max_detections){};
    void set_graph();
    TF_Buffer* read_file(std::string path);
    void set_visible_mode(bool mode) { visible = mode; }
    OD_Result sess_run(const cv::Mat img);
    void postprocessing(cv::Mat& src);
    void DeleteInputValues();
    void ResetOutputValues();
    
    ~ObjectDetection(); //{ close(); }
/*
    void close();*/
};
