#pragma once

#include"Item.h"
#include <cocos2d.h>
#include <iostream>
#include <memory>
#include <string>



class Ore :public Item {
public:
    // ������ﲻͬʱ�ڶ�Ӧ��ͼƬ·��
    const std::string mining_pic;
    // ���õؿ�λ��
    cocos2d::Vec2 position;
    // ����ȥ������
    int mining_day;     
    // �ڿ��ָ�����Ҫ��ʱ��
    int recover_time;      
    // �Ƿ����ȡ
    bool available;        

    //������
    Ore(const std::string& ore_name, const std::string& initial_pic,
       const std::string& mining_pic, const int value, int recover_time, cocos2d::Vec2 position);
    Ore(const Ore& other);
    // Ĭ�ϳ�ʼ������
    Ore():Item("Unkown", "Unkown"), mining_pic("Unkown"),recover_time(0),
        mining_day(0), position(1000,1000), available(true) {}


    virtual ~Ore() {};

    //��ȡ���ﵱǰ�Ƿ�����ջ�
    bool IsHarvestable() const { return available; }
    //����������Ʒ��ֵ ����������������ֵ
    void SetValue(const int update_value);
    //�����жϵ�ǰ������other�����ܷ��ڱ����й��ô洢������λ
    virtual bool CanBeDepositTogether(const Item& other) const;

    //��ȡshared_ptr<Crop>���͵ĵĸ��� 
    //��ֲʱʹ�ø÷���
    //�Ա�����������ջ��ʱͨ��reset���ٶ���
    //�����ֶ�����new��delete���ܳ��ֵ�����
    virtual std::shared_ptr<Item> GetCopy() const;

    std::shared_ptr<Ore> GetOreCopy() const;

    bool Remove(std::shared_ptr<Ore> to_remove);


};