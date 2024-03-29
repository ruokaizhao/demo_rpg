#pragma once
#include <cstdint>

typedef std::uint16_t ability_type;

typedef std::uint16_t buff_duration_type;

typedef std::uint16_t buff_type;

typedef std::uint16_t level_type;

typedef std::uint64_t experience_type;

typedef std::uint16_t point_pool_type;

typedef std::int16_t stat_type;

typedef std::uint64_t damage_type;

enum class ABILITY_TARGET
{
	SELF, ALLY, ENEMY
};

enum class ABILITY_SCALAR
{
	NONE, STRENGTH, INTELLIGENCE, AGILITY
};

enum class ARMOR_SLOT
{
	HEAD, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUMBER_OF_SLOTS
};

enum class WEAPON_SLOT
{
	MELEE, RANGED, NUMBER_OF_SLOTS
};