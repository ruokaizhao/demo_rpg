#pragma once
#include "buff.h"
#include <vector>
#include "types.h"
#include "core_stat.h"

class Stat
{
public:
	explicit Stat(stat_type strength_value = 1u,
		stat_type intelligence_value = 1u,
		stat_type agility_value = 1u,
		stat_type armor_value = 0u,
		stat_type magic_resistance_value = 0u)
	{
		m_base.m_strength = strength_value;
		m_base.m_intelligence = intelligence_value;
		m_base.m_agility = agility_value;
		m_base.m_armor = armor_value;
		m_base.m_magic_resistance = magic_resistance_value;
	};

	stat_type get_base_strength() const
	{
		return m_base.m_strength;
	}

	stat_type get_base_intelligence() const
	{
		return m_base.m_intelligence;
	}

	stat_type get_base_agility() const
	{
		return m_base.m_agility;
	}

	stat_type get_base_armor() const
	{
		return m_base.m_armor;
	}

	stat_type get_base_magic_resistance() const
	{
		return m_base.m_magic_resistance;
	}

	stat_type get_total_strength() const
	{
		return m_base.m_strength + m_stat_from_buffs.m_strength < 0 ? 0 : m_base.m_strength + m_stat_from_buffs.m_strength;
	}

	stat_type get_total_intelligence() const
	{
		return m_base.m_intelligence + m_stat_from_buffs.m_intelligence < 0 ? 0 : m_base.m_intelligence + m_stat_from_buffs.m_intelligence;
	}

	stat_type get_total_agility() const
	{
		return m_base.m_agility + m_stat_from_buffs.m_agility < 0 ? 0 : m_base.m_agility + m_stat_from_buffs.m_agility;
	}

	stat_type get_total_armor() const
	{
		return m_base.m_armor + m_stat_from_buffs.m_armor < 0 ? 0 : m_base.m_armor + m_stat_from_buffs.m_armor;
	}

	stat_type get_total_magic_resistance() const
	{
		return m_base.m_magic_resistance + m_stat_from_buffs.m_magic_resistance < 0 ? 0 : m_base.m_magic_resistance + m_stat_from_buffs.m_magic_resistance;
	}

protected:
	void apply_buff(const Buff& buff_value)
	{
		for (auto& buff : m_buffs)
		{
			if (buff.m_name == buff_value.m_name)
			{
				buff.m_duration = buff_value.m_duration;
			}

			return;
		}

		m_buffs.push_back(buff_value);

		re_calculate_buffs();
	}

	void increase_stat(stat_type strength_value = 0u, stat_type intelligence_value = 0u, stat_type agility_value = 0u, stat_type armor_value = 0u, stat_type magic_resistance_value = 0u)
	{
		m_base.m_strength += strength_value;
		m_base.m_intelligence += intelligence_value;
		m_base.m_agility += agility_value;
		m_base.m_armor += armor_value;
		m_base.m_magic_resistance += magic_resistance_value;
	}

	void increase_stat(CoreStat stats_value)
	{
		m_base += stats_value;
	}

private:
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