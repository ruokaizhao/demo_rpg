#include "utils.h"

int main()
{
	std::unique_ptr<Enemy> enemy = nullptr;
	std::unique_ptr<Character> character = nullptr;
	
	std::cout << " Please select your class:\n";
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
	
	std::unique_ptr<Role> m_role_ptr = std::make_unique<Role>(character);
	std::unique_ptr<Player> player = std::make_unique<Player>(m_role_ptr);

	create_enemy(enemy, player);
	move_player_on_map(player, enemy);
	show_map();

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
		default:
			break;
		}

	move_player_on_map(player, enemy);
	show_map();
	}

	return 0;
}