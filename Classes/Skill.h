#pragma once
#include<iostream>
#include<unordered_map>

//���ּ��ܣ�ͨ���ջ�ũ��Ʒ��ũ������Ʒ����ȡ����
const int farming_skill = 0;
//�ɿ��� ͨ��������ʯ��ȡ���� ÿ���������Ӹ乤�ߵ�������
const int mining_skill = 1;
//�ɼ����� ͨ���ɼ���Ʒ�Ϳ�����ľ��ȡ���� ÿ���������Ӹ����ߵ�������
const int foraging_skill = 2;
//���㼼�� ͨ���ɹ���ɵ���С��Ϸ��ȡ����
const int fishing_skill = 3;
//ս������ �Ƿ�ʵ�ִ���
const int combat_skill = 4;

class Skill {
private:
    int type;                // �������ͣ����� farming_skill��
    int level;               // ��ǰ���ܵȼ���Ĭ�ϳ�ʼ�ȼ�Ϊ0��
    //experience �� experience_needed ���������ۼ�ֵ
    int experience;          // ��ǰ���ܾ���ֵ
    int experience_needed;   // �������辭��

    // ���ݵȼ���̬�����������辭��
    int CalculateExperienceNeeded ( const int level ) const;

public:
    //Ĭ�Ϲ��캯��
    Skill () {}

    // ���캯�� 
    Skill ( const int skill_type );

    // ��ȡ��������
    int GetType() const { return type; }

    // ��ȡ��ǰ���ܵȼ�
    int GetLevel() const { return level; }

    // ��ȡ��ǰ����ֵ
    int GetExperience() const { return experience; }

    // ��ȡ�������辭��
    int GetExperienceNeeded() const { return experience_needed; }

    // ���Ӿ���ֵ�����Զ����������߼�
    void AddExperience ( const int amount );

    // ���ü��ܵȼ��;���
    void Reset ();


private:
    // �ȼ�����
    int LevelUp ();

    //��������Ч������
};



