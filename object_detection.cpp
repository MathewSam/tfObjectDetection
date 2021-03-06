#include "object_detection.h"

/**
 * \brief This function is meant to free buffer initialized for loading graph
 * \param data: data that is read in from the file
 * \param length: size of above data
 */ 
void free_buffer(void* data, size_t length) {                                             
        free(data);                                                                       
} 
/**
* \brief Creates tensor object from the block memory provided in data
* \param data_type data type of tensor input
* \param dims dimensions of input array block of memory
* \param num_dims number of dimsions
* \param data input data
* \param len size of input data
*/
TF_Tensor* ObjectDetection::CreateTensor(TF_DataType data_type,const std::int64_t* dims,std::size_t num_dims,const void* data,std::size_t len){
    if(dims==nullptr||data==nullptr){
        return nullptr;
    }
    TF_Tensor* tensor = TF_AllocateTensor(data_type, dims, static_cast<int>(num_dims), len);
    if(tensor == nullptr){
        return nullptr;
    }
    std::memcpy(TF_TensorData(tensor), data, std::min(len, TF_TensorByteSize(tensor)));
    return tensor;
}
/**
 *  \brief Initializes and prepares all units used in sess_run. This includes loading the model to a new graph and setting inputs and outputs from graph 
 */
void ObjectDetection::set_graph() {
  std::cout<<"Load Model: "<<this->frozen_graph_path<<std::endl;
  this->graph_def = this->read_file(this->frozen_graph_path);
  this->graph = TF_NewGraph();
  this->graph_status = TF_NewStatus();
  this->graph_opts = TF_NewImportGraphDefOptions();
  TF_GraphImportGraphDef(this->graph, this->graph_def, 
                         this->graph_opts, this->graph_status);
  if (TF_GetCode(this->graph_status) != TF_OK) {
    fprintf(stderr, "ERROR: Unable to import graph %s", TF_Message(this->graph_status));
    exit(1);
  } else {
    fprintf(stdout, "Successfully imported graph\n");
  }

  // Create Session 
  this->sess_opts = TF_NewSessionOptions();
  this->sess_status = TF_NewStatus();
  this->sess = TF_NewSession(this->graph, this->sess_opts, this->sess_status);
  if(TF_GetCode(this->sess_status) != TF_OK) {
    fprintf(stderr, "ERROR: Unable to create session %s", TF_Message(this->sess_status));
  }
  // Set up input op
  this->input_op = TF_GraphOperationByName(graph, "image_tensor");
  this->input_opout = {input_op, 0};
  this->input_ops.push_back(input_opout);
  // Set up output ops
  this->boxes_op = TF_GraphOperationByName(graph, "detection_boxes");
  this->scores_op = TF_GraphOperationByName(graph, "detection_scores");
  this->classes_op = TF_GraphOperationByName(graph, "detection_classes");
  this->num_detections_op = TF_GraphOperationByName(graph, "num_detections");
  this->boxes_opout = {boxes_op, 0};
  this->scores_opout = {scores_op, 0};
  this->classes_opout = {classes_op, 0};
  this->num_detections_opout = {num_detections_op, 0};
  this->output_ops.push_back(boxes_opout);
  this->output_ops.push_back(scores_opout);
  this->output_ops.push_back(classes_opout);
  this->output_ops.push_back(num_detections_opout);

}

/**
 * \brief reads graph from input file and prepares buffer with data from file
 * \param path: path to file to load data from
 */ 
TF_Buffer* ObjectDetection::read_file(std::string path) {
  const char* file = path.c_str();
  FILE *f = fopen(file, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  //same as rewind(f);

  void* data = malloc(fsize);
  fread(data, fsize, 1, f);
  fclose(f);

  TF_Buffer* buf = TF_NewBuffer();
  buf->data = data;
  buf->length = fsize;
  buf->data_deallocator = free_buffer;
  return buf;
}
/**
 * \brief runs input image provided through computation graph and returns predictions from graph
 * \param img: input image to run through graph
 * \return result of object detection in structure OD_Result 
 */ 
OD_Result ObjectDetection::sess_run(const cv::Mat img) {
  ResetOutputValues();
  // Create input variable
  int img_width = img.cols;
  int img_height = img.rows;
  int img_channel = img.channels();  
  const std::vector<std::int64_t> input_dims = {1, img_height, img_width, img_channel};
  int image_size_by_dims = img_height*img_width*img_channel;
  int image_tensor_size = image_size_by_dims;

  TF_Tensor* input_value = CreateTensor(TF_UINT8,
                                        input_dims.data(), input_dims.size(),
                                        img.isContinuous()? img.data: img.clone().data, image_tensor_size);
  // TF_Tensor* input_values[1] = {input_value};
  input_values.emplace_back(input_value);
  // Create output variable
  const std::vector<std::int64_t> box_dims = {1, this->max_detections, 4};
  const std::vector<std::int64_t> scores_dims = {1, this->max_detections};
  const std::vector<std::int64_t> classes_dims = {1, this->max_detections};
  const std::vector<std::int64_t> num_detections_dims = {1, 1};
  TF_Tensor* boxes_value = TF_AllocateTensor(TF_FLOAT, box_dims.data(), box_dims.size(), sizeof(float) * 4 * this->max_detections);
  TF_Tensor* scores_value = TF_AllocateTensor(TF_FLOAT, scores_dims.data(), scores_dims.size(), sizeof(float) * this->max_detections);
  TF_Tensor* classes_value = TF_AllocateTensor(TF_FLOAT, classes_dims.data(), classes_dims.size(), sizeof(float) * this->max_detections);
  TF_Tensor* num_detections_value = TF_AllocateTensor(TF_FLOAT, num_detections_dims.data(), num_detections_dims.size(), sizeof(float));
  // TF_Tensor* output_values[4] = {boxes_value, scores_value, classes_value, num_detections_value};
  output_values.emplace_back(boxes_value);
  output_values.emplace_back(scores_value);
  output_values.emplace_back(classes_value);
  output_values.emplace_back(num_detections_value);

  const TF_Output* inputs_ptr = input_ops.empty() ? nullptr : &input_ops[0];
  TF_Tensor* const* input_values_ptr =
      input_values.empty() ? nullptr : &input_values[0];
  const TF_Output* outputs_ptr = output_ops.empty() ? nullptr : &output_ops[0];
  TF_Tensor** output_values_ptr =
      output_values.empty() ? nullptr : &output_values[0];
      
  // Create session
  TF_SessionRun(this->sess, nullptr,
                inputs_ptr, input_values_ptr, this->input_ops.size(),
                outputs_ptr, output_values_ptr, this->output_ops.size(),
                nullptr, 0, nullptr, this->sess_status);
  
  this->od_result.boxes = (float*)TF_TensorData(output_values[0]);
  this->od_result.scores = (float*)TF_TensorData(output_values[1]);
  this->od_result.label_ids = (float*)TF_TensorData(output_values[2]);
  this->od_result.num_detections = (float*)TF_TensorData(output_values[3]);
  TF_DeleteTensor(boxes_value);
  TF_DeleteTensor(scores_value);
  TF_DeleteTensor(classes_value);
  TF_DeleteTensor(num_detections_value);
  DeleteInputValues();
  return this->od_result;
}
/**
 * \brief Function to deallocate input  of graph
 */ 
void ObjectDetection::DeleteInputValues() {
  for (size_t i = 0; i < input_values.size(); ++i) {
    if (input_values[i] != nullptr) TF_DeleteTensor(input_values[i]);
  }
  input_values.clear();
}
/**
 * \brief Function to deallocate output  of graph
 */ 
void ObjectDetection::ResetOutputValues() {
  for (size_t i = 0; i < output_values.size(); ++i) {
    if (output_values[i] != nullptr) TF_DeleteTensor(output_values[i]);
  }
  output_values.clear();
}
/**
 * \brief Destructor for the ObjectDetection instance
 */ 
ObjectDetection::~ObjectDetection() {
  TF_CloseSession(this->sess, this->sess_status);
  TF_DeleteSession(this->sess, this->sess_status);
  TF_DeleteSessionOptions(this->sess_opts);
  TF_DeleteImportGraphDefOptions(this->graph_opts);
  TF_DeleteGraph(this->graph);
  TF_DeleteStatus(this->graph_status);
}