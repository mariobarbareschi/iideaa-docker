#include <iostream>
#include <fstream>
#include <math.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int evoApprox8u_component_4;
int evoApprox8u_component_3;
int evoApprox8u_component_2;
int evoApprox8u_component_1;
int evoApprox8u_component_0;

extern "C" double BELLERO_getError() {    
    int            num_images = 0;
    double         mpsnr      = 0;
    std::string    dataset    = "/root/projects/Sobel/code/dataset";
    std::string    get_psnr   = "/root/projects/Sobel/code/build-clang/bin/get_psnr";
    std::string    command    = get_psnr + " " + dataset + " " +
                                std::to_string(evoApprox8u_component_0) + " " +
                                std::to_string(evoApprox8u_component_1) + " " + 
                                std::to_string(evoApprox8u_component_2) + " " + 
                                std::to_string(evoApprox8u_component_3) + " " + 
                                std::to_string(evoApprox8u_component_4); 
    std::string retstring = exec(command.c_str());
    mpsnr = stod(retstring);
    return -mpsnr; // higher psnr is better... but error has to be minimized!
}


extern "C" double BELLERO_Reward()
{
    std::string    get_area   = "/root/projects/Sobel/code/build-clang/bin/get_area";
    std::string    command    = get_area + " " +
                                std::to_string(evoApprox8u_component_0) + " " +
                                std::to_string(evoApprox8u_component_1) + " " + 
                                std::to_string(evoApprox8u_component_2) + " " + 
                                std::to_string(evoApprox8u_component_3) + " " + 
                                std::to_string(evoApprox8u_component_4); 
    std::string retstring = exec(command.c_str());
    double area = stod(retstring);
  return -area; // area must be minimized
}

extern "C" double BELLERO_Penality()
{
    std::string    get_power   = "/root/projects/Sobel/code/build-clang/bin/get_power";
    std::string    command    = get_power + " " +
                                std::to_string(evoApprox8u_component_0) + " " +
                                std::to_string(evoApprox8u_component_1) + " " + 
                                std::to_string(evoApprox8u_component_2) + " " + 
                                std::to_string(evoApprox8u_component_3) + " " + 
                                std::to_string(evoApprox8u_component_4); 
    std::string retstring = exec(command.c_str());
    double power = stod(retstring);
  return power;
}
