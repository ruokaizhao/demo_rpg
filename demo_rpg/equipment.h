#pragma once
#include "core_stat.h"
#include <string>
#include <typeinfo>

// Do not want other people to change this value, so it is placed in the cpp file, and since the constructor needs to read s_id_generator, it is placed in the cpp file as well.
// But template implementations need to be written in the header file, not a separate source file, so this has to be move to the header file.
static IdType s_id_generator = 0u;

class ItemDelegate
{
public:
	ItemDelegate(std::string name_value) : m_name{ name_value } {}

	const std::string& get_name() const
	{
		return m_name;
	}

	virtual std::string get_type() const = 0;
	virtual ~ItemDelegate() = default;
private:
	std::string m_name;
};

template <typename T>
class EquipmentDelegate : public ItemDelegate
{
public:
	EquipmentDelegate(std::string name_value, T slot_value, CoreStat stat_value) : ItemDelegate{ name_value }, m_slot{ slot_value }, m_stat{ stat_value }, m_id{ ++s_id_generator } {}

	virtual ~EquipmentDelegate() = default;

	const T& get_slot() const
	{
		return m_slot;
	}

	const CoreStat& get_stat() const
	{
		return m_stat;
	}

private:
	const IdType m_id;
	// By using template, we can declare m_slot here in the parent class instead of in the child classes
	T m_slot;
	CoreStat m_stat;
};

class Armor final : public EquipmentDelegate<ArmorSlot>
{
	friend class ItemGenerator;
public:
	std::string get_type() const override
	{
		return typeid(*this).name();
	}

	Armor() = delete;
	Armor(const Armor&) = delete;
	Armor(Armor&&) = delete;

private:
	Armor(std::string name_value, ArmorSlot slot_value, CoreStat stat_value) : EquipmentDelegate{ name_value,slot_value, stat_value } {}
};

class Weapon final : public EquipmentDelegate<WeaponSlot>
{
	friend class ItemGenerator;
public:
	bool m_is_two_handed;
	DamageType m_min_damage;
	DamageType m_max_damage;

	std::string get_type() const override
	{
		return typeid(*this).name();
	}

	Weapon() = delete;
	Weapon(const Weapon&) = delete;
	Weapon(Weapon&&) = delete;

private:
	Weapon(std::string name_value, WeaponSlot slot_value, CoreStat stat_value, bool is_two_handed_value, DamageType min_damage_value, DamageType max_damage_value) : EquipmentDelegate{ name_value,slot_value, stat_value }, m_is_two_handed{ is_two_handed_value }, m_min_damage{ min_damage_value }, m_max_damage{ max_damage_value } {}
};
