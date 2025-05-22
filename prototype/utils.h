#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
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

void show_character_sheet(const std::unique_ptr<Player>& player)
{
	system("cls");

	std::cout
		<< "Player Name: "
		<< player->get_m_name() << '\n'
		<< "Class: "
		<< player->get_m_role_ptr()->get_m_character_ptr()->get_class_name() << '\n'
		<< "Level: "
		<< player->get_m_role_ptr()->get_m_character_ptr()->get_current_level() << '\n'
		<< "HP: "
		<< player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->get_current_point()
		<< "/"
		<< player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->get_max_point() << '\n'
		<< "XP: " << player->get_m_role_ptr()->get_m_character_ptr()->get_current_experience()
		<< "/"
		<< player->get_m_role_ptr()->get_m_character_ptr()->get_experience_till_next_level() << '\n'
		<< "Str: "
		<< player->get_m_role_ptr()->get_total_strength() << '\n'
		<< "Int: "
		<< player->get_m_role_ptr()->get_total_intelligence() << '\n'
		<< "Agi: "
		<< player->get_m_role_ptr()->get_total_agility() << '\n'
		<< "Physical Defense: "
		<< player->get_m_role_ptr()->get_total_physical_defense() << '\n'
		<< "Magic Resistance: "
		<< player->get_m_role_ptr()->get_total_magic_resistance() << '\n'
		<< "Melee Damage: "
		<< player->get_m_role_ptr()->get_melee_damage() << '\n'
		<< "Ranged Damage: "
		<< player->get_m_role_ptr()->get_ranged_damage() << '\n';

	std::cout << "\nAbilities: \n";

	for (const auto& ability : player->get_m_role_ptr()->get_m_character_ptr()->get_abilities())
	{
		std::cout << "  " << ability->get_m_name() << '\n';
	}

	std::cout << "\nArmors: \n";

	for (const auto& armor : player->get_m_role_ptr()->get_armors())
	{
		if (armor != nullptr)
		{
			std::cout << "  " << armor->get_m_item_ptr()->get_name() << '\n';
		}
	}

	std::cout << "\nWeapons: \n";

	for (const auto& weapon : player->get_m_role_ptr()->get_weapons())
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
	bool round_used{ false };
	char input{};

	std::vector<std::unique_ptr<GameItem>>& inventory = player->get_m_role_ptr()->get_inventory();

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
				selection = selection < 1 ? 0 : --selection;
				break;
			case 's':
			case 'S':
				selection = selection >= inventory.size() - 1 ? inventory.size() - 1 : ++selection;
				break;
			case 'u':
			case 'U':
			{
				if (inventory.empty())
				{
					break;
				}

				bool is_last_item = selection == inventory.size() - 1 ? true : false;
				bool is_potion = GameItemManager::is_item_potion(inventory.at(selection));
				round_used = GameItemManager::use_or_equip_item(player->get_m_role_ptr(), selection);

				if (is_last_item && round_used)
				{
					selection = selection < 1 ? 0 : inventory.size() - 1;
				}

				if (is_potion && !round_used)
				{
					std::cout << "You are already at full health.\n\n";
					wait_for_enter();
				}
				close_inventory = (round_used && during_battle) ? true : false;
				break;
			}
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

DamageType calculate_ability_hit_point_effect(const std::unique_ptr<Player>& player, const std::unique_ptr<Ability>& ability)
{
	DamageType ability_hit_point_effect = ability->get_m_hit_point_effect();

	switch (ability->get_m_scalar())
	{
	case AbilityScalar::strength:
		// Abilities that deal physical damage should include base attack power.
		// Since only Warrior abilities currently scale with strength, it's safe to add melee damage here.
		ability_hit_point_effect += (player->get_m_role_ptr()->get_total_strength() + player->get_m_role_ptr()->get_melee_damage());
		break;
	case AbilityScalar::intelligence:
		ability_hit_point_effect += player->get_m_role_ptr()->get_total_intelligence();
		break;
	case AbilityScalar::agility:
		// Both Hunter and Rogue abilities scale with agility, so apply ranged damage to Hunter and melee damage to Rogue.
		if (typeid(*(player->get_m_role_ptr()->get_m_character_ptr())) == typeid(Hunter))
		{
			ability_hit_point_effect += (player->get_m_role_ptr()->get_total_agility() + player->get_m_role_ptr()->get_ranged_damage());
		}
		else
		{
			ability_hit_point_effect += (player->get_m_role_ptr()->get_total_agility() + player->get_m_role_ptr()->get_melee_damage());
		}
		break;
	default:
		break;
	}

	return ability_hit_point_effect;
}

bool show_ability_selection(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	size_t selection{ 0 };
	bool close_ability_selection{ false };
	bool round_used{ false };
	char input{};

	std::vector<std::unique_ptr<Ability>>& abilities = player->get_m_role_ptr()->get_m_character_ptr()->get_abilities();

	if (abilities.size() == 0)
	{
		system("cls");
		std::cout << "Current Inventory\n\n";
		std::cout << "You do not have any abilities yet.\n\n";
		wait_for_enter("Press ENTER to close ability selection...");
	}
	else
	{
		while (!close_ability_selection)
		{
			system("cls");
			std::cout << "Abilities\n\n";

			size_t index{ 0 };
			for (auto& ability : abilities)
			{
				std::cout << (index == selection ? ">  " : "   ") << ability->get_m_name()
					<< " (Base HP effect: " << ability->get_m_hit_point_effect() 
					<< ", Cost: " << ability->get_m_cost() 
					<< ", Cooldown: " << ability->get_m_cooldown() 
					<< ", Round until available: " << (ability->get_m_round_until_available() > 0 ? std::to_string(ability->get_m_round_until_available()) : "Ready") << ")\n";

				++index;
			}

			std::cout << "\n\nMove up with (w), down with (s), (u) to use the selected ability and (q) to close ability selection.\n";
			std::cin >> input;

			switch (input)
			{
			case 'w':
			case 'W':
				selection = selection < 1 ? 0 : --selection;
				break;
			case 's':
			case 'S':
				selection = selection >= abilities.size() - 1 ? abilities.size() - 1 : ++selection;
				break;
			case 'u':
			case 'U':
			{
				std::unique_ptr<Ability>& ability = abilities.at(selection);
				DamageType ability_hit_point_effect = calculate_ability_hit_point_effect(player, ability);

				if (ability->get_m_round_until_available() > 0)
				{
					std::cout << "Ability is not available yet.\n\n";
					wait_for_enter();
				}
				else if (ability->get_m_target() == AbilityTarget::enemy)
				{
					enemy->get_monster_ptr()->get_hit_point()->reduce_current_point(ability_hit_point_effect);
					ability->set_m_time_until_available(ability->get_m_cooldown());
					round_used = true;
				}
				else if (ability->get_m_target() == AbilityTarget::ally)
				{
					if (player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->is_full())
					{
						std::cout << "You are already at full health.\n\n";
						round_used = false;
						wait_for_enter();
					}
					else
					{
						player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->increase_current_point(ability_hit_point_effect);
						ability->set_m_time_until_available(ability->get_m_cooldown());
						round_used = true;
					}
				}
				close_ability_selection = round_used;
				break;
			}
			case 'q':
			case 'Q':
				close_ability_selection = true;
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
		item_dropped = GameItemManager::generate_item("Helmet", ArmorSlot::head, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 10)
	{
		item_dropped = GameItemManager::generate_item("Chest Armor", ArmorSlot::chest, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 15)
	{
		item_dropped = GameItemManager::generate_item("Legs Armor", ArmorSlot::legs, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 20)
	{
		item_dropped = GameItemManager::generate_item("Boots", ArmorSlot::boots, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 25)
	{
		item_dropped = GameItemManager::generate_item("Gloves", ArmorSlot::gloves, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 30)
	{
		item_dropped = GameItemManager::generate_item("Ring 1", ArmorSlot::ring1, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 35)
	{
		item_dropped = GameItemManager::generate_item("Ring 2", ArmorSlot::ring2, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 40)
	{
		item_dropped = GameItemManager::generate_item("Neckless", ArmorSlot::neck, std::make_unique<BaseStat>(0, 0, 0, 1, 0));
	}
	else if (drop_seed < 45)
	{
		item_dropped = GameItemManager::generate_item("Sword", WeaponSlot::melee, std::make_unique<BaseStat>(), true, 3u, 5u);
	}
	else if (drop_seed < 50)
	{
		item_dropped = GameItemManager::generate_item("Bow", WeaponSlot::ranged, std::make_unique<BaseStat>(), true, 2u, 4u);
	}
	else if (drop_seed < 90)
	{
		item_dropped = GameItemManager::generate_item("Healing Salve", 5u, Random::random(1, 2), nullptr);
	}

	return item_dropped;
}


void create_enemy(std::unique_ptr<Enemy>& enemy, const std::unique_ptr<Player>& player)
{
	PointPoolType min_hit_point = player->get_m_role_ptr()->get_m_character_ptr()->get_current_level();
	PointPoolType max_hit_point = static_cast<PointPoolType>(player->get_m_role_ptr()->get_m_character_ptr()->get_current_level()) * 3u;

	std::unique_ptr<PointPool> monster_point_pool_ptr = std::make_unique<PointPool>(Random::random(min_hit_point, max_hit_point), Random::random(min_hit_point, max_hit_point));

	DamageType min_damage = player->get_m_role_ptr()->get_m_character_ptr()->get_current_level();
	DamageType max_damage = static_cast<DamageType>(player->get_m_role_ptr()->get_m_character_ptr()->get_current_level()) * 3u;

	std::unique_ptr<Monster> monster_ptr = std::make_unique<Monster>(monster_point_pool_ptr, min_damage, max_damage);

	ExperienceType experience = static_cast<ExperienceType>(pow(2, static_cast<ExperienceType>(player->get_m_role_ptr()->get_m_character_ptr()->get_current_level()) - 1) * 20u);

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
	for (auto& ability : player->get_m_role_ptr()->get_m_character_ptr()->get_abilities())
	{
		// Set the cooldown of the ability to 0 at the beginning of the each battle.
		ability->set_m_time_until_available(0);
	}

	while (player->is_alive() && enemy->is_alive())
	{
		BattleOptions battle_option{ BattleOptions::none };
		char input{};

		for (auto& ability : player->get_m_role_ptr()->get_m_character_ptr()->get_abilities())
		{
			// Decrease the cooldown of the ability by 1 at the beginning of each round.
			if (ability->get_m_round_until_available() > 0)
			{
				ability->set_m_time_until_available(ability->get_m_round_until_available() - 1);
			}
		}

		while (battle_option == BattleOptions::none)
		{
			system("cls");

			std::cout << std::setw(30) << std::left << "" << "Player vs. Enemy" << '\n' << '\n'
				<< std::setw(10) << std::left
				<< player->get_m_name()
				<< std::setw(50) << std::left << ""
				<< "Enemy: \n"
				<< std::setw(7) << std::left
				<< "Class: "
				<< std::setw(10) << std::left
				<< player->get_m_role_ptr()->get_m_character_ptr()->get_class_name()
				<< std::setw(7) << std::left
				<< "Level: "
				<< std::setw(5) << std::left
				<< player->get_m_role_ptr()->get_m_character_ptr()->get_current_level()
				<< std::setw(4) << std::left
				<< "HP: "
				<< std::setw(3) << std::left
				<< player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->get_current_point()
				<< std::setw(1) << std::left
				<< "/"
				<< std::setw(3) << std::right
				<< player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->get_max_point()
				<< std::setw(20) << std::left << ""
				<< std::setw(4) << std::left
				<< "HP: "
				<< std::setw(3) << std::left
				<< enemy->get_monster_ptr()->get_hit_point()->get_current_point()
				<< std::setw(1) << std::left
				<< "/"
				<< std::setw(3) << std::right
				<< enemy->get_monster_ptr()->get_hit_point()->get_max_point()
				<< '\n';

			std::cout << '\n' << '\n' << "Please make a selection:\n"
				<< "a: Attack\n"
				<< "i: Show inventory\n"
				<< "u: Show ability selection"
				<< '\n';

			std::cin >> input;

			switch (input)
			{
			case 'a':
			case 'A':
			{
				// Hunter deals ranged damage.
				DamageType damage = typeid(*(player->get_m_role_ptr())) == typeid(Hunter) ? player->get_m_role_ptr()->get_ranged_damage() : player->get_m_role_ptr()->get_melee_damage();
				enemy->get_monster_ptr()->get_hit_point()->reduce_current_point(damage);
				battle_option = BattleOptions::attack;
				break;
			}
			case 'i':
			case 'I':
				battle_option = show_inventory(player, true) ? BattleOptions::inventory : BattleOptions::none;
				break;
			case 'u':
			case 'U':
				battle_option = show_ability_selection(player, enemy) ? BattleOptions::ability : BattleOptions::none;
				break;
			default:
				break;
			}
		}

		if (enemy->is_alive())
		{
			DamageType reduced_damage = enemy->get_monster_ptr()->get_damage() - player->get_m_role_ptr()->get_total_physical_defense();
			DamageType damage = reduced_damage <= 1 ? 1 : reduced_damage;
			player->get_m_role_ptr()->get_m_character_ptr()->get_hit_point()->reduce_current_point(damage);
		}
	}

	if (!player->is_alive())
	{
		std::cout << "\nYou have died!" << '\n' << '\n';

	}
	else if (!enemy->is_alive())
	{
		std::cout << "You have defeated the enemy!" << '\n';
		std::cout << "You have gained " << enemy->get_experience() << " experiences!" << '\n';
		LevelType previous_level = player->get_m_role_ptr()->get_m_character_ptr()->get_current_level();
		player->get_m_role_ptr()->get_m_character_ptr()->gain_experience(enemy->get_experience());
		LevelType current_level = player->get_m_role_ptr()->get_m_character_ptr()->get_current_level();

		if (current_level > previous_level)
		{
			std::cout << "You have leveled up to " << current_level << '!' << '\n';
		}

		std::unique_ptr<GameItem> item_dropped = drop_item();
		if (item_dropped != nullptr)
		{
			std::cout << "You have received: " << item_dropped->get_m_item_ptr()->get_name() << '!' << '\n' << '\n';
		}
		else
		{
			std::cout << '\n';
		}

		GameItemManager::add_to_inventory(player->get_m_role_ptr(), std::move(item_dropped));
	}

	wait_for_enter();
}

void move_player_on_map(std::unique_ptr<Player>& player, std::unique_ptr<Enemy>& enemy)
{
	if (world_map.at(player->get_m_x_position()).at(player->get_m_y_position()) == 'E')
	{
		enter_battle(player, enemy);

		if (player->is_alive())
		{
			world_map.at(player->get_m_previous_x_position()).at(player->get_m_previous_y_position()) = ' ';
			world_map.at(player->get_m_x_position()).at(player->get_m_y_position()) = 'P';

			player->set_m_previous_x_position(player->get_m_x_position());
			player->set_m_previous_y_position(player->get_m_y_position());

			create_enemy(enemy, player);
		}
		else
		{
			world_map.at(player->get_m_previous_x_position()).at(player->get_m_previous_y_position()) = ' ';
		}
	}
	else if (world_map.at(player->get_m_x_position()).at(player->get_m_y_position()) != 'x' && world_map.at(player->get_m_x_position()).at(player->get_m_y_position()) != 'P')
	{
		world_map.at(player->get_m_previous_x_position()).at(player->get_m_previous_y_position()) = ' ';
		world_map.at(player->get_m_x_position()).at(player->get_m_y_position()) = 'P';

		player->set_m_previous_x_position(player->get_m_x_position());
		player->set_m_previous_y_position(player->get_m_y_position());
	}
	else
	{
		player->set_m_x_position(player->get_m_previous_x_position());
		player->set_m_y_position(player->get_m_previous_y_position());
	}
}
