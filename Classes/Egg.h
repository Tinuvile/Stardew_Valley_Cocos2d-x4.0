#pragma once
#include"Item.h"

const int kEggValue = 40;

class Egg :public Item {
private:
	//��Ϊʳ����ṩ������
	const int energy_provided = 15;
public:
	//���캯��
	Egg ();

	//����������
	virtual ~Egg ();

	//��ȡ`energy_provided`
	int GetEnergyProvided ()const {
		return energy_provided;
	}
};