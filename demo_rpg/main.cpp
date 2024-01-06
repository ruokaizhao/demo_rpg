#include <iostream>
#include "warrior.h"
#include "wizard.h"
#include "cleric.h"
#include "rogue.h"

int main()
{
	Cleric cleric_1;

	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << "Cleric Level " << cleric_1.get_current_level() << "\n"
			<< "-Experience: " << cleric_1.get_current_experience() << "/" << cleric_1.get_experience_till_next_level() << "\n"
			<< "-Max Hit Point: " << cleric_1.get_max_hit_point() << "\n"
			<< "-Strength: " << cleric_1.get_strength() << "\n"
			<< "-Intellect: " << cleric_1.get_intellect() << "\n";

		cleric_1.gain_experience(100u);
	}

	Warrior warrior_1;

	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << "Warrior Level " << warrior_1.get_current_level() << "\n"
			<< "-Experience: " << warrior_1.get_current_experience() << "/" << warrior_1.get_experience_till_next_level() << "\n"
			<< "-Max Hit Point: " << warrior_1.get_max_hit_point() << "\n"
			<< "-Strength: " << warrior_1.get_strength() << "\n"
			<< "-Intellect: " << warrior_1.get_intellect() << "\n";

		warrior_1.gain_experience(100u);
	}

	Wizard wizard_1;

	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << "Wizard Level " << wizard_1.get_current_level() << "\n"
			<< "-Experience: " << wizard_1.get_current_experience() << "/" << wizard_1.get_experience_till_next_level() << "\n"
			<< "-Max Hit Point: " << wizard_1.get_max_hit_point() << "\n"
			<< "-Strength: " << wizard_1.get_strength() << "\n"
			<< "-Intellect: " << wizard_1.get_intellect() << "\n";

		wizard_1.gain_experience(100u);
	}

	Rogue rogue_1;

	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << "Rogue Level " << rogue_1.get_current_level() << "\n"
			<< "-Experience: " << rogue_1.get_current_experience() << "/" << rogue_1.get_experience_till_next_level() << "\n"
			<< "-Max Hit Point: " << rogue_1.get_max_hit_point() << "\n"
			<< "-Strength: " << rogue_1.get_strength() << "\n"
			<< "-Intellect: " << rogue_1.get_intellect() << "\n";

		rogue_1.gain_experience(100u);
	}
}