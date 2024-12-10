/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 �����κ������ʹ�ø�����������޸ġ��ϲ����������ַ���������Լ����۸�����ĸ�����ǰ�������и���������Ҫ���ֶ������������Ȩ���������������

 �������"ԭ��"�ṩ���������κ���ʽ�ı�֤�������������ڶ������ԡ��ض���;�����ԺͲ���Ȩ�ı�֤�����κ�����£����߻��Ȩ�����߾�������ʹ�ø��������������ص��κ����⡢�𺦻��������γе����Σ������Ǻ�ͬ����Ȩ��Ϊ��������ʽ��
 ****************************************************************************/

#include "AppDelegate.h"
#include "GameBeginUI.h"
#include "Player.h"
#include "Town.h"
#include "supermarket.h"
#include "CreateCharacterUI.h"

 // #define USE_AUDIO_ENGINE 1   // �����Ҫʹ����Ƶ���棬����ȡ��ע����һ��

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"  // �����������Ƶ���棬��������Ƶ�����ͷ�ļ�
using namespace cocos2d::experimental;  // ʹ����Ƶ����������ռ�
#endif

USING_NS_CC;  // ʹ��cocos2d�������ռ�

/******************************** ȫ�ֱ��������� ****************************************/
int remainingTime = 60000;
Player* player1 = nullptr;
Town* town = NULL;
supermarket* seedshop = NULL;
std::map<std::pair<std::string, Vec2>, bool> T_lastplace;
Inventory* inventory = new Inventory ();//���ﱳ��
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
    // ��ʼ�� Director�������࣬���ڹ������ͻ��ƣ�
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

    return true;  // ���سɹ�
}

// �л������ĺ���
void AppDelegate::runScene(cocos2d::Director* director) {

    player1 = Player::create();

    // ��ȡ��ǰ��ͼ�Ŀɼ���С��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();  // ��ȡ��Ļ��������Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();  // ��ȡ��Ļԭ���λ�ã����½ǣ�
  
    std::pair<std::string, Vec2> key = { "initiation",Vec2(350,350)};
    T_lastplace.insert(std::make_pair(key, true));
    key = { "seedshop",Vec2(230,470) };
    T_lastplace.insert(std::make_pair(key, false));
    director->runWithScene ( Town::create () );
    //director->runWithScene ( supermarket::create () );

    //����UI����
    //director->runWithScene ( BeginScene::create () );
    //���������������
    //director->runWithScene ( CreateCharacter::create () );
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
