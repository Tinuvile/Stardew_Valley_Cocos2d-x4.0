# <strong>加分项</strong>

- 基础功能
  - 农场管理
    - 玩家可以耕种、种植并收获多种作物，作物可否种植有季节限制，作物的成熟时间根据种类和季节变化。
    - 养殖牛、鸡和羊。
    - 农场操作包括浇水、施肥、收获，以及管理干旱和病害威胁，未及时处理会导致作物死亡。
    - 管理农场资源，如水资源、种子和肥料存储。
  - 社区交互：
    - 与镇上的居民建立关系、对话、送礼物和结婚，各种行为影响与人物的亲密度。
    - 参与定期的社区活动和节日庆典。
    - 接受并完成居民的委托任务、小镇任务或是节假日任务，提高声望、收获金币和特殊物品。
  - 探索和冒险：
    - 探索农场周边的地区，包括森林、山脉和神秘洞穴。
    - 挖掘矿物、钓鱼和收集稀有物品。
  - 角色成长和技能：
    - 角色技能树，包括农业、采矿、钓鱼和料理等。
    - 随着技能提升，解锁新的作物种类、工具升级和烹饪食谱。
- 拓展功能
  - 天气系统
    - 复杂的天气系统，会影响农作物的种植以及NPC的穿着，包括下雨、季节变化。
  - 背景音乐
    - 根据场景的变换切换背景音乐。

## 天气系统
我们构建了复杂的天气与季节系统，游戏中的各个元素都会随之变化，例如在雨天种植的作物无需浇水也不会枯萎等。雨水效果的实现利用了Cocos2d-x中的粒子系统，这个系统是一种用于生成和管理大量粒子的系统，
允许开发者设置粒子的生命周期、速度、颜色、透明度、大小、旋转等，我们创建雨滴粒子并将其加入到场景中，使用调度器实现游戏运行过程中对粒子状态的更新。
```cpp
emitter = ParticleRain::create();
emitter->setDuration(ParticleSystem::DURATION_INFINITY);
emitter->setScale(5.7f);
emitter->setTotalParticles(100);
emitter->setSpeed(250);
addChild(emitter, 10);
schedule([this](float dt) {
    updaterain(dt);
    }, "update_rain_key");
```

## 音频系统
我们为游戏里的各个场景及人物行为准备了丰富的音频系统，开场动画使用星露谷游戏的原音频，农场、沙滩、商店以及结婚也有专属的背景音乐。使用Cocos2d-x中的AudioEngine实现，
这个类专用于处理游戏音频，支持异步加载和播放，可以确保游戏的流畅性
```cpp
开场音乐：
auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/01 - Stardew Valley Overture.mp3" , true );
农场音乐：
auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/TheShire.mp3" , true );
沙滩音乐：
auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/Mayten.mp3" , true );
商店音乐：
auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/MayYouBeHappyAndProsperous.mp3" , true );
结婚音乐：
auto backgroundAudioID = AudioEngine::play2d ( "MUSIC/AthousandYears.mp3" , true );
```

## 项目协作
在本次项目中，我们进行了合理的任务分工，将整体任务划分为四个主要部分：地图与场景、主角与操作、社区NPC与任务以及UI界面。根据小组成员的特点，我们为每个部分分配了具体任务。在各部分独立实现的同时，
我们也为其他成员提供了必要的接口和函数调用，以便于各模块之间的协作。

另外，我们使用git进行版本控制，并使用github进行项目托管。通过git分支确保开发的独立性，合并时可以更容易地处理差异、减少干扰。

## C++特性使用

- 智能指针
  使用`std::shared_ptr`可以自动管理内存的生命周期。当一个对象没有使用时，智能指针会自动释放内存，避免内存泄漏。通过返回智能指针，可以确保获得对象的共享所有权，同时避免了手动管理内存的复杂性。我们采用这种方法使得代码更安全，减少了常见的内存错误。
  ```cpp
  virtual std::shared_ptr<Item> GetCopy() const;
  ```

- 自动类型推导
  `auto`关键字允许编译器推导变量类型，可以让代码变得更加简洁和易读。使用`auto`可以省去显式类型声明的麻烦，尤其在处理复杂类型（如容器或函数返回类型）时，能显著提升代码的可维护性和可读性。
  ```cpp
  auto farm = farm::create ();
  ```

- 范围基于的循环
  使用范围基于的循环为我们提供了简洁的迭代方式，无需手动管理迭代器或索引。可以有效减少错误，避免遍历容器时的越界问题，同时代码也更为整洁。
  ```cpp
  for (auto& pair : T_lastplace)
  ```

- Lambda表达式
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

- nullptr
  `nullptr`是 C++11 引入的更安全的空指针表示。它解决了使用常量`NULL`导致的潜在类型转换问题，并且提供了更强的类型安全性。我们使用`nullptr`来避免因空指针引发的错误，提高代码的可维护性与健壮性。
  ```cpp
  return nullptr;
  ```

- 抛出异常
  异常处理机制允许程序在发生错误时进行处理而非直接崩溃。抛出异常使得错误信息更明显，我们在调试任务系统时使用抛出异常和异常捕获，来查找错误信息与错误位置。
  ```cpp
  throw std::runtime_error ( "No task found with the required item." );
  ```

## 单元测试
在本项目中，我们还引入了单元测试以确保代码的正确性和稳定性。单元测试是软件开发中一种常用的测试方法，旨在验证代码中每个功能模块的独立性和可靠性。我们选择`Google Test`框架对人物亲密度数据管理等进行了单元测试。
提高了代码的可靠性，也为未来的重构和功能扩展提供了保障，降低了引入新错误的风险。
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

int main ( int argc , char** argv ) {
    ::testing::InitGoogleTest ( &argc , argv );
    return RUN_ALL_TESTS ();
}
```
