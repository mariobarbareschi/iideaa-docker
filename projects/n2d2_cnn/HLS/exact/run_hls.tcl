open_project -reset project1
#set_top network
set_top fccell_propagate_2d

# The following paths are relative to the HLS/exact subdirectory
#add_files src/conv1.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/conv2.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/conv3.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
add_files src/fc1.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/fc2.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/output.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/pool1.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/pool2.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
add_files src/sat.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files src/network.cc -cflags "-std=gnu++11 -I../../code/include -I../../code/include/n2d2 -I../../code/include/iideaa" 
#add_files -tb fir_test.c
#add_files -tb out.gold.dat
open_solution -reset "solution1"
set_part {xcvu9p-flgb2104-1-i}
create_clock -period 10 -name default
#source "./project1/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
exit
