#pragma once
#include <cstdint>

typedef std::uint16_t stat_type;

class Stat {
public:
	explicit Stat(stat_type strength_value = 1u, stat_type intelligence_value = 1u, stat_type agility_value = 1u, stat_type armor_value = 0u, stat_type magic_resistance_value = 0u) : m_strength{ strength_value }, m_intelligence{ intelligence_value }, m_agility{ agility_value }, m_armor{ armor_value }, m_magic_resistance{ magic_resistance_value } {};

	stat_type get_strength() const
	{
		return m_strength;
	}

	stat_type get_intelligence() const
	{
		return m_intelligence;
	}

	stat_type get_agility() const
	{
		return m_agility;
	}

	stat_type get_armor() const
	{
		return m_armor;
	}

	stat_type get_magic_resistance() const
	{
		return m_magic_resistance;
	}

protected:
	void increase_stats(stat_type strength_value = 0u, stat_type intelligence_value = 0u, stat_type agility_value = 0u, stat_type armor_value = 0u, stat_type magic_resistance_value = 0u)
	{
		m_strength += strength_value;
		m_intelligence += intelligence_value;
		m_agility += agility_value;
		m_armor += armor_value;
		m_magic_resistance += magic_resistance_value;
	}

private:
	stat_type m_strength;
	stat_type m_intelligence;
	stat_type m_agility;
	stat_type m_armor;
	stat_type m_magic_resistance;
};