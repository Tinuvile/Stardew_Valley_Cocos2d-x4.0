#include "pch.h"  // Ԥ����ͷ�ļ�  
#include "gtest/gtest.h"  

/*
����д���в��ԵĲ��֣�������˵��Ĳ���->������Դ������->�����н��в���
*/

// ��������ʾ��  
TEST ( NpcRelationshipTests , AddNpcTest ) {
    NpcRelationship npcRel;
    npcRel.add_npc ( "NPC_1" );

    // ��֤ NPC �Ƿ��ѱ����  
    ASSERT_EQ ( 0 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , SetRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 30 );

    // ��֤��ϵ�����Ƿ�����  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , IncreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.increaseRelationship ( "NPC_1" , "NPC_2" , 10 );

    // ��֤��ϵ����  
    ASSERT_EQ ( 60 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , DecreaseRelationshipTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 50 );
    npcRel.decreaseRelationship ( "NPC_1" , "NPC_2" , 20 );

    // ��֤��ϵ����  
    ASSERT_EQ ( 30 , npcRel.getRelationship ( "NPC_1" , "NPC_2" ) );
}

TEST ( NpcRelationshipTests , GetRelationshipLevelTest ) {
    NpcRelationship npcRel;
    npcRel.setRelationship ( "NPC_1" , "NPC_2" , 70 );

    // ��֤��ϵ�ȼ�  
    ASSERT_STREQ ( "����" , npcRel.getRelationshipLevel ( "NPC_1" , "NPC_2" ).c_str () );
}

// ������  
int main ( int argc , char** argv ) {
    ::testing::InitGoogleTest ( &argc , argv );
    return RUN_ALL_TESTS ();
}