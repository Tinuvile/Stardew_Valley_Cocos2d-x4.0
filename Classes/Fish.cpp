#include"Fish.h"

Fish::Fish(int fish_index)
	:Food(fish_name[fish_index],fish_path[fish_index],kFishBasicValue,kFishBasicEnergy){
	switch (fish_index) {
		case 0:
			catching_difficulty = 1;
			break;
		case 1:
			catching_difficulty = 3;
			break;
		case 2:
			catching_difficulty = 2;
			break;
		default:
			catching_difficulty = 1;
			break;
	}
	value *= catching_difficulty;
	energy_provided *= catching_difficulty;
}


int Fish::GetCatchingDiffuculty () const {
	return catching_difficulty;
}

std::shared_ptr<Item> Fish::GetCopy () const {
	auto copy = std::make_shared<Fish> ( *this );
	return copy;
}