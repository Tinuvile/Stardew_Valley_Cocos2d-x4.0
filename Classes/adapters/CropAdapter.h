#pragma once
#include "../GameObjectInterface.h"
#include "../Crop.h"
#include "cocos2d.h"
#include <string>
#include <memory>

/**
 * Crop类的适配器
 * 将Crop对象适配到统一的GameObjectInterface接口
 */
class CropAdapter : public GameObjectInterface {
private:
    std::shared_ptr<Crop> crop;
    std::string id;
    cocos2d::Vec2 position;
    cocos2d::Sprite* sprite;
    bool isActiveFlag;
    float lastUpdateTime;
    
public:
    /**
     * 构造函数
     * @param cropPtr 作物对象指针
     * @param objectId 对象ID
     * @param pos 作物位置
     */
    CropAdapter(std::shared_ptr<Crop> cropPtr, const std::string& objectId, 
                const cocos2d::Vec2& pos);
    
    /**
     * 析构函数
     */
    virtual ~CropAdapter();

    // === 基础属性实现 ===
    std::string getId() const override { return id; }
    std::string getType() const override { return "Crop"; }
    std::string getName() const override;

    // === 位置管理实现 ===
    cocos2d::Vec2 getPosition() const override { return position; }
    void setPosition(const cocos2d::Vec2& pos) override;
    cocos2d::Rect getBounds() const override;

    // === 渲染相关实现 ===
    cocos2d::Node* getRenderNode() const override { return sprite; }
    void updateTexture(float deltaTime) override;
    bool isVisible() const override;
    void setVisible(bool visible) override;

    // === 生命周期管理实现 ===
    void update(float deltaTime) override;
    bool isActive() const override { return isActiveFlag && crop != nullptr; }
    void setActive(bool active) override { isActiveFlag = active; }
    void cleanup() override;

    // === 交互能力实现 ===
    bool canInteract() const override;
    void onInteract(GameObjectInterface* interactor = nullptr) override;
    std::string getInteractionHint() const override;

    // === 收获能力实现 ===
    bool isHarvestable() const override;
    std::shared_ptr<class Item> harvest() override;
    bool requiresTool() const override { return false; }
    std::string getRequiredTool() const override { return ""; }

    // === 成长能力实现 ===
    bool canGrow() const override { return true; }
    float getGrowthProgress() const override;
    void water() override;
    bool needsWater() const override;
    void advanceGrowth() override;

    // === 状态查询实现 ===
    std::string getStatusText() const override;
    float getHealth() const override;
    void setHealth(float health) override {} // 作物不使用生命值系统

    // === 事件回调实现 ===
    void onCollisionEnter(GameObjectInterface* other) override;
    void onCollisionExit(GameObjectInterface* other) override;
    void onDayPass() override;
    void onSeasonChange(const std::string& newSeason) override;

    // === Crop特有方法 ===
    
    /**
     * 获取作物当前阶段
     * @return 作物阶段枚举
     */
    Phase getCropPhase() const;
    
    /**
     * 获取作物季节
     * @return 适合生长的季节
     */
    std::string getCropSeason() const;
    
    /**
     * 获取作物种植天数
     * @return 已种植天数
     */
    int getPlantDay() const;
    
    /**
     * 获取成熟所需天数
     * @return 成熟所需天数
     */
    int getMatureNeeded() const;
    
    /**
     * 检查今天是否已浇水
     * @return 是否已浇水
     */
    bool isWateredToday() const;
    
    /**
     * 设置浇水状态
     * @param watered 是否浇水
     */
    void setWatered(bool watered);
    
    /**
     * 获取作物价值
     * @return 当前价值
     */
    int getCropValue() const;
    
    /**
     * 设置作物为枯死状态
     */
    void setDead();
    
    /**
     * 检查作物是否为种子状态
     * @return 是否为种子
     */
    bool isSeed() const;
    
    /**
     * 检查作物是否成熟
     * @return 是否成熟
     */
    bool isMature() const;
    
    /**
     * 检查作物是否枯死
     * @return 是否枯死
     */
    bool isDead() const;
    
    /**
     * 强制更新作物生长状态
     */
    void forceGrowthUpdate();
    
    /**
     * 获取作物的副本（用于收获）
     * @return 作物副本
     */
    std::shared_ptr<Crop> getCropCopy() const;
    
    /**
     * 获取原始Crop对象指针
     * @return Crop对象指针
     */
    std::shared_ptr<Crop> getCropPtr() const { return crop; }
    
    /**
     * 根据阶段获取对应的图片路径
     * @param phase 作物阶段
     * @return 图片路径
     */
    std::string getTexturePathForPhase(Phase phase) const;
    
    /**
     * 检查作物是否适合当前季节
     * @param currentSeason 当前季节
     * @return 是否适合
     */
    bool isSuitableForSeason(const std::string& currentSeason) const;

private:
    /**
     * 初始化作物精灵
     */
    void initializeSprite();
    
    /**
     * 更新作物外观
     */
    void updateCropAppearance();
    
    /**
     * 检查作物生长条件
     * @return 是否满足生长条件
     */
    bool checkGrowthConditions() const;
    
    /**
     * 计算生长进度百分比
     * @return 生长进度 (0.0-1.0)
     */
    float calculateGrowthPercentage() const;
};
