#ifndef ECONOMIC_SYSTEM_H  
#define ECONOMIC_SYSTEM_H  

#include <string>  
#include "TestItem.h"  // ���� TestItem.h �Ի�ȡ item �ļ۸�  

using namespace std;

class EconomicSystem {
public:
    // ���캯������������  
    EconomicSystem ();
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
    void sellItem ( const string& itemName );

private:
    // ����������  
    int goldAmount;
    TestItem itemManager;  // ���� Item ����  
};

#endif  // ECONOMIC_SYSTEM_H