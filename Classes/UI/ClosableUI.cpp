// ClosableUI.cpp - 可关闭UI基类实现
#include "ClosableUI.h"

ClosableUI::ClosableUI()
    : m_keyboardListener(nullptr) {
}

ClosableUI::~ClosableUI() {
    // EventListener会被Cocos2d-x自动管理和清理
    m_keyboardListener = nullptr;
}

bool ClosableUI::init() {
    if (!Layer::init()) {
        return false;
    }

    return true;
}

void ClosableUI::setupEscCloseListener() {
    // 创建键盘事件监听器
    m_keyboardListener = EventListenerKeyboard::create();

    // 设置按键按下回调
    m_keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            // 调用虚方法，允许子类自定义行为
            this->onEscPressed();
        }
    };

    // 将监听器添加到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);
}

void ClosableUI::onEscPressed() {
    // 默认行为：移除UI
    this->removeFromParent();
}
