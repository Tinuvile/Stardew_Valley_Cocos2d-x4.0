#include "AppDelegate.h"
//#include "Town.h"
#include "farm.h"
#include "Crop.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"
#include "vector"

USING_NS_CC;

farm::farm() {}

farm::~farm() {}

bool farm::init()
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
    // AllInitialize_crop();

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // ���ñ���ͼƬ
    auto background_real = Sprite::create("farm/farm.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(1.5f);

    auto background = Sprite::create("farm/farm_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(1.5f);


    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�
  

    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );
   

    Image img;
    if (img.initWithImageFile("farm/farm_path.png"))
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
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // ע�� Y �ᷴ��
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // ��¼��Ļ����
                }
            }
        }
    }

    // �ָ���ҵ�״̬
    if (player1)
    {
        player1->setPosition(800, 1100);
        player1->speed = 2.5f;
    }

    // ��ʼ����ɫ��������ӵ�����
    if (player1->getParent() == NULL) {
        this->addChild(player1, 17);
    }
    player1->setScale(1.5f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));
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
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                isPKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
                isWKeyPressed = true;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_G) {
                isGKeyPressed = true;
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                isPKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
                isWKeyPressed = false;
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_G) {
                isGKeyPressed = false;
            }
        };

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    return true;
}


farm* farm::create()
{
    farm* scene = new farm();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

//void farm::AllInitialize_crop() {
//
//    int nums = 0;
//
//    for (auto it : Crop_information) {
//
//        if (it->Isplant()) {
//
//            // �ж�ǰһ���Ƿ�ˮ
//            if ((it->watered == false) && (it->harvestable == false)) {
//                // �ж��Ƿ��Ѿ������ή״̬
//                if (it->GetPhase() != Phase::SAPLESS) {
//                    it->ChangePhase(Phase::SAPLESS);
//                    it->mature_needed += 2; // �ӳ������ջ�
//                    auto test = Sprite::create("crop/sapless.png");
//                    this->addChild(test, 15 - nums / 19);
//                    test->setPosition(545 + ((nums % 19) - 1) * 48, 910 - ((nums / 19) - 1) * 48);
//                    test->setScale(2.1f);
//                }
//                else {
//                    it->ChangePlant(false);
//                    it->harvestable = false;
//                }
//                nums++;
//                continue;
//            }
//
//            // ����״̬
//            it->UpdateGrowth();
//
//            // ��ȡ����
//            std::string type = it->GetName();
//
//            cocos2d::log("nums = %d", nums);
//
//            if (it->GetPhase() == Phase::MATURE) {
//                auto test = Sprite::create(cropbasicinformation[type].thirdpath);
//                this->addChild(test, 15 - nums / 19);
//                test->setPosition(545 + ((nums % 19) - 1) * 48, 910 - ((nums / 19) - 1) * 48);
//                test->setScale(2.1f);
//            }
//            else if (it->GetPhase() == Phase::GROWING) {
//                auto test = Sprite::create(cropbasicinformation[type].secondpath);
//                this->addChild(test, 15 - nums / 19);
//                test->setPosition(545 + ((nums % 19) - 1) * 48, 910 - ((nums / 19) - 1) * 48);
//                test->setScale(2.1f);
//            }
//            else {
//                auto test = Sprite::create(cropbasicinformation[type].firstpath);
//                this->addChild(test, 15 - nums / 19);
//                test->setPosition(545 + ((nums % 19) - 1) * 48, 910 - ((nums / 19) - 1) * 48);
//                test->setScale(2.1f);
//            }
//        }
//
//        nums++;
//
//    }
//
//}

void farm::plant_seed(Vec2 pos) {

    

}

// �������Ƿ�ӽ�������������
void farm::checkPlayerPosition()
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

         remainingTime = 0;
         player1->removeFromParent();
         auto nextday = farm::create();
         Director::getInstance()->replaceScene(nextday);
           

    }

    // ���±�ǩλ��
    float currentx = 0, currenty = 0;
    if (playerPos.x <= 637) {
        currentx = 637;
    }
    else if (playerPos.x >= 960) {
        currentx = 960;
    }
    else {
        currentx = playerPos.x;  
    }

    if (playerPos.y >= 777) {
        currenty = 777;
    }
    else if (playerPos.y <= 500) {
        currenty = 500;
    }
    else {
        currenty = playerPos.y;
    }

    _timerLabelD->setPosition(currentx - 710, currenty + 570);
    _timerLabelH->setPosition(currentx - 570, currenty + 570);
    _timerLabelS->setPosition(currentx - 430, currenty + 570);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);

    
    // ����ֲ�йصĲ���
    if (plant_area.containsPoint(playerPos)) {
        // �Ƿ�ִ����ֲ
        //if (isPKeyPressed) {

        //    int nums = getRegionNumber(Vec2(playerPos.x + 10, playerPos.y - 10));

        //    std::string TypeName = "wheat";

        //    // �ж��Ƿ������ֲ�ļ���
        //    if ((cropbasicinformation[TypeName].season == Season) || (cropbasicinformation[TypeName].season == "All")) {

        //        Crop_information.push_back(wheat.GetCropCopy());

        //        // ��ʼ���ã����õ�һ��ͼƬ���Ŵ�
        //        player1->setTexture("character1/player_plant1.png");
        //        player1->setScale(2.5f);

        //        // �ӳ�0.3����л����ڶ���ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_plant2.png");  // ����Ϊplayer_plant2
        //            player1->setScale(2.7f);
        //            }, 0.15f, "change_image1_key");

        //        // �ӳ�0.6����л���������ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_left3.png"); // ����Ϊplayer_left3
        //            player1->setScale(1.5f);
        //            this->addChild(Crop_information.back()->GetIcon(), 15 - nums / 19);
        //            Crop_information.back()->SetIcon(cropbasicinformation[Crop_information.back()->GetName()].firstpath);
        //            Crop_information.back()->GetIcon()->setPosition(500 + ((nums % 19) - 1) * 48, 910 - ((nums / 19) - 1) * 48);
        //            Crop_information.back()->GetIcon()->setScale(2.1f);

        //            }, 0.35f, "change_image2_key");

        //    }
        //}
        // �Ƿ�ִ�н�ˮ
        //else if (isWKeyPressed) {
        //   
        //    int nums = getRegionNumber(Vec2(playerPos.x + 25, playerPos.y - 10));
        //    if (Crop_information[nums - 1]->Isplant()) {
        //       
        //        // �������ɫ�ڴ��ڼ��������Ķ���
        //        player1->moveDown = false;
        //        player1->moveLeft = false;
        //        player1->moveUp = false;
        //        player1->moveRight = false;

        //        // ��Ϊ�ѽ�ˮ
        //        Crop_information[nums - 1]->watered = true;

        //        // ��ʼ���ã����õ�һ��ͼƬ���Ŵ�
        //        player1->setTexture("character1/player_water2.png");
        //        player1->setScale(1.7f);

        //        // �ӳ�0.3����л����ڶ���ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_water1.png");  // ����Ϊplayer_water1
        //            player1->setScale(1.7f);
        //            }, 0.15f, "change_image1_key");

        //        // �ӳ�0.6����л���������ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_right3.png"); // ����Ϊplayer_right3
        //            player1->setScale(1.5f);  
        //            // �ָ���ɫ�����Ķ���Ȩ��
        //            player1->moveDown = true;
        //            player1->moveLeft = true;
        //            player1->moveUp = true;
        //            player1->moveRight = true;
        //            }, 0.35f, "change_image2_key");
        //    }
        //}
        // �Ƿ�ִ���ջ�
        //else if (isGKeyPressed) {
        //    
        //    int nums = getRegionNumber(Vec2(playerPos.x + 10, playerPos.y - 10));
        //    if (Crop_information[nums - 1]->harvestable) {
        //        
        //        
        //        Crop_information[nums - 1]->ChangePlant(false);
        //        Crop_information[nums - 1]->harvestable = false;
        //        
        //        // ���Ǿ���
        //        auto test = Sprite::create("farm/tile.png");
        //        this->addChild(test, 15 - nums / 19);
        //        test->setPosition(495 + ((nums % 19) - 1) * 48, 915 - ((nums / 19) - 1) * 48);
        //        test->setScaleX(2.5f);
        //        test->setScaleY(2.9f);

        //        
        //        // ��ʼ���ã����õ�һ��ͼƬ���Ŵ�
        //        player1->setTexture("character1/player_plant1.png");
        //        player1->setScale(2.5f);

        //        // �ӳ�0.3����л����ڶ���ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_plant2.png");  // ����Ϊplayer_plant2
        //            player1->setScale(2.7f);
        //            }, 0.15f, "change_image1_key");

        //        // �ӳ�0.6����л���������ͼƬ
        //        player1->scheduleOnce([=](float dt) {
        //            player1->setTexture("character1/player_left3.png"); // ����Ϊplayer_left3
        //            player1->setScale(1.5f);

        //            }, 0.35f, "change_image2_key");
        //    }


        //}

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

int farm::getRegionNumber(Vec2 pos) {

    // �����������Ĳ���
    int left_bottom_x = 496;  // ���½�x����
    int left_bottom_y = 467;  // ���½�y����
    int width = 912;          // ���ο��
    int height = 480;         // ���θ߶�
    int block_size = 48;      // ÿ��Ĵ�С

    // �����ܵ�����������
    int rows = height / block_size;  // ����
    int cols = width / block_size;   // ����

    // �������������к��б��
    int col = (pos.x - left_bottom_x) / block_size;
    int row = (left_bottom_y + height - pos.y) / block_size;
    // ��ֹԽ��
    if (col < 0) {
        col = 0;
    } 
    if (row < 0) {
        row = 0;
    }
    // ���������ţ����к���
    int region_number = (row)*cols + col + 1;  // ��Ŵ�1��ʼ

    return region_number;
}






