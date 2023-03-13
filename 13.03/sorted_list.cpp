#include "sorted_list.h"

void add(sorted_list *&list, int value)
{
	auto *new_el = new list_elem;
	new_el->x = value;
	list->length++;
	if (!list->first)
		list->first = list->last = new_el;
	else
	{
		if (value <= list->first->x)
		{
			new_el->next = list->first;
			list->first->prev = new_el;
			list->first = new_el;
		}
		else if (value >= list->last->x)
		{
			new_el->prev = list->last;
			list->last->next = new_el;
			list->last = new_el;
		}
		else
		{
			auto *curr = list->first;
			while (curr->next->x < value)
			{
				curr = curr->next;
			}
			curr->next->prev = new_el;
			new_el->next = curr->next;
			curr->next = new_el;
			new_el->prev = curr;
		}
	}
}

bool get(sorted_list *list, int index, int &value)
{
	if (index < 0 || index >= list->length)
		return false;
	if (index == 0)
	{
		value = list->first->x;
		return true;
	}
	else if (index == list->length - 1)
	{
		value = list->last->x;
		return true;
	}
	else
	{
		auto center = (list->length - 1) / 2;
		bool forward = index <= center;
		auto *curr = (forward) ? list->first->next : list->last->prev;
		if (!forward)
			index = list->length - index - 1;
		int cnt = 0;
		while (++cnt < index)
			curr = (forward) ? curr->next : curr->prev;
		value = curr->x;
		return true;
	}
}

bool contains(sorted_list *list, int value)
{
	if (!list->first || list->first->x > value || list->last->x < value)
		return false;
	auto *curr = list->first;
	while (curr->x < value)
	{
		curr = curr->next;
	}
	return curr->x == value;
}

bool remove_all(sorted_list *&list, int value)
{
	if (!list->first || list->first->x > value || list->last->x < value)
		return false;
	auto *curr = list->first;
	while (curr->x <= value)
	{
		if (curr->x == value)
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			auto *old_el = curr;
			curr = curr->next;
			delete old_el;
		}
		else
			curr = curr->next;
	}
}
bool remove(sorted_list *&list, int value)
{
	if (!list->first || list->first->x > value || list->last->x < value)
		return false;
	auto *curr = list->first;
	while (curr->x <= value)
	{
		if (curr->x == value)
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			auto *old_el = curr;
			curr = curr->next;
			delete old_el;
			return true;
		}
		else
			curr = curr->next;
	}
	return false;
}
bool remove_at(sorted_list *list, int index)
{
	if (index < 0 || index >= list->length)
		return false;
	if (index == 0)
	{
		auto first = list->first;
		list->first = first != nullptr ? first->next : nullptr;
		if (list->first != nullptr) {
			list->first->prev = nullptr;
		}
		delete first;
		return true;
	}
	else if (index == list->length - 1)
	{
		auto last = list->last;
		list->last = last != nullptr ? last->prev : nullptr;
		if (list->last != nullptr) {
			list->last->next = nullptr;
		}
		delete last;
		return true;
	}
	else
	{
		auto center = (list->length - 1) / 2;
		bool forward = index <= center;
		auto *curr = (forward) ? list->first->next : list->last->prev;
		if (!forward)
			index = list->length - index - 1;
		int cnt = 0;
		while (++cnt < index)
			curr = (forward) ? curr->next : curr->prev;
		// We are working in the middle of the list, this conditions must be satisfied
		assert(curr != nullptr);
		assert(curr->prev != nullptr);
		assert(curr->next != nullptr);
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		return true;
	}
}