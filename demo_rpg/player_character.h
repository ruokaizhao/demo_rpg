#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include "point_pool.h"
#include "stat.h"

#define PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR : PlayerCharacterDelegate{} \
	{                                                                     \
		hit_point->set_max_point(BASE_POINT);                             \
		hit_point->increase_current_point(BASE_POINT);                    \
		increase_stats(BASE_STRENGTH, BASE_INTELLECT);                    \
	}
#define LEVEL_UP                                                              \
	void level_up() override                                                  \
	{                                                                         \
		hit_point->set_max_point(                                             \
			hit_point->get_max_point() +                                      \
			static_cast<point_pool_type>((BASE_POINT + 1u) / 2.0f));          \
		hit_point->increase_current_point(                                    \
			static_cast<point_pool_type>((BASE_POINT + 1u) / 2.0f));          \
		increase_stats(static_cast<stat_type>((BASE_STRENGTH + 1u) / 2.0f),   \
					   static_cast<stat_type>((BASE_INTELLECT + 1u) / 2.0f)); \
	}

#define PLAYER_CLASS_DEFINITION(class_name, base_point, base_strength, \
								base_intellect)                        \
	class class_name : public PlayerCharacterDelegate                  \
	{                                                                  \
	public:                                                            \
		static constexpr point_pool_type BASE_POINT =                  \
			static_cast<point_pool_type>(base_point);                  \
		static constexpr stat_type BASE_STRENGTH =                     \
			static_cast<stat_type>(base_strength);                     \
		static constexpr stat_type BASE_INTELLECT =                    \
			static_cast<stat_type>(base_intellect);                    \
                                                                       \
		class_name() PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR             \
                                                                       \
			std::string get_class_name() const override                \
		{                                                              \
			return std::string{#class_name};                           \
		}                                                              \
                                                                       \
	private:                                                           \
		LEVEL_UP                                                       \
	};

typedef std::uint16_t level_type;
typedef std::uint64_t experience_type;

class PlayerCharacterDelegate : public Stat
{
	static constexpr level_type LEVEL_UP_SCALAR = 2u;
	static constexpr experience_type EXPERIENCE_TILL_LEVEL_TWO = 100u;

public:
	std::unique_ptr<PointPool> hit_point;

	PlayerCharacterDelegate() : Stat{0u, 0u}
	{
		m_current_level = 1u;
		m_current_experience = 0u;
		m_experience_till_next_level = EXPERIENCE_TILL_LEVEL_TWO;
		hit_point = std::make_unique<PointPool>();
	}

	virtual ~PlayerCharacterDelegate() = default;

	level_type get_current_level() const { return m_current_level; }

	experience_type get_current_experience() const
	{
		return m_current_experience;
	}

	experience_type get_experience_till_next_level() const
	{
		return m_experience_till_next_level;
	}

	virtual std::string get_class_name() const = 0;

	void gain_experience(experience_type experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled())
		{
		};
	}

private:
	level_type m_current_level;
	experience_type m_current_experience;
	experience_type m_experience_till_next_level;

	virtual void level_up() = 0;

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
	PlayerCharacter() = delete;
	PlayerCharacter(PlayerCharacterDelegate *player_character_delegate)
		: player_character_delegate{player_character_delegate} {}

	~PlayerCharacter() { delete player_character_delegate; }

	PlayerCharacterDelegate *player_character() const
	{
		return player_character_delegate;
	}

private:
	PlayerCharacterDelegate *player_character_delegate;
};

PLAYER_CLASS_DEFINITION(Cleric, 14u, 3u, 5u);
PLAYER_CLASS_DEFINITION(Rogue, 14u, 4u, 4u);
PLAYER_CLASS_DEFINITION(Warrior, 20u, 5u, 2u);
PLAYER_CLASS_DEFINITION(Wizard, 10u, 1u, 8u);