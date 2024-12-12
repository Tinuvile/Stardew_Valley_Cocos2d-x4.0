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
	//构造函数
	Chicken ( const cocos2d::Rect& area );

	//虚析构函数
	virtual ~Chicken ();

	//静态create函数
	static Chicken* create ( const cocos2d::Rect& area );

	//init初始化
	virtual bool init ();

	// 产出鸡蛋
	// 要获取Egg在基类Item以外的独有成员（如energy_provided)
	// 需要使用std::xxx_pointer_cast(如std::dynamic_pointer_cast< >( )将指针基类型转换为派生类
	virtual std::shared_ptr<Item> ProduceProduct ();


	//更新图像
	void UpdateTexture (float deltaTime);


};