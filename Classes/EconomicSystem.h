#ifndef ECONOMIC_SYSTEM_H  
#define ECONOMIC_SYSTEM_H  

#include <string>  
#include "TestItem.h"  // 包含 TestItem.h 以获取 item 的价格  

using namespace std;

class EconomicSystem {
public:
    // 构造函数和析构函数  
    EconomicSystem ();
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
    void sellItem ( const string& itemName );

private:
    // 保存金币数量  
    int goldAmount;
    TestItem itemManager;  // 创建 Item 对象  
};

#endif  // ECONOMIC_SYSTEM_H