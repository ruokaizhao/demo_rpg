#pragma once
#include <string>

typedef uint16_t ability_type;

enum class ABILITY_TARGET
{
	SELF,
	ALLY,
	ENEMY
};

enum class ABILITY_SCALAR
{
	NONE, STRENGTH, INTELLIGENCE, AGILITY
};

struct Ability
{
	Ability(std::string name_value = "unnamed",
		ability_type cost_value = 0u,
		ability_type cooldown_value = 1u,
		ability_type hit_point_effect_value = 1u,
		ABILITY_TARGET target_value = ABILITY_TARGET::SELF,
		ABILITY_SCALAR scalar_value = ABILITY_SCALAR::NONE)
		: m_name{ name_value },
		m_cost{ cost_value },
		m_cooldown{ cooldown_value },
		m_hit_point_effect{ hit_point_effect_value },
		m_target{ target_value },
		m_scalar{ scalar_value } {}

	std::string m_name;
	ability_type m_cost;
	ability_type m_cooldown;
	ability_type m_hit_point_effect;
	ABILITY_TARGET m_target;
	ABILITY_SCALAR m_scalar;
};
