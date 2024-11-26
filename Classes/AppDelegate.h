/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 ����������������������ʹ�á����ơ��޸ġ��ϲ����������ַ�������ɺ�/�����ۣ��������ô��������ִ����Щ������ǰ���Ǳ�����Ȩ���������������

 �������ԭ�����ṩ�������κ���ʽ�ı�֤�������߶���ʹ�ø�������������κ����ⲻ�е����Ρ�
 ****************************************************************************/

#ifndef  _APP_DELEGATE_H_  // ��ֹͷ�ļ�����ΰ����ĺ�
#define  _APP_DELEGATE_H_

#include "cocos2d.h"  // ���� Cocos2d-x �������ͷ�ļ�
#include "Player.h"

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

};

#endif // _APP_DELEGATE_H_  // ������ֹͷ�ļ�����ΰ����ĺ�
