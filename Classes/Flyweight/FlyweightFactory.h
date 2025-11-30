// FlyweightFactory.h - 享元工厂（单例模式）
// 管理所有享元对象的创建和复用
#ifndef __FLYWEIGHT_FACTORY_H__
#define __FLYWEIGHT_FACTORY_H__

#include <map>
#include <memory>
#include <string>

// 前向声明
class CropFlyweight;
class TreeFlyweight;
class OreFlyweight;

/**
 * @class FlyweightFactory
 * @brief 享元工厂（单例）
 *
 * 负责创建和管理所有享元对象
 * 确保相同类型的对象只创建一次，实现对象共享
 */
class FlyweightFactory {
public:
    /**
     * @brief 获取工厂单例实例
     * @return 工厂实例指针
     */
    static FlyweightFactory* getInstance();

    /**
     * @brief 销毁工厂单例
     */
    static void destroyInstance();

    // ==================== 获取享元对象 ====================

    /**
     * @brief 获取农作物享元对象
     * @param cropType 作物类型（如"Parsnip", "Cauliflower"等）
     * @return 作物享元对象指针，如果类型不存在返回nullptr
     */
    CropFlyweight* getCropFlyweight(const std::string& cropType);

    /**
     * @brief 获取树木享元对象
     * @param treeType 树木类型（如"Oak", "Maple"等）
     * @return 树木享元对象指针，如果类型不存在返回nullptr
     */
    TreeFlyweight* getTreeFlyweight(const std::string& treeType);

    /**
     * @brief 获取矿石享元对象
     * @param oreType 矿石类型（如"Ruby", "Emerald"等）
     * @return 矿石享元对象指针，如果类型不存在返回nullptr
     */
    OreFlyweight* getOreFlyweight(const std::string& oreType);

    // ==================== 预加载资源 ====================

    /**
     * @brief 预加载所有作物类型
     * 在游戏启动时调用，创建所有作物的享元对象
     */
    void preloadCropTypes();

    /**
     * @brief 预加载所有树木类型
     */
    void preloadTreeTypes();

    /**
     * @brief 预加载所有矿石类型
     */
    void preloadOreTypes();

    /**
     * @brief 预加载所有资源
     * 调用上述所有preload方法
     */
    void preloadAll();

    // ==================== 资源管理 ====================

    /**
     * @brief 清理所有享元对象
     * 释放所有已创建的享元对象内存
     */
    void cleanup();

    /**
     * @brief 获取统计信息
     * @return 返回各类型享元对象的数量
     */
    void printStatistics() const;

private:
    // 私有构造函数（单例模式）
    FlyweightFactory();
    ~FlyweightFactory();

    // 禁止拷贝和赋值
    FlyweightFactory(const FlyweightFactory&) = delete;
    FlyweightFactory& operator=(const FlyweightFactory&) = delete;

private:
    // 单例实例
    static FlyweightFactory* s_instance;

    // 享元对象容器（使用unique_ptr自动管理内存）
    std::map<std::string, std::unique_ptr<CropFlyweight>> m_cropFlyweights;
    std::map<std::string, std::unique_ptr<TreeFlyweight>> m_treeFlyweights;
    std::map<std::string, std::unique_ptr<OreFlyweight>> m_oreFlyweights;
};

#endif // __FLYWEIGHT_FACTORY_H__
