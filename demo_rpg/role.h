#pragma once
#include "character.h"

class Role
{
public:
	Role(CharacterDelegate* character_delegate_ptr_value) : character_delegate_ptr{ character_delegate_ptr_value } {}

	~Role()
	{
		delete character_delegate_ptr;
	}

	// Getters
	std::string get_class_name() const
	{
		return character_delegate_ptr->get_class_name();
	}

	LevelType get_current_level() const
	{
		return character_delegate_ptr->get_current_level();
	}

	ExperienceType get_current_experience() const
	{
		return character_delegate_ptr->get_current_experience();
	}

	ExperienceType get_experience_till_next_level() const
	{
		return character_delegate_ptr->get_experience_till_next_level();
	}

	PointPoolType get_current_hit_point() const
	{
		return character_delegate_ptr->get_hit_point()->get_current_point();
	}

	PointPoolType get_max_hit_point() const
	{
		return character_delegate_ptr->get_hit_point()->get_max_point();
	}

	PointPoolType get_current_mana_point() const
	{
		if (character_delegate_ptr->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return character_delegate_ptr->get_mana_point()->get_current_point();
	}

	PointPoolType get_max_mana_point() const
	{
		if (character_delegate_ptr->get_mana_point() == nullptr)
		{
			return 0u;
		}

		return character_delegate_ptr->get_mana_point()->get_max_point();
	}

	StatType get_total_strength() const
	{
		StatType total_strength_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_strength_from_armors += armor->get_stat().m_strength;
			}
		}
		return character_delegate_ptr->get_total_strength() + total_strength_from_armors < 0 ? 0 : character_delegate_ptr->get_total_strength() + total_strength_from_armors;
	}

	StatType get_total_intelligence() const
	{
		StatType total_intelligence_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_intelligence_from_armors += armor->get_stat().m_intelligence;
			}
		}
		return character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors < 0 ? 0 : character_delegate_ptr->get_total_intelligence() + total_intelligence_from_armors;
	}

	StatType get_total_agility() const
	{
		StatType total_agility_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_agility_from_armors += armor->get_stat().m_agility;
			}
		}
		return character_delegate_ptr->get_total_agility() + total_agility_from_armors < 0 ? 0 : character_delegate_ptr->get_total_agility() + total_agility_from_armors;
	}

	StatType get_total_physical_defense() const
	{
		StatType total_physical_defense_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_physical_defense_from_armors += armor->get_stat().m_physical_defense;
			}
		}
		return character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors < 0 ? 0 : character_delegate_ptr->get_total_physical_defense() + total_physical_defense_from_armors;
	}

	StatType get_total_magic_resistance() const
	{
		StatType total_magic_resistance_from_armors = 0u;
		for (const auto& armor : armors)
		{
			if (armor != nullptr)
			{
				total_magic_resistance_from_armors += armor->get_stat().m_magic_resistance;
			}
		}
		return character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors < 0 ? 0 : character_delegate_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors;
	}

	const std::vector<Ability>& get_abilities() const
	{
		return character_delegate_ptr->get_abilities();
	}

	const std::array<std::unique_ptr<Equipment<ArmorSlot>>, static_cast<size_t>(ArmorSlot::number_of_slots)>& get_armors() const
	{
		return armors;
	}

	const std::array<std::unique_ptr<Equipment<WeaponSlot>>, static_cast<size_t>(WeaponSlot::number_of_slots)>& get_weapons() const
	{
		return weapons;
	}

	// Modifiers
	void gain_experience(ExperienceType experience_value) const
	{
		character_delegate_ptr->gain_experience(experience_value);
	}

	void add_buff(const Buff& buff)
	{
		character_delegate_ptr->add_buff(buff);
	}

	// Overloaded functions
	bool equip_equipment(std::unique_ptr<Equipment<ArmorSlot>>& equipment)
	{
		if (dynamic_cast<Armor*>(equipment.get()) != nullptr)
		{
			// This is just for comparison, the code in equip_equipment for WEAPON_SLOT is better, the reason being that the 
			// get_slot has been moved to the parent class and we can call get_slot directly on an instance of Equipment,
			// therefore, we no longer need to cast the equipment to Armor. 
			std::unique_ptr<Armor> armor = static_cast<std::unique_ptr<Armor>>(dynamic_cast<Armor*>(equipment.release()));

			// No need to check if the slot is equiped, when assigning a new value to smart pointer, the old value is automatically deleted.
			armors.at(static_cast<size_t>(armor->get_slot())) = std::move(armor);

			return true;
		}

		return false;
	}

	// unique_ptr needs to be passed by reference, because it is not copyable.
	bool equip_equipment(std::unique_ptr<Equipment<WeaponSlot>>& equipment)
	{
		if (dynamic_cast<Weapon*>(equipment.get()) != nullptr)
		{
			weapons.at(static_cast<size_t>(equipment->get_slot())) = std::move(equipment);

			return true;
		}

		return false;
	}

	// Delete constructors
	Role() = delete;
	Role(const Role&) = delete;
	Role(Role&&) = delete;

private:
	CharacterDelegate* character_delegate_ptr;
	// If not initialized, smart pointers are default to nullptr.
	std::array<std::unique_ptr<Equipment<ArmorSlot>>, static_cast<size_t>(ArmorSlot::number_of_slots)> armors;
	std::array<std::unique_ptr<Equipment<WeaponSlot>>, static_cast<size_t>(WeaponSlot::number_of_slots)> weapons;
};
