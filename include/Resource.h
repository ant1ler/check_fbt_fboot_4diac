#pragma once

#include<iostream>
#include<vector>
#include<string>

class Resource{
private:
    std::string name;
    std::string type;

public:
    inline void set_name(const std::string& _name){this->name = _name;};
    inline void set_type(const std::string& _type){this->type = _type;};

    inline std::string get_name() const {return this->name;};
    inline std::string get_type() const {return this->type;};
    
    void print_info();
};