#pragma once
#include"Item.h"

//ţ��Ĭ�ϼ�ֵ
const int kMilkValue = 100;

class Milk :public Item {
private:
	//���º��ṩ������
	const int energy_provied = 30;
public:
	//���캯��
	Milk ();
	virtual ~Milk ();
	//��ȡ���ṩ������
	int GetEnergyProvided () const {
		return energy_provied;
	}

};