#include"Food.h"

Food::Food ( const std::string& name , const std::string& path1 , const int value , int energy , int num_limit )
	:Item ( name , path1 , value , num_limit ) , energy ( energy ) {
};

std::shared_ptr<Food> Food::create ( FoodType type ) {
	switch (type) {
		case FoodType::Milk: {
			auto milk = std::make_shared<Food> ( "Milk" , "Livestock/milk.png" , kMilkValue , kMilkEnergy );
			return milk;
		}
		case FoodType::Egg: {
			auto egg = std::make_shared<Food> ( "Egg" , "Livestock/egg.png" , kEggValue , kEggEnergy );
			return egg;
		}
		case FoodType::FriedEgg: {
			auto fried_egg = std::make_shared<Food> ( "FriedEgg" , "Food/fried_egg.png" , kEggValue * 3 , kEggEnergy * 2 );
			return fried_egg;
		}
		case FoodType::Omelet: {
			auto omelet = std::make_shared<Food> ( "Omelet" , "Food/omelet.png" , kEggValue * 2 + kMilkValue , kMilkEnergy + kEggEnergy );
			return omelet;
		}
		case FoodType::GrilledFish: {
			auto grilled_fish = std::make_shared<Food> ( "GrilledFish" , "Food/grilled_fish.png" , 150 , 50 );
			return grilled_fish;
		}
		default:
			CCLOG ( "fail to create Food with type :%d" , type );

	}
	return nullptr;
}


std::shared_ptr<Item> Food::GetCopy () const  {
	auto copy = std::make_shared<Food> ( *this );  // ʹ��Food�ĸ��ƹ��캯��
	return copy;
}