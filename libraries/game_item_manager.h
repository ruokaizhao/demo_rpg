#pragma once
#include "game_item.h"

class GameItemManager
{
public:
	// Armor
	static std::unique_ptr<GameItem> generate_item(std::string name_value, ArmorSlot slot_value, BaseStat stat_value)
	{
		std::unique_ptr<GameItem> item_ptr = std::unique_ptr<GameItem>{ new GameItem{ std::shared_ptr<Item>{ new Armor{ name_value, slot_value, stat_value } } } };

		return item_ptr;
	}

	static bool is_item_armor(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Armor*>(item->get_m_item_ptr().get()) != nullptr)
		{
			return true;
		}

		return false;
	}

	static std::shared_ptr<Armor> convert_item_to_armor(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return nullptr;
		}

		if (is_item_armor(item))
		{
			// If you're just trying to convert a shared_ptr<Base> to a shared_ptr<Derived>, and the actual object is of the correct type (Armor), then yes ¡ª dynamic_pointer_cast can work just fine.
			// The base class has at least one virtual function (so RTTI is available).
			// The object is really of the derived type
			// You cannot use dynamic_pointer_cast to point to a subobject, member field, or an alias view (like you can with aliasing).
			// return std::dynamic_pointer_cast<Armor>(item->get_m_item_ptr());
			return std::shared_ptr<Armor>{item->get_m_item_ptr(), static_cast<Armor*>(item->get_m_item_ptr().get())};
		}

		return nullptr;
	}

	// Weapon
	static std::unique_ptr<GameItem> generate_item(std::string name_value, WeaponSlot slot_value, BaseStat stat_value, bool is_two_handed_value, DamageType min_damage_value, DamageType max_damage_value)
	{
		std::unique_ptr<GameItem> item_ptr = std::unique_ptr<GameItem>{ new GameItem{ std::shared_ptr<Item>(new Weapon{name_value, slot_value, stat_value, is_two_handed_value, min_damage_value, max_damage_value}) } };

		return item_ptr;
	}

	static bool is_item_weapon(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Weapon*>(item->get_m_item_ptr().get()) != nullptr)
		{
			return true;
		}

		return false;
	}

	static std::shared_ptr<Weapon> convert_item_to_weapon(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return nullptr;
		}

		if (is_item_weapon(item))
		{
			return std::shared_ptr<Weapon>{item->get_m_item_ptr(), static_cast<Weapon*>(item->get_m_item_ptr().get())};
		}

		return nullptr;
	}

	// Potion
	static std::unique_ptr<GameItem> generate_item(std::string name_value, PointPoolType hit_point_value = 0u, ItemCountType count_value = 1u, std::unique_ptr<Buff> buff_value = nullptr)
	{
		std::unique_ptr<GameItem> item_ptr = std::unique_ptr<GameItem>{ new GameItem{ std::shared_ptr<Item>{ new Potion{name_value, hit_point_value, ((count_value == 0u) ? static_cast<ItemCountType>(1u) : count_value), std::move(buff_value) } } } };

		return item_ptr;
	}

	static bool is_item_potion(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Potion*>(item->get_m_item_ptr().get()) != nullptr)
		{
			return true;
		}

		return false;
	}

	static std::shared_ptr<Potion> convert_item_to_potion(const std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return nullptr;
		}

		if (is_item_potion(item))
		{
			return std::shared_ptr<Potion>{item->get_m_item_ptr(), static_cast<Potion*>(item->get_m_item_ptr().get())};
		}

		return nullptr;
	}

	// unique_ptr needs to be passed by reference, because it is not copyable.
	static bool use_or_equip_item(std::unique_ptr<Role>& role, size_t index)
	{
		std::unique_ptr<GameItem>& item = role->get_inventory().at(index);

		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return false;
		}

		if (is_item_armor(item))
		{
			auto equipment = convert_item_to_armor(item);
			auto slot = static_cast<size_t>(equipment->get_slot());

			if (role->m_armors.at(slot) == nullptr)
			{
				role->m_armors.at(slot) = std::move(item);
			}
			else
			{
				// If we do
				// add_to_inventory(role, role->m_armors.at(static_cast<size_t>(equipment->get_slot())));
				// role->m_armors.at(static_cast<size_t>(equipment->get_slot())) = std::move(item);,
				// we will get an unknown file: error: SEH exception with code 0xc0000005 thrown in the test body. error,
				// spent some time and can't figure out why.
				std::unique_ptr<GameItem> old_item = std::move(role->m_armors.at(slot));
				role->m_armors.at(slot) = std::move(item);
				add_to_inventory(role, old_item);
			}

			cleanup_inventory(role);

			return true;
		}

		if (is_item_weapon(item))
		{
			auto equipment = convert_item_to_weapon(item);
			auto slot = static_cast<size_t>(equipment->get_slot());

			if (role->m_weapons.at(slot) == nullptr)
			{
				role->m_weapons.at(slot) = std::move(item);
			}
			else
			{
				std::unique_ptr<GameItem> old_item = std::move(role->m_weapons.at(slot));
				add_to_inventory(role, old_item);
				role->m_weapons.at(slot) = std::move(item);
			}
			// Objects pointed by equipment and armor are still needed, so we need to prevent them being deleted by the smart pointers by releasing the smart pointers.
			// However, after using shared_ptr instead of unique_ptr, we don't need to release the smart pointers here.
			// equipment.release();

			cleanup_inventory(role);

			return true;
		}

		if (is_item_potion(item))
		{
			auto potion = convert_item_to_potion(item);

			if (potion->get_buff() != nullptr)
			{
				role->apply_buff(*(potion->get_buff()));
			}

			// If the hit point is full and the potion does not have a buff, the potion will not be used.
			if (role->get_m_character_ptr()->get_hit_point()->is_full() && potion->get_buff() == nullptr)
			{
				return false;
			}

			if (!role->get_m_character_ptr()->get_hit_point()->is_full())
			{
				role->get_m_character_ptr()->get_hit_point()->increase_current_point(potion->get_hit_point());
			}

			// Reduce the count of the potion after using it.
			(potion->get_count())--;

			// Destroy the potion if the count is 0
			if (potion->get_count() == 0)
			{
				item->mark_for_deletion();
			}
			cleanup_inventory(role);

			return true;
		}

		return false;
	}

	static bool add_to_inventory(std::unique_ptr<Role>& role, std::unique_ptr<GameItem>& item)
	{
		if (item == nullptr || item->get_m_item_ptr() == nullptr)
		{
			return false;
		}

		role->m_inventory.push_back(std::move(item));

		return true;
	}

	static void cleanup_inventory(std::unique_ptr<Role>& role)
	{
		role->m_inventory.erase(std::remove_if(role->m_inventory.begin(), role->m_inventory.end(), [](const std::unique_ptr<GameItem>& item) -> bool {return item == nullptr || item->is_marked_for_deletion(); }), role->m_inventory.end());
	}
};
