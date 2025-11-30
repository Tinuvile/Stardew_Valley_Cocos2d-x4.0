#pragma once

#include "Item.h"
#include <cocos2d.h>
#include <iostream>
#include <memory>
#include <string>

// Forward declarations
class OreFlyweight;
class OreExtrinsicState;

class Ore : public Item {
public:
    const std::string mining_pic;
    cocos2d::Vec2 position;
    int mining_day;
    int recover_time;
    bool available;

    // Original constructor
    Ore(const std::string& ore_name, const std::string& initial_pic,
        const std::string& mining_pic, const int value, int recover_time, cocos2d::Vec2 position);
    Ore(const Ore& other);

    // New: Flyweight pattern constructor
    Ore(OreFlyweight* flyweight, OreExtrinsicState* extrinsicState);

    // Default constructor
    Ore() : Item("Unknown", "Unknown"), mining_pic("Unknown"), recover_time(0),
        mining_day(0), position(1000, 1000), available(true),
        m_flyweight(nullptr), m_extrinsicState(nullptr), m_useFlyweight(false) {}

    virtual ~Ore() {}

    bool IsHarvestable() const { return available; }
    void SetValue(const int update_value);
    virtual bool CanBeDepositTogether(const Item& other) const;
    virtual std::shared_ptr<Item> GetCopy() const;
    std::shared_ptr<Ore> GetOreCopy() const;
    bool Remove(std::shared_ptr<Ore> to_remove);

    // Flyweight pattern methods
    OreFlyweight* getFlyweight() const { return m_flyweight; }
    OreExtrinsicState* getExtrinsicState() const { return m_extrinsicState; }
    bool isUsingFlyweight() const { return m_useFlyweight; }

private:
    // Flyweight pattern members
    OreFlyweight* m_flyweight;
    OreExtrinsicState* m_extrinsicState;
    bool m_useFlyweight;
};
