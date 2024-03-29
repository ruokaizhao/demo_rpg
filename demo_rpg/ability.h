#pragma once
#include <string>
#include "types.h"

struct Ability
{
	std::string m_name;
	AbilityType m_cost;
	AbilityType m_cooldown;
	AbilityType m_hit_point_effect;
	AbilityTarget m_target;
	AbilityScalar m_scalar;

	Ability(std::string name_value = "unnamed",
		AbilityType cost_value = 0u,
		AbilityType cooldown_value = 1u,
		AbilityType hit_point_effect_value = 1u,
		AbilityTarget target_value = AbilityTarget::SELF,
		AbilityScalar scalar_value = AbilityScalar::none)
		: m_name{ name_value },
		m_cost{ cost_value },
		m_cooldown{ cooldown_value },
		m_hit_point_effect{ hit_point_effect_value },
		m_target{ target_value },
		m_scalar{ scalar_value } {}
};