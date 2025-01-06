#pragma once
#include "macro.h"
#include "ability.h"
#include "game_item.h"
#include "point_pool.h"
#include "base_stat.h"
#include <vector>

class Character
{
	static constexpr LevelType LEVEL_UP_SCALAR = 2u;
	static constexpr ExperienceType EXPERIENCE_TILL_LEVEL_TWO = 100u;

public:
	Character()
		: m_base_stat{ BaseStat{} },
		m_current_level{ 1u },
		m_current_experience{ 0u },
		m_experience_till_next_level{ EXPERIENCE_TILL_LEVEL_TWO },
		m_hit_point{ std::make_unique<PointPool>() },
		m_abilities{} {
	}

	const StatType get_base_strength() const
	{
		return m_base_stat.m_strength;
	}

	const StatType get_base_intelligence() const
	{
		return m_base_stat.m_intelligence;
	}

	const StatType get_base_agility() const
	{
		return m_base_stat.m_agility;
	}

	const StatType get_base_physical_defense() const
	{
		return m_base_stat.m_physical_defense;
	}

	const StatType get_base_magic_resistance() const
	{
		return m_base_stat.m_magic_resistance;
	}

	LevelType get_current_level() const
	{
		return m_current_level;
	}

	std::unique_ptr<PointPool>& get_hit_point()
	{
		return m_hit_point;
	}

	std::unique_ptr<PointPool>& get_mana_point()
	{
		return m_mana_point;
	}

	ExperienceType get_current_experience() const
	{
		return m_current_experience;
	}

	ExperienceType get_experience_till_next_level() const
	{
		return m_experience_till_next_level;
	}

	std::vector<Ability>& get_abilities()
	{
		return m_abilities;
	}

	void gain_experience(ExperienceType experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled())
		{
		}
	}

	virtual ~Character() = default;
	virtual std::string get_class_name() const = 0;
	virtual void level_up() = 0;

protected:
	void increase_stat(StatType strength_value = 0u, StatType intelligence_value = 0u, StatType agility_value = 0u, StatType armor_value = 0u, StatType magic_resistance_value = 0u)
	{
		m_base_stat.m_strength += strength_value;
		m_base_stat.m_intelligence += intelligence_value;
		m_base_stat.m_agility += agility_value;
		m_base_stat.m_physical_defense += armor_value;
		m_base_stat.m_magic_resistance += magic_resistance_value;
	}

	void increase_stat(BaseStat stats_value)
	{
		m_base_stat += stats_value;
	}

private:
	BaseStat m_base_stat;
	std::unique_ptr<PointPool> m_hit_point;
	std::unique_ptr<PointPool> m_mana_point;
	LevelType m_current_level;
	ExperienceType m_current_experience;
	ExperienceType m_experience_till_next_level;
	std::vector<Ability> m_abilities;

	bool check_if_leveled()
	{
		if (m_current_experience >= m_experience_till_next_level)
		{
			m_current_level++;
			m_current_experience -= m_experience_till_next_level;
			level_up();
			m_experience_till_next_level *= LEVEL_UP_SCALAR;

			return true;
		}

		return false;
	}
};
