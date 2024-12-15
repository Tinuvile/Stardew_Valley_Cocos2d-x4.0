#include"Sheep.h"

Sheep::Sheep ( const cocos2d::Rect& area )
	:Livestock ( "Sheep" , sheep_icon[0] , area ) {};


Sheep* Sheep::create ( const cocos2d::Rect& area ) {
	Sheep* sheep = new Sheep ( area );
	if (sheep && sheep->init ()) {
		sheep->autorelease ();
		return sheep;
	}
	CC_SAFE_DELETE ( sheep );
	return nullptr;
}

bool Sheep::init () {
	if (!Livestock::init ()) {
		CCLOG ( "Failed to initialize Sheep." );
		return false;
	}

	// ���ò�ͬ�����ͼ��
	// ǰ������ͼƬ�����ƶ������޸�
	this->initWithFile ( sheep_icon[0] ); // Ĭ��ͼ��Ϊǰ��

	// ÿ��һ��ʱ���������ƶ�
	schedule ( [this]( float deltaTime ) {
		this->RandomMove ();
	} , 7.0f , "sheep_random_move_key" );


	schedule ( [this]( float deltaTime ) {
		this->UpdateTexture ( deltaTime );
	} , 0.2f , "sheep_texture_update_key" );


	return true;
}

std::shared_ptr<Item> Sheep::ProduceProduct () {
	if (can_produce) {
		CCLOG ( "Sheep produced wool!" );
		std::shared_ptr<Wool> production = std::make_shared<Wool> ( Wool () );
		can_produce = false;
		return production;
	}
	return nullptr;
}

void Sheep::UpdateTexture ( float deltaTime ) {
	if (moving) {
		current_frame = (current_frame + 1) % 4;
		this->setTexture ( sheep_icon[move_direction * 4 + current_frame] );
	}
	if (!can_produce) {
		this->setTexture ( sheared_sheep_icon[move_direction * 4 + current_frame] );
	}
}
