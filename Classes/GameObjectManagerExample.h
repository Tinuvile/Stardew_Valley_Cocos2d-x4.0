#pragma once
#include "GameObjectManager.h"
#include "adapters/AdapterFactory.h"
#include "Player.h"
#include "NPC.h"
#include "Crop.h"
#include "Livestock.h"
#include "Tree.h"
#include "Ore.h"
#include "cocos2d.h"

/**
 * 游戏对象管理器集成示例
 * 演示如何使用新的统一对象管理系统
 */
class GameObjectManagerExample {
private:
    GameObjectManager* objectManager;
    cocos2d::Scene* currentScene;
    
public:
    GameObjectManagerExample();
    ~GameObjectManagerExample();
    
    /**
     * 初始化示例
     * @param scene 当前场景
     * @return 是否初始化成功
     */
    bool initialize(cocos2d::Scene* scene);
    
    /**
     * 清理示例
     */
    void cleanup();
    
    /**
     * 更新所有对象
     * @param deltaTime 时间间隔
     */
    void update(float deltaTime);
    
    // === 示例功能 ===
    
    /**
     * 创建示例玩家
     * @param position 初始位置
     * @return 玩家对象ID
     */
    std::string createExamplePlayer(const cocos2d::Vec2& position);
    
    /**
     * 创建示例NPC
     * @param name NPC名称
     * @param position 初始位置
     * @return NPC对象ID
     */
    std::string createExampleNPC(const std::string& name, const cocos2d::Vec2& position);
    
    /**
     * 创建示例作物
     * @param cropName 作物名称
     * @param position 种植位置
     * @return 作物对象ID
     */
    std::string createExampleCrop(const std::string& cropName, const cocos2d::Vec2& position);
    
    /**
     * 创建示例家畜
     * @param species 家畜种类
     * @param position 初始位置
     * @param area 移动区域
     * @return 家畜对象ID
     */
    std::string createExampleLivestock(const std::string& species, 
                                     const cocos2d::Vec2& position,
                                     const cocos2d::Rect& area);
    
    /**
     * 创建示例树木
     * @param position 树木位置
     * @return 树木对象ID
     */
    std::string createExampleTree(const cocos2d::Vec2& position);
    
    /**
     * 创建示例矿石
     * @param position 矿石位置
     * @return 矿石对象ID
     */
    std::string createExampleOre(const cocos2d::Vec2& position);
    
    // === 演示功能 ===
    
    /**
     * 演示碰撞检测
     */
    void demonstrateCollisionDetection();
    
    /**
     * 演示范围查询
     * @param center 查询中心
     * @param radius 查询半径
     */
    void demonstrateRangeQuery(const cocos2d::Vec2& center, float radius);
    
    /**
     * 演示交互功能
     * @param playerPos 玩家位置
     */
    void demonstrateInteraction(const cocos2d::Vec2& playerPos);
    
    /**
     * 演示日期变化事件
     */
    void demonstrateDayPass();
    
    /**
     * 演示季节变化事件
     * @param newSeason 新季节
     */
    void demonstrateSeasonChange(const std::string& newSeason);
    
    /**
     * 演示对象统计
     */
    void demonstrateObjectStats();
    
    /**
     * 创建一个完整的农场场景示例
     */
    void createFarmSceneExample();
    
    /**
     * 创建一个完整的小镇场景示例
     */
    void createTownSceneExample();
    
    // === 工具方法 ===
    
    /**
     * 获取对象管理器
     * @return 对象管理器指针
     */
    GameObjectManager* getObjectManager() const { return objectManager; }
    
    /**
     * 打印所有对象信息
     */
    void printAllObjects() const;
    
    /**
     * 验证系统完整性
     * @return 是否通过验证
     */
    bool validateSystem() const;

private:
    /**
     * 设置事件回调
     */
    void setupEventCallbacks();
    
    /**
     * 创建默认的作物基础信息
     */
    void initializeCropData();
};
