/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_db_set_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:35:40 by fsitter           #+#    #+#             */
/*   Updated: 2026/07/29 15:35:41 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_db.h"

uint32_t	db_write_entry_size(const char *key, const char *value);
bool		db_write(t_db *db, const char *key, const char *value);
bool		db_resize_if(t_db *db, uint32_t needed_bytes);

bool	db_set(t_db *db, const char *key, const char *value)
{
	uint32_t	needed_bytes;
	uint32_t	val_offset;

	needed_bytes = db_write_entry_size(key, value);
	if (db_resize_if(db, needed_bytes) == false)
		return (false);
	val_offset = db->arena_head + ft_strlen(key) + 1;
	if (db_write(db, key, value) == false)
		return (false);
	if (db_insert_index(db, db->arena_head, val_offset, ft_strlen(value)))
		db->hmap_size++;
	db->arena_head += needed_bytes;
	return (true);
}

#include <string.h>

bool	db_insert_index(t_db *db, uint32_t key_offset, uint32_t val_offset,
		uint32_t val_len)
{
	uint32_t	slot;
	bool		is_new;
	const char	*key = &db->data_arena[key_offset];

	slot = f_db_hash0(key) & (db->hmap_cap - 1);
	is_new = true;
	while (db->slots.val_lenght[slot] != 0)
	{
		if (strcmp(&db->data_arena[db->slots.key[slot]], key) == 0)
		{
			is_new = false;
			break ;
		}
		slot = (slot + 1) & (db->hmap_cap - 1);
	}
	db->slots.key[slot] = key_offset;
	db->slots.val_start[slot] = val_offset;
	db->slots.val_lenght[slot] = val_len;
	return (is_new);
}

const char	*db_get(t_db *db, const char *key)
{
	uint32_t	slot;

	if (!db || !key || db->hmap_cap == 0)
		return (NULL);
	slot = f_db_hash0(key) & (db->hmap_cap - 1);
	while (db->slots.val_lenght[slot] != 0)
	{
		if (strcmp(&db->data_arena[db->slots.key[slot]], key) == 0)
			return (&db->data_arena[db->slots.val_start[slot]]);
		slot = (slot + 1) & (db->hmap_cap - 1);
	}
	return (NULL);
}

uint32_t	db_write_entry_size(const char *key, const char *value)
{
	return (ft_strlen(key) + ft_strlen(value) + 2);
}

bool	db_write(t_db *db, const char *key, const char *value)
{
	uint32_t	key_space;
	uint32_t	val_space;

	key_space = ft_strlen(key) + 1;
	val_space = ft_strlen(value) + 1;
	if (!ft_memcpy(&db->data_arena[db->arena_head], key, key_space))
		return (false);
	if (!ft_memcpy(&db->data_arena[db->arena_head + key_space], value,
			val_space))
		return (false);
	return (true);
}

// bool db_insert_index(t_db *db, const char *key, 
// uint32_t val_offset, uint32_t val_len)
// {
//     uint32_t slot;
//     bool is_new;

//     slot = f_db_hash0(key) & (db->hmap_cap - 1);
//     is_new = true;
//     while (db->slots.key[slot] != NULL)
//     {
//         if (strcmp(db->slots.key[slot], key) == 0) // TODO
//         {
//             is_new = false;
//             break ;
//         }
//         slot = (slot + 1) & (db->hmap_cap - 1);
//     }
//     db->slots.key[slot] = key; // index
//     db->slots.val_start[slot] = val_offset;
//     db->slots.val_lenght[slot] = val_len;
//     return (is_new);
// }