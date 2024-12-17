#pragma once
#include"Food.h"

const int kFishTypes = 3;
const int kFishBasicValue = 100;
const int kFishBasicEnergy = 55;

//��¼��ͬ�����������
const std::string fish_name[] = {
	"sartine","tuna","albacore"
};

//��¼��ͬ������ͼƬ��·��
const std::string fish_path[] = {
	"Fish/AquariumFish-22.png","Fish/AquariumFish-21.png","Fish/AquariumFish-97.png"
};

class Fish :public Food {
private:
	//�����Ѷ�
	int catching_difficulty;

	int energy_provided;
public:
	//���캯��
	Fish ( int fish_id );

	//��������
	virtual ~Fish () {};

	int GetCatchingDiffuculty () const;

};