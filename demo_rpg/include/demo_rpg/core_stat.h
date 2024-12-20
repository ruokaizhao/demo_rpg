#pragma once
#include "types.h"
#include <string>

class CoreStat
{
public:
	explicit CoreStat(StatType strength_value = 0u,
		StatType intelligence_value = 0u,
		StatType agility_value = 0u,
		StatType physical_defense_value = 0u,
		StatType magic_resistance_value = 0u)
		: m_strength{ strength_value },
		m_intelligence{ intelligence_value },
		m_agility{ agility_value },
		m_physical_defense{ physical_defense_value },
		m_magic_resistance{ magic_resistance_value } {}

	CoreStat& operator+=(const CoreStat& rhs)
	{
		m_strength += rhs.m_strength;
		m_intelligence += rhs.m_intelligence;
		m_agility += rhs.m_agility;
		m_physical_defense += rhs.m_physical_defense;
		m_magic_resistance += rhs.m_magic_resistance;

		return *this;
	}

	CoreStat& operator-=(const CoreStat& rhs)
	{
		m_strength -= rhs.m_strength;
		m_intelligence -= rhs.m_intelligence;
		m_agility -= rhs.m_agility;
		m_physical_defense -= rhs.m_physical_defense;
		m_magic_resistance -= rhs.m_magic_resistance;

		return *this;
	}

	StatType m_strength;
	StatType m_intelligence;
	StatType m_agility;
	StatType m_physical_defense;
	StatType m_magic_resistance;
};
