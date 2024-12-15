#include"Livestock.h"

Livestock::Livestock ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area )
    : species ( species ) , icon_path ( icon_path ) , can_produce ( true ) , move_area ( area ) {};

Livestock::~Livestock(){
}

Livestock* Livestock::create ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area ) {
    Livestock* livestock = new Livestock ( species , icon_path , area );
    if (livestock && livestock->init ()) {
        livestock->autorelease ();  // 自动管理内存
        return livestock;
    }
    CC_SAFE_DELETE ( livestock );
    return nullptr;
}

void Livestock::RandomMove() {
    // 随机选择一个方向：0 - 下 , 1 - 上 , 2 - 左 , 3 - 右
    int direction = cocos2d::RandomHelper::random_int ( 0 , 3 );
    if (species == "Chicken") {
        direction %= 2;
        direction += 2;
    }
    // 获取当前的位置
    cocos2d::Vec2 current_position = this->getPosition ();

    // 根据方向修改目标位置
    cocos2d::Vec2 target_pos;

    switch (direction) {
        case 0: // 下
            target_pos = cocos2d::Vec2 ( current_position.x , move_area.getMinY () + 20.0f );
            break;
        case 1: // 上
            target_pos = cocos2d::Vec2 ( current_position.x , move_area.getMaxY () - 20.0f );
            break;
        case 2: // 左
            target_pos = cocos2d::Vec2 ( move_area.getMinX () + 20.0f , current_position.y );
            break;
        case 3: // 右
            target_pos = cocos2d::Vec2 ( move_area.getMaxX () - 20.0f , current_position.y );
            break;
    }
    
    move_direction = direction;

    //更改移动状态
    SetMoving ( true );

    // 创建 MoveTo 动作
    auto move_to = cocos2d::MoveTo::create ( 4.0f , target_pos );

    // 在移动完成时设置 isMoving 为 false
    auto callback = [this]() {
        this->SetMoving ( false );  // 移动完成后停止更新图像
        };
    auto sequence = cocos2d::Sequence::create ( move_to , cocos2d::CallFunc::create ( callback ) , nullptr );
    this->runAction ( sequence );

    //更改移动状态
    moving = true;
}

bool Livestock::init () {
    // 调用基类 Sprite 的初始化
    if (!Sprite::init ()) {
        CCLOG ( "failed to initialize Livestock." );
        return false;
    }

    // 设置家畜的图标
    if (!this->initWithFile ( icon_path )) {
        CCLOG ( "fail to initialize Livestock with file %s" , icon_path.c_str () );
        return false;
    }

    //更改图标大小
    this->setScale ( 5.0f , 5.0f );

    // 设置初始位置在活动范围内
    this->setPosition ( cocos2d::Vec2 (
        cocos2d::RandomHelper::random_real ( move_area.getMinX () , move_area.getMaxX () ) ,
        cocos2d::RandomHelper::random_real ( move_area.getMinY () , move_area.getMaxY () )
    ) );

    // 每隔一段时间随机移动
    schedule ( [this]( float deltaTime ) {
        this->RandomMove ();
    } , 15.0f , "livestock_random_move_key" );

    return true;
}

