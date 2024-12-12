#include"Chicken.h"

Chicken::Chicken ( const cocos2d::Rect& area )
	:Livestock ( "Chicken" , chicken_icon[0] , area ) {};

Chicken::~Chicken () {
}

Chicken* Chicken::create ( const cocos2d::Rect& area ) {
	Chicken* chicken = new Chicken ( area );
	if (chicken && chicken->init ()) {
		chicken->autorelease ();
		return chicken;
	}
	CC_SAFE_DELETE ( chicken );
	return nullptr;
}

bool Chicken::init () {
	if (!Livestock::init ()) {
		CCLOG ( "Failed to initialize Cow." );
		return false;
	}

	// 设置不同方向的图标
	// 前后左右图片根据移动方向修改
	this->initWithFile ( chicken_icon[0] ); // 默认图标为前面

	// 每隔一段时间进行随机移动
	schedule ( [this]( float deltaTime ) {
		this->RandomMove ();
	} , 7.0f , "chicken_random_move_key" );


	schedule ( [this]( float deltaTime ) {
		this->UpdateTexture ( deltaTime );
	} , 0.15f , "chicken_texture_update_key" );


	return true;

}

std::shared_ptr<Item> Chicken::ProduceProduct () {
	if (can_produce) {
		CCLOG ( "Chicken produced egg!" );
		std::shared_ptr<Egg> production = std::make_shared<Egg> ( Egg () );
		can_produce = false;
		return production;
	}
	return nullptr;
}

void Chicken::UpdateTexture ( float deltaTime ) {
	if (moving) {
		current_frame = (current_frame + 1) % 4;
		this->setTexture ( chicken_icon[(move_direction - 2) * 4 + current_frame] );
	}

}