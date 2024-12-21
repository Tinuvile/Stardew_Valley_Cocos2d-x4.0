#pragma once
#include"Food.h"
#include"Fish.h"
#include<vector>
#include<string>
#include<memory>


enum class Dishes {
	Wrong = -1,
	FriedEgg,
	GrilledFish,
	Omelet
};

class CookingPot :public cocos2d::Sprite {
private:
	std::vector<std::shared_ptr<Item>> pot;
public:
	CookingPot () {};
	~CookingPot () {};
	static CookingPot* create ();
	virtual bool init ();
	Dishes GetDishesId () const;
	std::shared_ptr<Item> GetDishes (Dishes dishes_id);
	void AddIngredient ( const  Item& ingredient );
	std::shared_ptr<Item> GetPotBack ();
	int GetPotSize () const;
	void ClearPot ();

	//仅供调试使用
	void DisplayPotInCCLOG () const;
	
};