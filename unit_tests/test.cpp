#include "pch.h"
#include <iostream>
#include <algorithm>
#include "role.h"
#include "game_item_manager.h"
#include <monster.h>

namespace DemoRPGUnitTests {
    // The following tests are for the Ability class.
    TEST(AbilityTest, Initialization) {
        Ability unnamed_ability;

        EXPECT_EQ("unnamed", unnamed_ability.m_name);
        EXPECT_EQ(0u, unnamed_ability.m_cost);
        EXPECT_EQ(1u, unnamed_ability.m_cooldown);
        EXPECT_EQ(1u, unnamed_ability.m_hit_point_effect);
        EXPECT_EQ(AbilityTarget::SELF, unnamed_ability.m_target);
        EXPECT_EQ(AbilityScalar::none, unnamed_ability.m_scalar);

        Ability heal_ability{ "Heal", 1u, 2u, 3u, AbilityTarget::ALLY, AbilityScalar::intelligence };

        EXPECT_EQ("Heal", heal_ability.m_name);
        EXPECT_EQ(1u, heal_ability.m_cost);
        EXPECT_EQ(2u, heal_ability.m_cooldown);
        EXPECT_EQ(3u, heal_ability.m_hit_point_effect);
        EXPECT_EQ(AbilityTarget::ALLY, heal_ability.m_target);
        EXPECT_EQ(AbilityScalar::intelligence, heal_ability.m_scalar);
    }

    // The following tests are for the Buff class.
    TEST(BuffTest, Initialization) {
        Buff unnamed_buff;

        EXPECT_EQ(unnamed_buff.m_name, "unnamed");
        EXPECT_FALSE(unnamed_buff.m_is_debuff);
        EXPECT_EQ(unnamed_buff.m_duration, 2u);
        EXPECT_EQ(unnamed_buff.m_stat.m_strength, 0u);
        EXPECT_EQ(unnamed_buff.m_stat.m_intelligence, 0u);
        EXPECT_EQ(unnamed_buff.m_stat.m_agility, 0u);
        EXPECT_EQ(unnamed_buff.m_stat.m_physical_defense, 0u);
        EXPECT_EQ(unnamed_buff.m_stat.m_magic_resistance, 0u);

        Buff power_buff("Power", false, 5u, 10u, 20u, 30u, 40u, 50u);

        EXPECT_EQ(power_buff.m_name, "Power");
        EXPECT_FALSE(power_buff.m_is_debuff);
        EXPECT_EQ(power_buff.m_duration, 5u);
        EXPECT_EQ(power_buff.m_stat.m_strength, 10u);
        EXPECT_EQ(power_buff.m_stat.m_intelligence, 20u);
        EXPECT_EQ(power_buff.m_stat.m_agility, 30u);
        EXPECT_EQ(power_buff.m_stat.m_physical_defense, 40u);
        EXPECT_EQ(power_buff.m_stat.m_magic_resistance, 50u);

        BaseStat core_stat{ 5u, 10u, 15u, 20u, 25u };
        Buff Stat_buff(core_stat, "Stat", true, 3u);

        EXPECT_EQ(Stat_buff.m_name, "Stat");
        EXPECT_TRUE(Stat_buff.m_is_debuff);
        EXPECT_EQ(Stat_buff.m_duration, 3u);
        EXPECT_EQ(Stat_buff.m_stat.m_strength, 5u);
        EXPECT_EQ(Stat_buff.m_stat.m_intelligence, 10u);
        EXPECT_EQ(Stat_buff.m_stat.m_agility, 15u);
        EXPECT_EQ(Stat_buff.m_stat.m_physical_defense, 20u);
        EXPECT_EQ(Stat_buff.m_stat.m_magic_resistance, 25u);
    }

    // Test case for Cleric class
    TEST(ClericTest, Initialization) {
        Cleric cleric;

        EXPECT_EQ(cleric.get_class_name(), "Cleric");
        EXPECT_EQ(cleric.get_current_level(), 1u);
        EXPECT_EQ(cleric.get_current_experience(), 0u);
        EXPECT_EQ(cleric.get_experience_till_next_level(), 100u);
        EXPECT_EQ(cleric.get_hit_point()->get_max_point(), 14u);
        EXPECT_EQ(cleric.get_hit_point()->get_current_point(), 14u);
        EXPECT_EQ(cleric.get_mana_point()->get_max_point(), 10u);
        EXPECT_EQ(cleric.get_mana_point()->get_current_point(), 10u);
        EXPECT_EQ(cleric.get_base_strength(), 3u);
        EXPECT_EQ(cleric.get_base_intelligence(), 5u);
        EXPECT_EQ(cleric.get_base_agility(), 1u);
        ASSERT_EQ(cleric.get_abilities().size(), 1u);
        EXPECT_EQ(cleric.get_abilities().at(0).m_name, "Heal");
    }

    TEST(ClericTest, LevelUp) {
        Cleric cleric;
        cleric.gain_experience(100u);

        EXPECT_EQ(cleric.get_current_level(), 2u);
        EXPECT_EQ(cleric.get_current_experience(), 0u);
        EXPECT_EQ(cleric.get_experience_till_next_level(), 200u);
        EXPECT_EQ(cleric.get_hit_point()->get_max_point(), 21u);
        EXPECT_EQ(cleric.get_hit_point()->get_current_point(), 21u);
        EXPECT_EQ(cleric.get_mana_point()->get_max_point(), 15u);
        EXPECT_EQ(cleric.get_mana_point()->get_current_point(), 15u);
        EXPECT_EQ(cleric.get_base_strength(), 5u);
        EXPECT_EQ(cleric.get_base_intelligence(), 8u);
        EXPECT_EQ(cleric.get_base_agility(), 2u);
        ASSERT_EQ(cleric.get_abilities().size(), 2u);
        EXPECT_EQ(cleric.get_abilities()[1].m_name, "Smite");
    }

    // Test case for Rogue class
    TEST(RogueTest, Initialization) {
        Rogue rogue;

        EXPECT_EQ(rogue.get_class_name(), "Rogue");
        EXPECT_EQ(rogue.get_current_level(), 1u);
        EXPECT_EQ(rogue.get_current_experience(), 0u);
        EXPECT_EQ(rogue.get_experience_till_next_level(), 100u);
        EXPECT_EQ(rogue.get_hit_point()->get_max_point(), 12u);
        EXPECT_EQ(rogue.get_hit_point()->get_current_point(), 12u);
        EXPECT_EQ(rogue.get_base_strength(), 3u);
        EXPECT_EQ(rogue.get_base_intelligence(), 3u);
        EXPECT_EQ(rogue.get_base_agility(), 5u);
    }

    TEST(RogueTest, LevelUp) {
        Rogue rogue;
        rogue.gain_experience(100u);

        EXPECT_EQ(rogue.get_current_level(), 2u);
        EXPECT_EQ(rogue.get_current_experience(), 0u);
        EXPECT_EQ(rogue.get_experience_till_next_level(), 200u);
        EXPECT_EQ(rogue.get_hit_point()->get_max_point(), 18u);
        EXPECT_EQ(rogue.get_hit_point()->get_current_point(), 18u);
        EXPECT_EQ(rogue.get_base_strength(), 5u);
        EXPECT_EQ(rogue.get_base_intelligence(), 5u);
        EXPECT_EQ(rogue.get_base_agility(), 8u);
    }

    // Test case for Warrior class
    TEST(WarriorTest, Initialization) {
        Warrior warrior;

        EXPECT_EQ(warrior.get_class_name(), "Warrior");
        EXPECT_EQ(warrior.get_current_level(), 1u);
        EXPECT_EQ(warrior.get_current_experience(), 0u);
        EXPECT_EQ(warrior.get_experience_till_next_level(), 100u);
        EXPECT_EQ(warrior.get_hit_point()->get_max_point(), 18u);
        EXPECT_EQ(warrior.get_hit_point()->get_current_point(), 18u);
        EXPECT_EQ(warrior.get_base_strength(), 6u);
        EXPECT_EQ(warrior.get_base_intelligence(), 2u);
        EXPECT_EQ(warrior.get_base_agility(), 2u);
    }

    TEST(WarriorTest, LevelUp) {
        Warrior warrior;
        warrior.gain_experience(100u);

        EXPECT_EQ(warrior.get_current_level(), 2u);
        EXPECT_EQ(warrior.get_current_experience(), 0u);
        EXPECT_EQ(warrior.get_experience_till_next_level(), 200u);
        EXPECT_EQ(warrior.get_hit_point()->get_max_point(), 27u);
        EXPECT_EQ(warrior.get_hit_point()->get_current_point(), 27u);
        EXPECT_EQ(warrior.get_base_strength(), 9u);
        EXPECT_EQ(warrior.get_base_intelligence(), 3u);
        EXPECT_EQ(warrior.get_base_agility(), 3u);
        ASSERT_EQ(warrior.get_abilities().size(), 1u);
        EXPECT_EQ(warrior.get_abilities()[0].m_name, "Power Attact");
    }

    // Test case for Wizard class
    TEST(WizardTest, Initialization) {
        Wizard wizard;

        EXPECT_EQ(wizard.get_class_name(), "Wizard");
        EXPECT_EQ(wizard.get_current_level(), 1u);
        EXPECT_EQ(wizard.get_current_experience(), 0u);
        EXPECT_EQ(wizard.get_experience_till_next_level(), 100u);
        EXPECT_EQ(wizard.get_hit_point()->get_max_point(), 10u);
        EXPECT_EQ(wizard.get_hit_point()->get_current_point(), 10u);
        EXPECT_EQ(wizard.get_mana_point()->get_max_point(), 14u);
        EXPECT_EQ(wizard.get_mana_point()->get_current_point(), 14u);
        EXPECT_EQ(wizard.get_base_strength(), 1u);
        EXPECT_EQ(wizard.get_base_intelligence(), 8u);
        EXPECT_EQ(wizard.get_base_agility(), 2u);
        ASSERT_EQ(wizard.get_abilities().size(), 1u);
        EXPECT_EQ(wizard.get_abilities()[0].m_name, "Fireball");
    }

    TEST(WizardTest, LevelUp) {
        Wizard wizard;
        wizard.gain_experience(100u);

        EXPECT_EQ(wizard.get_current_level(), 2u);
        EXPECT_EQ(wizard.get_current_experience(), 0u);
        EXPECT_EQ(wizard.get_experience_till_next_level(), 200u);
        EXPECT_EQ(wizard.get_hit_point()->get_max_point(), 15u);
        EXPECT_EQ(wizard.get_hit_point()->get_current_point(), 15u);
        EXPECT_EQ(wizard.get_mana_point()->get_max_point(), 21u);
        EXPECT_EQ(wizard.get_mana_point()->get_current_point(), 21u);
        EXPECT_EQ(wizard.get_base_strength(), 2u);
        EXPECT_EQ(wizard.get_base_intelligence(), 12u);
        EXPECT_EQ(wizard.get_base_agility(), 3u);
        ASSERT_EQ(wizard.get_abilities().size(), 2u);
        EXPECT_EQ(wizard.get_abilities()[1].m_name, "Icebolt");
    }

    // The following tests are for the CoreStat class.
    TEST(CoreStatTest, Initialization) {
        BaseStat core_stat_1;

        EXPECT_EQ(core_stat_1.m_strength, 0u);
        EXPECT_EQ(core_stat_1.m_strength, 0u);
        EXPECT_EQ(core_stat_1.m_intelligence, 0u);
        EXPECT_EQ(core_stat_1.m_agility, 0u);
        EXPECT_EQ(core_stat_1.m_physical_defense, 0u);
        EXPECT_EQ(core_stat_1.m_magic_resistance, 0u);

        BaseStat core_stat_2{ 0u, 0u, 0u, 5u, 5u };

        EXPECT_EQ(core_stat_2.m_strength, 0u);
        EXPECT_EQ(core_stat_2.m_intelligence, 0u);
        EXPECT_EQ(core_stat_2.m_agility, 0u);
        EXPECT_EQ(core_stat_2.m_physical_defense, 5u);
        EXPECT_EQ(core_stat_2.m_magic_resistance, 5u);
    }

    TEST(CoreStatTest, AdditionAndSubtraction) {
        BaseStat core_stat_1{ 0u, 0u, 0u, 5u, 5u };

        EXPECT_EQ(core_stat_1.m_strength, 0u);
        EXPECT_EQ(core_stat_1.m_intelligence, 0u);
        EXPECT_EQ(core_stat_1.m_agility, 0u);
        EXPECT_EQ(core_stat_1.m_physical_defense, 5u);
        EXPECT_EQ(core_stat_1.m_magic_resistance, 5u);

        BaseStat core_stat_2{ 1u, 1u, 1u, 2u, 2u };
        core_stat_2 += core_stat_1;

        EXPECT_EQ(core_stat_2.m_strength, 1u);
        EXPECT_EQ(core_stat_2.m_intelligence, 1u);
        EXPECT_EQ(core_stat_2.m_agility, 1u);
        EXPECT_EQ(core_stat_2.m_physical_defense, 7u);
        EXPECT_EQ(core_stat_2.m_magic_resistance, 7u);

        BaseStat core_stat_3{ 10u, 10u, 10u, 10u, 10u };
        core_stat_3 -= core_stat_2;

        EXPECT_EQ(core_stat_3.m_strength, 9u);
        EXPECT_EQ(core_stat_3.m_intelligence, 9u);
        EXPECT_EQ(core_stat_3.m_agility, 9u);
        EXPECT_EQ(core_stat_3.m_physical_defense, 3u);
        EXPECT_EQ(core_stat_3.m_magic_resistance, 3u);
    }

    // The following tests are for the Equipment class.
    TEST(EquipmentTest, Armor) {
        std::unique_ptr<GameItem> armor = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 1u, 1u, 1u, 1u, 1u });

        EXPECT_EQ(armor->get_m_item_ptr()->get_name(), "Helmet");
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_slot(), ArmorSlot::head);
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_stat().m_strength, 1u);
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_stat().m_intelligence, 1u);
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_stat().m_agility, 1u);
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_stat().m_physical_defense, 1u);
        EXPECT_EQ(dynamic_cast<Armor*>(armor->get_m_item_ptr().get())->get_stat().m_magic_resistance, 1u);
    }

    TEST(EquipmentTest, Weapon) {
        std::unique_ptr<GameItem> weapon = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 1u, 1u, 1u, 1u, 1u }, false, 5u, 10u);
        EXPECT_EQ(weapon->get_m_item_ptr()->get_name(), "Sword");
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_slot(), WeaponSlot::melee);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_stat().m_strength, 1u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_stat().m_intelligence, 1u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_stat().m_agility, 1u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_stat().m_physical_defense, 1u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_stat().m_magic_resistance, 1u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_min_damage(), 5u);
        EXPECT_EQ(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->get_max_damage(), 10u);
        EXPECT_FALSE(dynamic_cast<Weapon*>(weapon->get_m_item_ptr().get())->is_two_handed());
    }

    TEST(EquipmentTest, Potion) {
        std::unique_ptr<GameItem> potion = GameItemManager::generate_item("Heal Potion", 5u, 3u);
        EXPECT_EQ(potion->get_m_item_ptr()->get_name(), "Heal Potion");
        EXPECT_EQ(dynamic_cast<Potion*>(potion->get_m_item_ptr().get())->get_hit_point(), 5u);
        EXPECT_EQ(dynamic_cast<Potion*>(potion->get_m_item_ptr().get())->get_count(), 3u);
        EXPECT_EQ(dynamic_cast<Potion*>(potion->get_m_item_ptr().get())->get_buff(), nullptr);
    }

    // The following tests are for the Item class.
    TEST(ItemTest, Armor) {
        std::unique_ptr<GameItem> armor = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 1u, 1u, 1u, 1u, 1u });

        EXPECT_EQ(armor->get_m_item_ptr()->get_name(), "Helmet");
        EXPECT_FALSE(armor->is_marked_for_deletion());
        armor->mark_for_deletion();
        EXPECT_TRUE(armor->is_marked_for_deletion());
    }

    TEST(ItemTest, Weapon) {
        std::unique_ptr<GameItem> weapon = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 1u, 1u, 1u, 1u, 1u }, false, 5u, 10u);
        EXPECT_EQ(weapon->get_m_item_ptr()->get_name(), "Sword");

        EXPECT_FALSE(weapon->is_marked_for_deletion());
        weapon->mark_for_deletion();
        EXPECT_TRUE(weapon->is_marked_for_deletion());
    }

    TEST(ItemTest, Potion) {
        std::unique_ptr<GameItem> potion = GameItemManager::generate_item("Heal Potion", 5u, 3u);
        EXPECT_EQ(potion->get_m_item_ptr()->get_name(), "Heal Potion");

        EXPECT_FALSE(potion->is_marked_for_deletion());
        potion->mark_for_deletion();
        EXPECT_TRUE(potion->is_marked_for_deletion());
    }

    // The following tests are for the GameItemManager class.
    TEST(GameItemManagerTest, GenerateArmorItem) {
        std::unique_ptr<GameItem> item = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 1u, 1u, 1u, 1u, 1u });
        ASSERT_NE(item, nullptr);
        EXPECT_TRUE(GameItemManager::is_item_armor(item));
        EXPECT_EQ(GameItemManager::convert_item_to_weapon(item), nullptr);
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item), nullptr);

        std::shared_ptr<Armor> armor = GameItemManager::convert_item_to_armor(item);
        ASSERT_NE(armor, nullptr);

        EXPECT_EQ(armor->get_name(), "Helmet");
        EXPECT_EQ(armor->get_slot(), ArmorSlot::head);
        EXPECT_EQ(armor->get_stat().m_strength, 1u);
        EXPECT_EQ(armor->get_stat().m_intelligence, 1u);
        EXPECT_EQ(armor->get_stat().m_agility, 1u);
        EXPECT_EQ(armor->get_stat().m_physical_defense, 1u);
        EXPECT_EQ(armor->get_stat().m_magic_resistance, 1u);
    }

    TEST(GameItemManagerTest, GenerateWeaponItem) {
        std::unique_ptr<GameItem> item = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 1u, 1u, 1u, 1u, 1u }, false, 5u, 10u);
        ASSERT_NE(item, nullptr);
        EXPECT_TRUE(GameItemManager::is_item_weapon(item));
        EXPECT_EQ(GameItemManager::convert_item_to_armor(item), nullptr);
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item), nullptr);

        std::shared_ptr<Weapon> weapon = GameItemManager::convert_item_to_weapon(item);
        ASSERT_NE(weapon, nullptr);

        EXPECT_EQ(weapon->get_name(), "Sword");
        EXPECT_EQ(weapon->get_slot(), WeaponSlot::melee);
        EXPECT_EQ(weapon->get_stat().m_strength, 1u);
        EXPECT_EQ(weapon->get_stat().m_intelligence, 1u);
        EXPECT_EQ(weapon->get_stat().m_agility, 1u);
        EXPECT_EQ(weapon->get_stat().m_physical_defense, 1u);
        EXPECT_EQ(weapon->get_stat().m_magic_resistance, 1u);
        EXPECT_EQ(weapon->get_min_damage(), 5u);
        EXPECT_EQ(weapon->get_max_damage(), 10u);
        EXPECT_FALSE(weapon->is_two_handed());

    }

    TEST(GameItemManagerTest, GeneratePotionItem) {
        std::unique_ptr<GameItem> item = GameItemManager::generate_item("Heal Potion", 5u, 3u);
        ASSERT_NE(item, nullptr);
        EXPECT_TRUE(GameItemManager::is_item_potion(item));
        EXPECT_EQ(GameItemManager::convert_item_to_armor(item), nullptr);
        EXPECT_EQ(GameItemManager::convert_item_to_weapon(item), nullptr);

        std::shared_ptr<Potion> potion = GameItemManager::convert_item_to_potion(item);
        ASSERT_NE(potion, nullptr);

        EXPECT_EQ(potion->get_name(), "Heal Potion");
        EXPECT_EQ(potion->get_hit_point(), 5u);
        EXPECT_EQ(potion->get_count(), 3u);
        EXPECT_EQ(potion->get_buff(), nullptr);
    }

    TEST(GameItemManagerTest, EquipArmorItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 1u, 1u, 1u, 1u, 1u });

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, item_helmet));
        EXPECT_EQ(warrior.get_armor_at(ArmorSlot::head)->get_m_item_ptr()->get_name(), "Helmet");
        EXPECT_EQ(warrior.get_inventory().size(), 0);

        std::unique_ptr<GameItem> item_stronger_helmet = GameItemManager::generate_item("Stronger Helmet", ArmorSlot::head, BaseStat{ 2u, 2u, 2u, 2u, 2u });

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, item_stronger_helmet));
        EXPECT_EQ(warrior.get_armor_at(ArmorSlot::head)->get_m_item_ptr()->get_name(), "Stronger Helmet");
        EXPECT_EQ(warrior.get_inventory().size(), 1);
        EXPECT_EQ(warrior.get_inventory().at(0)->get_m_item_ptr()->get_name(), "Helmet");

        auto temp_item = std::move(warrior.get_inventory().at(0));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, std::move(temp_item)));
        EXPECT_EQ(warrior.get_armor_at(ArmorSlot::head)->get_m_item_ptr()->get_name(), "Helmet");
        EXPECT_EQ(warrior.get_inventory().at(0), nullptr);
        EXPECT_EQ(warrior.get_inventory().at(1)->get_m_item_ptr()->get_name(), "Stronger Helmet");
    }

    TEST(GameItemManagerTest, EquipWeaponItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 1u, 1u, 1u, 1u, 1u }, true, 5u, 10u);

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, item_sword));
        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::melee)->get_m_item_ptr()->get_name(), "Sword");
        EXPECT_EQ(warrior.get_inventory().size(), 0);

        std::unique_ptr<GameItem> item_sharper_sword = GameItemManager::generate_item("Sharper Sword", WeaponSlot::melee, BaseStat{ 2u, 2u, 2u, 2u, 2u }, true, 10u, 20u);

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, item_sharper_sword));
        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::melee)->get_m_item_ptr()->get_name(), "Sharper Sword");
        EXPECT_EQ(warrior.get_inventory().size(), 1);
        EXPECT_EQ(warrior.get_inventory().at(0)->get_m_item_ptr()->get_name(), "Sword");

        auto temp_item = std::move(warrior.get_inventory().at(0));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, std::move(temp_item)));
        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::melee)->get_m_item_ptr()->get_name(), "Sword");
        EXPECT_EQ(warrior.get_inventory().at(0), nullptr);
        EXPECT_EQ(warrior.get_inventory().at(1)->get_m_item_ptr()->get_name(), "Sharper Sword");
    }

    TEST(GameItemManagerTest, EquipPotionItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_heal_potion = GameItemManager::generate_item("Heal Potion", 5u, 3u);

        EXPECT_FALSE(GameItemManager::equip_equipment(warrior, item_heal_potion));
    }

    TEST(GameItemManagerTest, UserArmorItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 1u, 1u, 1u, 1u, 1u });

        EXPECT_FALSE(GameItemManager::use_item(warrior, item_helmet));
    }

    TEST(GameItemManagerTest, UserWeaponItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 1u, 1u, 1u, 1u, 1u }, true, 5u, 10u);

        EXPECT_FALSE(GameItemManager::use_item(warrior, item_sword));
    }

    TEST(GameItemManagerTest, UserPotionItem) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_heal_potion = GameItemManager::generate_item("Heal Potion", 6u, 3u);

        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 18u);
        EXPECT_FALSE(GameItemManager::use_item(warrior, item_heal_potion));
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item_heal_potion)->get_count(), 3u);

        warrior.get_m_character_ptr()->get_hit_point()->reduce_current_point(10u);
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 8u);

        EXPECT_TRUE(GameItemManager::use_item(warrior, item_heal_potion));
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 14u);
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item_heal_potion)->get_count(), 2u);

        EXPECT_TRUE(GameItemManager::use_item(warrior, item_heal_potion));
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 18u);
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item_heal_potion)->get_count(), 1u);

        EXPECT_FALSE(GameItemManager::use_item(warrior, item_heal_potion));
        EXPECT_EQ(GameItemManager::convert_item_to_potion(item_heal_potion)->get_count(), 1u);
    }

    TEST(GameItemManagerTest, AddToInventory) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_heal_potion = GameItemManager::generate_item("Heal Potion", 6u, 2u);
        ASSERT_TRUE(GameItemManager::add_to_inventory(warrior, item_heal_potion));
        ASSERT_EQ(warrior.get_inventory().size(), 1);

        warrior.get_m_character_ptr()->get_hit_point()->reduce_current_point(10u);
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 8u);

        EXPECT_TRUE(GameItemManager::use_item(warrior, warrior.get_inventory().at(0)));
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 14u);

        EXPECT_TRUE(GameItemManager::use_item(warrior, warrior.get_inventory().at(0)));
        EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 18u);
        EXPECT_EQ(warrior.get_inventory().size(), 0);
    }

    TEST(GameItemManagerTest, CleanupInventory) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        std::unique_ptr<GameItem> item_heal_potion = GameItemManager::generate_item("Heal Potion", 6u, 2u);

        GameItemManager::add_to_inventory(warrior, item_heal_potion);
        ASSERT_EQ(warrior.get_inventory().size(), 1);

        warrior.get_inventory().at(0)->mark_for_deletion();
        GameItemManager::cleanup_inventory(warrior);
        EXPECT_EQ(warrior.get_inventory().size(), 0);
    }

    // The following tests are for the PointPool class.
    TEST(PointPoolTest, DefaultConstructor) {
        PointPool pool;
        EXPECT_EQ(pool.get_current_point(), 0);
        EXPECT_EQ(pool.get_max_point(), 0);
    }

    TEST(PointPoolTest, ParameterizedConstructor) {
        PointPool pool(50, 100);
        EXPECT_EQ(pool.get_current_point(), 50);
        EXPECT_EQ(pool.get_max_point(), 100);
    }

    TEST(PointPoolTest, ConstructorCurrentExceedsMax) {
        PointPool pool(150, 100);
        EXPECT_EQ(pool.get_current_point(), 100);
        EXPECT_EQ(pool.get_max_point(), 100);
    }

    TEST(PointPoolTest, IsFullFunction) {
        PointPool pool1(100, 100);
        EXPECT_TRUE(pool1.is_full());

        PointPool pool2(50, 100);
        EXPECT_FALSE(pool2.is_full());
    }

    TEST(PointPoolTest, SetMaxPoint) {
        PointPool pool(50, 100);

        EXPECT_TRUE(pool.set_max_point(200));
        EXPECT_EQ(pool.get_max_point(), 200);
        EXPECT_EQ(pool.get_current_point(), 50);

        EXPECT_TRUE(pool.set_max_point(25));
        EXPECT_EQ(pool.get_max_point(), 25);
        EXPECT_EQ(pool.get_current_point(), 25);

        EXPECT_FALSE(pool.set_max_point(0));
        EXPECT_EQ(pool.get_max_point(), 25);
    }

    TEST(PointPoolTest, IncreaseCurrentPoint) {
        PointPool pool(50, 100);

        pool.increase_current_point(25);
        EXPECT_EQ(pool.get_current_point(), 75);

        pool.increase_current_point(50);  // Try exceed max
        EXPECT_EQ(pool.get_current_point(), 100);

        pool.increase_current_point(0);   // Zero increase
        EXPECT_EQ(pool.get_current_point(), 100);
    }

    TEST(PointPoolTest, ReduceCurrentPoint) {
        PointPool pool(50, 100);

        pool.reduce_current_point(20);
        EXPECT_EQ(pool.get_current_point(), 30);

        pool.reduce_current_point(30);    // Reduce to zero
        EXPECT_EQ(pool.get_current_point(), 0);

        pool.reduce_current_point(50);    // Try reduce below zero
        EXPECT_EQ(pool.get_current_point(), 0);

        pool.reduce_current_point(0);     // Zero reduction
        EXPECT_EQ(pool.get_current_point(), 0);
    }

    TEST(PointPoolTest, CurrentPointEdgeCases) {
        PointPool pool(100, 100);

        pool.reduce_current_point(100);   // Full to zero
        EXPECT_EQ(pool.get_current_point(), 0);

        pool.increase_current_point(100); // Zero to full
        EXPECT_EQ(pool.get_current_point(), 100);
        EXPECT_TRUE(pool.is_full());
    }

    // The following tests are for the Role class.
    TEST(RoleTest, ConstructorAndDeletions) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        EXPECT_NE(warrior.get_m_character_ptr(), nullptr);
    }

    TEST(RoleTest, CharacterBasics) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        EXPECT_EQ(warrior.get_m_character_ptr()->get_class_name(), "Warrior");
        EXPECT_EQ(warrior.get_m_character_ptr()->get_current_level(), 1);
        EXPECT_NE(warrior.get_m_character_ptr()->get_hit_point(), nullptr);
    }

    TEST(RoleTest, InventoryOperations) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        EXPECT_EQ(warrior.get_inventory().size(), 0);
    }

    TEST(RoleTest, ArmorEquipment) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });

        EXPECT_EQ(warrior.get_armor_at(ArmorSlot::head), nullptr);
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        EXPECT_NE(warrior.get_armor_at(ArmorSlot::head), nullptr);
        EXPECT_EQ(warrior.get_armor_at(ArmorSlot::head)->get_m_item_ptr()->get_name(), "Helmet");
    }

    TEST(RoleTest, MeleeWeaponEquipment) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{}, true, 10u, 20u);

        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::melee), nullptr);
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));
        EXPECT_NE(warrior.get_weapon_at(WeaponSlot::melee), nullptr);
        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::melee)->get_m_item_ptr()->get_name(), "Sword");

        for (int i = 0u; i < 100u; ++i) {
			auto melee_damage = warrior.get_melee_damage();
			auto ranged_damage = warrior.get_ranged_damage();
            EXPECT_EQ(ranged_damage, 1u);
            EXPECT_GE(melee_damage, 13u);
            EXPECT_LE(melee_damage, 23u);
        }
    }

    TEST(RoleTest, RangedWeaponEquipment) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto bow = GameItemManager::generate_item("Bow", WeaponSlot::ranged, BaseStat{}, true, 8u, 15u);

        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::ranged), nullptr);
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, bow));
        EXPECT_NE(warrior.get_weapon_at(WeaponSlot::ranged), nullptr);
        EXPECT_EQ(warrior.get_weapon_at(WeaponSlot::ranged)->get_m_item_ptr()->get_name(), "Bow");

        for (int i = 0u; i < 100u; ++i) {
            auto melee_damage = warrior.get_melee_damage();
            auto ranged_damage = warrior.get_ranged_damage();
            EXPECT_EQ(melee_damage, 3u);
            EXPECT_GE(ranged_damage, 9u);
            EXPECT_LE(ranged_damage, 16u);
        }
    }

    TEST(RoleTest, StatCalculationsSingleBuff) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto base_str = warrior.get_total_strength();
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{3u, 3u, 3u, 3u, 3u}, true, 10u, 20u);
        Buff buff{ BaseStat{ 5u, 4u, 3u, 2u, 1u }, "Test Buff", false, 3 };

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));
        warrior.apply_buff(buff);

        EXPECT_EQ(warrior.get_m_buffs().size(), 1);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 3);
        EXPECT_EQ(warrior.get_total_strength(), 19u);
        EXPECT_EQ(warrior.get_total_intelligence(), 14u);
        EXPECT_EQ(warrior.get_total_agility(), 13u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 10u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 9u);
    }

    TEST(RoleTest, StatCalculationsSingleDebuff) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto base_str = warrior.get_total_strength();
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 3u, 3u, 3u, 3u, 3u }, true, 10u, 20u);
        Buff debuff1{ BaseStat{ 10u, 10u, 10u, 10u, 10u }, "Debuff1", true, 3 };

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));
        warrior.apply_buff(debuff1);

        EXPECT_EQ(warrior.get_m_buffs().size(), 1);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 3);
        EXPECT_EQ(warrior.get_total_strength(), 4u);
        EXPECT_EQ(warrior.get_total_intelligence(), 0u);
        EXPECT_EQ(warrior.get_total_agility(), 0u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 0u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 0u);
    }

    TEST(RoleTest, StatCalculationsMultipleBuffs) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto base_str = warrior.get_total_strength();
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 3u, 3u, 3u, 3u, 3u }, true, 10u, 20u);
        Buff buff1{ BaseStat{ 5u, 4u, 3u, 2u, 1u }, "Buff1", false, 3 };
        Buff buff2{ BaseStat{ 2u, 2u, 2u, 2u, 2u }, "Buff2", false, 3 };

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));
        warrior.apply_buff(buff1);
        warrior.apply_buff(buff2);

        EXPECT_EQ(warrior.get_m_buffs().size(), 2);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 3);
        EXPECT_EQ(warrior.get_total_strength(), 21u);
        EXPECT_EQ(warrior.get_total_intelligence(), 16u);
        EXPECT_EQ(warrior.get_total_agility(), 15u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 12u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 11u);

        Buff duplicate_buff1{ BaseStat{ 5u, 4u, 3u, 2u, 1u }, "Buff1", false, 5 };
        warrior.apply_buff(duplicate_buff1);

        EXPECT_EQ(warrior.get_m_buffs().size(), 2);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 5);
        EXPECT_EQ(warrior.get_total_strength(), 21u);
        EXPECT_EQ(warrior.get_total_intelligence(), 16u);
        EXPECT_EQ(warrior.get_total_agility(), 15u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 12u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 11u);
    }

    TEST(RoleTest, StatCalculationsMultipleDebuffs) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto base_str = warrior.get_total_strength();
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 3u, 3u, 3u, 3u, 3u }, true, 10u, 20u);
        Buff debuff1{ BaseStat{ 5u, 4u, 3u, 2u, 1u }, "Debuff1", true, 3 };
        Buff debuff2{ BaseStat{ 8u, 8u, 8u, 8u, 8u }, "Debuff2", true, 3 };

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));
        warrior.apply_buff(debuff1);
        warrior.apply_buff(debuff2);

        EXPECT_EQ(warrior.get_m_buffs().size(), 2);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 3);
        EXPECT_EQ(warrior.get_total_strength(), 1u);
        EXPECT_EQ(warrior.get_total_intelligence(), 0u);
        EXPECT_EQ(warrior.get_total_agility(), 0u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 0u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 0u);

        Buff duplicate_debuff1{ BaseStat{ 5u, 4u, 3u, 2u, 1u }, "Debuff1", true, 5 };
        warrior.apply_buff(duplicate_debuff1);

        EXPECT_EQ(warrior.get_m_buffs().size(), 2);
        EXPECT_EQ(warrior.get_m_buffs().at(0).m_duration, 5);
        EXPECT_EQ(warrior.get_total_strength(), 1u);
        EXPECT_EQ(warrior.get_total_intelligence(), 0u);
        EXPECT_EQ(warrior.get_total_agility(), 0u);
        EXPECT_EQ(warrior.get_total_physical_defense(), 0u);
        EXPECT_EQ(warrior.get_total_magic_resistance(), 0u);
    }

	// The following tests are for the Monster class.
    TEST(MonsterTest, Construction) {
        Monster monster(std::make_unique<PointPool>(10u, 10u), 5u, 7u);

        EXPECT_EQ(monster.get_hit_point()->get_current_point(), 10u);
        EXPECT_EQ(monster.get_hit_point()->get_max_point(), 10u);

        for (int i = 0u; i < 100u; ++i) {
            auto damage = monster.get_damage();
            EXPECT_GE(damage, 5u);
            EXPECT_LE(damage, 7u);
        }
    }

    TEST(MonsterTest, EdgeCases) {
        Monster monster(std::make_unique<PointPool>(0u, 10u), 0u, 0u);

        EXPECT_EQ(monster.get_hit_point()->get_current_point(), 0u);
        EXPECT_EQ(monster.get_damage(), 0u);
    }

	// The following tests are for the battle between a warrior and a monster.
	TEST(BattleTest, LevelOneWarriorVsMonster) {
		Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
		auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
		auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 3u, 3u, 3u, 3u, 3u }, true, 2u, 4u);

		ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
		ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));

		Monster monster(std::make_unique<PointPool>(30u, 30u), 5u, 7u);
		
        while (warrior.get_m_character_ptr()->get_hit_point()->get_current_point() > 0 && monster.get_hit_point()->get_current_point() > 0) {
			monster.get_hit_point()->reduce_current_point(warrior.get_melee_damage());
			warrior.get_m_character_ptr()->get_hit_point()->reduce_current_point(monster.get_damage());
		}

		EXPECT_EQ(warrior.get_m_character_ptr()->get_hit_point()->get_current_point(), 0u);
	}

    TEST(BattleTest, LevelThreeWarriorVsMonster) {
        Role warrior{ std::unique_ptr<Character>{new Warrior{}} };
        auto helmet = GameItemManager::generate_item("Helmet", ArmorSlot::head, BaseStat{ 5u,5u,5u,5u,5u });
        auto sword = GameItemManager::generate_item("Sword", WeaponSlot::melee, BaseStat{ 3u, 3u, 3u, 3u, 3u }, true, 2u, 4u);
        warrior.get_m_character_ptr()->gain_experience(300u);

        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, helmet));
        ASSERT_TRUE(GameItemManager::equip_equipment(warrior, sword));

        Monster monster(std::make_unique<PointPool>(30u, 30u), 5u, 7u);

        while (warrior.get_m_character_ptr()->get_hit_point()->get_current_point() > 0 && monster.get_hit_point()->get_current_point() > 0) {
            monster.get_hit_point()->reduce_current_point(warrior.get_melee_damage());
            warrior.get_m_character_ptr()->get_hit_point()->reduce_current_point(monster.get_damage());
        }

        EXPECT_EQ(monster.get_hit_point()->get_current_point(), 0u);
    }
} // namespace DemoRPGUnitTests;
