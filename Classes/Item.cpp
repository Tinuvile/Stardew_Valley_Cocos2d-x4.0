#include"Item.h"

Item::Item ( const std::string& name , const std::string& icon_path , const int value = 1 , const int& num_limit = 99 )
    :name ( name ) , max_count_in_one_grid ( num_limit ) , value ( value ) , usable ( false ) {
    icon = cocos2d::Sprite::create ( icon_path );
    if (icon == nullptr) {
        CCLOG ( "fail to create Sprite with file path:%s" , icon_path );
    }
    icon->autorelease ();
}
