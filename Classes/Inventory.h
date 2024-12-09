#pragma once
#include<algorithm>
#include<memory>
#include<map>

#include"Item.h"

const int kRowSize = 12;
const int kDefaultSize = kRowSize * 2;

class Inventory {
private:
	//��������
	int capacity;

	//��ǰѡ�е���Ʒλ��
	int selected_position;

	//map�洢����Ʒ�ڱ����е�λ����Ϊkey�������Ͻ�Ϊ1���������ҡ����ϵ��µ�����
	//std::pair�洢��Ӧ��Itemָ��(ʹ��shared_ptr)�ͱ�����λ��/�����ж����ŵĸ�����Ʒ��������ľͷ��99��ʾ�����еĸ�һ�������д洢��99��ľͷ��
	//������һ�������д�ŵ�Item��ֻ��Ӧһ��shared_ptr
	std::map<int , std::pair<std::shared_ptr<Item> , int>> package;

public:
	Inventory ( const int& size = kDefaultSize );

	Inventory ( const Inventory& other );

	~Inventory ();

	//�ɹ����ʱ����true,���ʧ��ʱ����false
	bool AddItem ( const Item& item );

	//�ɹ��������`add_num`��itemʱ����true,���򷵻�false
	bool AddItem ( const Item& item , const int& add_num );

	//�Ƴ�`remove_num`���ڱ�����`position`λ�õ���Ʒ
	//��`remove_num`�����ø�����������Ʒ������������ոø���
	//����ֵ��
	//������`position`λ�ô�δ������Ʒʱ����-1
	//`remove_num`�����ø�����������Ʒ������������ոø��ӣ�������1
	//�����Ƴ�������`position`����`remove_num`����Ʒʱ������0;
	int RemoveItem ( const int& position , const int& remove_num = 1 );

	//��ձ�����`position`λ�õĸ���
	bool ClearGrid ( const int& position );

	//��ȡ`selected_position`��Item
	//δ�ҵ��򷵻�nullptr
	std::shared_ptr<Item> GetSelectedItem ()const;

	//��ȡ`selected_position`��Item�ĸ�����������������ֲ����Ҫ��ȡ�����ͬItemʵ���ĳ���)
	//δ�ҵ��򿽱�ʧ���򷵻�nullptr
	std::shared_ptr<Item> GetSelectedItemCopy ();


	std::shared_ptr<Item> GetItemAt ( int position ) const {
		auto it = package.find ( position );
		if (it != package.end ()) {
			return it->second.first; // ���ش洢�� Item  
		}
		return nullptr; // ���û���ҵ� Item������ nullptr  
	}

	// ��ȡָ��λ���е���Ʒ����  
	int GetItemCountAt ( int position ) const {
		auto it = package.find ( position );
		if (it != package.end ()) {
			return it->second.second; // ���ظ�λ�õ���Ʒ����  
		}
		return 0; // �����λ��û����Ʒ������ 0  
	}


	//��`new_position`�Ϸ�ʱ����`selected_position`����Ϊ`new_position`
	// �Ϸ���`new_position`Ӧ��Ϊ��[1,kRowSize]���������ֻ��������Ʒ���һ����λ��Ϊ`selected_position`
	//��ԭ`selected_position`����Item��������Ϊunusable״̬
	//��`new_position`<1 || `new_position`>kRowSize ����-1
	//��`new_position`����Item,������Ϊusable״̬������0
	//��`new_position`����Item,����-1
	int SetSelectedItem (const int new_position);

	Inventory& operator=( const Inventory& other ) {
		if (this == &other) {
			return *this;
		}
		this->capacity = other.capacity;
		this->package = other.package;
		return *this;
	}

	//�����̨���Package��Ϣ�������ڵ���
	void DisplayPackageInCCLOG ();
};