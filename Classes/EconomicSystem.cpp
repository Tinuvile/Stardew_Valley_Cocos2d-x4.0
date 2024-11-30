#include "EconomicSystem.h"  

// 构造函数  
EconomicSystem::EconomicSystem () : goldAmount ( 0 ) {
    // 不再初始化物品，使用 Item 类来管理物品  
}

// 析构函数  
EconomicSystem::~EconomicSystem () {
    // 此处没有资源需要清理  
}

// 增加金币的函数  
void EconomicSystem::addGold ( int amount ) {
    if (amount < 0) {
        throw invalid_argument ( "Amount must be non-negative." );
    }
    goldAmount += amount;
}

// 减少金币的函数  
void EconomicSystem::subtractGold ( int amount ) {
    if (amount < 0) {
        throw invalid_argument ( "Amount must be non-negative." );
    }
    if (goldAmount < amount) {
        throw runtime_error ( "Not enough gold." );
    }
    goldAmount -= amount;
}

// 读取拥有金币数量的函数  
int EconomicSystem::getGoldAmount () const {
    return goldAmount;
}

// 购买函数  
void EconomicSystem::buyItem ( const string& itemName ) {
    int price = itemManager.getPrice ( itemName ); // 使用 Item 类获取价格  
    subtractGold ( price );
}

// 出售函数  
void EconomicSystem::sellItem ( const string& itemName ) {
    int price = itemManager.getPrice ( itemName ); // 使用 Item 类获取价格  
    addGold ( price ); // 假设出售时物品价格等于购买时价格  
}