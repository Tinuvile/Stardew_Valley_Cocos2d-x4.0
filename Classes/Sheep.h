#pragma once
#include"Livestock.h"
#include"Wool.h"

const std::string sheep_icon[] = {
	"Livestock/sheep_front1.png","Livestock/sheep_front2.png","Livestock/sheep_front3.png","Livestock/sheep_front4.png",
	"Livestock/sheep_back1.png","Livestock/sheep_back2.png","Livestock/sheep_back3.png","Livestock/sheep_back4.png",
	"Livestock/sheep_left1.png","Livestock/sheep_left2.png","Livestock/sheep_left3.png","Livestock/sheep_left4.png",
	"Livestock/sheep_right1.png","Livestock/sheep_right2.png", "Livestock/sheep_right3.png","Livestock/sheep_right4.png"
};

const std::string sheared_sheep_icon[] = {
	"Livestock/sheared_sheep_front1.png","Livestock/sheared_sheep_front2.png","Livestock/sheared_sheep_front3.png","Livestock/sheared_sheep_front4.png",
	"Livestock/sheared_sheep_back1.png","Livestock/sheared_sheep_back2.png","Livestock/sheared_sheep_back3.png","Livestock/sheared_sheep_back4.png",
	"Livestock/sheared_sheep_left1.png","Livestock/sheared_sheep_left2.png","Livestock/sheared_sheep_left3.png","Livestock/sheared_sheep_left4.png",
	"Livestock/sheared_sheep_right1.png","Livestock/sheared_sheep_right2.png", "Livestock/sheared_sheep_right3.png","Livestock/sheared_sheep_right4.png"
};

class Sheep :public Livestock {
private:
	int current_frame = 0;
public:
	// 构造函数
	Sheep ( const cocos2d::Rect& area );

	//虚析构函数
	virtual ~Sheep () {};

	// 静态create函数
	static Sheep* create ( const cocos2d::Rect& area );

	// init初始化
	virtual bool init ();

	// 产出羊毛
	// 要获取Wool在基类Item以外的独有成员（如energy_provided)
	// 需要使用std::xxx_pointer_cast(如std::dynamic_pointer_cast<Wool>()将指针基类型转换为Wool
	virtual std::shared_ptr<Item> ProduceProduct ();

	//移动时更新图像
	virtual void UpdateTexture ( float deltaTime );
};