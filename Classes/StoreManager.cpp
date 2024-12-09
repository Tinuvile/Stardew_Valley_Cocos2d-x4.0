#include "StoreManager.h"  
#include "cocos2d.h"  

USING_NS_CC;

StoreManager::StoreManager ()
    : storeInventory ( std::make_unique<Inventory> () ) { // 在构造列表中使用 std::make_unique  
}

StoreManager::~StoreManager () {
    // 不需要显示 delete，unique_ptr 会自动释放资源  
}

bool StoreManager::initStore () {
    addItemsToStore ();
    return true; // 可以根据需要返回其他状态信息  
}

void StoreManager::addItemToStore ( Item item , int index ) {
    bool addedSuccessfully = storeInventory->AddItem ( item );
    if (addedSuccessfully) {
        storeInventory->SetSelectedItem ( index );
        CCLOG ( "Item '%s' added successfully." , item.GetName ().c_str () );
    }
    else {
        CCLOG ( "Failed to add item '%s'. Inventory might be full." , item.GetName ().c_str () );
    }
}

void StoreManager::addItemsToStore () {
    // 定义物品名称和路径的数组  
    // 售卖动物列表
    std::vector<std::pair<std::string , std::string>> animalItems = {
        {"Golden_Chicken", "Item/Surpermarket/Animal/Golden_Chicken.png"},
        {"Duck", "Item/Surpermarket/Animal/Duck.png"},
        {"Goat", "Item/Surpermarket/Animal/Goat.png"},
        {"Pig", "Item/Surpermarket/Animal/Pig.png"},
        {"Rabbit", "Item/Surpermarket/Animal/Rabbit.png"},
        {"Sheep", "Item/Surpermarket/Animal/Sheep.png"},
        {"White_Chicken", "Item/Surpermarket/Animal/White_Chicken.png"}
    };

    for (size_t i = 0; i < animalItems.size (); ++i) {
        Item item ( animalItems[i].first , animalItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + 1) );
    }

    // 春季种子物品列表  
    std::vector<std::pair<std::string , std::string>> springItems = {
        {"Bean_Starter", "Item/Surpermarket/Spring/Bean_Starter.png"},
        {"Carrot_Seeds", "Item/Surpermarket/Spring/Carrot_Seeds.png"},
        {"Cauliflower_Seeds", "Item/Surpermarket/Spring/Cauliflower_Seeds.png"},
        {"Coffee_Bean", "Item/Surpermarket/Spring/Coffee_Bean.png"},
        {"Garlic_Seeds", "Item/Surpermarket/Spring/Garlic_Seeds.png"},
        {"Jazz_Seeds", "Item/Surpermarket/Spring/Jazz_Seeds.png"},
        {"Kale_Seeds", "Item/Surpermarket/Spring/Kale_Seeds.png"},
        {"Parsnip_Seeds", "Item/Surpermarket/Spring/Parsnip_Seeds.png"},
        {"Potato_Seeds", "Item/Surpermarket/Spring/Potato_Seeds.png"},
        {"Rhubarb_Seeds", "Item/Surpermarket/Spring/Rhubarb_Seeds.png"},
        {"Rice_Shoot", "Item/Surpermarket/Spring/Rice_Shoot.png"},
        {"Strawberry_Seeds", "Item/Surpermarket/Spring/Strawberry_Seeds.png"},
        {"Tulip_Bulb", "Item/Surpermarket/Spring/Tulip_Bulb.png"}
    };

    for (size_t i = 0; i < springItems.size (); ++i) {
        Item item ( springItems[i].first , springItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + animalItems.size () + 1) ); // 继续索引  
    }

    // 夏季种子物品列表
    std::vector<std::pair<std::string , std::string>> summerItems = {
        {"Amaranth_Seeds", "Item/Surpermarket/Summer/Amaranth_Seeds.png"},
        {"Artichoke_Seeds", "Item/Surpermarket/Summer/Artichoke_Seeds.png"},
        {"Beet_Seeds", "Item/Surpermarket/Summer/Beet_Seeds.png"},
        {"Blueberry_Seeds", "Item/Surpermarket/Summer/Blueberry_Seeds.png"},
        {"Bok_Choy_Seeds", "Item/Surpermarket/Summer/Bok_Choy_Seeds.png"},
        {"Broccoli_Seeds", "Item/Surpermarket/Summer/Broccoli_Seeds.png"},
        {"Corn_Seeds", "Item/Surpermarket/Summer/Corn_Seeds.png"},
        {"Cranberry_Seeds", "Item/Surpermarket/Summer/Cranberry_Seeds.png"},
        {"Eggplant_Seeds", "Item/Surpermarket/Summer/Eggplant_Seeds.png"},
        {"Fairy_Seeds", "Item/Surpermarket/Summer/Fairy_Seeds.png"},
        {"Grape_Starter", "Item/Surpermarket/Summer/Grape_Starter.png"},
        {"Hops_Starter", "Item/Surpermarket/Summer/Hops_Starter.png"},
        {"Melon_Seeds", "Item/Surpermarket/Summer/Melon_Seeds.png"},
        {"Pepper_Seeds", "Item/Surpermarket/Summer/Pepper_Seeds.png"},
        {"Poppy_Seeds", "Item/Surpermarket/Summer/Poppy_Seeds.png"},
        {"Pumpkin_Seeds", "Item/Surpermarket/Summer/Pumpkin_Seeds.png"},
        {"Radish_Seeds", "Item/Surpermarket/Summer/Radish_Seeds.png"},
        {"Red_Cabbage_Seeds", "Item/Surpermarket/Summer/Red_Cabbage_Seeds.png"},
        {"Spangle_Seeds", "Item/Surpermarket/Summer/Spangle_Seeds.png"},
        {"Starfruit_Seeds", "Item/Surpermarket/Summer/Starfruit_Seeds.png"},
        {"Summer_Squash_Seeds", "Item/Surpermarket/Summer/Summer_Squash_Seeds.png"},
        {"Sunflower_Seeds", "Item/Surpermarket/Summer/Sunflower_Seeds.png"},
        {"Tomato_Seeds", "Item/Surpermarket/Summer/Tomato_Seeds.png"},
        {"Wheat_Seeds", "Item/Surpermarket/Summer/Wheat_Seeds.png"},
        {"Yam_Seeds", "Item/Surpermarket/Summer/Yam_Seeds.png"}
    };

    for (size_t i = 0; i < summerItems.size (); ++i) {
        Item item ( summerItems[i].first , summerItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + animalItems.size () + springItems.size () + 1) ); // 继续索引  
    }

    // 冬季种子物品列表
    std::vector<std::pair<std::string , std::string>> winterItems = {
        {"Powdermelon_Seeds", "Item/Surpermarket/Summer/Powdermelon_Seeds.png"}
    };

    for (size_t i = 0; i < winterItems.size (); ++i) {
        Item item ( winterItems[i].first , winterItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + animalItems.size () + springItems.size () + summerItems.size () + 1) ); // 继续索引  
    }

    // 工具列表
    std::vector<std::pair<std::string , std::string>> toolItems = {
        {"36_Backpack", "Item/Surpermarket/Tools/36_Backpack.png"},
        {"Backpack", "Item/Surpermarket/Tools/Backpack.png"},
        {"Advanced_Iridium_Rod", "Item/Surpermarket/Tools/Advanced_Iridium_Rod.png"},
        {"Axe", "Item/Surpermarket/Tools/Axe.png"},
        {"Bamboo_Pole", "Item/Surpermarket/Tools/Bamboo_Pole.png"},
        {"Copper_Axe", "Item/Surpermarket/Tools/Copper_Axe.png"},
        {"Copper_Hoe", "Item/Surpermarket/Tools/Copper_Hoe.png"},
        {"Copper_Pan", "Item/Surpermarket/Tools/Copper_Pan.png"},
        {"Copper_Pickaxe", "Item/Surpermarket/Tools/Copper_Pickaxe.png"},
        {"Copper_Watering", "Item/Surpermarket/Tools/Copper_Watering.png"},
        {"Fiberglass_Rod", "Item/Surpermarket/Tools/Fiberglass_Rod.png"},
        {"Gold_Axe", "Item/Surpermarket/Tools/Gold_Axe.png"},
        {"Gold_Hoe", "Item/Surpermarket/Tools/Gold_Hoe.png"},
        {"Gold_Pan", "Item/Surpermarket/Tools/Gold_Pan.png"},
        {"Gold_Pickaxe", "Item/Surpermarket/Tools/Gold_Pickaxe.png"},
        {"Gold_Watering_Can", "Item/Surpermarket/Tools/Gold_Watering_Can.png"},
        {"Golden_Scythe", "Item/Surpermarket/Tools/Golden_Scythe.png"},
        {"Hoe", "Item/Surpermarket/Tools/Hoe.png"},
        {"Pickaxe", "Item/Surpermarket/Tools/Pickaxe.png"},
        {"Milk_Pail", "Item/Surpermarket/Tools/Milk_Pail.png"},
        {"Scythe", "Item/Surpermarket/Tools/Scythe.png"},
        {"Steel_Axe", "Item/Surpermarket/Tools/Steel_Axe.png"},
        {"Steel_Hoe", "Item/Surpermarket/Tools/Steel_Hoe.png"},
        {"Steel_Pan", "Item/Surpermarket/Tools/Steel_Pan.png"},
        {"Steel_Pickaxe", "Item/Surpermarket/Tools/Steel_Pickaxe.png"},
        {"Steel_Watering", "Item/Surpermarket/Tools/Steel_Watering.png"},
        {"Trash_Can_Copper", "Item/Surpermarket/Tools/Trash_Can_Copper.png"},
        {"Watering_Can", "Item/Surpermarket/Tools/Watering_Can.png"},
        {"Trash_Can_Steel", "Item/Surpermarket/Tools/Trash_Can_Steel.png"}
    };

    for (size_t i = 0; i < toolItems.size (); ++i) {
        Item item ( toolItems[i].first , toolItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + animalItems.size () + springItems.size () 
            + summerItems.size () + winterItems.size () + 1) ); // 继续索引  
    }

    // 树苗列表
    std::vector<std::pair<std::string , std::string>> treeItems = {
        {"Apple_Sapling", "Item/Surpermarket/Tree/Apple_Sapling.png"},
        {"Apricot_Sapling", "Item/Surpermarket/Tree/Apricot_Sapling.png"},
        {"Banana_Sapling", "Item/Surpermarket/Tree/Banana_Sapling.png"},
        {"Cherry_Sapling", "Item/Surpermarket/Tree/Cherry_Sapling.png"},
        {"Mango_Sapling", "Item/Surpermarket/Tree/Mango_Sapling.png"},
        {"Orange_Sapling", "Item/Surpermarket/Tree/Orange_Sapling.png"},
        {"Peach_Sapling", "Item/Surpermarket/Tree/Peach_Sapling.png"},
        {"Pomegranate_Sapling", "Item/Surpermarket/Tree/Pomegranate_Sapling.png"}
    };

    for (size_t i = 0; i < treeItems.size (); ++i) {
        Item item ( treeItems[i].first , treeItems[i].second , 1 , 99 );
        addItemToStore ( item , static_cast<int>(i + animalItems.size () + springItems.size ()
            + summerItems.size () + winterItems.size () + toolItems.size () + 1) ); // 继续索引  
    }
}