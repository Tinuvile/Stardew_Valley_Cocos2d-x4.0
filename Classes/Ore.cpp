#include "Ore.h"

Ore::Ore(const std::string& ore_name, const std::string& initial_pic,
	const std::string& mining_pic, const int value, int recover_time, cocos2d::Vec2 position)
	:Item(ore_name, initial_pic, value), mining_pic(mining_pic),
	mining_day(0), available(true),recover_time(recover_time),position(position) {
}

Ore::Ore(const Ore& other)
	:Item(other), mining_pic(other.mining_pic),
	mining_day(0), available(true), position(100,100),recover_time(other.recover_time) {
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