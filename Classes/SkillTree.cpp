#include"SkillTree.h"

SkillTree::SkillTree () {
	skills[farming_skill] = Skill ( farming_skill );
	skills[mining_skill] = Skill ( mining_skill );
	skills[foraging_skill] = Skill ( foraging_skill );
	skills[fishing_skill] = Skill ( fishing_skill );
	skills[combat_skill] = Skill ( combat_skill );
}

bool SkillTree::AddExperience ( const int& skill_type , const int& amount ) {
	if (skills.find ( skill_type ) != skills.end ()) {
		skills[skill_type].AddExperience ( amount );
		return true;
	}
	return false;
}

std::vector<int> SkillTree::GetSkillLevels () {
	std::vector<int> skill_levels;
	for (int skill_type = farming_skill; skill_type <= combat_skill; skill_type++) {
		int temp_level = -1;
		if (skills.find ( skill_type ) != skills.end ()) {
			temp_level = (skills[skill_type]).GetLevel ();
		}
		skill_levels.push_back ( temp_level );
	}
	return skill_levels;
}
