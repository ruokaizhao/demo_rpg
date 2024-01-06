#pragma once
#include <cstdint>

typedef std::uint16_t stat_type;

class Stat {
public:
	Stat() : m_strength{ static_cast<stat_type>(1u) }, m_intellect{ static_cast<stat_type>(1u) } {};
	explicit Stat(stat_type strength_value, stat_type intellect_value) : m_strength{ strength_value }, m_intellect{ intellect_value } {};

	stat_type get_strength() const
	{
		return m_strength;
	}

	stat_type get_intellect() const
	{
		return m_intellect;
	}

protected:
	void increase_stats(stat_type strength_value, stat_type intellect_value)
	{
		m_strength += strength_value;
		m_intellect += intellect_value;
	}

private:
	stat_type m_strength;
	stat_type m_intellect;
};