#pragma once
#include"Item.h"

const int kFishTypes = 3;
const int kFishBasicValue = 100;
const int kFishBasicEnergy = 55;

//记录不同种类鱼的名字
const std::string fish_name[] = {
	"sartine","tuna","albacore"
};

//记录不同种类鱼图片的路径
const std::string fish_path[] = {
	"Fish/AquariumFish-22.png","Fish/AquariumFish-21.png","Fish/AquariumFish-97.png"
};

class Fish :public Item {
private:
	//捕获难度
	int catching_difficulty;

	int energy_provided;
public:
	//构造函数
	Fish ( int fish_id );

	//析构函数
	virtual ~Fish () {};

	int GetEnergyProvided () const;

	int GetCatchingDiffuculty () const;

};