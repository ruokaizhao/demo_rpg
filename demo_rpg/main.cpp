#include <iostream>
#include "role.h"
#include "equipment.h"

int main()
{
	Role player_1{ new Cleric{} };

	std::unique_ptr<Equipment<ArmorSlot>> helmet = std::make_unique<Armor>("Strong Helmet", ArmorSlot::head, CoreStat{ 0u, 0u, 0u, 5u, 5u });
	std::unique_ptr<Equipment<ArmorSlot>> chest = std::make_unique<Armor>("Strong Chest", ArmorSlot::chest, CoreStat{ 0u, 0u, 0u, 10u, 10u });
	std::unique_ptr<Equipment<ArmorSlot>> legs = std::make_unique<Armor>("Strong legs", ArmorSlot::legs, CoreStat{ 0u, 0u, 0u, 2u, 2u });

	player_1.equip_equipment(helmet);
	player_1.equip_equipment(chest);
	player_1.equip_equipment(legs);

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << player_1.get_class_name() << " Level " << player_1.get_current_level() << '\n'
			<< "-Experience: " << player_1.get_current_experience() << '/' << player_1.get_experience_till_next_level() << '\n'
			<< "-Hit Point: " << player_1.get_current_hit_point() << '/' << player_1.get_max_hit_point() << '\n';

		std::cout << "-Mana Point: " << player_1.get_current_mana_point() << '/' << player_1.get_max_mana_point() << '\n';

		std::cout << "-Strength: " << player_1.get_total_strength() << '\n'
			<< "-Intelligence: " << player_1.get_total_intelligence() << '\n'
			<< "-Agility: " << player_1.get_total_agility() << '\n'
			<< "-Armor: " << player_1.get_total_physical_defense() << '\n'
			<< "-Magic Resistance: " << player_1.get_total_magic_resistance() << '\n';

		std::cout << "-Ability: " << '\n';
		for (const auto& ability : player_1.get_abilities())
		{
			std::cout
				<< "  Name: " << ability.m_name << '\n'
				<< "  Cost: " << ability.m_cost << '\n'
				<< "  Cooldown: " << ability.m_cooldown << '\n'
				<< "  Hit Point Effect: " << ability.m_hit_point_effect << '\n'
				<< "  Target: " << static_cast<int>(ability.m_target) << '\n';
		}

		std::cout << '\n';

		player_1.gain_experience(100u);
	}

	player_1.add_buff(Buff{ "Weak", true, 2u, 6u });

	std::cout << "Armors: " << '\n';
	for (const auto& armor : player_1.get_armors())
	{
		std::cout << armor->get_name() << ":" << '\n' << "  Armor: " << armor->get_stat().m_physical_defense << ", " << "Magic Resistance: " << static_cast<int>(armor->get_slot()) << '\n';
	}

	return 0;
}