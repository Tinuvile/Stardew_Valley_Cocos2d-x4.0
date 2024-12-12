#ifndef __BasicInformation_H__
#define __BasicInformation_H__

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

class CropBasicInformation {

public:

    CropBasicInformation(std::string FP, std::string SP, std::string TP, std::string SS) : firstpath(FP), secondpath(SP), season(SS), thirdpath(TP){}
    CropBasicInformation(){}

   
    // ��һ�׶ε�ͼ��
    std::string firstpath;
    // �ڶ��׶ε�ͼ��
    std::string secondpath;
    // �����׶ε�ͼ��
    std::string thirdpath;
    // ���������ļ���
    std::string season;
   


};

#endif
