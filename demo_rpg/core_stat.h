#pragma once
#include "types.h"

class CoreStat
{
public:
	explicit CoreStat(stat_type strength_value = 0u,
		stat_type intelligence_value = 0u,
		stat_type agility_value = 0u,
		stat_type armor_value = 0u,
		stat_type magic_resistance_value = 0u)
		: m_strength{ strength_value },
		m_intelligence{ intelligence_value },
		m_agility{ agility_value },
		m_armor{ armor_value },
		m_magic_resistance{ magic_resistance_value } {}

	CoreStat& operator+=(const CoreStat& rhs)
	{
		m_strength += rhs.m_strength;
		m_intelligence += rhs.m_intelligence;
		m_agility += rhs.m_agility;
		m_armor += rhs.m_armor;
		m_magic_resistance += rhs.m_magic_resistance;

		return *this;
	}

	CoreStat& operator-=(const CoreStat& rhs)
	{
		m_strength -= rhs.m_strength;
		m_intelligence -= rhs.m_intelligence;
		m_agility -= rhs.m_agility;
		m_armor -= rhs.m_armor;
		m_magic_resistance -= rhs.m_magic_resistance;

		return *this;
	}

	stat_type m_strength;
	stat_type m_intelligence;
	stat_type m_agility;
	stat_type m_armor;
	stat_type m_magic_resistance;
};
