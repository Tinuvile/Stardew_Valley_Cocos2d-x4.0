#pragma once
#include "cocos2d.h"
#include <string>

//物品基类
class Item {
protected:
    std::string name;
    int value;
    bool usable;

public:
    Item(const std::string& name, const std::string& path1, const int value = 1, const int& num_limit = 99);

    //若需创建Sprite所用的图片地址
    const std::string initial_pic;
    // 每个背包格子中最大物品数量
    const int max_count_in_one_grid;

    Item(const Item& other);

    virtual ~Item () {};

    //返回对应Item的name
    const std::string& GetName() const { return name; }

    //返回物品价值
    int GetValue() const { return value; }

    //判断物品是否可使用，可用则返回true, 否则返回false
    const bool IsUsable() const { return usable; }

    //将物品状态设置为可用
    void SetUsable() { usable = true; }

    //将物品状态设置为不可用
    void SetUnusable() { usable = false; }

    //用于判断当前对象与other对象能否在背包中公用存储背包格位
    virtual bool CanBeDepositTogether(const Item& other) const { return max_count_in_one_grid >= 1 && name == other.GetName(); }

    virtual std::shared_ptr<Item> GetCopy() const;

    virtual void Use();  // 每个物品的使用方法
};