/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 许可声明：本软件可以自由使用、复制、修改、合并、发布、分发、再许可和/或销售，并允许获得此软件的人执行这些操作，前提是保留版权声明和许可声明。

 软件按“原样”提供，不做任何形式的保证，开发者对因使用该软件而产生的任何问题不承担责任。
 ****************************************************************************/

#ifndef  _APP_DELEGATE_H_  // 防止头文件被多次包含的宏
#define  _APP_DELEGATE_H_

#include "cocos2d.h"  // 引入 Cocos2d-x 引擎的主头文件
#include "Player.h"

 /**
  @brief    Cocos2d 应用程序的委托类（AppDelegate）

  此类负责处理应用程序的生命周期管理，包括应用启动、进入后台、进入前台等操作。
  继承自 cocos2d::Application 类，但通过私有继承来隐藏部分接口，确保用户只能访问公共接口。
  */

  /************************************ 全局变量声明区 ******************************************/
  // 设定游戏画面大小：1600, 1280
static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 1280);  // 设计分辨率



class AppDelegate : private cocos2d::Application  // 继承自 cocos2d::Application 类，并私有化继承
{
public:
    // 构造函数
    AppDelegate();

    // 析构函数
    virtual ~AppDelegate();

    // 初始化 OpenGL 上下文属性的函数
    virtual void initGLContextAttrs();

    /**
    @brief    应用程序启动时的初始化函数
    @return true    初始化成功，应用继续运行。
    @return false   初始化失败，应用程序退出。
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief    应用程序进入后台时调用。
    @param    the pointer of the application 指向应用程序的指针（Cocos2d 内部会调用此函数）
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief    应用程序重新进入前台时调用。
    @param    the pointer of the application 指向应用程序的指针（Cocos2d 内部会调用此函数）
    */
    virtual void applicationWillEnterForeground();

    void runScene(cocos2d::Director* director);

};

#endif // _APP_DELEGATE_H_  // 结束防止头文件被多次包含的宏
