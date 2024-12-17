#include"Cow.h"

Cow::Cow ( const cocos2d::Rect& area )
	: Livestock ( "Cow" , cow_icon[0] , area) {
};

Cow::~Cow () {
}

Cow* Cow::create ( const cocos2d::Rect& area ) {
	Cow* cow = new Cow ( area );
	if (cow && cow->init ()) {
		cow->autorelease ();
		return cow;
	}
	CC_SAFE_DELETE ( cow );
	return nullptr;
}

bool Cow::init () {
	if (!Livestock::init ()) {
		CCLOG ( "Failed to initialize Cow." );
		return false;
	}

	// ���ò�ͬ�����ͼ��
	// ǰ������ͼƬ�����ƶ������޸�
	this->initWithFile ( cow_icon[0]); // Ĭ��ͼ��Ϊǰ��

	// ÿ��һ��ʱ���������ƶ�
	schedule ( [this]( float deltaTime ) {
		this->RandomMove ();
	} , 7.0f , "cow_random_move_key" );


	schedule ( [this]( float deltaTime ) {
		this->UpdateTexture ( deltaTime );
	} , 0.2f , "cow_texture_update_key" );


	return true;
}

std::shared_ptr<Item> Cow::ProduceProduct () {
	if (can_produce) {
		CCLOG ( "Cow produced milk!" );
		std::shared_ptr<Food> production = Food::create ( FoodType::Milk);
		can_produce = false;
		return production;
	}
	return nullptr;
}

void Cow::UpdateTexture ( float deltaTime ) {
	if (moving) {
		current_frame = (current_frame + 1) % 4;
		this->setTexture ( cow_icon[move_direction * 4 + current_frame] );
	}

}


