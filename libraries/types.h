#pragma once
#include <cstdint>

typedef std::uint16_t AbilityType;

typedef std::uint16_t BuffDurationType;

typedef std::uint16_t BuffType;

typedef std::uint16_t LevelType;

typedef std::uint64_t ExperienceType;

typedef std::uint64_t PointPoolType;

typedef std::int16_t StatType;

typedef std::uint64_t DamageType;

typedef std::uint16_t IdType;

typedef std::uint16_t ItemCountType;

enum class AbilityTarget
{
	self, ally, enemy
};

enum class AbilityScalar
{
	none, strength, intelligence, agility
};

enum class ArmorSlot
{
	head, chest, legs, boots, gloves, ring1, ring2, neck, number_of_slots
};

enum class WeaponSlot
{
	melee, ranged, number_of_slots
};