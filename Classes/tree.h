#pragma once

#include"Item.h"
#include <cocos2d.h>
#include <iostream>
#include <memory>
#include <string>



class Tree :public Item {
public:
    // 存放作物不同时期对应的图片路径
    const std::string G_Cut_pic; //
    const std::string Y_Ini_pic; //
    // 放置地块位置
    cocos2d::Vec2 position;
    // 被挖去的日子
    int mining_day;     
    // 挖矿后恢复所需要的时间
    int recover_time;      
    // 是否可挖取
    bool available;        

    
    Tree(const std::string& ore_name, const std::string& initial_pic,
       const std::string& G_Cut_pic, const std::string& Y_Ini_pic,
        const int value, int recover_time, cocos2d::Vec2 position);
    Tree(const Tree& other);
    // 默认初始化函数
    Tree() :Item("Unkown", "Unkown"), G_Cut_pic("Unkown"), Y_Ini_pic("Unkown"), recover_time(0),
        mining_day(0), position(1000,1000), available(true) {}


    virtual ~Tree() {};

    //获取作物当前是否可以收获
    bool IsHarvestable() const { return available; }
    //重新设置物品价值 成熟作物需更新其价值
    void SetValue(const int update_value);
    //用于判断当前对象与other对象能否在背包中公用存储背包格位
    virtual bool CanBeDepositTogether(const Item& other) const;

    //获取shared_ptr<Crop>类型的的副本 
    //种植时使用该方法
    //以便后续铲除或收获后及时通过reset销毁对象
    //避免手动调用new和delete可能出现的问题
    virtual std::shared_ptr<Item> GetCopy() const;

    std::shared_ptr<Tree> GetTreeCopy() const;

    bool Remove(std::shared_ptr<Tree> to_remove);


};