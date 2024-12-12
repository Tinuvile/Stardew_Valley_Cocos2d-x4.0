#include "AppDelegate.h"
#include "Town.h"
#include "Crop.h"
#include "supermarket.h"
#include "Player.h"
#include "ui/CocosGUI.h"
#include "InventoryUI.h"

USING_NS_CC;

Town::Town() {}

Town::~Town() {}

bool Town::init()
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

    // �����еĳ�ʼ��Ʒ���
    inventory->AddItem ( Bamboo_Pole );

    inventory->AddItem ( Apple_Sapling );

    inventory->AddItem ( Apple_Sapling );

    inventory->AddItem ( Potato_Seeds );

    inventory->AddItem ( Carrot_Seeds );

    inventory->AddItem ( Cauliflower_Seeds );

    inventory->AddItem ( Coffee_Bean );

    inventory->AddItem ( Garlic_Seeds );

    inventory->AddItem ( Jazz_Seeds );

    inventory->AddItem ( Kale_Seeds );

    inventory->AddItem ( Parsnip_Seeds );

    inventory->AddItem ( Rhubarb_Seeds );

    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF("Position: (0, 0)", "fonts/Marker Felt.ttf", 24);
    if (_positionLabel)
    {
        this->addChild(_positionLabel, 10);
        _positionLabel->setScale(2.3f);
    }

    // ���ñ���ͼƬ
    auto background_real = Sprite::create("Town/Town.png");
    background_real->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_real, 1);
    background_real->setScale(1.7f);

    auto background_up = Sprite::create("Town/Town_up.png");
    background_up->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background_up, 7);
    background_up->setScale(1.7f);

    auto background = Sprite::create("Town/Town_path.png");
    this->addChild(background, 5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(1.7f);


    Vec2 spritePosition = background->getPosition();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = background->getContentSize();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�
  

    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2(
        spritePosition.x - background->getScaleX() * spriteSize.width / 2,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - background->getScaleY() * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );
   

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
                    float screenX = leftBottomPosition.x + x * background->getScaleX();
                    float screenY = leftBottomPosition.y + (height - y - 1) * background->getScaleY();  // ע�� Y �ᷴ��
                    nonTransparentPixels.push_back(Vec2(screenX, screenY));  // ��¼��Ļ����
                }
            }
        }
    }


    // ��ʼ�����ż�
    opendoor = Sprite::create("opendoor.png");
    this->addChild(opendoor, 11);

    // �ָ���ҵ�״̬
    if (player1)
    {
        for (auto& pair : T_lastplace) {
            if (pair.second == true) {  // ��� bool ֵ�Ƿ�Ϊ true
                player1->setPosition(pair.first.second);
                pair.second = false;
            }
        }
        player1->speed = 2.5f;
    }

    cocos2d::log("transform");

    // ��ʼ����ɫ��������ӵ�����
    if (player1->getParent() == NULL) {
        cocos2d::log("player1->get");
        this->addChild(player1, 5);
    }
    player1->setScale(1.5f);
    player1->setAnchorPoint(Vec2(0.5f, 0.2f));
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

    // ʹ�� getAbigailAnimations() ��ȡ NPC ����֡  
    auto abigailAnimations = getAbigailAnimations ();
    // ���� NPC ʾ��  
    auto abigail = NPCreate::CreateNPC ( "Abigail" , cocos2d::Vec2 ( -100 , 400 ) , abigailAnimations , nonTransparentPixels );
    if (abigail) {
        // CCLOG ( "NPC Abigail created successfully." );
        auto abigailSprite = abigail->GetSprite ();
        if (abigailSprite) {
            // CCLOG ( "Abigail sprite created successfully at position: (%f, %f)" , abigailSprite->getPositionX () , abigailSprite->getPositionY () );
            this->addChild ( abigailSprite , 5 ); // ȷ����ӵ�������  

            // ʹ�õ�����ÿ 1.0 ����� RandomMove  
            this->schedule ( [abigail]( float dt ) {
                abigail->RandomMove ();

                // ��ȡ Abigail �ĵ�ǰλ��  
                auto abigailSprite = abigail->GetSprite (); // ��ȡ����  
                if (abigailSprite) {
                    // ��ȡ��ǰ�����λ�úʹ�С  
                    Vec2 position = abigailSprite->getPosition ();
                    Size size = abigailSprite->getContentSize ();
                    // CCLOG ( "Abigail's current position: (%f, %f)" , position.x , position.y ); // ��ӡλ��  
                }
            } , 1.0f , "random_move_key" ); // ÿ 1.0 ������ƶ�һ��  
        }
        else {
            CCLOG ( "Abigail sprite is nullptr." );
        }
    }
    else {
        CCLOG ( "Failed to create NPC Abigail." );
    }

    // ����Ľ����뾶  
    const float interactionRadius = 30.0f;

    // ����¼�������
    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this , abigail , interactionRadius]( Event* event ) {

        // ��ȡ�������λ��
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos ( mouseEvent->getCursorX () , mouseEvent->getCursorY () );
        clickPos = this->convertToNodeSpace ( clickPos );

        // ����Ƿ����� Abigail   
        if (abigail) {
            auto abigailSprite = abigail->GetSprite ();
            if (abigailSprite && abigailSprite->getBoundingBox ().containsPoint ( clickPos )) {
                // ��ȡ��ҵ�λ��  
                Vec2 playerPos = player1->getPosition ();

                // ��������� Abigail ֮��ľ���  
                float distance = playerPos.distance ( abigailSprite->getPosition () );

                // �� InventoryUI  
                static InventoryUI* currentInventoryUI = nullptr; // ���浱ǰ��ʾ�� InventoryUI  
                if (currentInventoryUI == nullptr) {
                    currentInventoryUI = InventoryUI::create ( inventory );
                    this->addChild ( currentInventoryUI , 11 ); // �� InventoryUI ��ӵ� Town ���ϲ�  
                }

                /*
                // �������Ƿ�������ķ�Χ��
                if (distance <= interactionRadius) {
                    CCLOG ( "Abigail clicked and player is within range! Opening InventoryUI." );
                    // �� InventoryUI
                    static InventoryUI* currentInventoryUI = nullptr; // ���浱ǰ��ʾ�� InventoryUI
                    if (currentInventoryUI == nullptr) {
                        currentInventoryUI = InventoryUI::create ( inventory );
                        this->addChild ( currentInventoryUI , 11 ); // �� InventoryUI ��ӵ� Town ���ϲ�
                    }
                }
                else {
                    CCLOG ( "Player is too far from Abigail to interact." );
                }
                */
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , button );

    // ���ü��̼�����  
    auto listenerWithPlayer = EventListenerKeyboard::create ();
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        // ��¼ Enter ��������  
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
            isEnterKeyPressed = true;
            CCLOG ( "Enter key pressed." );
        }
        // ������������  
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            static InventoryUI* currentInventoryUI = nullptr;  // ���浱ǰ��ʾ�� InventoryUI  
            // �����ǰû�д� InventoryUI�������  
            if (currentInventoryUI == nullptr) {
                CCLOG ( "Opening inventory." );
                currentInventoryUI = InventoryUI::create ( inventory );
                this->addChild ( currentInventoryUI , 11 );  // �� InventoryUI ��ӵ� Town ���ϲ�  
            }
            // ����Ѿ��� InventoryUI����ر���  
            else {
                CCLOG ( "Closing inventory." );
                this->removeChild ( currentInventoryUI , true );  // �ӵ�ǰ�������Ƴ� InventoryUI  
                currentInventoryUI = nullptr;  // ����ָ��  
            }
        }
        };

    listenerWithPlayer->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        // �ͷ� Enter ��ʱ������Ϊ false  
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
            isEnterKeyPressed = false;
            CCLOG ( "Enter key released." );
        }
        };

    // ����������ӵ��¼��ַ�����  
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerWithPlayer , this );

    return true;
}


Town* Town::create()
{
    Town* scene = new Town();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

// �������Ƿ�ӽ�������������
void Town::checkPlayerPosition()
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

        for (auto it = Crop_information.begin(); it != Crop_information.end();) {

            auto crop = *it;  // �����õ������Է��� Crop ����

            // �ж�ǰһ���Ƿ�ˮ
            if ((crop->watered == false) && (crop->GetPhase() != Phase::MATURE)) {
                // �ж��Ƿ��Ѿ������ή״̬
                if (crop->GetPhase() != Phase::SAPLESS) {
                    crop->ChangePhase(Phase::SAPLESS);
                    crop->ChangMatureNeeded(2); // �ӳ������ջ�
                    it++;
                }
                else {
                    // ɾ��Ԫ�ز����µ�����
                    it = Crop_information.erase(it);
                }

            }
            else {
                // ����״̬
                crop->UpdateGrowth();
                it++;
            }

        }

        for (auto& pair : F_lastplace) {
            if (pair.first.first == "myhouse") {  // ��� bool ֵ�Ƿ�Ϊ true
                pair.second = true;
            }
        }


        remainingTime = 0;
        player1->removeFromParent();
        auto nextday = Myhouse::create();
        Director::getInstance()->replaceScene(nextday);



    }

    // ���±�ǩλ��
    float currentx = 0, currenty = 0;
    if (playerPos.x <= -117) {
        currentx = -117;
    }
    else if (playerPos.x >= 1773) {
        currentx = 1773;
    }
    else {
        currentx = playerPos.x;
    }

    if (playerPos.y >= 1498) {
        currenty = 1498;
    }
    else if (playerPos.y <= -222) {
        currenty = -222;
    }
    else {
        currenty = playerPos.y;
    }

    _timerLabelD->setPosition(currentx - 710, currenty + 570);
    _timerLabelH->setPosition(currentx - 570, currenty + 570);
    _timerLabelS->setPosition(currentx - 430, currenty + 570);
    _positionLabel->setPosition(currentx - 570, currenty + 490);
    button->setPosition(currentx + 730, currenty - 590);
   
    // �������Ƿ����Ŀ�����򣬲��Ұ��� Enter ��
    if (Region_supermarket.containsPoint(playerPos)) {
        // ��ҽ���Ŀ������
        opendoor->setVisible(true);
        opendoor->setPosition(playerPos.x + 110, playerPos.y + 30);
        CCLOG("Player in target area");

        if (isEnterKeyPressed) {
            for (auto& pair : T_lastplace) {
                if (pair.first.first == "seedshop") {  // ��� bool ֵ�Ƿ�Ϊ true
                    pair.second = true;
                }
            }
            // ��ӡ������Ϣ����� Enter ����״̬
            CCLOG("Player in target area, isEnterKeyPressed: %d", isEnterKeyPressed);
            // ���ó����л��߼�
            player1->removeFromParent();
            seedshop = supermarket::create();
            Director::getInstance()->replaceScene(seedshop);
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






