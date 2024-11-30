#include "Item.h"  

// ���캯��  
Item::Item () {
    // ��ʼ����Ʒ����۸�
    // ʾ�� 
    itemPrices["Sword"] = 50;   // ���ļ۸�
}

// ��ȡ��Ʒ�ļ۸�  
int Item::getPrice ( const string& itemName ) const {
    auto it = itemPrices.find ( itemName );
    if (it != itemPrices.end ()) {
        return it->second;
    }
    throw invalid_argument ( "Item not found." );
}