#include "tree.h"

Tree::Tree(const std::string& ore_name, const std::string& initial_pic,
	const std::string& G_Cut_pic, const std::string& Y_Ini_pic, 
	const int value, int recover_time, cocos2d::Vec2 position)
	:Item(ore_name, initial_pic, value), G_Cut_pic(G_Cut_pic),Y_Ini_pic(Y_Ini_pic), 
	mining_day(0), available(true),recover_time(recover_time),position(position),removetimes(2) {
}

Tree::Tree(const Tree& other)
	:Item(other), G_Cut_pic(other.G_Cut_pic), Y_Ini_pic(other.Y_Ini_pic),
	mining_day(0), available(true), position(other.position),recover_time(other.recover_time), removetimes(2) {
}


std::shared_ptr<Item> Tree::GetCopy() const {
	auto copy = std::make_shared<Tree>(*this);
	return copy;
}

std::shared_ptr<Tree> Tree::GetTreeCopy() const {
	auto copy = std::make_shared<Tree>(*this);
	return copy;
}


void Tree::SetValue(const int new_value) {
	value = new_value;
}

bool Tree::CanBeDepositTogether(const Item& other) const {
	const Tree* other_crop = dynamic_cast<const Tree*>(&other);
	if (other_crop) {
		return name == other_crop->GetName();
	}
	return false;
}


bool Tree::Remove(std::shared_ptr<Tree> to_remove) {
	if (to_remove) {
		to_remove.reset();
		return true;
	}
	return false;
}