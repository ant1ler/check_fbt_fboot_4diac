#pragma once

#include "pugixml.hpp"
#include"FunctionalBlock.h"
#include"Resource.h"
#include"Connection.h"
#include<iostream>

class FbootModel{
public:
    std::string filename;
    std::vector<FunctionalBlock> fb;
    std::vector<Resource> resource;
    std::vector<Connection> connection;

    void add_func_block(FunctionalBlock func_block);
    void add_resource(Resource res);
    void add_connection(Connection connect);
    void get_structure();
    
    Resource parse_resource(std::string line);
    FunctionalBlock parse_create_fb(std::string line);
    void parse_write_connection(std::string line);
    Connection parse_create_connection(std::string line);

    void parse(std::string filename);
};