#include"SystemModel.h"
#include<iostream>


void SystemModel::add_func_block(FunctionalBlock func_block){
    fb.push_back(func_block);
}

void SystemModel::add_resource(Resource res){
    resource.push_back(res);
}

void SystemModel::add_connection(Connection connect){
    connection.push_back(connect);
}

void SystemModel::add_mapping(Mapping mapp){
    mapping.push_back(mapp);
}

void SystemModel::get_structure(){

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

    std::cout << "Mapping:" << std::endl;
    for(int i = 0; i < mapping.size(); i++){
        mapping[i].get_info();
    }
    std::cout  << std::endl;
}

FunctionalBlock SystemModel::parse_fb(pugi::xml_node fb_node){
    FunctionalBlock FB;

    FB.name = fb_node.attribute("Name").as_string();
    FB.type = fb_node.attribute("Type").as_string();

    for(pugi::xml_node param_node : fb_node.children("Parameter")){
        FB.params.push_back({param_node.attribute("Name").as_string(), param_node.attribute("Value").as_string()});
    }

    return FB;
}

Resource SystemModel::parse_res(pugi::xml_node res_node){
    Resource res;

    res.name = res_node.attribute("Name").as_string();
    res.type = res_node.attribute("Type").as_string();

    return res;

}

Connection SystemModel::parse_connect(pugi::xml_node connect_node){
    Connection con;

    con.start = connect_node.attribute("Source").as_string();
    con.end = connect_node.attribute("Destination").as_string();

    return con;

}

Mapping SystemModel::parse_mapping(pugi::xml_node mapping_node){
    Mapping mapp;

    mapp.from = mapping_node.attribute("From").as_string();
    mapp.to = mapping_node.attribute("To").as_string();

    return mapp;
}

void SystemModel::parse(std::string sys_filename){

    pugi::xml_document doc;
    doc.load_file(sys_filename.c_str());
    pugi::xml_node system_node = doc.child("System");

    pugi::xml_node app_node = system_node.child("Application");
    pugi::xml_node sub_app_node = app_node.child("SubAppNetwork");

    for(pugi::xml_node node : sub_app_node.children("FB")){
        add_func_block(parse_fb(node));
        
    }

    pugi::xml_node event_con_node = sub_app_node.child("EventConnections");
    for(pugi::xml_node node : event_con_node.children("Connection")){
        add_connection(parse_connect(node));
    }

    pugi::xml_node data_con_node = sub_app_node.child("DataConnections");
    for(pugi::xml_node node : data_con_node.children("Connection")){
        add_connection(parse_connect(node));
    }

    pugi::xml_node device_node = system_node.child("Device");

    for(pugi::xml_node node : device_node.children("Resource")){
        add_resource(parse_res(node));

        pugi::xml_node fb_network_node = node.child("FBNetwork");
        pugi::xml_node dev_even_con = fb_network_node.child("EventConnections");
        for(pugi::xml_node node_temp : dev_even_con.children("Connection")){
            add_connection(parse_connect(node_temp));
        }
    }

    for(pugi::xml_node mapp_node : system_node.children("Mapping")){
        add_mapping(parse_mapping(mapp_node));
    }
}
