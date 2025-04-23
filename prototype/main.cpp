#include "utils.h"

int main()
{
	std::unique_ptr<Enemy> enemy = nullptr;
	std::unique_ptr<Character> character = nullptr;
	
	std::cout << " Please select your class:\n\n";
	std::cout << " A: Warrior\n";
	std::cout << " B: Rogue\n";
	std::cout << " C: Wizard\n";
	std::cout << " D: Cleric\n";

	char selection{};
	while (character == nullptr)
	{	
		std::cin >> selection;

		switch (selection)
		{
		case 'a':
		case 'A':
			character = std::make_unique<Warrior>();
			break;
		case 'b':
		case 'B':
			character = std::make_unique<Rogue>();
			break;
		case 'c':
		case 'C':
			character = std::make_unique<Wizard>();
			break;
		case 'd':
		case 'D':
			character = std::make_unique<Cleric>();
			break;
		default:
			std::cout << " Invalid input.\n";
			break;
		}
	}

	std::string name_input{};
	std::cout << "Please enter your character's name: \n";
	std::cin >> name_input;

	
	std::unique_ptr<Role> m_role_ptr = std::make_unique<Role>(character);
	std::unique_ptr<Player> player = std::make_unique<Player>(m_role_ptr, name_input);

	create_enemy(enemy, player);
	move_player_on_map(player, enemy);
	show_map();

	std::cout << "\nMove with (wasd), (i) to see inventory, and (c) to see character sheet.\n";

	char direction{};
	while (player->is_alive())
	{
		std::cin >> direction;

		switch (direction)
		{
		case 'w':
		case 'W':
			player->m_x_position--;
			break;
		case 's':
		case 'S':
			player->m_x_position++;
			break;
		case 'a':
		case 'A':
			player->m_y_position--;
			break;
		case 'd':
		case 'D':
			player->m_y_position++;
			break;
		case 'i':
		case 'I':
			show_inventory(player);
			break;
		case 'c':
		case 'C':
			show_character_sheet(player);
			break;
		default:
			break;
		}

	move_player_on_map(player, enemy);
	show_map();

	std::cout << "\nMove with (wasd), (i) to see inventory, and (c) to see character sheet.\n";
	}

	return 0;
}