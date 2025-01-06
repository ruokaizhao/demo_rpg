#pragma once
#include "point_pool.h"
#include "utils.h"
#include <memory>

class Monster
{
public:
	Monster(std::unique_ptr<PointPool>& hit_point_value, DamageType min_damage_value, DamageType max_damage_value) : m_hit_point{ std::move(hit_point_value) }, m_min_damage{ min_damage_value }, m_max_damage{ max_damage_value } {};

	~Monster() = default;

	std::unique_ptr<PointPool>& get_hit_point()
	{
		return m_hit_point;
	}

	const DamageType get_damage() const
	{
		return Random::random(m_min_damage, m_max_damage);
	}

private:
	std::unique_ptr<PointPool> m_hit_point;
	DamageType m_min_damage;
	DamageType m_max_damage;
};