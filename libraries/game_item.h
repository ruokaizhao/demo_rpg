#pragma once
#include "item.h"

class GameItem
{
	friend class GameItemManager;

public:
	~GameItem() = default;

	const std::shared_ptr<Item> &get_m_item_ptr() const
	{
		return m_item_ptr;
	}

	bool is_marked_for_deletion() const
	{
		return m_marked_for_deletion;
	}

	void mark_for_deletion()
	{
		m_marked_for_deletion = true;
	}

private:
	std::shared_ptr<Item> m_item_ptr;
	bool m_marked_for_deletion{false};

	GameItem(std::shared_ptr<Item> m_item_ptr_value) : m_item_ptr{std::move(m_item_ptr_value)} {}
};
