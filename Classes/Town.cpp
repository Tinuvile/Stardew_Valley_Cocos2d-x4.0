#include "AppDelegate.h"
#include "Town.h"
#include "supermarket.h"
#include "Player.h"
#include "physics/CCPhysicsWorld.h"
#include "ui/CocosGUI.h"

#include"Inventory.h"
#include"Item.h"
#include"Crop.h"
#include "InventoryUI.h"
#include "NPCreate.h"

USING_NS_CC;

extern int remainingTime;
extern Player* player1;
extern Town* town;
extern supermarket* seedshop;
extern std::map <std::pair<std::string, Vec2>, bool> T_lastplace;


Town::Town() {}

Town::~Town() {}

bool Town::init()
{


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    button = cocos2d::Sprite::create("CloseNormal.png");
    this->addChild(button, 11);

    
    // ���� Inventory ʵ��  
    inventory = new Inventory ();

    // �����Ʒ�����  
    Item Grass ( "Grass" , "Item/Grass/grass-0.png" , 1 , 99 );
    Item Tools ( "Tools" , "Item/Tools/tools-16.png" , 1 , 99 );

    bool addedSuccessfully = inventory->AddItem ( Grass );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 1 ); // ��������ѡ���һ����λ
        CCLOG ( "Item 'Grass' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Grass'. Inventory might be full." );
    }

    addedSuccessfully = inventory->AddItem ( Tools );
    if (addedSuccessfully) {
        inventory->SetSelectedItem ( 2 ); // ��������ѡ���һ����λ
        CCLOG ( "Item 'Grass' added successfully." );
    }
    else {
        CCLOG ( "Failed to add item 'Grass'. Inventory might be full." );
    }
    

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
        player1->speed = 1.5f;
    }

    // ��ʼ����ɫ��������ӵ�����
    if (player1->getParent() == NULL) {
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


    /*
    // ���� NPC  
    NPC* npc1 = NPCreate::CreateNPC ( "NPC1" , Vec2 ( 300 , 400 ) , "npc/Abigail/Abigail-0.png" ); // NPC 1  
    NPC* npc2 = NPCreate::CreateNPC ( "NPC2" , Vec2 ( 500 , 600 ) , "npc/Abigail/Abigail-1.png" ); // NPC 2  
    NPC* npc3 = NPCreate::CreateNPC ( "NPC3" , Vec2 ( 700 , 300 ) , "npc/Abigail/Abigail-2.png" ); // NPC 3  
  
    npc1->GetSprite ()->setScale ( player1->getScale () * 2.2 );
    npc2->GetSprite ()->setScale ( player1->getScale () * 2.2 );
    npc3->GetSprite ()->setScale ( player1->getScale () * 2.2 );

    this->addChild ( npc1->GetSprite () , 5 ); // ��� NPC 1 ������  
    this->addChild ( npc2->GetSprite () , 5 ); // ��� NPC 2 ������  
    this->addChild ( npc3->GetSprite () , 5 ); // ��� NPC 3 ������ 
    */  


    // ���ü��̼�����
    auto listenerWithPlayer = EventListenerKeyboard::create();
    listenerWithPlayer->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // ��¼ Enter ��������
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = true;
                CCLOG("Enter key pressed. ");
            }
        };

    listenerWithPlayer->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // �ͷ� Enter ��ʱ������Ϊ false
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
                isEnterKeyPressed = false;
                CCLOG("Enter key released. ");
            }
        };
    listenerWithPlayer->onKeyPressed = [this]( EventKeyboard::KeyCode keyCode , Event* event ) {
        // �������Ĵ���  

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

    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerWithPlayer, this);

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


    // ����ʣ��ʱ��
    remainingTime = remainingTime--;

    // ���¼�ʱ����ʾ
    remainingTime--;
    _timerLabel->setString("Timer: " + std::to_string(remainingTime / 60));

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

    
    _timerLabel->setPosition(currentx - 630, currenty + 570);
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






