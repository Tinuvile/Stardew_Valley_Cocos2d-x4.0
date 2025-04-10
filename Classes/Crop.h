#pragma once

#include"Item.h"
#include "AppDelegate.h"
#include<cocos2d.h>
#include <iostream>
#include <memory>
#include <string>

enum Phase {
    SEED,    //种子
    GROWING, //生长中
    MATURE,  //成熟
    SAPLESS, // 枯萎状态 
    DEAD     //枯死 在季节更换后作物需设为枯死状态 
};

class Crop :public Item {
private:
    const std::string season; //作物生长的季节
    int mature_needed;  //达到成熟所需天数
    Phase phase;      //当前阶段，对应`SEED` `GROWING` `MATURE`三个阶段 
    bool harvestable;         //是否可收获
public:
    //存放作物不同时期对应的图片路径
    const std::string growing_pic;
    const std::string mature_pic;
    // 种植地块编号
    int nums;
    //当天是否浇过水 每天更新为false
    bool watered;            
    // 种植的日期
    int plant_day;     
    //作物类
    Crop(const std::string& crop_name, const std::string& initial_pic,
        const std::string& growing_pic, const std::string& mature_pic, const std::string& season,
        const Phase& current_phase = SEED, const int value = 1, const int plant_day = 0,
        const bool is_harvestable = false, const int mature_limit = 4);
    Crop(const Crop& other);
    // 默认初始化函数
    Crop():Item("Unkown", "Unkown", 0), growing_pic("Unkown"), mature_pic("Unkown"),
        season("Unkown"), mature_needed(0), phase(Phase::SEED),
        plant_day(0), harvestable(false), watered(false), nums(500) {}


    virtual ~Crop() {};


    const std::string& GetSeason() const { return season; }
    //判断是否为种子状态
    bool IsSeed() const { return phase == SEED; }
    //判断是否为成熟状态
    bool IsMature() const { return phase == MATURE; }
    //获取作物种植的天数
    int GetGrowthProgress() const { return plant_day; }
    //获取当前的`phase`
    Phase GetPhase() const { return phase; }
    //获取作物当前是否可以收获
    bool IsHarvestable() const { return harvestable; }
    // 浇水
    void Water();
    // 更新作物状态 每进入新的一天时需调用
    void UpdateGrowth();
    //设置状态为DEAD growth_progress设为-1 harvestable为flase
    void SetDead();
    //重新设置物品价值 成熟作物需更新其价值
    void SetValue(const int update_value);

    //用于判断当前对象与other对象能否在背包中公用存储背包格位
    virtual bool CanBeDepositTogether(const Item& other) const;

    //获取shared_ptr<Crop>类型的的副本 
    //种植时使用该方法
    //以便后续铲除或收获后及时通过reset销毁对象
    //避免手动调用new和delete可能出现的问题
    virtual std::shared_ptr<Item> GetCopy() const;

    std::shared_ptr<Crop> GetCropCopy() const;

    //收获
    //此处仅提供能否收获的条件判断和销毁对应Crop对象的操作


    //获取物品操作需进一步结合玩家类
    //对应实例不可收获或传入的shared_ptr<Crop>为空均返回false
    //对应实例可收获则销毁对应对象返回true
    static bool Harvest(std::shared_ptr<Crop> to_harvest);


    //铲除
    //提供销毁对应Crop对象的操作


    //若传入的shared_ptr<Crop>为空返回false
    //否则销毁对应对象并返回true
    static bool Remove(std::shared_ptr<Crop> to_remove);


    void ChangePhase(Phase phase) {
        this->phase = phase;
    }

    void ChangMatureNeeded(int Time) {
        this->mature_needed += Time;
    }

};