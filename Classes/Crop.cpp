#include"Crop.h"

Crop::Crop ( const std::string& crop_name , const std::string& icon_path , const std::string& season ,
		const Phase& current_phase , const int value , const int growth_progress ,
		const bool is_harvestable , const int mature_limit )
	:Item ( crop_name , icon_path , value ) , season ( season ) , mature_needed ( mature_limit ) , phase ( current_phase ) ,
	growth_progress ( growth_progress ) , harvestable ( is_harvestable ) , watered ( false ) {}

Crop::Crop ( const Crop& other )
	:Item ( other ) , season ( other.season ) , mature_needed ( other.mature_needed ) , phase ( other.phase ) ,
	growth_progress ( other.growth_progress ) , harvestable ( other.harvestable ) , watered ( other.watered ) {}

void Crop::Water () {
	if (phase != DEAD && !harvestable && !watered) {
		watered = true;
	}
}

std::shared_ptr<Item> Crop::GetCopy () const {
	auto copy = std::make_shared<Crop> ( *this );
	return copy;
}

void Crop::UpdateGrowth () {
	if (phase != DEAD && !harvestable && watered) {
		//恢复为未浇水状态
		watered = false;
		if (++growth_progress >= 1) {
			//更新phase为GROWING
			if (growth_progress < mature_needed) {
				phase = GROWING;
			}
			//更新phase为MATURE,同时更新`harvestable
			else {
				phase = MATURE;
				harvestable = true;
			}
		}
	}
}

void Crop::SetDead () {
	phase = DEAD;
	growth_progress = -1;
	harvestable = false;
}

void Crop::SetValue ( const int new_value ) {
	value = new_value;
}

bool Crop::CanBeDepositTogether ( const Item& other ) const {
	const Crop* other_crop = dynamic_cast<const Crop*>(&other);
	if (other_crop) {
		return name == other_crop->GetName () && phase == other_crop->GetPhase ();
	}
	return false;
}

bool Crop::Harvest (std::shared_ptr<Crop> to_harvest) {
	if (to_harvest) {
		if (to_harvest->IsHarvestable ()) {
			to_harvest.reset ();
			return true;
		}
	}
	return false;
}

bool Crop::Remove ( std::shared_ptr<Crop> to_remove ) {
	if (to_remove) {
		to_remove.reset ();
		return true;
	}
	return false;
}
