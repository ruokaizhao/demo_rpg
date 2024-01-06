#pragma once
#include <cstdint>

typedef std::uint16_t level_type;
typedef std::uint64_t experience_type;

class LevelSystem {
public:
	static constexpr level_type LEVEL_UP_SCALAR = 2u;
	static constexpr experience_type EXPERIENCE_TILL_LEVEL_TWO = 100u;

	LevelSystem()
	{
		m_current_level = 1u;
		m_current_experience = 0u;
		m_experience_till_next_level = EXPERIENCE_TILL_LEVEL_TWO;
	}

	level_type get_current_level()
	{
		return m_current_level;
	}

	experience_type get_current_experience()
	{
		return m_current_experience;
	}

	experience_type get_experience_till_next_level()
	{
		return m_experience_till_next_level;
	}

	void gain_experience(experience_type experience_value)
	{
		m_current_experience += experience_value;

		while (check_if_leveled()) {};
	}

protected:

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