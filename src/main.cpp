#include"SysModel.h"
#include"FbootModel.h"
#include<iostream>

void validate(FbootModel fboot, SysModel sys){

    std::vector<FunctionalBlock> fb_fboot;
    std::vector<FunctionalBlock> fb_sys;
    bool fb_validate = false;

    for(int i = 0; i < fboot.get_fb().size(); i++){
        for(int j = 0; j < sys.get_fb().size(); j++){
            if(fboot.get_fb()[i].get_name() == sys.get_fb()[j].get_name()){
                if(fboot.get_fb()[i].get_type() == sys.get_fb()[j].get_type()){
                    if(fboot.get_fb()[i].get_params() == sys.get_fb()[j].get_params()){
                        if(fboot.get_fb()[i].get_resource() == sys.get_fb()[j].get_resource().substr(sys.get_fb()[j].get_resource().find(".") + 1, std::string::npos)){

                            fb_fboot.push_back(fboot.get_fb()[i]);
                            fb_sys.push_back(sys.get_fb()[j]);
                        }
                    }
                }
            }
        }
    }
    if(fb_fboot.size() == fboot.get_fb().size() and fb_sys.size() == sys.get_fb().size()) {fb_validate = true;}


    std::vector<Resource> resource_fboot;
    std::vector<Resource> resource_sys;
    bool resource_validate = false;

    for(int i = 0; i < fboot.get_resource().size(); i++){
        for(int j = 0; j < sys.get_resource().size(); j++){
            if(fboot.get_resource()[i].get_name() == sys.get_resource()[j].get_name().substr(sys.get_resource()[j].get_name().find(".") + 1, std::string::npos)){
                if(fboot.get_resource()[i].get_type() == sys.get_resource()[j].get_type()){

                    resource_fboot.push_back(fboot.get_resource()[i]);

                    resource_sys.push_back(sys.get_resource()[j]);
                }
            }
        }
    }
    if(resource_fboot.size() == fboot.get_resource().size() and resource_sys.size() == sys.get_resource().size()) {resource_validate = true;}

    std::vector<Connection> connection_fboot;
    std::vector<Connection> connection_sys;
    bool connection_validate = false;
    std::cout << "Connection" << std::endl;
    for(int i = 0; i < fboot.get_connection().size(); i++){
        for(int j = 0; j < sys.get_connection().size(); j++){
            if(fboot.get_connection()[i].get_start() == sys.get_connection()[j].get_start()){
                if(fboot.get_connection()[i].get_end() == sys.get_connection()[j].get_end()){

                    connection_fboot.push_back(fboot.get_connection()[j]);

                    connection_sys.push_back(sys.get_connection()[j]);
                }
            }
        }
    }
    if(connection_fboot.size() == fboot.get_connection().size() and connection_sys.size() == sys.get_connection().size()) {connection_validate = true;}

    if(fb_validate and resource_validate and connection_validate){
        std::cout << "Fboot-файл совпадает с sys-файлом" << std::endl;
    }
    else{
        std::cout << "Fboot-файл не совпадает с sys-файлом" << std::endl;
    } 
}

int main(){
    SysModel sys;
    FbootModel fboot;

    pugi::xml_document doc;
    if (!doc.load_file("/home/ant1ler/check_fbt_fboot_4diac/files/parse_test.sys")) {
        std::cerr << "Ошибка загрузки XML!" << std::endl;
        return 0;
    }

    std::string sys_filename = "/home/ant1ler/check_fbt_fboot_4diac/files/parse_test.sys";
    sys.set_filename(sys_filename);
    sys.parse(sys.get_filename());
    sys.correction();
    sys.print_structure();

    std::cout << std::endl;

    std::string fboot_filename = "/home/ant1ler/check_fbt_fboot_4diac/files/parse_test_FORTE_PC.fboot";
    fboot.set_filename(fboot_filename);
    fboot.parse(fboot.get_filename());
    fboot.correction();
    fboot.print_structure();

    validate(fboot, sys);
}