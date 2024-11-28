## 项目简介

星露谷风格的农场生活模拟游戏。玩家将管理自己的农场，种植作物，养殖动物，与镇上的居民互动，参与节日活动，并探索周围的自然环境。游戏包含丰富的季节变化、社区交互和个人角色发展。

## 基础功能

### 农场管理
- 玩家可以耕种、种植并收获多种作物，作物的成熟时间根据种类和季节变化。
- 养殖包括但不限于牛、鸡和羊等动物。
- 农场操作包括浇水、施肥，以及管理干旱和病害威胁，未及时处理会导致作物死亡。
- 管理农场资源，如水资源、种子和肥料存储。
### 社区交互：
- 与镇上的居民建立关系，包括友谊和浪漫关系。
- 参与定期的社区活动和节日庆典。
- 接受并完成居民的委托任务，提高声望和收获奖励，任务包括收集特定物品、帮助修复建筑等。
### 探索和冒险：
- 探索农场周边的地区，包括森林、山脉和神秘洞穴。
- 挖掘矿物、钓鱼和收集稀有物品。
### 角色成长和技能：
- 角色技能树，包括农业、采矿、钓鱼和料理等。
- 随着技能提升，解锁新的作物种类、工具升级和烹饪食谱。

## 开发日志

### 2024/11/26
* 配置Cocos与CMake环境
* 确定小组分工
* 完成中枢地图移动区域限制

### 2024/11/27
* 开场动画与界面UI

### 2024/11/28
* 角色人物关系类
* 单元测试

## NpcRelationship接口

### 概述
NpcRelationship 类用于管理 NPC（非玩家角色）之间的关系。该类提供了添加或移除 NPC、设置和获取 NPC 之间的关系值以及关系层级的方法。

### 类声明
```cpp
class NpcRelationship {  
public:  
    NpcRelationship();         // 构造函数  
    ~NpcRelationship();        // 析构函数  

    void add_npc(const string& npcName);           // 添加一个 NPC  
    void remove_npc(const string& npcName);        // 移除一个 NPC  

    void setRelationship(const string& npcA, const string& npcB, int value); // 设置两个 NPC 之间的关系值  
    
    void increaseRelationship(const std::string& npcA, const std::string& npcB, int amount); // 增加关系值  
    void decreaseRelationship(const std::string& npcA, const std::string& npcB, int amount); // 减少关系值  

    std::string getRelationshipLevel(const std::string& npcA, const std::string& npcB) const; // 获取 NPC 之间关系等级，此处分为四种，可用于设计与主角的交互行为  

    int getRelationship(const string& npcA, const string& npcB) const; // 获取 NPC 之间的关系值  

    void printRelationships() const; // 打印所有 NPC 之间的关系  
private:  
    unordered_map<string, unordered_map<string, int>> relationships; // 存储 NPC 之间的关系  

    static const int MIN_RELATIONSHIP = -100; // 最小关系值  
    static const int MAX_RELATIONSHIP = 100;  // 最大关系值  
};
```

## Test说明

Test部分用于测试编写的数据结构类的正确性，具体使用方法放在代码文件中，可能需要用vs installer下载google test
