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
  - 接受并完成居民的委托任务，提高声望和收获奖励，任务包括收集特定物品、参与节日等。
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





