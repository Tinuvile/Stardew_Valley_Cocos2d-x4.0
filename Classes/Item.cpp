#include "Item.h"

Item::Item ( const std::string& name , const std::string& icon_path , const int value , const int& num_limit )
    :name ( name ) , initial_pic ( icon_path ) , max_count_in_one_grid ( num_limit ) , value ( value ) , usable ( false ) {
}

Item::Item ( const Item& other )
    : name ( other.name ) , initial_pic ( other.initial_pic ) , max_count_in_one_grid ( other.max_count_in_one_grid ) , value ( other.value )
    , usable ( false ) {
}



std::shared_ptr<Item> Item::GetCopy () const {
    auto copy = std::make_shared<Item> ( *this );  // ʹ��Item�ĸ��ƹ��캯��
    return copy;
}

void Item::Use () {
    // ��Ʒ��ʹ���߼�������ʵ����Ҫʵ�֣�
}