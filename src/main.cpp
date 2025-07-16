#include"SystemModel.h"
#include<iostream>

int main(){
    SystemModel sys;

    pugi::xml_document doc;
    if (!doc.load_file("/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.xml")) {
        std::cerr << "Ошибка загрузки XML!" << std::endl;
        return 0;
    }

    sys.filename = "/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.xml";
    sys.parse(sys.filename);
    sys.get_structure();
}