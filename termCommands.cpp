#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <filesystem>

namespace fs=std::filesystem;

std::string getCwd(){
    fs::path cwd = fs::current_path();

    return cwd.string();
}

std::string exec(const char* cmd, bool silent) {
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");
    
    if (!pipe) throw std::runtime_error("popen() failed!");
    
    while (!feof(pipe)) {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }
    
    auto rc = pclose(pipe);
    

    if (silent == false){
        if (rc == EXIT_SUCCESS) {
            std::cout << "SUCCESS\n";
        }
        else {
            std::cout << "FAILED\n";
        }
    }
    
    return result;
}