cmake_minimum_required(VERSION 3.21)
project(Play_With_Fire)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH "E:/Qt/6.2.4/mingw_64")
set(CMAKE_PREFIX_PATH "C:/Qt/6.2.4/mingw_64")



find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        Multimedia)

add_executable(Play_With_Fire main.cpp src/windows/Home.cpp src/windows/Home.h src/views/TextField.cpp src/views/TextField.h src/views/Background.cpp src/views/Background.h src/views/label.cpp src/views/label.h src/views/Button.cpp src/views/Button.h src/windows/Game.cpp src/windows/Game.h src/views/Block.cpp src/views/Block.h src/views/Box.cpp src/views/Box.h src/views/Wall.cpp src/views/Wall.h src/views/Player.cpp src/views/Player.h resources.qrc src/views/Bomb.cpp src/views/Bomb.h src/views/chooseCharacter.cpp src/views/chooseCharacter.h)
target_link_libraries(Play_With_Fire
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

