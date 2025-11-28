#include "NPCAdapter.h"
#include "cocos2d.h"

USING_NS_CC;

// 声明外部函数（来自NPC.cpp中的全局函数）
extern std::vector<std::vector<std::string>> getDialog(std::string npc, std::string relation_ship);
extern std::vector<std::vector<std::string>> getFestivalDialog(std::string npc, std::string relation_ship);
extern std::string getNPCportraits(std::string name, std::string status);

NPCAdapter::NPCAdapter(NPC* npcPtr, const std::string& objectId)
    : npc(npcPtr), id(objectId), isActiveFlag(true), interactionRange(60.0f), isInDialog(false) {
    if (!npc) {
        CCLOG("NPCAdapter::NPCAdapter - Warning: null NPC pointer provided");
        isActiveFlag = false;
    }
}

// === 基础属性实现 ===

std::string NPCAdapter::getName() const {
    return npc ? npc->GetName() : "Unknown NPC";
}

// === 位置管理实现 ===

cocos2d::Vec2 NPCAdapter::getPosition() const {
    return npc ? npc->GetPosition() : Vec2::ZERO;
}

void NPCAdapter::setPosition(const cocos2d::Vec2& pos) {
    if (npc) {
        npc->SetPosition(pos);
    }
}

cocos2d::Rect NPCAdapter::getBounds() const {
    if (npc) {
        auto sprite = npc->GetSprite();
        if (sprite) {
            return sprite->getBoundingBox();
        }
    }
    return Rect::ZERO;
}

// === 渲染相关实现 ===

cocos2d::Node* NPCAdapter::getRenderNode() const {
    return npc;
}

void NPCAdapter::updateTexture(float deltaTime) {
    if (!npc) return;
    
    // NPC的纹理更新通常通过动画系统处理
    // 这里可以根据需要添加特定的纹理更新逻辑
}

bool NPCAdapter::isVisible() const {
    if (npc) {
        auto sprite = npc->GetSprite();
        return sprite ? sprite->isVisible() : false;
    }
    return false;
}

void NPCAdapter::setVisible(bool visible) {
    if (npc) {
        auto sprite = npc->GetSprite();
        if (sprite) {
            sprite->setVisible(visible);
        }
    }
}

// === 生命周期管理实现 ===

void NPCAdapter::update(float deltaTime) {
    if (!npc || !isActiveFlag) return;
    
    // 更新NPC行为
    updateBehavior(deltaTime);
}

void NPCAdapter::cleanup() {
    // 注意：这里不删除npc对象，因为它可能被其他地方管理
    if (isInDialog) {
        isInDialog = false;
    }
    npc = nullptr;
    isActiveFlag = false;
}

// === 交互能力实现 ===

void NPCAdapter::onInteract(GameObjectInterface* interactor) {
    if (!npc || !interactor || isInDialog) return;
    
    CCLOG("NPCAdapter::onInteract - %s interacted with by %s", 
          getName().c_str(), interactor->getName().c_str());
    
    // 面向交互者
    faceTowards(interactor->getPosition());
    
    // 开始对话
    startDialog();
}

std::string NPCAdapter::getInteractionHint() const {
    if (!npc) return "";
    
    std::string hint = "Talk to " + getName();
    if (isInDialog) {
        hint = "Talking to " + getName();
    }
    return hint;
}

// === 移动能力实现 ===

void NPCAdapter::moveTo(const cocos2d::Vec2& target) {
    if (!npc) return;
    
    npc->MoveToPosition(target);
}

void NPCAdapter::randomMove() {
    if (!npc) return;
    
    npc->RandomMove();
}

void NPCAdapter::stopMovement() {
    if (!npc) return;
    
    // 停止当前的移动动作
    // 这可能需要根据NPC的具体实现来调整
}

// === 对话能力实现 ===

std::vector<std::string> NPCAdapter::getDialogOptions() const {
    if (!npc) return {};
    
    return getTypeSpecificDialog();
}

void NPCAdapter::startDialog() {
    if (!npc || isInDialog) return;
    
    isInDialog = true;
    CCLOG("NPCAdapter::startDialog - Started dialog with %s", getName().c_str());
    
    // 这里可以触发UI显示对话框
    // 需要与现有的对话系统集成
}

// === 状态查询实现 ===

std::string NPCAdapter::getStatusText() const {
    if (!npc) return "NPC (Invalid)";
    
    std::string status = getName();
    if (isInDialog) {
        status += " (Talking)";
    } else {
        status += " (Available)";
    }
    
    return status;
}

// === 事件回调实现 ===

void NPCAdapter::onCollisionEnter(GameObjectInterface* other) {
    if (!npc || !other) return;
    
    CCLOG("NPCAdapter::onCollisionEnter - %s collided with %s", 
          getName().c_str(), other->getName().c_str());
}

void NPCAdapter::onCollisionExit(GameObjectInterface* other) {
    if (!npc || !other) return;
    
    CCLOG("NPCAdapter::onCollisionExit - %s stopped colliding with %s", 
          getName().c_str(), other->getName().c_str());
}

void NPCAdapter::onDayPass() {
    if (!npc) return;
    
    CCLOG("NPCAdapter::onDayPass - New day for %s", getName().c_str());
    
    // 重置对话状态
    isInDialog = false;
    
    // 可以在这里实现NPC的每日行为重置
}

void NPCAdapter::onSeasonChange(const std::string& newSeason) {
    if (!npc) return;
    
    CCLOG("NPCAdapter::onSeasonChange - %s season change to: %s", 
          getName().c_str(), newSeason.c_str());
    
    // 可以在这里根据季节调整NPC的行为或外观
}

// === NPC特有方法实现 ===

cocos2d::Sprite* NPCAdapter::getNPCSprite() const {
    return npc ? npc->GetSprite() : nullptr;
}

bool NPCAdapter::isPositionValid(const cocos2d::Vec2& targetPos, const cocos2d::Vec2& direction) const {
    if (!npc) return false;
    
    return npc->IsPositionValid(targetPos, direction);
}

std::vector<std::string> NPCAdapter::getDialogForRelationship(const std::string& relationshipLevel) const {
    if (!npc) return {};
    
    try {
        auto dialogData = getDialog(getName(), relationshipLevel);
        std::vector<std::string> result;
        
        // 将二维字符串数组转换为一维数组
        for (const auto& dialogLine : dialogData) {
            for (const auto& text : dialogLine) {
                if (!text.empty()) {
                    result.push_back(text);
                }
            }
        }
        
        return result;
    } catch (...) {
        CCLOG("NPCAdapter::getDialogForRelationship - Error getting dialog for %s with relationship %s", 
              getName().c_str(), relationshipLevel.c_str());
        return {"Hello!"};
    }
}

std::vector<std::string> NPCAdapter::getFestivalDialog(const std::string& relationshipLevel) const {
    if (!npc) return {};
    
    try {
        auto dialogData = ::getFestivalDialog(getName(), relationshipLevel);
        std::vector<std::string> result;
        
        for (const auto& dialogLine : dialogData) {
            for (const std::string& text : dialogLine) {
                if (!text.empty()) {
                    result.push_back(text);
                }
            }
        }
        
        return result;
    } catch (...) {
        CCLOG("NPCAdapter::getFestivalDialog - Error getting festival dialog for %s", getName().c_str());
        return {"Happy festival!"};
    }
}

std::string NPCAdapter::getPortraitPath(const std::string& status) const {
    if (!npc) return "";
    
    try {
        return getNPCportraits(getName(), status);
    } catch (...) {
        CCLOG("NPCAdapter::getPortraitPath - Error getting portrait for %s with status %s", 
              getName().c_str(), status.c_str());
        return "";
    }
}

void NPCAdapter::playAnimation(const std::string& animationName, bool loop) {
    if (!npc) return;
    
    // 这里需要根据NPC类的动画系统实现
    // 当前NPC类可能有CreateAnimation和PlayAnimation方法需要调用
    CCLOG("NPCAdapter::playAnimation - Playing animation %s for %s", 
          animationName.c_str(), getName().c_str());
}

void NPCAdapter::faceTowards(const cocos2d::Vec2& targetPos) {
    if (!npc) return;
    
    Vec2 currentPos = getPosition();
    Vec2 direction = targetPos - currentPos;
    
    // 根据方向调整NPC的朝向
    // 这可能需要调用NPC的动画系统来改变朝向
    CCLOG("NPCAdapter::faceTowards - %s facing towards (%f, %f)", 
          getName().c_str(), targetPos.x, targetPos.y);
}

// === 私有方法实现 ===

void NPCAdapter::updateBehavior(float deltaTime) {
    if (!npc) return;
    
    // 如果不在对话中，执行AI移动
    if (!isInDialog) {
        updateAIMovement();
    }
}

void NPCAdapter::updateAIMovement() {
    if (!npc) return;
    
    // 定期执行随机移动
    static float moveTimer = 0.0f;
    moveTimer += 1.0f/60.0f; // 假设60FPS
    
    if (moveTimer >= 3.0f) { // 每3秒随机移动一次
        randomMove();
        moveTimer = 0.0f;
    }
}

std::vector<std::string> NPCAdapter::getTypeSpecificDialog() const {
    if (!npc) return {};
    
    // 默认对话，实际应该根据关系等级获取
    std::string defaultRelationship = "normal";
    return getDialogForRelationship(defaultRelationship);
}
