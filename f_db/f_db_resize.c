/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_db_resize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:16:50 by fsitter           #+#    #+#             */
/*   Updated: 2026/07/29 15:16:51 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_db.h"
#include <bits/types/struct_itimerspec.h>
#include <stdint.h>

bool	db_resize_slots(t_db *db);
bool	db_resize_arena(t_db *db);
void	db_copy_dict_to_new(t_db *db, uint32_t old_cap, t_hashmap *old_slots);

bool	db_resize_if(t_db *db, uint32_t needed_bytes)
{
	if ((db->hmap_size + 1) * 3 > db->hmap_cap * 2)
	{
		if (db_resize_slots(db) == false)
			return (false);
	}
	while (db->arena_head + needed_bytes > db->arena_cap)
	{
		if (db_resize_arena(db) == false)
			return (false);
	}
	return (true);
}

bool	db_resize_slots(t_db *db)
{
	t_hashmap	old_slots;

	old_slots = db->slots;
	if (allocate_slots(db, db->hmap_cap * 2) == false)
		return (false);
	db_copy_dict_to_new(db, db->hmap_cap / 2, &old_slots);
	free(old_slots.key);
	return (true);
}

void	db_copy_dict_to_new(t_db *db, uint32_t old_cap, t_hashmap *old_slots)
{
	uint32_t	old_i;
	uint32_t	new_i;
	const char	*key;

	old_i = 0;
	while (old_i < old_cap)
	{
		if (old_slots->val_lenght[old_i] != 0)
		{
			key = &db->data_arena[old_slots->key[old_i]];
			new_i = f_db_hash0(key) & (db->hmap_cap - 1);
			while (db->slots.val_lenght[new_i] != 0)
				new_i = (new_i + 1) & (db->hmap_cap - 1);
			db->slots.key[new_i] = old_slots->key[old_i];
			db->slots.val_start[new_i] = old_slots->val_start[old_i];
			db->slots.val_lenght[new_i] = old_slots->val_lenght[old_i];
		}
		old_i++;
	}
}

bool	db_resize_arena(t_db *db)
{
	uint32_t	new_size;
	void		*old_block;

	new_size = db->arena_cap * 2;
	old_block = (void *)db->data_arena;
	db->data_arena = malloc(new_size);
	if (!db->data_arena)
		return (false);
	ft_memcpy(db->data_arena, old_block, db->arena_cap);
	db->arena_cap = new_size;
	free(old_block);
	return (true);
}

// Funktion um eine Hashmap aus einer Arena zu machen
// void    db_load_keyring_from_arena(t_db *db);
// void db_load_keyring_from_arena(t_db *db)
// {
//     uint32_t i;
//     const char *key;
//     uint32_t key_len;
//     uint32_t val_offset;
//     uint32_t val_len;

//     i = 0;
//     db->hmap_size = 0;
//     while (i < db->arena_head)
//     {
//         key = &db->data_arena[i];
//         key_len = ft_strlen(key);
//         val_offset = i + key_len + 1;
//         val_len = ft_strlen(&db->data_arena[val_offset]);
//         if (db_insert_index(db, key, val_offset, val_len))
//             db->hmap_size++;
//         i = val_offset + val_len + 1;
//     }
// }