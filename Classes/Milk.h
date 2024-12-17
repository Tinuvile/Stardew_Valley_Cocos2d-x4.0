#pragma once
#include"Food.h"

//牛奶默认价值
const int kMilkValue = 100;

class Milk :public Food {
private:
public:
	//构造函数
	Milk ();
	virtual ~Milk ();

};