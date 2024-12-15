#include "AppDelegate.h"
#include "Barn.h"
#include "farm.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

Barn::Barn() {}

Barn::~Barn() {}

bool Barn::init()
{
    //��ȡ�������ľ��ο�
    if (barn_space.size () < kMaxLivestock) {
        auto scene_size= Director::getInstance ()->getVisibleSize ();

        float rectWidth = scene_size.width / 14;
        float rectHeight = scene_size.height / 12;

        // ����ÿ����������
        for (int row = 0; row < 12; ++row) {
            for (int col = 0; col < 14; ++col) {
                if ( (row ==2 || row == 4 || row ==6) &&
                    col % 2 == 0 && col >= 6) {
                    // ���½�����
                    float x = col * rectWidth;
                    float y = row * rectHeight;

                    // �������β��洢�� vector ��
                    cocos2d::Rect rect ( x , y , rectWidth , rectHeight );
                    barn_space.push_back ( std::make_pair ( rect , false ) );
                    if (row == 6 && col == 7) {
                        break;
                    }
                }
                else {
                    continue;
                }
            }
        }
    }

    //�������Լ���
    Cow* test_cow = Cow::create ( barn_space[0].first );
    livestocks.push_back ( test_cow );
    this->addChild ( livestocks[0] , 10);

    Chicken* test_chicken = Chicken::create ( barn_space[1].first );
    livestocks.push_back ( test_chicken );
    this->addChild ( livestocks[1] , 10 );
    
   /* Sheep* test_sheep = Sheep::create(barn_space[2].first);
    livestocks.push_back(test_sheep);
    this->addChild ( livestocks[2] , 10 );*/

    for (int i = 0; i < 9; i++) {
        auto test_animal = Chicken::create ( barn_space[3 + i].first );
        livestocks.push_back ( test_animal );
        this->addChild ( livestocks[3 + i] , 10 );
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    // ���ü�ʱ����ǩ
    _timerLabelD = Label::createWithTTF("Day: 0", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelD, 10);
    _timerLabelD->setScale(1.3f);
    _timerLabelD->setPosition(Vec2(50, 1250));

    _timerLabelH = Label::createWithTTF("0:00", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelH, 10);
    _timerLabelH->setScale(1.3f);
    _timerLabelH->setPosition(Vec2(130, 1250));

    _timerLabelS = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 24);
    this->addChild(_timerLabelS, 10);
    _timerLabelS->setScale(1.3f);
    _timerLabelS->setPosition(Vec2(210, 1250));

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel) {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(1.3f);
    }
    _positionLabel->setPosition(130, 1200);


    // ���ñ���ͼƬ
    auto background_real = Sprite::create("Barn/Barn.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(5.1f);

    auto background = Sprite::create("Barn/Barn_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(5.1f);


    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�


    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );


    Image img;
    if (img.initWithImageFile("Barn/Barn_path.png"))
    {
        int width = img.getWidth();
        int height = img.getHeight();

        // ��ȡ��������
        unsigned char* data = img.getData();

        // �����������أ�����Ƿ������ݣ�͸���ȴ���0��
        for (int y = 0; y < height; y = y + 2)
        {
            for (int x = 0; x < width; x = x + 2)
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
    if (player1->getParent() == NULL) {
        this->addChild(player1, 11);
        player1->setScale(2.7f);
        player1->setPosition(700, 450);
        player1->speed = 7.0f;
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
            else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
                static int isOpen = 0;
                static InventoryUI* currentInventoryUI = nullptr;  // ���浱ǰ��ʾ�� InventoryUI  
                // �����ǰû�д� InventoryUI�������  
                if (currentInventoryUI == nullptr || isOpen == 0) {
                    isOpen = 1;
                    CCLOG ( "Opening inventory." );
                    currentInventoryUI = InventoryUI::create ( inventory , "Barn" );
                    this->addChild ( currentInventoryUI , 20 );  // �� InventoryUI ��ӵ��ϲ�  
                }
                // ����Ѿ��� InventoryUI����ر���  
                else {
                    isOpen = 0;
                    CCLOG ( "Closing inventory." );
                    this->removeChild ( currentInventoryUI , true );  // �ӵ�ǰ�������Ƴ� InventoryUI  
                    currentInventoryUI = nullptr;  // ����ָ��  
                }
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                isEnterKeyPressed = false;
            }
        };

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

    // ������������
    auto mouse_listener = cocos2d::EventListenerMouse::create ();

    // ������¼��Ļص�����
    mouse_listener->onMouseDown = CC_CALLBACK_1 ( Barn::GetProduction , this );

    // ����������ӵ��¼��ַ���
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( mouse_listener , this );


    return true;
}


Barn* Barn::create()
{
    Barn* scene = new Barn();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}


// �������Ƿ�ӽ�������������
void Barn::checkPlayerPosition()
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
    _timerLabelD->setString("Day: " + std::to_string(day));
    _timerLabelH->setString(std::to_string(remainingTime / 1800) + ":00");
    _timerLabelS->setString(Season);
    if (remainingTime == 432000) {

        day++;
        /*IsNextDay = true;*/

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

        //for (auto it = Crop_information.begin(); it != Crop_information.end(); /* no increment here */) {

        //    auto crop = *it;  // �����õ������Է��� Crop ����

        //     �ж�ǰһ���Ƿ�ˮ
        //    if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
        //         �ж��Ƿ��Ѿ������ή״̬
        //        if (crop->GetPhase() != Phase::SAPLESS) {
        //            crop->ChangePhase(Phase::SAPLESS);
        //            crop->ChangMatureNeeded(2); // �ӳ������ջ�
        //        }
        //        else {
        //             ɾ��Ԫ�ز����µ�����
        //            it = Crop_information.erase(it);
        //        }
        //        ++it;
        //        continue;  // �����������룬ֱ�Ӽ���ѭ��
        //    }
        //    else {
        //         ����״̬
        //        crop->UpdateGrowth();
        //    }

        //    it++;
        //}

        player1->removeFromParent();
        auto nextday = farm::create();
        Director::getInstance()->replaceScene(nextday);


    }



    // �Ƿ����ũ��
    if (Out_Barn.containsPoint(playerPos)) {
        if (isEnterKeyPressed) {
            player1->removeFromParent();
            auto NextSence = farm::create();
            Director::getInstance()->replaceScene(NextSence);
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
        else {
            if (player1->rightpressed == false) {
                player1->moveRight = true;
            }
        }

    }


}

void Barn::GetProduction ( cocos2d::EventMouse* event ) {
    // �ж��Ƿ�������Ҽ����
    if (event->getMouseButton () == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
    {
        // ��ȡ�����λ��
        cocos2d::Vec2 click_pos = this->convertToNodeSpace ( event->getLocationInView () );

        //����livestocks
        for (auto& livestock : livestocks) {
            if (livestock->IsCanProduce ()) {
                // �жϵ��λ���Ƿ��� Sprite �ڲ�
                if (livestock->getBoundingBox ().containsPoint ( click_pos )) {
                    CCLOG ( "Right-clicked on the produce_enabled livestock!" );
                    auto product = livestock->ProduceProduct ();
                    inventory->AddItem ( *product );
                    inventory->DisplayPackageInCCLOG ();
                    //���¶�Ӧlivestock��can_produce״̬Ϊfalse
                    livestock->SetCanProduce ( false );
                }

            }

        }
    }
}






