#pragma once

#include "pugixml.hpp"
#include"FunctionalBlock.h"
#include"Resource.h"
#include"Connection.h"
#include"Mapping.h"
#include<iostream>

class SystemModel{
public:
    std::string filename;
    std::vector<FunctionalBlock> fb;
    std::vector<Resource> resource;
    std::vector<Connection> connection;
    std::vector<Mapping> mapping;


    void add_func_block(FunctionalBlock func_block);
    void add_resource(Resource res);
    void add_connection(Connection connect);
    void add_mapping(Mapping mapp);
    void get_structure();
    FunctionalBlock parse_fb(std::string project_name, pugi::xml_node fb_node);
    Resource parse_res(std::string device_name, pugi::xml_node res_node);
    Connection parse_fb_connect(std::string project_name, pugi::xml_node connect_node);
    Connection parse_resource_connect(pugi::xml_node connect_node);
    Mapping parse_mapping(pugi::xml_node mapping_node);
    void parse(std::string filename);
};