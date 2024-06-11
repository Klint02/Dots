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

bool contains(int len, char** arr, std::string str1) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == str1) {
            return true;
        }
    }
    return false;
}

int main (int argc, char** argv) {
        std::cout << argv[1] << (argv[1] == "Plus") << std::endl;

    if (argc > 2 ) {
        std::cout << "Too many arguments" << std::endl;
        std::cout << R"(Only provide either "Plus" or "Minus")" << std::endl;
        return 0;
    }

    if (argc < 2) {
        std::cout << "You must provide an argument" << std::endl;
        std::cout << R"(Only provide either "Plus" or "Minus")" << std::endl;
        return 0;
    }
    int workspace = stoi(cmd_exec(R"((hyprctl monitors -j | jq -r ".[] | select(.name==\"eDP-1\").activeWorkspace.id"))", ""));

    if (contains(argc, argv, "Plus")) {
        if (workspace != 10) {
            workspace++;
        } else {
            workspace = 1;
        }
    }

    if (contains(argc, argv, "Minus")) {
        if (workspace != 1) {
            workspace--;
        } else {
            workspace = 10;
        }
    }
    std::cout << workspace << std::endl;

    cmd_exec("hyprctl dispatch workspace " + std::to_string(workspace), "v");
    //cmd_exec("hyprctl dispatch workspace " + std::to_string(workspace + 10), "v");
    //cmd_exec("hyprctl dispatch workspace " + std::to_string(workspace + 20), "v");

    return 0;
}