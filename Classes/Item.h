#ifndef ITEM_H  
#define ITEM_H  

#include <unordered_map>  
#include <string>  
#include <stdexcept>  

using namespace std;

class Item {
public:
    // ���캯��  
    Item ();

    // ��ȡ��Ʒ�ļ۸�  
    int getPrice ( const string& itemName ) const;

private:
    // ��Ʒ�۸��  
    unordered_map<string , int> itemPrices;
};

#endif // ITEM_H
