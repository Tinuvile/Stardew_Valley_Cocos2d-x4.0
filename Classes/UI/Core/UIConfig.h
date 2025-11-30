// UIConfig.h - UI配置管理器
// 管理场景边界、坐标等配置信息
#ifndef __UI_CONFIG_H__
#define __UI_CONFIG_H__

#include "cocos2d.h"
#include <string>
#include <unordered_map>

USING_NS_CC;

/**
 * @class UIConfig
 * @brief UI配置管理类，管理场景边界等配置
 *
 * 统一管理之前散落在各个UI中的配置信息，如：
 * - 场景边界坐标
 * - UI资源路径
 * - 特定场景的UI配置
 */
class UIConfig {
public:
    // 场景边界信息
    struct SceneBounds {
        float leftBoundary;
        float rightBoundary;
        float upperBoundary;
        float lowerBoundary;

        SceneBounds()
            : leftBoundary(-10000.0f)
            , rightBoundary(10000.0f)
            , upperBoundary(10000.0f)
            , lowerBoundary(-10000.0f) {
        }

        SceneBounds(float left, float right, float upper, float lower)
            : leftBoundary(left)
            , rightBoundary(right)
            , upperBoundary(upper)
            , lowerBoundary(lower) {
        }
    };

    // 获取单例
    static UIConfig* getInstance();

    // 获取场景边界
    SceneBounds getSceneBounds(const std::string& sceneName) const;

    // 根据场景边界调整坐标
    Vec2 adjustCoordinate(const std::string& sceneName, const Vec2& position) const;

    // UI资源路径管理
    std::string getUIResourcePath(const std::string& resourceName) const;

    // 常用UI资源路径
    struct UIResources {
        // 背包相关
        static constexpr const char* BAG_BACKGROUND = "UIresource/beibao/newbag2.png";
        static constexpr const char* ITEM_BLOCK = "UIresource/beibao/itemblock.png";
        static constexpr const char* BAG_KEY = "UIresource/beibao/bagkey.png";
        static constexpr const char* SKILL_KEY = "UIresource/beibao/Skillkey.png";
        static constexpr const char* INTIMACY_KEY = "UIresource/beibao/intimacykey.png";
        static constexpr const char* QUIT_KEY = "UIresource/beibao/quit.png";

        // 技能树相关
        static constexpr const char* SKILL_BACKGROUND = "UIresource/SkillTree/background.png";
        static constexpr const char* SKILL_BACKGROUND1 = "UIresource/SkillTree/background1.png";
        static constexpr const char* FULL_SKILL1 = "UIresource/SkillTree/fullSkill1.png";
        static constexpr const char* FULL_SKILL2 = "UIresource/SkillTree/fullSkill2.png";
        static constexpr const char* EMPTY_SKILL1 = "UIresource/SkillTree/emptySkill1.png";
        static constexpr const char* EMPTY_SKILL2 = "UIresource/SkillTree/emptySkill2.png";

        // 游戏开始界面
        static constexpr const char* START_BUTTON1 = "UIresource/start1.png";
        static constexpr const char* START_BUTTON2 = "UIresource/start2.png";
        static constexpr const char* LOAD_BUTTON1 = "UIresource/load1.png";
        static constexpr const char* LOAD_BUTTON2 = "UIresource/load2.png";
        static constexpr const char* COOP_BUTTON1 = "UIresource/coop1.png";
        static constexpr const char* COOP_BUTTON2 = "UIresource/coop2.png";
        static constexpr const char* QUIT_BUTTON1 = "UIresource/quit1.png";
        static constexpr const char* QUIT_BUTTON2 = "UIresource/quit2.png";

        // 按钮相关
        static constexpr const char* OK_BUTTON_NORMAL = "UIresource/create/OK.png";
        static constexpr const char* OK_BUTTON_PRESSED = "UIresource/create/OK.png";

        // 其他
        static constexpr const char* QUIT_IMAGE = "UIresource/quit.png";
        static constexpr const char* MAILBOX_IMAGE = "UIresource/xinxiang/renwu2.png";
    };

private:
    UIConfig();
    ~UIConfig();

    // 禁止拷贝
    UIConfig(const UIConfig&) = delete;
    UIConfig& operator=(const UIConfig&) = delete;

    // 初始化场景边界
    void initializeSceneBounds();

private:
    static UIConfig* s_instance;
    std::unordered_map<std::string, SceneBounds> m_sceneBounds;
};

#endif // __UI_CONFIG_H__
