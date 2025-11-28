#include "InputManager.h"
#include "Player.h"
#include "InventoryUI.h"
#include "AppDelegate.h"

// 包含所有处理器类
#include "PlayerMovementHandler.h"
#include "UIHandler.h"
#include "SceneActionHandler.h"
#include "GlobalActionHandler.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() 
    : keyboardListener(nullptr)
    , isInitialized(false)
    , currentRegisteredScene(nullptr)
    , totalKeyPressedCount(0)
    , handledKeyCount(0)
{
    // 构造函数
}

InputManager::~InputManager() {
    if (keyboardListener) {
        if (currentRegisteredScene) {
            currentRegisteredScene->_eventDispatcher->removeEventListener(keyboardListener);
        }
        keyboardListener = nullptr;
    }
}

InputManager* InputManager::getInstance() {
    if (!instance) {
        instance = new InputManager();
    }
    return instance;
}

void InputManager::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void InputManager::initialize() {
    if (isInitialized) {
        return;
    }
    
    setupKeyboardListener();
    setupHandlerChain(); // 现在所有处理器都已实现
    
    isInitialized = true;
    
    CCLOG("[InputManager] Input system initialized successfully");
}

void InputManager::setupKeyboardListener() {
    if (keyboardListener) {
        return;
    }
    
    keyboardListener = EventListenerKeyboard::create();
    
    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        this->onKeyPressed(keyCode, event);
    };
    
    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        this->onKeyReleased(keyCode, event);
    };
    
    CCLOG("[InputManager] Keyboard listener created");
}

void InputManager::setupHandlerChain() {
    // 创建所有处理器实例
    auto uiHandler = std::make_shared<UIHandler>();
    auto sceneHandler = std::make_shared<SceneActionHandler>();
    auto movementHandler = std::make_shared<PlayerMovementHandler>();
    auto globalHandler = std::make_shared<GlobalActionHandler>();
    
    // 建立责任链：UI优先级最高 -> 场景动作 -> 玩家移动 -> 全局动作
    // 这个顺序确保了：
    // 1. UI事件优先处理（如ESC关闭界面）
    // 2. 场景特定动作其次（如农场的种植）
    // 3. 玩家移动处理（方向键）
    // 4. 全局功能兜底（如帮助、截图）
    uiHandler->setNext(sceneHandler);
    sceneHandler->setNext(movementHandler);
    movementHandler->setNext(globalHandler);
    
    handlerChain = uiHandler;
    
    CCLOG("[InputManager] Handler chain setup completed: UI -> Scene -> Movement -> Global");
}

void InputManager::updateGameContext(const std::string& sceneName, cocos2d::Scene* scene) {
    gameContext.setSceneInfo(sceneName, scene);
    gameContext.updatePlayerPosition();
    
    CCLOG("[InputManager] Game context updated - Scene: %s", sceneName.c_str());
}

void InputManager::setUIState(bool isOpen, const std::string& uiName) {
    gameContext.setUIState(isOpen, uiName);
    
    CCLOG("[InputManager] UI state changed - Open: %s, Name: %s", 
          isOpen ? "true" : "false", uiName.c_str());
}

void InputManager::setGamePaused(bool paused) {
    gameContext.isGamePaused = paused;
    gameContext.canMove = !paused && !gameContext.isUIOpen;
    
    CCLOG("[InputManager] Game paused state changed: %s", paused ? "true" : "false");
}

void InputManager::registerWithScene(cocos2d::Scene* scene) {
    if (!scene || !keyboardListener) {
        CCLOG("[InputManager] Cannot register - scene or listener is null");
        return;
    }
    
    // 如果已经注册了其他场景，先取消注册
    if (currentRegisteredScene && currentRegisteredScene != scene) {
        unregisterFromScene(currentRegisteredScene);
    }
    
    scene->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
    currentRegisteredScene = scene;
    
    CCLOG("[InputManager] Registered keyboard listener with scene");
}

void InputManager::unregisterFromScene(cocos2d::Scene* scene) {
    if (!scene || !keyboardListener) {
        return;
    }
    
    scene->_eventDispatcher->removeEventListener(keyboardListener);
    if (currentRegisteredScene == scene) {
        currentRegisteredScene = nullptr;
    }
    
    CCLOG("[InputManager] Unregistered keyboard listener from scene");
}

void InputManager::setPlayer(Player* player) {
    gameContext.player = player;
    if (player) {
        gameContext.updatePlayerPosition();
        CCLOG("[InputManager] Player reference updated");
    }
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    totalKeyPressedCount++;
    
    // 更新玩家位置
    gameContext.updatePlayerPosition();
    
    bool handled = false;
    
    // 临时处理逻辑，等责任链实现后会替换
    if (handlerChain) {
        handled = handlerChain->handleKeyPressed(keyCode, event, gameContext);
    } else {
        // 临时的基础处理逻辑
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                CCLOG("[InputManager] ESC key pressed (temporary handling)");
                handled = true;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                if (gameContext.canPerformGameAction()) {
                    CCLOG("[InputManager] Arrow key pressed: %d (temporary handling)", static_cast<int>(keyCode));
                    handled = true;
                }
                break;
            default:
                break;
        }
    }
    
    if (handled) {
        handledKeyCount++;
    }
    
    CCLOG("[InputManager] Key pressed: %d, Handled: %s", 
          static_cast<int>(keyCode), handled ? "true" : "false");
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    // 更新玩家位置
    gameContext.updatePlayerPosition();
    
    bool handled = false;
    
    if (handlerChain) {
        handled = handlerChain->handleKeyReleased(keyCode, event, gameContext);
    }
    
    CCLOG("[InputManager] Key released: %d, Handled: %s", 
          static_cast<int>(keyCode), handled ? "true" : "false");
}

void InputManager::openInventory(const std::string& sceneName) {
    // 检查是否已经有界面打开
    if (gameContext.isUIOpen) {
        CCLOG("[InputManager] Cannot open inventory - UI already open: %s", gameContext.activeUI.c_str());
        return;
    }
    
    // 创建背包界面
    auto inventoryUI = InventoryUI::create(inventory, sceneName);
    if (inventoryUI && gameContext.scene) {
        gameContext.scene->addChild(inventoryUI, 20);
        setUIState(true, "InventoryUI");
        CCLOG("[InputManager] Inventory opened for scene: %s", sceneName.c_str());
    } else {
        CCLOG("[InputManager] Failed to create inventory UI");
    }
}

void InputManager::closeCurrentUI() {
    if (!gameContext.isUIOpen || gameContext.activeUI.empty()) {
        CCLOG("[InputManager] No UI to close");
        return;
    }
    
    // 查找并移除当前UI
    if (gameContext.scene) {
        auto uiNode = gameContext.scene->getChildByName(gameContext.activeUI);
        if (uiNode) {
            gameContext.scene->removeChild(uiNode, true);
            CCLOG("[InputManager] Closed UI: %s", gameContext.activeUI.c_str());
        } else {
            CCLOG("[InputManager] UI node not found: %s", gameContext.activeUI.c_str());
        }
    }
    
    setUIState(false);
}
