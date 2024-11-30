#include "EconomicSystem.h"  

// ���캯��  
EconomicSystem::EconomicSystem () : goldAmount ( 0 ) {
    // ���ٳ�ʼ����Ʒ��ʹ�� Item ����������Ʒ  
}

// ��������  
EconomicSystem::~EconomicSystem () {
    // �˴�û����Դ��Ҫ����  
}

// ���ӽ�ҵĺ���  
void EconomicSystem::addGold ( int amount ) {
    if (amount < 0) {
        throw invalid_argument ( "Amount must be non-negative." );
    }
    goldAmount += amount;
}

// ���ٽ�ҵĺ���  
void EconomicSystem::subtractGold ( int amount ) {
    if (amount < 0) {
        throw invalid_argument ( "Amount must be non-negative." );
    }
    if (goldAmount < amount) {
        throw runtime_error ( "Not enough gold." );
    }
    goldAmount -= amount;
}

// ��ȡӵ�н�������ĺ���  
int EconomicSystem::getGoldAmount () const {
    return goldAmount;
}

// ������  
void EconomicSystem::buyItem ( const string& itemName ) {
    int price = itemManager.getPrice ( itemName ); // ʹ�� Item ���ȡ�۸�  
    subtractGold ( price );
}

// ���ۺ���  
void EconomicSystem::sellItem ( const string& itemName ) {
    int price = itemManager.getPrice ( itemName ); // ʹ�� Item ���ȡ�۸�  
    addGold ( price ); // �������ʱ��Ʒ�۸���ڹ���ʱ�۸�  
}