#include <iostream>
#include "player_character.h"

int main()
{
	PlayerCharacter player_1{new Rogue{}};

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << player_1.player_character()->get_class_name() << " Level " << player_1.player_character()->get_current_level() << '\n'
				  << "-Experience: " << player_1.player_character()->get_current_experience() << '/' << player_1.player_character()->get_experience_till_next_level() << '\n'
				  << "-Hit Point: " << player_1.player_character()->get_hit_point().get_current_point() << '/' << player_1.player_character()->get_hit_point().get_max_point() << '\n'
				  << "-Mana Point: " << player_1.player_character()->get_mana_point().get_current_point() << '/' << player_1.player_character()->get_mana_point().get_max_point() << '\n'
				  << "-Strength: " << player_1.player_character()->get_strength() << '\n'
				  << "-Intellect: " << player_1.player_character()->get_intellect() << '\n'
				  << "-Agility: " << player_1.player_character()->get_agility() << '\n'
				  << "-Armor: " << player_1.player_character()->get_armor() << '\n'
				  << "-Magic Resistance: " << player_1.player_character()->get_magic_resistance() << '\n';

		player_1.player_character()->gain_experience(100u);
	}
}