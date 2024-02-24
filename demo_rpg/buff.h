#pragma once
#include <string>
#include "types.h"

struct Buff
{
	std::string m_name;
	bool m_is_debuff;
	buff_duration_type m_duration;
	buff_type m_strength;
	buff_type m_intelligence;
	buff_type m_agility;
	buff_type m_armor;
	buff_type m_magic_resistance;

	Buff(std::string name_value = "unnamed",
		bool is_debuff_value = false,
		buff_duration_type duration_value = 2u,
		buff_type strength_value = 0u,
		buff_type intelligence_value = 0u,
		buff_type agility_value = 0u,
		buff_type armor_value = 0u,
		buff_type magic_resistance_value = 0u)
		: m_name{ name_value },
		m_is_debuff{ is_debuff_value },
		m_duration{ duration_value },
		m_strength{ strength_value },
		m_intelligence{ intelligence_value },
		m_agility{ agility_value },
		m_armor{ armor_value },
		m_magic_resistance{ magic_resistance_value } {}
};