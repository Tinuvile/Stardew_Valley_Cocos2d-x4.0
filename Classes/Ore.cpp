#include "Ore.h"
#include "Flyweight/OreFlyweight.h"
#include "Flyweight/OreExtrinsicState.h"

Ore::Ore(const std::string& ore_name, const std::string& initial_pic,
	const std::string& mining_pic, const int value, int recover_time, cocos2d::Vec2 position)
	:Item(ore_name, initial_pic, value), mining_pic(mining_pic),
	mining_day(0), available(true),recover_time(recover_time),position(position),
	m_flyweight(nullptr), m_extrinsicState(nullptr), m_useFlyweight(false) {
}

Ore::Ore(const Ore& other)
	:Item(other), mining_pic(other.mining_pic),
	mining_day(0), available(true), position(other.position),recover_time(other.recover_time),
	m_flyweight(other.m_flyweight), m_extrinsicState(nullptr), m_useFlyweight(other.m_useFlyweight) {
	// 如果使用享元模式，需要复制外部状态
	if (m_useFlyweight && other.m_extrinsicState) {
		m_extrinsicState = new OreExtrinsicState(*other.m_extrinsicState);
	}
}

// 新增：使用享元模式的构造函数
Ore::Ore(OreFlyweight* flyweight, OreExtrinsicState* extrinsicState)
	:Item(flyweight->getName(), flyweight->getInitialPic(), flyweight->getValue()),
	mining_pic(flyweight->getMiningPic()),
	mining_day(extrinsicState->getMiningDay()),
	available(extrinsicState->isAvailable()),
	recover_time(flyweight->getRecoverTime()),
	position(extrinsicState->getPosition()),
	m_flyweight(flyweight),
	m_extrinsicState(extrinsicState),
	m_useFlyweight(true) {
}


std::shared_ptr<Item> Ore::GetCopy() const {
	auto copy = std::make_shared<Ore>(*this);
	return copy;
}

std::shared_ptr<Ore> Ore::GetOreCopy() const {
	auto copy = std::make_shared<Ore>(*this);
	return copy;
}


void Ore::SetValue(const int new_value) {
	value = new_value;
}

bool Ore::CanBeDepositTogether(const Item& other) const {
	const Ore* other_crop = dynamic_cast<const Ore*>(&other);
	if (other_crop) {
		return name == other_crop->GetName();
	}
	return false;
}


bool Ore::Remove(std::shared_ptr<Ore> to_remove) {
	if (to_remove) {
		to_remove.reset();
		return true;
	}
	return false;
}