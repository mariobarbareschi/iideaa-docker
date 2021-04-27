#!/bin/bash
#set -x
#bellerophon -v \
#  -objs evoapproxlib.o \
#  -objs /usr/lib/x86_64-linux-gnu/libz.so \
#  -objs /usr/lib/x86_64-linux-gnu/libtiff.so \
#  -objs /usr/lib/x86_64-linux-gnu/libjpeg.so \
#  -objs /usr/lib/x86_64-linux-gnu/libpng.so \
#  -arcs /usr/local/lib/libopencv_calib3d.a \
#  -arcs /usr/local/lib/libopencv_core.a \
#  -arcs /usr/local/lib/libopencv_dnn.a \
#  -arcs /usr/local/lib/libopencv_features2d.a \
#  -arcs /usr/local/lib/libopencv_flann.a \
#  -arcs /usr/local/lib/libopencv_gapi.a \
#  -arcs /usr/local/lib/libopencv_highgui.a \
#  -arcs /usr/local/lib/libopencv_imgcodecs.a \
#  -arcs /usr/local/lib/libopencv_imgproc.a \
#  -arcs /usr/local/lib/libopencv_ml.a \
#  -arcs /usr/local/lib/libopencv_objdetect.a \
#  -arcs /usr/local/lib/libopencv_photo.a \
#  -arcs /usr/local/lib/libopencv_stitching.a \
#  -arcs /usr/local/lib/libopencv_video.a \
#  -arcs /usr/local/lib/libopencv_videoio.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libade.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libquirc.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/liblibwebp.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/liblibjasper.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libIlmImf.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/liblibprotobuf.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libippiw.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libittnotify.a \
#  -arcs /usr/local/lib/opencv4/3rdparty/libippicv.a \
#  -arcs /root/projects/Sobel/code/build-clang/libs.a/libmetrics.a \
#  -libdb /root/projects/Sobel/code/build-clang/ -cd-dir ./ -r /root/projects/Sobel/clang-chimera/output/mutants/sobel.cc/3/evoapprox8u.csv -t EvoAprx  -maxGrade 18 -P gaconfig.param 0.5


 
set -x
bellerophon -v \
  -objs evoapproxlib.o \
  -libdb /root/projects/Sobel/code/build-clang/ -cd-dir ./ -r /root/projects/Sobel/clang-chimera/output/mutants/sobel.cc/3/evoapprox8u.csv -t EvoAprx  -maxGrade 18 -P gaconfig.param 0.5
