#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Stardew_Valley_Cocos2d-x4.0)

project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test Stardew_Valley_Cocos2d-x4.0 into root project
    # 设置全局警告抑制
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    
    # 为MSVC设置警告级别
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W0")
    endif()
    
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     # Core
     Classes/Core/AppDelegate.cpp
     Classes/Core/InputManager.cpp
     
     # Commands
     Classes/Commands/GameActionCommand.cpp
     Classes/Commands/PlayerMovementCommand.cpp
     Classes/Commands/SceneInteractionCommand.cpp
     Classes/Commands/UICommand.cpp
     
     # Factories
     Classes/Factories/AnimalFactory.cpp
     Classes/Factories/SceneBoundaryFactory.cpp
     
     # Entities
     Classes/Entities/Chicken.cpp
     Classes/Entities/Cow.cpp
     Classes/Entities/Crop.cpp
     Classes/Entities/Fish.cpp
     Classes/Entities/Livestock.cpp
     Classes/Entities/Marry.cpp
     Classes/Entities/NPC.cpp
     Classes/Entities/NPCreate.cpp
     Classes/Entities/NpcRelationship.cpp
     Classes/Entities/Player.cpp
     Classes/Entities/Sheep.cpp
     Classes/Entities/tree.cpp
     
     # Items
     Classes/Items/CookingPot.cpp
     Classes/Items/Food.cpp
     Classes/Items/Generaltem.cpp
     Classes/Items/Item.cpp
     Classes/Items/ItemFlyweight.cpp
     Classes/Items/Ore.cpp
     Classes/Items/Wool.cpp
     
     # Scenes
     Classes/Scenes/Barn.cpp
     Classes/Scenes/Beach.cpp
     Classes/Scenes/Cave.cpp
     Classes/Scenes/CropSpritePool.cpp
     Classes/Scenes/farm.cpp
     Classes/Scenes/Forest.cpp
     Classes/Scenes/HelloWorldScene.cpp
     Classes/Scenes/Myhouse.cpp
     Classes/Scenes/supermarket.cpp
     Classes/Scenes/Town.cpp
     
     # Systems
     Classes/Systems/EconomicSystem.cpp
     Classes/Systems/EnergySystem.cpp
     Classes/Systems/FishingGame.cpp
     Classes/Systems/GameInteractionFacade.cpp
     Classes/Systems/Inventroy.cpp
     Classes/Systems/Skill.cpp
     Classes/Systems/SkillTree.cpp
     Classes/Systems/TaskManagement.cpp
     Classes/Systems/Timesystem.cpp
     
     # UI
     Classes/UI/CreateCharacterUI.cpp
     Classes/UI/DailyRecordUI.cpp
     Classes/UI/DetailedtaskUI.cpp
     Classes/UI/GameBeginUI.cpp
     Classes/UI/intimacyUI.cpp
     Classes/UI/InventoryUI.cpp
     Classes/UI/mailBoxUI.cpp
     Classes/UI/mini_bag.cpp
     Classes/UI/NPCtalkUI.cpp
     Classes/UI/quitUI.cpp
     Classes/UI/SkilltreeUI.cpp
     Classes/UI/StoreUI.cpp
     )
list(APPEND GAME_HEADER
     # Core
     Classes/Core/AppDelegate.h
     Classes/Core/BasicInformation.h
     Classes/Core/GameStateObserver.h
     Classes/Core/InputManager.h
     
     # Commands
     Classes/Commands/GameActionCommand.h
     Classes/Commands/KeyCommand.h
     Classes/Commands/PlayerMovementCommand.h
     Classes/Commands/SceneInteractionCommand.h
     Classes/Commands/UICommand.h
     
     # Entities
     Classes/Entities/Chicken.h
     Classes/Entities/Cow.h
     Classes/Entities/Crop.h
     Classes/Entities/Fish.h
     Classes/Entities/Livestock.h
     Classes/Entities/Marry.h
     Classes/Entities/NPC.h
     Classes/Entities/NPCreate.h
     Classes/Entities/NpcRelationship.h
     Classes/Entities/Player.h
     Classes/Entities/Sheep.h
     Classes/Entities/tree.h
     
     # Items
     Classes/Items/CookingPot.h
     Classes/Items/Food.h
     Classes/Items/Generaltem.h
     Classes/Items/Item.h
     Classes/Items/ItemFlyweight.h
     Classes/Items/Ore.h
     Classes/Items/Wool.h
     
     # Scenes
     Classes/Scenes/Barn.h
     Classes/Scenes/Beach.h
     Classes/Scenes/Cave.h
     Classes/Scenes/CropSpritePool.h
     Classes/Scenes/farm.h
     Classes/Scenes/Forest.h
     Classes/Scenes/HelloWorldScene.h
     Classes/Scenes/Myhouse.h
     Classes/Scenes/supermarket.h
     Classes/Scenes/Town.h
     
     # Systems
     Classes/Systems/EconomicSystem.h
     Classes/Systems/EnergySystem.h
     Classes/Systems/FishingGame.h
     Classes/Systems/GameInteractionFacade.h
     Classes/Systems/Inventory.h
     Classes/Systems/Skill.h
     Classes/Systems/SkillTree.h
     Classes/Systems/TaskManagement.h
     Classes/Systems/Timesystem.h
     
     # UI
     Classes/UI/CreateCharacterUI.h
     Classes/UI/DailyRecordUI.h
     Classes/UI/DetailedtaskUI.h
     Classes/UI/GameBeginUI.h
     Classes/UI/intimacyUI.h
     Classes/UI/InventoryUI.h
     Classes/UI/mailBoxUI.h
     Classes/UI/mini_bag.h
     Classes/UI/NPCtalkUI.h
     Classes/UI/quitUI.h
     Classes/UI/SkillTreeUI.h
     Classes/UI/StoreUI.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# 添加编译器特定设置
if(MSVC)
    # 设置UTF-8编码支持
    target_compile_options(${APP_NAME} PRIVATE /utf-8)
    # 禁用所有警告
    target_compile_options(${APP_NAME} PRIVATE /w)
    # 设置警告级别为最低
    target_compile_options(${APP_NAME} PRIVATE /W0)
    # 禁用特定常见警告
    target_compile_options(${APP_NAME} PRIVATE /wd4819) # 文件编码问题
    target_compile_options(${APP_NAME} PRIVATE /wd4996) # 已弃用函数
    target_compile_options(${APP_NAME} PRIVATE /wd4244) # 类型转换可能丢失数据
    target_compile_options(${APP_NAME} PRIVATE /wd4267) # size_t到int的转换
    target_compile_options(${APP_NAME} PRIVATE /wd4800) # 强制转换为bool
    target_compile_options(${APP_NAME} PRIVATE /wd4005) # 宏重定义
    target_compile_options(${APP_NAME} PRIVATE /wd4018) # 有符号/无符号不匹配
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC和Clang警告抑制
    target_compile_options(${APP_NAME} PRIVATE -w)
    target_compile_options(${APP_NAME} PRIVATE -Wno-all)
    target_compile_options(${APP_NAME} PRIVATE -Wno-deprecated)
    target_compile_options(${APP_NAME} PRIVATE -Wno-deprecated-declarations)
    target_compile_options(${APP_NAME} PRIVATE -Wno-unused-variable)
    target_compile_options(${APP_NAME} PRIVATE -Wno-unused-parameter)
    target_compile_options(${APP_NAME} PRIVATE -Wno-sign-compare)
    target_compile_options(${APP_NAME} PRIVATE -Wno-conversion)
endif()

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
