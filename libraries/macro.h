#pragma once

#define SET_UP_CHARACTER                                     \
	get_hit_point()->set_max_point(BASE_HIT_POINT);          \
	get_hit_point()->increase_current_point(BASE_HIT_POINT); \
	increase_stat(BASE_STRENGTH, BASE_INTELLIGENCE, BASE_AGILITY)
#define LEVEL_UP                                                                                                                        \
	get_hit_point()->set_max_point(get_hit_point()->get_max_point() + static_cast<PointPoolType>((BASE_HIT_POINT + 1u) / 2.0f));        \
	get_hit_point()->increase_current_point(static_cast<PointPoolType>((BASE_HIT_POINT + 1u) / 2.0f));                                  \
	if (get_mana_point() != nullptr)                                                                                                    \
	{                                                                                                                                   \
		get_mana_point()->set_max_point(get_mana_point()->get_max_point() + static_cast<PointPoolType>((BASE_MANA_POINT + 1u) / 2.0f)); \
		get_mana_point()->increase_current_point(static_cast<PointPoolType>((BASE_MANA_POINT + 1u) / 2.0f));                            \
	}                                                                                                                                   \
	increase_stat(static_cast<StatType>((BASE_STRENGTH + 1u) / 2.0f),                                                                   \
				  static_cast<StatType>((BASE_INTELLIGENCE + 1u) / 2.0f),                                                               \
				  static_cast<StatType>((BASE_AGILITY + 1u) / 2.0f))