#include "EconomicSystem.h"  
#include "cocos2d.h"  // 确保包含 cocos2d.h 来使用 CCLOG  
#include <iostream>  

// 构造函数初始化金币数量为0  
EconomicSystem::EconomicSystem ( Inventory* mybag , Inventory* goods )
    : goldAmount ( 0 ) , _mybag ( mybag ) , _goods ( goods ) {
    // 初始化代码可以在这里执行  
}

// 析构函数  
EconomicSystem::~EconomicSystem () {
    // 清理代码  
}

// 增加金币的函数  
void EconomicSystem::addGold ( int amount ) {
    if (amount > 0) {
        goldAmount += amount;
        CCLOG ( "Added %d gold. Total: %d gold." , amount , goldAmount );
    }
    else {
        CCLOG ( "Amount to add must be positive." );
    }
}

// 减少金币的函数  
void EconomicSystem::subtractGold ( int amount ) {
    if (amount > 0 && amount <= goldAmount) {
        goldAmount -= amount;
        CCLOG ( "Subtracted %d gold. Total: %d gold." , amount , goldAmount );
    }
    else {
        if (amount > goldAmount) {
            CCLOG ( "Not enough gold to subtract." );
        }
        else {
            CCLOG ( "Amount to subtract must be positive." );
        }
    }
}

// 读取拥有金币数量的函数  
int EconomicSystem::getGoldAmount () const {
    return goldAmount;
}

// 购买函数  
void EconomicSystem::buyItem ( const string& itemName ) {
    Item item = _goods->GetItemByName ( itemName );

    if (goldAmount >= item.GetValue ()) {
        subtractGold ( item.GetValue () );
        _mybag->AddItem ( item );
        CCLOG ( "Purchased item: %s" , itemName.c_str () );
    }
    else {
        CCLOG ( "Not enough gold to buy %s." , itemName.c_str () );
    }
}

// 出售函数  
void EconomicSystem::sellItem ( const string& itemName , int count) {
    Item item = _mybag->GetItemByName ( itemName ); // 从背包中获取物品  

    int itemValue = item.GetValue (); // 获取卖出价格  
    addGold ( itemValue * count );
    _mybag->RemoveItem ( item , count );
    CCLOG ( "Sold item: %s for %d gold." , itemName.c_str () , itemValue * count );
}