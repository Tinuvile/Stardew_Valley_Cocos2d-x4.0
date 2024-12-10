#ifndef ECONOMIC_SYSTEM_H  
#define ECONOMIC_SYSTEM_H  

#include <string>  
#include "Item.h"
#include "Inventory.h"

using namespace std;

class EconomicSystem {
public:
    // 构造函数和析构函数  
    EconomicSystem ( Inventory* mybag , Inventory* goods );
    ~EconomicSystem ();

    // 增加金币的函数  
    void addGold ( int amount );

    // 减少金币的函数  
    void subtractGold ( int amount );

    // 读取拥有金币数量的函数  
    int getGoldAmount () const;

    // 购买函数  
    void buyItem ( const string& itemName );

    // 出售函数  
    void sellItem ( const string& itemName , int count = 1 );

private:
    // 保存金币数量  
    int goldAmount; 

    Inventory* _mybag; // 指向自己背包实例的指针  

    Inventory* _goods; // 指向商品实例的指针  
};

#endif  // ECONOMIC_SYSTEM_H