#include "pch.h"  // 预编译头文件  
#include "gtest/gtest.h"  

/*
这里写进行测试的部分，在上面菜单的测试->测试资源管理器->运行中进行测试
*/

// 测试用例示例  
TEST ( NpcRelationshipTests , AddNpcTest ) {
    NpcRelationship npcRel;
    npcRel.add_npc ( "NPC_1" );

    // 验证 NPC 是否已被添加  
    ASSERT_EQ ( 0 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , SetRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 30 );

    // 验证关系设置是否正常  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , IncreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.increaseRelationship ( "NPC_1" , "NPC_2" , 10 );

    // 验证关系增加  
    ASSERT_EQ ( 60 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , DecreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.decreaseRelationship ( "NPC_1" , "NPC_2" , 20 );

    // 验证关系减少  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , GetRelationshipLevelTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 70 );

    // 验证关系等级  
    ASSERT_STREQ ( "亲密" , npcRel.getRelationshipLevel ( "NPC_1" , "NPC_2" ).c_str () );
}

// 主函数  
int main ( int argc , char** argv ) {
    ::testing::InitGoogleTest ( &argc , argv );
    return RUN_ALL_TESTS ();
}