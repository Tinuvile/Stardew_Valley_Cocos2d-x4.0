#pragma once
#include "cocos2d.h"
#include <string>

//��Ʒ����
class Item {
protected:
    std::string name;
    int value;
    bool usable;

public:
    Item(const std::string& name, const std::string& path1, const int value = 1, const int& num_limit = 99);

    //���贴��Sprite���õ�ͼƬ��ַ
    const std::string initial_pic;
    // ÿ�����������������Ʒ����
    const int max_count_in_one_grid;

    Item(const Item& other);

    virtual ~Item () {};

    //���ض�ӦItem��name
    const std::string& GetName() const { return name; }

    //������Ʒ��ֵ
    int GetValue() const { return value; }

    //�ж���Ʒ�Ƿ��ʹ�ã������򷵻�true, ���򷵻�false
    const bool IsUsable() const { return usable; }

    //����Ʒ״̬����Ϊ����
    void SetUsable() { usable = true; }

    //����Ʒ״̬����Ϊ������
    void SetUnusable() { usable = false; }

    //�����жϵ�ǰ������other�����ܷ��ڱ����й��ô洢������λ
    virtual bool CanBeDepositTogether(const Item& other) const { return max_count_in_one_grid >= 1 && name == other.GetName(); }

    virtual std::shared_ptr<Item> GetCopy() const;

    virtual void Use();  // ÿ����Ʒ��ʹ�÷���
};