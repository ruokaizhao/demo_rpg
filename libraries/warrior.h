#pragma once
#include "character.h"

class Warrior : public Character
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(18u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(0u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(6u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(2u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(2u);

	Warrior() : Character{}
	{
		SET_UP_CHARACTER;
	}

	std::string get_class_name() const override
	{
		return std::string{ "Warrior" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;

		if (get_current_level() == 2)
		{
			get_abilities().emplace_back("Power Attact", 0u, 3u, 4u, AbilityTarget::enemy, AbilityScalar::strength);
		}
	}
};