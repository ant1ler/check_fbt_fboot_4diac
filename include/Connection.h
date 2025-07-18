#pragma once

//#include"FunctionalBlock.h"
#include<iostream>

class Connection{
private:
    std::string start;
    std::string end;

public:
    inline void set_start(const std::string& _start){this->start = _start;};
    inline void set_end(const std::string& _end){this->end = _end;};

    inline std::string get_start() const {return this->start;};
    inline std::string get_end() const {return this->end;};

    void print_info();
};