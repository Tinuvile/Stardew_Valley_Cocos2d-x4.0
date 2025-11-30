#pragma once
// StoreUI.h - 商店界面（使用建造者模式重构）
#include "cocos2d.h"
#include "Inventory.h"
#include "AppDelegate.h"
#include "EconomicSystem.h"
#include "UI/Core/UITheme.h"
#include "UI/Core/UIConfig.h"

USING_NS_CC;

class StoreUI : public cocos2d::Layer {
public:
    virtual bool init(Inventory* mybag, Inventory* goods);
    static StoreUI* create(Inventory* mybag, Inventory* goods);

    void updateDisplay(); // 更新物品显示
    void updateCoordinate(float& x, float& y);

    void onItemSlotClicked(cocos2d::Ref* sender); // 物品槽的点击事件处理

private:
    // UI设置方法 - 使用建造者模式重构
    void setupUI();
    void backgroundcreate();
    void setupCharacterDisplay();
    void setupProductDisplay();
    void setupMoneyDisplay();
    void setupSlider();
    void setupItemSlots();
    void setupInteractions();
    void setupMouseEvents();
    void setupProductItemMouseEvents(cocos2d::Sprite* itemFrame, std::shared_ptr<Item> item, int index);

private:
    // 核心数据
    Inventory* _mybag; // 指向自己背包实例的指针
    Inventory* _goods; // 指向商店物品实例的指针
    std::shared_ptr<EconomicSystem> economicSystem;
    std::string m_sceneName; // 场景名称

    // UI组件
    cocos2d::Label* _itemLabel;  // 显示物品信息的标签
    cocos2d::Vector<cocos2d::Sprite*> _itemSlots; // 存储物品槽的Sprite
    cocos2d::ui::ScrollView* m_scrollView; // 商品滚动视图
    cocos2d::Label* m_moneyLabel; // 金钱显示标签
    cocos2d::Sprite* m_sliderHandle; // 滑动条滑块

    // 交互状态
    int _selectedSlot; // 当前选中的槽位
    bool isClick; // 标志位，表示是否被点击过
    std::shared_ptr<Item> chosen_Item; // 选中的物品

    // 配置参数
    static const int kRowSize = 12; // 每行槽数量
};
