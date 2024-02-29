#pragma once
#include <cstdint>

typedef std::uint16_t ability_type;

typedef std::uint16_t buff_duration_type;

typedef std::uint16_t buff_type;

typedef std::uint16_t level_type;

typedef std::uint64_t experience_type;

typedef std::uint16_t point_pool_type;

typedef std::int16_t stat_type;

enum class ABILITY_TARGET
{
	SELF,
	ALLY,
	ENEMY
};

enum class ABILITY_SCALAR
{
	NONE, STRENGTH, INTELLIGENCE, AGILITY
};