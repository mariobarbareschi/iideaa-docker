add_library(taylor SHARED
            taylor.cpp
           )
target_include_directories(taylor PRIVATE ${CMAKE_SOURCE_DIR}/taylor ${CMAKE_SOURCE_DIR}/stirling)
target_link_libraries(taylor stirling)
