#include "AppDelegate.h"
#include "supermarket.h"
#include "Town.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "StoreManager.h"

USING_NS_CC;

extern int remainingTime;
extern Player* player1;
extern Town* town;
extern supermarket* seedshop;

supermarket::supermarket() {}

supermarket::~supermarket() {}

bool supermarket::init()
{
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    StoreManager* storeManager = new StoreManager ();
    storeManager->initStore ();

    // ���ü�ʱ����ǩ
    _timerLabel = Label::createWithTTF("Timer: 60", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabel, 10);
    _timerLabel->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
    _timerLabel->setScale(2.3f);

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // ��ʼ�����ż�
    opendoor = Sprite::create("opendoor.png");
    this->addChild(opendoor, 11);
    opendoor->setVisible(false);

    // ���ñ���ͼƬ
    auto background_real = Sprite::create("supermarket/supermarket.png");
    background_real->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    this->addChild(background_real, 1);
    background_real->setScale(6.7f);

    auto background_up = Sprite::create("supermarket/supermarket_up.png");
    background_up->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    this->addChild(background_up, 7);
    background_up->setScale(6.7f);

    auto background = Sprite::create("supermarket/supermarket_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2 + 1700, visibleSize.height / 2 + 370));
    background->setScale(6.7f);


    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�
  

    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );
   

    Image img;
    if (img.initWithImageFile("supermarket/supermarket_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // ��ȡ��������
        unsigned char* data = img.getData();

        // �����������أ�����Ƿ������ݣ�͸���ȴ���0��
        for (int y = 0; y < height; y = y + 4)
        {
            for (int x = 0; x < width; x = x + 4)
            {
                // ��ȡ��ǰ���ص� RGBA ֵ
                int index = (y * width + x) * 4;  // ÿ������ռ�� 4 ���ֽ� (RGBA)
                unsigned char a = data[index + 3];  // ͸����

                // ���͸���� (alpha) ���� 0����ʾ������������
                if (a > 0)
                {
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // ע�� Y �ᷴ��
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // ��¼��Ļ����
                }
            }
        }
    }


    // ��ʼ����ɫ��������ӵ�����
    this->addChild(player1, 5);
    player1->schedule([=](float dt) {
        player1->player1_move();
        }, 0.05f, "player1_move");

    player1->schedule([=](float dt) {
        player1->player_change();
        }, 0.3f, "player_change");
    player1->setPosition(Vec2(visibleSize.width / 2 + 43, visibleSize.height / 2 - 101));  // ������ҳ�ʼλ��
    player1->setScale(3.1f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));
    player1->speed = 2.5f;

    // ���㱳����������ź�Χ
    float scaledWidth = background->getContentSize().width * background->getScaleX();
    float scaledHeight = background->getContentSize().height * background->getScaleY();

    // ���� Follow �ı߽� Rect
    auto followRect = cocos2d::Rect(leftBottomPosition.x, leftBottomPosition.y, scaledWidth, scaledHeight);

    // ���� Follow ��������������ڱ�����Χ���ƶ�
    auto followAction = Follow::create(player1, followRect);
    this->runAction(followAction);


    // ���ڸ������״̬
    this->schedule([this](float dt) {
        this->checkPlayerPosition();  // �������Ƿ�ӽ�������
        }, 0.01f, "check_position_key");

    auto listener = EventListenerMouse::create();

    listener->onMouseDown = [this](Event* event) {
       
        // ��ȡ�������λ��
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos(mouseEvent->getCursorX(), mouseEvent->getCursorY());
        clickPos = this->convertToNodeSpace(clickPos);
        // ����������λ��
        CCLOG("Mouse Position: (%f, %f)", clickPos.x, clickPos.y);

        // �жϵ��λ���Ƿ��ھ��鷶Χ��
        if (button != nullptr && button->getBoundingBox().containsPoint(clickPos)) {
            CCLOG("Button clicked!");
            Director::getInstance()->end();
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);

    // ���ü��̼�����
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // ��¼ Enter ��������
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed.");
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = false;
                CCLOG("Enter key released.");
            }
        };

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);


    return true;
}


supermarket* supermarket::create()
{
    supermarket* scene = new supermarket();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// �������Ƿ�ӽ�������������
void supermarket::checkPlayerPosition()
{
    // ��ȡ��ҵ�λ��
    Vec2 playerPos = player1->getPosition();

    // ����λ�ñ�ǩ������
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    
    }


    // ����ʣ��ʱ��
    remainingTime--;

    // ���¼�ʱ����ʾ
    remainingTime--;
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 600));


    // ���±�ǩλ��
    float currentx = 0, currenty = 0;
    if (playerPos.x <= 743) {
        currentx = 743;
    }
    else if (playerPos.x >= 1773) {
        currentx = 1773;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y <= -82) {
        currenty = -82;
    }
    else {
        currenty = playerPos.y;
    }


    _timerLabel->setPosition(currentx - 590, currenty + 570);
    _positionLabel->setPosition(currentx - 530, currenty + 490);
    button->setPosition(currentx + 690, currenty - 590);
   
    // �������Ƿ����Ŀ�����򣬲��Ұ��� Enter ��
    if (Region_Out.containsPoint(playerPos)) {
        // ��ҽ���Ŀ������
        opendoor->setVisible(true);
        opendoor->setPosition(playerPos.x + 110, playerPos.y + 30);


        if (isEnterKeyPressed) {
            // ��ӡ������Ϣ����� Enter ����״̬
            CCLOG("Player in target area, isEnterKeyPressed: %d", isEnterKeyPressed);
            // ���ó����л��߼�
            player1->removeFromParent();
            town = Town::create();
            Director::getInstance()->replaceScene(town);
          
        }

    }
    else {
        opendoor->setVisible(false);
    }

    for (const auto& point : nonTransparentPixels)
    {
        // ���������������֮��ľ���
        float distance = 0;

        Vec2 temp;
        temp = playerPos;
        temp.x -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 55) {
            player1->moveLeft = false;
           
        }
        else {
            if (player1->leftpressed == false) {
                player1->moveLeft = true;
            }
        }



        temp = playerPos;
        temp.y -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 25) {
            player1->moveDown = false;
        }
        else {
            if (player1->downpressed == false) {
                player1->moveDown = true;
            }
        }

        temp = playerPos;
        temp.y += player1->speed;
        distance = temp.distance(point);
        if (distance <= 45) {
            player1->moveUp = false;
        }
        else {
            if (player1->uppressed == false) {
                player1->moveUp = true;
            }
        }

        temp = playerPos;
        temp.x += player1->speed;
        distance = temp.distance(point);
        if (distance <= 55) {
            player1->moveRight = false;
        }
        else {
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }

    }



}




