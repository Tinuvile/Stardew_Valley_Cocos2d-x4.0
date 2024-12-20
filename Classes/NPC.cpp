#include "NPC.h"
#include "AppDelegate.h"

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
    CreateAnimation ( name + "_upAnimation" , animations[0] , 0.3f );
    CreateAnimation ( name + "_downAnimation" , animations[1] , 0.3f );
    CreateAnimation ( name + "_leftAnimation" , animations[2] , 0.3f );
    CreateAnimation ( name + "_rightAnimation" , animations[3] , 0.3f );

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
        cocos2d::log ( "%s" , framePath.c_str() );
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
        animationName = name + "_leftAnimation";
    }
    else if (targetPosition.x > position.x) {
        animationName = name + "_rightAnimation";
    }
    else if (targetPosition.y < position.y) {
        animationName = name + "_downAnimation";
    }
    else if (targetPosition.y > position.y) {
        animationName = name + "_upAnimation";
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



// 获取对话信息的函数
std::vector<std::vector<std::string>> getDialog ( std::string npc , std::string relation_ship ) {
    if (npc_relationship->getRelationship ( "player" , npc ) >= 80) {
        return {
            {"Here, I brought you a gift!", "I really appreciate it!", "How have you been?", "Can we talk?", "Sure"},
            {"I have something special for you.", "Thank you! That means a lot.", "I just wanted to check in.", "I don't care.", "Leave me alone!"},
            {"Look what I got for you, a little present!", "Wow, this is amazing!", "I am not.", "Okay", "Alright"},
            {"I thought you might like this.", "This is so thoughtful of you!", "Why not?", "I just don't.", "That's rude!"}
        };
    }
    else if (relation_ship == "非常差") {
        return {
            {"I'm busy, I don't have time for you.", "Okay", "How have you been?", "Can we talk?", "Sure"},
            {"Why are you bothering me?", "Just wanted to check in.", "I don't care.", "Leave me alone!", "Okay"},
            {"You are a baby dragon, you are a baby dragon.", "I am not.", "Okay", "Alright", "Whatever"},
            {"I don't want to talk to you.", "Why not?", "I just don't.", "That's rude!", "Okay"}
        };
    }
    else if (relation_ship == "一般") {
        return {
            {"Hello, is there something you need?", "Nothing, just wanted to ask you.", "How have you been?", "Can we talk?", "Sure"},
            {"How have you been?", "Pretty good, just busy with work.", "What about you?", "Let's catch up!", "Okay"},
            {"Can we talk?", "Sure, but I have limited time.", "What do you want to discuss?", "I'm all ears.", "Okay"},
            {"What do you think about our relationship?", "It's average, nothing special.", "I hope it improves.", "Let's work on it.", "Okay"}
        };
    }
    else if (relation_ship == "友好") {
        return {
            {"Hey, how's it going?", "I'm good, thanks!", "What about you?", "Let's hang out!", "Sure"},
            {"What are you up to?", "Just relaxing, you?", "Same here, want to chat?", "Sure, let's talk.", "Okay"},
            {"Can we chat for a bit?", "Absolutely, what's on your mind?", "I have some ideas.", "I'd love to hear them.", "Okay"},
            {"How do you feel about us?", "I think we're getting along well.", "I agree, it's nice.", "Let's keep it that way.", "Okay"}
        };
    }
    else if (relation_ship == "亲密") {
        return {
            {"Let's go on a date.", "Oh, I have a gift for you.", "Let's do this more often.", "Absolutely!", "Sure"},
            {"We should go on a trip together!", "That sounds amazing!", "I can't wait!", "Yeah!", "Okay"},
            {"You know how much I care about you, right?", "Of course, I feel the same way.", "You're very important to me.", "Thank you, that means a lot.", "Okay"},
            {"You're my best friend.", "And you're mine, always here for you.", "Let's stick together.", "Forever!", "Okay"}
        };
    }
    return {};
}

// 获取节日对话信息的函数
std::vector<std::vector<std::string>> getFestivalDialog ( std::string npc , std::string relation_ship ) {
    if (npc_relationship->getRelationship ( "player" , npc ) >= 80) {
        return {
            {"Here, I brought you a gift!", "I really appreciate it!", "How have you been?", "Can we talk?", "Sure"},
            {"I have something special for you.", "Thank you! That means a lot.", "I just wanted to check in.", "I don't care.", "Leave me alone!"},
            {"Look what I got for you, a little present!", "Wow, this is amazing!", "I am not.", "Okay", "Alright"},
            {"I thought you might like this.", "This is so thoughtful of you!", "Why not?", "I just don't.", "That's rude!"}
        };
    }
    else if (relation_ship == "非常差") {
        return {
            {"I'm busy, I don't have time for you.", "Okay", "How have you been?", "Can we talk?", "Sure"},
            {"Why are you bothering me?", "Just wanted to check in.", "I don't care.", "Leave me alone!", "Okay"},
            {"You are a baby dragon, you are a baby dragon.", "I am not.", "Okay", "Alright", "Whatever"},
            {"I don't want to talk to you.", "Why not?", "I just don't.", "That's rude!", "Okay"}
        };
    }
    else if (relation_ship == "一般") {
        return {
            {"Hello, is there something you need?", "Nothing, just wanted to ask you.", "How have you been?", "Can we talk?", "Sure"},
            {"How have you been?", "Pretty good, just busy with work.", "What about you?", "Let's catch up!", "Okay"},
            {"Can we talk?", "Sure, but I have limited time.", "What do you want to discuss?", "I'm all ears.", "Okay"},
            {"What do you think about our relationship?", "It's average, nothing special.", "I hope it improves.", "Let's work on it.", "Okay"}
        };
    }
    else if (relation_ship == "友好") {
        return {
            {"Hey, how's it going?", "I'm good, thanks!", "What about you?", "Let's hang out!", "Sure"},
            {"What are you up to?", "Just relaxing, you?", "Same here, want to chat?", "Sure, let's talk.", "Okay"},
            {"Can we chat for a bit?", "Absolutely, what's on your mind?", "I have some ideas.", "I'd love to hear them.", "Okay"},
            {"How do you feel about us?", "I think we're getting along well.", "I agree, it's nice.", "Let's keep it that way.", "Okay"}
        };
    }
    else if (relation_ship == "亲密") {
        return {
            {"Let's go on a date.", "Oh, I have a gift for you.", "Let's do this more often.", "Absolutely!", "Sure"},
            {"We should go on a trip together!", "That sounds amazing!", "I can't wait!", "Yeah!", "Okay"},
            {"You know how much I care about you, right?", "Of course, I feel the same way.", "You're very important to me.", "Thank you, that means a lot.", "Okay"},
            {"You're my best friend.", "And you're mine, always here for you.", "Let's stick together.", "Forever!", "Okay"}
        };
    }
    return {};
}

// 获取 NPC 大头照路径
std::string getNPCportraits ( std::string name , std::string status ) {
    std::map<std::string , std::map<std::string , std::string>> npcPortraits;

    // Abigail
    // 夏季
    npcPortraits["Abigail"]["SummerNormal"] = "Portraits/Abigail/Abigail_Beach-0.png";
    npcPortraits["Abigail"]["SummerSmile"] = "Portraits/Abigail/Abigail_Beach-1.png";
    npcPortraits["Abigail"]["SummerAngry"] = "Portraits/Abigail/Abigail_Beach-5.png";
    npcPortraits["Abigail"]["SummerAmazed"] = "Portraits/Abigail/Abigail_Beach-7.png";
    // 冬季
    npcPortraits["Abigail"]["WinterNormal"] = "Portraits/Abigail/Abigail_Winter-0.png";
    npcPortraits["Abigail"]["WinterSmile"] = "Portraits/Abigail/Abigail_Winter-1.png";
    npcPortraits["Abigail"]["WinterAngry"] = "Portraits/Abigail/Abigail_Winter-5.png";
    npcPortraits["Abigail"]["WinterAmazed"] = "Portraits/Abigail/Abigail_Winter-7.png";
    // 普通
    npcPortraits["Abigail"]["Normal"] = "Portraits/Abigail/Abigail-0.png";
    npcPortraits["Abigail"]["Smile"] = "Portraits/Abigail/Abigail-1.png";
    npcPortraits["Abigail"]["Angry"] = "Portraits/Abigail/Abigail-5.png";
    npcPortraits["Abigail"]["Amazed"] = "Portraits/Abigail/Abigail-7.png";


    // Alex
    // 夏季
    npcPortraits["Alex"]["SummerNormal"] = "Portraits/Alex/Alex_Beach-0.png";
    npcPortraits["Alex"]["SummerSmile"] = "Portraits/Alex/Alex_Beach-1.png";
    npcPortraits["Alex"]["SummerAngry"] = "Portraits/Alex/Alex_Beach-4.png";
    npcPortraits["Alex"]["SummerAmazed"] = "Portraits/Alex/Alex_Beach-6.png";
    // 冬季
    npcPortraits["Alex"]["WinterNormal"] = "Portraits/Alex/Alex_Winter-0.png";
    npcPortraits["Alex"]["WinterSmile"] = "Portraits/Alex/Alex_Winter-1.png";
    npcPortraits["Alex"]["WinterAngry"] = "Portraits/Alex/Alex_Winter-5.png";
    npcPortraits["Alex"]["WinterAmazed"] = "Portraits/Alex/Alex_Winter-7.png";
    // 普通
    npcPortraits["Alex"]["Normal"] = "Portraits/Alex/Alex-0.png";
    npcPortraits["Alex"]["Smile"] = "Portraits/Alex/Alex-1.png";
    npcPortraits["Alex"]["Angry"] = "Portraits/Alex/Alex-5.png";
    npcPortraits["Alex"]["Amazed"] = "Portraits/Alex/Alex-7.png";


    // Caroline
    // 夏季
    npcPortraits["Caroline"]["SummerNormal"] = "Portraits/Caroline/Caroline_Beach-0.png";
    npcPortraits["Caroline"]["SummerSmile"] = "Portraits/Caroline/Caroline_Beach-1.png";
    npcPortraits["Caroline"]["SummerAngry"] = "Portraits/Caroline/Caroline_Beach-2.png";
    npcPortraits["Caroline"]["SummerAmazed"] = "Portraits/Caroline/Caroline_Beach-3.png";
    // 冬季
    npcPortraits["Caroline"]["WinterNormal"] = "Portraits/Caroline/Caroline_Winter-0.png";
    npcPortraits["Caroline"]["WinterSmile"] = "Portraits/Caroline/Caroline_Winter-1.png";
    npcPortraits["Caroline"]["WinterAngry"] = "Portraits/Caroline/Caroline_Winter-2.png";
    npcPortraits["Caroline"]["WinterAmazed"] = "Portraits/Caroline/Caroline_Winter-3.png";
    // 普通
    npcPortraits["Caroline"]["Normal"] = "Portraits/Caroline/Caroline-0.png";
    npcPortraits["Caroline"]["Smile"] = "Portraits/Caroline/Caroline-1.png";
    npcPortraits["Caroline"]["Angry"] = "Portraits/Caroline/Caroline-2.png";
    npcPortraits["Caroline"]["Amazed"] = "Portraits/Caroline/Caroline-3.png";


    // Elliott
    // 夏季
    npcPortraits["Elliott"]["SummerNormal"] = "Portraits/Elliott/Elliott_Beach-0.png";
    npcPortraits["Elliott"]["SummerSmile"] = "Portraits/Elliott/Elliott_Beach-5.png";
    npcPortraits["Elliott"]["SummerAngry"] = "Portraits/Elliott/Elliott_Beach-1.png";
    npcPortraits["Elliott"]["SummerAmazed"] = "Portraits/Elliott/Elliott_Beach-8.png";
    // 冬季
    npcPortraits["Elliott"]["WinterNormal"] = "Portraits/Elliott/Elliott_Winter-0.png";
    npcPortraits["Elliott"]["WinterSmile"] = "Portraits/Elliott/Elliott_Winter-5.png";
    npcPortraits["Elliott"]["WinterAngry"] = "Portraits/Elliott/Elliott_Winter-1.png";
    npcPortraits["Elliott"]["WinterAmazed"] = "Portraits/Elliott/Elliott_Winter-8.png";
    // 普通
    npcPortraits["Elliott"]["Normal"] = "Portraits/Elliott/Elliott-0.png";
    npcPortraits["Elliott"]["Smile"] = "Portraits/Elliott/Elliott-5.png";
    npcPortraits["Elliott"]["Angry"] = "Portraits/Elliott/Elliott-1.png";
    npcPortraits["Elliott"]["Amazed"] = "Portraits/Elliott/Elliott-8.png";


    // Emily
    // 夏季
    npcPortraits["Emily"]["SummerNormal"] = "Portraits/Emily/Emily_Beach-0.png";
    npcPortraits["Emily"]["SummerSmile"] = "Portraits/Emily/Emily_Beach-1.png";
    npcPortraits["Emily"]["SummerAngry"] = "Portraits/Emily/Emily_Beach-2.png";
    npcPortraits["Emily"]["SummerAmazed"] = "Portraits/Emily/Emily_Beach-6.png";
    // 冬季
    npcPortraits["Emily"]["WinterNormal"] = "Portraits/Emily/Emily_Winter-0.png";
    npcPortraits["Emily"]["WinterSmile"] = "Portraits/Emily/Emily_Winter-1.png";
    npcPortraits["Emily"]["WinterAngry"] = "Portraits/Emily/Emily_Winter-2.png";
    npcPortraits["Emily"]["WinterAmazed"] = "Portraits/Emily/Emily_Winter-6.png";
    // 普通
    npcPortraits["Emily"]["Normal"] = "Portraits/Emily/Emily-0.png";
    npcPortraits["Emily"]["Smile"] = "Portraits/Emily/Emily-1.png";
    npcPortraits["Emily"]["Angry"] = "Portraits/Emily/Emily-2.png";
    npcPortraits["Emily"]["Amazed"] = "Portraits/Emily/Emily-6.png";
    // 如果给定 NPC 名称在映射中存在  
    if (npcPortraits.find ( name ) != npcPortraits.end ()) {
        // 返回相应状态的头像路径  
        return npcPortraits[name][status];
    }

    // 如果 NPC 名称不存在，则返回空字符串或错误信息  
    return "ERROR"; // 或者可以返回默认头像路径  
}

// 获取 Abigail 动画帧信息的函数  
std::vector<std::vector<std::string>> getAbigailAnimations (std::string season) {
    if (season == "Winter") {
        return {
        {"npc/Abigail_Winter/Abigail_Winter-8.png", "npc/Abigail_Winter/Abigail_Winter-9.png", "npc/Abigail_Winter/Abigail_Winter-10.png", "npc/Abigail_Winter/Abigail_Winter-11.png"},
        {"npc/Abigail_Winter/Abigail_Winter-0.png", "npc/Abigail_Winter/Abigail_Winter-1.png", "npc/Abigail_Winter/Abigail_Winter-2.png", "npc/Abigail_Winter/Abigail_Winter-3.png"},
        {"npc/Abigail_Winter/Abigail_Winter-14.png", "npc/Abigail_Winter/Abigail_Winter-13.png", "npc/Abigail_Winter/Abigail_Winter-14.png", "npc/Abigail_Winter/Abigail_Winter-15.png"},
        {"npc/Abigail_Winter/Abigail_Winter-4.png", "npc/Abigail_Winter/Abigail_Winter-5.png", "npc/Abigail_Winter/Abigail_Winter-6.png", "npc/Abigail_Winter/Abigail_Winter-7.png"}
        };
    }
    else if (season == "Beach") {
        return {
        {"npc/Abigail_Beach/Abigail_Beach-8.png", "npc/Abigail_Beach/Abigail_Beach-9.png", "npc/Abigail_Beach/Abigail_Beach-10.png", "npc/Abigail_Beach/Abigail_Beach-11.png"},
        {"npc/Abigail_Beach/Abigail_Beach-0.png", "npc/Abigail_Beach/Abigail_Beach-1.png", "npc/Abigail_Beach/Abigail_Beach-2.png", "npc/Abigail_Beach/Abigail_Beach-3.png"},
        {"npc/Abigail_Beach/Abigail_Beach-14.png", "npc/Abigail_Beach/Abigail_Beach-13.png", "npc/Abigail_Beach/Abigail_Beach-14.png", "npc/Abigail_Beach/Abigail_Beach-15.png"},
        {"npc/Abigail_Beach/Abigail_Beach-4.png", "npc/Abigail_Beach/Abigail_Beach-5.png", "npc/Abigail_Beach/Abigail_Beach-6.png", "npc/Abigail_Beach/Abigail_Beach-7.png"}
        };
    }
    else {
        return {
        {"npc/Abigail/Abigail-8.png", "npc/Abigail/Abigail-9.png", "npc/Abigail/Abigail-10.png", "npc/Abigail/Abigail-11.png"},
        {"npc/Abigail/Abigail-0.png", "npc/Abigail/Abigail-1.png", "npc/Abigail/Abigail-2.png", "npc/Abigail/Abigail-3.png"},
        {"npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-13.png", "npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-15.png"},
        {"npc/Abigail/Abigail-4.png", "npc/Abigail/Abigail-5.png", "npc/Abigail/Abigail-6.png", "npc/Abigail/Abigail-7.png"}
        };
    }
}

// 获取 Alex 动画信息的函数
std::vector<std::vector<std::string>> getAlexAnimations (std::string season) {
    if (season == "Winter") {
        return {
        {"npc/Alex_Winter/Alex_Winter-8.png", "npc/Alex_Winter/Alex_Winter-9.png", "npc/Alex_Winter/Alex_Winter-10.png", "npc/Alex_Winter/Alex_Winter-11.png"},
        {"npc/Alex_Winter/Alex_Winter-0.png", "npc/Alex_Winter/Alex_Winter-1.png", "npc/Alex_Winter/Alex_Winter-2.png", "npc/Alex_Winter/Alex_Winter-3.png"},
        {"npc/Alex_Winter/Alex_Winter-14.png", "npc/Alex_Winter/Alex_Winter-13.png", "npc/Alex_Winter/Alex_Winter-14.png", "npc/Alex_Winter/Alex_Winter-15.png"},
        {"npc/Alex_Winter/Alex_Winter-4.png", "npc/Alex_Winter/Alex_Winter-5.png", "npc/Alex_Winter/Alex_Winter-6.png", "npc/Alex_Winter/Alex_Winter-7.png"}
        };
    }
    else if (season == "Beach") {
        return {
        {"npc/Alex_Beach/Alex_Beach-8.png", "npc/Alex_Beach/Alex_Beach-9.png", "npc/Alex_Beach/Alex_Beach-10.png", "npc/Alex_Beach/Alex_Beach-11.png"},
        {"npc/Alex_Beach/Alex_Beach-0.png", "npc/Alex_Beach/Alex_Beach-1.png", "npc/Alex_Beach/Alex_Beach-2.png", "npc/Alex_Beach/Alex_Beach-3.png"},
        {"npc/Alex_Beach/Alex_Beach-14.png", "npc/Alex_Beach/Alex_Beach-13.png", "npc/Alex_Beach/Alex_Beach-14.png", "npc/Alex_Beach/Alex_Beach-15.png"},
        {"npc/Alex_Beach/Alex_Beach-4.png", "npc/Alex_Beach/Alex_Beach-5.png", "npc/Alex_Beach/Alex_Beach-6.png", "npc/Alex_Beach/Alex_Beach-7.png"}
        };
    }
    else {
        return {
        {"npc/Alex/Alex-8.png", "npc/Alex/Alex-9.png", "npc/Alex/Alex-10.png", "npc/Alex/Alex-11.png"},
        {"npc/Alex/Alex-0.png", "npc/Alex/Alex-1.png", "npc/Alex/Alex-2.png", "npc/Alex/Alex-3.png"},
        {"npc/Alex/Alex-14.png", "npc/Alex/Alex-13.png", "npc/Alex/Alex-14.png", "npc/Alex/Alex-15.png"},
        {"npc/Alex/Alex-4.png", "npc/Alex/Alex-5.png", "npc/Alex/Alex-6.png", "npc/Alex/Alex-7.png"}
        };
    }
}

// 获取 Caroline 动画信息的函数
std::vector<std::vector<std::string>> getCarolineAnimations (std::string season) {
    if (season == "Winter") {
        return {
        {"npc/Caroline_Winter/Caroline_Winter-8.png", "npc/Caroline_Winter/Caroline_Winter-9.png", "npc/Caroline_Winter/Caroline_Winter-10.png", "npc/Caroline_Winter/Caroline_Winter-11.png"},
        {"npc/Caroline_Winter/Caroline_Winter-0.png", "npc/Caroline_Winter/Caroline_Winter-1.png", "npc/Caroline_Winter/Caroline_Winter-2.png", "npc/Caroline_Winter/Caroline_Winter-3.png"},
        {"npc/Caroline_Winter/Caroline_Winter-14.png", "npc/Caroline_Winter/Caroline_Winter-13.png", "npc/Caroline_Winter/Caroline_Winter-14.png", "npc/Caroline_Winter/Caroline_Winter-15.png"},
        {"npc/Caroline_Winter/Caroline_Winter-4.png", "npc/Caroline_Winter/Caroline_Winter-5.png", "npc/Caroline_Winter/Caroline_Winter-6.png", "npc/Caroline_Winter/Caroline_Winter-7.png"}
        };
    }
    else if (season == "Beach") {
        return {
        {"npc/Caroline_Beach/Caroline_Beach-8.png", "npc/Caroline_Beach/Caroline_Beach-9.png", "npc/Caroline_Beach/Caroline_Beach-10.png", "npc/Caroline_Beach/Caroline_Beach-11.png"},
        {"npc/Caroline_Beach/Caroline_Beach-0.png", "npc/Caroline_Beach/Caroline_Beach-1.png", "npc/Caroline_Beach/Caroline_Beach-2.png", "npc/Caroline_Beach/Caroline_Beach-3.png"},
        {"npc/Caroline_Beach/Caroline_Beach-14.png", "npc/Caroline_Beach/Caroline_Beach-13.png", "npc/Caroline_Beach/Caroline_Beach-14.png", "npc/Caroline_Beach/Caroline_Beach-15.png"},
        {"npc/Caroline_Beach/Caroline_Beach-4.png", "npc/Caroline_Beach/Caroline_Beach-5.png", "npc/Caroline_Beach/Caroline_Beach-6.png", "npc/Caroline_Beach/Caroline_Beach-7.png"}
        };
    }
    else {
        return {
        {"npc/Caroline/Caroline-8.png", "npc/Caroline/Caroline-9.png", "npc/Caroline/Caroline-10.png", "npc/Caroline/Caroline-11.png"},
        {"npc/Caroline/Caroline-0.png", "npc/Caroline/Caroline-1.png", "npc/Caroline/Caroline-2.png", "npc/Caroline/Caroline-3.png"},
        {"npc/Caroline/Caroline-14.png", "npc/Caroline/Caroline-13.png", "npc/Caroline/Caroline-14.png", "npc/Caroline/Caroline-15.png"},
        {"npc/Caroline/Caroline-4.png", "npc/Caroline/Caroline-5.png", "npc/Caroline/Caroline-6.png", "npc/Caroline/Caroline-7.png"}
        };
    }
}

// 获取 Elliott 动画信息的函数
std::vector<std::vector<std::string>> getElliottAnimations (std::string season) {
    if (season == "Winter") {
        return {
        {"npc/Elliott_Winter/Elliott_Winter-8.png", "npc/Elliott_Winter/Elliott_Winter-9.png", "npc/Elliott_Winter/Elliott_Winter-10.png", "npc/Elliott_Winter/Elliott_Winter-11.png"},
        {"npc/Elliott_Winter/Elliott_Winter-0.png", "npc/Elliott_Winter/Elliott_Winter-1.png", "npc/Elliott_Winter/Elliott_Winter-2.png", "npc/Elliott_Winter/Elliott_Winter-3.png"},
        {"npc/Elliott_Winter/Elliott_Winter-14.png", "npc/Elliott_Winter/Elliott_Winter-13.png", "npc/Elliott_Winter/Elliott_Winter-14.png", "npc/Elliott_Winter/Elliott_Winter-15.png"},
        {"npc/Elliott_Winter/Elliott_Winter-4.png", "npc/Elliott_Winter/Elliott_Winter-5.png", "npc/Elliott_Winter/Elliott_Winter-6.png", "npc/Elliott_Winter/Elliott_Winter-7.png"}
        };
    }
    else if (season == "Beach") {
        return {
        {"npc/Elliott_Beach/Elliott_Beach-8.png", "npc/Elliott_Beach/Elliott_Beach-9.png", "npc/Elliott_Beach/Elliott_Beach-10.png", "npc/Elliott_Beach/Elliott_Beach-11.png"},
        {"npc/Elliott_Beach/Elliott_Beach-0.png", "npc/Elliott_Beach/Elliott_Beach-1.png", "npc/Elliott_Beach/Elliott_Beach-2.png", "npc/Elliott_Beach/Elliott_Beach-3.png"},
        {"npc/Elliott_Beach/Elliott_Beach-14.png", "npc/Elliott_Beach/Elliott_Beach-13.png", "npc/Elliott_Beach/Elliott_Beach-14.png", "npc/Elliott_Beach/Elliott_Beach-15.png"},
        {"npc/Elliott_Beach/Elliott_Beach-4.png", "npc/Elliott_Beach/Elliott_Beach-5.png", "npc/Elliott_Beach/Elliott_Beach-6.png", "npc/Elliott_Beach/Elliott_Beach-7.png"}
        };
    }
    else {
        return {
        {"npc/Elliott/Elliott-8.png", "npc/Elliott/Elliott-9.png", "npc/Elliott/Elliott-10.png", "npc/Elliott/Elliott-11.png"},
        {"npc/Elliott/Elliott-0.png", "npc/Elliott/Elliott-1.png", "npc/Elliott/Elliott-2.png", "npc/Elliott/Elliott-3.png"},
        {"npc/Elliott/Elliott-14.png", "npc/Elliott/Elliott-13.png", "npc/Elliott/Elliott-14.png", "npc/Elliott/Elliott-15.png"},
        {"npc/Elliott/Elliott-4.png", "npc/Elliott/Elliott-5.png", "npc/Elliott/Elliott-6.png", "npc/Elliott/Elliott-7.png"}
        };
    }
}

// 获取 Emily 动画信息的函数
std::vector<std::vector<std::string>> getEmilyAnimations (std::string season) {
    if (season == "Winter") {
        return {
        {"npc/Emily_Winter/Emily_Winter-8.png", "npc/Emily_Winter/Emily_Winter-9.png", "npc/Emily_Winter/Emily_Winter-10.png", "npc/Emily_Winter/Emily_Winter-11.png"},
        {"npc/Emily_Winter/Emily_Winter-0.png", "npc/Emily_Winter/Emily_Winter-1.png", "npc/Emily_Winter/Emily_Winter-2.png", "npc/Emily_Winter/Emily_Winter-3.png"},
        {"npc/Emily_Winter/Emily_Winter-14.png", "npc/Emily_Winter/Emily_Winter-13.png", "npc/Emily_Winter/Emily_Winter-14.png", "npc/Emily_Winter/Emily_Winter-15.png"},
        {"npc/Emily_Winter/Emily_Winter-4.png", "npc/Emily_Winter/Emily_Winter-5.png", "npc/Emily_Winter/Emily_Winter-6.png", "npc/Emily_Winter/Emily_Winter-7.png"}
        };
    }
    else if (season == "Beach") {
        return {
        {"npc/Emily_Beach/Emily_Beach-8.png", "npc/Emily_Beach/Emily_Beach-9.png", "npc/Emily_Beach/Emily_Beach-10.png", "npc/Emily_Beach/Emily_Beach-11.png"},
        {"npc/Emily_Beach/Emily_Beach-0.png", "npc/Emily_Beach/Emily_Beach-1.png", "npc/Emily_Beach/Emily_Beach-2.png", "npc/Emily_Beach/Emily_Beach-3.png"},
        {"npc/Emily_Beach/Emily_Beach-14.png", "npc/Emily_Beach/Emily_Beach-13.png", "npc/Emily_Beach/Emily_Beach-14.png", "npc/Emily_Beach/Emily_Beach-15.png"},
        {"npc/Emily_Beach/Emily_Beach-4.png", "npc/Emily_Beach/Emily_Beach-5.png", "npc/Emily_Beach/Emily_Beach-6.png", "npc/Emily_Beach/Emily_Beach-7.png"}
        };
    }
    else {
        return {
        {"npc/Emily/Emily-8.png", "npc/Emily/Emily-9.png", "npc/Emily/Emily-10.png", "npc/Emily/Emily-11.png"},
        {"npc/Emily/Emily-0.png", "npc/Emily/Emily-1.png", "npc/Emily/Emily-2.png", "npc/Emily/Emily-3.png"},
        {"npc/Emily/Emily-14.png", "npc/Emily/Emily-13.png", "npc/Emily/Emily-14.png", "npc/Emily/Emily-15.png"},
        {"npc/Emily/Emily-4.png", "npc/Emily/Emily-5.png", "npc/Emily/Emily-6.png", "npc/Emily/Emily-7.png"}
        };
    }
}

// 获取节日时的 Fisherman 的图函数
std::vector<std::string> getFisherman ( std::string season ) {
    if (season == "Summer") {
        return{
            "npc/Assorted_Fishermen/Assorted_Fishermen-0.png","npc/Assorted_Fishermen/Assorted_Fishermen-1.png",
            "npc/Assorted_Fishermen/Assorted_Fishermen-2.png","npc/Assorted_Fishermen/Assorted_Fishermen-3.png"
        };
    }
    else if (season == "Winter") {
        return{
            "npc/Assorted_Fishermen_Winter/Assorted_Fishermen_Winter-0.png","npc/Assorted_Fishermen_Winter/Assorted_Fishermen_Winter-1.png",
            "npc/Assorted_Fishermen_Winter/Assorted_Fishermen_Winter-2.png","npc/Assorted_Fishermen_Winter/Assorted_Fishermen_Winter-3.png"
        };
    }
    return {};
}