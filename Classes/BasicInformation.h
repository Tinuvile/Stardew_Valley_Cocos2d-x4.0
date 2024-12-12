#ifndef __BasicInformation_H__
#define __BasicInformation_H__

#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

class CropBasicInformation {

public:

    CropBasicInformation(std::string FP, std::string SP, std::string TP, std::string SS) : firstpath(FP), secondpath(SP), season(SS), thirdpath(TP){}
    CropBasicInformation(){}

   
    // 第一阶段的图像
    std::string firstpath;
    // 第二阶段的图像
    std::string secondpath;
    // 第三阶段的图像
    std::string thirdpath;
    // 适宜生长的季节
    std::string season;
   


};

#endif
