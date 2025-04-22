#pragma once
#include <memory>
#include "role.h"

class Player
{
public:
	Player(std::unique_ptr<Role>& role_ptr_value, std::string name_value) : m_role_ptr{ std::move(role_ptr_value) }, m_name{ name_value } {}

	const std::string get_name() const
	{
		return m_name;
	}

	bool is_alive() const
	{
		return m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point() > 0;
	}

	std::string m_name;
	std::unique_ptr<Role> m_role_ptr;
	int m_previous_x_position{ 10 };
	int m_previous_y_position{ 5 };
	int m_x_position{ 10 };
	int m_y_position{ 5 };
};