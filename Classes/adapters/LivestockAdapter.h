#pragma once
#include "../GameObjectInterface.h"
#include "../Livestock.h"
#include "cocos2d.h"
#include <string>
#include <memory>

/**
 * Livestock类的适配器
 * 将Livestock对象适配到统一的GameObjectInterface接口
 */
class LivestockAdapter : public GameObjectInterface {
private:
    Livestock* livestock;
    std::string id;
    bool isActiveFlag;
    float lastMoveTime;
    float moveInterval;
    float lastProductionTime;
    float productionInterval;
    
public:
    /**
     * 构造函数
     * @param livestockPtr 家畜对象指针
     * @param objectId 对象ID
     */
    LivestockAdapter(Livestock* livestockPtr, const std::string& objectId);
    
    /**
     * 析构函数
     */
    virtual ~LivestockAdapter() = default;

    // === 基础属性实现 ===
    std::string getId() const override { return id; }
    std::string getType() const override { return "Livestock"; }
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
    bool isActive() const override { return isActiveFlag && livestock != nullptr; }
    void setActive(bool active) override { isActiveFlag = active; }
    void cleanup() override;

    // === 交互能力实现 ===
    bool canInteract() const override { return true; }
    void onInteract(GameObjectInterface* interactor = nullptr) override;
    std::string getInteractionHint() const override;

    // === 移动能力实现 ===
    bool canMove() const override { return true; }
    float getMovementSpeed() const override { return 30.0f; } // 家畜移动速度
    void moveTo(const cocos2d::Vec2& target) override;
    void randomMove() override;
    void stopMovement() override;

    // === 生产能力实现 ===
    bool canProduce() const override { return true; }
    bool isReadyToProduce() const override;
    std::shared_ptr<class Item> produce() override;
    float getProductionProgress() const override;

    // === 状态查询实现 ===
    std::string getStatusText() const override;
    float getHealth() const override { return 1.0f; } // 家畜默认满血

    // === 事件回调实现 ===
    void onCollisionEnter(GameObjectInterface* other) override;
    void onCollisionExit(GameObjectInterface* other) override;
    void onDayPass() override;
    void onSeasonChange(const std::string& newSeason) override;

    // === Livestock特有方法 ===
    
    /**
     * 获取家畜种类
     * @return 种类名称
     */
    std::string getSpecies() const;
    
    /**
     * 获取移动区域
     * @return 移动限制区域
     */
    cocos2d::Rect getMoveArea() const;
    
    /**
     * 设置移动区域
     * @param area 新的移动区域
     */
    void setMoveArea(const cocos2d::Rect& area);
    
    /**
     * 检查是否在移动中
     * @return 是否在移动
     */
    bool isMoving() const;
    
    /**
     * 设置移动状态
     * @param moving 是否在移动
     */
    void setMoving(bool moving);
    
    /**
     * 获取移动方向
     * @return 移动方向（0-3：上下左右）
     */
    int getMoveDirection() const;
    
    /**
     * 设置移动方向
     * @param direction 新的移动方向
     */
    void setMoveDirection(int direction);
    
    /**
     * 设置是否可以生产
     * @param canProduce 是否可以生产
     */
    void setCanProduce(bool canProduce);
    
    /**
     * 检查位置是否在允许的移动范围内
     * @param pos 要检查的位置
     * @return 是否在范围内
     */
    bool isPositionInMoveArea(const cocos2d::Vec2& pos) const;
    
    /**
     * 获取到移动区域边界的距离
     * @param pos 要检查的位置
     * @return 到边界的最短距离，负值表示在区域外
     */
    float getDistanceToMoveAreaBoundary(const cocos2d::Vec2& pos) const;
    
    /**
     * 设置移动间隔时间
     * @param interval 移动间隔（秒）
     */
    void setMoveInterval(float interval) { moveInterval = interval; }
    
    /**
     * 获取移动间隔时间
     * @return 移动间隔（秒）
     */
    float getMoveInterval() const { return moveInterval; }
    
    /**
     * 设置生产间隔时间
     * @param interval 生产间隔（秒）
     */
    void setProductionInterval(float interval) { productionInterval = interval; }
    
    /**
     * 获取生产间隔时间
     * @return 生产间隔（秒）
     */
    float getProductionInterval() const { return productionInterval; }
    
    /**
     * 喂食家畜（提高生产效率）
     * @param food 食物类型
     */
    void feed(const std::string& food);
    
    /**
     * 检查家畜是否饥饿
     * @return 是否饥饿
     */
    bool isHungry() const;
    
    /**
     * 获取家畜心情状态
     * @return 心情状态字符串
     */
    std::string getMoodStatus() const;
    
    /**
     * 获取原始Livestock对象指针
     * @return Livestock对象指针
     */
    Livestock* getLivestockPtr() const { return livestock; }

private:
    /**
     * 更新家畜行为
     * @param deltaTime 时间间隔
     */
    void updateBehavior(float deltaTime);
    
    /**
     * 更新移动逻辑
     * @param deltaTime 时间间隔
     */
    void updateMovement(float deltaTime);
    
    /**
     * 更新生产逻辑
     * @param deltaTime 时间间隔
     */
    void updateProduction(float deltaTime);
    
    /**
     * 计算下一个移动位置
     * @return 新的移动位置
     */
    cocos2d::Vec2 calculateNextMovePosition() const;
    
    /**
     * 检查移动位置是否有效
     * @param pos 要检查的位置
     * @return 是否有效
     */
    bool isValidMovePosition(const cocos2d::Vec2& pos) const;
    
    /**
     * 获取家畜类型特定的产品
     * @return 产品Item指针
     */
    std::shared_ptr<class Item> getSpeciesSpecificProduct() const;
};
