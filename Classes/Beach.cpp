#include "AppDelegate.h"
#include "Beach.h"
#include "farm.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

Beach::Beach () {}

Beach::~Beach () {}

bool Beach::init ()
{
    //��ȡ��Ļ��Χ������
    auto visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    //�����˳���ť
    button = cocos2d::Sprite::create ( "CloseNormal.png" );
    this->addChild ( button , 11 );

    // ���ü�ʱ����ǩ
   // ���ü�ʱ����ǩ
    TimeUI = Timesystem::create ( "Beach" );
    this->addChild(TimeUI, 13);

    if (Weather == "Rainy") {
        // ����
        createRainEffect();
    }
    // ��������ʼ�� Label ����ʾ��ɫ��λ��
    _positionLabel = Label::createWithTTF ( "Position: (0, 0)" , "fonts/Marker Felt.ttf" , 24 );
    if (_positionLabel) {
        this->addChild ( _positionLabel , 10 );
        _positionLabel->setScale ( 1.3f );
    }
    _positionLabel->setPosition ( 130 , 1200 );


    // ���ñ���ͼƬ
    auto background_real = Sprite::create ( "Beach/Beach.png" );
    background_real->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    this->addChild ( background_real , 1 );
    background_real->setScale ( 2.3f );

    auto immovable_background = Sprite::create ( "Beach/Beach_path.png" );
    this->addChild ( immovable_background , 5 );
    immovable_background->setPosition ( Vec2 ( visibleSize.width / 2 , visibleSize.height / 2 ) );
    immovable_background->setScale ( 2.3f );


    Vec2 spritePosition = immovable_background->getPosition ();   // ��ȡ�����λ�ã����ĵ㣩
    Size spriteSize = immovable_background->getContentSize ();    // ��ȡ����ĳߴ磨��Ⱥ͸߶ȣ�


    // �������½ǵ�����
    Vec2 leftBottomPosition = Vec2 (
        spritePosition.x - immovable_background->getScaleX () * spriteSize.width / 2 ,   // ���ĵ� x �����ȥ��ȵ�һ��
        spritePosition.y - immovable_background->getScaleY () * spriteSize.height / 2   // ���ĵ� y �����ȥ�߶ȵ�һ��
    );


    Image img;
    if (img.initWithImageFile ( "Beach/Beach_path.png" ))
    {
        int width = img.getWidth ();
        int height = img.getHeight ();

        // ��ȡ��������
        unsigned char* data = img.getData ();

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
                    float screenX = leftBottomPosition.x + x * immovable_background->getScaleX ();
                    float screenY = leftBottomPosition.y + (height - y - 1) * immovable_background->getScaleY ();  // ע�� Y �ᷴ��
                    non_transparent_pixels.push_back ( Vec2 ( screenX , screenY ) );  // ��¼��Ļ����
                }
            }
        }
    }


    // ��ʼ����ɫ��������ӵ�����
    if (player1->getParent () == NULL) {
        this->addChild ( player1 , 11 );
        player1->setScale ( 1.6f );
        player1->setPosition ( 320 , 1400 );
        player1->setAnchorPoint ( Vec2 ( 0.5f , 0.2f ) );


    }

    // ��������Ķ�ʱ��
    player1->schedule ( [=]( float dt ) {
        player1->player1_move ();
        } , 0.05f , "player1_move" );

    player1->schedule ( [=]( float dt ) {
        player1->player_change ();
        } , 0.3f , "player_change" );


    // ���㱳����������ź�Χ
    float scaledWidth = immovable_background->getContentSize ().width * immovable_background->getScaleX ();
    float scaledHeight = immovable_background->getContentSize ().height * immovable_background->getScaleY ();

    // ���� Follow �ı߽� Rect
    auto followRect = cocos2d::Rect ( leftBottomPosition.x , leftBottomPosition.y , scaledWidth , scaledHeight );

    // ���� Follow ��������������ڱ�����Χ���ƶ�
    auto followAction = Follow::create ( player1 , followRect );
    this->runAction ( followAction );

    // ���ڸ������״̬
    this->schedule ( [this]( float dt ) {
        this->CheckPlayerPosition ();  // �������Ƿ�ӽ�������
        } , 0.01f , "check_position_key" );

    auto listener = EventListenerMouse::create ();
    listener->onMouseDown = [this]( Event* event ) {

        // ��ȡ�������λ��
        auto mouseEvent = static_cast<EventMouse*>(event);
        Vec2 clickPos ( mouseEvent->getCursorX () , mouseEvent->getCursorY () );
        clickPos = this->convertToNodeSpace ( clickPos );

        // �жϵ��λ���Ƿ��ھ��鷶Χ��
        if (button != nullptr && button->getBoundingBox ().containsPoint ( clickPos )) {
            Director::getInstance ()->end ();
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listener , button );

    // ���ü��̼�����
    auto listenerWithPlayer = EventListenerKeyboard::create ();
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG ( "Enter key pressed. " );
            }
        };

    listenerWithPlayer->onKeyReleased = [this]( EventKeyboard::KeyCode keyCode , Event* event )
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
            }
        };

    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode key_code , Event* event ) {
        if (key_code == EventKeyboard::KeyCode::KEY_H) {

            if (!this->getChildByName ( "FishingGameLayer" )) {
                //��������Ϸ������볡����
                auto fishing_game = FishingGame::create ( player1->getPosition () );
                this->addChild ( fishing_game , 10 , "FishingGameLayer" );
                ////��ͣ�����������ڵ�Ļ
                //player1->pause ();
                //this->pause ();
            }
        }
        else if (key_code == EventKeyboard::KeyCode::KEY_ESCAPE) {
            static int isOpen = 0;
            static InventoryUI* currentInventoryUI = nullptr;  // ���浱ǰ��ʾ�� InventoryUI  
            // �����ǰû�д� InventoryUI�������  
            if (currentInventoryUI == nullptr || isOpen == 0) {
                isOpen = 1;
                CCLOG ( "Opening inventory." );
                currentInventoryUI = InventoryUI::create ( inventory , "Beach" );
                this->addChild ( currentInventoryUI , 30 );  // �� InventoryUI ��ӵ��ϲ�  
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

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority ( listenerWithPlayer , this );


    //�����µı�����ʾ
    miniBag = mini_bag::create ( inventory );
    miniBag->setScale ( 1.0f );
    Vec2 pos = miniBag->getPosition ();
    if (miniBag != NULL) {
        cocos2d::log ( "miniBagtest %f" , pos.x );
    }
    if (!this->getChildByName ( "mini_bag" )) {
        this->addChild ( miniBag , 10 , "mini_bag" );
    }


    // ������Ʒ��
    schedule ( [=]( float deltaTime ) {
        if (inventory->is_updated == true) {
            miniBag->updateDisplay ();
            inventory->is_updated = false;
        }
        } , 0.1f , "item_update_key" );

        return true;
        }


        Beach * Beach::create ()
    {
        Beach* scene = new Beach ();
        if (scene && scene->init ())
        {
            scene->autorelease ();
            return scene;
        }
        CC_SAFE_DELETE ( scene );
        return nullptr;
    }


    // �������Ƿ�ӽ�������������
    void Beach::CheckPlayerPosition ()
    {

        // ��ȡ��ҵ�λ��
        Vec2 playerPos = player1->getPosition ();

        // ����λ�ñ�ǩ������
        if (_positionLabel)
        {
            _positionLabel->setString ( "Position: (" + std::to_string ( static_cast<int>(playerPos.x) ) + ", " + std::to_string ( static_cast<int>(playerPos.y) ) + ")" );

        }

        // ���¼�ʱ����ʾ
        remainingTime++;
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

            if (day % 3 == 1) {
                Weather = "Rainy";
            }
            else {
                Weather = "Sunny";
            }

            if ((Season == "Spring") && (day == 1)) {
                Festival = "Fishing Day";
            }
            else {
                Festival = "Noraml Day";
            }


            for (auto it = Crop_information.begin(); it != Crop_information.end();) {

                auto crop = *it;  // �����õ������Է��� Crop ����

                if (Weather == "Rainy") {
                    crop->watered = true;
                }

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
        float currentx = 0 , currenty = 0;
        if (playerPos.x <= -315) {
            currentx = -315;
        }
        else if (playerPos.x >= 20000) {
            currentx = 20000;
        }
        else {
            currentx = playerPos.x;
        }

        if (playerPos.y >= 920) {
            currenty = 920;
        }
        else if (playerPos.y <= 360) {
            currenty = 360;
        }
        else {
            currenty = playerPos.y;
        }

        _positionLabel->setPosition ( currentx - 570 , currenty + 490 );
        button->setPosition ( currentx + 730 , currenty - 590 );
        miniBag->setPosition ( currentx , currenty );
        TimeUI->setPosition(currentx, currenty);

        // �Ƿ����ũ��
        if (Out_Beach.containsPoint ( playerPos )) {
            if (isEnterKeyPressed) {
                player1->removeFromParent ();
                auto NextSence = farm::create ();
                Director::getInstance ()->replaceScene ( NextSence );
            }
        }


        for (const auto& point : non_transparent_pixels)
        {
            // ���������������֮��ľ���
            float distance = 0;

            Vec2 temp;
            temp = playerPos;
            temp.x -= player1->speed;
            distance = temp.distance ( point );
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
            distance = temp.distance ( point );
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
            distance = temp.distance ( point );
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
            distance = temp.distance ( point );
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

    void Beach::createRainEffect() {

        emitter = ParticleRain::create();
        emitter->setDuration(ParticleSystem::DURATION_INFINITY);
        emitter->setScale(5.7f);
        emitter->setTotalParticles(100);
        emitter->setSpeed(250);

        addChild(emitter, 10);

        // ÿ֡����������������
        schedule([this](float dt) {
            updaterain(dt);
            }, "update_rain_key");

    }

    void Beach::updaterain(float deltaTime) {
        if (emitter) {
            // �������һ���������ڣ���Χ 1 �� 1.5 ��֮�䣩
            float newLife = cocos2d::rand_0_1() * 1.5f;

            // �����µ���������
            emitter->setLife(newLife);

            emitter->setEmissionRate(emitter->getTotalParticles() / emitter->getLife() * 1.3);
        }
    }