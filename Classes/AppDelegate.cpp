/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 允许任何人免费使用该软件，包括修改、合并、发布、分发、再许可以及销售该软件的副本，前提是所有副本或者重要部分都必须包含本版权声明和许可声明。

 该软件按"原样"提供，不附带任何形式的保证，包括但不限于对适销性、特定用途适用性和不侵权的保证。在任何情况下，作者或版权持有者均不对因使用该软件或与该软件相关的任何索赔、损害或其他责任承担责任，无论是合同、侵权行为或其他方式。
 ****************************************************************************/

#include "AppDelegate.h"

 // #define USE_AUDIO_ENGINE 1   // 如果需要使用音频引擎，可以取消注释这一行

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // 如果启用了音频引擎，则引入音频引擎的头文件
using namespace cocos2d::experimental;  // 使用音频引擎的命名空间
#endif

USING_NS_CC;  // 使用cocos2d的命名空间

// 在此文件中定义并初始化全局变量
int remainingTime = 0;
int day = 1;
bool frombed = false;
bool IsNextDay = false;
CropBasicInformation WHEAT("crop/wheat1.png", "crop/wheat2.png", "crop/wheat3.png", "All");
CropBasicInformation CORN("crop/corn1.png", "crop/corn2.png", "crop/corn3.png", "Spring");
CropBasicInformation POTATO("crop/potato1.png", "crop/potato2.png", "crop/potato3.png", "All");
CropBasicInformation PUMPKIN("crop/pumpkin1.png", "crop/pumpkin2.png", "crop/pumpkin3.png", "Summer");
CropBasicInformation BLUEBERRY("crop/blueberry1.png", "crop/blueberry2.png", "crop/blueberry3.png", "Autumn");

Crop wheat("wheat", "crop/wheat1.png", "crop/wheat2.png", "crop/wheat3.png", "All", Phase::SEED, 50, 0, false, 4);
Crop corn("corn", "crop/corn1.png", "crop/corn2.png", "crop/corn3.png", "Spring", Phase::SEED, 50, 0, false, 6);
Crop potato("potato", "crop/potato1.png", "crop/potato2.png", "crop/potato3.png", "All", Phase::SEED, 30, 0, false, 4);
Crop pumpkin("pumpkin", "crop/pumpkin1.png", "crop/pumpkin2.png", "crop/pumpkin3.png", "Autumn", Phase::SEED, 70, 0, false, 6);
Crop blueberry("blueberry", "crop/blueberry1.png", "crop/blueberry2.png", "crop/blueberry3.png", "Summer", Phase::SEED, 100, 0, false, 7);

std::string Season = "Spring";
std::map<std::string, int> season;
std::vector<std::shared_ptr<Crop>> Crop_information;
std::vector<std::shared_ptr<Ore>> Ore_information;
std::vector<std::shared_ptr<Tree>> Tree_information;
std::map<std::string, Crop> cropbasicinformation;
std::map<std::pair<std::string, Vec2>, bool> T_lastplace;
std::map<std::pair<std::string, Vec2>, bool> F_lastplace;

// 全局指针变量定义
Player* player1 = nullptr;
Town* town = nullptr;
supermarket* seedshop = nullptr;
farm* Farm = nullptr;
Myhouse* myhouse = nullptr;


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
    
    Initialize();

    // 获取当前视图的可见大小和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();  // 获取屏幕可视区域的大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // 获取屏幕原点的位置（左下角）
  
    std::pair<std::string, Vec2> key = { "initiation",Vec2(350,350)};
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2(230,470) };
    T_lastplace.insert(std::make_pair(key, false));
    director->runWithScene ( Town::create () );
    // director->runWithScene ( supermarket::create () );

    // 测试运行畜棚
    /*auto test = Barn::create();
    director->runWithScene(test);*/

    // 测试运行矿洞
    auto test = Cave::create();
    director->runWithScene(test);

    // 测试运行商店
    /*auto test = supermarket::create();
    director->runWithScene(test);*/

    // 测试运行城镇
    /*auto test = Town::create();
    director->runWithScene(test);*/

    // 测试运行森林
    /*auto test = Forest::create();
    director->runWithScene(test);*/

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

void AppDelegate::Initialize() {

    // 创建人物
    player1 = Player::create();

    // 初始化矿石信息
    Ore RUBY("Ruby", "Ore/Ruby1.png", "Ore/Ruby2.png", 10, 3, Vec2(500 ,650));
    Ore_information.push_back(RUBY.GetOreCopy());
    Ore_information.back()->position = Vec2(500, 750);
    Ore_information.push_back(RUBY.GetOreCopy());
    Ore_information.back()->position = Vec2(450, 550);
    Ore_information.push_back(RUBY.GetOreCopy());
    Ore_information.back()->position = Vec2(1150, 450);
    Ore Emerald("Emerald", "Ore/Emerald1.png", "Ore/Emerald2.png", 10, 3, Vec2(500, 650));
    Ore_information.push_back(Emerald.GetOreCopy());
    Ore_information.back()->position = Vec2(700, 950);
    Ore_information.push_back(Emerald.GetOreCopy());
    Ore_information.back()->position = Vec2(350, 350);
    Ore_information.push_back(Emerald.GetOreCopy());
    Ore_information.back()->position = Vec2(900, 300);
    Ore Amethyst("Amethyst", "Ore/Amethyst1.png", "Ore/Amethyst2.png", 10, 3, Vec2(500, 650));
    Ore_information.push_back(Amethyst.GetOreCopy());
    Ore_information.back()->position = Vec2(550, 650);
    Ore_information.push_back(Amethyst.GetOreCopy());
    Ore_information.back()->position = Vec2(950, 950);
    Ore_information.push_back(Amethyst.GetOreCopy());
    Ore_information.back()->position = Vec2(1150, 750);

    // 初始化树木信息
    Tree temp1("tree1", "Tree/tree1.png", "Tree/tree2.png","Tree/tree3.png", 10, 3, Vec2(1250, 1700));
    Tree_information.push_back(temp1.GetTreeCopy());
    Tree temp2("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(-400, 850));
    Tree_information.push_back(temp2.GetTreeCopy());
    Tree temp3("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(0, 900));
    Tree_information.push_back(temp3.GetTreeCopy());
    Tree temp4("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(1200, 1200));
    Tree_information.push_back(temp4.GetTreeCopy());
    Tree temp5("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(700, 1750));
    Tree_information.push_back(temp5.GetTreeCopy());
    Tree temp6("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(900, 1350));
    Tree_information.push_back(temp6.GetTreeCopy());
    Tree temp7("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(1600, 1650));
    Tree_information.push_back(temp7.GetTreeCopy());
    Tree temp8("tree1", "Tree/tree1.png", "Tree/tree2.png", "Tree/tree3.png", 10, 3, Vec2(200, 1130));
    Tree_information.push_back(temp8.GetTreeCopy());

    // 初始化存储作物信息的数组
    cropbasicinformation.insert({ "wheat", wheat });
    cropbasicinformation.insert({ "corn", corn });
    cropbasicinformation.insert({ "potato", potato });
    cropbasicinformation.insert({ "pumpkin", pumpkin });
    cropbasicinformation.insert({ "blueberry", blueberry });

    // 初始化小镇各地址坐标
    std::pair<std::string, Vec2> key = { "initiation",Vec2(350,350) };
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2(230,470) };
    T_lastplace.insert(std::make_pair(key, false));

    // 初始化农场各地址坐标
    key = { "initiation",Vec2(800, 1100) };
    F_lastplace.insert(std::make_pair(key, true));
    key = { "myhouse", Vec2(70, 920) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "barn",Vec2(20, 170) };
    F_lastplace.insert(std::make_pair(key, false));
    key = { "cave",Vec2(645, 1175) };
    F_lastplace.insert(std::make_pair(key, false));

    // 初始化季节
    season.insert({ "Spring", 1 });
    season.insert({ "Summer", 2 });
    season.insert({ "Autumn", 3 });
    season.insert({ "Winter", 4 });

}


