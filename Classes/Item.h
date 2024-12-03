#pragma once
#include "cocos2d.h"
#include <string>

//������Ʒ����
class Item {
protected:
    std::string name;
    cocos2d::Sprite* icon;  //��Ʒ��ͼ�괴����Sprite
    int value;
    bool usable;
    Item ( const std::string& name , const std::string& icon_path , const int value = 1 , const int& num_limit = 99 );
public:
    const int max_count_in_one_grid;

    Item ( const Item& other );
    virtual ~Item () {}

    //���ض�ӦItem��name
    const std::string& GetName () const { return name; }
    //����icon��Ӧ��Sprite*
    cocos2d::Sprite* GetIcon () const { return icon; }
    //������Ʒ��ֵ
    int GetValue () const { return value; }
    //�ж���Ʒ�Ƿ��ʹ�ã������򷵻�ture,���򷵻�false
    const bool IsUsable () const { return usable; }
    //����Ʒ״̬����Ϊ����
    void SetUsable () { usable = true; }
    //����Ʒ״̬����Ϊ������
    void SetUnusable () { usable = false; }


    //�����жϵ�ǰ������other�����ܷ��ڱ����й��ô洢������λ
    virtual bool CanBeDepositTogether ( const Item& other ) const { return max_count_in_one_grid >= 1 && name == other.GetName (); }
    //�޸���ƷIcon
    virtual void SetIcon ( const std::string& file_source );

    virtual std::shared_ptr<Item> GetCopy () const ;

    virtual void Use ();  // ÿ����Ʒ��ʹ�÷���
};