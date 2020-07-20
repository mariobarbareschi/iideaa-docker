open_project -reset project1

set_top network_wrapper

# The following paths are relative to the HLS/exact subdirectory
add_files src/top.cc -cflags "-m64 -std=c++11 -I../../code/include -I../../code/include/n2d2 -Iinclude" 
add_files src/network.cc -cflags "-m64 -std=c++11 -I../../code/include -I../../code/include/n2d2 -Iinclude" 
add_files src/fap.cc -cflags "-m64 -std=c++11 -I../../code/include -I../../code/include/n2d2 -Iinclude" 

open_solution -reset "solution1"
set_part {xcvu9p-flgb2104-1-i}
create_clock -period 10 -name default
#source "./project1/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
exit
