#pragma once
#include"Food.h"

const int kEggValue = 40;
const int kEggEnergy = 15;

class Egg :public Food {
private:
public:
	//���캯��
	Egg ();

	//����������
	virtual ~Egg ();
};