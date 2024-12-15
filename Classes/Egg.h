#pragma once
#include"Item.h"

const int kEggValue = 40;

class Egg :public Item {
private:
	//作为食物可提供的能量
	const int energy_provided = 15;
public:
	//构造函数
	Egg ();

	//虚析构函数
	virtual ~Egg ();

	//获取`energy_provided`
	int GetEnergyProvided ()const {
		return energy_provided;
	}
};