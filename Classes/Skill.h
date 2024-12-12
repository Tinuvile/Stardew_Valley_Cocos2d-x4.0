#pragma once
#include<iostream>
#include<unordered_map>

//耕种技能，通过收获农产品（农作物，畜产品）获取经验
const int farming_skill = 0;
//采矿技能 通过敲碎岩石获取经验 每次升级增加镐工具的熟练度
const int mining_skill = 1;
//采集技能 通过采集物品和砍伐树木获取经验 每次升级增加斧工具的熟练度
const int foraging_skill = 2;
//钓鱼技能 通过成功完成钓鱼小游戏获取经验
const int fishing_skill = 3;
//战斗技能 是否实现待定
const int combat_skill = 4;

class Skill {
private:
    int type;                // 技能类型（例如 farming_skill）
    int level;               // 当前技能等级，默认初始等级为0级
    //experience 和 experience_needed 均采用总累计值
    int experience;          // 当前技能经验值
    int experience_needed;   // 升级所需经验

    // 根据等级动态计算升级所需经验
    int CalculateExperienceNeeded ( const int level ) const;

public:
    //默认构造函数
    Skill () {}

    // 构造函数 
    Skill ( const int skill_type );

    // 获取技能类型
    int GetType() const { return type; }

    // 获取当前技能等级
    int GetLevel() const { return level; }

    // 获取当前经验值
    int GetExperience() const { return experience; }

    // 获取升级所需经验
    int GetExperienceNeeded() const { return experience_needed; }

    // 增加经验值，并自动处理升级逻辑
    void AddExperience ( const int amount );

    // 重置技能等级和经验
    void Reset ();


private:
    // 等级提升
    int LevelUp ();

    //升级具体效果待定
};



