#pragma once
#include "buff.h"
#include <vector>

class Stat
{
public:
	explicit Stat(StatType strength_value = 1u,
		StatType intelligence_value = 1u,
		StatType agility_value = 1u,
		StatType armor_value = 0u,
		StatType magic_resistance_value = 0u)
	{
		m_base.m_strength = strength_value;
		m_base.m_intelligence = intelligence_value;
		m_base.m_agility = agility_value;
		m_base.m_physical_defense = armor_value;
		m_base.m_magic_resistance = magic_resistance_value;
	};

	StatType get_base_strength() const
	{
		return m_base.m_strength;
	}

	StatType get_base_intelligence() const
	{
		return m_base.m_intelligence;
	}

	StatType get_base_agility() const
	{
		return m_base.m_agility;
	}

	StatType get_base_physical_defense() const
	{
		return m_base.m_physical_defense;
	}

	StatType get_base_magic_resistance() const
	{
		return m_base.m_magic_resistance;
	}

	StatType get_total_strength() const
	{
		return m_base.m_strength + m_stat_from_buffs.m_strength < 0 ? 0 : m_base.m_strength + m_stat_from_buffs.m_strength;
	}

	StatType get_total_intelligence() const
	{
		return m_base.m_intelligence + m_stat_from_buffs.m_intelligence < 0 ? 0 : m_base.m_intelligence + m_stat_from_buffs.m_intelligence;
	}

	StatType get_total_agility() const
	{
		return m_base.m_agility + m_stat_from_buffs.m_agility < 0 ? 0 : m_base.m_agility + m_stat_from_buffs.m_agility;
	}

	StatType get_total_physical_defense() const
	{
		return m_base.m_physical_defense + m_stat_from_buffs.m_physical_defense < 0 ? 0 : m_base.m_physical_defense + m_stat_from_buffs.m_physical_defense;
	}

	StatType get_total_magic_resistance() const
	{
		return m_base.m_magic_resistance + m_stat_from_buffs.m_magic_resistance < 0 ? 0 : m_base.m_magic_resistance + m_stat_from_buffs.m_magic_resistance;
	}

	void apply_buff(const Buff& buff_value)
	{
		for (auto& buff : m_buffs)
		{
			if (buff.m_name == buff_value.m_name)
			{
				buff.m_duration = buff_value.m_duration;

				return;
			}
		}

		m_buffs.push_back(buff_value);

		re_calculate_buffs();
	}

	void increase_stat(StatType strength_value = 0u, StatType intelligence_value = 0u, StatType agility_value = 0u, StatType armor_value = 0u, StatType magic_resistance_value = 0u)
	{
		m_base.m_strength += strength_value;
		m_base.m_intelligence += intelligence_value;
		m_base.m_agility += agility_value;
		m_base.m_physical_defense += armor_value;
		m_base.m_magic_resistance += magic_resistance_value;
	}

	void increase_stat(CoreStat stats_value)
	{
		m_base += stats_value;
	}

public:
	CoreStat m_base{};
	CoreStat m_stat_from_buffs{};
	std::vector<Buff> m_buffs{};

	void re_calculate_buffs()
	{
		CoreStat temporary_stat_from_buffs{ 0, 0, 0, 0, 0 };

		for (const auto& buff : m_buffs)
		{
			if (buff.m_is_debuff)
			{
				temporary_stat_from_buffs -= buff.m_stat;
			}
			else
			{
				temporary_stat_from_buffs += buff.m_stat;
			}
		}

		m_stat_from_buffs = temporary_stat_from_buffs;
	}
};