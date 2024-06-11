#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

std::string cmd_exec(std::string arg, std::string flag) {
    char output_buffer [1024];
    std::string final_output;
    FILE *process = popen(arg.c_str() , "r");
    if(process != NULL) {
        while(fgets(output_buffer, sizeof(output_buffer), process) != NULL) {
            if (flag == "verbose" || flag == "v") std::cout << output_buffer << std::endl;
            final_output += output_buffer;
        }
    }
    pclose(process);
    return final_output;
}

int main (int argc, char** argv) {

    cmd_exec("hyprctl dispatch togglefloating", "v");

    return 0;
}