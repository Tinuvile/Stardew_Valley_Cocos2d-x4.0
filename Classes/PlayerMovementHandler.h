#ifndef __PLAYER_MOVEMENT_HANDLER_H__
#define __PLAYER_MOVEMENT_HANDLER_H__

#include "InputHandler.h"

/**
 * 玩家移动输入处理器
 * 负责处理方向键输入，控制玩家的移动和动画
 */
class PlayerMovementHandler : public InputHandler {
public:
    PlayerMovementHandler();
    virtual ~PlayerMovementHandler() = default;
    
    /**
     * 处理按键按下事件
     * 主要处理方向键（↑↓←→）
     */
    bool handleKeyPressed(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 处理按键释放事件
     * 更新玩家状态和贴图
     */
    bool handleKeyReleased(EventKeyboard::KeyCode keyCode, Event* event, const GameContext& context) override;
    
    /**
     * 获取处理器类型名称
     */
    std::string getHandlerType() const override { return "PlayerMovementHandler"; }

private:
    
    /**
     * 检查是否为方向键
     * @param keyCode 按键代码
     * @return 是否为方向键
     */
    bool isDirectionKey(EventKeyboard::KeyCode keyCode);
    
    /**
     * 将按键转换为方向
     * @param keyCode 按键代码
     * @return 方向值 (0:上, 1:下, 2:左, 3:右, -1:无效)
     */
    int getDirectionFromKey(EventKeyboard::KeyCode keyCode);
    
    // 使用Player类的方向常量
    static const int UP = Player::DIRECTION_UP;
    static const int DOWN = Player::DIRECTION_DOWN;
    static const int LEFT = Player::DIRECTION_LEFT;
    static const int RIGHT = Player::DIRECTION_RIGHT;
};

#endif // __PLAYER_MOVEMENT_HANDLER_H__
