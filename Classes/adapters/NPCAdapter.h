#pragma once
#include "../GameObjectInterface.h"
#include "../NPC.h"
#include "cocos2d.h"
#include <string>
#include <vector>

/**
 * NPC类的适配器
 * 将NPC对象适配到统一的GameObjectInterface接口
 */
class NPCAdapter : public GameObjectInterface {
private:
    NPC* npc;
    std::string id;
    bool isActiveFlag;
    float interactionRange;
    bool isInDialog;
    
public:
    /**
     * 构造函数
     * @param npcPtr NPC对象指针
     * @param objectId 对象ID
     */
    NPCAdapter(NPC* npcPtr, const std::string& objectId);
    
    /**
     * 析构函数
     */
    virtual ~NPCAdapter() = default;

    // === 基础属性实现 ===
    std::string getId() const override { return id; }
    std::string getType() const override { return "NPC"; }
    std::string getName() const override;

    // === 位置管理实现 ===
    cocos2d::Vec2 getPosition() const override;
    void setPosition(const cocos2d::Vec2& pos) override;
    cocos2d::Rect getBounds() const override;

    // === 渲染相关实现 ===
    cocos2d::Node* getRenderNode() const override;
    void updateTexture(float deltaTime) override;
    bool isVisible() const override;
    void setVisible(bool visible) override;

    // === 生命周期管理实现 ===
    void update(float deltaTime) override;
    bool isActive() const override { return isActiveFlag && npc != nullptr; }
    void setActive(bool active) override { isActiveFlag = active; }
    void cleanup() override;

    // === 交互能力实现 ===
    bool canInteract() const override { return true; }
    void onInteract(GameObjectInterface* interactor = nullptr) override;
    std::string getInteractionHint() const override;

    // === 移动能力实现 ===
    bool canMove() const override { return true; }
    float getMovementSpeed() const override { return 60.0f; } // NPC移动速度
    void moveTo(const cocos2d::Vec2& target) override;
    void randomMove() override;
    void stopMovement() override;

    // === 对话能力实现 ===
    bool canTalk() const override { return true; }
    std::vector<std::string> getDialogOptions() const override;
    void startDialog() override;

    // === 状态查询实现 ===
    std::string getStatusText() const override;
    float getHealth() const override { return 1.0f; } // NPC默认满血

    // === 事件回调实现 ===
    void onCollisionEnter(GameObjectInterface* other) override;
    void onCollisionExit(GameObjectInterface* other) override;
    void onDayPass() override;
    void onSeasonChange(const std::string& newSeason) override;

    // === NPC特有方法 ===
    
    /**
     * 获取NPC的精灵对象
     * @return 精灵对象指针
     */
    cocos2d::Sprite* getNPCSprite() const;
    
    /**
     * 设置交互范围
     * @param range 交互范围（像素）
     */
    void setInteractionRange(float range) { interactionRange = range; }
    
    /**
     * 获取交互范围
     * @return 交互范围
     */
    float getInteractionRange() const { return interactionRange; }
    
    /**
     * 检查指定位置是否有效（NPC可以移动到该位置）
     * @param targetPos 目标位置
     * @param direction 移动方向
     * @return 是否有效
     */
    bool isPositionValid(const cocos2d::Vec2& targetPos, const cocos2d::Vec2& direction) const;
    
    /**
     * 获取对话选项
     * @param relationshipLevel 关系等级
     * @return 对话选项列表
     */
    std::vector<std::string> getDialogForRelationship(const std::string& relationshipLevel) const;
    
    /**
     * 获取节日对话
     * @param relationshipLevel 关系等级
     * @return 节日对话选项
     */
    std::vector<std::string> getFestivalDialog(const std::string& relationshipLevel) const;
    
    /**
     * 获取NPC肖像
     * @param status 状态（normal, happy, sad等）
     * @return 肖像图片路径
     */
    std::string getPortraitPath(const std::string& status = "normal") const;
    
    /**
     * 检查是否正在对话中
     * @return 是否在对话中
     */
    bool isDialogActive() const { return isInDialog; }
    
    /**
     * 设置对话状态
     * @param active 是否激活对话
     */
    void setDialogActive(bool active) { isInDialog = active; }
    
    /**
     * 获取原始NPC对象指针
     * @return NPC对象指针
     */
    NPC* getNPCPtr() const { return npc; }
    
    /**
     * 播放动画
     * @param animationName 动画名称
     * @param loop 是否循环
     */
    void playAnimation(const std::string& animationName, bool loop = true);
    
    /**
     * 面向指定位置
     * @param targetPos 目标位置
     */
    void faceTowards(const cocos2d::Vec2& targetPos);

private:
    /**
     * 更新NPC行为逻辑
     * @param deltaTime 时间间隔
     */
    void updateBehavior(float deltaTime);
    
    /**
     * 处理AI移动逻辑
     */
    void updateAIMovement();
    
    /**
     * 获取NPC类型特定的对话
     * @return 对话选项
     */
    std::vector<std::string> getTypeSpecificDialog() const;
};
