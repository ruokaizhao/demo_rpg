#include <iostream>
#include "player_character.h"

int main()
{
	PlayerCharacter player_1{ new Cleric{} };

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << player_1.get_class_name() << " Level " << player_1.get_current_level() << '\n'
			<< "-Experience: " << player_1.get_current_experience() << '/' << player_1.get_experience_till_next_level() << '\n'
			<< "-Hit Point: " << player_1.get_current_hit_point() << '/' << player_1.get_max_hit_point() << '\n';

		std::cout << "-Mana Point: " << player_1.get_current_mana_point() << '/' << player_1.get_max_mana_point() << '\n';

		std::cout << "-Strength: " << player_1.get_total_strength() << '\n'
			<< "-Intelligence: " << player_1.get_total_intelligence() << '\n'
			<< "-Agility: " << player_1.get_total_agility() << '\n'
			<< "-Armor: " << player_1.get_total_armor() << '\n'
			<< "-Magic Resistance: " << player_1.get_total_magic_resistance() << '\n';

		for (const auto& ability : player_1.get_abilities())
		{
			std::cout << " Ability: " << '\n'
				<< " -Name: " << ability.m_name << '\n'
				<< " -Cost: " << ability.m_cost << '\n'
				<< " -Cooldown: " << ability.m_cooldown << '\n'
				<< " -Hit Point Effect: " << ability.m_hit_point_effect << '\n'
				<< " -Target: " << static_cast<int>(ability.m_target) << '\n';
		}

		player_1.gain_experience(100u);
	}

	player_1.add_buff(Buff{ "Weak", false, 2u, 6u });

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << player_1.get_class_name() << " Level " << player_1.get_current_level() << '\n'
			<< "-Experience: " << player_1.get_current_experience() << '/' << player_1.get_experience_till_next_level() << '\n'
			<< "-Hit Point: " << player_1.get_current_hit_point() << '/' << player_1.get_max_hit_point() << '\n';

		std::cout << "-Mana Point: " << player_1.get_current_mana_point() << '/' << player_1.get_max_mana_point() << '\n';

		std::cout << "-Strength: " << player_1.get_total_strength() << '\n'
			<< "-Intelligence: " << player_1.get_total_intelligence() << '\n'
			<< "-Agility: " << player_1.get_total_agility() << '\n'
			<< "-Armor: " << player_1.get_total_armor() << '\n'
			<< "-Magic Resistance: " << player_1.get_total_magic_resistance() << '\n';

		for (const auto& ability : player_1.get_abilities())
		{
			std::cout << " Ability: " << '\n'
				<< " -Name: " << ability.m_name << '\n'
				<< " -Cost: " << ability.m_cost << '\n'
				<< " -Cooldown: " << ability.m_cooldown << '\n'
				<< " -Hit Point Effect: " << ability.m_hit_point_effect << '\n'
				<< " -Target: " << static_cast<int>(ability.m_target) << '\n';
		}

		player_1.gain_experience(100u);
	}

}