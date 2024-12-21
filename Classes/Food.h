#pragma once
#include"Item.h"
#include<memory>

//食物类型枚举，新增类型时在此添加
enum class FoodType {
	Milk,
	Egg,
	FriedEgg,
	GrilledFish,
	Omelet
};

//不同食物的价格
const int kMilkValue = 100;
const int kEggValue = 40;

//不同食物提供的能量
const int kEggEnergy = 15;
const int kMilkEnergy = 30;

class Food :public Item {
private:
	//吃掉后能提供的能量
	int energy;
public:

	//构造函数
	Food ( const std::string& name , const std::string& path1 , const int value , int energy , int num_limit = 99 );

	//复制构造函数
	Food ( const Food& other ) :Item ( other ) , energy ( other.energy ) {};

	static std::shared_ptr<Food> create ( FoodType type );
	
	virtual ~Food () {};

	virtual std::shared_ptr<Item> GetCopy () const;

	int GetEnergy () const { return energy; }

};