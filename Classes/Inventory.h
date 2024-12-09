#pragma once
#include<algorithm>
#include<memory>
#include<map>

#include"Item.h"

const int kRowSize = 12;
const int kDefaultSize = kRowSize * 2;

class Inventory {
private:
	//背包容量
	int capacity;

	//当前选中的物品位置
	int selected_position;

	//map存储，物品在背包中的位置作为key（以左上角为1，按从左到右、从上到下递增）
	//std::pair存储对应的Item指针(使用shared_ptr)和背包该位置/格子中多个存放的该种物品个数（如木头，99表示背包中的该一个格子中存储了99个木头）
	//对于在一个格子中存放的Item，只对应一个shared_ptr
	std::map<int , std::pair<std::shared_ptr<Item> , int>> package;

public:
	Inventory ( const int& size = kDefaultSize );

	Inventory ( const Inventory& other );

	~Inventory ();

	//成功添加时返回true,添加失败时返回false
	bool AddItem ( const Item& item );

	//成功添加所有`add_num`个item时返回true,否则返回false
	bool AddItem ( const Item& item , const int& add_num );

	//移除`remove_num`个在背包中`position`位置的物品
	//若`remove_num`超过该格子中现有物品的数量，则清空该格子
	//返回值：
	//背包的`position`位置处未放置物品时返回-1
	//`remove_num`超过该格子中现有物品的数量，则清空该格子，并返回1
	//正常移除背包中`position`处的`remove_num`个物品时，返回0;
	int RemoveItem ( const int& position , const int& remove_num = 1 );

	//清空背包中`position`位置的格子
	bool ClearGrid ( const int& position );

	//获取`selected_position`的Item
	//未找到则返回nullptr
	std::shared_ptr<Item> GetSelectedItem ()const;

	//获取`selected_position`的Item的副本（用于如种子种植等需要获取多个不同Item实例的场景)
	//未找到或拷贝失败则返回nullptr
	std::shared_ptr<Item> GetSelectedItemCopy ();


	std::shared_ptr<Item> GetItemAt ( int position ) const {
		auto it = package.find ( position );
		if (it != package.end ()) {
			return it->second.first; // 返回存储的 Item  
		}
		return nullptr; // 如果没有找到 Item，返回 nullptr  
	}

	// 获取指定位置中的物品个数  
	int GetItemCountAt ( int position ) const {
		auto it = package.find ( position );
		if (it != package.end ()) {
			return it->second.second; // 返回该位置的物品个数  
		}
		return 0; // 如果该位置没有物品，返回 0  
	}


	//在`new_position`合法时，将`selected_position`设置为`new_position`
	// 合法的`new_position`应当为在[1,kRowSize]间的整数（只能设置物品栏最顶一栏的位置为`selected_position`
	//若原`selected_position`处有Item，更新其为unusable状态
	//若`new_position`<1 || `new_position`>kRowSize 返回-1
	//若`new_position`处有Item,更新其为usable状态，返回0
	//若`new_position`处无Item,返回-1
	int SetSelectedItem (const int new_position);

	Inventory& operator=( const Inventory& other ) {
		if (this == &other) {
			return *this;
		}
		this->capacity = other.capacity;
		this->package = other.package;
		return *this;
	}

	//向控制台输出Package信息，仅用于调试
	void DisplayPackageInCCLOG ();
};