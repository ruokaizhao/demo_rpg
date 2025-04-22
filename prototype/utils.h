#pragma once
#include <iostream>
#include <iomanip>
#include "player.h"
#include "enemy.h"
#include "world_map.h"
#include "warrior.h"
#include "game_item_manager.h"

static void show_map()
{
	system("cls");

	for (const auto& row : world_map)
	{
		std::cout << row << '\n';
	}
}

static void show_inventory(std::unique_ptr<Player>& player)
{
	system("cls");

	std::cout << "Current Inventory\n\n";

	std::vector<std::unique_ptr<GameItem>>& inventory = player->m_role_ptr->get_inventory();

	if (inventory.size() == 0)
	{
		std::cout << "The inventory is empty.\n";
	}
	else
	{
		for (auto& item : inventory)
		{
			std::cout << "> " << item->get_m_item_ptr()->get_name() << '\n';
		}
	}

	std::cout << "\n\nPlease any key to return to the map view.\n";

	char input{};
	std::cin >> input;
}

static std::unique_ptr<GameItem> drop_item()
{
	std::unique_ptr<GameItem> item_dropped = nullptr;
	int drop_seed = Random::random(0, 100);

	if (drop_seed < 5)
	{
		item_dropped = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 10)
	{
		item_dropped = GameItemManager::generate_item("Chest Armor", ArmorSlot::chest, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 15)
	{
		item_dropped = GameItemManager::generate_item("Legs Armor", ArmorSlot::legs, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 20)
	{
		item_dropped = GameItemManager::generate_item("Boots", ArmorSlot::boots, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 25)
	{
		item_dropped = GameItemManager::generate_item("Gloves", ArmorSlot::gloves, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 30)
	{
		item_dropped = GameItemManager::generate_item("Ring 1", ArmorSlot::ring1, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 35)
	{
		item_dropped = GameItemManager::generate_item("Ring 2", ArmorSlot::ring2, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 40)
	{
		item_dropped = GameItemManager::generate_item("Neckless", ArmorSlot::neck, BaseStat{ 0, 0, 0, 1, 0 });
	}
	else if (drop_seed < 45)
	{
		item_dropped = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{}, true, 3u, 5u);
	}
	else if (drop_seed < 50)
	{
		item_dropped = GameItemManager::generate_item("Bow", WeaponSlot::ranged, BaseStat{}, true, 2u, 4u);
	}
	else if (drop_seed < 90)
	{
		item_dropped = GameItemManager::generate_item("Healing Salve", 5u, Random::random(1, 2), nullptr);
	}

	return item_dropped;
}


static void create_enemy(std::unique_ptr<Enemy>& enemy, const std::unique_ptr<Player>& player)
{
	if (enemy != nullptr)
	{
		world_map.at(enemy->m_x_position).at(enemy->m_y_position) = ' ';
	}

	PointPoolType min_hit_point = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	PointPoolType max_hit_point = static_cast<PointPoolType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 10;

	std::unique_ptr<PointPool> monster_point_pool_ptr = std::make_unique<PointPool>(Random::random(min_hit_point, max_hit_point), Random::random(min_hit_point, max_hit_point));

	DamageType min_damage = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	DamageType max_damage = static_cast<DamageType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 5;

	std::unique_ptr<Monster> monster_ptr = std::make_unique<Monster>(monster_point_pool_ptr, min_damage, max_damage);

	ExperienceType experience = static_cast<ExperienceType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 1000000;

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

		std::cout << std::setw(30) << std::left << "" << "Player vs. Enemy" << '\n' << '\n'
			<< std::setw(10) << std::left
			<< player->get_name()
			<< std::setw(50) << std::left << ""
			<< "Enemy: "
			<< '\n'
			<< std::setw(7) << std::left
			<< "Class: "
			<< std::setw(10) << std::left
			<< player->m_role_ptr->get_m_character_ptr()->get_class_name()
			<< std::setw(7) << std::left
			<< "Level: "
			<< std::setw(5) << std::left
			<< player->m_role_ptr->get_m_character_ptr()->get_current_level()
			<< std::setw(4) << std::left
			<< "HP: "
			<< std::setw(3) << std::left
			<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point()
			<< std::setw(1) << std::left
			<< "/"
			<< std::setw(3) << std::right
			<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_max_point()
			<< std::setw(20) << std::left << ""
			<< std::setw(4) << std::left
			<< "HP: "
			<< std::setw(3) << std::left
			<< enemy->m_monster_ptr->get_hit_point()->get_current_point()
			<< std::setw(1) << std::left
			<< "/"
			<< std::setw(3) << std::right
			<< enemy->m_monster_ptr->get_hit_point()->get_max_point()
			<< '\n';

		std::cout << '\n' << '\n' << "Please make a selection:\n"
			<< "a. Attack\n"
			<< '\n';

		char input{};
		std::cin >> input;

		while (input != 'a')
		{
			std::cout << "Invalid selection! Please try again:";
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
		std::unique_ptr<GameItem> item_dropped = drop_item();
		GameItemManager::add_to_inventory(player->m_role_ptr, item_dropped);

		std::cout << "You have defeated the enemy!" << '\n';
		std::cout << "You have gained " << enemy->m_experience << " experiences!" << '\n';
		std::cout << "You have received: " << player->m_role_ptr->get_inventory().back()->get_m_item_ptr()->get_name() << '!' << '\n' << '\n';
		std::cout << "Press any key to continue..." << '\n';

		create_enemy(enemy, player);
	}

	char input{};
	std::cin >> input;
}

static void move_player_on_map(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	if (world_map.at(player->m_x_position).at(player->m_y_position) == 'E')
	{
		enter_battle(player, enemy);

		if (player->is_alive())
		{
			world_map.at(player->m_previous_x_position).at(player->m_previous_y_position) = ' ';
			world_map.at(player->m_x_position).at(player->m_y_position) = 'P';

			player->m_previous_x_position = player->m_x_position;
			player->m_previous_y_position = player->m_y_position;
		}
		else
		{
			world_map.at(player->m_previous_x_position).at(player->m_previous_y_position) = ' ';
		}
	}
	else if (world_map.at(player->m_x_position).at(player->m_y_position) != 'x' && world_map.at(player->m_x_position).at(player->m_y_position) != 'P')
	{
		world_map.at(player->m_previous_x_position).at(player->m_previous_y_position) = ' ';
		world_map.at(player->m_x_position).at(player->m_y_position) = 'P';

		player->m_previous_x_position = player->m_x_position;
		player->m_previous_y_position = player->m_y_position;
	}
	else
	{
		player->m_x_position = player->m_previous_x_position;
		player->m_y_position = player->m_previous_y_position;
	}
}

