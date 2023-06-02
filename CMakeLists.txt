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
set(BACKEND
        backend/main.cpp
        backend/utilities.h
        backend/imagefile.cpp
        backend/imagefile.h
        backend/pixel.h
        backend/pixel.cpp
        backend/utilities.cpp
        backend/editingTools/croptool.cpp
        backend/editingTools/croptool.h
        backend/editingTools/imageedit.h
        backend/editingTools/edits.h
        backend/editingTools/editingmanager.h
        backend/editingTools/editingmanager.cpp
)

set(GUI
        gui/inputdialog.cpp
        gui/inputdialog.h
        gui/mainwindow.cpp
        gui/mainwindow.h
        gui/mainwindow.ui
)



# Create the executable target
add_executable(${PROJECT_NAME} ${BACKEND} ${GUI})

# Link OpenCV libraries

target_link_libraries(ProjectImageEdit Qt6::Widgets Qt6::Core)



