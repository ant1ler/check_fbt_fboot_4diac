#pragma once

#include<iostream>
#include<string>

class Mapping{
private:
    std::string from;
    std::string to;

public:
    inline void set_from(const std::string& _from){this->from = _from;};
    inline void set_to(const std::string& _to){this->to = _to;};

    inline std::string get_from() const {return this->from;};
    inline std::string get_to() const {return this->to;};

    void print_info();
};