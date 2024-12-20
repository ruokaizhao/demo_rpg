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

		StatType total_strength_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<WeaponSlot>>(static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()));
				total_strength_from_weapons += equipment->get_stat().m_strength;
				equipment.release();
			}
		}

		StatType total_strength = m_character_ptr->get_base_strength() + total_strength_from_armors + total_strength_from_weapons + m_stat_from_buffs.m_strength;

		return total_strength < 0 ? 0 : total_strength;
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

		StatType total_intelligence_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<WeaponSlot>>(static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()));
				total_intelligence_from_weapons += equipment->get_stat().m_intelligence;
				equipment.release();
			}
		}

		StatType total_intelligence = m_character_ptr->get_base_intelligence() + total_intelligence_from_armors + total_intelligence_from_weapons + m_stat_from_buffs.m_intelligence;

		return total_intelligence < 0 ? 0 : total_intelligence;
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

		StatType total_agility_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<WeaponSlot>>(static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()));
				total_agility_from_weapons += equipment->get_stat().m_agility;
				equipment.release();
			}
		}

		StatType total_agility = m_character_ptr->get_base_agility() + total_agility_from_armors + total_agility_from_weapons + m_stat_from_buffs.m_agility;

		return total_agility < 0 ? 0 : total_agility;
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

		StatType total_physical_defense_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<WeaponSlot>>(static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()));
				total_physical_defense_from_weapons += equipment->get_stat().m_physical_defense;
				equipment.release();
			}
		}

		StatType total_physical_defense = m_character_ptr->get_base_physical_defense() + total_physical_defense_from_armors + total_physical_defense_from_weapons + m_stat_from_buffs.m_physical_defense;

		return total_physical_defense < 0 ? 0 : total_physical_defense;
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

		StatType total_magic_resistance_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::unique_ptr<Equipment<WeaponSlot>>(static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()));
				total_magic_resistance_from_weapons += equipment->get_stat().m_magic_resistance;
				equipment.release();
			}
		}

		StatType total_magic_resistance = m_character_ptr->get_base_magic_resistance() + total_magic_resistance_from_armors + total_magic_resistance_from_weapons + m_stat_from_buffs.m_magic_resistance;

		return total_magic_resistance < 0 ? 0 : total_magic_resistance;
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

	const auto& get_m_buffs() const
	{
		return m_buffs;
	}

	void apply_buff(const Buff& buff_value)
	{
		for (auto& buff : m_buffs)
		{
			if (buff.m_name == buff_value.m_name)
			{
				buff.m_duration = buff_value.m_duration;

				return;
			}
		}

		m_buffs.push_back(buff_value);

		re_calculate_buffs();
	}

	void re_calculate_buffs()
	{
		BaseStat temporary_stat_from_buffs{ 0, 0, 0, 0, 0 };

		for (const auto& buff : m_buffs)
		{
			if (buff.m_is_debuff)
			{
				temporary_stat_from_buffs -= buff.m_stat;
			}
			else
			{
				temporary_stat_from_buffs += buff.m_stat;
			}
		}

		m_stat_from_buffs = temporary_stat_from_buffs;
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
	BaseStat m_stat_from_buffs{};
	std::vector<Buff> m_buffs{};
};
