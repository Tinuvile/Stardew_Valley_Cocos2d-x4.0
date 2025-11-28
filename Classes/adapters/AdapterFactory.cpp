#include "AdapterFactory.h"
#include "cocos2d.h"
#include <sstream>

// 静态成员初始化
int AdapterFactory::idCounter = 1000;

std::unique_ptr<GameObjectInterface> AdapterFactory::createPlayerAdapter(
    Player* player, const std::string& id) {
    
    if (!player) {
        CCLOG("AdapterFactory::createPlayerAdapter - Null player pointer");
        return nullptr;
    }
    
    return std::make_unique<PlayerAdapter>(player, id);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createNPCAdapter(
    NPC* npc, const std::string& id) {
    
    if (!npc) {
        CCLOG("AdapterFactory::createNPCAdapter - Null NPC pointer");
        return nullptr;
    }
    
    return std::make_unique<NPCAdapter>(npc, id);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createCropAdapter(
    std::shared_ptr<Crop> crop, const std::string& id, const cocos2d::Vec2& position) {
    
    if (!crop) {
        CCLOG("AdapterFactory::createCropAdapter - Null crop pointer");
        return nullptr;
    }
    
    return std::make_unique<CropAdapter>(crop, id, position);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createLivestockAdapter(
    Livestock* livestock, const std::string& id) {
    
    if (!livestock) {
        CCLOG("AdapterFactory::createLivestockAdapter - Null livestock pointer");
        return nullptr;
    }
    
    return std::make_unique<LivestockAdapter>(livestock, id);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createTreeAdapter(
    std::shared_ptr<Tree> tree, const std::string& id) {
    
    if (!tree) {
        CCLOG("AdapterFactory::createTreeAdapter - Null tree pointer");
        return nullptr;
    }
    
    return std::make_unique<TreeAdapter>(tree, id);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createOreAdapter(
    std::shared_ptr<Ore> ore, const std::string& id) {
    
    if (!ore) {
        CCLOG("AdapterFactory::createOreAdapter - Null ore pointer");
        return nullptr;
    }
    
    return std::make_unique<OreAdapter>(ore, id);
}

std::unique_ptr<GameObjectInterface> AdapterFactory::createAdapter(
    const std::string& type, void* params) {
    
    // 这是一个通用的创建函数，需要根据具体需求来实现参数解析
    CCLOG("AdapterFactory::createAdapter - Creating adapter of type: %s", type.c_str());
    
    // 这里可以根据type和params来创建相应的适配器
    // 由于参数类型不同，这个函数可能需要更复杂的参数结构
    
    return nullptr; // 暂时返回nullptr，具体实现根据需求
}

std::string AdapterFactory::generateId(const std::string& prefix) {
    std::stringstream ss;
    ss << prefix << "_" << (idCounter++);
    return ss.str();
}
