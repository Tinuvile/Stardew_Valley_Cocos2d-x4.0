#pragma once
#include"Food.h"

const int kEggValue = 40;
const int kEggEnergy = 15;

class Egg :public Food {
private:
public:
	//构造函数
	Egg ();

	//虚析构函数
	virtual ~Egg ();
};