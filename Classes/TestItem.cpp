#include "TestItem.h"  

// ���캯��  
TestItem::TestItem () {
    // ��ʼ����Ʒ����۸�
    // ʾ�� 
    itemPrices["Sword"] = 50;   // ���ļ۸�
}

// ��ȡ��Ʒ�ļ۸�  
int TestItem::getPrice ( const string& itemName ) const {
    auto it = itemPrices.find ( itemName );
    if (it != itemPrices.end ()) {
        return it->second;
    }
    throw invalid_argument ( "Item not found." );
}