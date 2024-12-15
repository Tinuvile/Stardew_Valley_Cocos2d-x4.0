#pragma once

#include"cocos2d.h"
#include"Item.h"
#include<memory>
#include<string>


class Livestock : public cocos2d::Sprite {
protected:
    std::string species;  // ���࣬����"ţ", "��", "��"��
    std::string icon_path; // ͼƬ·��
    bool can_produce;  // �Ƿ���������������Ƿ��Ѿ����̡��µ��ȣ�
    cocos2d::Rect move_area;  // �޶������ľ��η�Χ
    int move_direction = 0;  //�ƶ��ķ���
    bool moving = false;  //�ƶ�״̬�������ƶ���Ϊtrue,��ֹΪfalse
public:
    // ���캯��
    Livestock ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area );

    virtual bool init ();

    // ��̬create����
    static Livestock* create ( const std::string& species , const std::string& icon_path , const cocos2d::Rect& area );

    // ����������
    virtual ~Livestock ();

    // ����ƶ��ķ���
    void RandomMove ();

    // ���ü����ܷ�������Ʒ��״̬
    void SetCanProduce ( bool can ) {
        can_produce = can;
    }

    // �����Ƿ����������Ʒ
    bool IsCanProduce () const {
        return can_produce;
    }

    // ������Ʒ���鷽��
    virtual std::shared_ptr<Item> ProduceProduct () {
        return nullptr;
    }

    // ��ȡ���������
    const std::string& GetSpecies () const {
        return species;
    }

    void SetMoving ( bool is_moving ) { moving = is_moving; }
    

};