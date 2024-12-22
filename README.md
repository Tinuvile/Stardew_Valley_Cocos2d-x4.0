## 项目简介

星露谷风格的农场生活模拟游戏。玩家将管理自己的农场，种植作物，养殖动物，与镇上的居民互动，参与节日活动，并探索周围的自然环境。游戏包含丰富的季节变化、社区交互和个人角色发展。

## 功能实现

### 基础功能

- 农场管理
  - 玩家可以耕种、种植并收获多种作物，作物的成熟时间根据种类和季节变化。
  - 养殖牛、鸡和羊等动物。
  - 农场操作包括浇水、施肥，以及管理干旱和病害威胁，未及时处理会导致作物死亡。
  - 管理农场资源，如水资源、种子和肥料存储。
- 社区交互：
  - 与镇上的居民建立关系，包括友谊和浪漫关系。
  - 参与定期的社区活动和节日庆典。
  - 接受并完成居民的委托任务，提高声望和收获奖励，任务包括收集特定物品、帮助修复建筑等。
- 探索和冒险：
  - 探索农场周边的地区，包括森林、山脉和神秘洞穴。
  - 挖掘矿物、钓鱼和收集稀有物品。
- 角色成长和技能：
  - 角色技能树，包括农业、采矿、钓鱼和料理等。
  - 随着技能提升，解锁新的作物种类、工具升级和烹饪食谱。

### 拓展功能
- 天气系统
  - 复杂的天气系统，会影响农作物的种植以及NPC的穿着，包括干旱、下雨与季节变化。
- 背景音乐
  - 根据场景的变换切换背景音乐。

## 成员分工
| 姓名 | 学号 | 分工 | 工作量 |
| :---: | :---: | :---: | :---: |
| 杨子龙（组长） | 2353257 | 场景系统<br> 天气与时间系统<br> 技能树系统<br> 养殖系统<br> | 25% |
| 钱宝强 | 2353018 | 背包系统<br> 钓鱼系统<br> 主角操作系统<br> 家畜系统 | 25% |
| 谭鹏翀 | 2351588 | 交互系统<br> UI界面<br> 开场动画制作<br> 商店系统 | 25% |
| 张竹和 | 2352495 | NPC系统<br> 亲密度系统<br> 人物经济系统<br> 任务系统 | 25% |

## 项目结构
* **/Classes**  
  - 类定义与实现  

  - **UI类**  
    - `GameBeginUI.h`, `GameBeginUI.cpp`    开始游戏界面  
    - `CreateCharacterUI.h`, `CreateCharacterUI.cpp` 人物创建界面  
    - `DailyRecordUI.h`, `DailyRecordUI.cpp` 任务显示界面  
    - `DetailedtaskUI.h`, `DetailedtaskUI.cpp` 任务详情界面  
    - `IntimacyUI.h`, `IntimacyUI.cpp` 人物亲密度界面  
    - `InventoryUI.h`, `InventoryUI.cpp` 背包主界面  
    - `MailBoxUI.h`, `MailBoxUI.cpp` 信箱界面  
    - `MiniBag.h`, `MiniBag.cpp` 物品栏界面  
    - `SkillTreeUI.h`, `SkillTreeUI.cpp` 技能树界面  
    - `StoreUI.h`, `StoreUI.cpp` 商店界面  
    - `QuitUI.h`, `QuitUI.cpp` 退出游戏界面

  - **场景类**  
      - `Barn.h`, `Barn.cpp`     畜棚场景  
      - `Beach.h`, `Beach.cpp`   沙滩场景  
      - `Cave.h`, `Cave.cpp`     洞穴场景  
      - `farm.h`, `farm.cpp`     农场场景  
      - `Forest.h`, `Forest.cpp` 森林场景  
      - `Myhouse.h`, `Myhouse.cpp` 家场景  
      - `surpermarket.h`, `surpermarket.cpp` 超市场景  
      - `Town.h`, `Town.cpp` 小镇场景  

  - **NPC类**  
    - `NPC.h`, `NPC.cpp`    人物信息类  
    - `NPCreate.h`, `NPCreate.cpp` 人物创建类  
    - `NpcRelationship.h`, `NpcRelationship.cpp` 人物亲密度类 
    - `NPCtalkUI.h`, `NPCtalkUI.cpp` NPC对话类

  - **人物及相关操作类**  
    - `Player.h`, `Player.cpp` 玩家类
    - `Chicken.h`, `Chicken.cpp`,`Cow.h`, `Cow.cpp`,`Sheep.h`, `Sheep.cpp`  农场动物类  
    - `Crop.h`, `Crop.cpp` 农作物类 
    - `EconomicSystem.h`, `EconomicSystem.cpp` 人物经济系统类 
    - `Fish.h`, `Fish.cpp` 鱼类  
    - `FishingGame.h`, `FishingGame.cpp` 钓鱼游戏类  
    - `Food.h`, `Food.cpp` 食品类  
    - `Inventory.h`, `Inventory.cpp` 背包类  
    - `Item.h`, `Item.cpp` 物品类  
    - `Livestock.h`, `Livestock.cpp` 家畜养殖类  
    - `Ore.h`, `Ore.cpp`   作物收获类
    - `Skill.h`, `Skill.cpp`, `SkillTree.h`, `SkillTree.cpp` 技能与技能树类
    - `TaskManagement.h`, `TaskManagement.cpp` 任务系统类
    - `tree.h`, `tree.cpp` 树类
    - `Marry.h`, `Marry.cpp` 结婚类
    - `CookingPot.h`, `CookingPot.cpp` 食品制作类

  - **其他** 
    - `AppDelegate.h`, `AppDelegate.cpp` 程序入口
    - `surpermarket.h`, `surpermarket.cpp` 商店售卖类
    - `BasicInformation.h` 作物生长类
    - `GeneralItem.h`, `GeneralItem.cpp` 物品信息类

* **/Resources**  
  - 资源文件

* **/cocos2d**  
  - Cocos2d依赖文件
 
* **/proj.win32**  
  - 游戏程序

## 操作介绍与演示
 `ESC` 触发主UI，包含背包、技能数、亲密度、退出界面；
 `Enter` 在特定路径转换场景；
 `点击NPC` 触发与任务对话；
 `点击物品栏物品再点击NPC` 给NPC送礼物；

 ### 小镇
 `点击物品栏物品再点击箱子` 提交任务物品完成任务；

 ### 农场
 `选择物品栏种子再按P` 种植；
 `W` 浇水；`G` 收获；
 `点击物品栏物品再点击箱子` 出售物品；

 ### 家
 `Enter` 睡觉；

 ### 畜棚
 `鼠标右键` 收家畜产品；

 ### 矿洞
 `M` 挖矿；

 ### 森林
 `L` 砍树；

 ### 沙滩
 `H` 钓鱼；

 ### 商店
 `P` 打开/关闭购买界面；
 `点击商品再点击背包` 购买；
    
## 开发日志

### 2024/11/26
* 配置Cocos与CMake环境
* 确定小组分工
* 完成中枢地图移动区域限制

### 2024/11/27
* 开场界面UI
* 地图视角跟随人物

### 2024/11/28
* 角色人物关系类
* 单元测试

### 2024/11/29
* 开场动画

### 2024/11/30
* 主角经济系统类
* 鼠标事件类
* 物品基类及物品栏类

### 2024/12/1
* 人物自由移动（可以长按连续移动）
* 小镇场景与商店场景的自由切换

### 2024/12/09
* 背包类与界面实现

### 2024/12/11
* 商店界面实现
* NPC创建和随机移动

### 2024/12/15
* 功能对接
* 实现小镇、牧场、森林、矿场、海滩以及家、畜棚、商店
* 实现NPC随机对话、人物购买、砍树、种植、畜牧、睡觉等操作

## 功能实现

- 场景类
  
  本项目共实现了八个场景，场景类均继承自Cocos2d-x的`Scene`类，用于管理游戏中的不同场景，每个场景类均包含了初始化、角色位置检测以及元素交互等基础功能，以及其他特定功能。场景类的基本结构如下：
  ```cpp
  class BaseScene : public cocos2d::Scene  
  {  
  public:  
      BaseScene();  
      virtual ~BaseScene();  

      virtual bool init();  

      static BaseScene* create();  

      // 判断角色的位置  
      virtual void checkPlayerPosition() = 0;  

      // 创建一个列表，用于保存所有非透明像素的坐标  
      std::vector<cocos2d::Vec2> nonTransparentPixels;  

      // 退出按钮  
      cocos2d::MenuItemImage* closeItem;  
      cocos2d::Menu* menu;  

  protected:  
      // 键盘输入状态  
      bool isEnterKeyPressed = false;  
  };  
  ```

- 物品与背包类
  
  `Item`类是游戏中的物品基类，定义了物品的基本属性和行为，`Crop`类即继承自`Item`类实现。
  ```cpp
  //物品基类
  class Item {
  protected:
      std::string name;
      int value;
      bool usable;
  public:
      Item(const std::string& name, const std::string& path1, const int value = 1, const int& num_limit = 99);

      //若需创建Sprite所用的图片地址
      const std::string initial_pic;
      // 每个背包格子中最大物品数量
      const int max_count_in_one_grid;

      Item(const Item& other);

      virtual ~Item () {};

      //返回对应Item的name
      const std::string& GetName() const { return name; }

      //返回物品价值
      int GetValue() const { return value; }

      //判断物品是否可使用，可用则返回true, 否则返回false
      const bool IsUsable() const { return usable; }

      //将物品状态设置为可用
      void SetUsable() { usable = true; }

      //将物品状态设置为不可用
      void SetUnusable() { usable = false; }

      //用于判断当前对象与other对象能否在背包中公用存储背包格位
      virtual bool CanBeDepositTogether(const Item& other) const { return max_count_in_one_grid >= 1 && name == other.GetName(); }

      virtual std::shared_ptr<Item> GetCopy() const;

      virtual void Use();  // 每个物品的使用方法

      bool operator==( const Item& other ) const {
          return false;
      }
  };
  ```
在`Item`类中，使用`std::shared_ptr<Item>`智能指针来返回物品的副本，使得在不需要手动管理内存的情况下，也能自动管理内存的生命周期，确保对象的有效性和可用性，避免内存泄漏。另外，利用多态，声明`Use`函数为纯虚函数，任何继承自`Item`的类必须实现此函数，使得不同物品可以有不同的使用效果。类中还重载比较运算符来比较物品的名称和价值。

`Inventory`类实现了游戏中物品的背包管理功能，使用`std::map`和`std::shared_ptr`来储存物品及其数量，支持物品的添加、移除、选择等操作。
```cpp
class Inventory {
private:
	//背包容量
	int capacity;

	//当前选中的物品位置
	int selected_position;

	//map存储，物品在背包中的位置作为key（以左上角为1，按从左到右、从上到下递增）
	//std::pair存储对应的Item指针(使用shared_ptr)和背包该位置/格子中多个存放的该种物品个数（如木头，99表示背包中的该一个格子中存储了99个木头）
	//对于在一个格子中存放的Item，只对应一个shared_ptr
	std::map<int , std::pair<std::shared_ptr<Item> , int>> package;

public:
	Inventory ( const int& size = kDefaultSize );

	Inventory ( const Inventory& other );

	~Inventory ();

	bool is_updated = false;//检测背包是否更新过

	//成功添加时返回true,添加失败时返回false
	bool AddItem ( const Item& item );

	//成功添加所有`add_num`个item时返回true,否则返回false
	bool AddItem ( const Item& item , const int& add_num );

	//移除`remove_num`个在背包中`position`位置的物品
	//若`remove_num`超过该格子中现有物品的数量，则清空该格子
	//返回值：
	//背包的`position`位置处未放置物品时返回-1
	//`remove_num`超过该格子中现有物品的数量，则清空该格子，并返回1
	//正常移除背包中`position`处的`remove_num`个物品时，返回0;
	int RemoveItem ( const int& position , const int& remove_num = 1 );

	//清空背包中`position`位置的格子
	bool ClearGrid ( const int& position );

	//获取`selected_position`的Item
	//未找到则返回nullptr
	std::shared_ptr<Item> GetSelectedItem ()const;

	//获取`selected_position`的Item的副本（用于如种子种植等需要获取多个不同Item实例的场景)
	//未找到或拷贝失败则返回nullptr
	std::shared_ptr<Item> GetSelectedItemCopy ();


	std::shared_ptr<Item> GetItemAt ( int position ) const {}

	// 获取指定位置中的物品个数  
	int GetItemCountAt ( int position ) const {}

	// 获取背包中指定名称的 Item  
	Item Inventory::GetItemByName ( const std::string& itemName ) const {}

	// 使用 Item 和数量移除物品  
	int Inventory::RemoveItem ( const Item& item , const int& remove_num = 1 ) {}

	//在`new_position`合法时，将`selected_position`设置为`new_position`
	// 合法的`new_position`应当为在[1,kRowSize]间的整数（只能设置物品栏最顶一栏的位置为`selected_position`
	//若原`selected_position`处有Item，更新其为unusable状态
	//若`new_position`<1 || `new_position`>kRowSize 返回-1
	//若`new_position`处有Item,更新其为usable状态，返回0
	//若`new_position`处无Item,返回-1
	int SetSelectedItem (const int new_position);

	Inventory& operator=( const Inventory& other ) {
		if (this == &other) {
			return *this;
		}
		this->capacity = other.capacity;
		this->package = other.package;
		return *this;
	}

	//向控制台输出Package信息，仅用于调试
	void DisplayPackageInCCLOG ();
};
```

- UI界面
  
本项目共实现了11个UI界面，以推动用户与游戏内容的互动，`GameBeginUI`类与`CreateCharacterUI`类继承自Scene，其他类均继承自Layer。每个类中主要包括`init`方法（初始化UI组件）、`create`方法（创建类的实例）以及一些私有成员函数、成员变量以及事件处理（鼠标键盘事件以及UI显示的更新）。基本框架如下：
```cpp
class BaseUI : public cocos2d::Layer {  
public:  
    virtual bool init() {  
        // 初始化背景或其他 UI 组件  
        return true; // 返回初始化状态  
    }  

    static BaseUI* create() {  
        BaseUI* ret = new (std::nothrow) BaseUI();  
        if (ret && ret->init()) {  
            ret->autorelease(); // 确保对象的内存安全  
            return ret;  
        }  
        delete ret;  
        return nullptr;  
    }  

protected:  
    // 私有成员变量  
    std::string sceneName; // 场景名称  
    cocos2d::Label* itemLabel; // 显示物品信息的标签  
    cocos2d::Vector<cocos2d::Sprite*> itemSlots; // 存储物品槽的 Sprite  
    bool isClick = false; // 标志是否被点击  

    // 私有成员函数示例  
    void backgroundCreate() {  
        // 创建背景图  
    }  

    void updateDisplay() {  
        // 更新显示内容  
    }  

    void close() {  
        // 关闭界面或返回上一个界面  
    }  

    void updateCoordinate(float& x, float& y) {  
        // 更新坐标位置  
    }  

    void buttonsSwitching() {  
        // 切换按钮状态或样式  
    }  
};  
```

## C++特性使用及其他

### 智能指针
使用`std::shared_ptr`可以自动管理内存的生命周期。当一个对象没有使用时，智能指针会自动释放内存，避免内存泄漏。通过返回智能指针，可以确保获得对象的共享所有权，同时避免了手动管理内存的复杂性。我们采用这种方法使得代码更安全，减少了常见的内存错误。
```cpp
virtual std::shared_ptr<Item> GetCopy() const;
```

### 自动类型推导
`auto`关键字允许编译器推导变量类型，可以让代码变得更加简洁和易读。使用`auto`可以省去显式类型声明的麻烦，尤其在处理复杂类型（如容器或函数返回类型）时，能显著提升代码的可维护性和可读性。
```cpp
auto farm = farm::create ();
```

### 范围基于的循环
使用范围基于的循环为我们提供了简洁的迭代方式，无需手动管理迭代器或索引。可以有效减少错误，避免遍历容器时的越界问题，同时代码也更为整洁。
```cpp
for (auto& pair : T_lastplace)
```

### Lambda表达式
```cpp
this->schedule ( [elliott]( float dt ) {
    elliott->RandomMove ();
    auto elliottSprite = elliott->GetSprite (); 
    if (elliottSprite) {
        Vec2 position = elliottSprite->getPosition ();
        Size size = elliottSprite->getContentSize ();
        // CCLOG ( "Elliott's current position: (%f, %f)" , position.x , position.y );  
    }
    } , 1.0f , "random_move_key_elliott" );
```

### nullptr
`nullptr`是 C++11 引入的更安全的空指针表示。它解决了使用常量`NULL`导致的潜在类型转换问题，并且提供了更强的类型安全性。我们使用`nullptr`来避免因空指针引发的错误，提高代码的可维护性与健壮性。
```cpp
return nullptr;
```

### 抛出异常
异常处理机制允许程序在发生错误时进行处理而非直接崩溃。抛出异常使得错误信息更明显，我们在调试任务系统时使用抛出异常和异常捕获，来查找错误信息与错误位置。
```cpp
throw std::runtime_error ( "No task found with the required item." );
```

### 单元测试
使用单元测试可以有效确保代码的正确性和稳定性。我们结合`Google Test`框架，编写测试用例对负责后端管理数据的类进行测试。通过进行自动化的测试，检查代码中的问题，维护代码质量，并在重构和扩展功能时降低引入错误的风险。
```cpp
#include "pch.h"  // 预编译头文件  
#include "gtest/gtest.h"  

// 测试用例 
TEST ( NpcRelationshipTests , AddNpcTest ) {
    NpcRelationship npcRel;
    npcRel.add_npc ( "NPC_1" );

    // 验证 NPC 是否已被添加  
    ASSERT_EQ ( 0 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , SetRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 30 );

    // 验证关系设置是否正常  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , IncreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.increaseRelationship ( "NPC_1" , "NPC_2" , 10 );

    // 验证关系增加  
    ASSERT_EQ ( 60 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , DecreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.decreaseRelationship ( "NPC_1" , "NPC_2" , 20 );

    // 验证关系减少  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , GetRelationshipLevelTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 70 );

    // 验证关系等级  
    ASSERT_STREQ ( "亲密" , npcRel.getRelationshipLevel ( "NPC_1" , "NPC_2" ).c_str () );
}

// 主函数  
int main ( int argc , char** argv ) {
    ::testing::InitGoogleTest ( &argc , argv );
    return RUN_ALL_TESTS ();
}
```





















