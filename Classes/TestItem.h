#pragma once

#include <unordered_map>  
#include <string>  
#include <stdexcept>  

using namespace std;

class TestItem {
public:
    // 构造函数  
    TestItem ();

    // 获取物品的价格  
    int getPrice ( const string& itemName ) const;

private:
    // 物品价格表  
    unordered_map<string , int> itemPrices;
};

#endif // ITEM_H
