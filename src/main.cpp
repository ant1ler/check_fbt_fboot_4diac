#include"SystemModel.h"
#include"FbootModel.h"
#include<iostream>

int main(){
    SystemModel sys;
    FbootModel fboot;

    pugi::xml_document doc;
    if (!doc.load_file("/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.sys")) {
        std::cerr << "Ошибка загрузки XML!" << std::endl;
        return 0;
    }

    sys.filename = "/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.sys";
    sys.parse(sys.filename);
    sys.get_structure();
    std::cout << std::endl;
    fboot.filename = "/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1_FORTE_PC.fboot";
    fboot.parse(fboot.filename);
    fboot.get_structure();
}