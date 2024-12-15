#include "TestItem.h"  

// 构造函数  
TestItem::TestItem () {
    // 初始化物品及其价格
    // 示例 
    itemPrices["Sword"] = 50;   // 剑的价格
}

// 获取物品的价格  
int TestItem::getPrice ( const string& itemName ) const {
    auto it = itemPrices.find ( itemName );
    if (it != itemPrices.end ()) {
        return it->second;
    }
    throw invalid_argument ( "Item not found." );
}