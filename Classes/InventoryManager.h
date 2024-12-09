#ifndef INVENTORY_MANAGER_H  
#define INVENTORY_MANAGER_H  

#include "Inventory.h"  
#include "Item.h"  
#include "cocos2d.h"  

class InventoryManager {
public:
    InventoryManager ();
    ~InventoryManager ();

    bool initInventory ();
    void addItemsToInventory ();

private:
    Inventory* inventory;
};

#endif // INVENTORY_MANAGER_H