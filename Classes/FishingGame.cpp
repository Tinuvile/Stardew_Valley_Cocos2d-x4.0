#include"FishingGame.h"

FishingGame* FishingGame::create ( const cocos2d::Vec2& player_position ) {
    FishingGame* fishing_game = new FishingGame ( player_position );
    if (fishing_game && fishing_game->init ()) {
        fishing_game->autorelease ();
        return fishing_game;
    }
    CC_SAFE_DELETE ( fishing_game );
    return nullptr;
}

bool FishingGame::init() {
    fish_type = cocos2d::RandomHelper::random_int ( 0 , 2 );

    position.x += 100;
    position.y -= 70;

    //背景初始化
    background = cocos2d::Sprite::create ( "Beach/fishing_icon.png" );
    background->setAnchorPoint ( cocos2d::Vec2 ( 0 , 0 ) );
    background->setScale ( kBackgroundScale );
    background->setPosition ( position );
    this->addChild ( background , 0 );

    float background_width = background->getContentSize ().width * kBackgroundScale;
    float background_height = background->getContentSize ().height * kBackgroundScale;
    
    // 进度条初始化
    progress_bar = cocos2d::ProgressTimer::create ( cocos2d::Sprite::create ( "Beach/progress_bar.png" ) );
    progress_bar->setAnchorPoint ( cocos2d::Vec2 ( 0 , 0 ) );
    progress_bar->setScaleX ( kBackgroundScale * kProgressBarBasicScaleX );
    progress_bar->setScaleY ( kBackgroundScale * kProgressBarBasicScaleY );
    progress_bar->setType ( cocos2d::ProgressTimer::Type::BAR );
    progress_bar->setMidpoint ( cocos2d::Vec2 ( 0 , 0 ) );
    progress_bar->setBarChangeRate ( cocos2d::Vec2 ( 0 , 1 ) );
    progress_bar->setPosition ( cocos2d::Vec2 ( position.x + background_width * kProgressBarBeginX / kBackgroundWidth ,
        position.y + background_height * kProgressBarBeginY / kBackgroundHeight ) );
    progress_bar->setPercentage ( 3 ); // 初始值5%
    this->addChild ( progress_bar , 5 );

    auto icon_pos = position;
    icon_pos.x +=  background_width * kIconBeginX / kBackgroundWidth;
    icon_pos.y = icon_pos.y + background_height * kIconBeginY / kBackgroundHeight;

    // 鱼精灵初始化
    fish = cocos2d::Sprite::create ( "Beach/fishlike_icon.png" );
    fishlike_icon_height = icon_pos.y; // 初始位置
    fish->setAnchorPoint ( cocos2d::Vec2 ( 0 , 0 ) );
    fish->setScale ( kBackgroundScale*kFishBasicScale );
    fish->setPosition ( cocos2d::Vec2 ( icon_pos.x , fishlike_icon_height ) );
    this->addChild ( fish , 10 );

    // 绿色浮标初始化
    green_bar = cocos2d::Sprite::create ( "Beach/green_bar.png" );
    green_bar->setAnchorPoint ( cocos2d::Vec2 ( 0 , 0 ) );
    green_bar->setScale ( kBackgroundScale );
    green_bar->setScaleY ( kBackgroundScale * kGreeenBarBasicScaleY );
    green_bar_height = icon_pos.y;
    green_bar->setPosition ( cocos2d::Vec2 ( icon_pos.x , green_bar_height ) );
    this->addChild ( green_bar , 5 );

    // 添加事件监听器
    AddMouseListener ();

    // 定时器更新鱼和浮标的位置
    this->schedule ( CC_SCHEDULE_SELECTOR ( FishingGame::UpdateGame ) , 0.016f );

    return true;
}

// 鼠标活动监听
void FishingGame::AddMouseListener () {
    auto listener = cocos2d::EventListenerMouse::create ();
    listener->onMouseDown = [this]( cocos2d::EventMouse* event ) {
        is_pressing = true;
        };
    listener->onMouseUp = [this]( cocos2d::EventMouse* event ) {
        is_pressing = false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , this );
}


void FishingGame::UpdateGame ( float dt ) {
    float movable_height = background->getContentSize ().height * kIconHeight / kBackgroundHeight * kBackgroundScale;

    // 更新绿色浮标
    if (is_pressing) {
        green_bar_height += 300 * dt; // 上升速度
    }
    else {
        green_bar_height -= 350 * dt; // 下降速度
    }

    // 限制绿色浮标的移动范围
    green_bar_height = std::max ( position.y , std::min ( position.y + movable_height - green_bar->getContentSize ().height * kGreeenBarBasicScaleY * kBackgroundScale
        , green_bar_height ) );
    green_bar->setPositionY ( green_bar_height );

    // 设置鱼的捕获难度
    float fish_move_range = [this]() {
        int catching_difficulty;
        switch (fish_type) {
            case 0:
                catching_difficulty = 1;
                break;
            case 1:
                catching_difficulty = 3;
                break;
            case 2:
                catching_difficulty = 2;
                break;
            default:
                catching_difficulty = 1;
                break;
        }
        switch (catching_difficulty) {
            case 1:
                return 0.5f;
            case 2:
                return 0.80f;
            case 3:
                return 1.1f;
            default:
                return 0.5f;
        }
    }();

    // 鱼的随机移动和控制移动范围
    fishlike_icon_height += cocos2d::RandomHelper::random_real ( -movable_height , movable_height ) * dt * kBackgroundScale * fish_move_range;
    fishlike_icon_height = std::max ( position.y , std::min ( position.y + movable_height - fish->getContentSize ().height * kFishBasicScale * kBackgroundScale ,
        fishlike_icon_height ) );
    fish->setPositionY ( fishlike_icon_height );

    // 检查绿色浮标与鱼的位置
    CheckFishInBar ();
}

void FishingGame::CheckFishInBar () {
    //绿色浮标的顶部和底部位置
    float green_bar_bottom = green_bar_height;
    float green_bar_top = green_bar_bottom + green_bar->getContentSize ().height * green_bar->getScaleY ();

    // 鱼的顶部和底部位置
    float fish_top = fishlike_icon_height + fish->getContentSize ().height * fish->getScaleY ();
    float fish_bottom = fishlike_icon_height/* - fish->getContentSize ().height * fish->getScaleY ()*/;

    // 判断鱼是否在绿色浮标区域内
    //if (fish_top > green_bar_bottom && fish_bottom < green_bar_top) {
    //    // 鱼在绿色浮标区域内，进度条增加
    //    progress_bar->setPercentage ( progress_bar->getPercentage () + 0.4f );
    //}
    //else {
    //    // 鱼不在绿色浮标区域内，进度条减少
    //    progress_bar->setPercentage ( progress_bar->getPercentage () - 0.55f );
    //}
    if (fish_bottom > green_bar_bottom && fish_top < green_bar_top) {
        // 鱼在绿色浮标区域内，进度条增加
        progress_bar->setPercentage ( progress_bar->getPercentage () + 0.4f );
    }
    else {
        // 鱼不在绿色浮标区域内，进度条减少
        progress_bar->setPercentage ( progress_bar->getPercentage () - 0.55f );
    }

    // 检查游戏结束条件
    if (progress_bar->getPercentage () >= 100) {
        CCLOG ( "You caught the fish!" );
        EndGame ( true );
    }
    else if (progress_bar->getPercentage () <= 0) {
        CCLOG ( "The fish escaped!" );
        EndGame ( false );
    }
}

void FishingGame::EndGame ( bool success ) {
    if (success) {
        // 向背包中加入对应鱼
        std::shared_ptr<Fish> fish_caught = std::make_shared<Fish> ( fish_type );
        inventory->AddItem ( *fish_caught );
        inventory->DisplayPackageInCCLOG ();
        CCLOG ( "Player wins!" );
    }
    else {
        // 鱼逃脱的逻辑
        CCLOG ( "Player loses!" );
    }
    ////恢复其他节点的活动
    //this->getParent ()->resume ();
    //player1->resume ();

    this->removeFromParent ();
}