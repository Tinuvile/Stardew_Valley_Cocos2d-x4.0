#include"Food.h"

Food::Food ( const std::string& name , const std::string& path1 , const int value , int energy , int num_limit )
	:Item ( name , path1 , value , num_limit ) , energy ( energy ) {
};

std::shared_ptr<Food> Food::create (FoodType type) {
	switch (type) {
		case FoodType::Milk: {
			auto milk = std::make_shared<Food> ( "Milk" , "Livestock/milk.png" , kMilkValue , kMilkEnergy );
			return milk;
		}
		case FoodType::Egg: {
			auto egg = std::make_shared<Food> ( "Egg" , "Livestock / egg.png" , kEggValue , kEggEnergy );
			return egg;
		}
		default:
			CCLOG ( "fail to create Food with type :%d" , type );
	}
	return nullptr;
}
