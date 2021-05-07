all:
	mkdir -p bin; g++ ./source_files/main.cpp ./source_files/image.cpp ./source_files/classifier.cpp  -o ./bin/Practica1.bin \
		-I/home/ezhizhpon/Apps/opencv-4.5.1/opencv_install/include/opencv4 \
		-L/home/ezhizhpon/Apps/opencv-4.5.1/opencv_install/lib \
		-lstdc++fs \
		-lopencv_core \
		-lopencv_highgui \
		-lopencv_imgproc \
		-lopencv_imgcodecs \
		-lopencv_video  \
		-lopencv_videoio \

run:
	cd bin/; ./Practica1.bin