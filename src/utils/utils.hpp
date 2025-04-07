#pragma once

#include <string>
#include <fstream>

#include <iostream>

namespace utils {
    inline std::string read_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "could not open file: " << filename << std::endl;
            return "";
        }
    
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    
        return content;
    }
};