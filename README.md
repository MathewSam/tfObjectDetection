# tfObjectDetection
This project is an attempt to build an object detection system using Tensorflow for C++ and OpenCV. The project is built for linux, specifically pop os! v18.04. The installation process should be identical for Ubuntu 18.04. 


## Dependencies
1. g++ >= 7.4.0  
    (for Linux)  
    Already available in most distros

    (for Windows)  
    Recommend using MinGW  

2. Tensorflow: 
    Installed from [here](https://www.tensorflow.org/install/lang_c)

3. OpenCV:   
    (For Linux)  
    > sudo apt-get install libopencv-dev  
      
    (For Windows ** Official installation directions are a bit spotty if not outdated. You will have better luck following below link or a youtube video)  
    Follow instructions in [here](https://www.deciphertechnic.com/install-opencv-with-visual-studio/)  


## Running
To run the testing file, you run:<br/>
> g++ object_detection.cpp video_handler.cpp testing.cpp -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_datasets -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_line_descriptor -lopencv_optflow -lopencv_video -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_rgbd -lopencv_viz -lopencv_surface_matching -lopencv_text -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core -ltensorflow  


Will be updated with a make file soon

## Model used
The model used for the detection task is taken from the paper [Single Shot MultiBox Detector](https://arxiv.org/abs/1512.02325)

## Reference
Since resources available for utilizing tensorflow C API is scarce, I used the following to get a foothold:  
1. [Medium Deep Learning page for Tensorflow in C](https://medium.com/@danishshres/single-shot-detection-using-tensorflow-c-api-edfe5d9942a4)
2. [This Tensorflow for C repository](https://github.com/rky0930/tf_c_api)

