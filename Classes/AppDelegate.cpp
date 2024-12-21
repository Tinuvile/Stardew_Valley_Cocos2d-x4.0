/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 允许任何人免费使用该软件，包括修改、合并、发布、分发、再许可以及销售该软件的副本，前提是所有副本或者重要部分都必须包含本版权声明和许可声明。

 该软件按"原样"提供，不附带任何形式的保证，包括但不限于对适销性、特定用途适用性和不侵权的保证。在任何情况下，作者或版权持有者均不对因使用该软件或与该软件相关的任何索赔、损害或其他责任承担责任，无论是合同、侵权行为或其他方式。
 ****************************************************************************/

#include "AppDelegate.h"
#include "GameBeginUI.h"
#include "Player.h"
//#include "Town.h"
#include "Barn.h"
//#include "supermarket.h"
#include "CreateCharacterUI.h"

// #define USE_AUDIO_ENGINE 1   // 如果需要使用音频引擎，可以取消注释这一行

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // 如果启用了音频引擎，则引入音频引擎的头文件
// using namespace cocos2d::experimental;  // 使用音频引擎的命名空间
#endif

USING_NS_CC;  // 使用cocos2d的命名空间

/******************************** 全局变量声明区 ****************************************/
// 在此文件中定义并初始化全局变量
int remainingTime = 10800;
int day = 1;
int GoldAmount = 4000;
int strength = 100;
bool frombed = true;
bool IsNextDay = false;
bool IsSleep = true;
bool GoldMaskfirst = true;
bool RainBowfirst = true;

Crop wheat ( "wheat" , "Crops/wheat1.png" , "Crops/wheat2.png" , "Crops/wheat3.png" , "All" , Phase::SEED , 50 , 0 , false , 4 );
Crop corn ( "corn" , "Crops/corn1.png" , "Crops/corn2.png" , "Crops/corn3.png" , "Spring" , Phase::SEED , 50 , 0 , false , 6 );
Crop potato ( "potato" , "Crops/potato1.png" , "Crops/potato2.png" , "Crops/potato3.png" , "All" , Phase::SEED , 30 , 0 , false , 2 );
Crop pumpkin ( "pumpkin" , "Crops/pumpkin1.png" , "Crops/pumpkin2.png" , "Crops/pumpkin3.png" , "Autumn" , Phase::SEED , 70 , 0 , false , 6 );
Crop blueberry ( "blueberry" , "Crops/blueberry1.png" , "Crops/blueberry2.png" , "Crops/blueberry3.png" , "Summer" , Phase::SEED , 100 , 0 , false , 7 );

std::string Season = "Spring";
std::string Weather = "Rainy";
std::string Festival = "Fishing Festival";
std::map<std::string , int> season;
std::vector<std::shared_ptr<Crop>> Crop_information;
std::vector<std::shared_ptr<Ore>> Ore_information;
std::vector<std::shared_ptr<Tree>> Tree_information;
std::map<std::string , Crop> cropbasicinformation;
std::map<std::pair<std::string , Vec2> , bool> T_lastplace;
std::map<std::pair<std::string , Vec2> , bool> F_lastplace;
std::map<std::pair<std::string , Vec2>, bool> W_lastplace;

std::string protagonistName = "player";
std::string FarmName = "An ordinary farm";

// 全局指针变量定义
Player* player1 = nullptr;
mini_bag* miniBag = nullptr;
Timesystem* TimeUI = nullptr;

Inventory* inventory = new Inventory ();

NpcRelationship* npc_relationship = new NpcRelationship();

std::vector<std::pair<Rect , bool>> barn_space;
std::vector<Livestock*> livestocks;
SkillTree* skill_tree = new SkillTree ();

// 创建任务管理器
TaskManagement* taskManager = new TaskManagement();
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

    // set the background music and continuously play it.
    auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/01 - Stardew Valley Overture.mp3" , true );

    return true;  // 返回成功
}

// 切换场景的函数
void AppDelegate::runScene(cocos2d::Director* director) {
    Initialize ();
    
    // 获取当前视图的可见大小和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();  // 获取屏幕可视区域的大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // 获取屏幕原点的位置（左下角）
  

    std::pair<std::string , Vec2> key = { "initiation",Vec2 ( 350,350 ) };
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert(std::make_pair(key, false));

    // 运行农场
    //auto farm = farm::create ();
    //director->runWithScene ( farm );

    //运行海滩场景
    // auto beach = Beach::create ();
    // director->runWithScene ( beach );

    // 运行家的场景
   /*  auto test = Myhouse::create();
     director->runWithScene(test); */

    // 运行小镇的场景
     //auto test = Town::create ();
     //director->runWithScene(test);

    // 运行商店的场景
    //auto test = supermarket::create();
    //director->runWithScene(test);

    // 运行Cave
     //auto test = Cave::create();
     //director->runWithScene(test);

    // 运行Beach
    // auto test = Beach::create();
    // director->runWithScene(test);
    
    // 运行森林
    /* auto test = Forest::create();
     director->runWithScene(test);*/

     // 运行畜棚
     // auto test = Barn::create();
     // director->runWithScene(test);

    //开局UI运行
    director->runWithScene ( BeginScene::create () );
    //创建人物界面运行
    // director->runWithScene ( CreateCharacter::create () );
}

void AppDelegate::Initialize () {

    // 初始化存储作物信息的数组
    cropbasicinformation.insert({ "Wheat_Seeds", wheat });
    cropbasicinformation.insert({ "Corn_Seeds", corn });
    cropbasicinformation.insert({ "Potato_Seeds", potato });
    cropbasicinformation.insert({ "Pumpkin_Seeds", pumpkin });
    cropbasicinformation.insert({ "Blueberry_Seeds", blueberry });

    // 初始化宝石信息
    Ore Ruby("Ruby", "Ore/Ruby1.png", "Ore/Ruby2.png", 3, 3, Vec2(350, 500));                   // 红宝石
    Ore_information.push_back(Ruby.GetOreCopy());
    Ruby.position = Vec2(950, 750);
    Ore_information.push_back(Ruby.GetOreCopy());

    Ore Amethyst("Amethyst", "Ore/Amethyst1.png", "Ore/Amethyst2.png", 5, 5, Vec2(800, 250));   // 紫宝石
    Ore_information.push_back(Amethyst.GetOreCopy());
    Amethyst.position = Vec2(750, 850);
    Ore_information.push_back(Amethyst.GetOreCopy());

    Ore Emerald("Emerald", "Ore/Emerald1.png", "Ore/Emerald2.png", 5, 5, Vec2(900, 150));       // 绿宝石
    Ore_information.push_back(Emerald.GetOreCopy());
    Emerald.position = Vec2(1250, 350);
    Ore_information.push_back(Emerald.GetOreCopy());

    // 初始化树木信息
    Tree tree("tree", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 15, 5, Vec2(50, 950));
    Tree_information.push_back(tree.GetTreeCopy());
    tree.position = Vec2(-400, 700);
    Tree_information.push_back(tree.GetTreeCopy());
    tree.position = Vec2(800, 1250);
    Tree_information.push_back(tree.GetTreeCopy());
    tree.position = Vec2(900, 1650);
    Tree_information.push_back(tree.GetTreeCopy());
    tree.position = Vec2(1300, 1550);
    Tree_information.push_back(tree.GetTreeCopy());

    // 初始化小镇各地址坐标
    std::pair<std::string , Vec2> key = { "initiation",Vec2 (-840,-340) };
    T_lastplace.insert ( std::make_pair ( key , true ) );
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert ( std::make_pair ( key , false ) );
    key = { "forest",Vec2(-840,-340) };
    T_lastplace.insert(std::make_pair(key, false));
    key = { "beach",Vec2(500, -750) };
    T_lastplace.insert(std::make_pair(key, false));

    // 初始化农场各地址坐标
    key = { "initiation",Vec2(70, 920) };
    F_lastplace.insert(std::make_pair(key, true));
    key = { "myhouse",Vec2(70, 920) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "barn",Vec2(20, 170) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "forest",Vec2(740,-30) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "cave",Vec2(635, 1185) };
    F_lastplace.insert(std::make_pair(key, false));

    // 初始化森林各地址坐标
    key = { "initiation",Vec2(1150,2650) };
    W_lastplace.insert(std::make_pair(key, true));
    key = { "town",Vec2(2600, 1900) };
    W_lastplace.insert(std::make_pair(key, false));
    key = { "farm",Vec2(1150, 2650) };
    W_lastplace.insert(std::make_pair(key, false));

    // 创建任务  
    TaskManagement::Task task1 (
        "Fetch the Amethyst" ,
        TaskManagement::NPC_TASK ,
        "Retrieve the Amethyst for Abigail." , // 详细说明  
        "Spring" , // 初始日期  
        "Summer"  // 截至日期  
    );
    task1.npcName = "Abigail"; // 发布任务的 NPC 名字  
    task1.requiredItems.push_back ( Bean_Starter ); // 需要的物品  
    task1.rewardCoins = 500; // 奖励金币  
    task1.relationshipPoints = 10; // NPC 好感度  

    TaskManagement::Task task2 (
        "Collect Emerald" ,
        TaskManagement::SYSTEM_TASK ,
        "Collect an Emerald for system tasks." , // 详细说明  
        "Summer" , // 初始日期  
        "Autumn"  // 截至日期  
    );
    task2.requiredItems.push_back ( emerald ); // 需要的物品  
    task2.rewardCoins = 30; // 奖励金币  

    TaskManagement::Task task3 (
        "Festival Gathering" ,
        TaskManagement::FESTIVAL_TASK ,
        "Join the festival and collect special items." , // 详细说明  
        "Winter" , // 初始日期  
        "Summer"  // 截至日期  
    );
    task3.specialRewards.push_back ( Gold_Hoe );   // 特殊奖励  
    task3.relationshipPoints = 5; // 与所有人的好感度  

    // 将任务添加到任务管理器  
    taskManager->createTask ( task1 );
    taskManager->createTask ( task2 );
    taskManager->createTask ( task3 );

    // taskManager->AddAcceptTask ( task1 );

    //初始化Barn内可放置家畜矩阵
    barn_space.push_back(std::make_pair(Rect(685.714294, 213.333328, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(800.000000, 213.333328, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(914.285706, 213.333328, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(1142.857178, 213.333328, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(685.714294, 426.666656, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(800.000000, 426.666656, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(914.285706, 426.666656, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(1142.857178, 426.666656, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(685.714294, 640.000000, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(800.000000, 640.000000, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(914.285706, 640.000000, 114.285713, 106.666664), false));
    barn_space.push_back(std::make_pair(Rect(1142.857178, 640.000000, 114.285713, 106.666664), false));

    // 初始化季节
    season.insert ( { "Spring", 1 } );
    season.insert ( { "Summer", 2 } );
    season.insert ( { "Autumn", 3 } );
    season.insert ( { "Winter", 4 } );

    // 创建任务  
    //TaskManagement::Task task1 ( "Fetch the Amethyst" , TaskManagement::NPC_TASK );
    //task1.npcName = "Abigail"; // 发布任务的 NPC 名字  
    //task1.requiredItems.push_back ( amethyst ); // 需要的物品  
    //task1.rewardCoins = 500; // 奖励金币  
    //task1.relationshipPoints = 10; // NPC 好感度  

    //TaskManagement::Task task2 ( "Collect Emerald" , TaskManagement::SYSTEM_TASK );
    //task2.requiredItems.push_back ( emerald ); // 需要的物品  
    //task2.rewardCoins = 30; // 奖励金币  

    //TaskManagement::Task task3 ( "Festival Gathering" , TaskManagement::FESTIVAL_TASK );
    //task3.specialRewards.push_back ( Gold_Hoe );   // 特殊奖励  
    //task3.relationshipPoints = 5; // 与所有人的好感度  

    //// 将任务添加到任务管理器  
    //taskManager->createTask ( task1 );
    //taskManager->createTask ( task2 );
    //taskManager->createTask ( task3 );
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
