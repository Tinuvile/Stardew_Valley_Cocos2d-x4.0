#include"Inventory.h"

Inventory::Inventory ( const int& size )
	:capacity ( size ) , selected_position ( -1 ) {};
Inventory::Inventory ( const Inventory& other )
	:capacity ( other.capacity ) , selected_position ( -1 ) , package ( other.package ) {};
Inventory::~Inventory () {}

bool Inventory::AddItem ( const Item& item ) {
	for (auto& pair : package) {
		if (pair.second.first->GetName () == item.GetName ()
			&& pair.second.second < item.max_count_in_one_grid) {
			++pair.second.second;
			return true;
		}
	}
	int size = package.size ();
	if (size < capacity) {
		package[++size] = std::make_pair ( std::make_shared<Item> ( item ) , 1 );
		return true;
	}
	return false;
}

bool Inventory::AddItem ( const Item& item , const int& add_num ) {
	int remaining = add_num;
	for (auto & pair : package) {
		if (pair.second.first->GetName () == item.GetName ()
			&& pair.second.second < item.max_count_in_one_grid) {
			int space_left = item.max_count_in_one_grid - pair.second.second;
			int to_add = std::min ( remaining , space_left );
			pair.second.second += to_add;
			remaining -= to_add;
			if (remaining <= 0) {
				return true;
			}
		}
	}
	int size = package.size ();
	while (remaining > 0 && size < capacity) {
		int to_add = std::min ( remaining , item.max_count_in_one_grid );
		remaining -= to_add;
		package[++size] = std::make_pair ( std::make_shared<Item> ( item ) , (to_add) );
	}
	return remaining <= 0;
}

int Inventory::RemoveItem ( const int& position , const int& remove_num = 1 ) {
	auto it = package.find ( position );
	if (it != package.end ()) {
		if (it->second.second > remove_num) {
			it->second.second -= remove_num;
			return 0;
		}
		package.erase ( it );
		return 1;
	}
	return -1;
}

bool Inventory::ClearGrid ( const int& position ) {
	auto it = package.find ( position );
	if (it != package.end ()) {
		package.erase ( it );
		return true;
	}
	return false;
}

std::shared_ptr<Item> Inventory::GetSelectedItem ()const {
	if (selected_position >= 1 && selected_position <= kRowSize) {
		auto it = package.find ( selected_position );
		if (it != package.end ()) {
			return it->second.first;
		}
	}
	return nullptr;
}

int Inventory::SetSelectedItem (const int new_position) {
	if (new_position == selected_position) {
		return 0;
	}
	auto it_previous = package.find ( selected_position );
	//若原来`selected_position`位置处有物品，将其改为unusable
	if (it_previous != package.end ()) {
		it_previous->second.first->SetUnusable ();
	}
	//只能设置物品栏最顶层中的Item为当前选中物品
	if (new_position >= 1 && new_position <= kRowSize) {
		selected_position = new_position;
		auto it_new = package.find ( new_position );
		//若新位置有Item,设置其为usable
		if (it_new != package.end () && it_new->second.first != nullptr) {
			it_new->second.first->SetUsable ();
			return 0;
		}
		return 1;
	}
	return -1;
}

