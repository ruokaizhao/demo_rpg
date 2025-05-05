#pragma once
#include "character.h"

class Hunter : public Character
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(12u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(0u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(3u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(3u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(5u);

	Hunter() : Character{}
	{
		SET_UP_CHARACTER;
	}

	std::string get_class_name() const override
	{
		return std::string{ "Hunter" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;

		if (get_current_level() == 2)
		{
			get_abilities().emplace_back(std::make_unique<Ability>("Power Shot", 0u, 3u, 4u, AbilityTarget::enemy, AbilityScalar::agility));
		}
	}
};