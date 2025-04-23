#pragma once
#include "character.h"

class Cleric : public Character
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(14u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(10u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(3u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(5u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(1u);

	Cleric() : Character{}
	{
		get_mana_point() = std::make_unique<PointPool>(BASE_MANA_POINT, BASE_MANA_POINT);

		SET_UP_CHARACTER;

		get_abilities().emplace_back(std::make_unique<Ability>("Heal", 2u, 1u, 2u, AbilityTarget::ally, AbilityScalar::intelligence));
	}

	std::string get_class_name() const override
	{
		return std::string{ "Cleric" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;

		if (get_current_level() == 2)
		{
			get_abilities().emplace_back(std::make_unique<Ability>("Smite", 2u, 1u, 2u, AbilityTarget::enemy, AbilityScalar::intelligence));
		}
	}
};