cmake_minimum_required(VERSION 3.10)
project(CHECK_FBT_FBOOT_4DIAC)

# Установка стандарта C++ (C++11 или выше)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для сборки pugixml как статической библиотеки
option(PUGIXML_BUILD_STATIC "Build pugixml as static library" ON)

# Добавляем pugixml как подпроект
add_subdirectory(pugixml-master)

# Список исходных файлов проекта
set(SOURCES
    src/main.cpp
    src/Connection.cpp
    src/FunctionalBlock.cpp
    src/Resource.cpp
    src/SystemModel.cpp
)

# Список заголовочных файлов проекта
set(HEADERS
    include/Connection.h
    include/FunctionalBlock.h
    include/Resource.h
    include/SystemModel.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключаем pugixml к нашему проекту
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml-static)  # Используем статическую версию

# Указываем пути к заголовочным файлам
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/src
)

# Копируем XML файлы из корня проекта в директорию сборки
file(GLOB XML_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.xml")
foreach(XML_FILE ${XML_FILES})
    configure_file(${XML_FILE} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Копируем системные файлы (.sys, .fboot) если нужно
file(GLOB SYS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.sys" "${CMAKE_CURRENT_SOURCE_DIR}/*.fboot")
foreach(SYS_FILE ${SYS_FILES})
    configure_file(${SYS_FILE} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()