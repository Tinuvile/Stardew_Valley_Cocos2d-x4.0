/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 允许任何人免费使用该软件，包括修改、合并、发布、分发、再许可以及销售该软件的副本，前提是所有副本或者重要部分都必须包含本版权声明和许可声明。

 该软件按"原样"提供，不附带任何形式的保证，包括但不限于对适销性、特定用途适用性和不侵权的保证。在任何情况下，作者或版权持有者均不对因使用该软件或与该软件相关的任何索赔、损害或其他责任承担责任，无论是合同、侵权行为或其他方式。
 ****************************************************************************/

#include "AppDelegate.h"
//#include "GameBeginUI.h"
#include "Player.h"
//#include "Town.h"
#include "Barn.h"
//#include "supermarket.h"
//#include "CreateCharacterUI.h"

 // #define USE_AUDIO_ENGINE 1   // 如果需要使用音频引擎，可以取消注释这一行

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // 如果启用了音频引擎，则引入音频引擎的头文件
using namespace cocos2d::experimental;  // 使用音频引擎的命名空间
#endif

USING_NS_CC;  // 使用cocos2d的命名空间

/******************************** 全局变量声明区 ****************************************/
// 在此文件中定义并初始化全局变量
int remainingTime = 0;
int day = 1;
int GoldAmount = 4000;
bool frombed = false;
bool IsNextDay = false;

Crop wheat ( "wheat" , "crop/wheat1.png" , "crop/wheat2.png" , "crop/wheat3.png" , "All" , Phase::SEED , 50 , 0 , false , 4 );
Crop corn ( "corn" , "crop/corn1.png" , "crop/corn2.png" , "crop/corn3.png" , "Spring" , Phase::SEED , 50 , 0 , false , 6 );
Crop potato ( "potato" , "crop/potato1.png" , "crop/potato2.png" , "crop/potato3.png" , "All" , Phase::SEED , 30 , 0 , false , 4 );
Crop pumpkin ( "pumpkin" , "crop/pumpkin1.png" , "crop/pumpkin2.png" , "crop/pumpkin3.png" , "Autumn" , Phase::SEED , 70 , 0 , false , 6 );
Crop blueberry ( "blueberry" , "crop/blueberry1.png" , "crop/blueberry2.png" , "crop/blueberry3.png" , "Summer" , Phase::SEED , 100 , 0 , false , 7 );

std::string Season = "Spring";
std::map<std::string , int> season;
std::vector<std::shared_ptr<Crop>> Crop_information;
std::vector<std::shared_ptr<Ore>> Ore_information;
std::vector<std::shared_ptr<Tree>> Tree_information;
std::map<std::string , Crop> cropbasicinformation;
std::map<std::pair<std::string , Vec2> , bool> T_lastplace;
std::map<std::pair<std::string , Vec2> , bool> F_lastplace;
std::map<std::pair<std::string , Vec2>, bool> W_lastplace;

// 全局指针变量定义
Player* player1 = nullptr;
mini_bag* miniBag = nullptr;
Town* town = nullptr;
supermarket* seedshop = nullptr;
farm* Farm = nullptr;
std::map<std::pair<std::string , Vec2> , bool> T_lastplace;

Inventory* inventory = new Inventory ();
NpcRelationship* npc_relationship = new NpcRelationship();
std::vector<std::pair<Rect , bool>> barn_space;
std::vector<Livestock*> livestocks;
SkillTree* skillTree = new SkillTree ();
/****************************************************************************************/


AppDelegate::AppDelegate() {
    // 构造函数：AppDelegate构造时会调用
}

AppDelegate::~AppDelegate() {
    // 析构函数：程序结束时会调用
#if USE_AUDIO_ENGINE
    AudioEngine::end();  // 如果使用了音频引擎，停止音频引擎
#endif
}

// 初始化 OpenGL 上下文属性
void AppDelegate::initGLContextAttrs() {
    // 设置OpenGL上下文的属性：红、绿、蓝、透明通道的位深，深度、模板和多重采样
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };  // 设置 OpenGL 上下文的颜色和深度缓冲等属性

    GLView::setGLContextAttrs(glContextAttrs);  // 将设置的上下文属性应用到 GLView
}

// 如果想通过包管理器安装更多包，不要修改或删除这个函数
static int register_all_packages() {
    return 0;  // 标志位，用于包管理器
}

// 应用启动完成后调用
bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化 Director（导演类，用于管理场景和绘制）
    auto director = Director::getInstance();  // 获取 Director 实例
    auto glview = director->getOpenGLView();  // 获取 OpenGL 视图
    
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Startdew", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Startdew");
#endif
        director->setOpenGLView(glview);
    }

    // 打开 FPS 显示
    director->setDisplayStats(true);  // 显示帧率统计信息

    // 设置帧率。默认值为 1.0/60，即 60 FPS
    director->setAnimationInterval(1.0f / 60);  // 设置动画帧率为 60 FPS

    // 设置设计分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    director->setContentScaleFactor(1.0f);

    register_all_packages();  // 注册所有的包

    runScene(director);

    return true;  // 返回成功
}

// 切换场景的函数
void AppDelegate::runScene(cocos2d::Director* director) {

    Initialize ();
    player1 = Player::create();

    // 获取当前视图的可见大小和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();  // 获取屏幕可视区域的大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // 获取屏幕原点的位置（左下角）
  
    std::pair<std::string, Vec2> key = { "initiation",Vec2(350,350)};
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2(230,470) };
    T_lastplace.insert(std::make_pair(key, false));

    //运行海滩场景
    auto beach = Beach::create ();
    director->runWithScene ( beach );

    // 运行家的场景
    /*auto test = Myhouse::create();
    director->runWithScene(test); */

    // 运行小镇的场景
    //auto test = Town::create();
    //director->runWithScene(test);

    // 运行商店的场景
    /*auto test = supermarket::create();
    director->runWithScene(test);*/

    // 运行Cave
    //auto test = Cave::create();
    //director->runWithScene(test);

    // 运行Beach
    //auto test = Beach::create();
    //director->runWithScene(test);
    
    // 运行森林
    auto test = Forest::create();
    director->runWithScene(test);

    //开局UI运行
    //director->runWithScene ( BeginScene::create () );
    //创建人物界面运行
    //director->runWithScene ( CreateCharacter::create () );
}

void AppDelegate::Initialize () {
    // 创建人物
    player1 = Player::create ();
    // 初始化存储作物信息的数组
    //cropbasicinformation.insert ( { "wheat", WHEAT } );
    //cropbasicinformation.insert ( { "corn", CORN } );
    //cropbasicinformation.insert ( { "potato", POTATO } );
    //cropbasicinformation.insert ( { "pumpkin", PUMPKIN } );
    //cropbasicinformation.insert ( { "blueberry", BLUEBERRY } );
    // 初始化小镇各地址坐标
    std::pair<std::string , Vec2> key = { "initiation",Vec2 (-925,650) };
    T_lastplace.insert ( std::make_pair ( key , true ) );
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert ( std::make_pair ( key , false ) );
    key = { "forest",Vec2(-925,650) };
    T_lastplace.insert(std::make_pair(key, false));

    // 初始化农场各地址坐标
    key = { "initiation",Vec2(70, 920) };
    F_lastplace.insert(std::make_pair(key, true));
    key = { "myhouse",Vec2(70, 920) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "barn",Vec2(20, 170) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "forest",Vec2(-740,-330) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "cave",Vec2(635, 1185) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "beach",Vec2(500, -750) };
    F_lastplace.insert(std::make_pair(key, false));

    // 初始化森林各地址坐标
    key = { "initiation",Vec2(1150,2650) };
    W_lastplace.insert(std::make_pair(key, true));
    key = { "town",Vec2(2600, 1900) };
    W_lastplace.insert(std::make_pair(key, false));
    key = { "farm",Vec2(1150, 2650) };
    W_lastplace.insert(std::make_pair(key, false));

    // 初始化季节
    season.insert ( { "Spring", 1 } );
    season.insert ( { "Summer", 2 } );
    season.insert ( { "Autumn", 3 } );
    season.insert ( { "Winter", 4 } );
}



// 当应用程序进入后台时调用
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();  // 停止动画

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();  // 暂停所有音频（如果启用了音频引擎）
#endif
}

// 当应用程序重新进入前台时调用
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();  // 恢复动画

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();  // 恢复所有音频（如果启用了音频引擎）
#endif
}
