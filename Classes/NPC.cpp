#include "NPC.h"

// NPC �๹�캯��  
NPC::NPC ( const std::string& name , const cocos2d::Vec2& position ,
    const std::vector<std::vector<std::string>>& animationFrames ,
    const std::vector<cocos2d::Vec2>& validPositions )
    : name ( name ) , position ( position ) , animations ( animationFrames ) ,
    nonTransparentPixels ( validPositions ) , currentAnimationName ( "" ) {

    // CCLOG ( "Number of valid positions: %zu" , nonTransparentPixels.size () );

    this->sprite = cocos2d::Sprite::create ( animationFrames[1][0] ); // ʹ���·���ĵ�һ֡��Ϊ��ʼͼ��  
    if (!this->sprite) {
        // CCLOG ( "Error: Sprite could not be created from %s" , animationFrames[1][0].c_str () );
        return; // ���������������緵�ػ��׳��쳣  
    }
    this->sprite->setPosition ( position );
    // ���� NPC ������  
    this->sprite->setScale ( 3.0f );

    // �����ĸ�����Ķ���  
    CreateAnimation ( "upAnimation" , animations[0] , 0.3f );
    CreateAnimation ( "downAnimation" , animations[1] , 0.3f );
    CreateAnimation ( "leftAnimation" , animations[2] , 0.3f );
    CreateAnimation ( "rightAnimation" , animations[3] , 0.3f );

}

void NPC::RandomMove () {
    // CCLOG ( "RandomMove method called" );

    // ������ƶ��ķ��򣬷ֱ�Ϊ�ϡ��¡�����  
    std::vector<cocos2d::Vec2> directions = {
        cocos2d::Vec2 ( 0, 50 ),    // ��  
        cocos2d::Vec2 ( 0, -50 ),   // ��  
        cocos2d::Vec2 ( -50, 0 ),   // ��  
        cocos2d::Vec2 ( 50, 0 )     // ��  
    };

    // ���ѡ��һ������  
    int randomIndex = rand () % directions.size ();
    cocos2d::Vec2 moveDirection = directions[randomIndex];

    // ����Ŀ��λ��  
    cocos2d::Vec2 targetPosition = position + moveDirection;

    // CCLOG ( "Attempting to move to position: (%f, %f)" , targetPosition.x , targetPosition.y );

    // �ж�Ŀ��λ���Ƿ���Ч�����ﴫ�뷽��  
    if (IsPositionValid ( targetPosition , moveDirection )) {
        MoveToPosition ( targetPosition );
    }
    else {
        // CCLOG ( "Position (%f, %f) is not valid. Skipping movement." , targetPosition.x , targetPosition.y );
    }
}

// ���Ŀ��λ���Ƿ���Ч  
bool NPC::IsPositionValid ( const cocos2d::Vec2& targetPosition , const cocos2d::Vec2& direction ) {
    // CCLOG ( "Checking if position is valid: (%f, %f)" , targetPosition.x , targetPosition.y );

    // ����ڸ���������ǰ�ĸ�����  
    for (int i = 1; i <= 4; ++i) {
        cocos2d::Vec2 checkPosition = targetPosition + direction * static_cast<float>(i);
        bool isTransparent = true; // ������͸����  

        // ����λ���Ƿ��� nonTransparentPixels ������  
        for (const auto& pixel : nonTransparentPixels) {
            if (pixel.distance ( checkPosition ) < 36) { // ����ھ����ڣ���ʾ��λ�ò�͸��  
                // CCLOG ( "Found non-transparent pixel at: (%f, %f)" , checkPosition.x , checkPosition.y );
                isTransparent = false; // ���ֲ�͸������  
                break;
            }
        }

        if (!isTransparent) { // ������ֲ�͸�����أ����� false  
            // CCLOG ( "Position (%f, %f) is not valid due to non-transparent pixel." , checkPosition.x , checkPosition.y );
            return false;
        }
    }

    // ������м������ؾ�͸�����򷵻� true  
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
    // �ڲ����µĶ���ǰ��ֹͣ��ǰ����  
    this->sprite->stopAllActions (); // �������ж���

    auto animation = cocos2d::AnimationCache::getInstance ()->getAnimation ( animationName );
    if (animation) {
        auto animateAction = cocos2d::Animate::create ( animation );

        // ���ѭ�����ţ�����ʹ�� RepeatForever  
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

    // �жϳ��򲢲��Ŷ�Ӧ����  
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



    // ֻ�ڵ�ǰ��������Ŀ�궯��ʱ���Ŷ���  
    if (currentAnimationName != animationName) {
        PlayAnimation ( animationName , true );
        currentAnimationName = animationName; // ���ٵ�ǰ��������  
    }

    // ����һ���ƶ�����  
    auto moveAction = cocos2d::MoveTo::create ( 6.0f , targetPosition );
    auto moveDone = cocos2d::CallFunc::create ( [this , targetPosition]() {
        position = targetPosition; // ���µ�ǰλ��  
        // ���Բ���ֹͣ����  
        currentAnimationName = ""; // �ƶ���ɺ����ö���״̬  
    } );

    this->sprite->runAction ( cocos2d::Sequence::create ( moveAction , moveDone , nullptr ) );

    if (moveAction->isDone ()) {
        PlayAnimation ( "standAnimation" , true ); // ���ƶ���ɺ󲥷�վ������  
        currentAnimationName = "standAnimation"; // ����״̬  
    }
}
