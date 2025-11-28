#pragma once
#include "../GameObjectInterface.h"
#include "../tree.h"
#include "cocos2d.h"
#include <string>
#include <memory>

/**
 * Tree类的适配器
 * 将Tree对象适配到统一的GameObjectInterface接口
 */
class TreeAdapter : public GameObjectInterface {
private:
    std::shared_ptr<Tree> tree;
    std::string id;
    cocos2d::Sprite* sprite;
    bool isActiveFlag;
    bool isBeingHarvested;
    
public:
    /**
     * 构造函数
     * @param treePtr 树对象指针
     * @param objectId 对象ID
     */
    TreeAdapter(std::shared_ptr<Tree> treePtr, const std::string& objectId);
    
    /**
     * 析构函数
     */
    virtual ~TreeAdapter();

    // === 基础属性实现 ===
    std::string getId() const override { return id; }
    std::string getType() const override { return "Tree"; }
    std::string getName() const override;

    // === 位置管理实现 ===
    cocos2d::Vec2 getPosition() const override;
    void setPosition(const cocos2d::Vec2& pos) override;
    cocos2d::Rect getBounds() const override;

    // === 渲染相关实现 ===
    cocos2d::Node* getRenderNode() const override { return sprite; }
    void updateTexture(float deltaTime) override;
    bool isVisible() const override;
    void setVisible(bool visible) override;

    // === 生命周期管理实现 ===
    void update(float deltaTime) override;
    bool isActive() const override { return isActiveFlag && tree != nullptr; }
    void setActive(bool active) override { isActiveFlag = active; }
    void cleanup() override;

    // === 交互能力实现 ===
    bool canInteract() const override;
    void onInteract(GameObjectInterface* interactor = nullptr) override;
    std::string getInteractionHint() const override;

    // === 收获能力实现 ===
    bool isHarvestable() const override;
    std::shared_ptr<class Item> harvest() override;
    bool requiresTool() const override { return true; }
    std::string getRequiredTool() const override { return "Axe"; }

    // === 状态查询实现 ===
    std::string getStatusText() const override;
    float getHealth() const override;
    void setHealth(float health) override {} // 树木不使用生命值系统

    // === 事件回调实现 ===
    void onCollisionEnter(GameObjectInterface* other) override;
    void onCollisionExit(GameObjectInterface* other) override;
    void onDayPass() override;
    void onSeasonChange(const std::string& newSeason) override;

    // === Tree特有方法 ===
    
    /**
     * 获取树木被砍伐的次数
     * @return 砍伐次数
     */
    int getRemoveTimes() const;
    
    /**
     * 获取恢复时间
     * @return 恢复所需天数
     */
    int getRecoverTime() const;
    
    /**
     * 获取被砍伐的日期
     * @return 砍伐日期
     */
    int getMiningDay() const;
    
    /**
     * 检查树木是否可用（可砍伐）
     * @return 是否可用
     */
    bool isAvailable() const;
    
    /**
     * 设置树木可用状态
     * @param available 是否可用
     */
    void setAvailable(bool available);
    
    /**
     * 砍伐树木
     * @return 是否成功砍伐
     */
    bool chopTree();
    
    /**
     * 获取树木的当前纹理路径
     * @return 纹理路径
     */
    std::string getCurrentTexturePath() const;
    
    /**
     * 检查树木是否正在恢复中
     * @return 是否在恢复
     */
    bool isRecovering() const;
    
    /**
     * 获取恢复进度
     * @return 恢复进度 (0.0-1.0)
     */
    float getRecoveryProgress() const;
    
    /**
     * 强制恢复树木
     */
    void forceRecover();
    
    /**
     * 获取树木的产出物品
     * @return 产出的物品
     */
    std::shared_ptr<class Item> getProduct() const;
    
    /**
     * 获取原始Tree对象指针
     * @return Tree对象指针
     */
    std::shared_ptr<Tree> getTreePtr() const { return tree; }

private:
    /**
     * 初始化树木精灵
     */
    void initializeSprite();
    
    /**
     * 更新树木外观
     */
    void updateTreeAppearance();
    
    /**
     * 检查恢复条件
     */
    void checkRecovery();
    
    /**
     * 计算恢复进度
     * @return 恢复进度百分比
     */
    float calculateRecoveryProgress() const;
};
