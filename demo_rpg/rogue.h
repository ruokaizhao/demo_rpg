#pragma once
#include "hit_point.h"
#include "stat.h"
#include "level_system.h"

class Rogue : public HitPoint, public Stat, public LevelSystem
{
public:
	static constexpr hit_point_type BASE_HIT_POINT = static_cast<hit_point_type>(12u);
	static constexpr stat_type BASE_STRENGTH = static_cast<stat_type>(3u);
	static constexpr stat_type BASE_INTELLECT = static_cast<stat_type>(2u);

	static constexpr hit_point_type HIT_POINT_GROWTH = static_cast<hit_point_type>(6u);
	static constexpr stat_type STRENGTH_GROWTH = static_cast<stat_type>(2u);
	static constexpr stat_type INTELLECT_GROWTH = static_cast<stat_type>(1u);

	Rogue() : HitPoint{ BASE_HIT_POINT, BASE_HIT_POINT }, Stat{ BASE_STRENGTH, BASE_INTELLECT }, LevelSystem{} {};

private:
	void level_up() override
	{
		set_max_hit_point(get_max_hit_point() + HIT_POINT_GROWTH);
		increase_stats(STRENGTH_GROWTH, INTELLECT_GROWTH);
	}
};