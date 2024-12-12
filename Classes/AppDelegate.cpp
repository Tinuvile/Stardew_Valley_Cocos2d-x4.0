/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 �����κ������ʹ�ø�����������޸ġ��ϲ����������ַ���������Լ����۸�����ĸ�����ǰ�������и���������Ҫ���ֶ������������Ȩ���������������

 �������"ԭ��"�ṩ���������κ���ʽ�ı�֤�������������ڶ������ԡ��ض���;�����ԺͲ���Ȩ�ı�֤�����κ�����£����߻��Ȩ�����߾�������ʹ�ø��������������ص��κ����⡢�𺦻��������γе����Σ������Ǻ�ͬ����Ȩ��Ϊ��������ʽ��
 ****************************************************************************/

#include "AppDelegate.h"

 // #define USE_AUDIO_ENGINE 1   // �����Ҫʹ����Ƶ���棬����ȡ��ע����һ��

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // �����������Ƶ���棬��������Ƶ�����ͷ�ļ�
using namespace cocos2d::experimental;  // ʹ����Ƶ����������ռ�
#endif

USING_NS_CC;  // ʹ��cocos2d�������ռ�

/******************************** ȫ�ֱ��������� ****************************************/
// �ڴ��ļ��ж��岢��ʼ��ȫ�ֱ���
int remainingTime = 60000;
int day = 1;
bool frombed = false;
bool IsNextDay = false;
CropBasicInformation WHEAT ( "crop/wheat1.png" , "crop/wheat2.png" , "crop/wheat3.png" , "All" );
CropBasicInformation CORN ( "crop/corn1.png" , "crop/corn2.png" , "crop/corn3.png" , "Spring" );
CropBasicInformation POTATO ( "crop/potato1.png" , "crop/potato2.png" , "crop/potato3.png" , "All" );
CropBasicInformation PUMPKIN ( "crop/pumpkin1.png" , "crop/pumpkin2.png" , "crop/pumpkin3.png" , "Summer" );
CropBasicInformation BLUEBERRY ( "crop/blueberry1.png" , "crop/blueberry2.png" , "crop/blueberry3.png" , "Autumn" );

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

// ȫ��ָ���������
Player* player1 = nullptr;
Town* town = nullptr;
supermarket* seedshop = nullptr;
farm* Farm = nullptr;
Myhouse* myhouse = nullptr;

std::map<std::pair<std::string , Vec2> , bool> T_lastplace;

Inventory* inventory = new Inventory ();
std::vector<std::pair<Rect , bool>> barn_space;
std::vector<Livestock*> livestocks;
/****************************************************************************************/


AppDelegate::AppDelegate () {
    // ���캯����AppDelegate����ʱ�����
}

AppDelegate::~AppDelegate () {
    // �����������������ʱ�����
#if USE_AUDIO_ENGINE
    AudioEngine::end ();  // ���ʹ������Ƶ���棬ֹͣ��Ƶ����
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs () {
    // ����OpenGL�����ĵ����ԣ��졢�̡�����͸��ͨ����λ���ȡ�ģ��Ͷ��ز���
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };  // ���� OpenGL �����ĵ���ɫ����Ȼ��������

    GLView::setGLContextAttrs ( glContextAttrs );  // �����õ�����������Ӧ�õ� GLView
}

// �����ͨ������������װ���������Ҫ�޸Ļ�ɾ���������
static int register_all_packages () {
    return 0;  // ��־λ�����ڰ�������
}

// Ӧ��������ɺ����
bool AppDelegate::applicationDidFinishLaunching () {
    // ��ʼ�� Director�������࣬���ڹ������ͻ��ƣ�
    auto director = Director::getInstance ();  // ��ȡ Director ʵ��
    auto glview = director->getOpenGLView ();  // ��ȡ OpenGL ��ͼ

    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect ( "Startdew" , cocos2d::Rect ( 0 , 0 , designResolutionSize.width , designResolutionSize.height ) );
#else
        glview = GLViewImpl::create ( "Startdew" );
#endif
        director->setOpenGLView ( glview );
    }

    // �� FPS ��ʾ
    director->setDisplayStats ( true );  // ��ʾ֡��ͳ����Ϣ

    // ����֡�ʡ�Ĭ��ֵΪ 1.0/60���� 60 FPS
    director->setAnimationInterval ( 1.0f / 60 );  // ���ö���֡��Ϊ 60 FPS

    // ������Ʒֱ���
    glview->setDesignResolutionSize ( designResolutionSize.width , designResolutionSize.height , ResolutionPolicy::NO_BORDER );
    director->setContentScaleFactor ( 1.0f );

    register_all_packages ();  // ע�����еİ�

    runScene ( director );

    return true;  // ���سɹ�
}

// �л������ĺ���
void AppDelegate::runScene ( cocos2d::Director* director ) {

    Initialize ();
    player1 = Player::create ();

    // ��ȡ��ǰ��ͼ�Ŀɼ���С��ԭ��λ��
    auto visibleSize = Director::getInstance ()->getVisibleSize ();  // ��ȡ��Ļ��������Ĵ�С
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();  // ��ȡ��Ļԭ���λ�ã����½ǣ�

    std::pair<std::string , Vec2> key = { "initiation",Vec2 ( 350,350 ) };
    T_lastplace.insert ( std::make_pair ( key , true ) );
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert ( std::make_pair ( key , false ) );
    /*town = Town::create();*/
    auto barn = Barn::create ();

    //�������ﳡ��
    director->runWithScene ( barn );

    // ����С�򳡾�
    //director->runWithScene ( town );

    //����UI����
    //director->runWithScene ( BeginScene::create () );
    //���������������
    //director->runWithScene ( CreateCharacter::create () );
}

void AppDelegate::Initialize () {
    // ��������
    player1 = Player::create ();
    // ��ʼ���洢������Ϣ������
    //cropbasicinformation.insert ( { "wheat", WHEAT } );
    //cropbasicinformation.insert ( { "corn", CORN } );
    //cropbasicinformation.insert ( { "potato", POTATO } );
    //cropbasicinformation.insert ( { "pumpkin", PUMPKIN } );
    //cropbasicinformation.insert ( { "blueberry", BLUEBERRY } );
    // ��ʼ��С�����ַ����
    std::pair<std::string , Vec2> key = { "initiation",Vec2 ( 350,350 ) };
    T_lastplace.insert ( std::make_pair ( key , true ) );
    key = { "seedshop",Vec2 ( 230,470 ) };
    T_lastplace.insert ( std::make_pair ( key , false ) );
    // ��ʼ������
    season.insert ( { "Spring", 1 } );
    season.insert ( { "Summer", 2 } );
    season.insert ( { "Autumn", 3 } );
    season.insert ( { "Winter", 4 } );
}



// ��Ӧ�ó�������̨ʱ����
void AppDelegate::applicationDidEnterBackground () {
    Director::getInstance ()->stopAnimation ();  // ֹͣ����

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll ();  // ��ͣ������Ƶ�������������Ƶ���棩
#endif
}

// ��Ӧ�ó������½���ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground () {
    Director::getInstance ()->startAnimation ();  // �ָ�����

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll ();  // �ָ�������Ƶ�������������Ƶ���棩
#endif
}
