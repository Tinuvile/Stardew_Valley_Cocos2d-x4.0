#include "tree.h"
#include "Flyweight/TreeFlyweight.h"
#include "Flyweight/TreeExtrinsicState.h"

Tree::Tree(const std::string& ore_name, const std::string& initial_pic,
	const std::string& G_Cut_pic, const std::string& Y_Ini_pic,
	const int value, int recover_time, cocos2d::Vec2 position)
	:Item(ore_name, initial_pic, value), G_Cut_pic(G_Cut_pic),Y_Ini_pic(Y_Ini_pic),
	mining_day(0), available(true),recover_time(recover_time),position(position),removetimes(2),
	m_flyweight(nullptr), m_extrinsicState(nullptr), m_useFlyweight(false) {
}

Tree::Tree(const Tree& other)
	:Item(other), G_Cut_pic(other.G_Cut_pic), Y_Ini_pic(other.Y_Ini_pic),
	mining_day(0), available(true), position(other.position),recover_time(other.recover_time), removetimes(2),
	m_flyweight(other.m_flyweight), m_extrinsicState(nullptr), m_useFlyweight(other.m_useFlyweight) {
	// 如果使用享元模式，需要复制外部状态
	if (m_useFlyweight && other.m_extrinsicState) {
		m_extrinsicState = new TreeExtrinsicState(*other.m_extrinsicState);
	}
}

// 新增：使用享元模式的构造函数
Tree::Tree(TreeFlyweight* flyweight, TreeExtrinsicState* extrinsicState)
	:Item(flyweight->getName(), flyweight->getInitialPic(), flyweight->getValue()),
	G_Cut_pic(flyweight->getGCutPic()),
	Y_Ini_pic(flyweight->getYIniPic()),
	mining_day(extrinsicState->getMiningDay()),
	available(extrinsicState->isAvailable()),
	recover_time(flyweight->getRecoverTime()),
	position(extrinsicState->getPosition()),
	removetimes(flyweight->getRemoveTimes()),
	m_flyweight(flyweight),
	m_extrinsicState(extrinsicState),
	m_useFlyweight(true) {
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