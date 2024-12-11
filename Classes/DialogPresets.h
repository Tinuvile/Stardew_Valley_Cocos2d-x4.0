#ifndef __DIALOG_PRESETS_H__  
#define __DIALOG_PRESETS_H__  

#include <vector>  
#include <string>  

// 返回一组预设的对话内容  
std::vector<std::string> getDialogResponses () {
    return {
        "你好，欢迎来到我的小店！",
        "今天的天气真好，你觉得呢？",
        "如果需要帮助，请告诉我。",
        "你喜欢这个地方吗？"
    };
}

#endif // __DIALOG_PRESETS_H__
