cmake_minimum_required(VERSION 3.10)
project(CHECK_FBT_FBOOT_4DIAC)

# Установка стандарта C++ (C++11 или выше)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Опция для сборки pugixml как статической библиотеки (если она всё ещё нужна)
option(PUGIXML_BUILD_STATIC "Build pugixml as static library" ON)

# Добавляем pugixml как подпроект (если он всё ещё используется)
add_subdirectory(pugixml-master)

# Список исходных файлов проекта
set(SOURCES
    src/main.cpp
    src/Connection.cpp
    src/FunctionalBlock.cpp
    src/Resource.cpp
    src/SysModel.cpp
    src/Mapping.cpp
    src/FbootModel.cpp
)

# Список заголовочных файлов проекта
set(HEADERS
    include/Connection.h
    include/FunctionalBlock.h
    include/Resource.h
    include/SysModel.h
    include/Mapping.h
    include/FbootModel.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключаем pugixml (если он нужен)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml-static)

# Указываем пути к заголовочным файлам
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/src  # (если pugixml всё ещё используется)
)

# Копируем только .sys и .fboot файлы из папки files в директорию сборки
file(GLOB CONFIG_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/files/*.sys" 
    "${CMAKE_CURRENT_SOURCE_DIR}/files/*.fboot"
)
foreach(CONFIG_FILE ${CONFIG_FILES})
    get_filename_component(FILE_NAME ${CONFIG_FILE} NAME)
    configure_file(${CONFIG_FILE} ${CMAKE_BINARY_DIR}/${FILE_NAME} COPYONLY)
endforeach()