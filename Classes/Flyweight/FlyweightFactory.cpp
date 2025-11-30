// FlyweightFactory.cpp - 享元工厂实现
#include "FlyweightFactory.h"
#include "CropFlyweight.h"
#include "TreeFlyweight.h"
#include "OreFlyweight.h"
#include "cocos2d.h"

USING_NS_CC;

// 初始化静态成员
FlyweightFactory* FlyweightFactory::s_instance = nullptr;

FlyweightFactory::FlyweightFactory() {
    CCLOG("FlyweightFactory: Initializing...");
}

FlyweightFactory::~FlyweightFactory() {
    cleanup();
    CCLOG("FlyweightFactory: Destroyed");
}

FlyweightFactory* FlyweightFactory::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new FlyweightFactory();
    }
    return s_instance;
}

void FlyweightFactory::destroyInstance() {
    if (s_instance != nullptr) {
        delete s_instance;
        s_instance = nullptr;
    }
}

// ==================== 获取享元对象 ====================

CropFlyweight* FlyweightFactory::getCropFlyweight(const std::string& cropType) {
    auto it = m_cropFlyweights.find(cropType);
    if (it != m_cropFlyweights.end()) {
        return it->second.get();
    }
    CCLOG("FlyweightFactory: Crop type '%s' not found", cropType.c_str());
    return nullptr;
}

TreeFlyweight* FlyweightFactory::getTreeFlyweight(const std::string& treeType) {
    auto it = m_treeFlyweights.find(treeType);
    if (it != m_treeFlyweights.end()) {
        return it->second.get();
    }
    CCLOG("FlyweightFactory: Tree type '%s' not found", treeType.c_str());
    return nullptr;
}

OreFlyweight* FlyweightFactory::getOreFlyweight(const std::string& oreType) {
    auto it = m_oreFlyweights.find(oreType);
    if (it != m_oreFlyweights.end()) {
        return it->second.get();
    }
    CCLOG("FlyweightFactory: Ore type '%s' not found", oreType.c_str());
    return nullptr;
}


// ==================== 预加载资源 ====================

void FlyweightFactory::preloadCropTypes() {
    CCLOG("FlyweightFactory: Preloading crop types...");

    // 预加载所有作物类型
    // 根据AppDelegate.cpp中的cropbasicinformation初始化

    // Wheat (小麦) - 夏季作物
    m_cropFlyweights["Wheat"] = std::make_unique<CropFlyweight>(
        "Wheat",
        "crop/wheat1.png",    // 种子阶段
        "crop/wheat2.png",    // 生长阶段
        "crop/wheat4.png",    // 成熟阶段
        "Summer",
        7                     // 成熟所需天数
    );

    // Corn (玉米) - 夏季作物
    m_cropFlyweights["Corn"] = std::make_unique<CropFlyweight>(
        "Corn",
        "crop/corn1.png",
        "crop/corn2.png",
        "crop/corn4.png",
        "Summer",
        14
    );

    // Potato (土豆) - 春季作物
    m_cropFlyweights["Potato"] = std::make_unique<CropFlyweight>(
        "Potato",
        "crop/Potato1.png",
        "crop/Potato2.png",
        "crop/Potato4.png",
        "Spring",
        6
    );

    // Pumpkin (南瓜) - 秋季作物
    m_cropFlyweights["Pumpkin"] = std::make_unique<CropFlyweight>(
        "Pumpkin",
        "crop/Pumpkin1.png",
        "crop/Pumpkin2.png",
        "crop/Pumpkin4.png",
        "Autumn",
        13
    );

    // Blueberry (蓝莓) - 夏季作物
    m_cropFlyweights["Blueberry"] = std::make_unique<CropFlyweight>(
        "Blueberry",
        "crop/blueberry1.png",
        "crop/blueberry2.png",
        "crop/blueberry4.png",
        "Summer",
        13
    );

    CCLOG("FlyweightFactory: Loaded %d crop types", (int)m_cropFlyweights.size());
}

void FlyweightFactory::preloadTreeTypes() {
    CCLOG("FlyweightFactory: Preloading tree types...");

    // 预加载树木类型
    // 根据AppDelegate.cpp中的Tree初始化信息

    // Tree (树木) - 通用树木类型
    m_treeFlyweights["tree"] = std::make_unique<TreeFlyweight>(
        "tree",
        "Tree/tree1.png",    // 初始纹理
        "Tree/tree2.png",    // 砍伐后纹理
        "Tree/tree3.png",    // 黄色初始纹理
        15,                  // 价值
        5,                   // 恢复时间
        2                    // 砍伐次数
    );

    CCLOG("FlyweightFactory: Loaded %d tree types", (int)m_treeFlyweights.size());
}

void FlyweightFactory::preloadOreTypes() {
    CCLOG("FlyweightFactory: Preloading ore types...");

    // 预加载矿石类型
    // 根据AppDelegate.cpp中的Ore初始化信息

    // Ruby (红宝石)
    m_oreFlyweights["Ruby"] = std::make_unique<OreFlyweight>(
        "Ruby",
        "Ore/Ruby1.png",     // 初始纹理
        "Ore/Ruby2.png",     // 开采后纹理
        3,                   // 价值
        3                    // 恢复时间
    );

    // Amethyst (紫宝石)
    m_oreFlyweights["Amethyst"] = std::make_unique<OreFlyweight>(
        "Amethyst",
        "Ore/Amethyst1.png",
        "Ore/Amethyst2.png",
        5,
        5
    );

    // Emerald (绿宝石)
    m_oreFlyweights["Emerald"] = std::make_unique<OreFlyweight>(
        "Emerald",
        "Ore/Emerald1.png",
        "Ore/Emerald2.png",
        5,
        5
    );

    CCLOG("FlyweightFactory: Loaded %d ore types", (int)m_oreFlyweights.size());
}

void FlyweightFactory::preloadAll() {
    CCLOG("FlyweightFactory: Preloading all resources...");
    preloadCropTypes();
    preloadTreeTypes();
    preloadOreTypes();
    printStatistics();
}

// ==================== 资源管理 ====================

void FlyweightFactory::cleanup() {
    CCLOG("FlyweightFactory: Cleaning up resources...");
    m_cropFlyweights.clear();
    m_treeFlyweights.clear();
    m_oreFlyweights.clear();
    CCLOG("FlyweightFactory: Cleanup complete");
}

void FlyweightFactory::printStatistics() const {
    CCLOG("========== Flyweight Factory Statistics ==========");
    CCLOG("Crop flyweights: %d", (int)m_cropFlyweights.size());
    CCLOG("Tree flyweights: %d", (int)m_treeFlyweights.size());
    CCLOG("Ore flyweights: %d", (int)m_oreFlyweights.size());
    CCLOG("Total flyweights: %d",
        (int)(m_cropFlyweights.size() + m_treeFlyweights.size() +
              m_oreFlyweights.size()));
    CCLOG("==================================================");
}
