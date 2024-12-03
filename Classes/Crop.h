#pragma once

#include"Item.h"

#include<cocos2d.h>
#include <iostream>
#include <memory>
#include <string>

enum Phase {
    SEED,    //����
    GROWING, //������
    MATURE,  //����
    DEAD     //���� �ڼ��ڸ�������������Ϊ����״̬
};

class Crop:public Item {
private:
    const std::string season; //���������ļ���
    const int mature_needed;  //�ﵽ������������
    Phase phase;      //��ǰ�׶Σ���Ӧ`SEED` `GROWING` `MATURE`�����׶�
    int growth_progress;      //��������������ÿ����ˮ�ҽ�����һ��ʱ���ӣ�
    bool harvestable;         //�Ƿ���ջ�
    bool watered;             //�����Ƿ񽽹�ˮ ÿ�����Ϊfalse
public:
    //������
    Crop ( const std::string& crop_name , const std::string& icon_path , const std::string& season ,
        const Phase& current_phase = SEED , const int value = 1 , const int growth_progress = 0 ,
        const bool is_harvestable = false , const int mature_limit = 4 );
    Crop ( const Crop& other );


    virtual ~Crop () {};


    const std::string& GetSeason () const { return season; }
    //�ж��Ƿ�Ϊ����״̬
    bool IsSeed () const { return phase == SEED; }
    //�ж��Ƿ�Ϊ����״̬
    bool IsMature () const { return phase == MATURE; }
    //��ȡ���ﵱǰ������������
    int GetGrowthProgress () const { return growth_progress; }
    //��ȡ��ǰ��`phase`
    Phase GetPhase () const { return phase; }
    //��ȡ���ﵱǰ�Ƿ�����ջ�
    bool IsHarvestable () const { return harvestable; }
    // ��ˮ
    void Water ();
    // ��������״̬ ÿ�����µ�һ��ʱ�����
    void UpdateGrowth ();
    //����״̬ΪDEAD growth_progress��Ϊ-1 harvestableΪflase
    void SetDead ();
    //����������Ʒ��ֵ ����������������ֵ
    void SetValue ( const int update_value );

    //�����жϵ�ǰ������other�����ܷ��ڱ����й��ô洢������λ
    virtual bool CanBeDepositTogether ( const Item& other ) const;

    //��ȡshared_ptr<Crop>���͵ĵĸ��� 
    //��ֲʱʹ�ø÷���
    //�Ա�����������ջ��ʱͨ��reset���ٶ���
    //�����ֶ�����new��delete���ܳ��ֵ�����
    virtual std::shared_ptr<Item> GetCopy () const ; 

    //�ջ�
    //�˴����ṩ�ܷ��ջ�������жϺ����ٶ�ӦCrop����Ĳ���
    
    // ������
    // ����Ӧʵ����icon(Sprite*��)Ϊĳ������child�ڵ�
    // ʹ��ǰ�Ƚ���Ӹó������ӽڵ���ȥ����ͨ��GetIcon�ӿڻ�ȡ��ӦSprite*)
    // ���������ɵ�����
    
    //��ȡ��Ʒ�������һ����������
    //��Ӧʵ�������ջ�����shared_ptr<Crop>Ϊ�վ�����false
    //��Ӧʵ�����ջ������ٶ�Ӧ���󷵻�true
    static bool Harvest ( std::shared_ptr<Crop> to_harvest );


    //����
    //�ṩ���ٶ�ӦCrop����Ĳ���

    // ������
    // ����Ӧʵ����icon(Sprite*��)Ϊĳ������child�ڵ�
    // ʹ��ǰ�Ƚ���Ӹó������ӽڵ���ȥ����ͨ��GetIcon�ӿڻ�ȡ��ӦSprite*)
    // ���������ɵ�����

    //�������shared_ptr<Crop>Ϊ�շ���false
    //�������ٶ�Ӧ���󲢷���true
    static bool Remove ( std::shared_ptr<Crop> to_remove );
};