#pragma once
#include "PlayerAdapter.h"
#include "NPCAdapter.h"
#include "CropAdapter.h"
#include "LivestockAdapter.h"
#include "TreeAdapter.h"
#include "OreAdapter.h"
#include "../GameObjectInterface.h"
#include <memory>
#include <string>

/**
 * 适配器工厂类
 * 负责创建各种类型的游戏对象适配器
 */
class AdapterFactory {
public:
    /**
     * 创建Player适配器
     * @param player 玩家对象指针
     * @param id 对象ID
     * @return Player适配器
     */
    static std::unique_ptr<GameObjectInterface> createPlayerAdapter(
        Player* player, const std::string& id);
    
    /**
     * 创建NPC适配器
     * @param npc NPC对象指针
     * @param id 对象ID
     * @return NPC适配器
     */
    static std::unique_ptr<GameObjectInterface> createNPCAdapter(
        NPC* npc, const std::string& id);
    
    /**
     * 创建Crop适配器
     * @param crop 作物对象指针
     * @param id 对象ID
     * @param position 作物位置
     * @return Crop适配器
     */
    static std::unique_ptr<GameObjectInterface> createCropAdapter(
        std::shared_ptr<Crop> crop, const std::string& id, const cocos2d::Vec2& position);
    
    /**
     * 创建Livestock适配器
     * @param livestock 家畜对象指针
     * @param id 对象ID
     * @return Livestock适配器
     */
    static std::unique_ptr<GameObjectInterface> createLivestockAdapter(
        Livestock* livestock, const std::string& id);
    
    /**
     * 创建Tree适配器
     * @param tree 树木对象指针
     * @param id 对象ID
     * @return Tree适配器
     */
    static std::unique_ptr<GameObjectInterface> createTreeAdapter(
        std::shared_ptr<Tree> tree, const std::string& id);
    
    /**
     * 创建Ore适配器
     * @param ore 矿石对象指针
     * @param id 对象ID
     * @return Ore适配器
     */
    static std::unique_ptr<GameObjectInterface> createOreAdapter(
        std::shared_ptr<Ore> ore, const std::string& id);
    
    /**
     * 根据类型和参数创建适配器
     * @param type 对象类型
     * @param params 创建参数（类型相关）
     * @return 适配器对象
     */
    static std::unique_ptr<GameObjectInterface> createAdapter(
        const std::string& type, void* params);
    
    /**
     * 生成唯一ID
     * @param prefix ID前缀
     * @return 唯一ID
     */
    static std::string generateId(const std::string& prefix);

private:
    static int idCounter;
};
