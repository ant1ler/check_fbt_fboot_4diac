#pragma once

#include<iostream>
#include<vector>
#include<string>

class Resource{
private:
    std::string name;
    std::string type;
    std::string line;

public:
    inline void set_name(const std::string& _name){this->name = _name;};
    inline void set_type(const std::string& _type){this->type = _type;};
    inline void set_line(const std::string& _line){this->line = _line;};

    inline std::string get_name() const {return this->name;};
    inline std::string get_type() const {return this->type;};
    inline std::string get_line() const {return this->line;};
    
    void print_info();
};