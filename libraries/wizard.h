#pragma once
#include "character.h"

class Wizard : public Character
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(10u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(14u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(1u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(8u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(2u);

	Wizard() : Character{}
	{
		get_mana_point() = std::make_unique<PointPool>(BASE_MANA_POINT, BASE_MANA_POINT);

		SET_UP_CHARACTER;

		get_abilities().emplace_back("Fireball", 2u, 1u, 4u, AbilityTarget::ENEMY, AbilityScalar::intelligence);
	}

	std::string get_class_name() const override
	{
		return std::string{ "Wizard" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;

		if (get_current_level() == 2)
		{
			get_abilities().emplace_back("Icebolt", 3u, 1u, 6u, AbilityTarget::ENEMY, AbilityScalar::intelligence);
		}
	}
};