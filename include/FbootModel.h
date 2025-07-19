#pragma once

#include "pugixml.hpp"
#include"FunctionalBlock.h"
#include"Resource.h"
#include"Connection.h"
#include<iostream>

class FbootModel{
private:
    std::string filename;
    std::vector<FunctionalBlock> fb;
    std::vector<Resource> resource;
    std::vector<Connection> connection;

public:
    void add_func_block(FunctionalBlock func_block);
    void add_resource(Resource res);
    void add_connection(Connection connect);
    void print_structure();

    inline void set_filename(const std::string& _filename){this->filename = _filename;};
    inline void set_fb(const std::vector<FunctionalBlock>& _fb){this->fb = _fb;};
    inline void set_resource(const std::vector<Resource>& _resourse){this->resource = _resourse;};
    inline void set_connection(const std::vector<Connection>& _connection){this->connection = _connection;};

    inline std::string get_filename() const {return this->filename;};
    inline std::vector<FunctionalBlock> get_fb() const {return this->fb;};
    inline std::vector<Resource> get_resource() const {return this->resource;};
    inline std::vector<Connection> get_connection() const {return this->connection;};
    
    Resource parse_resource(std::string line);
    FunctionalBlock parse_create_fb(std::string line);
    void parse_write_connection(std::string line);
    Connection parse_create_connection(std::string line);
    void parse(std::string filename);

    void correction();
};