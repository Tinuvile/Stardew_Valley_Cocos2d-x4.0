/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 �����κ������ʹ�ø������������޸ġ��ϲ����������ַ����������Լ����۸������ĸ�����ǰ�������и���������Ҫ���ֶ������������Ȩ����������������

 ��������"ԭ��"�ṩ���������κ���ʽ�ı�֤�������������ڶ������ԡ��ض���;�����ԺͲ���Ȩ�ı�֤�����κ�����£����߻��Ȩ�����߾�������ʹ�ø����������������ص��κ����⡢�𺦻��������γе����Σ������Ǻ�ͬ����Ȩ��Ϊ��������ʽ��
 ****************************************************************************/

#include "AppDelegate.h"
#include "GameBeginUI.h"
#include "Player.h"
//#include "Town.h"
#include "Barn.h"
//#include "supermarket.h"
#include "CreateCharacterUI.h"
#include "EnergySystem.h"
#include "Flyweight/FlyweightFactory.h"
#include "Flyweight/CropFlyweight.h"
#include "Flyweight/CropExtrinsicState.h"
#include "Flyweight/TreeFlyweight.h"
#include "Flyweight/TreeExtrinsicState.h"
#include "Flyweight/OreFlyweight.h"
#include "Flyweight/OreExtrinsicState.h"

// #define USE_AUDIO_ENGINE 1   // �����Ҫʹ����Ƶ���棬����ȡ��ע����һ��

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // �����������Ƶ���棬��������Ƶ�����ͷ�ļ�
// using namespace cocos2d::experimental;  // ʹ����Ƶ����������ռ�
#endif

USING_NS_CC;  // ʹ��cocos2d�������ռ�

/******************************** ȫ�ֱ��������� ****************************************/
// �ڴ��ļ��ж��岢��ʼ��ȫ�ֱ���
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

// ȫ��ָ���������
Player* player1 = nullptr;
mini_bag* miniBag = nullptr;
Timesystem* TimeUI = nullptr;

Inventory* inventory = new Inventory ();

NpcRelationship* npc_relationship = new NpcRelationship();

std::vector<std::pair<Rect , bool>> barn_space;
std::vector<Livestock*> livestocks;
SkillTree* skill_tree = new SkillTree ();

// �������������
TaskManagement* taskManager = new TaskManagement();
/****************************************************************************************/


AppDelegate::AppDelegate() {
    // ���캯����AppDelegate����ʱ�����
}

AppDelegate::~AppDelegate() {
    // �����������������ʱ�����
#if USE_AUDIO_ENGINE
    AudioEngine::end();  // ���ʹ������Ƶ���棬ֹͣ��Ƶ����
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs() {
    // ����OpenGL�����ĵ����ԣ��졢�̡�����͸��ͨ����λ���ȡ�ģ��Ͷ��ز���
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };  // ���� OpenGL �����ĵ���ɫ����Ȼ��������

    GLView::setGLContextAttrs(glContextAttrs);  // �����õ�����������Ӧ�õ� GLView
}

// �����ͨ������������װ���������Ҫ�޸Ļ�ɾ���������
static int register_all_packages() {
    return 0;  // ��־λ�����ڰ�������
}

// Ӧ��������ɺ����
bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ�� Director�������࣬���ڹ��������ͻ��ƣ�
    auto director = Director::getInstance();  // ��ȡ Director ʵ��
    auto glview = director->getOpenGLView();  // ��ȡ OpenGL ��ͼ
    
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Startdew", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Startdew");
#endif
        director->setOpenGLView(glview);
    }

    // �� FPS ��ʾ
    director->setDisplayStats(true);  // ��ʾ֡��ͳ����Ϣ

    // ����֡�ʡ�Ĭ��ֵΪ 1.0/60���� 60 FPS
    director->setAnimationInterval(1.0f / 60);  // ���ö���֡��Ϊ 60 FPS

    // ������Ʒֱ���
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    director->setContentScaleFactor(1.0f);

    register_all_packages();  // ע�����еİ�

    runScene(director);

    // set the background music and continuously play it.
    auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/01 - Stardew Valley Overture.mp3" , true );

    return true;  // ���سɹ�
}

// �л������ĺ���
void AppDelegate::runScene(cocos2d::Director* director) {
    Initialize ();
    
    // ��ȡ��ǰ��ͼ�Ŀɼ���С��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();  // ��ȡ��Ļ��������Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // ��ȡ��Ļԭ���λ�ã����½ǣ�
  

    std::pair<std::string , Vec2> key = { "initiation",Vec2 ( 350,350 ) };
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert(std::make_pair(key, false));

    // ����ũ��
    //auto farm = farm::create ();
    //director->runWithScene ( farm );

    //���к�̲����
    // auto beach = Beach::create ();
    // director->runWithScene ( beach );

     //���мҵĳ���
     //auto test = Myhouse::create();
     //director->runWithScene(test); 

    // ����С��ĳ���
     //auto test = Town::create ();
     //director->runWithScene(test);

    // �����̵�ĳ���
    //auto test = supermarket::create();
    //director->runWithScene(test);

    // ����Cave
     //auto test = Cave::create();
     //director->runWithScene(test);

    // ����Beach
    // auto test = Beach::create();
    // director->runWithScene(test);
    
    // ����ɭ��
    /* auto test = Forest::create();
     director->runWithScene(test);*/

     // ��������
     // auto test = Barn::create();
     // director->runWithScene(test);

    //����UI����
    //director->runWithScene ( BeginScene::create () );
    //���������������
    director->runWithScene ( CreateCharacter::create () );
}

void AppDelegate::Initialize () {
    // 初始化享元工厂 - 预加载所有享元对象
    FlyweightFactory::getInstance()->preloadAll();

    // 初始化Observer系统
    // 设置初始能量值
    EnergySystem::getInstance()->setEnergy(strength);
    EnergySystem::getInstance()->setMaxEnergy(100);

    // 初始化存储农作物信息的容器
    cropbasicinformation.insert({ "Wheat_Seeds", wheat });
    cropbasicinformation.insert({ "Corn_Seeds", corn });
    cropbasicinformation.insert({ "Potato_Seeds", potato });
    cropbasicinformation.insert({ "Pumpkin_Seeds", pumpkin });
    cropbasicinformation.insert({ "Blueberry_Seeds", blueberry });

    // 获取享元工厂 - 用于创建树木和矿石
    auto factory = FlyweightFactory::getInstance();

    // 初始化矿石信息 - 使用享元模式
    auto rubyFlyweight = factory->getOreFlyweight("Ruby");
    auto amethystFlyweight = factory->getOreFlyweight("Amethyst");
    auto emeraldFlyweight = factory->getOreFlyweight("Emerald");

    if (rubyFlyweight) {
        auto rubyState1 = new OreExtrinsicState(rubyFlyweight, Vec2(350, 500), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(rubyFlyweight, rubyState1));

        auto rubyState2 = new OreExtrinsicState(rubyFlyweight, Vec2(950, 750), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(rubyFlyweight, rubyState2));
    }

    if (amethystFlyweight) {
        auto amethystState1 = new OreExtrinsicState(amethystFlyweight, Vec2(800, 250), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(amethystFlyweight, amethystState1));

        auto amethystState2 = new OreExtrinsicState(amethystFlyweight, Vec2(750, 850), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(amethystFlyweight, amethystState2));
    }

    if (emeraldFlyweight) {
        auto emeraldState1 = new OreExtrinsicState(emeraldFlyweight, Vec2(900, 150), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(emeraldFlyweight, emeraldState1));

        auto emeraldState2 = new OreExtrinsicState(emeraldFlyweight, Vec2(1250, 350), true, 0);
        Ore_information.push_back(std::make_shared<Ore>(emeraldFlyweight, emeraldState2));
    }

    // 初始化树木信息 - 使用享元模式
    auto treeFlyweight = factory->getTreeFlyweight("tree");

    if (treeFlyweight) {
        // 创建5棵树，每棵树有不同的位置（外部状态）
        auto state1 = new TreeExtrinsicState(treeFlyweight, Vec2(50, 950), true, 0);
        Tree_information.push_back(std::make_shared<Tree>(treeFlyweight, state1));

        auto state2 = new TreeExtrinsicState(treeFlyweight, Vec2(-400, 700), true, 0);
        Tree_information.push_back(std::make_shared<Tree>(treeFlyweight, state2));

        auto state3 = new TreeExtrinsicState(treeFlyweight, Vec2(800, 1250), true, 0);
        Tree_information.push_back(std::make_shared<Tree>(treeFlyweight, state3));

        auto state4 = new TreeExtrinsicState(treeFlyweight, Vec2(900, 1650), true, 0);
        Tree_information.push_back(std::make_shared<Tree>(treeFlyweight, state4));

        auto state5 = new TreeExtrinsicState(treeFlyweight, Vec2(1300, 1550), true, 0);
        Tree_information.push_back(std::make_shared<Tree>(treeFlyweight, state5));
    }

    // 初始化小镇地址链表
    std::pair<std::string , Vec2> key = { "initiation",Vec2 (-840,-340) };
    T_lastplace.insert ( std::make_pair ( key , true ) );
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert ( std::make_pair ( key , false ) );
    key = { "forest",Vec2(-840,-340) };
    T_lastplace.insert(std::make_pair(key, false));
    key = { "beach",Vec2(500, -750) };
    T_lastplace.insert(std::make_pair(key, false));

    // 初始化农场最近地址链表
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

    // 初始化森林各个地址链表
    key = { "initiation",Vec2(1150,2650) };
    W_lastplace.insert(std::make_pair(key, true));
    key = { "town",Vec2(2600, 1900) };
    W_lastplace.insert(std::make_pair(key, false));
    key = { "farm",Vec2(1150, 2650) };
    W_lastplace.insert(std::make_pair(key, false));

    // 添加任务
    TaskManagement::Task task1 (
        "Fetch the Amethyst" ,
        TaskManagement::NPC_TASK ,
        "Retrieve the Amethyst for Abigail." , // 详细说明
        "Spring" , // 开始季节
        "Summer"  // 结束季节
    );
    task1.npcName = "Abigail"; // 设置相关 NPC 名称
    task1.requiredItems.push_back ( Bean_Starter ); // 需要的物品
    task1.rewardCoins = 500; // 奖励金钱
    task1.relationshipPoints = 10; // NPC 好感度  

    TaskManagement::Task task2 (
        "Collect Emerald" ,
        TaskManagement::SYSTEM_TASK ,
        "Collect an Emerald for system tasks." , // ��ϸ˵��  
        "Summer" , // ��ʼ����  
        "Autumn"  // ��������  
    );
    task2.requiredItems.push_back ( emerald ); // ��Ҫ����Ʒ  
    task2.rewardCoins = 30; // �������  

    TaskManagement::Task task3 (
        "Festival Gathering" ,
        TaskManagement::FESTIVAL_TASK ,
        "Join the festival and collect special items." , // ��ϸ˵��  
        "Winter" , // ��ʼ����  
        "Summer"  // ��������  
    );
    task3.specialRewards.push_back ( Gold_Hoe );   // ���⽱��  
    task3.relationshipPoints = 5; // �������˵ĺøж�  

    // ���������ӵ����������  
    taskManager->createTask ( task1 );
    taskManager->createTask ( task2 );
    taskManager->createTask ( task3 );

    // taskManager->AddAcceptTask ( task1 );

    //��ʼ��Barn�ڿɷ��ü������
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

    // ��ʼ������
    season.insert ( { "Spring", 1 } );
    season.insert ( { "Summer", 2 } );
    season.insert ( { "Autumn", 3 } );
    season.insert ( { "Winter", 4 } );

    // ��������  
    //TaskManagement::Task task1 ( "Fetch the Amethyst" , TaskManagement::NPC_TASK );
    //task1.npcName = "Abigail"; // ��������� NPC ����  
    //task1.requiredItems.push_back ( amethyst ); // ��Ҫ����Ʒ  
    //task1.rewardCoins = 500; // �������  
    //task1.relationshipPoints = 10; // NPC �øж�  

    //TaskManagement::Task task2 ( "Collect Emerald" , TaskManagement::SYSTEM_TASK );
    //task2.requiredItems.push_back ( emerald ); // ��Ҫ����Ʒ  
    //task2.rewardCoins = 30; // �������  

    //TaskManagement::Task task3 ( "Festival Gathering" , TaskManagement::FESTIVAL_TASK );
    //task3.specialRewards.push_back ( Gold_Hoe );   // ���⽱��  
    //task3.relationshipPoints = 5; // �������˵ĺøж�  

    //// ���������ӵ����������  
    //taskManager->createTask ( task1 );
    //taskManager->createTask ( task2 );
    //taskManager->createTask ( task3 );
}



// ��Ӧ�ó�������̨ʱ����
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();  // ֹͣ����

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();  // ��ͣ������Ƶ�������������Ƶ���棩
#endif
}

// ��Ӧ�ó������½���ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();  // �ָ�����

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();  // �ָ�������Ƶ�������������Ƶ���棩
#endif
}
