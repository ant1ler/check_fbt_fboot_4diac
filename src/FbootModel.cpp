#include"FbootModel.h"
#include<iostream>
#include <fstream>

void FbootModel::add_func_block(FunctionalBlock func_block){
    fb.push_back(func_block);
}

void FbootModel::add_resource(Resource res){
    resource.push_back(res);
}

void FbootModel::add_connection(Connection connect){
    connection.push_back(connect);
}

void FbootModel::get_structure(){

    std::cout << "Functional Blocks:" << std::endl;
    for(int i = 0; i < fb.size(); i++){
        fb[i].get_info();
    }
    std::cout  << std::endl;

    std::cout << "Resources:" << std::endl;
    for(int i = 0; i < resource.size(); i++){
        resource[i].get_info();
    }
    std::cout  << std::endl;

    std::cout << "Connections:" << std::endl;
    for(int i = 0; i < connection.size(); i++){
        connection[i].get_info();
    }
    std::cout  << std::endl;
}

Resource FbootModel::parse_resource(std::string line){
    Resource res;

    res.name = line.substr(line.find("FB Name") + 9, line.find("Type") - line.find("FB Name") - 11);
    res.type = line.substr(line.find("Type") + 6, line.rfind("/>") - line.find("Type") - 8);

    return res;
}

FunctionalBlock FbootModel::parse_create_fb(std::string line){
    FunctionalBlock fb;

    std::string res = "";
    for(int i = 0; i < line.find(";"); i++){
        res += line[i];
    }
    fb.resource = res;

    fb.name = line.substr(line.find("FB Name") + 9, line.find("Type") - line.find("FB Name") - 11);
    fb.type = line.substr(line.find("Type") + 6, line.rfind("/>") - line.find("Type") - 8);

    return fb;
}

void FbootModel::parse_write_connection(std::string line){
    std::string name = "";
    std::string value = "";
    std::string func_block = "";

    value = line.substr(line.find("Source") + 8, line.find("Destination") - line.find("Source") - 10);
    if(value.find("&apos;") != std::string::npos) value.replace(value.find("&apos;"), 6, "'");
    if(value.find("&apos;") != std::string::npos) value.replace(value.find("&apos;"), 6, "'");

    func_block = line.substr(line.find("Destination") + 13, line.rfind("/>") - line.find("Destination") - 15);

    name = func_block.substr(func_block.rfind(".") + 1, std::string::npos);

    func_block.erase(func_block.rfind("."), std::string::npos);

    for(int i = 0; i < fb.size(); i++){
        if(fb[i].name == func_block){
            fb[i].params.push_back({name, value});
        }
    }
}

Connection FbootModel::parse_create_connection(std::string line){
    Connection con;

    con.start = line.substr(line.find("Source") + 8, line.find("Destination") - line.find("Source") - 10);
    con.end = line.substr(line.find("Destination") + 13, line.rfind("/>") - line.find("Destination") - 15);

    return con;
}

void FbootModel::parse(std::string filename){
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)){

        for(int i = 0; i < line.size(); i++){
            if(line[i] == '"'){
                line[i] = '/';
            }
        }

        if (line.empty() || line.find("Request") == 0) {
            continue;
        }

        if(line[0] == ';'){
            add_resource(parse_resource(line));
            continue;
        }

        else if(line.find("Action=/CREATE/><FB Name") != std::string::npos){
            add_func_block(parse_create_fb(line));
        }

        if(line.find("Action=/WRITE/><Connection") != std::string::npos){
            parse_write_connection(line);
        }

        if(line.find("Action=/CREATE/><Connection") != std::string::npos){
            add_connection(parse_create_connection(line));
        }
    }
}

