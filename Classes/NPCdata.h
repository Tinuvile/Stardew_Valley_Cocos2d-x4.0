#ifndef NPCDATA_H  
#define NPCDATA_H  

#include <vector>  
#include <string>  
#include <map>
#include "cocos2d.h"  

using namespace cocos2d;

// ��ȡ NPC ����֡��Ϣ�ĺ���  
std::vector<std::vector<std::string>> getAbigailAnimations () {
    return {
        {"npc/Abigail/Abigail-8.png", "npc/Abigail/Abigail-9.png", "npc/Abigail/Abigail-10.png", "npc/Abigail/Abigail-11.png"},
        {"npc/Abigail/Abigail-0.png", "npc/Abigail/Abigail-1.png", "npc/Abigail/Abigail-2.png", "npc/Abigail/Abigail-3.png"},
        {"npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-13.png", "npc/Abigail/Abigail-14.png", "npc/Abigail/Abigail-15.png"},
        {"npc/Abigail/Abigail-4.png", "npc/Abigail/Abigail-5.png", "npc/Abigail/Abigail-6.png", "npc/Abigail/Abigail-7.png"}
    };
}

// ��ȡ NPC ��ͷ��·��
std::string getNPCportraits ( std::string name , std::string status ) {
    std::map<std::string , std::map<std::string , std::string>> npcPortraits;

    // Abigail
    // �ļ�
    npcPortraits["Abigail"]["SummerNormal"] = "Portraits/Abigail/Abigail_Beach-0.png";
    npcPortraits["Abigail"]["SummerSmile"] = "Portraits/Abigail/Abigail_Beach-1.png";
    npcPortraits["Abigail"]["SummerAngry"] = "Portraits/Abigail/Abigail_Beach-5.png";
    npcPortraits["Abigail"]["SummerAmazed"] = "Portraits/Abigail/Abigail_Beach-7.png";
    // ����
    npcPortraits["Abigail"]["WinterNormal"] = "Portraits/Abigail/Abigail_Winter-0.png";
    npcPortraits["Abigail"]["WinterSmile"] = "Portraits/Abigail/Abigail_Winter-1.png";
    npcPortraits["Abigail"]["WinterAngry"] = "Portraits/Abigail/Abigail_Winter-5.png";
    npcPortraits["Abigail"]["WinterAmazed"] = "Portraits/Abigail/Abigail_Winter-7.png";
    // ��ͨ
    npcPortraits["Abigail"]["Normal"] = "Portraits/Abigail/Abigail-0.png";
    npcPortraits["Abigail"]["Smile"] = "Portraits/Abigail/Abigail-1.png";
    npcPortraits["Abigail"]["Angry"] = "Portraits/Abigail/Abigail-5.png";
    npcPortraits["Abigail"]["Amazed"] = "Portraits/Abigail/Abigail-7.png";


    // Alex
    // �ļ�
    npcPortraits["Alex"]["SummerNormal"] = "Portraits/Alex/Alex_Beach-0.png";
    npcPortraits["Alex"]["SummerSmile"] = "Portraits/Alex/Alex_Beach-1.png";
    npcPortraits["Alex"]["SummerAngry"] = "Portraits/Alex/Alex_Beach-4.png";
    npcPortraits["Alex"]["SummerAmazed"] = "Portraits/Alex/Alex_Beach-6.png";
    // ����
    npcPortraits["Alex"]["WinterNormal"] = "Portraits/Alex/Alex_Winter-0.png";
    npcPortraits["Alex"]["WinterSmile"] = "Portraits/Alex/Alex_Winter-1.png";
    npcPortraits["Alex"]["WinterAngry"] = "Portraits/Alex/Alex_Winter-5.png";
    npcPortraits["Alex"]["WinterAmazed"] = "Portraits/Alex/Alex_Winter-7.png";
    // ��ͨ
    npcPortraits["Alex"]["Normal"] = "Portraits/Alex/Alex-0.png";
    npcPortraits["Alex"]["Smile"] = "Portraits/Alex/Alex-1.png";
    npcPortraits["Alex"]["Angry"] = "Portraits/Alex/Alex-5.png";
    npcPortraits["Alex"]["Amazed"] = "Portraits/Alex/Alex-7.png";


    // Caroline
    // �ļ�
    npcPortraits["Caroline"]["SummerNormal"] = "Portraits/Caroline/Caroline_Beach-0.png";
    npcPortraits["Caroline"]["SummerSmile"] = "Portraits/Caroline/Caroline_Beach-1.png";
    npcPortraits["Caroline"]["SummerAngry"] = "Portraits/Caroline/Caroline_Beach-2.png";
    npcPortraits["Caroline"]["SummerAmazed"] = "Portraits/Caroline/Caroline_Beach-3.png";
    // ����
    npcPortraits["Caroline"]["WinterNormal"] = "Portraits/Caroline/Caroline_Winter-0.png";
    npcPortraits["Caroline"]["WinterSmile"] = "Portraits/Caroline/Caroline_Winter-1.png";
    npcPortraits["Caroline"]["WinterAngry"] = "Portraits/Caroline/Caroline_Winter-2.png";
    npcPortraits["Caroline"]["WinterAmazed"] = "Portraits/Caroline/Caroline_Winter-3.png";
    // ��ͨ
    npcPortraits["Caroline"]["Normal"] = "Portraits/Caroline/Caroline-0.png";
    npcPortraits["Caroline"]["Smile"] = "Portraits/Caroline/Caroline-1.png";
    npcPortraits["Caroline"]["Angry"] = "Portraits/Caroline/Caroline-2.png";
    npcPortraits["Caroline"]["Amazed"] = "Portraits/Caroline/Caroline-3.png";


    // Elliott
    // �ļ�
    npcPortraits["Elliott"]["SummerNormal"] = "Portraits/Elliott/Elliott_Beach-0.png";
    npcPortraits["Elliott"]["SummerSmile"] = "Portraits/Elliott/Elliott_Beach-5.png";
    npcPortraits["Elliott"]["SummerAngry"] = "Portraits/Elliott/Elliott_Beach-1.png";
    npcPortraits["Elliott"]["SummerAmazed"] = "Portraits/Elliott/Elliott_Beach-8.png";
    // ����
    npcPortraits["Elliott"]["WinterNormal"] = "Portraits/Elliott/Elliott_Winter-0.png";
    npcPortraits["Elliott"]["WinterSmile"] = "Portraits/Elliott/Elliott_Winter-5.png";
    npcPortraits["Elliott"]["WinterAngry"] = "Portraits/Elliott/Elliott_Winter-1.png";
    npcPortraits["Elliott"]["WinterAmazed"] = "Portraits/Elliott/Elliott_Winter-8.png";
    // ��ͨ
    npcPortraits["Elliott"]["Normal"] = "Portraits/Elliott/Elliott-0.png";
    npcPortraits["Elliott"]["Smile"] = "Portraits/Elliott/Elliott-5.png";
    npcPortraits["Elliott"]["Angry"] = "Portraits/Elliott/Elliott-1.png";
    npcPortraits["Elliott"]["Amazed"] = "Portraits/Elliott/Elliott-8.png";


    // Emily
    // �ļ�
    npcPortraits["Emily"]["SummerNormal"] = "Portraits/Emily/Emily_Beach-0.png";
    npcPortraits["Emily"]["SummerSmile"] = "Portraits/Emily/Emily_Beach-1.png";
    npcPortraits["Emily"]["SummerAngry"] = "Portraits/Emily/Emily_Beach-2.png";
    npcPortraits["Emily"]["SummerAmazed"] = "Portraits/Emily/Emily_Beach-6.png";
    // ����
    npcPortraits["Emily"]["WinterNormal"] = "Portraits/Emily/Emily_Winter-0.png";
    npcPortraits["Emily"]["WinterSmile"] = "Portraits/Emily/Emily_Winter-1.png";
    npcPortraits["Emily"]["WinterAngry"] = "Portraits/Emily/Emily_Winter-2.png";
    npcPortraits["Emily"]["WinterAmazed"] = "Portraits/Emily/Emily_Winter-6.png";
    // ��ͨ
    npcPortraits["Emily"]["Normal"] = "Portraits/Emily/Emily-0.png";
    npcPortraits["Emily"]["Smile"] = "Portraits/Emily/Emily-1.png";
    npcPortraits["Emily"]["Angry"] = "Portraits/Emily/Emily-2.png";
    npcPortraits["Emily"]["Amazed"] = "Portraits/Emily/Emily-6.png";


    // ������� NPC ������ӳ���д���  
    if (npcPortraits.find ( name ) != npcPortraits.end ()) { 
        // ������Ӧ״̬��ͷ��·��  
        return npcPortraits[name][status];
    }

    // ��� NPC ���Ʋ����ڣ��򷵻ؿ��ַ����������Ϣ  
    return "ERROR"; // ���߿��Է���Ĭ��ͷ��·��  
}

#endif // NPCDATA_H