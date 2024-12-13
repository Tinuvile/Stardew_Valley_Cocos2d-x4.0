#include "NPC.h"

// NPC 类构造函数  
NPC::NPC ( const std::string& name , const cocos2d::Vec2& position ,
    const std::vector<std::vector<std::string>>& animationFrames ,
    const std::vector<cocos2d::Vec2>& validPositions )
    : name ( name ) , position ( position ) , animations ( animationFrames ) ,
    nonTransparentPixels ( validPositions ) , currentAnimationName ( "" ) {

    // CCLOG ( "Number of valid positions: %zu" , nonTransparentPixels.size () );

    this->sprite = cocos2d::Sprite::create ( animationFrames[1][0] ); // 使用下方向的第一帧作为初始图像  
    if (!this->sprite) {
        // CCLOG ( "Error: Sprite could not be created from %s" , animationFrames[1][0].c_str () );
        return; // 处理错误情况，例如返回或抛出异常  
    }
    this->sprite->setPosition ( position );
    // 设置 NPC 的缩放  
    this->sprite->setScale ( 3.0f );

    // 创建四个方向的动画  
    CreateAnimation ( "upAnimation" , animations[0] , 0.3f );
    CreateAnimation ( "downAnimation" , animations[1] , 0.3f );
    CreateAnimation ( "leftAnimation" , animations[2] , 0.3f );
    CreateAnimation ( "rightAnimation" , animations[3] , 0.3f );

}

void NPC::RandomMove () {
    // CCLOG ( "RandomMove method called" );

    // 定义可移动的方向，分别为上、下、左、右  
    std::vector<cocos2d::Vec2> directions = {
        cocos2d::Vec2 ( 0, 50 ),    // 上  
        cocos2d::Vec2 ( 0, -50 ),   // 下  
        cocos2d::Vec2 ( -50, 0 ),   // 左  
        cocos2d::Vec2 ( 50, 0 )     // 右  
    };

    // 随机选择一个方向  
    int randomIndex = rand () % directions.size ();
    cocos2d::Vec2 moveDirection = directions[randomIndex];

    // 计算目标位置  
    cocos2d::Vec2 targetPosition = position + moveDirection;

    // CCLOG ( "Attempting to move to position: (%f, %f)" , targetPosition.x , targetPosition.y );

    // 判断目标位置是否有效，这里传入方向  
    if (IsPositionValid ( targetPosition , moveDirection )) {
        MoveToPosition ( targetPosition );
    }
    else {
        // CCLOG ( "Position (%f, %f) is not valid. Skipping movement." , targetPosition.x , targetPosition.y );
    }
}

// 检查目标位置是否有效  
bool NPC::IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction ) {
    // CCLOG ( "Checking if position is valid: (%f, %f)" , targetPosition.x , targetPosition.y );

    // 检查在给定方向上前四个像素  
    for (int i = 1; i <= 4; ++i) {
        cocos2d::Vec2 checkPosition = targetPosition + direction * static_cast<float>(i);
        bool isTransparent = true; // 假设是透明的  

        // 检查该位置是否在 nonTransparentPixels 区域内  
        for (const auto& pixel : nonTransparentPixels) {
            if (pixel.distance ( checkPosition ) < 36) { // 如果在距离内，表示该位置不透明  
                // CCLOG ( "Found non-transparent pixel at: (%f, %f)" , checkPosition.x , checkPosition.y );
                isTransparent = false; // 发现不透明像素  
                break;
            }
        }

        if (!isTransparent) { // 如果发现不透明像素，返回 false  
            // CCLOG ( "Position (%f, %f) is not valid due to non-transparent pixel." , checkPosition.x , checkPosition.y );
            return false;
        }
    }

    // 如果所有检查的像素均透明，则返回 true  
    // CCLOG ( "Position (%f, %f) is valid." , targetPosition.x , targetPosition.y );
    return true;
}


void NPC::CreateAnimation ( const std::string& animationName , const std::vector<std::string>& framePaths , float delay ) {
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for (const auto& framePath : framePaths) {
        cocos2d::SpriteFrame* frame = cocos2d::SpriteFrame::create ( framePath , cocos2d::Rect ( 0 , 0 , sprite->getContentSize ().width , sprite->getContentSize ().height ) );
        frames.pushBack ( frame );
    }
    auto animation = cocos2d::Animation::createWithSpriteFrames ( frames , delay );
    cocos2d::AnimationCache::getInstance ()->addAnimation ( animation , animationName );
}


void NPC::PlayAnimation ( const std::string& animationName , bool loop ) {
    // 在播放新的动画前，停止当前动画  
    this->sprite->stopAllActions (); // 丢弃所有动画

    auto animation = cocos2d::AnimationCache::getInstance ()->getAnimation ( animationName );
    if (animation) {
        auto animateAction = cocos2d::Animate::create ( animation );

        // 如果循环播放，我们使用 RepeatForever  
        if (loop) {
            auto repeatAction = cocos2d::RepeatForever::create ( animateAction );
            sprite->runAction ( repeatAction );
        }
        else {
            sprite->runAction ( animateAction );
        }
    }
}


void NPC::MoveToPosition ( const cocos2d::Vec2& targetPosition ) {
    //CCLOG ( "Moving to position: (%f, %f)" , targetPosition.x , targetPosition.y );

    // 判断朝向并播放对应动画  
    std::string animationName;
    if (targetPosition.x < position.x) {
        animationName = "leftAnimation";
    }
    else if (targetPosition.x > position.x) {
        animationName = "rightAnimation";
    }
    else if (targetPosition.y < position.y) {
        animationName = "downAnimation";
    }
    else if (targetPosition.y > position.y) {
        animationName = "upAnimation";
    }



    // 只在当前动画不是目标动画时播放动画  
    if (currentAnimationName != animationName) {
        PlayAnimation ( animationName , true );
        currentAnimationName = animationName; // 跟踪当前动画名称  
    }

    // 创建一个移动动作  
    auto moveAction = cocos2d::MoveTo::create ( 6.0f , targetPosition );
    auto moveDone = cocos2d::CallFunc::create ( [this , targetPosition]() {
        position = targetPosition; // 更新当前位置  
        // 可以播放停止动画  
        currentAnimationName = ""; // 移动完成后重置动画状态  
    } );

    this->sprite->runAction ( cocos2d::Sequence::create ( moveAction , moveDone , nullptr ) );

    if (moveAction->isDone ()) {
        PlayAnimation ( "standAnimation" , true ); // 在移动完成后播放站立动画  
        currentAnimationName = "standAnimation"; // 更新状态  
    }
}
