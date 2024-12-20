#pragma once
#include "character.h"
#include <array>
#include <algorithm>

class Role
{
	friend class GameItemManager;
public:
	Role(std::unique_ptr<Character> character_ptr_value) : m_character_ptr{ std::move(character_ptr_value) } {}

	~Role() = default;

	const std::unique_ptr<Character>& get_m_character_ptr() const
	{
		return m_character_ptr;
	}

	StatType get_total_strength() const
	{
		StatType total_strength_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<ArmorSlot>>(static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()));
				total_strength_from_armors += equipment->get_stat().m_strength;
				equipment.release();
			}
		}
		return m_character_ptr->get_total_strength() + total_strength_from_armors < 0 ? 0 : m_character_ptr->get_total_strength() + total_strength_from_armors;
	}

	StatType get_total_intelligence() const
	{
		StatType total_intelligence_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<ArmorSlot>>(static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()));
				total_intelligence_from_armors += equipment->get_stat().m_intelligence;
				equipment.release();
			}
		}
		return m_character_ptr->get_total_intelligence() + total_intelligence_from_armors < 0 ? 0 : m_character_ptr->get_total_intelligence() + total_intelligence_from_armors;
	}

	StatType get_total_agility() const
	{
		StatType total_agility_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<ArmorSlot>>(static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()));
				total_agility_from_armors += equipment->get_stat().m_agility;
				equipment.release();
			}
		}
		return m_character_ptr->get_total_agility() + total_agility_from_armors < 0 ? 0 : m_character_ptr->get_total_agility() + total_agility_from_armors;
	}

	StatType get_total_physical_defense() const
	{
		StatType total_physical_defense_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<ArmorSlot>>(static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()));
				total_physical_defense_from_armors += equipment->get_stat().m_physical_defense;
				equipment.release();
			}
		}
		return m_character_ptr->get_total_physical_defense() + total_physical_defense_from_armors < 0 ? 0 : m_character_ptr->get_total_physical_defense() + total_physical_defense_from_armors;
	}

	StatType get_total_magic_resistance() const
	{
		StatType total_magic_resistance_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<ArmorSlot>>(static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()));
				total_magic_resistance_from_armors += equipment->get_stat().m_magic_resistance;
				equipment.release();
			}
		}
		return m_character_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors < 0 ? 0 : m_character_ptr->get_total_magic_resistance() + total_magic_resistance_from_armors;
	}

	auto& get_inventory()
	{
		return m_inventory;
	}

	const auto& get_armors() const
	{
		return m_armors;
	}

	const auto& get_weapons() const
	{
		return m_weapons;
	}

	const auto& get_armor_at(ArmorSlot slot) const
	{
		return m_armors.at(static_cast<size_t>(slot));
	}

	const auto& get_weapon_at(WeaponSlot slot) const
	{
		return m_weapons.at(static_cast<size_t>(slot));
	}

	// Delete constructors
	Role() = delete;
	Role(const Role&) = delete;
	Role(Role&&) = delete;

private:
	// If not initialized, smart pointers are default to nullptr.
	std::unique_ptr<Character> m_character_ptr;
	std::vector<std::unique_ptr<GameItem>> m_inventory;
	std::array<std::unique_ptr<GameItem>, static_cast<size_t>(ArmorSlot::number_of_slots)> m_armors;
	std::array<std::unique_ptr<GameItem>, static_cast<size_t>(WeaponSlot::number_of_slots)> m_weapons;
};
