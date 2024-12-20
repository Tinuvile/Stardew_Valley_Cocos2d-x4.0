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
	// 构造函数
	Cow ( const cocos2d::Rect& area );

	//虚析构函数
	virtual ~Cow ();

	// 静态create函数
	static Cow* create ( const cocos2d::Rect& area );

	// init初始化
	virtual bool init ();

	// 产出牛奶
	// 要获取Milk在基类Item以外的独有成员（如energy)
	// 需要使用std::xxx_pointer_cast(如std::dynamic_pointer_cast<Food>()将指针基类型转换为Food
	virtual std::shared_ptr<Item> ProduceProduct ();

	//移动时更新图像
	virtual void UpdateTexture ( float deltaTime );

};