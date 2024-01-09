#pragma once
#include <cstdint>
#include <string>
#include "point_pool.h"
#include "stat.h"

#define PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR							  \
		get_hit_point().set_max_point(BASE_HIT_POINT);                              \
		get_hit_point().increase_current_point(BASE_HIT_POINT);                     \
		increase_stats(BASE_STRENGTH, BASE_INTELLECT, BASE_AGILITY)      
#define LEVEL_UP                                                              \
		get_hit_point().set_max_point(                                              \
			get_hit_point().get_max_point() +                                       \
			static_cast<point_pool_type>((BASE_HIT_POINT + 1u) / 2.0f));          \
		get_hit_point().increase_current_point(                                     \
			static_cast<point_pool_type>((BASE_HIT_POINT + 1u) / 2.0f));          \
		increase_stats(static_cast<stat_type>((BASE_STRENGTH + 1u) / 2.0f),   \
					   static_cast<stat_type>((BASE_INTELLECT + 1u) / 2.0f),  \
                       static_cast<stat_type>((BASE_AGILITY + 1u) / 2.0f))   

typedef std::uint16_t level_type;
typedef std::uint64_t experience_type;

class PlayerCharacterDelegate : public Stat
{
	static constexpr level_type LEVEL_UP_SCALAR = 2u;
	static constexpr experience_type EXPERIENCE_TILL_LEVEL_TWO = 100u;

public:
	PlayerCharacterDelegate() : Stat{ 0u, 0u, 0u }, m_current_level{ 1u },
		m_current_experience{ 0u }, m_experience_till_next_level{ EXPERIENCE_TILL_LEVEL_TWO }, hit_point{} {}

	virtual ~PlayerCharacterDelegate() = default;

	PointPool get_hit_point() const { return hit_point; }

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
	virtual void level_up() = 0;
	virtual PointPool get_mana_point() const { return PointPool{}; };

	void gain_experience(experience_type experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled()) {}
	}

private:
	PointPool hit_point;
	level_type m_current_level;
	experience_type m_current_experience;
	experience_type m_experience_till_next_level;

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
	PlayerCharacter(PlayerCharacterDelegate* player_character_delegate)
		: player_character_delegate{ player_character_delegate } {}

	~PlayerCharacter() { delete player_character_delegate; }

	PlayerCharacterDelegate* player_character() const
	{
		return player_character_delegate;
	}

private:
	PlayerCharacterDelegate* player_character_delegate;
};

class Cleric : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT =
		static_cast<point_pool_type>(14u);
	static constexpr point_pool_type BASE_MANA_POINT =
		static_cast<point_pool_type>(10u);
	static constexpr stat_type BASE_STRENGTH =
		static_cast<stat_type>(3u);
	static constexpr stat_type BASE_INTELLECT =
		static_cast<stat_type>(5u);
	static constexpr stat_type BASE_AGILITY =
		static_cast<stat_type>(1u);

	Cleric() : PlayerCharacterDelegate{}, mana_point{ BASE_MANA_POINT , BASE_MANA_POINT }
	{
		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;
	}

	std::string get_class_name() const override
	{
		return std::string{ "Cleric" };
	}

	PointPool get_mana_point() const override { return mana_point; }

private:
	PointPool mana_point;
	void level_up() override
	{
		LEVEL_UP;

		mana_point.set_max_point(
			mana_point.get_max_point() +
			static_cast<point_pool_type>((BASE_MANA_POINT + 1u) / 2.0f));
		mana_point.increase_current_point(
			static_cast<point_pool_type>((BASE_MANA_POINT + 1u) / 2.0f));
	}

};

class Rogue : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT =
		static_cast<point_pool_type>(12u);
	static constexpr stat_type BASE_STRENGTH =
		static_cast<stat_type>(3u);
	static constexpr stat_type BASE_INTELLECT =
		static_cast<stat_type>(3u);
	static constexpr stat_type BASE_AGILITY =
		static_cast<stat_type>(5u);

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
	static constexpr point_pool_type BASE_HIT_POINT =
		static_cast<point_pool_type>(18u);
	static constexpr stat_type BASE_STRENGTH =
		static_cast<stat_type>(5u);
	static constexpr stat_type BASE_INTELLECT =
		static_cast<stat_type>(2u);
	static constexpr stat_type BASE_AGILITY =
		static_cast<stat_type>(2u);

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
	}

};

class Wizard : public PlayerCharacterDelegate
{
public:
	static constexpr point_pool_type BASE_HIT_POINT =
		static_cast<point_pool_type>(10u);
	static constexpr stat_type BASE_STRENGTH =
		static_cast<stat_type>(1u);
	static constexpr stat_type BASE_INTELLECT =
		static_cast<stat_type>(8u);
	static constexpr stat_type BASE_AGILITY =
		static_cast<stat_type>(1u);

	Wizard() : PlayerCharacterDelegate{}
	{
		PLAYER_CHARACTER_DELEGATE_CONSTRUCTOR;
	}

	std::string get_class_name() const override
	{
		return std::string{ "Wizard" };
	}

private:
	void level_up() override
	{
		LEVEL_UP;
	}

};
