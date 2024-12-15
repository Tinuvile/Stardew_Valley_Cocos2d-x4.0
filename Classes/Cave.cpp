#include "AppDelegate.h"
#include "farm.h"
#include "Cave.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "vector"

USING_NS_CC;

Cave::Cave() {}

Cave::~Cave() {}

bool Cave::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    // ���ü�ʱ����ǩ
    _timerLabelD = Label::createWithTTF("Day: 0", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelD, 10);
    _timerLabelD->setScale(2.3f);

    _timerLabelH = Label::createWithTTF("0:00", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelH, 10);
    _timerLabelH->setScale(2.3f);

    _timerLabelS = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelS, 10);
    _timerLabelS->setScale(2.3f);

    // �ָ���ֲ
    AllInitialize_ore();

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // ���ñ���ͼƬ
    auto background_real = Sprite::create("Cave/cave.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(2.9f);

    auto background = Sprite::create("Cave/cave_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(2.9f);


    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�
  

    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );
   

    Image img;
    if (img.initWithImageFile("Cave/cave_path.png"))
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
                int index = (y * width + x) * 4;    // ÿ������ռ�� 4 ���ֽ� (RGBA)
                unsigned char a = data[index + 3];  // ͸����

                // ���͸���� (alpha) ���� 0����ʾ������������
                if (a > 0)
                {
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // ע�� Y �ᷴ��
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));                             // ��¼��Ļ����
                }
            }
        }
    }

    // ��ʼ����ɫ��������ӵ�����
    if (player1->getParent() == NULL) {
        this->addChild(player1, 17);
        
        player1->setPosition(500,650);      
        player1->speed = 6.1f;
        player1->setScale(2.3f);
        player1->setAnchorPoint(Vec2(0.5f, 0.2f));
    }    

    
    // ��������Ķ�ʱ��
    player1->schedule([=](float dt) {
        player1->player1_move();
        }, 0.05f, "player1_move");

    player1->schedule([=](float dt) {
        player1->player_change();
        }, 0.3f, "player_change");


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

        // �жϵ��λ���Ƿ��ھ��鷶Χ��
        if (button != nullptr && button->getBoundingBox().containsPoint(clickPos)) {
            Director::getInstance()->end();
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, button);

    // ���ü��̼�����
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_M) {
                isMKeyPressed = true;
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = false;
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_M) {
                isMKeyPressed = false;
            }
        };

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    return true;
}


Cave* Cave::create()
{
    Cave* scene = new Cave();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

void Cave::AllInitialize_ore() {

    for (auto it = Ore_information.begin(); it != Ore_information.end(); /* no increment here */) {

        auto ore = *it;  // �����õ������Է��� Crop ����
        
        if (IsNextDay) {
            if (!ore->available) {
                if (season[Season] * 7 + day - ore->mining_day >= ore->recover_time) {
                    ore->available = true;
                }
            }
        }

        cocos2d::log("Create Ore");

        if (ore->available) {
            auto temp = Sprite::create(ore->initial_pic);
            this->addChild(temp, 5);
            temp->setPosition(ore->position);
            temp->setScale(2.7f);
        }
        else {
            auto temp = Sprite::create(ore->mining_pic);
            this->addChild(temp, 5);
            temp->setPosition(ore->position);
            temp->setScale(2.7f);
        }
        it++;


    }

}

// �������Ƿ�ӽ�������������
void Cave::checkPlayerPosition()
{

    // ��ȡ��ҵ�λ��
    Vec2 playerPos = player1->getPosition();

    // ����λ�ñ�ǩ������
    if (_positionLabel)
    {
        _positionLabel->setString("Position: (" + std::to_string(static_cast<int>(playerPos.x)) + ", " + std::to_string(static_cast<int>(playerPos.y)) + ")");
    
    }
    
    // ���¼�ʱ����ʾ
    remainingTime++;
    _timerLabelD->setString("Day: " + std ::to_string(day));
    _timerLabelH->setString(std::to_string(remainingTime / 1800) + ":00");
    _timerLabelS->setString(Season);
    if (remainingTime == 43200) {
        
        day++;

        IsNextDay = true;

        if (day == 8) {
            if (Season == "Spring") {
                Season = "Summer";
            }
            else if (Season == "Summer") {
                Season = "Autumn";
            }
            else {
                Season = "Winter";
            }
            day = 1;
        }


        for (auto it = Crop_information.begin(); it != Crop_information.end(); /* no increment here */) {

            auto crop = *it;  // �����õ������Է��� Crop ����

            // �ж�ǰһ���Ƿ�ˮ
            if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
                // �ж��Ƿ��Ѿ������ή״̬
                if (crop->GetPhase() != Phase::SAPLESS) {
                    crop->ChangePhase(Phase::SAPLESS);
                    crop->ChangMatureNeeded(2); // �ӳ������ջ�
                }
                else {
                    // ɾ��Ԫ�ز����µ�����
                    it = Crop_information.erase(it);
                }
                ++it;
                continue;  // �����������룬ֱ�Ӽ���ѭ��
            }
            else {
                // ����״̬
                crop->UpdateGrowth();
            }

            it++;
        }

         remainingTime = 0;
         player1->removeFromParent();
         auto nextday = Myhouse::create();
         Director::getInstance()->replaceScene(nextday);
           

    }

    // ���±�ǩλ��
    float currentx = 0, currenty = 0;
    if (playerPos.x <= 786) {
        currentx = 786;
    }
    else if (playerPos.x >= 817) {
        currentx = 817;
    }
    else {
        currentx = playerPos.x;  
    }

    if (playerPos.y >= 808) {
        currenty = 808;
    }
    else if (playerPos.y <= 460) {
        currenty = 460;
    }
    else {
        currenty = playerPos.y;
    }

    _timerLabelD->setPosition(currentx - 710, currenty + 570);
    _timerLabelH->setPosition(currentx - 570, currenty + 570);
    _timerLabelS->setPosition(currentx - 410, currenty + 570);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);

    if (isMKeyPressed) {
        for (auto it = Ore_information.begin(); it != Ore_information.end(); /* no increment here */) {

            auto ore = *it;  // �����õ������Է��� Crop ����

            float distance = ore->position.distance(playerPos);
            if (distance <= 75 && ore->available) {

                ore->available = false;

                ore->mining_day = season[Season] * 7 + day;

                if (player1->pic_path == "character1/player_right3.png") {
                   
                    player1->setTexture("character1/player_plant3.png");
                    player1->setScale(3.9f);

                    // �ӳ�0.3����л����ڶ���ͼƬ
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_plant4.png");  // ����Ϊplayer_plant2
                        player1->setScale(4.1f);
                        }, 0.15f, "change_image1_key");

                    // �ӳ�0.6����л���������ͼƬ
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_right3.png"); // ����Ϊplayer_left3
                        player1->setScale(2.3f);
                        auto earth = Sprite::create("Ore/earth.png");
                        this->addChild(earth, 5);
                        earth->setPosition(ore->position);
                        earth->setScale(2.9f);
                        auto temp = Sprite::create(ore->mining_pic);
                        this->addChild(temp, 6);
                        temp->setPosition(ore->position);
                        temp->setScale(2.7f);
                        }, 0.35f, "change_image2_key");

                }
                else {
                    player1->setTexture("character1/player_plant1.png");
                    player1->setScale(3.9f);

                    // �ӳ�0.3����л����ڶ���ͼƬ
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_plant2.png");  // ����Ϊplayer_plant2
                        player1->setScale(4.1f);
                        }, 0.15f, "change_image1_key");

                    // �ӳ�0.6����л���������ͼƬ
                    player1->scheduleOnce([=](float dt) {
                        player1->setTexture("character1/player_left3.png"); // ����Ϊplayer_left3
                        player1->setScale(2.3f);
                        auto earth = Sprite::create("Ore/earth.png");
                        this->addChild(earth, 5);
                        earth->setPosition(ore->position);
                        earth->setScale(2.9f);
                        auto temp = Sprite::create(ore->mining_pic);
                        this->addChild(temp, 6);
                        temp->setPosition(ore->position);
                        temp->setScale(2.7f);
                        }, 0.35f, "change_image2_key");
                }
            }


            it++;

        }
    }

    if (Out_cave.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            player1->removeFromParent();
            auto nextscene = farm::create();
            Director::getInstance()->replaceScene(nextscene);
        }
    }

    for (const auto& point : nonTransparentPixels)
    {
        // ���������������֮��ľ���
        float distance = 0;

        Vec2 temp;
        temp = playerPos;
        temp.x -= player1->speed;
        distance = temp.distance(point);
        if (distance <= 17) {
            player1->moveLeft = false;
        }
        else {
            if (player1->leftpressed == false) {
                player1->moveLeft = true;
            }
        }
        
        temp = playerPos;
        temp.y -= 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveDown = false;
        }
        else {
            if (player1->downpressed == false) {
                player1->moveDown = true;
            }
        }

        temp = playerPos;
        temp.y += 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveUp = false;
        }
        else {
            if (player1->uppressed == false) {
                player1->moveUp = true;
            }
        }

        temp = playerPos;
        temp.x += 10;
        distance = temp.distance(point);
        if (distance <= 15) {
            player1->moveRight = false;
        }
        else{
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }
       
    }
    

}

int Cave::getRegionNumber(Vec2 pos) {

    int region_number = 1;

    return region_number;
}






