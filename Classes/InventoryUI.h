// InventoryUI.h - 背包界面（使用建造者模式重构）
#pragma once
#include "cocos2d.h"
#include "Inventory.h"
#include "AppDelegate.h"
#include "UI/ClosableUI.h"

class InventoryUI : public ClosableUI {
public:
    virtual bool init(Inventory* inventory, std::string sceneName);
    static InventoryUI* create(Inventory* inventory, std::string sceneName);

    void updateDisplay(); // 更新物品显示

private:
    // UI设置方法 - 使用建造者模式重构
    void setupUI();
    void setupItemSlots();

private:
    Inventory* _inventory; // 背包实例指针
    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的Sprite
    int _selectedSlot; // 当前选中的槽位
    std::string m_sceneName; // 场景名称
    cocos2d::Label* _itemLabel; // 显示物品信息的标签
    bool isClick = false; // 标志位，表示是否被点击过
    cocos2d::Sprite* currentItemSprite = nullptr; // 标识当前选中的物品
};
