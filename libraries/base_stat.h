#pragma once
#include "types.h"
#include <string>

class BaseStat
{
public:
	explicit BaseStat(StatType strength_value = 0u,
		StatType intelligence_value = 0u,
		StatType agility_value = 0u,
		StatType physical_defense_value = 0u,
		StatType magic_resistance_value = 0u)
		: m_strength{ strength_value },
		m_intelligence{ intelligence_value },
		m_agility{ agility_value },
		m_physical_defense{ physical_defense_value },
		m_magic_resistance{ magic_resistance_value } {
	}

	BaseStat& operator+=(const BaseStat& rhs)
	{
		m_strength += rhs.m_strength;
		m_intelligence += rhs.m_intelligence;
		m_agility += rhs.m_agility;
		m_physical_defense += rhs.m_physical_defense;
		m_magic_resistance += rhs.m_magic_resistance;

		return *this;
	}

	BaseStat& operator-=(const BaseStat& rhs)
	{
		m_strength -= rhs.m_strength;
		m_intelligence -= rhs.m_intelligence;
		m_agility -= rhs.m_agility;
		m_physical_defense -= rhs.m_physical_defense;
		m_magic_resistance -= rhs.m_magic_resistance;

		return *this;
	}

	const StatType get_m_strength() const
	{
		return m_strength;
	}

	const StatType get_m_intelligence() const
	{
		return m_intelligence;
	}

	const StatType get_m_agility() const
	{
		return m_agility;
	}

	const StatType get_m_physical_defense() const
	{
		return m_physical_defense;
	}

	const StatType get_m_magic_resistance() const
	{
		return m_magic_resistance;
	}

	void set_m_strength(StatType strength_value)
	{
		m_strength = strength_value;
	}

	void set_m_intelligence(StatType intelligence_value)
	{
		m_intelligence = intelligence_value;
	}

	void set_m_agility(StatType agility_value)
	{
		m_agility = agility_value;
	}

	void set_m_physical_defense(StatType physical_defense_value)
	{
		m_physical_defense = physical_defense_value;
	}

	void set_m_magic_resistance(StatType magic_resistance_value)
	{
		m_magic_resistance = magic_resistance_value;
	}

private:
	StatType m_strength;
	StatType m_intelligence;
	StatType m_agility;
	StatType m_physical_defense;
	StatType m_magic_resistance;
};
