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

#define PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR                \
	get_hit_point()->set_max_point(BASE_HIT_POINT);          \
	get_hit_point()->increase_current_point(BASE_HIT_POINT); \
	increase_stat(BASE_STRENGTH, BASE_INTELLIGENCE, BASE_AGILITY)
#define LEVEL_UP                                                                                                                          \
	get_hit_point()->set_max_point(get_hit_point()->get_max_point() + static_cast<point_pool_type>((BASE_HIT_POINT + 1u) / 2.0f));        \
	get_hit_point()->increase_current_point(static_cast<point_pool_type>((BASE_HIT_POINT + 1u) / 2.0f));                                  \
	if (get_mana_point() != nullptr)                                                                                                      \
	{                                                                                                                                     \
		get_mana_point()->set_max_point(get_mana_point()->get_max_point() + static_cast<point_pool_type>((BASE_MANA_POINT + 1u) / 2.0f)); \
		get_mana_point()->increase_current_point(static_cast<point_pool_type>((BASE_MANA_POINT + 1u) / 2.0f));                            \
	}                                                                                                                                     \
	increase_stat(static_cast<stat_type>((BASE_STRENGTH + 1u) / 2.0f),                                                                    \
				   static_cast<stat_type>((BASE_INTELLIGENCE + 1u) / 2.0f),                                                               \
				   static_cast<stat_type>((BASE_AGILITY + 1u) / 2.0f))


class PlayerCharacterDelegate : public Stat
{
	static constexpr level_type LEVEL_UP_SCALAR = 2u;
	static constexpr experience_type EXPERIENCE_TILL_LEVEL_TWO = 100u;

public:
	PlayerCharacterDelegate()
		: Stat{ 0u, 0u, 0u },
		m_current_level{ 1u },
		m_current_experience{ 0u },
		m_experience_till_next_level{ EXPERIENCE_TILL_LEVEL_TWO },
		hit_point{ std::make_unique<PointPool>() },
		m_abilities{} {}

	level_type get_current_level() const
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

	experience_type get_current_experience() const
	{
		return m_current_experience;
	}

	experience_type get_experience_till_next_level() const
	{
		return m_experience_till_next_level;
	}

	std::vector<Ability>& get_abilities()
	{
		return m_abilities;
	}

	void gain_experience(experience_type experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled()) {}
	}

	void add_buff(const Buff& buff)
	{
		apply_buff(buff);
	}

	virtual ~PlayerCharacterDelegate() = default;
	virtual std::string get_class_name() const = 0;
	virtual void level_up() = 0;

private:
	std::unique_ptr<PointPool> hit_point;
	std::unique_ptr<PointPool> mana_point;
	level_type m_current_level;
	experience_type m_current_experience;
	experience_type m_experience_till_next_level;
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

class PlayerCharacter
{
public:
	PlayerCharacter(PlayerCharacterDelegate* player_character_delegate_ptr) : player_character_delegate{ player_character_delegate_ptr } {}

	~PlayerCharacter()
	{
		delete player_character_delegate;
	}

	// Getters
	std::string get_class_name() const
	{
		return player_character_delegate->get_class_name();
	}

	level_type get_current_level() const
	{
		return player_character_delegate->get_current_level();
	}

	experience_type get_current_experience() const
	{
		return player_character_delegate->get_current_experience();
	}

	experience_type get_experience_till_next_level() const
	{
		return player_character_delegate->get_experience_till_next_level();
	}

	point_pool_type get_current_hit_point() const
	{
		return player_character_delegate->get_hit_point()->get_current_point();
	}

	point_pool_type get_max_hit_point() const
	{
		return player_character_delegate->get_hit_point()->get_max_point();
	}

	point_pool_type get_current_mana_point() const
	{
		if (player_character_delegate->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return player_character_delegate->get_mana_point()->get_current_point();
	}

	point_pool_type get_max_mana_point() const
	{
		if (player_character_delegate->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return player_character_delegate->get_mana_point()->get_max_point();
	}

	stat_type get_total_strength() const
	{
		stat_type total_strength_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_strength_from_armors += armor->get_stat().m_strength;
			}
		}
		return player_character_delegate->get_total_strength() + total_strength_from_armors < 0 ? 0 : player_character_delegate->get_total_strength() + total_strength_from_armors;
	}

	stat_type get_total_intelligence() const
	{
		stat_type total_intelligence_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_intelligence_from_armors += armor->get_stat().m_intelligence;
			}
		}
		return player_character_delegate->get_total_intelligence() + total_intelligence_from_armors < 0 ? 0 : player_character_delegate->get_total_intelligence() + total_intelligence_from_armors;
	}

	stat_type get_total_agility() const
	{
		stat_type total_agility_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_agility_from_armors += armor->get_stat().m_agility;
			}
		}
		return player_character_delegate->get_total_agility() + total_agility_from_armors < 0 ? 0 : player_character_delegate->get_total_agility() + total_agility_from_armors;
	}

	stat_type get_total_armor() const
	{
		stat_type total_armor_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_armor_from_armors += armor->get_stat().m_armor;
			}
		}
		return player_character_delegate->get_total_armor() + total_armor_from_armors < 0 ? 0 : player_character_delegate->get_total_armor() + total_armor_from_armors;
	}

	stat_type get_total_magic_resistance() const
	{
		stat_type total_magic_resistance_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_magic_resistance_from_armors += armor->get_stat().m_magic_resistance;
			}
		}
		return player_character_delegate->get_total_magic_resistance() + total_magic_resistance_from_armors < 0 ? 0 : player_character_delegate->get_total_magic_resistance() + total_magic_resistance_from_armors;
	}

	const std::vector<Ability>& get_abilities() const
	{
		return player_character_delegate->get_abilities();
	}

	const std::array<std::unique_ptr<Equipment<ARMOR_SLOT>>, static_cast<size_t>(ARMOR_SLOT::NUMBER_OF_SLOTS)>& get_armors() const
	{
		return armors;
	}

	const std::array<std::unique_ptr<Equipment<WEAPON_SLOT>>, static_cast<size_t>(WEAPON_SLOT::NUMBER_OF_SLOTS)>& get_weapons() const
	{
		return weapons;
	}

	// Modifiers
	void gain_experience(experience_type experience_value) const
	{
		player_character_delegate->gain_experience(experience_value);
	}

	void add_buff(const Buff& buff)
	{
		player_character_delegate->add_buff(buff);
	}

	// Overloaded functions
	bool equip_equipment(std::unique_ptr<Equipment<ARMOR_SLOT>>& equipment)
	{
		if (dynamic_cast<Armor*>(equipment.get()) != nullptr)
		{
			// This is just for comparison, the code in equip_equipment for WEAPON_SLOT is better, the reason being that the 
			// get_slot has been moved to the parent class and we can call get_slot directly on an instance of Equipment,
			// therefore, we no longer need to cast the equipment to Armor. 
			std::unique_ptr<Armor> armor = static_cast<std::unique_ptr<Armor>>(dynamic_cast<Armor*>(equipment.release()));

			// No need to check if the slot is equiped, when assigning a new value to smart pointer, the old value is automatically deleted.
			armors.at(static_cast<size_t>(armor->get_slot())) = std::move(armor);

			return true;
		}

		return false;
	}

	// unique_ptr needs to be passed by reference, because it is not copyable.
	bool equip_equipment(std::unique_ptr<Equipment<WEAPON_SLOT>>& equipment)
	{
		if (dynamic_cast<Weapon*>(equipment.get()) != nullptr)
		{
			weapons.at(static_cast<size_t>(equipment->get_slot())) = std::move(equipment);

			return true;
		}

		return false;
	}

	// Delete constructors
	PlayerCharacter() = delete;
	PlayerCharacter(const PlayerCharacter&) = delete;
	PlayerCharacter(PlayerCharacter&&) = delete;

private:
	PlayerCharacterDelegate* player_character_delegate;
	// If not initialized, smart pointers are default to nullptr.
	std::array<std::unique_ptr<Equipment<ARMOR_SLOT>>, static_cast<size_t>(ARMOR_SLOT::NUMBER_OF_SLOTS)> armors;
	std::array<std::unique_ptr<Equipment<WEAPON_SLOT>>, static_cast<size_t>(WEAPON_SLOT::NUMBER_OF_SLOTS)> weapons;
};

class Cleric : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT = static_cast<point_pool_type>(14u);
	static constexpr point_pool_type BASE_MANA_POINT = static_cast<point_pool_type>(10u);
	static constexpr stat_type BASE_STRENGTH = static_cast<stat_type>(3u);
	static constexpr stat_type BASE_INTELLIGENCE = static_cast<stat_type>(5u);
	static constexpr stat_type BASE_AGILITY = static_cast<stat_type>(1u);

	Cleric() : PlayerCharacterDelegate{}
	{
		get_mana_point() = std::make_unique<PointPool>(BASE_MANA_POINT, BASE_MANA_POINT);

		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;

		get_abilities().emplace_back("Heal", 2u, 1u, 2u, ABILITY_TARGET::ALLY, ABILITY_SCALAR::INTELLIGENCE);
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
			get_abilities().emplace_back("Smite", 2u, 1u, 2u, ABILITY_TARGET::ENEMY, ABILITY_SCALAR::INTELLIGENCE);
		}
	}
};

class Rogue : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT = static_cast<point_pool_type>(12u);
	static constexpr point_pool_type BASE_MANA_POINT = static_cast<point_pool_type>(0u);
	static constexpr stat_type BASE_STRENGTH = static_cast<stat_type>(3u);
	static constexpr stat_type BASE_INTELLIGENCE = static_cast<stat_type>(3u);
	static constexpr stat_type BASE_AGILITY = static_cast<stat_type>(5u);

	Rogue() : PlayerCharacterDelegate{}
	{
		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;
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

class Warrior : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT = static_cast<point_pool_type>(18u);
	static constexpr point_pool_type BASE_MANA_POINT = static_cast<point_pool_type>(0u);
	static constexpr stat_type BASE_STRENGTH = static_cast<stat_type>(6u);
	static constexpr stat_type BASE_INTELLIGENCE = static_cast<stat_type>(2u);
	static constexpr stat_type BASE_AGILITY = static_cast<stat_type>(2u);

	Warrior() : PlayerCharacterDelegate{}
	{
		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;
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
			get_abilities().emplace_back("Power Attact", 0u, 3u, 4u, ABILITY_TARGET::ENEMY, ABILITY_SCALAR::STRENGTH);
		}
	}
};

class Wizard : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT = static_cast<point_pool_type>(10u);
	static constexpr point_pool_type BASE_MANA_POINT = static_cast<point_pool_type>(14u);
	static constexpr stat_type BASE_STRENGTH = static_cast<stat_type>(1u);
	static constexpr stat_type BASE_INTELLIGENCE = static_cast<stat_type>(8u);
	static constexpr stat_type BASE_AGILITY = static_cast<stat_type>(2u);

	Wizard() : PlayerCharacterDelegate{}
	{
		get_mana_point() = std::make_unique<PointPool>(BASE_MANA_POINT, BASE_MANA_POINT);

		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;

		get_abilities().emplace_back("Fireball", 2u, 1u, 4u, ABILITY_TARGET::ENEMY, ABILITY_SCALAR::INTELLIGENCE);
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
			get_abilities().emplace_back("Icebolt", 3u, 1u, 6u, ABILITY_TARGET::ENEMY, ABILITY_SCALAR::INTELLIGENCE);
		}
	}
};
