#pragma once

#include <unordered_map>  
#include <string>  
#include <stdexcept>  

using namespace std;

class TestItem {
public:
    // ���캯��  
    TestItem ();

    // ��ȡ��Ʒ�ļ۸�  
    int getPrice ( const string& itemName ) const;

private:
    // ��Ʒ�۸��  
    unordered_map<string , int> itemPrices;
};

#endif // ITEM_H
