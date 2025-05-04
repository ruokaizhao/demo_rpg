#pragma once
#include "include_class.h"
#include <array>
#include <algorithm>
#include "utils.h"

class Role
{
	friend class GameItemManager;
public:
	Role(std::unique_ptr<Character>& character_ptr_value) : m_character_ptr{ std::move(character_ptr_value) }, m_stat_from_buffs_ptr{ std::make_unique<BaseStat>() } {}

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
				auto equipment = std::shared_ptr<Equipment<ArmorSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()) };
				total_strength_from_armors += equipment->get_stat_ptr()->get_m_strength();
			}
		}

		StatType total_strength_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<WeaponSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()) };
				total_strength_from_weapons += equipment->get_stat_ptr()->get_m_strength();
			}
		}

		StatType total_strength = m_character_ptr->get_base_strength() + total_strength_from_armors + total_strength_from_weapons + m_stat_from_buffs_ptr->get_m_strength();

		return total_strength < 0 ? 0 : total_strength;
	}

	StatType get_total_intelligence() const
	{
		StatType total_intelligence_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<ArmorSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()) };
				total_intelligence_from_armors += equipment->get_stat_ptr()->get_m_intelligence();
			}
		}

		StatType total_intelligence_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<WeaponSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()) };
				total_intelligence_from_weapons += equipment->get_stat_ptr()->get_m_intelligence();
			}
		}

		StatType total_intelligence = m_character_ptr->get_base_intelligence() + total_intelligence_from_armors + total_intelligence_from_weapons + m_stat_from_buffs_ptr->get_m_intelligence();

		return total_intelligence < 0 ? 0 : total_intelligence;
	}

	StatType get_total_agility() const
	{
		StatType total_agility_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<ArmorSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()) };
				total_agility_from_armors += equipment->get_stat_ptr()->get_m_agility();
			}
		}

		StatType total_agility_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<WeaponSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()) };
				total_agility_from_weapons += equipment->get_stat_ptr()->get_m_agility();
			}
		}

		StatType total_agility = m_character_ptr->get_base_agility() + total_agility_from_armors + total_agility_from_weapons + m_stat_from_buffs_ptr->get_m_agility();

		return total_agility < 0 ? 0 : total_agility;
	}

	StatType get_total_physical_defense() const
	{
		StatType total_physical_defense_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<ArmorSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()) };
				total_physical_defense_from_armors += equipment->get_stat_ptr()->get_m_physical_defense();
			}
		}

		StatType total_physical_defense_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<WeaponSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()) };
				total_physical_defense_from_weapons += equipment->get_stat_ptr()->get_m_physical_defense();
			}
		}

		StatType total_physical_defense = m_character_ptr->get_base_physical_defense() + total_physical_defense_from_armors + total_physical_defense_from_weapons + m_stat_from_buffs_ptr->get_m_physical_defense();

		return total_physical_defense < 0 ? 0 : total_physical_defense;
	}

	StatType get_total_magic_resistance() const
	{
		StatType total_magic_resistance_from_armors = 0u;
		for (const auto& item : m_armors)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<ArmorSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<ArmorSlot>*>(item->get_m_item_ptr().get()) };
				total_magic_resistance_from_armors += equipment->get_stat_ptr()->get_m_magic_resistance();
			}
		}

		StatType total_magic_resistance_from_weapons = 0u;
		for (const auto& item : m_weapons)
		{
			if (item != nullptr)
			{
				auto equipment = std::shared_ptr<Equipment<WeaponSlot>>{ item->get_m_item_ptr(), static_cast<Equipment<WeaponSlot>*>(item->get_m_item_ptr().get()) };
				total_magic_resistance_from_weapons += equipment->get_stat_ptr()->get_m_magic_resistance();
			}
		}

		StatType total_magic_resistance = m_character_ptr->get_base_magic_resistance() + total_magic_resistance_from_armors + total_magic_resistance_from_weapons + m_stat_from_buffs_ptr->get_m_magic_resistance();

		return total_magic_resistance < 0 ? 0 : total_magic_resistance;
	}

	const DamageType get_melee_damage() const
	{
		DamageType total_melee_damage = 0u;


		if (get_weapon_at(WeaponSlot::melee) != nullptr && get_weapon_at(WeaponSlot::melee)->get_m_item_ptr() != nullptr)
		{
			auto equipment = std::shared_ptr<Weapon>{ get_weapon_at(WeaponSlot::melee)->get_m_item_ptr(), static_cast<Weapon*>(get_weapon_at(WeaponSlot::melee)->get_m_item_ptr().get()) };

			total_melee_damage += Random::random(equipment->get_min_damage(), equipment->get_max_damage());
		}

		return total_melee_damage += (get_total_strength() / 2u);
	}

	const DamageType get_ranged_damage() const
	{
		DamageType total_ranged_damage = 0u;

		if (get_weapon_at(WeaponSlot::ranged) != nullptr && get_weapon_at(WeaponSlot::ranged)->get_m_item_ptr() != nullptr)
		{
			auto equipment = std::shared_ptr<Weapon>{ get_weapon_at(WeaponSlot::ranged)->get_m_item_ptr(), static_cast<Weapon*>(get_weapon_at(WeaponSlot::ranged)->get_m_item_ptr().get()) };

			total_ranged_damage += Random::random(equipment->get_min_damage(), equipment->get_max_damage());
		}

		return total_ranged_damage += (get_total_agility() / 2u);
	}

	std::vector<std::unique_ptr<GameItem>>& get_inventory()
	{
		return m_inventory;
	}

	const std::array<std::unique_ptr<GameItem>, static_cast<size_t>(ArmorSlot::number_of_slots)>& get_armors() const
	{
		return m_armors;
	}

	const std::array<std::unique_ptr<GameItem>, static_cast<size_t>(WeaponSlot::number_of_slots)>& get_weapons() const
	{
		return m_weapons;
	}

	const std::unique_ptr<GameItem>& get_armor_at(ArmorSlot slot) const
	{
		return m_armors.at(static_cast<size_t>(slot));
	}

	const std::unique_ptr<GameItem>& get_weapon_at(WeaponSlot slot) const
	{
		return m_weapons.at(static_cast<size_t>(slot));
	}

	const std::vector<std::unique_ptr<Buff>>& get_m_buffs() const
	{
		return m_buffs;
	}

	void apply_buff(std::unique_ptr<Buff> buff_ptr_value)
	{
		for (auto& buff : m_buffs)
		{
			if (buff->get_m_name() == buff_ptr_value->get_m_name())
			{
				buff->set_m_duration(buff_ptr_value->get_m_duration());

				return;
			}
		}

		m_buffs.push_back(std::move(buff_ptr_value));

		re_calculate_buffs();
	}

	void re_calculate_buffs()
	{
		std::unique_ptr<BaseStat> temporary_stat_from_buffs_ptr = std::make_unique<BaseStat>(0, 0, 0, 0, 0);

		for (const auto& buff : m_buffs)
		{
			if (buff->get_m_is_debuff())
			{
				*(temporary_stat_from_buffs_ptr) -= *(buff->get_m_stat_ptr());
			}
			else
			{
				*(temporary_stat_from_buffs_ptr) += *(buff->get_m_stat_ptr());
			}
		}

		m_stat_from_buffs_ptr = std::move(temporary_stat_from_buffs_ptr);
	}

	// Delete constructors
	Role() = delete;
	Role(const Role&) = delete;
	Role(Role&&) = delete;

private:
	// If not initialized, smart pointers are default to nullptr.
	std::unique_ptr<Character> m_character_ptr{};
	std::vector<std::unique_ptr<GameItem>> m_inventory{};
	std::array<std::unique_ptr<GameItem>, static_cast<size_t>(ArmorSlot::number_of_slots)> m_armors{};
	std::array<std::unique_ptr<GameItem>, static_cast<size_t>(WeaponSlot::number_of_slots)> m_weapons{};
	std::unique_ptr<BaseStat> m_stat_from_buffs_ptr{};
	std::vector<std::unique_ptr<Buff>> m_buffs{};
};
