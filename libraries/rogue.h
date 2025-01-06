#pragma once
#include "character.h"

class Rogue : public Character
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(12u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(0u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(3u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(3u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(5u);

	Rogue() : Character{}
	{
		SET_UP_CHARACTER;
	}

	std::string get_class_name() const override
	{
		return std::string{ "Rogue" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;
	}
};