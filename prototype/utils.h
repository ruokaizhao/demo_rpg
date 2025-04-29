#pragma once
#include <iostream>
#include <iomanip>
#include "player.h"
#include "enemy.h"
#include "world_map.h"
#include "warrior.h"
#include "game_item_manager.h"
#include "enums.h"

void show_map()
{
	system("cls");

	for (const auto& row : world_map)
	{
		std::cout << row << '\n';
	}
}

void wait_for_enter(const std::string& message = "Press ENTER to continue...")
{
	std::cout << message << '\n';
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void show_character_sheet(std::unique_ptr<Player>& player)
{
	system("cls");

	std::cout
		<< "Player Name: "
		<< player->get_name() << '\n'
		<< "Class: "
		<< player->m_role_ptr->get_m_character_ptr()->get_class_name() << '\n'
		<< "Level: "
		<< player->m_role_ptr->get_m_character_ptr()->get_current_level() << '\n'
		<< "HP: "
		<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_current_point()
		<< "/"
		<< player->m_role_ptr->get_m_character_ptr()->get_hit_point()->get_max_point() << '\n'
		<< "XP: " << player->m_role_ptr->get_m_character_ptr()->get_current_experience()
		<< "/"
		<< player->m_role_ptr->get_m_character_ptr()->get_experience_till_next_level() << '\n'
		<< "Str: "
		<< player->m_role_ptr->get_total_strength() << '\n'
		<< "Int: "
		<< player->m_role_ptr->get_total_intelligence() << '\n'
		<< "Agi: "
		<< player->m_role_ptr->get_total_agility() << '\n'
		<< "Physical Defense: "
		<< player->m_role_ptr->get_total_physical_defense() << '\n'
		<< "Magic Resistance: "
		<< player->m_role_ptr->get_total_magic_resistance() << '\n'
		<< "Melee Damage: "
		<< player->m_role_ptr->get_melee_damage() << '\n'
		<< "Ranged Damage: "
		<< player->m_role_ptr->get_ranged_damage() << '\n';

	std::cout << "\nAbilities: \n";

	for (const auto& ability : player->m_role_ptr->get_m_character_ptr()->get_abilities())
	{
		std::cout << "  " << ability->m_name << '\n';
	}
		
	std::cout << "\nArmors: \n";

	for (const auto& armor : player->m_role_ptr->get_armors())
	{
		if (armor != nullptr)
		{
			std::cout << "  " << armor->get_m_item_ptr()->get_name() << '\n';
		}
	}

	std::cout << "\nWeapons: \n";

	for (const auto& weapon : player->m_role_ptr->get_weapons())
	{
		if (weapon != nullptr)
		{
			std::cout << "  " << weapon->get_m_item_ptr()->get_name() << '\n';
		}
	}

	std::cout << '\n';

	wait_for_enter();
}

bool show_inventory(std::unique_ptr<Player>& player, bool during_battle)
{
	size_t selection{ 0 };
	bool close_inventory{ false };
	char input{};
	bool round_used{ false };

	std::vector<std::unique_ptr<GameItem>>& inventory = player->m_role_ptr->get_inventory();

	if (inventory.size() == 0)
	{
		system("cls");
		std::cout << "Current Inventory\n\n";
		std::cout << "The inventory is empty.\n\n";
		wait_for_enter("Press ENTER to close inventory...");
	}
	else
	{
		while (!close_inventory)
		{
			system("cls");
			std::cout << "Current Inventory\n\n";

			size_t index{ 0 };
			for (auto& item : inventory)
			{
				std::cout << (index == selection ? ">  " : "   ") << item->get_m_item_ptr()->get_name() << '\n';
				if (GameItemManager::is_item_potion(item))
				{
					std::cout << "     Quantity: " << GameItemManager::convert_item_to_potion(item)->get_count() << '\n';
				}
				++index;
			}

			std::cout << "\n\nMove up with (w), down with (s), (u) to use the selected item and (q) to close inventory.\n";
			std::cin >> input;

			switch (input)
			{
			case 'w':
			case 'W':
				selection = selection <= 0 ? 0 : --selection;
				break;
			case 's':
			case 'S':
				selection = selection >= inventory.size() - 1 ? inventory.size() - 1 : ++selection;
				break;
			case 'u':
			case 'U':
				round_used = GameItemManager::use_or_equip_item(player->m_role_ptr, selection);
				close_inventory = (round_used && during_battle) ? true : false;
				break;
			case 'q':
			case 'Q':
				close_inventory = true;
				break;
			default:
				break;
			}
		}
	}

	return round_used;
}

std::unique_ptr<GameItem> drop_item()
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


void create_enemy(std::unique_ptr<Enemy>& enemy, const std::unique_ptr<Player>& player)
{
	PointPoolType min_hit_point = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	PointPoolType max_hit_point = static_cast<PointPoolType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 2;

	std::unique_ptr<PointPool> monster_point_pool_ptr = std::make_unique<PointPool>(Random::random(min_hit_point, max_hit_point), Random::random(min_hit_point, max_hit_point));

	DamageType min_damage = player->m_role_ptr->get_m_character_ptr()->get_current_level();
	DamageType max_damage = static_cast<DamageType>(player->m_role_ptr->get_m_character_ptr()->get_current_level()) * 2;

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

void enter_battle(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	while (player->is_alive() && enemy->is_alive())
	{
		BattleOptions battle_option{ BattleOptions::none };
		char input{};

		while (battle_option == BattleOptions::none)
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
				<< "a: Attack\n"
				<< "i: Open inventory\n"
				<< "u: Use abilities"
				<< '\n';

			std::cin >> input;

			switch (input)
			{
			case 'a':
			case 'A':
				enemy->m_monster_ptr->get_hit_point()->reduce_current_point(player->m_role_ptr->get_melee_damage());
				battle_option = BattleOptions::attack;
				break;
			case 'i':
			case 'I':
				battle_option = show_inventory(player, true) ? BattleOptions::inventory : BattleOptions::none;
				break;
			case 'u':
			case 'U':
				battle_option = BattleOptions::ability;
				break;
			default:
				break;
			}
		}

		if (enemy->is_alive())
		{
			DamageType damage_taken = enemy->m_monster_ptr->get_damage() - player->m_role_ptr->get_total_physical_defense() <= 1 ? 1 : enemy->m_monster_ptr->get_damage() - player->m_role_ptr->get_total_physical_defense();
			player->m_role_ptr->get_m_character_ptr()->get_hit_point()->reduce_current_point(damage_taken);
		}
	}

	if (!player->is_alive())
	{
		std::cout << "\nYou have died!" << '\n\n';

	}
	else if (!enemy->is_alive())
	{
		std::cout << "You have defeated the enemy!" << '\n';
		std::cout << "You have gained " << enemy->m_experience << " experiences!" << '\n';

		std::unique_ptr<GameItem> item_dropped = drop_item();
		if (item_dropped != nullptr)
		{
			std::cout << "You have received: " << item_dropped->get_m_item_ptr()->get_name() << '!' << '\n' << '\n';
		}
		else
		{
			std::cout << '\n';
		}

		player->m_role_ptr->get_m_character_ptr()->gain_experience(enemy->m_experience);
		GameItemManager::add_to_inventory(player->m_role_ptr, item_dropped);
	}

	wait_for_enter();
}

void move_player_on_map(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
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

			create_enemy(enemy, player);
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

