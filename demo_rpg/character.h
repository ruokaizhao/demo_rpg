#pragma once
#include <string>
#include "point_pool.h"
#include "stat.h"
#include <vector>
#include "ability.h"
#include <memory>
#include "types.h"
#include "equipment.h"
#include <array>

#define SET_UP_CHARACTER                \
	get_hit_point()->set_max_point(BASE_HIT_POINT);          \
	get_hit_point()->increase_current_point(BASE_HIT_POINT); \
	increase_stat(BASE_STRENGTH, BASE_INTELLIGENCE, BASE_AGILITY)
#define LEVEL_UP                                                                                                                          \
	get_hit_point()->set_max_point(get_hit_point()->get_max_point() + static_cast<PointPoolType>((BASE_HIT_POINT + 1u) / 2.0f));        \
	get_hit_point()->increase_current_point(static_cast<PointPoolType>((BASE_HIT_POINT + 1u) / 2.0f));                                  \
	if (get_mana_point() != nullptr)                                                                                                      \
	{                                                                                                                                     \
		get_mana_point()->set_max_point(get_mana_point()->get_max_point() + static_cast<PointPoolType>((BASE_MANA_POINT + 1u) / 2.0f)); \
		get_mana_point()->increase_current_point(static_cast<PointPoolType>((BASE_MANA_POINT + 1u) / 2.0f));                            \
	}                                                                                                                                     \
	increase_stat(static_cast<StatType>((BASE_STRENGTH + 1u) / 2.0f),                                                                    \
				   static_cast<StatType>((BASE_INTELLIGENCE + 1u) / 2.0f),                                                               \
				   static_cast<StatType>((BASE_AGILITY + 1u) / 2.0f))


class CharacterDelegate : public Stat
{
	static constexpr LevelType LEVEL_UP_SCALAR = 2u;
	static constexpr ExperienceType EXPERIENCE_TILL_LEVEL_TWO = 100u;

public:
	CharacterDelegate()
		: Stat{ 0u, 0u, 0u },
		m_current_level{ 1u },
		m_current_experience{ 0u },
		m_experience_till_next_level{ EXPERIENCE_TILL_LEVEL_TWO },
		hit_point{ std::make_unique<PointPool>() },
		m_abilities{} {}

	LevelType get_current_level() const
	{
		return m_current_level;
	}

	std::unique_ptr<PointPool>& get_hit_point()
	{
		return hit_point;
	}

	std::unique_ptr<PointPool>& get_mana_point()
	{
		return mana_point;
	}

	ExperienceType get_current_experience() const
	{
		return m_current_experience;
	}

	ExperienceType get_experience_till_next_level() const
	{
		return m_experience_till_next_level;
	}

	std::vector<Ability>& get_abilities()
	{
		return m_abilities;
	}

	void gain_experience(ExperienceType experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled()) {}
	}

	void add_buff(const Buff& buff)
	{
		apply_buff(buff);
	}

	virtual ~CharacterDelegate() = default;
	virtual std::string get_class_name() const = 0;
	virtual void level_up() = 0;

private:
	std::unique_ptr<PointPool> hit_point;
	std::unique_ptr<PointPool> mana_point;
	LevelType m_current_level;
	ExperienceType m_current_experience;
	ExperienceType m_experience_till_next_level;
	std::vector<Ability> m_abilities;

	bool check_if_leveled()
	{
		if (m_current_experience >= m_experience_till_next_level)
		{
			m_current_level++;
			m_current_experience -= m_experience_till_next_level;
			level_up();
			m_experience_till_next_level *= LEVEL_UP_SCALAR;
			return true;
		}
		return false;
	}
};

class Cleric : public CharacterDelegate
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(14u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(10u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(3u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(5u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(1u);

	Cleric() : CharacterDelegate{}
	{
		get_mana_point() = std::make_unique<PointPool>(BASE_MANA_POINT, BASE_MANA_POINT);

		SET_UP_CHARACTER;

		get_abilities().emplace_back("Heal", 2u, 1u, 2u, AbilityTarget::ALLY, AbilityScalar::intelligence);
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
			get_abilities().emplace_back("Smite", 2u, 1u, 2u, AbilityTarget::ENEMY, AbilityScalar::intelligence);
		}
	}
};

class Rogue : public CharacterDelegate
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(12u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(0u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(3u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(3u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(5u);

	Rogue() : CharacterDelegate{}
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

class Warrior : public CharacterDelegate
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(18u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(0u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(6u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(2u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(2u);

	Warrior() : CharacterDelegate{}
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
			get_abilities().emplace_back("Power Attact", 0u, 3u, 4u, AbilityTarget::ENEMY, AbilityScalar::strength);
		}
	}
};

class Wizard : public CharacterDelegate
{
public:
	static constexpr PointPoolType BASE_HIT_POINT = static_cast<PointPoolType>(10u);
	static constexpr PointPoolType BASE_MANA_POINT = static_cast<PointPoolType>(14u);
	static constexpr StatType BASE_STRENGTH = static_cast<StatType>(1u);
	static constexpr StatType BASE_INTELLIGENCE = static_cast<StatType>(8u);
	static constexpr StatType BASE_AGILITY = static_cast<StatType>(2u);

	Wizard() : CharacterDelegate{}
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