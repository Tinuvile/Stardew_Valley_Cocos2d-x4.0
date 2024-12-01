#pragma once
#include "cocos2d.h"
#include <string>

//抽象物品基类
class Item {
protected:
    std::string name;
    cocos2d::Sprite* icon;  //物品的图标创建的Sprite
    int value;
    bool usable;
    Item ( const std::string& name , const std::string& icon_path , const int value = 1 , const int& num_limit = 99 );
public:
    const int max_count_in_one_grid;  

    virtual ~Item () {}

    const std::string& GetName () const { return name; }
    cocos2d::Sprite* GetIcon () const { return icon; }
    const bool IsUsable () const { return usable; }
    void SetUsable () { usable = true; }
    void SetUnusable () { usable = false; }
    virtual void Use ();  // 每个物品的使用方法
};