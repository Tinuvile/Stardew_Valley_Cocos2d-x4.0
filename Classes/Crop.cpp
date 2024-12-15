#include"Crop.h"

Crop::Crop(const std::string& crop_name, const std::string& initial_pic,
	const std::string& growing_pic, const std::string& mature_pic, const std::string& season,
	const Phase& current_phase, const int value, const int plant_day,
	const bool is_harvestable, const int mature_limit)
	:Item(crop_name, initial_pic, value), growing_pic(growing_pic), mature_pic(mature_pic),
	season(season), mature_needed(mature_limit), phase(current_phase),
	plant_day(plant_day), harvestable(is_harvestable), watered(false),nums(500) {
}

Crop::Crop(const Crop& other)
	:Item(other), growing_pic(other.growing_pic), mature_pic(other.mature_pic),
	season(other.season), mature_needed(other.mature_needed), phase(other.phase),
	plant_day(other.plant_day), harvestable(other.harvestable), watered(other.watered), nums(other.nums) {
}


void Crop::Water() {
	if (phase != DEAD && !harvestable && !watered) {
		watered = true;
	}
}

std::shared_ptr<Item> Crop::GetCopy() const {
	auto copy = std::make_shared<Crop>(*this);
	return copy;
}

std::shared_ptr<Crop> Crop::GetCropCopy() const {
	auto copy = std::make_shared<Crop>(*this);
	return copy;
}

void Crop::UpdateGrowth() {
	
	this->watered = false;

	int times = 0;
	//if (Season == "Spring") {
	//	times = 1;
	//}
	//else if (Season == "Summmer") {
	//	times = 2;
	//}
	//else if (Season == "Autumn") {
	//	times = 3;
	//}
	//else {
	//	times = 4;
	//}
	//int growth_progress = times * 7 + day - this->plant_day;
	/*if (growth_progress >= mature_needed) {
		this->phase = Phase::MATURE;
	}
	else if (growth_progress >= mature_needed / 2) {
		this->phase = Phase::GROWING;
	}
	else {
		this->phase = Phase::SEED;
	}*/
}

void Crop::SetDead() {
	phase = DEAD;
	harvestable = false;
}

void Crop::SetValue(const int new_value) {
	value = new_value;
}

bool Crop::CanBeDepositTogether(const Item& other) const {
	const Crop* other_crop = dynamic_cast<const Crop*>(&other);
	if (other_crop) {
		return name == other_crop->GetName() && phase == other_crop->GetPhase();
	}
	return false;
}

bool Crop::Harvest(std::shared_ptr<Crop> to_harvest) {
	if (to_harvest) {
		if (to_harvest->IsHarvestable()) {
			to_harvest.reset();
			return true;
		}
	}
	return false;
}

bool Crop::Remove(std::shared_ptr<Crop> to_remove) {
	if (to_remove) {
		to_remove.reset();
		return true;
	}
	return false;
}