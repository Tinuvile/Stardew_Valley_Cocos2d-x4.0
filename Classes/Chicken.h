#pragma once
#include"Livestock.h"
#include"Egg.h"
#include<string>

const std::string chicken_icon[] = {
	"Livestock/brown_chicken_left1.png","Livestock/brown_chicken_left2.png","Livestock/brown_chicken_left3.png","Livestock/brown_chicken_left4.png",
	"Livestock/brown_chicken_right1.png","Livestock/brown_chicken_right2.png","Livestock/brown_chicken_right3.png","Livestock/brown_chicken_right4.png"
};

class Chicken :public Livestock {
private:
	int current_frame = 0;
public:
	//���캯��
	Chicken ( const cocos2d::Rect& area );

	//����������
	virtual ~Chicken ();

	//��̬create����
	static Chicken* create ( const cocos2d::Rect& area );

	//init��ʼ��
	virtual bool init ();

	// ��������
	// Ҫ��ȡEgg�ڻ���Item����Ķ��г�Ա����energy_provided)
	// ��Ҫʹ��std::xxx_pointer_cast(��std::dynamic_pointer_cast< >( )��ָ�������ת��Ϊ������
	virtual std::shared_ptr<Item> ProduceProduct ();


	//����ͼ��
	void UpdateTexture (float deltaTime);


};