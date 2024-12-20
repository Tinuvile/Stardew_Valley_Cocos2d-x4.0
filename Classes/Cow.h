#pragma once
#include"Livestock.h"
#include "Food.h"

const std::string cow_icon[] = {
	"Livestock/white_cow_front1.png","Livestock/white_cow_front2.png","Livestock/white_cow_front3.png","Livestock/white_cow_front4.png",
	"Livestock/white_cow_back1.png","Livestock/white_cow_back2.png","Livestock/white_cow_back3.png","Livestock/white_cow_back4.png",
	"Livestock/white_cow_left1.png","Livestock/white_cow_left2.png","Livestock/white_cow_left3.png","Livestock/white_cow_left4.png",
	"Livestock/white_cow_right1.png","Livestock/white_cow_right2.png", "Livestock/white_cow_right3.png","Livestock/white_cow_right4.png"
};

class Cow :public Livestock {
private:
	int current_frame = 0;
public:
	// ���캯��
	Cow ( const cocos2d::Rect& area );

	//����������
	virtual ~Cow ();

	// ��̬create����
	static Cow* create ( const cocos2d::Rect& area );

	// init��ʼ��
	virtual bool init ();

	// ����ţ��
	// Ҫ��ȡMilk�ڻ���Item����Ķ��г�Ա����energy)
	// ��Ҫʹ��std::xxx_pointer_cast(��std::dynamic_pointer_cast<Food>()��ָ�������ת��ΪFood
	virtual std::shared_ptr<Item> ProduceProduct ();

	//�ƶ�ʱ����ͼ��
	virtual void UpdateTexture ( float deltaTime );

};