#pragma once

#include"Item.h"
#include "AppDelegate.h"
#include<cocos2d.h>
#include <iostream>
#include <memory>
#include <string>

enum Phase {
    SEED,    //����
    GROWING, //������
    MATURE,  //����
    SAPLESS, // ��ή״̬ 
    DEAD     //���� �ڼ��ڸ�������������Ϊ����״̬ 
};

class Crop :public Item {
private:
    const std::string season; //���������ļ���
    int mature_needed;  //�ﵽ������������
    Phase phase;      //��ǰ�׶Σ���Ӧ`SEED` `GROWING` `MATURE`�����׶� 
    bool harvestable;         //�Ƿ���ջ�
public:
    //������ﲻͬʱ�ڶ�Ӧ��ͼƬ·��
    const std::string growing_pic;
    const std::string mature_pic;
    // ��ֲ�ؿ���
    int nums;
    //�����Ƿ񽽹�ˮ ÿ�����Ϊfalse
    bool watered;            
    // ��ֲ������
    int plant_day;     
    //������
    Crop(const std::string& crop_name, const std::string& initial_pic,
        const std::string& growing_pic, const std::string& mature_pic, const std::string& season,
        const Phase& current_phase = SEED, const int value = 1, const int plant_day = 0,
        const bool is_harvestable = false, const int mature_limit = 4);
    Crop(const Crop& other);
    // Ĭ�ϳ�ʼ������
    Crop():Item("Unkown", "Unkown", 0), growing_pic("Unkown"), mature_pic("Unkown"),
        season("Unkown"), mature_needed(0), phase(Phase::SEED),
        plant_day(0), harvestable(false), watered(false), nums(500) {}


    virtual ~Crop() {};


    const std::string& GetSeason() const { return season; }
    //�ж��Ƿ�Ϊ����״̬
    bool IsSeed() const { return phase == SEED; }
    //�ж��Ƿ�Ϊ����״̬
    bool IsMature() const { return phase == MATURE; }
    //��ȡ������ֲ������
    int GetGrowthProgress() const { return plant_day; }
    //��ȡ��ǰ��`phase`
    Phase GetPhase() const { return phase; }
    //��ȡ���ﵱǰ�Ƿ�����ջ�
    bool IsHarvestable() const { return harvestable; }
    // ��ˮ
    void Water();
    // ��������״̬ ÿ�����µ�һ��ʱ�����
    void UpdateGrowth();
    //����״̬ΪDEAD growth_progress��Ϊ-1 harvestableΪflase
    void SetDead();
    //����������Ʒ��ֵ ����������������ֵ
    void SetValue(const int update_value);

    //�����жϵ�ǰ������other�����ܷ��ڱ����й��ô洢������λ
    virtual bool CanBeDepositTogether(const Item& other) const;

    //��ȡshared_ptr<Crop>���͵ĵĸ��� 
    //��ֲʱʹ�ø÷���
    //�Ա�����������ջ��ʱͨ��reset���ٶ���
    //�����ֶ�����new��delete���ܳ��ֵ�����
    virtual std::shared_ptr<Item> GetCopy() const;

    std::shared_ptr<Crop> GetCropCopy() const;

    //�ջ�
    //�˴����ṩ�ܷ��ջ�������жϺ����ٶ�ӦCrop����Ĳ���


    //��ȡ��Ʒ�������һ����������
    //��Ӧʵ�������ջ�����shared_ptr<Crop>Ϊ�վ�����false
    //��Ӧʵ�����ջ������ٶ�Ӧ���󷵻�true
    static bool Harvest(std::shared_ptr<Crop> to_harvest);


    //����
    //�ṩ���ٶ�ӦCrop����Ĳ���


    //�������shared_ptr<Crop>Ϊ�շ���false
    //�������ٶ�Ӧ���󲢷���true
    static bool Remove(std::shared_ptr<Crop> to_remove);


    void ChangePhase(Phase phase) {
        this->phase = phase;
    }

    void ChangMatureNeeded(int Time) {
        this->mature_needed += Time;
    }

};