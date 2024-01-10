#include <iostream>
#include "player_character.h"

int main()
{
	PlayerCharacter player_1{ new Warrior{} };

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << player_1.player_character()->get_class_name() << " Level " << player_1.player_character()->get_current_level() << '\n'
			<< "-Experience: " << player_1.player_character()->get_current_experience() << '/' << player_1.player_character()->get_experience_till_next_level() << '\n'
			<< "-Hit Point: " << player_1.player_character()->get_hit_point()->get_current_point() << '/' << player_1.player_character()->get_hit_point()->get_max_point() << '\n';

		if (player_1.player_character()->get_mana_point() != nullptr)
		{
			std::cout << "-Mana Point: " << player_1.player_character()->get_mana_point()->get_current_point() << '/' << player_1.player_character()->get_mana_point()->get_max_point() << '\n';
		}
		else
		{
			std::cout << "-Mana Point: " << 0u << '/' << 0u << '\n';
		}
		std::cout << "-Strength: " << player_1.player_character()->get_strength() << '\n'
			<< "-Intelligence: " << player_1.player_character()->get_intelligence() << '\n'
			<< "-Agility: " << player_1.player_character()->get_agility() << '\n'
			<< "-Armor: " << player_1.player_character()->get_armor() << '\n'
			<< "-Magic Resistance: " << player_1.player_character()->get_magic_resistance() << '\n';

		for (const auto& ability : player_1.player_character()->get_abilities())
		{
			std::cout << " Ability: " << '\n'
				<< " -Name: " << ability.m_name << '\n'
				<< " -Cost: " << ability.m_cost << '\n'
				<< " -Cooldown: " << ability.m_cooldown << '\n'
				<< " -Hit Point Effect: " << ability.m_hit_point_effect << '\n'
				<< " -Target: " << static_cast<int>(ability.m_target) << '\n';
		}

		player_1.player_character()->gain_experience(100u);
	}
}