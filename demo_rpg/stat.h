#pragma once
#include "buff.h"
#include <vector>
#include "types.h"

class Stat
{
public:
	explicit Stat(stat_type strength_value = 1u, stat_type intelligence_value = 1u, stat_type agility_value = 1u, stat_type armor_value = 0u, stat_type magic_resistance_value = 0u) : m_base_strength{ strength_value }, m_base_intelligence{ intelligence_value }, m_base_agility{ agility_value }, m_base_armor{ armor_value }, m_base_magic_resistance{ magic_resistance_value } {};

	stat_type get_base_strength() const
	{
		return m_base_strength;
	}

	stat_type get_base_intelligence() const
	{
		return m_base_intelligence;
	}

	stat_type get_base_agility() const
	{
		return m_base_agility;
	}

	stat_type get_base_armor() const
	{
		return m_base_armor;
	}

	stat_type get_base_magic_resistance() const
	{
		return m_base_magic_resistance;
	}

	stat_type get_total_strength() const
	{
		return m_base_strength + m_strength_from_buff < 0 ? 0 : m_base_strength + m_strength_from_buff;
	}

	stat_type get_total_intelligence() const
	{
		return m_base_intelligence + m_intelligence_from_buff < 0 ? 0 : m_base_intelligence + m_intelligence_from_buff;
	}

	stat_type get_total_agility() const
	{
		return m_base_agility + m_agility_from_buff < 0 ? 0 : m_base_agility + m_agility_from_buff;
	}

	stat_type get_total_armor() const
	{
		return m_base_armor + m_armor_from_buff < 0 ? 0 : m_base_armor + m_armor_from_buff;
	}

	stat_type get_total_magic_resistance() const
	{
		return m_base_magic_resistance + m_magic_resistance_from_buff < 0 ? 0 : m_base_magic_resistance + m_magic_resistance_from_buff;
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

	void increase_stats(stat_type strength_value = 0u, stat_type intelligence_value = 0u, stat_type agility_value = 0u, stat_type armor_value = 0u, stat_type magic_resistance_value = 0u)
	{
		m_base_strength += strength_value;
		m_base_intelligence += intelligence_value;
		m_base_agility += agility_value;
		m_base_armor += armor_value;
		m_base_magic_resistance += magic_resistance_value;
	}

private:
	stat_type m_base_strength;
	stat_type m_base_intelligence;
	stat_type m_base_agility;
	stat_type m_base_armor;
	stat_type m_base_magic_resistance;
	stat_type m_strength_from_buff = 0u;
	stat_type m_intelligence_from_buff = 0u;
	stat_type m_agility_from_buff = 0u;
	stat_type m_armor_from_buff = 0u;
	stat_type m_magic_resistance_from_buff = 0u;
	std::vector<Buff> m_buffs;

	void re_calculate_buffs()
	{
		stat_type temporary_strength_from_buff = 0u;
		stat_type temporary_intelligence_from_buff = 0u;
		stat_type temporary_agility_from_buff = 0u;
		stat_type temporary_armor_from_buff = 0u;
		stat_type temporary_magic_resistance_from_buff = 0u;

		for (const auto& buff : m_buffs)
		{
			if (buff.m_is_debuff)
			{
				temporary_strength_from_buff -= buff.m_strength;
				temporary_intelligence_from_buff -= buff.m_intelligence;
				temporary_agility_from_buff -= buff.m_agility;
				temporary_armor_from_buff -= buff.m_armor;
				temporary_magic_resistance_from_buff -= buff.m_magic_resistance;
			}
			else
			{
				temporary_strength_from_buff += buff.m_strength;
				temporary_intelligence_from_buff += buff.m_intelligence;
				temporary_agility_from_buff += buff.m_agility;
				temporary_armor_from_buff += buff.m_armor;
				temporary_magic_resistance_from_buff += buff.m_magic_resistance;
			}
		}

		m_strength_from_buff = temporary_strength_from_buff;
		m_intelligence_from_buff = temporary_intelligence_from_buff;
		m_agility_from_buff = temporary_agility_from_buff;
		m_armor_from_buff = temporary_armor_from_buff;
		m_magic_resistance_from_buff = temporary_magic_resistance_from_buff;
	}
};