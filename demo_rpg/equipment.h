#pragma once
#include <string>
#include "core_stat.h"
#include <typeinfo>

template <typename T>
class Equipment
{
public:
	Equipment<T>(std::string name_value, T slot_value, CoreStat stat_value) : m_name{ name_value }, m_slot{slot_value}, m_stat { stat_value } {}

	virtual std::string get_type() const = 0;

	virtual ~Equipment() = default;

	const std::string& get_name() const
	{
		return m_name;
	}

	const T& get_slot() const
	{
		return m_slot;
	}

	const auto& get_stat() const
	{
		return m_stat;
	}

private:
	std::string m_name;
	// By using template, we can declare m_slot here in the parent class instead of in the child classes
	T m_slot;
	CoreStat m_stat;
};

class Armor final : public Equipment<ArmorSlot>
{
public:
	Armor(std::string name_value, ArmorSlot slot_value, CoreStat stat_value ) : Equipment{ name_value,slot_value, stat_value } {}

	std::string get_type() const override
	{
		return typeid(*this).name();
	}

	Armor() = delete;
	Armor(const Armor &) = delete;
	Armor(Armor &&) = delete;
};

class Weapon final : public Equipment<WeaponSlot>
{
public:
	bool m_is_two_handed;
	DamageType m_min_damage;
	DamageType m_max_damage;

	Weapon(std::string name_value, WeaponSlot slot_value, CoreStat stat_value, bool is_two_handed_value, DamageType min_damage_value, DamageType max_damage_value) : Equipment{ name_value,slot_value, stat_value }, m_is_two_handed{ is_two_handed_value }, m_min_damage{ min_damage_value }, m_max_damage{ max_damage_value } {}

	std::string get_type() const override
	{
		return typeid(*this).name();
	}

	Weapon() = delete;
	Weapon(const Weapon&) = delete;
	Weapon(Weapon&&) = delete;
};