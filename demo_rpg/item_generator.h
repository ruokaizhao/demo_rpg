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
};
