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

	//Ϊ`skill_type`��Ӧ�ļ�������`amount`�����ľ���
	//��skills��û��skill_type��Ӧ��skill�򷵻�false
	//���򷵻�true
	bool AddExperience ( const int& skill_type , const int& amount );

	//��ȡ��ǰ�����ܵĵȼ� vector���±���Skill��type��Ӧ
	std::vector<int> GetSkillLevels ();

	//����()������
	//����Ϊ����ȡָ�����ͼ��ܵĵ�ǰ�ȼ�
	//��skills��û��skill_type��Ӧ��skill�򷵻�-1
	//���򷵻ض�ӦSkill��`level`
	int operator()( const int& skill_type ) {
		if (skills.find ( skill_type ) != skills.end ()) {
			return skills[skill_type].GetLevel ();
		}
		return -1;
	}



	
};