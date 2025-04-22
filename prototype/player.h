#pragma once
#include <memory>
#include "role.h"

class Player
{
public:
	Player(std::unique_ptr<Role>& role_ptr_value) : m_role_ptr{ std::move(role_ptr_value) } {}

	bool is_alive() const
	{
		return m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point() > 0;
	}

	std::unique_ptr<Role> m_role_ptr;
	int m_previous_x_position{10};
	int m_previous_y_position{5};
	int m_x_position{10};
	int m_y_position{5};
};