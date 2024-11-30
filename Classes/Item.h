#ifndef ITEM_H  
#define ITEM_H  

#include <unordered_map>  
#include <string>  
#include <stdexcept>  

using namespace std;

class Item {
public:
    // 构造函数  
    Item ();

    // 获取物品的价格  
    int getPrice ( const string& itemName ) const;

private:
    // 物品价格表  
    unordered_map<string , int> itemPrices;
};

#endif // ITEM_H
