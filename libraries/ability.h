#pragma once
#include "types.h"
#include "enums.h"
#include <string>

class Ability
{
public:
	Ability(std::string name_value = "unnamed",
		AbilityType cost_value = 0u,
		AbilityType cooldown_value = 1u,
		AbilityType hit_point_effect_value = 1u,
		AbilityTarget target_value = AbilityTarget::self,
		AbilityScalar scalar_value = AbilityScalar::none)
		: m_name{ name_value },
		m_cost{ cost_value },
		m_cooldown{ cooldown_value },
		m_hit_point_effect{ hit_point_effect_value },
		m_target{ target_value },
		m_scalar{ scalar_value } {}

	const std::string get_m_name() const
	{
		return m_name;
	}

	const AbilityType get_m_cost() const
	{
		return m_cost;
	}

	const AbilityType get_m_cooldown() const
	{
		return m_cooldown;
	}

	const AbilityType get_m_round_until_available() const
	{
		return m_round_until_available;
	}

	const AbilityType get_m_hit_point_effect() const
	{
		return m_hit_point_effect;
	}

	const AbilityTarget get_m_target() const
	{
		return m_target;
	}

	const AbilityScalar get_m_scalar() const
	{
		return m_scalar;
	}

	void set_m_time_until_available(AbilityType time_value)
	{
		m_round_until_available = time_value;
	}

private:
	std::string m_name{};
	AbilityType m_cost{};
	AbilityType m_cooldown{};
	AbilityType m_round_until_available{};
	AbilityType m_hit_point_effect{};
	AbilityTarget m_target{};
	AbilityScalar m_scalar{};
};