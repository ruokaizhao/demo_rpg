#pragma once
#include "equipment.h"
#include <memory>

class Item
{
	friend class ItemGenerator;
public:
	~Item() = default;

	std::unique_ptr<ItemDelegate>& get_m_item_delegate_ptr()
	{
		return m_item_delegate_ptr;
	}

private:
	std::unique_ptr<ItemDelegate> m_item_delegate_ptr;

	Item(std::unique_ptr<ItemDelegate> m_item_delegate_ptr_value) : m_item_delegate_ptr{ std::move(m_item_delegate_ptr_value) } {}
};
