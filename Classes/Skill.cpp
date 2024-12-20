#include"Skill.h"

int Skill::CalculateExperienceNeeded ( const int level ) const {
    return (level + 1) * 100;
}

Skill::Skill(const int skill_type)
    : type ( skill_type ) , level ( 0 ) , experience ( 0 ) ,
    experience_needed ( CalculateExperienceNeeded ( 0 ) ) {}

void Skill::AddExperience ( const int amount ) {
    experience += amount;
    while (experience >= experience_needed) {
        LevelUp ();
    }
}

void Skill::Reset() {
    level = 0;
    experience = 0;
    experience_needed = CalculateExperienceNeeded ( 0 );
}

int Skill::LevelUp() {
    level++;
    experience_needed = CalculateExperienceNeeded ( level );
    return level;
}