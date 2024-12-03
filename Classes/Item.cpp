#include"Item.h"

Item::Item ( const std::string& name , const std::string& icon_path , const int value , const int& num_limit )
    :name ( name ) , max_count_in_one_grid ( num_limit ) , value ( value ) , usable ( false ) {
    icon = cocos2d::Sprite::create ( icon_path );
    if (icon == nullptr) {
        CCLOG ( "fail to create Sprite with file path:%s" , icon_path );
    }
    icon->autorelease ();
}

Item::Item ( const Item& other )
    : name ( other.name ) , max_count_in_one_grid ( other.max_count_in_one_grid ) , value ( other.value )
    , usable ( false ) {
    icon = cocos2d::Sprite::createWithTexture ( other.GetIcon ()->getTexture () );
    if (icon == nullptr) {
        CCLOG ( "fail to create Sprite with other's Texture" );
    }
    icon->autorelease ();
}

void Item::SetIcon ( const std::string& file_source ) {
    icon->setTexture ( file_source );
}

std::shared_ptr<Item> Item::GetCopy () const {
    auto copy = std::make_shared<Item> ( *this );
    return copy;
}

void Item::Use () {}