#include <iostream>
#include <iomanip>
#include "player.h"
#include "enemy.h"
#include "world_map.h"
#include "warrior.h"

static void show_map()
{
	system("cls");

	for (const auto& row : world_map)
	{
		for (const auto& cell : row)
		{
			std::cout << cell;
		}
		std::cout << '\n';
	}
}

static void create_enemy(std::unique_ptr<Enemy>& enemy, const std::unique_ptr<Player>& player)
{
	if (!enemy)
	{
		enemy.release();
	}

	PointPoolType min_hit_point = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	PointPoolType max_hit_point = static_cast<PointPoolType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 2;

	std::unique_ptr<PointPool> monster_point_pool_ptr = std::make_unique<PointPool>(Random::random(min_hit_point, max_hit_point), Random::random(min_hit_point, max_hit_point));

	DamageType min_damage = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	DamageType max_damage = static_cast<DamageType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 2;

	std::unique_ptr<Monster> monster_ptr = std::make_unique<Monster>(monster_point_pool_ptr, min_damage, max_damage);

	ExperienceType experience = static_cast<ExperienceType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 50;


	int m_x_position = Random::random(1, 11);
	int m_y_position = Random::random(1, 11);

	while (world_map.at(m_x_position).at(m_y_position) == 'x' || (world_map.at(m_x_position).at(m_y_position) == 'P'))
	{
		m_x_position = Random::random(1, 11);
		m_y_position = Random::random(1, 11);
	}

	enemy = std::make_unique<Enemy>(monster_ptr, m_x_position, m_y_position, experience);

	world_map.at(m_x_position).at(m_y_position) = 'E';
}

static void enter_battle(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	while (player->is_alive() && enemy->is_alive())
	{
		system("cls");

		std::cout << std::setw(10) << std::left << "" << "Player vs. Enemy" << '\n'
			<< "Player: " 
			<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point() 
			<< "/" 
			<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_max_point()
			<< std::setw(10) << std::left << "" 
			<< "Enemy: " 
			<< enemy->m_monster_ptr->get_hit_point()->get_current_point() 
			<< "/" 
			<< enemy->m_monster_ptr->get_hit_point()->get_max_point()
			<< '\n';

		std::cout << '\n' << "Please make a selection: \n"
			<< "a. Attack\n"
			<< '\n';

		char input{};
		std::cin >> input;

		while (input != 'a')
		{
			std::cout << "Invalid selection! Please try again: ";
			std::cin >> input;
		}

		enemy->m_monster_ptr->get_hit_point()->reduce_current_point(player->m_role_ptr->get_melee_damage());

		if (enemy->is_alive())
		{
			player->m_role_ptr->get_m_character_ptr()->get_hit_point()->reduce_current_point(enemy->m_monster_ptr->get_damage());
		}
		else
		{
			break;
		}
	}

	if (!player->is_alive())
	{
		std::cout << "You have died!" << '\n';
	}
	else if (!enemy->is_alive())
	{
		player->m_role_ptr->get_m_character_ptr()->gain_experience(enemy->m_experience);
		std::cout << "You have defeated the enemy!" << '\n';
		std::cout << "You have gained " << enemy->m_experience << " experiences!" << '\n';
		std::cout << "Press any key to continue..." << '\n';
	}

	create_enemy(enemy, player);

	char input{};
	std::cin >> input;
}

static void move_player_on_map(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	if (world_map.at(player->m_x_position).at(player->m_y_position) == 'E')
	{
		enter_battle(player, enemy);
	}

	if (world_map.at(player->m_x_position).at(player->m_y_position) != 'x')
	{
		world_map.at(player->m_x_position).at(player->m_y_position) = 'P';
		world_map.at(player->m_previous_x_position).at(player->m_previous_y_position) = ' ';

		player->m_previous_x_position = player->m_x_position;
		player->m_previous_y_position = player->m_y_position;
	}
	else
	{
		player->m_x_position = player->m_previous_x_position;
		player->m_y_position = player->m_previous_y_position;
	}
}


int main()
{
	std::unique_ptr<Enemy> enemy = nullptr;

	std::unique_ptr<Character> warrior_character = std::make_unique<Warrior>();
	std::unique_ptr<Role> m_role_ptr = std::make_unique<Role>(warrior_character);
	std::unique_ptr<Player> player = std::make_unique<Player>(m_role_ptr);

	create_enemy(enemy, player);
	move_player_on_map(player, enemy);

	show_map();

	char direction{};
	while (std::cin >> direction)
	{
		switch (direction)
		{
		case 'w':
			player->m_x_position--;
			break;
		case 's':
			player->m_x_position++;
			break;
		case 'a':
			player->m_y_position--;
			break;
		case 'd':
			player->m_y_position++;
			break;
		default:
			break;
		}

	move_player_on_map(player, enemy);
	show_map();
	}
}