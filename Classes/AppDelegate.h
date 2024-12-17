#ifndef  _APP_DELEGATE_H_  // ��ֹͷ�ļ�����ΰ����ĺ�
#define  _APP_DELEGATE_H_

#include "cocos2d.h"  
//#include "GameBeginUI.h"
#include "Barn.h"
#include "Beach.h"
#include "Cave.h"
#include "farm.h"
#include "Forest.h"
#include "Myhouse.h"
#include "supermarket.h"
#include "Town.h"

#include "Player.h"

#include "mini_bag.h"
#include "Inventory.h"
#include "InventoryUI.h"

#include "Item.h"
#include "Generaltem.h"

#include "BasicInformation.h"
#include "Crop.h"
#include "Ore.h"
#include "tree.h"

#include "Livestock.h"
#include "Chicken.h"
#include "Cow.h"
#include "Sheep.h"

#include "NPC.h"
#include "NPCreate.h"
#include "NPCtalkUI.h"
#include "NpcRelationship.h"
#include "intimacyUI.h"

#include "StoreUI.h"
#include "EconomicSystem.h"

#include "SkillTree.h"

#include <memory>

#define Daytime 43200

USING_NS_CC;

class Player;
class Town;
class farm;
class supermarket;
class Myhouse;
class Crop;
class Item;
class CropBasicInformation;
class Barn;
class Inventory;
class NpcRelationship;
class mini_bag;
/******************************** ȫ�ֱ��������� ***************************************/
extern int remainingTime;  // ����������ʼ��
extern int day;
extern int GoldAmount;
extern bool IsNextDay;
extern bool frombed;
extern std::string Season;
extern std::map<std::string , int> season;
// ÿ������Ļ�����Ϣ
extern std::map<std::string , Crop> cropbasicinformation;
extern std::map<std::pair<std::string , Vec2> , bool> T_lastplace;
extern std::map<std::pair<std::string, Vec2>, bool> F_lastplace;
extern std::map<std::pair<std::string, Vec2>, bool> W_lastplace;
// �Ѿ���ֲ�������״̬��Ϣ
extern std::vector<std::shared_ptr<Crop>> Crop_information;
extern std::vector<std::shared_ptr<Ore>> Ore_information; 
extern std::vector<std::shared_ptr<Tree>> Tree_information; 
// ��ʼ��������Ļ�����Ϣ
extern CropBasicInformation WHEAT;
extern CropBasicInformation CORN;
extern CropBasicInformation POTATO;
extern CropBasicInformation PUMPKIN;
extern CropBasicInformation BLUEBERRY;
extern Crop wheat; 
extern Crop corn;
extern Crop potato;
extern Crop pumpkin;
extern Crop blueberry;
extern Player* player1;  // ����ָ�����������ʼ��
extern SkillTree* skill_tree;
extern mini_bag* miniBag;
extern Inventory* inventory;
extern NpcRelationship* npc_relationship;
//�洢�����п��м����ľ������򣬲���¼�������Ƿ��Ѵ��ڼ���
extern std::vector<std::pair<Rect , bool>> barn_space;
//�洢�����еļ���
extern std::vector<Livestock*> livestocks;
/**************************************************************************************/


 /**
  @brief    Cocos2d Ӧ�ó����ί���ࣨAppDelegate��

  ���ฺ����Ӧ�ó�����������ڹ�������Ӧ�������������̨������ǰ̨�Ȳ�����
  �̳��� cocos2d::Application �࣬��ͨ��˽�м̳������ز��ֽӿڣ�ȷ���û�ֻ�ܷ��ʹ����ӿڡ�
  */

  /************************************ ȫ�ֱ��������� ******************************************/
  // �趨��Ϸ�����С��1600, 1280
static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 1280);  // ��Ʒֱ���


class AppDelegate : private cocos2d::Application  // �̳��� cocos2d::Application �࣬��˽�л��̳�
{
public:
    // ���캯��
    AppDelegate();

    // ��������
    virtual ~AppDelegate();

    // ��ʼ�� OpenGL ���������Եĺ���
    virtual void initGLContextAttrs();

    /**
    @brief    Ӧ�ó�������ʱ�ĳ�ʼ������
    @return true    ��ʼ���ɹ���Ӧ�ü������С�
    @return false   ��ʼ��ʧ�ܣ�Ӧ�ó����˳���
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief    Ӧ�ó�������̨ʱ���á�
    @param    the pointer of the application ָ��Ӧ�ó����ָ�루Cocos2d �ڲ�����ô˺�����
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief    Ӧ�ó������½���ǰ̨ʱ���á�
    @param    the pointer of the application ָ��Ӧ�ó����ָ�루Cocos2d �ڲ�����ô˺�����
    */
    virtual void applicationWillEnterForeground();

    void runScene(cocos2d::Director* director);

    void Initialize();


};

#endif // _APP_DELEGATE_H_  // ������ֹͷ�ļ�����ΰ����ĺ�
