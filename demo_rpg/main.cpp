#include "role.h"
#include <iostream>
#include "item_generator.h"
#include <algorithm>

int main()
{
	Role role_1{ std::unique_ptr<Cleric>{new Cleric{}} };

	
	std::unique_ptr<Item> helmet = ItemGenerator::generate_item("Strong Helmet", ArmorSlot::head, CoreStat{0u, 0u, 0u, 5u, 5u});
	std::unique_ptr<Item> chest = ItemGenerator::generate_item("Strong Chest", ArmorSlot::chest, CoreStat{0u, 0u, 0u, 10u, 10u});
	std::unique_ptr<Item> legs = ItemGenerator::generate_item("Strong legs", ArmorSlot::legs, CoreStat{ 0u, 0u, 0u, 2u, 2u });
	std::unique_ptr<Item> low_level_legs = ItemGenerator::generate_item("Low Level legs", ArmorSlot::legs, CoreStat{0u, 0u, 0u, 1u, 1u});

	role_1.equip_equipment(helmet);
	role_1.equip_equipment(chest);
	role_1.equip_equipment(low_level_legs);
	role_1.equip_equipment(legs);
	

	
	std::unique_ptr<Item> sword = ItemGenerator::generate_item("Sharp Sword", WeaponSlot::melee, CoreStat{0u, 0u, 0u, 0u, 0u}, true, 10u, 20u);

	role_1.equip_equipment(sword);
	

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << role_1.get_class_name() << " Level " << role_1.get_current_level() << '\n'
				  << "-Experience: " << role_1.get_current_experience() << '/' << role_1.get_experience_till_next_level() << '\n'
				  << "-Hit Point: " << role_1.get_hit_point()->get_current_point() << '/' << role_1.get_hit_point()->get_max_point() << '\n';

		std::cout << "-Mana Point: " << (role_1.get_mana_point() != nullptr ? role_1.get_mana_point()->get_current_point() : 0u)
				  << '/' << (role_1.get_mana_point() != nullptr ? role_1.get_mana_point()->get_max_point() : 0u) << '\n';

		std::cout << "-Strength: " << role_1.get_total_strength() << '\n'
				  << "-Intelligence: " << role_1.get_total_intelligence() << '\n'
				  << "-Agility: " << role_1.get_total_agility() << '\n'
				  << "-Armor: " << role_1.get_total_physical_defense() << '\n'
				  << "-Magic Resistance: " << role_1.get_total_magic_resistance() << '\n';

		std::cout << "-Ability: " << '\n';
		for (const auto &ability : role_1.get_abilities())
		{
			std::cout
				<< "  Name: " << ability.m_name << '\n'
				<< "  Cost: " << ability.m_cost << '\n'
				<< "  Cooldown: " << ability.m_cooldown << '\n'
				<< "  Hit Point Effect: " << ability.m_hit_point_effect << '\n'
				<< "  Target: " << static_cast<int>(ability.m_target) << '\n';
		}

		std::cout << '\n';

		role_1.gain_experience(100u);
	}

	role_1.add_buff(Buff{"Weak", true, 2u, 6u});

	std::cout << "Armors: " << '\n';
	for (const auto &item : role_1.get_armors())
	{
		if (item != nullptr)
		{
			Armor *armor = static_cast<Armor *>(item->get_m_item_delegate_ptr().get());
			std::cout << armor->get_name() << ":" << '\n'
					  << "  Armor: " << armor->get_stat().m_physical_defense << ", " << "Magic Resistance: " << armor->get_stat().m_magic_resistance << '\n';
		}
	}

	std::cout << "Weapons: " << '\n';
	for (const auto &item : role_1.get_weapons())
	{
		if (item != nullptr)
		{
			Weapon *weapon_ptr = static_cast<Weapon *>(item->get_m_item_delegate_ptr().get());
			std::cout << weapon_ptr->get_name() << ":" << '\n'
					  << "  Min Damage: " << weapon_ptr->m_min_damage << ", " << "Max Damage: " << weapon_ptr->m_max_damage << '\n';
		}
	}

	std::cout << '\n'
			  << "-Hit Point before taking damage: " << role_1.get_hit_point()->get_current_point() << '/' << role_1.get_hit_point()->get_max_point() << '\n';

	role_1.get_hit_point()->reduce_current_point(10u);

	std::cout << "-Hit Point after taking damage: " << role_1.get_hit_point()->get_current_point() << '/' << role_1.get_hit_point()->get_max_point() << '\n';

	std::unique_ptr<Item> heal_salve = ItemGenerator::generate_item("Heal Salve", 2u, 5u);

	role_1.add_to_inventory(heal_salve);

	role_1.use_item(role_1.get_inventory().at(1));
	role_1.use_item(role_1.get_inventory().at(1));
	role_1.use_item(role_1.get_inventory().at(1));
	role_1.use_item(role_1.get_inventory().at(1));

	std::cout << "-Hit Point after using potion: " << role_1.get_hit_point()->get_current_point() << '/' << role_1.get_hit_point()->get_max_point() << '\n';

	try {
		role_1.use_item(role_1.get_inventory().at(1));
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	
	std::unique_ptr<Item> Cleaver = ItemGenerator::generate_item("Power Cleaver", WeaponSlot::melee, CoreStat{0u, 0u, 0u, 0u, 0u}, true, 15u, 25u);

	role_1.equip_equipment(Cleaver);

	std::cout << "Weapons: " << '\n';
	for (const auto &item : role_1.get_weapons())
	{
		if (item != nullptr)
		{
			Weapon *weapon_ptr = static_cast<Weapon *>(item->get_m_item_delegate_ptr().get());
			std::cout << weapon_ptr->get_name() << ":" << '\n'
					  << "  Min Damage: " << weapon_ptr->m_min_damage << ", " << "Max Damage: " << weapon_ptr->m_max_damage << '\n';
		}
	}

	std::cout << "Inventory: " << "there are " << role_1.get_inventory().size() << " items in the inventory." << '\n';
	for (auto& item : role_1.get_inventory())
	{
		std::cout << *item;
	}

	return 0;
}