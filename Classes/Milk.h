#pragma once
#include"Item.h"

//牛奶默认价值
const int kMilkValue = 100;

class Milk :public Item {
private:
	//吃下后提供的能量
	const int energy_provied = 30;
public:
	//构造函数
	Milk ();
	virtual ~Milk ();
	//获取能提供的能量
	int GetEnergyProvided () const {
		return energy_provied;
	}

};