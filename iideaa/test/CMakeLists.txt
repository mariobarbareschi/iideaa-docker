add_executable(test_trunc test_trunc.cc)
target_include_directories(test_trunc PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_trunc PRIVATE iideaa)


add_executable(test_evoaprx test_evoaprx.cc)
target_include_directories(test_evoaprx PRIVATE ${INCLUDE_DIR})
target_link_libraries(test_evoaprx PRIVATE iideaa)
