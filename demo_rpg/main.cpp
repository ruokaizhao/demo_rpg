#include "role.h"
#include <iostream>
#include "item_generator.h"

int main()
{
	Role role_1{ std::unique_ptr<Cleric>{new Cleric{}} };

	{
		Item* helmet = ItemGenerator::generate_item("Strong Helmet", ArmorSlot::head, CoreStat{ 0u, 0u, 0u, 5u, 5u });
		Item* chest = ItemGenerator::generate_item( "Strong Chest", ArmorSlot::chest, CoreStat{ 0u, 0u, 0u, 10u, 10u } );
		Item* legs = ItemGenerator::generate_item( "Strong legs", ArmorSlot::legs, CoreStat{ 0u, 0u, 0u, 2u, 2u } );

		role_1.equip_equipment(helmet);
		role_1.equip_equipment(chest);
		role_1.equip_equipment(legs);
	}

	{
		Item* sword = ItemGenerator::generate_item("Sharp Sword", WeaponSlot::melee, CoreStat{ 0u, 0u, 0u, 0u, 0u }, true, 10u, 20u);

		role_1.equip_equipment(sword);
	}

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << role_1.get_class_name() << " Level " << role_1.get_current_level() << '\n'
			<< "-Experience: " << role_1.get_current_experience() << '/' << role_1.get_experience_till_next_level() << '\n'
			<< "-Hit Point: " << role_1.get_current_hit_point() << '/' << role_1.get_max_hit_point() << '\n';

		std::cout << "-Mana Point: " << role_1.get_current_mana_point() << '/' << role_1.get_max_mana_point() << '\n';

		std::cout << "-Strength: " << role_1.get_total_strength() << '\n'
			<< "-Intelligence: " << role_1.get_total_intelligence() << '\n'
			<< "-Agility: " << role_1.get_total_agility() << '\n'
			<< "-Armor: " << role_1.get_total_physical_defense() << '\n'
			<< "-Magic Resistance: " << role_1.get_total_magic_resistance() << '\n';

		std::cout << "-Ability: " << '\n';
		for (const auto& ability : role_1.get_abilities())
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

	role_1.add_buff(Buff{ "Weak", true, 2u, 6u });

	std::cout << "Armors: " << '\n';
	for (const auto& armor : role_1.get_armors())
	{
		if (armor != nullptr)
		{
			std::cout << armor->get_name() << ":" << '\n' << "  Armor: " << armor->get_stat().m_physical_defense << ", " << "Magic Resistance: " << armor->get_stat().m_magic_resistance << '\n';
		}
	}

	std::cout << "Weapons: " << '\n';
	for (const auto& weapon : role_1.get_weapons())
	{
		if (weapon != nullptr)
		{
			Weapon* weapon_ptr = static_cast<Weapon*>(weapon.get());
			std::cout << weapon->get_name() << ":" << '\n' << "  Min Damage: " << weapon_ptr->m_min_damage << ", " << "Max Damage: " << weapon_ptr->m_max_damage << '\n';
		}
	}

	return 0;
}