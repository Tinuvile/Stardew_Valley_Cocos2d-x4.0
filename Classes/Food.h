#pragma once
#include"Item.h"
#include<memory>

//ʳ������ö�٣���������ʱ�ڴ����
enum class FoodType {
	Milk,
	Egg,
	FriedEgg,
	GrilledFish,
	Omelet
};

//��ͬʳ��ļ۸�
const int kMilkValue = 100;
const int kEggValue = 40;

//��ͬʳ���ṩ������
const int kEggEnergy = 15;
const int kMilkEnergy = 30;

class Food :public Item {
private:
	//�Ե������ṩ������
	int energy;
public:

	//���캯��
	Food ( const std::string& name , const std::string& path1 , const int value , int energy , int num_limit = 99 );

	//���ƹ��캯��
	Food ( const Food& other ) :Item ( other ) , energy ( other.energy ) {};

	static std::shared_ptr<Food> create ( FoodType type );
	
	virtual ~Food () {};

	virtual std::shared_ptr<Item> GetCopy () const;

	int GetEnergy () const { return energy; }

};