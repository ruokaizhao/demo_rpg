#include "utils.h"

int main()
{
	std::unique_ptr<Enemy> enemy = nullptr;
	std::unique_ptr<Character> character = nullptr;
	
	std::cout << " Please select your class:\n\n";
	std::cout << " 1: Cleric\n";
	std::cout << " 2: Hunter\n";
	std::cout << " 3: Rogue\n";
	std::cout << " 4: Warrior\n";
	std::cout << " 5: Wizard\n";

	int selection{};
	while (character == nullptr)
	{	
		std::cin >> selection;

		switch (selection)
		{
		case 1:
			character = std::make_unique<Cleric>();
			break;
		case 2:
			character = std::make_unique<Hunter>();
			break;
		case 3:
			character = std::make_unique<Rogue>();
			break;
		case 4:
			character = std::make_unique<Warrior>();
			break;
		case 5:
			character = std::make_unique<Wizard>();
			break;
		default:
			std::cout << " Invalid input.\n";
			break;
		}
	}

	std::string name_input{};
	std::cout << "\nPlease enter your character's name: \n";
	std::cin >> name_input;

	std::unique_ptr<Player> player = std::make_unique<Player>(std::make_unique<Role>(std::move(character)), name_input);

	create_enemy(enemy, player);
	move_player_on_map(player, enemy);
	show_map();

	std::cout << "\nMove with (wasd), (i) to show inventory, and (c) to show character sheet.\n";

	char direction{};
	while (player->is_alive())
	{
		std::cin >> direction;

		switch (direction)
		{
		case 'w':
		case 'W':
			player->set_m_x_position(player->get_m_x_position() - 1);
			break;
		case 's':
		case 'S':
			player->set_m_x_position(player->get_m_x_position() + 1);
			break;
		case 'a':
		case 'A':
			player->set_m_y_position(player->get_m_y_position() - 1);
			break;
		case 'd':
		case 'D':
			player->set_m_y_position(player->get_m_y_position() + 1);
			break;
		case 'i':
		case 'I':
			show_inventory(player, false);
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

	std::cout << "\nMove with (wasd), (i) to show inventory, and (c) to show character sheet.\n";
	}

	return 0;
}