#include"Livestock.h"

Livestock::Livestock ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area )
    : species ( species ) , icon_path ( icon_path ) , can_produce ( true ) , move_area ( area ) {};

Livestock::~Livestock(){
}

Livestock* Livestock::create ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area ) {
    Livestock* livestock = new Livestock ( species , icon_path , area );
    if (livestock && livestock->init ()) {
        livestock->autorelease ();  // �Զ������ڴ�
        return livestock;
    }
    CC_SAFE_DELETE ( livestock );
    return nullptr;
}

void Livestock::RandomMove() {
    // ���ѡ��һ������0 - �� , 1 - �� , 2 - �� , 3 - ��
    int direction = cocos2d::RandomHelper::random_int ( 0 , 3 );
    if (species == "Chicken") {
        direction %= 2;
        direction += 2;
    }
    // ��ȡ��ǰ��λ��
    cocos2d::Vec2 current_position = this->getPosition ();

    // ���ݷ����޸�Ŀ��λ��
    cocos2d::Vec2 target_pos;

    switch (direction) {
        case 0: // ��
            target_pos = cocos2d::Vec2 ( current_position.x , move_area.getMinY () + 20.0f );
            break;
        case 1: // ��
            target_pos = cocos2d::Vec2 ( current_position.x , move_area.getMaxY () - 20.0f );
            break;
        case 2: // ��
            target_pos = cocos2d::Vec2 ( move_area.getMinX () + 20.0f , current_position.y );
            break;
        case 3: // ��
            target_pos = cocos2d::Vec2 ( move_area.getMaxX () - 20.0f , current_position.y );
            break;
    }
    
    move_direction = direction;

    //�����ƶ�״̬
    SetMoving ( true );

    // ���� MoveTo ����
    auto move_to = cocos2d::MoveTo::create ( 4.0f , target_pos );

    // ���ƶ����ʱ���� isMoving Ϊ false
    auto callback = [this]() {
        this->SetMoving ( false );  // �ƶ���ɺ�ֹͣ����ͼ��
        };
    auto sequence = cocos2d::Sequence::create ( move_to , cocos2d::CallFunc::create ( callback ) , nullptr );
    this->runAction ( sequence );

    //�����ƶ�״̬
    moving = true;
}

bool Livestock::init () {
    // ���û��� Sprite �ĳ�ʼ��
    if (!Sprite::init ()) {
        CCLOG ( "failed to initialize Livestock." );
        return false;
    }

    // ���ü����ͼ��
    if (!this->initWithFile ( icon_path )) {
        CCLOG ( "fail to initialize Livestock with file %s" , icon_path.c_str () );
        return false;
    }

    //����ͼ���С
    this->setScale ( 5.0f , 5.0f );

    // ���ó�ʼλ���ڻ��Χ��
    this->setPosition ( cocos2d::Vec2 (
        cocos2d::RandomHelper::random_real ( move_area.getMinX () , move_area.getMaxX () ) ,
        cocos2d::RandomHelper::random_real ( move_area.getMinY () , move_area.getMaxY () )
    ) );

    // ÿ��һ��ʱ������ƶ�
    schedule ( [this]( float deltaTime ) {
        this->RandomMove ();
    } , 15.0f , "livestock_random_move_key" );

    return true;
}

