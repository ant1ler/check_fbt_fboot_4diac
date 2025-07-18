#pragma once

#include<iostream>
#include<utility> 
#include<vector>
#include<string>

class FunctionalBlock{
private:  
    std::string name;
    std::string type;
    std::vector< std::pair<std::string, std::string> > params;
    std::string resource;

public:
    inline void set_name(const std::string& _name){this->name = _name;};
    inline void set_type(const std::string& _type){this->type = _type;};
    inline void set_params(const std::vector< std::pair<std::string, std::string> >& _params){this->params = _params;};
    inline void push_params(const std::pair<std::string, std::string>& _pair_params){this->params.push_back(_pair_params);};
    inline void set_resource(const std::string& _resource){this->resource = _resource;};

    inline std::string get_name() const {return this->name;};
    inline std::string get_type() const {return this->type;};
    inline std::vector< std::pair<std::string, std::string> > get_params() const {return this->params;};

    void print_info();
};
