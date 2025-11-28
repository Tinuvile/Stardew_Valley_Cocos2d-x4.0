#ifndef __SCENE_ACTION_HANDLER_H__
#define __SCENE_ACTION_HANDLER_H__

#include "InputHandler.h"

/**
 * 场景动作输入处理器
 * 根据不同场景处理相应的动作按键
 */
class SceneActionHandler : public InputHandler {
public:
    SceneActionHandler();
    virtual ~SceneActionHandler() = default;
    
    /**
     * 处理按键按下事件
     * 根据当前场景处理不同的动作按键
     */
    bool handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 处理按键释放事件
     */
    bool handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 获取处理器类型名称
     */
    std::string getHandlerType() const override { return "SceneActionHandler"; }

private:
    /**
     * 处理农场场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleFarmActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理海滩场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleBeachActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理洞穴场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleCaveActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理城镇场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleTownActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理房屋场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleHouseActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理森林场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleForestActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理畜棚场景的按键
     * @param keyCode 按键代码
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleBarnActions(EventKeyboard::KeyCode keyCode, const GameContext& context);
    
    /**
     * 处理通用的ENTER键交互
     * @param context 游戏上下文
     * @return 是否处理成功
     */
    bool handleEnterInteraction(const GameContext& context);
    
    /**
     * 种植作物
     * @param playerPos 玩家位置
     * @param scene 当前场景
     * @return 是否种植成功
     */
    bool plantCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene);
    
    /**
     * 浇水
     * @param playerPos 玩家位置
     * @param scene 当前场景
     * @return 是否浇水成功
     */
    bool waterCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene);
    
    /**
     * 收割作物
     * @param playerPos 玩家位置
     * @param scene 当前场景
     * @return 是否收割成功
     */
    bool harvestCrop(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene);
    
    /**
     * 开始钓鱼
     * @param playerPos 玩家位置
     * @param scene 当前场景
     * @return 是否成功开始钓鱼
     */
    bool startFishing(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene);
    
    /**
     * 挖矿
     * @param playerPos 玩家位置
     * @param scene 当前场景
     * @return 是否挖矿成功
     */
    bool mineOre(const cocos2d::Vec2& playerPos, cocos2d::Scene* scene);
    
    /**
     * 检查玩家是否有足够体力进行动作
     * @param requiredEnergy 需要的体力
     * @return 是否有足够体力
     */
    bool hasEnoughEnergy(int requiredEnergy);
    
    /**
     * 消耗玩家体力
     * @param energyCost 消耗的体力值
     */
    void consumeEnergy(int energyCost);
};

#endif // __SCENE_ACTION_HANDLER_H__
