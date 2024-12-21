#include"CookingPot.h"

CookingPot* CookingPot::create () {
    CookingPot* cooking_pot = new CookingPot ();
    if (cooking_pot && cooking_pot->init ()) {
        cooking_pot->autorelease ();  // 自动管理内存
        return cooking_pot;
    }
    CC_SAFE_DELETE ( cooking_pot );
    return nullptr;
}

bool CookingPot::init () {
    if (!Sprite::init ()) {
        CCLOG ( "failed to initialize Livestock." );
        return false;
    }

    // 设置大锅的图标
    if (!this->initWithFile ("farm/pot.png") ){
        CCLOG ( "fail to initialize Livestock with file :farm/pot.png" );
        return false;
    }

    //更改图标大小
    this->setScale ( 2.7f , 2.7f );

}

Dishes CookingPot::GetDishesId () const {
    if (pot.size () <= 0 || pot.size () > 2) {
        return Dishes::Wrong;
    }
    if (pot.size () == 1) {
        if (std::dynamic_pointer_cast<Fish>(pot[0]) != nullptr) {
            return Dishes::GrilledFish;
        }
        if (pot[0]->GetName () == "Egg") {
            return Dishes::FriedEgg;
        }
    }
    else {
        std::string ingredient_1 = pot[0]->GetName ();
        std::string ingredient_2 = pot[1]->GetName ();
        if ((ingredient_1 == "Milk" && ingredient_2 == "Egg") || (ingredient_1 == "Egg" && ingredient_2 == "Milk")) {
            return Dishes::Omelet;
        }
    }
    return Dishes::Wrong;
}

std::shared_ptr<Item> CookingPot::GetDishes ( Dishes dishes_id ) {
    if (dishes_id == Dishes::Wrong) {
        return nullptr;
    }
    switch (dishes_id) {
        case Dishes::FriedEgg:{
            auto fried_egg = Food::create ( FoodType::FriedEgg );
            return fried_egg;
        }
        case Dishes::GrilledFish: {
            auto grilled_fish = Food::create ( (FoodType::GrilledFish) );
            return grilled_fish;
        }
        case Dishes::Omelet: {
            auto omelet = Food::create ( FoodType::Omelet );
            return omelet;
        }
    }
    return nullptr;
}

void CookingPot::AddIngredient (const Item& ingredient ) {
    auto copy = ingredient.GetCopy ();
    pot.push_back ( copy );
}

std::shared_ptr<Item> CookingPot::GetPotBack () {
    auto temp = pot.back ();
    pot.pop_back ();
    return temp;
}

int CookingPot::GetPotSize () const {
    return pot.size();
}

void CookingPot::ClearPot () {
    pot.clear ();
}

void CookingPot::DisplayPotInCCLOG () const {
    for (auto it : pot) {
        CCLOG ( "%s" , it->GetName ().c_str () );
    }
}