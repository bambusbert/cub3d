/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_db_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 00:43:51 by fsitter           #+#    #+#             */
/*   Updated: 2026/07/29 15:30:43 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_db.h"

static bool	hashmap_init(t_db *db, uint32_t initial_slots);
static bool	arena_init(t_db *db, uint32_t initial_arena_size);

bool	db_init(t_db *db, uint32_t initial_slots, uint32_t initial_arena_size)
{
	if (hashmap_init(db, initial_slots) == false)
		return (false);
	if (arena_init(db, initial_arena_size) == false)
	{
		free_db(db);
		return (false);
	}
	return (true);
}

static bool	hashmap_init(t_db *db, uint32_t initial_slots)
{
	db->hmap_cap = MIN_ARENA_SLOTS;
	db->hmap_size = 0;
	while (db->hmap_cap < initial_slots)
		db->hmap_cap <<= 1;
	if (allocate_slots(db, db->hmap_cap) == false)
		return (false);
	return (true);
}

static bool	arena_init(t_db *db, uint32_t initial_arena_size)
{
	db->arena_cap = MIN_ARENA_SIZE;
	while (db->arena_cap < initial_arena_size)
		db->arena_cap <<= 1;
	db->data_arena = malloc(db->arena_cap);
	if (!db->data_arena)
		return (false);
	db->arena_head = 0;
	return (true);
}

bool	allocate_slots(t_db *db, uint32_t cap)
{
	size_t	total_hashmap_size;
	void	*total_block;
	uint8_t	*ptr;

	total_hashmap_size = ((sizeof(uint32_t) * 3)) * cap;
	total_block = ft_calloc(total_hashmap_size, 1);
	if (!total_block)
		return (false);
	ptr = (uint8_t *)total_block;
	db->slots.key = (uint32_t *)ptr;
	ptr += sizeof(uint32_t) * cap;
	db->slots.val_start = (uint32_t *)ptr;
	ptr += sizeof(uint32_t) * cap;
	db->slots.val_lenght = (uint32_t *)ptr;
	db->hmap_cap = cap;
	return (true);
}

void	free_db(t_db *db)
{
	if (!db)
		return ;
	if (db->slots.key)
	{
		free((void *)db->slots.key);
		db->slots.key = NULL;
		db->slots.val_start = NULL;
		db->slots.val_lenght = NULL;
		db->hmap_cap = 0;
		db->hmap_size = 0;
	}
	if (db->data_arena)
	{
		free(db->data_arena);
		db->data_arena = NULL;
		db->arena_cap = 0;
		db->arena_head = 0;
	}
	return ;
}
