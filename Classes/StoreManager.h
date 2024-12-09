#ifndef STORE_MANAGER_H  
#define STORE_MANAGER_H  

#include "Inventory.h"  
#include "Item.h"  
#include "cocos2d.h"  
#include "tuple"

class StoreManager {
public:
    StoreManager ();
    ~StoreManager ();

    bool initStore ();
    void StoreManager::addItemToStore ( Item& item , int index );
    void addItemsToStore ();

private:
    Inventory* storeInventory;
};

#endif // STORE_MANAGER_H