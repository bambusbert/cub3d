/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_db.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:38:49 by fsitter           #+#    #+#             */
/*   Updated: 2026/07/29 15:41:35 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_DB_H
# define F_DB_H

// 1024
# define MIN_ARENA_SIZE 1024
// 16
# define MIN_ARENA_SLOTS 16

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>

// struct prototypes
typedef struct s_hashmap	t_hashmap;
typedef struct s_db			t_db;

// prototypes

// f_db_hash.c
uint32_t					f_db_hash0(const char *key);
uint32_t					f_db_hash1(const char *key);

// f_db_init.c
bool						db_init(t_db *db, uint32_t initial_slots,
								uint32_t inital_arena_size);
bool						allocate_slots(t_db *db, uint32_t cap);
void						free_db(t_db *db);

// f_db_resize.c
bool						db_resize_if(t_db *db, uint32_t needed_bytes);

// f_db_set.c
bool						db_set(t_db *db, const char *key,
								const char *value);
bool						db_insert_index(t_db *db, uint32_t key_offset,
								uint32_t val_offset, uint32_t val_len);
const char					*db_get(t_db *db, const char *key);

// structs
typedef struct s_hashmap
{
	uint32_t				*key;
	uint32_t				*val_start;
	uint32_t				*val_lenght;
}							t_hashmap;

typedef struct s_db
{
	char					*data_arena;
	uint32_t				arena_cap;
	uint32_t				arena_head;

	t_hashmap				slots;
	uint32_t				hmap_cap;
	uint32_t				hmap_size;
}							t_db;

// TODO umrechnungen
typedef union u_ret
{
	char					*raw;
	int						as_int;
}							t_return;

#endif