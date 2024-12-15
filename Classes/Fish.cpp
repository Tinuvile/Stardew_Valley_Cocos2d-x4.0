#include"Fish.h"

Fish::Fish(int fish_index)
	:Item(fish_name[fish_index],fish_path[fish_index]){
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
	value = kFishBasicValue * catching_difficulty;
	energy_provided = kFishBasicEnergy * catching_difficulty;
}

int Fish::GetEnergyProvided () const {
	return energy_provided;
}

int Fish::GetCatchingDiffuculty () const {
	return catching_difficulty;
}