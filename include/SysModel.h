#pragma once

#include "pugixml.hpp"
#include"FunctionalBlock.h"
#include"Resource.h"
#include"Connection.h"
#include"Mapping.h"
#include<iostream>

class SysModel{
private:
    std::string filename;
    std::vector<FunctionalBlock> fb;
    std::vector<Resource> resource;
    std::vector<Connection> connection;
    std::vector<Mapping> mapping;

public:
    void add_func_block(FunctionalBlock func_block);
    void add_resource(Resource res);
    void add_connection(Connection connect);
    void add_mapping(Mapping mapp);
    void print_structure();

    inline void set_filename(const std::string& _filename){this->filename = _filename;};
    inline void set_fb(const std::vector<FunctionalBlock>& _fb){this->fb = _fb;};
    inline void set_resource(const std::vector<Resource>& _resourse){this->resource = _resourse;};
    inline void set_connection(const std::vector<Connection>& _connection){this->connection = _connection;};
    inline void set_mapping(const std::vector<Mapping>& _mapping){this->mapping = _mapping;};

    inline std::string get_filename() const {return this->filename;};
    inline std::vector<FunctionalBlock> get_fb() const {return this->fb;};
    inline std::vector<Resource> get_resource() const {return this->resource;};
    inline std::vector<Connection> get_connection() const {return this->connection;};
    inline std::vector<Mapping> get_mapping() const {return this->mapping;};
    
    FunctionalBlock parse_fb(std::string project_name, pugi::xml_node fb_node);
    Resource parse_res(std::string device_name, pugi::xml_node res_node);
    Connection parse_fb_connect(std::string project_name, pugi::xml_node connect_node);
    Connection parse_resource_connect(pugi::xml_node connect_node);
    Mapping parse_mapping(pugi::xml_node mapping_node);
    void parse(std::string filename);
};