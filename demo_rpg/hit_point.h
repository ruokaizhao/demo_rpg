#pragma once
#include <cstdint>

typedef std::uint16_t hit_point_type;

class HitPoint
{
public:
	HitPoint() : m_current_hit_point{ 0 }, m_max_hit_point{ 0 } {};

	HitPoint(
		hit_point_type current_hit_point_value,
		hit_point_type max_hit_point_value
	) :
		m_current_hit_point{ current_hit_point_value },
		m_max_hit_point{ max_hit_point_value }
	{
		if (m_current_hit_point > m_max_hit_point)
		{
			m_current_hit_point = m_max_hit_point;
		}
	}

	~HitPoint() = default;

	bool set_max_hit_point(hit_point_type max_hit_point_value)
	{
		if (max_hit_point_value < 1)
		{
			return false;
		}

		m_max_hit_point = max_hit_point_value;

		if (m_current_hit_point > m_max_hit_point)
		{
			m_current_hit_point = m_max_hit_point;
		}

		return true;
	}

	void take_damage(hit_point_type damage_value)
	{
		if (damage_value > m_current_hit_point)
		{
			m_current_hit_point = 0;
			return;
		}

		m_current_hit_point -= damage_value;
	}

	void take_heal(hit_point_type heal_value)
	{
		if (m_current_hit_point + heal_value > m_max_hit_point)
		{
			m_current_hit_point = m_max_hit_point;
			return;
		}

		m_current_hit_point += heal_value;
	}

	hit_point_type get_max_hit_point() const
	{
		return m_max_hit_point;
	}

	hit_point_type get_current_hit_point() const
	{
		return m_current_hit_point;
	}

private:
	hit_point_type m_current_hit_point;
	hit_point_type m_max_hit_point;
};