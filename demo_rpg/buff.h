#pragma once
#include "core_stat.h"

struct Buff
{
	std::string m_name;
	bool m_is_debuff;
	BuffDurationType m_duration;
	CoreStat m_stat;

	Buff(std::string name_value = "unnamed",
		bool is_debuff_value = false,
		BuffDurationType duration_value = 2u,
		BuffType strength_value = 0u,
		BuffType intelligence_value = 0u,
		BuffType agility_value = 0u,
		BuffType physical_defense_value = 0u,
		BuffType magic_resistance_value = 0u)
		: m_name{ name_value },
		m_is_debuff{ is_debuff_value },
		m_duration{ duration_value }
	{
		m_stat.m_strength = strength_value;
		m_stat.m_intelligence = intelligence_value;
		m_stat.m_agility = agility_value;
		m_stat.m_physical_defense = physical_defense_value;
		m_stat.m_magic_resistance = magic_resistance_value;
	}

	Buff(std::string name_value = "unnamed",
		bool is_debuff_value = false,
		BuffDurationType duration_value = 2u,
		CoreStat core_stat_value = CoreStat{})
		: m_name{ name_value },
		m_is_debuff{ is_debuff_value },
		m_duration{ duration_value }
	{
		m_stat = core_stat_value;
	}
};