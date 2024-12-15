#pragma once
#include"Skill.h"

#include<string>
#include<unordered_map>
#include<vector>


class SkillTree {
private:
	std::unordered_map<int,Skill> skills;
public:
	SkillTree ();

	//为`skill_type`对应的技能增加`amount`数量的经验
	//若skills中没有skill_type对应的skill则返回false
	//否则返回true
	bool AddExperience ( const int& skill_type , const int& amount );

	//获取当前各技能的等级 vector的下标与Skill的type对应
	std::vector<int> GetSkillLevels ();

	//重载()操作符
	//作用为：获取指定类型技能的当前等级
	//若skills中没有skill_type对应的skill则返回-1
	//否则返回对应Skill的`level`
	int operator()( const int& skill_type ) {
		if (skills.find ( skill_type ) != skills.end ()) {
			return skills[skill_type].GetLevel ();
		}
		return -1;
	}



	
};