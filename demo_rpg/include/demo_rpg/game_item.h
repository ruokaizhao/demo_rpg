#pragma once
#include "equipment.h"
#include <ostream>

class Item
{
	friend class ItemManager;
public:
	~Item() = default;

	const std::unique_ptr<ItemDelegate>& get_m_item_delegate_ptr() const
	{
		return m_item_delegate_ptr;
	}

	bool is_marked_for_deletion() const
	{
		return m_marked_for_deletion;
	}

	void mark_for_deletion()
	{
		m_marked_for_deletion = true;
	}

	friend std::ostream& operator<<(std::ostream& os, Item& item)
	{
		if (dynamic_cast<Armor*>(item.get_m_item_delegate_ptr().get()) != nullptr)
		{
			auto armor = std::unique_ptr<Armor>(static_cast<Armor*>(item.get_m_item_delegate_ptr().get()));
			os << armor->get_name() << ":" << '\n';
			os << "  Armor: " << armor->get_stat().m_physical_defense << '\n';

			armor.release();

			return os;
		}
		else if (dynamic_cast<Weapon*>(item.get_m_item_delegate_ptr().get()) != nullptr)
		{
			auto weapon = std::unique_ptr<Weapon>(static_cast<Weapon*>(item.get_m_item_delegate_ptr().get()));
			os << weapon->get_name() << ":" << '\n'
				<< "  Min Damage: " << weapon->m_min_damage << '\n'
				<< "  Max Damage: " << weapon->m_max_damage << '\n';

			weapon.release();

			return os;
		}
		else if (dynamic_cast<Potion*>(item.get_m_item_delegate_ptr().get()) != nullptr)
		{
			auto potion = std::unique_ptr<Potion>(static_cast<Potion*>(item.get_m_item_delegate_ptr().get()));
			os << potion->get_name() << ":" << '\n'
				<< "  Hit Point: " << potion->get_hit_point() << '\n'
				<< "  Count: " << potion->get_count() << '\n';

			potion.release();

			return os;
		}
		else
		{
			os << "Unknown item type." << '\n';
			return os;
		}
	}

private:
	std::unique_ptr<ItemDelegate> m_item_delegate_ptr;
	bool m_marked_for_deletion{ false };

	Item(std::unique_ptr<ItemDelegate> m_item_delegate_ptr_value) : m_item_delegate_ptr{ std::move(m_item_delegate_ptr_value) } {}
};
