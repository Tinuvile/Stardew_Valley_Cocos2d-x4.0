#pragma once

#include"cocos2d.h"
#include"Item.h"
#include<memory>
#include<string>


class Livestock : public cocos2d::Sprite {
protected:
    std::string species;  // 种类，例如"牛", "羊", "鸡"等
    std::string icon_path; // 图片路径
    bool can_produce;  // 是否可以生产（例如是否已经产奶、下蛋等）
    cocos2d::Rect move_area;  // 限定家畜活动的矩形范围
    int move_direction = 0;  //移动的方向
    bool moving = false;  //移动状态，正在移动改为true,静止为false
public:
    // 构造函数
    Livestock ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area );

    virtual bool init ();

    // 静态create方法
    static Livestock* create ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area );

    // 虚析构函数
    virtual ~Livestock ();

    // 随机移动的方法
    void RandomMove ();

    // 设置家畜能否生产产品的状态
    void SetCanProduce ( bool can ) {
        can_produce = can;
    }

    // 家畜是否可以生产产品
    bool IsCanProduce () const {
        return can_produce;
    }

    // 产出产品的虚方法
    virtual std::shared_ptr<Item> ProduceProduct () {
        return nullptr;
    }

    // 获取家畜的种类
    const std::string& GetSpecies () const {
        return species;
    }

    void SetMoving ( bool is_moving ) { moving = is_moving; }
    

};