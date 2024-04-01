#pragma once
#include "character.h"
#include <array>

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

	PointPoolType get_current_hit_point() const
	{
		return m_character_delegate_ptr->get_hit_point()->get_current_point();
	}

	PointPoolType get_max_hit_point() const
	{
		return m_character_delegate_ptr->get_hit_point()->get_max_point();
	}

	PointPoolType get_current_mana_point() const
	{
		if (m_character_delegate_ptr->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return m_character_delegate_ptr->get_mana_point()->get_current_point();
	}

	PointPoolType get_max_mana_point() const
	{
		if (m_character_delegate_ptr->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return m_character_delegate_ptr->get_mana_point()->get_max_point();
	}

	StatType get_total_strength() const
	{
		StatType total_strength_from_armors = 0u;
		for (const auto& armor : m_armors)
		{
			if (armor != nullptr)
			{
				total_strength_from_armors += armor->get_stat().m_strength;
			}
		}
		return m_character_delegate_ptr->get_total_strength() + total_strength_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_strength() + total_strength_from_armors;
	}

	StatType get_total_intelligence() const
	{
		StatType total_intelligence_from_armors = 0u;
		for (const auto& armor : m_armors)
		{
			if (armor != nullptr)
			{
				total_intelligence_from_armors += armor->get_stat().m_intelligence;
			}
		}
		return m_character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors;
	}

	StatType get_total_agility() const
	{
		StatType total_agility_from_armors = 0u;
		for (const auto& armor : m_armors)
		{
			if (armor != nullptr)
			{
				total_agility_from_armors += armor->get_stat().m_agility;
			}
		}
		return m_character_delegate_ptr->get_total_agility() + total_agility_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_agility() + total_agility_from_armors;
	}

	StatType get_total_physical_defense() const
	{
		StatType total_physical_defense_from_armors = 0u;
		for (const auto& armor : m_armors)
		{
			if (armor != nullptr)
			{
				total_physical_defense_from_armors += armor->get_stat().m_physical_defense;
			}
		}
		return m_character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors;
	}

	StatType get_total_magic_resistance() const
	{
		StatType total_magic_resistance_from_armors = 0u;
		for (const auto& armor : m_armors)
		{
			if (armor != nullptr)
			{
				total_magic_resistance_from_armors += armor->get_stat().m_magic_resistance;
			}
		}
		return m_character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors < 0 ? 0 : m_character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors;
	}

	const std::vector<Ability>& get_abilities() const
	{
		return m_character_delegate_ptr->get_abilities();
	}

	const std::array<std::unique_ptr<EquipmentDelegate<ArmorSlot>>, static_cast<size_t>(ArmorSlot::number_of_slots)>& get_armors() const
	{
		return m_armors;
	}

	const std::array<std::unique_ptr<EquipmentDelegate<WeaponSlot>>, static_cast<size_t>(WeaponSlot::number_of_slots)>& get_weapons() const
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
	bool equip_equipment(Item* item)
	{
		if (item == nullptr || item->get_m_item_delegate_ptr() == nullptr)
		{
			return false;
		}

		if (dynamic_cast<Armor*>(item->get_m_item_delegate_ptr().get()) != nullptr)
		{
			std::unique_ptr<EquipmentDelegate<ArmorSlot>> equipment = static_cast<std::unique_ptr<EquipmentDelegate<ArmorSlot>>>(static_cast<EquipmentDelegate<ArmorSlot>*>(item->get_m_item_delegate_ptr().release()));
			// This is just for comparison, the code in the below if block is better, the reason being that the 
			// get_slot has been moved to the parent class and we can call get_slot directly on an instance of Equipment,
			// therefore, we no longer need to cast the equipment to Armor. 
			std::unique_ptr<Armor> armor = static_cast<std::unique_ptr<Armor>>(dynamic_cast<Armor*>(equipment.release()));

			m_armors.at(static_cast<size_t>(armor->get_slot())) = std::move(armor);

			delete item;

			return true;
		}

		if (dynamic_cast<Weapon*>(item->get_m_item_delegate_ptr().get()) != nullptr)
		{
			std::unique_ptr<EquipmentDelegate<WeaponSlot>> equipment = static_cast<std::unique_ptr<EquipmentDelegate<WeaponSlot>>>(static_cast<EquipmentDelegate<WeaponSlot>*>(item->get_m_item_delegate_ptr().release()));
			// No need to check if the slot is equiped, when assigning a new value to smart pointer, the old value is automatically deleted.
			m_weapons.at(static_cast<size_t>(equipment->get_slot())) = std::move(equipment);

			delete item;

			return true;
		}

		delete item;

		return false;
	}

	// Delete constructors
	Role() = delete;
	Role(const Role&) = delete;
	Role(Role&&) = delete;

private:
	std::unique_ptr<CharacterDelegate> m_character_delegate_ptr;
	// If not initialized, smart pointers are default to nullptr.
	std::array<std::unique_ptr<EquipmentDelegate<ArmorSlot>>, static_cast<size_t>(ArmorSlot::number_of_slots)> m_armors;
	std::array<std::unique_ptr<EquipmentDelegate<WeaponSlot>>, static_cast<size_t>(WeaponSlot::number_of_slots)> m_weapons;
};
