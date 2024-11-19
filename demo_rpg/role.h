#pragma once
#include "character.h"
#include <array>
#include <algorithm>

class Role
{
public:
	Role(std::unique_ptr<CharacterDelegate> character_delegate_ptr_value) : m_character_delegate_ptr{ std::move(character_delegate_ptr_value) } {}

	~Role() = default;

	// Getters
	std::string get_class_name() const
	{
		return m_character_delegate_ptr->get_class_name();
	}

	LevelType get_current_level() const
	{
		return m_character_delegate_ptr->get_current_level();
	}

	ExperienceType get_current_experience() const
	{
		return m_character_delegate_ptr->get_current_experience();
	}

	ExperienceType get_experience_till_next_level() const
	{
		return m_character_delegate_ptr->get_experience_till_next_level();
	}

	std::unique_ptr<PointPool>& get_hit_point()
	{
		return m_character_delegate_ptr->get_hit_point();
	}

	std::unique_ptr<PointPool>& get_mana_point()
	{
		return m_character_delegate_ptr->get_mana_point();
	}

	StatType get_total_strength() const
	{
		StatType total_strength_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = std::unique_ptr<EquipmentDelegate<ArmorSlot>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().get()));
				total_strength_from_armors += equipment->get_stat().m_strength;
				equipment.release();
			}
		}
		return m_character_delegate_ptr->get_total_strength() + total_strength_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_strength() + total_strength_from_armors;
	}

	StatType get_total_intelligence() const
	{
		StatType total_intelligence_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = std::unique_ptr<EquipmentDelegate<ArmorSlot>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().get()));
				total_intelligence_from_armors += equipment->get_stat().m_intelligence;
				equipment.release();
			}
		}
		return m_character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors;
	}

	StatType get_total_agility() const
	{
		StatType total_agility_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = std::unique_ptr<EquipmentDelegate<ArmorSlot>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().get()));
				total_agility_from_armors += equipment->get_stat().m_agility;
				equipment.release();
			}
		}
		return m_character_delegate_ptr->get_total_agility() + total_agility_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_agility() + total_agility_from_armors;
	}

	StatType get_total_physical_defense() const
	{
		StatType total_physical_defense_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = std::unique_ptr<EquipmentDelegate<ArmorSlot>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().get()));
				total_physical_defense_from_armors += equipment->get_stat().m_physical_defense;
				equipment.release();
			}
		}
		return m_character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors;
	}

	StatType get_total_magic_resistance() const
	{
		StatType total_magic_resistance_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = std::unique_ptr<EquipmentDelegate<ArmorSlot>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().get()));
				total_magic_resistance_from_armors += equipment->get_stat().m_magic_resistance;
				equipment.release();
			}
		}
		return m_character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors;
	}

	std::vector<Ability>& get_abilities()
	{
		return m_character_delegate_ptr->get_abilities();
	}

	std::vector<std::unique_ptr<Item>>& get_inventory()
	{
		return m_inventory;
	}

	const std::array<std::unique_ptr<Item>, static_cast<size_t>(ArmorSlot::number_of_slots)>& get_armors() const
	{
		return m_armors;
	}

	const std::array<std::unique_ptr<Item>, static_cast<size_t>(WeaponSlot::number_of_slots)>& get_weapons() const
	{
		return m_weapons;
	}

	// Modifiers
	void gain_experience(ExperienceType experience_value) const
	{
		m_character_delegate_ptr->gain_experience(experience_value);
	}

	void add_buff(const Buff& buff)
	{
		m_character_delegate_ptr->add_buff(buff);
	}

	// unique_ptr needs to be passed by reference, because it is not copyable.
	bool equip_equipment(std::unique_ptr<Item>& item)
	{
		if (item == nullptr || item->get_m_item_delegate_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Armor*>(item->get_m_item_delegate_ptr().get()) != nullptr)
		{
			auto equipment = std::unique_ptr<Armor>(static_cast<Armor*>(item->get_m_item_delegate_ptr().get()));

			if (m_armors.at(static_cast<size_t>(equipment->get_slot())) == nullptr)
			{
				m_armors.at(static_cast<size_t>(equipment->get_slot())) = std::move(item);
			}
			else
			{
				add_to_inventory(m_armors.at(static_cast<size_t>(equipment->get_slot())));
				m_armors.at(static_cast<size_t>(equipment->get_slot())) = std::move(item);
			}
			// Objects pointed by equipment and armor are still needed, so we need to prevent them being deleted by the smart pointers by releasing the smart pointers.
			equipment.release();

			return true;
		}

		if (dynamic_cast<Weapon*>(item->get_m_item_delegate_ptr().get()) != nullptr)
		{
			auto equipment = std::unique_ptr<Weapon>(static_cast<Weapon*>(item->get_m_item_delegate_ptr().get()));

			if (m_weapons.at(static_cast<size_t>(equipment->get_slot())) == nullptr)
			{
				m_weapons.at(static_cast<size_t>(equipment->get_slot())) = std::move(item);
			}
			else
			{
				add_to_inventory(m_weapons.at(static_cast<size_t>(equipment->get_slot())));
				m_weapons.at(static_cast<size_t>(equipment->get_slot())) = std::move(item);
			}
			equipment.release();

			return true;
		}

		return false;
	}

	bool use_item(const std::unique_ptr<Item>& item)
	{
		if (item == nullptr || item->get_m_item_delegate_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Potion*>(item->get_m_item_delegate_ptr().get()))
		{
			auto potion = std::unique_ptr<Potion>(static_cast<Potion*>(item->get_m_item_delegate_ptr().get()));

			if (potion->get_buff() != nullptr)
			{
				add_buff(*(potion->get_buff()));
			}

			// If the hit point is full and the potion does not have a buff, the potion will not be used.
			if (get_hit_point()->is_full() && potion->get_buff() == nullptr)
			{
				potion.release();
				return false;
			}

			if (!get_hit_point()->is_full())
			{
				get_hit_point()->increase_current_point(potion->get_hit_point());
			}

			// Reduce the count of the potion after using it.
			(potion->get_count())--;

			// Destroy the potion if the count is 0
			if (potion->get_count() == 0)
			{
				item->mark_for_deletion();
				cleanup_inventory();
			}

			potion.release();

			return true;
		}

		return false;
	}

	void cleanup_inventory()
	{
		m_inventory.erase(std::remove_if(m_inventory.begin(), m_inventory.end(), [](const std::unique_ptr<Item>& item) {return item->is_marked_for_deletion(); }), m_inventory.end());
	}

	bool add_to_inventory(std::unique_ptr<Item>& item)
	{
		if (item == nullptr || item->get_m_item_delegate_ptr() == nullptr)
		{
			return false;
		}

		get_inventory().push_back(std::move(item));

		return true;
	}

	// Delete constructors
	Role() = delete;
	Role(const Role&) = delete;
	Role(Role&&) = delete;

private:
	// If not initialized, smart pointers are default to nullptr.
	std::unique_ptr<CharacterDelegate> m_character_delegate_ptr;
	std::vector<std::unique_ptr<Item>> m_inventory;
	std::array<std::unique_ptr<Item>, static_cast<size_t>(ArmorSlot::number_of_slots)> m_armors;
	std::array<std::unique_ptr<Item>, static_cast<size_t>(WeaponSlot::number_of_slots)> m_weapons;
};
