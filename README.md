# tfObjectDetection
This project is an attempt to build an object detection system using Tensorflow for C++ and OpenCV. The project is built for linux, specifically pop os! v18.04. The installation process should be identical for Ubuntu 18.04. 


## Dependencies
1. Tensorflow: Installed from [here](https://www.tensorflow.org/install/lang_c)
2. OpenCV: Installed by running sudo apt-get install libopencv-dev


## Running
To run the testing file, you run:<br/>
> g++ video_handler.cpp testing.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio  
Will be updated with a make file soon

## Model used
The model used for the detection task is taken from the paper [Scalable Object Detection using Deep NeuralNetworks](https://arxiv.org/abs/1312.2249)

## Reference
Since resources available for utilizing tensorflow C API is scarce, I used the following to get a foothold:  
1. [Medium Deep Learning page for Tensorflow in C](https://medium.com/@danishshres/single-shot-detection-using-tensorflow-c-api-edfe5d9942a4)
2. [This Tensorflow for C repository](https://github.com/rky0930/tf_c_api)

