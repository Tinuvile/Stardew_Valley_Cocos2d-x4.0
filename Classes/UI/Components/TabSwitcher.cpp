// TabSwitcher.cpp - 标签切换器组件实现
#include "TabSwitcher.h"
#include "../Builders/SpriteBuilder.h"
#include "../../InventoryUI.h"
#include "../../SkillTreeUI.h"
#include "../../intimacyUI.h"
#include "../../quitUI.h"
#include "../../AppDelegate.h"
#include "../../Inventory.h"

TabSwitcher::TabSwitcher()
    : m_sceneName("")
    , m_activeTab(TabType::INVENTORY)
    , m_theme(UITheme::getInstance())
    , m_config(UIConfig::getInstance())
    , m_bagButton(nullptr)
    , m_skillButton(nullptr)
    , m_intimacyButton(nullptr)
    , m_quitButton(nullptr)
    , m_basePosition(Vec2::ZERO) {
}

TabSwitcher::~TabSwitcher() {
}

TabSwitcher* TabSwitcher::create(const std::string& currentSceneName, TabType activeTab) {
    TabSwitcher* ret = new TabSwitcher();
    if (ret && ret->init(currentSceneName, activeTab)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TabSwitcher::init(const std::string& currentSceneName, TabType activeTab) {
    if (!Node::init()) {
        return false;
    }

    m_sceneName = currentSceneName;
    m_activeTab = activeTab;

    // 获取玩家位置并调整坐标
    Vec2 playerPos = player1->getPosition();
    m_basePosition = m_config->adjustCoordinate(m_sceneName, playerPos);

    createTabButtons();
    updateButtonStates();

    return true;
}

void TabSwitcher::createTabButtons() {
    Size visibleSize = m_theme->getVisibleSize();

    // 创建4个按钮 - 使用原始代码的缩放方式
    m_bagButton = SpriteBuilder()
        .setTexture(UIConfig::UIResources::BAG_KEY)
        .setAutoScale(16.5f)  // 替代原来的 scale/16.5
        .setPosition(getButtonPosition(0, m_basePosition))
        .setZOrder(2)
        .addToParent(this)
        .setClickCallback([this](Sprite*) { onTabClicked(TabType::INVENTORY); })
        .build();

    m_skillButton = SpriteBuilder()
        .setTexture(UIConfig::UIResources::SKILL_KEY)
        .setAutoScale(16.5f)
        .setPosition(getButtonPosition(1, m_basePosition))
        .setZOrder(2)
        .addToParent(this)
        .setClickCallback([this](Sprite*) { onTabClicked(TabType::SKILL_TREE); })
        .build();

    m_intimacyButton = SpriteBuilder()
        .setTexture(UIConfig::UIResources::INTIMACY_KEY)
        .setAutoScale(16.5f)
        .setPosition(getButtonPosition(2, m_basePosition))
        .setZOrder(2)
        .addToParent(this)
        .setClickCallback([this](Sprite*) { onTabClicked(TabType::INTIMACY); })
        .build();

    m_quitButton = SpriteBuilder()
        .setTexture(UIConfig::UIResources::QUIT_KEY)
        .setAutoScale(16.5f)
        .setPosition(getButtonPosition(3, m_basePosition))
        .setZOrder(2)
        .addToParent(this)
        .setClickCallback([this](Sprite*) { onTabClicked(TabType::QUIT); })
        .build();
}

Vec2 TabSwitcher::getButtonPosition(int index, const Vec2& basePosition) {
    Size visibleSize = m_theme->getVisibleSize();

    // 按钮间距
    float xOffset = -0.25f + index * 0.06f;  // -0.25, -0.19, -0.13, -0.07
    float yOffset = (index == static_cast<int>(m_activeTab)) ? 0.305f : 0.315f;  // 激活的按钮稍微下移

    return Vec2(
        basePosition.x + visibleSize.width * xOffset,
        basePosition.y + visibleSize.height * yOffset
    );
}

void TabSwitcher::updateButtonStates() {
    // 更新按钮位置，激活的按钮稍微下移
    if (m_bagButton) {
        m_bagButton->setPositionY(getButtonPosition(0, m_basePosition).y);
    }
    if (m_skillButton) {
        m_skillButton->setPositionY(getButtonPosition(1, m_basePosition).y);
    }
    if (m_intimacyButton) {
        m_intimacyButton->setPositionY(getButtonPosition(2, m_basePosition).y);
    }
    if (m_quitButton) {
        m_quitButton->setPositionY(getButtonPosition(3, m_basePosition).y);
    }
}

void TabSwitcher::setActiveTab(TabType tab) {
    m_activeTab = tab;
    updateButtonStates();
}

void TabSwitcher::setTabCallback(TabType tab, const std::function<void()>& callback) {
    m_callbacks[tab] = callback;
}

void TabSwitcher::onTabClicked(TabType tab) {
    // 如果设置了自定义回调，执行自定义回调
    if (m_callbacks.find(tab) != m_callbacks.end()) {
        m_callbacks[tab]();
        return;
    }

    // 否则执行默认行为
    auto parent = this->getParent();
    if (!parent) return;

    auto scene = Director::getInstance()->getRunningScene();
    if (!scene) return;

    // 重要：在移除自身之前保存需要的数据，避免访问已释放内存
    std::string sceneNameCopy = m_sceneName;  // 复制场景名称
    Inventory* inventoryPtr = inventory;          // 保存全局指针

  
    parent->removeFromParent();  // 移除当前UI - 在这里this可能失效，但局部变量仍然有效

  // 根据标签类型切换到对应UI
  switch (tab) {
  case TabType::INVENTORY:
    // 安全检查：确保inventory指针有效
    if (inventoryPtr) {
      auto inventoryUI = InventoryUI::create(inventoryPtr, sceneNameCopy);
      if (inventoryUI) {
        scene->addChild(inventoryUI, 20);
      }
    }
    break;

  case TabType::SKILL_TREE:
    {
      auto skillTreeUI = SkillTreeUI::create(sceneNameCopy);
      if (skillTreeUI) {
        scene->addChild(skillTreeUI, 20);
      }
    }
    break;

    case TabType::INTIMACY:
    {
      auto intimacyUIInstance = intimacyUI::create(sceneNameCopy);
      if (intimacyUIInstance) {
        scene->addChild(intimacyUIInstance, 20);
      }
    }
    break;

case TabType::QUIT:
    {
      auto quitUIInstance = quitUI::create(sceneNameCopy);
      if (quitUIInstance) {
        scene->addChild(quitUIInstance, 20);
      }
    }
    break;
  }
}

void TabSwitcher::updatePosition(const Vec2& playerPosition) {
    m_basePosition = m_config->adjustCoordinate(m_sceneName, playerPosition);

    // 更新所有按钮位置
    if (m_bagButton) {
        m_bagButton->setPosition(getButtonPosition(0, m_basePosition));
    }
    if (m_skillButton) {
        m_skillButton->setPosition(getButtonPosition(1, m_basePosition));
    }
    if (m_intimacyButton) {
        m_intimacyButton->setPosition(getButtonPosition(2, m_basePosition));
    }
    if (m_quitButton) {
        m_quitButton->setPosition(getButtonPosition(3, m_basePosition));
    }
}
