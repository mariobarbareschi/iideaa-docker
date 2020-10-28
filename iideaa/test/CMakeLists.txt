add_executable(test_trunc test_trunc.cc)
target_include_directories(test_trunc PRIVATE ${INCLUDE_DIR})
#target_link_directories(test_trunc PRIVATE iideaa)
link_directories(iideaa)
