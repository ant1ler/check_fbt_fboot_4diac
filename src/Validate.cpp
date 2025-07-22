#include"SysModel.h"
#include"FbootModel.h"
#include<iostream>

void validate(const FbootModel& fboot, const SysModel& sys) {
    bool isValid = true;
    
    // Вспомогательная функция для вывода заголовка ошибки
    auto printErrorHeader = [](const std::string& section) {
        std::cout << "\n=== Ошибка в разделе " << section << " ===\n";
    };
    
    // Вспомогательная функция для сравнения векторов параметров
    auto compareParams = [](const std::vector<std::pair<std::string, std::string>>& params1, 
                           const std::vector<std::pair<std::string, std::string>>& params2) {
        if (params1.size() != params2.size()) return false;
        
        for (const auto& p1 : params1) {
            bool found = false;
            for (const auto& p2 : params2) {
                if (p1 == p2) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    };

    //Сравнение ресурсов
    const auto& fboot_res = fboot.get_resource();
    const auto& sys_res = sys.get_resource();
    
    bool resMatch = true;
    if (fboot_res.size() != sys_res.size()) {
        printErrorHeader("Resources");
        std::cout << "Количество ресурсов не совпадает:\n";
        std::cout << "Fboot: " << fboot_res.size() << ", Sys: " << sys_res.size() << "\n";
        resMatch = false;
        isValid = false;
    }

    // Проверка каждого ресурса в FbootModel
    for (const auto& res_fboot : fboot_res) {
        bool found = false;
        for (const auto& res_sys : sys_res) {
            std::string sysResName = res_sys.get_name();
            size_t dotPos = sysResName.find_last_of('.');
            std::string sysResNameShort = (dotPos != std::string::npos) ? 
                                        sysResName.substr(dotPos + 1) : sysResName;
            
            if (res_fboot.get_name() == sysResNameShort) {
                found = true;
                
                // Проверка типа ресурса
                if (res_fboot.get_type() != res_sys.get_type()) {
                    if (resMatch) printErrorHeader("Resources");
                    std::cout << "Несовпадение типа для ресурса '" << res_fboot.get_name() << "':\n";
                    std::cout << "  Fboot: " << res_fboot.get_type() << "\n";
                    std::cout << "  Sys:   " << res_sys.get_type() << "\n";
                    resMatch = false;
                    isValid = false;
                }
                break;
            }
        }
        
        if (!found) {
            if (resMatch) printErrorHeader("Resources");
            std::cout << "Ресурс '" << res_fboot.get_name() 
                      << "' отсутствует в Sys модели\n";
            std::cout << res_fboot.get_line() << std::endl;
            resMatch = false;
            isValid = false;
        }
    }
    
    // Проверка ресурсов, которые есть в Sys, но нет в Fboot
    for (const auto& res_sys : sys_res) {
        std::string sysResName = res_sys.get_name();
        size_t dotPos = sysResName.find_last_of('.');
        std::string sysResNameShort = (dotPos != std::string::npos) ? 
                                    sysResName.substr(dotPos + 1) : sysResName;
        
        bool found = false;
        for (const auto& res_fboot : fboot_res) {
            if (res_fboot.get_name() == sysResNameShort) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            if (resMatch) printErrorHeader("Resources");
            std::cout << "Ресурс '" << sysResNameShort 
                      << "' отсутствует в Fboot модели\n";
            resMatch = false;
            isValid = false;
        }
    }

    // 2. Сравнение функциональных блоков
    const auto& fboot_fbs = fboot.get_fb();
    const auto& sys_fbs = sys.get_fb();
    
    bool fbMatch = true;
    if (fboot_fbs.size() != sys_fbs.size()) {
        printErrorHeader("Functional Blocks");
        std::cout << "Количество функциональных блоков не совпадает:\n";
        std::cout << "Fboot: " << fboot_fbs.size() << ", Sys: " << sys_fbs.size() << "\n";
        fbMatch = false;
        isValid = false;
    }

    // Проверка каждого FB в FbootModel
    for (const auto& fb_fboot : fboot_fbs) {
        bool found = false;
        for (const auto& fb_sys : sys_fbs) {
            if (fb_fboot.get_name() == fb_sys.get_name()) {
                found = true;
                
                // Проверка типа
                if (fb_fboot.get_type() != fb_sys.get_type()) {
                    if (fbMatch) printErrorHeader("Functional Blocks");
                    std::cout << "Несовпадение типа для FB '" << fb_fboot.get_name() << "':\n";
                    std::cout << "  Fboot: " << fb_fboot.get_type() << "\n";
                    std::cout << "  Sys:   " << fb_sys.get_type() << "\n";
                    fbMatch = false;
                    isValid = false;
                }
                
                // Проверка параметров
                if (!compareParams(fb_fboot.get_params(), fb_sys.get_params())) {
                    if (fbMatch) printErrorHeader("Functional Blocks");
                    std::cout << "Несовпадение параметров для FB '" << fb_fboot.get_name() << "':\n";
                    
                    // Вывод параметров из Fboot, которых нет в Sys
                    for (const auto& param : fb_fboot.get_params()) {
                        bool paramFound = false;
                        for (const auto& sysParam : fb_sys.get_params()) {
                            if (param == sysParam) {
                                paramFound = true;
                                break;
                            }
                        }
                        if (!paramFound) {
                            std::cout << "  Параметр отсутствует в Sys: " << param.first 
                                      << " = " << param.second << "\n";
                        }
                    }
                    
                    // Вывод параметров из Sys, которых нет в Fboot
                    for (const auto& param : fb_sys.get_params()) {
                        bool paramFound = false;
                        for (const auto& fbootParam : fb_fboot.get_params()) {
                            if (param == fbootParam) {
                                paramFound = true;
                                break;
                            }
                        }
                        if (!paramFound) {
                            std::cout << "  Параметр отсутствует в Fboot: " << param.first 
                                      << " = " << param.second << "\n";
                        }
                    }
                    
                    fbMatch = false;
                    isValid = false;
                }
                
                // Проверка ресурса
                std::string sysResource = fb_sys.get_resource();
                size_t dotPos = sysResource.find_last_of('.');
                std::string sysResourceShort = (dotPos != std::string::npos) ? 
                                              sysResource.substr(dotPos + 1) : sysResource;
                                              
                if (fb_fboot.get_resource() != sysResourceShort) {
                    if (fbMatch) printErrorHeader("Functional Blocks");
                    std::cout << "Несовпадение ресурса для FB '" << fb_fboot.get_name() << "':\n";
                    std::cout << "  Fboot: " << fb_fboot.get_resource() << "\n";
                    std::cout << "  Sys:   " << sysResourceShort << "\n";
                    fbMatch = false;
                    isValid = false;
                }
                
                break;
            }
        }
        
        if (!found) {
            if (fbMatch) printErrorHeader("Functional Blocks");
            std::cout << "Функциональный блок '" << fb_fboot.get_name() 
                      << "' отсутствует в Sys модели\n";
            std::cout << fb_fboot.get_fb_line() << std::endl;
            fbMatch = false;
            isValid = false;
        }
    }
    
    // Проверка FB, которые есть в Sys, но нет в Fboot
    for (const auto& fb_sys : sys_fbs) {
        bool found = false;
        for (const auto& fb_fboot : fboot_fbs) {
            if (fb_sys.get_name() == fb_fboot.get_name()) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            if (fbMatch) printErrorHeader("Functional Blocks");
            std::cout << "Функциональный блок '" << fb_sys.get_name() 
                      << "' отсутствует в Fboot модели\n";
            fbMatch = false;
            isValid = false;
        }
    }

    // 3. Сравнение соединений
    const auto& fboot_conn = fboot.get_connection();
    const auto& sys_conn = sys.get_connection();
    
    bool connMatch = true;
    if (fboot_conn.size() != sys_conn.size()) {
        printErrorHeader("Connections");
        std::cout << "Количество соединений не совпадает:\n";
        std::cout << "Fboot: " << fboot_conn.size() << ", Sys: " << sys_conn.size() << "\n";
        connMatch = false;
        isValid = false;
    }

    // Проверка каждого соединения в FbootModel
    for (const auto& conn_fboot : fboot_conn) {
        bool found = false;
        for (const auto& conn_sys : sys_conn) {
            if (conn_fboot.get_start() == conn_sys.get_start() && 
                conn_fboot.get_end() == conn_sys.get_end()) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            if (connMatch) printErrorHeader("Connections");
            std::cout << "Соединение отсутствует в Sys модели:\n";
            std::cout << conn_fboot.get_line() << std::endl;
            std::cout << "  Fboot: " << conn_fboot.get_start() << " -> " << conn_fboot.get_end() << "\n";
            connMatch = false;
            isValid = false;
        }
    }
    
    // Проверка соединений, которые есть в Sys, но нет в Fboot
    for (const auto& conn_sys : sys_conn) {
        bool found = false;
        for (const auto& conn_fboot : fboot_conn) {
            if (conn_sys.get_start() == conn_fboot.get_start() && 
                conn_sys.get_end() == conn_fboot.get_end()) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            if (connMatch) printErrorHeader("Connections");
            std::cout << "Соединение отсутствует в Fboot модели:\n";
            std::cout << "  Sys: " << conn_sys.get_start() << " -> " << conn_sys.get_end() << "\n";
            connMatch = false;
            isValid = false;
        }
    }

    // Итоговый вывод
    if (isValid) {
        std::cout << "\n========================================\n";
        std::cout << "Fboot-файл полностью совпадает с sys-файлом\n";
        std::cout << "========================================\n";
    } else {
        std::cout << "\n========================================\n";
        std::cout << "Обнаружены несоответствия между Fboot и Sys моделями\n";
        std::cout << "========================================\n";
    }
}