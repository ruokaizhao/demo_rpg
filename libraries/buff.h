#pragma once
#include "base_stat.h"

class Buff
{
public:
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
		m_duration{ duration_value },
		m_stat_ptr{ std::make_unique<BaseStat>() }
	{
		m_stat_ptr->set_m_strength(strength_value);
		m_stat_ptr->set_m_intelligence(intelligence_value);
		m_stat_ptr->set_m_agility(agility_value);
		m_stat_ptr->set_m_physical_defense(physical_defense_value);
		m_stat_ptr->set_m_magic_resistance(magic_resistance_value);
	}

	Buff(std::unique_ptr<BaseStat> core_stat_value_ptr, std::string name_value = "unnamed",
		bool is_debuff_value = false,
		BuffDurationType duration_value = 2u)
		: m_name{ name_value },
		m_is_debuff{ is_debuff_value },
		m_duration{ duration_value }, m_stat_ptr{ std::move(core_stat_value_ptr) } {
	}

	const std::string get_m_name() const
	{
		return m_name;
	}

	const bool get_m_is_debuff() const
	{
		return m_is_debuff;
	}

	const BuffDurationType get_m_duration() const
	{
		return m_duration;
	}

	const std::unique_ptr<BaseStat>& get_m_stat_ptr() const
	{
		return m_stat_ptr;
	}

	void set_m_duration(BuffDurationType duration_value)
	{
		m_duration = duration_value;
	}

private:
	std::string m_name;
	bool m_is_debuff;
	BuffDurationType m_duration;
	std::unique_ptr<BaseStat> m_stat_ptr;
};