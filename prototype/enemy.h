#pragma once
#include "monster.h"
#include "types.h"

class Enemy
{
public:
	Enemy(std::unique_ptr<Monster>& monster_ptr_value, int x_position_value, int y_position_value, ExperienceType m_experience_value) : m_monster_ptr{ std::move(monster_ptr_value) }, m_x_position{ x_position_value }, m_y_position{ y_position_value }, m_experience{ m_experience_value } {}

	bool is_alive() const
	{
		return m_monster_ptr->get_hit_point()->get_current_point() > 0;
	}

	const std::unique_ptr<Monster>& get_monster_ptr() const
	{
		return m_monster_ptr;
	}

	const int get_x_position() const
	{
		return m_x_position;
	}

	const int get_y_position() const
	{
		return m_y_position;
	}

	const ExperienceType get_experience() const
	{
		return m_experience;
	}

private:
	std::unique_ptr<Monster> m_monster_ptr;
	int m_x_position{};
	int m_y_position{};
	ExperienceType m_experience{};
};