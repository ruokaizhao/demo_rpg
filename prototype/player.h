#pragma once
#include <memory>
#include "role.h"

class Player
{
public:
	Player(std::unique_ptr<Role> role_ptr_value, std::string name_value) : m_role_ptr{ std::move(role_ptr_value) }, m_name{ name_value } {}

	const std::string get_m_name() const
	{
		return m_name;
	}

	bool is_alive() const
	{
		return m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point() > 0;
	}

	std::unique_ptr<Role>& get_m_role_ptr()
	{
		return m_role_ptr;
	}

	const int get_m_x_position() const
	{
		return m_x_position;
	}

	const int get_m_y_position() const
	{
		return m_y_position;
	}

	const int get_m_previous_x_position() const
	{
		return m_previous_x_position;
	}

	const int get_m_previous_y_position() const
	{
		return m_previous_y_position;
	}

	void set_m_x_position(int x_position_value)
	{
		m_x_position = x_position_value;
	}

	void set_m_y_position(int y_position_value)
	{
		m_y_position = y_position_value;
	}

	void set_m_previous_x_position(int x_position_value)
	{
		m_previous_x_position = x_position_value;
	}

	void set_m_previous_y_position(int y_position_value)
	{
		m_previous_y_position = y_position_value;
	}

private:
	std::string m_name;
	std::unique_ptr<Role> m_role_ptr;
	int m_previous_x_position{ 10 };
	int m_previous_y_position{ 5 };
	int m_x_position{ 10 };
	int m_y_position{ 5 };
};