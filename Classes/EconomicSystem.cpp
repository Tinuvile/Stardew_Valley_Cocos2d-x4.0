#include "EconomicSystem.h"  
#include "cocos2d.h"  // ȷ������ cocos2d.h ��ʹ�� CCLOG  
#include <iostream>  

// ���캯����ʼ���������Ϊ0  
EconomicSystem::EconomicSystem ( Inventory* mybag , Inventory* goods )
    : goldAmount ( 0 ) , _mybag ( mybag ) , _goods ( goods ) {
    // ��ʼ���������������ִ��  
}

// ��������  
EconomicSystem::~EconomicSystem () {
    // �������  
}

// ���ӽ�ҵĺ���  
void EconomicSystem::addGold ( int amount ) {
    if (amount > 0) {
        goldAmount += amount;
        CCLOG ( "Added %d gold. Total: %d gold." , amount , goldAmount );
    }
    else {
        CCLOG ( "Amount to add must be positive." );
    }
}

// ���ٽ�ҵĺ���  
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

// ��ȡӵ�н�������ĺ���  
int EconomicSystem::getGoldAmount () const {
    return goldAmount;
}

// ������  
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

// ���ۺ���  
void EconomicSystem::sellItem ( const string& itemName , int count) {
    Item item = _mybag->GetItemByName ( itemName ); // �ӱ����л�ȡ��Ʒ  

    int itemValue = item.GetValue (); // ��ȡ�����۸�  
    addGold ( itemValue * count );
    _mybag->RemoveItem ( item , count );
    CCLOG ( "Sold item: %s for %d gold." , itemName.c_str () , itemValue * count );
}