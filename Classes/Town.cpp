#include "AppDelegate.h"
#include "Town.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"

USING_NS_CC;

extern int remainingTime;

myhouse::myhouse() {}

myhouse::~myhouse() {}

bool myhouse::init()
{
    if (!Scene::init())
    {
        return false;
    }

   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
 

    // �����˳���ť��"X" ͼ�꣩�����ʱ�˳���Ϸ
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",  // ��ͨ״̬�µ�ͼƬ
        "CloseSelected.png",  // ��ѡ��״̬�µ�ͼƬ
        CC_CALLBACK_1(myhouse::menuCloseCallback, this));  // �����ťʱ���� menuCloseCallback ����


    // ���ð�ťλ�ã�ʹ��λ����Ļ���Ͻ�
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));  // ���ð�ť��λ��



    // �����˵�������ť��ӵ��˵��У������ò˵���λ��
    auto menu = Menu::create(closeItem, NULL);  // �����˵�����Ӱ�ť
    menu->setPosition(Vec2::ZERO);  // ���ò˵���λ��Ϊ��0��0���������½�
    this->addChild(menu, 10);  // ���˵���ӵ���ǰ������



    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        _positionLabel->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height - 50));  // ����λ��
        this->addChild(_positionLabel, 10);  
        _positionLabel->setScale(0.7f);
    }

    // ���ü�ʱ����ǩ
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    _timerLabel->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height - 90));
    this->addChild(_timerLabel, 10);

    // ����������ȡ���ı�ǩ
    In_gettask = Sprite::create("opendoor.png");
    this->addChild(In_gettask, 10);
    In_gettask->setScale(0.5f);
    In_gettask->setVisible(false);


    // ���ñ���ͼƬ
    auto background_real = Sprite::create("Town/Town.png");  
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real,1);
    background_real->setScale(0.7f);

    auto background_up = Sprite::create("Town/Town_up.png");  
    background_up->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_up, 7);
    background_up->setScale(0.7f);
 
    auto background = Sprite::create("Town/Town_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(0.7f);
   

    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    CCLOG("spritePosition: (%f, %f)", spritePosition.x, spritePosition.y);
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�
    CCLOG("spriteSize: (%f, %f)", spriteSize.width, spriteSize.height);

    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - 0.7 * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - 0.7 * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );
    CCLOG("leftBottomPosition: (%f, %f)", leftBottomPosition.x, leftBottomPosition.y);

    Image img;
    if (img.initWithImageFile("Town/Town_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // ��ȡ��������
        unsigned char* data = img.getData();

        // �����������أ�����Ƿ������ݣ�͸���ȴ���0��
        for (int y = 0; y < height; y = y + 8)
        {
            for (int x = 0; x < width; x = x + 8)
            {
                // ��ȡ��ǰ���ص� RGBA ֵ
                int index = (y * width + x) * 4;  // ÿ������ռ�� 4 ���ֽ� (RGBA)
                unsigned char a = data[index + 3];  // ͸����

                // ���͸���� (alpha) ���� 0����ʾ������������
                if (a > 0)
                {
                    float screenX = leftBottomPosition.x + x * 0.7;
                    float screenY = leftBottomPosition.y + (height - y - 1) * 0.7;  // ע�� Y �ᷴ��
                    CCLOG("Non-transparent pixel at: (%f, %f)", screenX, screenY);
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // ��¼��Ļ����
                }
            }
        }
    }


    // ��ʼ����ɫ��������ӵ�����
    auto player1 = Player::create();
    this->addChild(player1,5);
    player1->setPosition(Vec2(visibleSize.width / 2 + 43, visibleSize.height / 2 - 72));  // ������ҳ�ʼλ��
    player1->setScale(0.7f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));

    // ���ڸ������״̬
    schedule([this, player1](float dt) {
        this->checkPlayerPosition(player1);  // �������Ƿ�ӽ�������
        }, 0.01f, "check_position_key");


    return true;
}

myhouse* myhouse::create()
{
    myhouse* scene = new myhouse();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// �������Ƿ�ӽ�������������
void myhouse::checkPlayerPosition(Player* player)
{
    // ��ȡ��ҵ�λ��
    Vec2 playerPos = player->getPosition();
    
    // ����λ�ñ�ǩ������
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    }

    // ����ʣ��ʱ��
    remainingTime--;

    // ���¼�ʱ����ʾ
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));


    if (Get_Task.containsPoint(playerPos)) {
        In_gettask->setPosition(Vec2(playerPos.x + 35, playerPos.y + 10));
        In_gettask->setVisible(true);
    }
    else {
        In_gettask->setVisible(false);
    }


    // �������������㣬�������Ƿ�ӽ�ĳ��������
    for (const auto& point : nonTransparentPixels)
    {
        // ���������������֮��ľ���
        float distance = 0;

        Vec2 temp = playerPos;
        temp.x -= player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveLeft = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.y -= player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveDown = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.y += player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveUp = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }

        temp = playerPos;
        temp.x += player->speed;
        distance = temp.distance(point);
        if (distance <= 5) {
            player->moveRight = true;
            CCLOG("Player is near the boundary! Moving is stopped.");
        }
       
    }
}







// �˳���ť�Ļص�����
void myhouse::menuCloseCallback(Ref* pSender)
{
    // �˳����򣬽�����ǰ��Ϸ����
    Director::getInstance()->end();

    /* �����ϣ���˳�����Ӧ�ã����ǽ��رյ�ǰ���������Կ���ʹ�����´��룺
       �˲��ִ��������� iOS �Ϸ��ص�ԭ����Ļ������ֱ���˳�Ӧ�ã�

       EventCustom customEndEvent("game_scene_close_event");
       _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}




