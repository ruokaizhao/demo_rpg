#pragma once
#include "item.h"

class ItemGenerator
{
public:
	static Item* generate_item(std::string name_value, ArmorSlot slot_value, CoreStat stat_value)
	{
		Item* item_ptr = new Item{ std::unique_ptr<ItemDelegate>(new Armor{name_value, slot_value, stat_value}) };

		return item_ptr;
	}

	static Item* generate_item(std::string name_value, WeaponSlot slot_value, CoreStat stat_value, bool is_two_handed_value, DamageType min_damage_value, DamageType max_damage_value)
	{
		Item* item_ptr = new Item{ std::unique_ptr<ItemDelegate>(new Weapon{name_value, slot_value, stat_value, is_two_handed_value, min_damage_value, max_damage_value}) };

		return item_ptr;
	}

	static Item* generate_item(std::string name_value, PointPoolType hit_point_value = 0u, ItemCountType count_value = 1u, std::unique_ptr<Buff> buff_value = nullptr)
	{
		Item* item_ptr = new Item{ std::unique_ptr<ItemDelegate>(new Potion{name_value, hit_point_value, ((count_value == 0u) ? static_cast<ItemCountType>(1u): count_value), std::move(buff_value)}) };

		return item_ptr;
	}
};
