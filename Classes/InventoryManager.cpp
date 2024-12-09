#include "InventoryManager.h"  
#include "cocos2d.h"  

USING_NS_CC;

InventoryManager::InventoryManager () {
    inventory = new Inventory ();
}

InventoryManager::~InventoryManager () {
    delete inventory; // ȷ���ͷ��ڴ�  
}

bool InventoryManager::initInventory () {
    addItemsToInventory ();
    return true; // ���Ը�����Ҫ����������Ϣ  
}

void InventoryManager::addItemsToInventory () {
    Item Grass ( "Grass" , "Item/Grass/grass-0.png" , 1 , 99 );
    Item Tools ( "Tools" , "Item/Tools/tools-16.png" , 1 , 99 );

    bool addedSuccessfully = inventory->AddItem ( Grass );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 1 );
        CCLOG ( "Item 'Grass' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Grass'. Inventory might be full." );
    }

    addedSuccessfully = inventory->AddItem ( Tools );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 2 );
        CCLOG ( "Item 'Tools' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Tools'. Inventory might be full." );
    }

    addedSuccessfully = inventory->AddItem ( Tools );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 2 );
        CCLOG ( "Item 'Tools' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Tools'. Inventory might be full." );
    }
}