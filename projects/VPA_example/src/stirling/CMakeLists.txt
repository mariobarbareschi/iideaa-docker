add_library(stirling SHARED
            stirling.cpp
           )
target_include_directories(stirling PRIVATE ${CMAKE_SOURCE_DIR}/stirling)
