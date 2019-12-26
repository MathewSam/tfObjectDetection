# tfObjectDetection
This project is an attempt to build an object detection system using Tensorflow for C and OpenCV. The project aims to build a real time object detection model that can take input from the camera of a system and provide object detection outputs as boxes on the output screen.


## Dependencies for running locally
1. g++ >= 7.4.0  
2. Tensorflow for C:   
    Installed from [here](https://www.tensorflow.org/install/lang_c)
3. OpenCV >=3.2.0   


## Overview of Code Structure
This project is implemented using an Object Oriented Programming approach with a derived class VideoHandler and a base class ObjectDetection. The VideoHandler class specifically acts as an interface to load images from the camera to the ObjectDetection class which is responsible for running current frame through the computational graph to provide the predictions of where objects are located in the frame of the image. The VideoHandler also takes this prediction to draw boxes on the output frame to see where the object falls. The ObjectDetector class is inherited privately to avoid any access to internal operations of the object detection.

### object_detection.h
This file declares class that handles all object detection related data structures and functions. The primary data structures are:

1. OD_Result : A structure that encapsulates the results of object detection, namely, location(boxes) of the object in the camera stream, the confidence(scores) of object detected, label id(index of which class the object belongs to) and the number of detections for that frame

2. ObjectDetection: This class encapsulates the behaviour that handles the loading of the graph from a given file, and preparing the session to run the input through the computational graph to return predictions. 

###  object_detection.cpp  

This file holds the primary member functions of the ObjectDetection class  
 - CreateTensor : Function responsible to create and handle tensors for computational graph
 -  set_graph : Prepares computational graph for input
 - read_file : Used to load computational graph in set_graph
 - sess_run : runs provided image thjrough computational graph
 - DeleteInputValues : Delete existing frame in the input node of compuataional graph
 - ResetOutputValues : Resets output values 
 - ~ObjectDetection : Destructor for instance of class

### video_handler.h
This file hods declaration of the video handler part of the code which extracts frames from camera and feeds to the ObjectDetection unit of the code. The primary data structure here is:

1. VideoHandler: The class that inherits from the ObjectDetection class. 

### video_handler.cpp

This file holds the member functions of the VideoHandler class which are:
 - StreamHandler: Handles input stream from camera
 - postprocessing: computes and draws bounding box on object detected

## Rubric and Criteria
### Loops, Functions and I/O
 - The project demonstrates an understanding of C++ functions and control sturctures.
 - The project accepts user input and processes the input(main.cpp).
### Object Oriented Programming
 - The project uses Object Oriented Programming techniques(video_handler.h & .cpp and object_detection.h & .cpp).
 - Classes use appropriate access specifiers for class members(video_handler.h (line 15 & 18) and object_detection.h (line 16 & 42)).
 - Class constructors utilize member initialization lists(video_handler.h (line 19) and object_detection.h (line 43)).
 - Classes abstract implementation details from their interfaces.
 - Classes encapsulate behavior.
### Memory Management
 - The project makes use of references in function declarations.(video_handler.h (line 21))
 - The project uses destructors where required(object_detection.h (line 49))
 
## Running
To run the code, first clone repository
> git clone https://github.com/MathewSam/tfObjectDetection.git  

Compile  
> cd tfObjectDetection  
> make

Run 
>./streamer  

To exit, press Esc button.

## Model used
The model used for the detection task is taken from the paper [Single Shot MultiBox Detector](https://arxiv.org/abs/1512.02325). To use another model, please replace the frozen_inference_graph.pb file stored in the models folder with a pretrained model of your preference from the Tensorflow Object Detection API.

## Reference
Since resources available for utilizing tensorflow C API is scarce, I used the following to get a foothold:  
1. [Medium Deep Learning page for Tensorflow in C](https://medium.com/@danishshres/single-shot-detection-using-tensorflow-c-api-edfe5d9942a4)
2. [This Tensorflow for C repository](https://github.com/rky0930/tf_c_api)

