#pragma once
#include "GameObjectInterface.h"
#include "cocos2d.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <algorithm>

/**
 * 统一的游戏对象管理器
 * 负责管理所有游戏对象的生命周期、更新、渲染和交互
 */
class GameObjectManager {
private:
    // 所有游戏对象的主存储
    std::unordered_map<std::string, std::unique_ptr<GameObjectInterface>> objects;
    
    // 按类型分组的对象ID列表，用于快速查询
    std::unordered_map<std::string, std::vector<std::string>> typeGroups;
    
    // 待删除的对象ID列表
    std::vector<std::string> objectsToRemove;
    
    // 事件回调函数
    std::vector<std::function<void(GameObjectInterface*)>> onObjectAddedCallbacks;
    std::vector<std::function<void(const std::string&, const std::string&)>> onObjectRemovedCallbacks;
    
    // 管理器是否处于更新中的标志
    bool isUpdating = false;
    
public:
    GameObjectManager() = default;
    ~GameObjectManager() = default;

    // === 对象管理 ===
    
    /**
     * 添加游戏对象
     * @param obj 要添加的游戏对象
     * @return 是否添加成功
     */
    bool addObject(std::unique_ptr<GameObjectInterface> obj);
    
    /**
     * 创建并添加游戏对象
     * @param id 对象ID
     * @param obj 游戏对象
     * @return 是否添加成功
     */
    template<typename T>
    bool createObject(const std::string& id, std::unique_ptr<T> obj) {
        static_assert(std::is_base_of_v<GameObjectInterface, T>, 
                      "T must inherit from GameObjectInterface");
        return addObject(std::unique_ptr<GameObjectInterface>(obj.release()));
    }
    
    /**
     * 获取游戏对象
     * @param id 对象ID
     * @return 对象指针，未找到则返回nullptr
     */
    GameObjectInterface* getObject(const std::string& id) const;
    
    /**
     * 获取指定类型的所有对象
     * @param type 对象类型
     * @return 该类型的所有对象
     */
    std::vector<GameObjectInterface*> getObjectsByType(const std::string& type) const;
    
    /**
     * 移除游戏对象
     * @param id 要移除的对象ID
     */
    void removeObject(const std::string& id);
    
    /**
     * 立即移除对象（在更新循环外调用）
     */
    void removeObjectImmediate(const std::string& id);
    
    /**
     * 清空所有对象
     */
    void clear();
    
    /**
     * 获取对象数量
     */
    size_t getObjectCount() const { return objects.size(); }
    
    /**
     * 检查对象是否存在
     */
    bool hasObject(const std::string& id) const;

    // === 更新和渲染 ===
    
    /**
     * 更新所有激活的对象
     * @param deltaTime 时间间隔
     */
    void updateAll(float deltaTime);
    
    /**
     * 将所有对象添加到场景中进行渲染
     * @param scene 目标场景
     */
    void addToScene(cocos2d::Scene* scene);
    
    /**
     * 从场景中移除所有对象
     * @param scene 目标场景  
     */
    void removeFromScene(cocos2d::Scene* scene);

    // === 查询功能 ===
    
    /**
     * 根据位置范围查询对象
     * @param center 中心位置
     * @param radius 查询半径
     * @param filterType 可选的类型过滤器
     * @return 范围内的对象列表
     */
    std::vector<GameObjectInterface*> getObjectsInRange(
        const cocos2d::Vec2& center, 
        float radius,
        const std::string& filterType = "") const;
    
    /**
     * 根据矩形区域查询对象
     * @param area 查询区域
     * @param filterType 可选的类型过滤器
     * @return 区域内的对象列表
     */
    std::vector<GameObjectInterface*> getObjectsInArea(
        const cocos2d::Rect& area,
        const std::string& filterType = "") const;
    
    /**
     * 查询可交互的对象
     * @param position 查询位置
     * @param radius 查询半径
     * @return 可交互的对象列表
     */
    std::vector<GameObjectInterface*> getInteractableObjects(
        const cocos2d::Vec2& position, 
        float radius = 50.0f) const;
    
    /**
     * 获取最近的对象
     * @param position 参考位置
     * @param filterType 可选的类型过滤器
     * @return 最近的对象，未找到返回nullptr
     */
    GameObjectInterface* getNearestObject(
        const cocos2d::Vec2& position,
        const std::string& filterType = "") const;

    // === 碰撞检测 ===
    
    /**
     * 检测所有对象之间的碰撞
     * @return 碰撞对象对的列表
     */
    std::vector<std::pair<GameObjectInterface*, GameObjectInterface*>> checkAllCollisions() const;
    
    /**
     * 检测特定对象与其他对象的碰撞
     * @param objectId 要检测的对象ID
     * @return 与该对象碰撞的其他对象列表
     */
    std::vector<GameObjectInterface*> checkCollisions(const std::string& objectId) const;
    
    /**
     * 检测两个对象是否碰撞
     * @param obj1 对象1
     * @param obj2 对象2
     * @return 是否碰撞
     */
    static bool isColliding(GameObjectInterface* obj1, GameObjectInterface* obj2);

    // === 事件系统 ===
    
    /**
     * 注册对象添加事件回调
     */
    void onObjectAdded(std::function<void(GameObjectInterface*)> callback);
    
    /**
     * 注册对象移除事件回调
     */
    void onObjectRemoved(std::function<void(const std::string&, const std::string&)> callback);
    
    /**
     * 广播日期变化事件
     */
    void broadcastDayPass();
    
    /**
     * 广播季节变化事件
     */
    void broadcastSeasonChange(const std::string& newSeason);

    // === 序列化支持 ===
    
    /**
     * 序列化所有对象数据
     * @return 序列化后的JSON字符串
     */
    std::string serializeAll() const;
    
    /**
     * 从序列化数据恢复对象
     * @param data 序列化数据
     * @return 是否成功
     */
    bool deserializeAll(const std::string& data);

    // === 调试和统计 ===
    
    /**
     * 获取对象统计信息
     * @return 各类型对象的数量统计
     */
    std::unordered_map<std::string, int> getObjectStats() const;
    
    /**
     * 打印调试信息
     */
    void printDebugInfo() const;
    
    /**
     * 验证管理器内部数据的一致性
     * @return 是否一致
     */
    bool validateIntegrity() const;

private:
    /**
     * 处理待删除的对象
     */
    void processPendingRemovals();
    
    /**
     * 从类型组中移除对象
     */
    void removeFromTypeGroup(const std::string& type, const std::string& id);
    
    /**
     * 添加到类型组
     */
    void addToTypeGroup(const std::string& type, const std::string& id);
    
    /**
     * 触发对象添加事件
     */
    void triggerObjectAddedEvent(GameObjectInterface* obj);
    
    /**
     * 触发对象移除事件
     */
    void triggerObjectRemovedEvent(const std::string& id, const std::string& type);
};
