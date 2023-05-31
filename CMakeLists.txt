cmake_minimum_required(VERSION 3.5)

project(ProjectImageEdit)

# Set the minimum required version of Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED)



# Add your source files here
set(SOURCES
        main.cpp
        utilities.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        imagefile.cpp
        imagefile.h
        croptool.cpp
        croptool.h
        pixel.h
        pixel.cpp
        utilities.cpp
        imageedit.h
        edits.h
        editingmanager.h
        editingmanager.cpp
        inputdialog.h
        inputdialog.cpp
)




# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link OpenCV libraries

target_link_libraries(ProjectImageEdit Qt6::Widgets Qt6::Core)



