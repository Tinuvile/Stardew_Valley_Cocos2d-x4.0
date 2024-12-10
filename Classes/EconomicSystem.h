#ifndef ECONOMIC_SYSTEM_H  
#define ECONOMIC_SYSTEM_H  

#include <string>  
#include "Item.h"
#include "Inventory.h"

using namespace std;

class EconomicSystem {
public:
    // ���캯������������  
    EconomicSystem ( Inventory* mybag , Inventory* goods );
    ~EconomicSystem ();

    // ���ӽ�ҵĺ���  
    void addGold ( int amount );

    // ���ٽ�ҵĺ���  
    void subtractGold ( int amount );

    // ��ȡӵ�н�������ĺ���  
    int getGoldAmount () const;

    // ������  
    void buyItem ( const string& itemName );

    // ���ۺ���  
    void sellItem ( const string& itemName , int count = 1 );

private:
    // ����������  
    int goldAmount; 

    Inventory* _mybag; // ָ���Լ�����ʵ����ָ��  

    Inventory* _goods; // ָ����Ʒʵ����ָ��  
};

#endif  // ECONOMIC_SYSTEM_H