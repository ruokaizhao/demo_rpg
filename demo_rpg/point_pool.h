#pragma once
#include "types.h"

class PointPool
{
public:
	PointPool() : m_current_point{ 0u }, m_max_point{ 0u } {};

	PointPool(
		PointPoolType current_point_value,
		PointPoolType max_point_value
	) :
		m_current_point{ current_point_value },
		m_max_point{ max_point_value }
	{
		if (m_current_point > m_max_point)
		{
			m_current_point = m_max_point;
		}
	}

	~PointPool() = default;

	bool set_max_point(PointPoolType max_point_value)
	{
		if (max_point_value < 1)
		{
			return false;
		}

		m_max_point = max_point_value;

		if (m_current_point > m_max_point)
		{
			m_current_point = m_max_point;
		}

		return true;
	}

	void reduce_current_point(PointPoolType value_to_reduce)
	{
		if (value_to_reduce > m_current_point)
		{
			m_current_point = 0;
			return;
		}

		m_current_point -= value_to_reduce;
	}

	void increase_current_point(PointPoolType value_to_increase)
	{
		if (m_current_point + value_to_increase > m_max_point)
		{
			m_current_point = m_max_point;
			return;
		}

		m_current_point += value_to_increase;
	}

	PointPoolType get_max_point() const
	{
		return m_max_point;
	}

	PointPoolType get_current_point() const
	{
		return m_current_point;
	}

private:
	PointPoolType m_current_point;
	PointPoolType m_max_point;
};