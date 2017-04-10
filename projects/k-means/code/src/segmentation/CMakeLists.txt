add_library(segmentation SHARED
            segmentation.cpp
           )
target_include_directories(segmentation PRIVATE ${CMAKE_SOURCE_DIR}/include
                           PRIVATE ${CMAKE_SOURCE_DIR}/include/segmentation
                           )
