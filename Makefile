CXX=g++
RM=rm -f
LDLIBS=-ltensorflow $(shell pkg-config --cflags --libs opencv)
SRCS=object_detection.cpp video_handler.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
TARGET=streamer

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDLIBS) 

streamer.o: main.cpp

clean:
	$(RM) $(OBJS) $(TARGET) *.o