#pragma once

#include "Item.h"
#include <cocos2d.h>
#include <iostream>
#include <memory>
#include <string>

// Forward declarations
class TreeFlyweight;
class TreeExtrinsicState;

class Tree : public Item {
public:
    const std::string G_Cut_pic;
    const std::string Y_Ini_pic;
    cocos2d::Vec2 position;
    int mining_day;
    int recover_time;
    bool available;
    int removetimes;

    // Original constructor
    Tree(const std::string& ore_name, const std::string& initial_pic,
        const std::string& G_Cut_pic, const std::string& Y_Ini_pic,
        const int value, int recover_time, cocos2d::Vec2 position);
    Tree(const Tree& other);

    // New: Flyweight pattern constructor
    Tree(TreeFlyweight* flyweight, TreeExtrinsicState* extrinsicState);

    // Default constructor
    Tree() : Item("Unknown", "Unknown"), G_Cut_pic("Unknown"), Y_Ini_pic("Unknown"), recover_time(0),
        mining_day(0), position(1000, 1000), available(true), removetimes(2),
        m_flyweight(nullptr), m_extrinsicState(nullptr), m_useFlyweight(false) {}

    virtual ~Tree() {}

    bool IsHarvestable() const { return available; }
    void SetValue(const int update_value);
    virtual bool CanBeDepositTogether(const Item& other) const;
    virtual std::shared_ptr<Item> GetCopy() const;
    std::shared_ptr<Tree> GetTreeCopy() const;
    bool Remove(std::shared_ptr<Tree> to_remove);

    // Flyweight pattern methods
    TreeFlyweight* getFlyweight() const { return m_flyweight; }
    TreeExtrinsicState* getExtrinsicState() const { return m_extrinsicState; }
    bool isUsingFlyweight() const { return m_useFlyweight; }

private:
    // Flyweight pattern members
    TreeFlyweight* m_flyweight;
    TreeExtrinsicState* m_extrinsicState;
    bool m_useFlyweight;
};
