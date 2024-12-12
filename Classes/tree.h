#pragma once

#include"Item.h"
#include <cocos2d.h>
#include <iostream>
#include <memory>
#include <string>



class Tree :public Item {
public:
    // ������ﲻͬʱ�ڶ�Ӧ��ͼƬ·��
    const std::string G_Cut_pic; //
    const std::string Y_Ini_pic; //
    // ���õؿ�λ��
    cocos2d::Vec2 position;
    // ����ȥ������
    int mining_day;     
    // �ڿ��ָ�����Ҫ��ʱ��
    int recover_time;      
    // �Ƿ����ȡ
    bool available;        

    
    Tree(const std::string& ore_name, const std::string& initial_pic,
       const std::string& G_Cut_pic, const std::string& Y_Ini_pic,
        const int value, int recover_time, cocos2d::Vec2 position);
    Tree(const Tree& other);
    // Ĭ�ϳ�ʼ������
    Tree() :Item("Unkown", "Unkown"), G_Cut_pic("Unkown"), Y_Ini_pic("Unkown"), recover_time(0),
        mining_day(0), position(1000,1000), available(true) {}


    virtual ~Tree() {};

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

    std::shared_ptr<Tree> GetTreeCopy() const;

    bool Remove(std::shared_ptr<Tree> to_remove);


};