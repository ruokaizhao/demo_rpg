#pragma once
#include "buff.h"
#include <memory>
#include <string>

// Do not want other people to change this value, so it is placed in the cpp file, and since the constructor needs to read s_id_generator, it is placed in the cpp file as well.
// But template implementations need to be written in the header file, not a separate source file, so this has to be moved to the header file.
static IdType s_id_generator = 0u;

class Item
{
public:
	Item(std::string name_value) : m_name{ name_value } {}
	virtual ~Item() = default;

	virtual const std::string& get_name() const = 0;
protected:
	std::string m_name;
};

class Potion final : public Item
{
	friend class GameItemManager;
public:
	~Potion() override = default;

	const std::string& get_name() const override
	{
		return m_name;
	}

	ItemCountType& get_count()
	{
		return m_count;
	}

	PointPoolType get_hit_point() const
	{
		return m_hit_point;
	}

	std::unique_ptr<Buff>& get_buff()
	{
		return m_buff;
	}

	Potion() = delete;
	Potion(const Potion&) = delete;
	Potion(Potion&&) = delete;

private:
	ItemCountType m_count;
	PointPoolType m_hit_point;
	std::unique_ptr<Buff> m_buff;

	Potion(std::string name_value, PointPoolType hit_point_value, ItemCountType count_value, std::unique_ptr<Buff> buff_value) : Item{ name_value }, m_hit_point{ hit_point_value }, m_count{ count_value }, m_buff{ std::move(buff_value) } {}
};

template <typename T>
class Equipment : public Item
{
public:
	Equipment(std::string name_value, T slot_value, BaseStat stat_value) : Item{ name_value }, m_slot{ slot_value }, m_stat{ stat_value }, m_id{ ++s_id_generator } {}

	virtual ~Equipment() = default;

	const T& get_slot() const
	{
		return m_slot;
	}

	const BaseStat& get_stat() const
	{
		return m_stat;
	}

private:
	const IdType m_id;
	// By using template, we can declare m_slot here in the parent class instead of in the child classes
	T m_slot;
	BaseStat m_stat;
};

class Armor final : public Equipment<ArmorSlot>
{
	friend class GameItemManager;
public:
	~Armor() override = default;

	const std::string& get_name() const override
	{
		return m_name;
	}

	Armor() = delete;
	Armor(const Armor&) = delete;
	Armor(Armor&&) = delete;

private:
	Armor(std::string name_value, ArmorSlot slot_value, BaseStat stat_value) : Equipment{ name_value,slot_value, stat_value } {}
};

class Weapon final : public Equipment<WeaponSlot>
{
	friend class GameItemManager;
public:
	~Weapon() override = default;

	DamageType get_min_damage() const
	{
		return m_min_damage;
	}

	DamageType get_max_damage() const
	{
		return m_max_damage;
	}

	bool is_two_handed() const
	{
		return m_is_two_handed;
	}

	const std::string& get_name() const override
	{
		return m_name;
	}

	Weapon() = delete;
	Weapon(const Weapon&) = delete;
	Weapon(Weapon&&) = delete;

private:
	bool m_is_two_handed;
	DamageType m_min_damage;
	DamageType m_max_damage;

	Weapon(std::string name_value, WeaponSlot slot_value, BaseStat stat_value, bool is_two_handed_value, DamageType min_damage_value, DamageType max_damage_value) : Equipment{ name_value,slot_value, stat_value }, m_is_two_handed{ is_two_handed_value }, m_min_damage{ min_damage_value }, m_max_damage{ max_damage_value } {}
};
