/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_db_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:17:22 by fsitter           #+#    #+#             */
/*   Updated: 2026/07/29 15:31:19 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_db.h"

uint32_t	f_db_hash0(const char *key)
{
	uint32_t	hash;

	hash = 5381;
	while (*key)
		hash = ((hash << 5) + hash) + (unsigned char)*key++;
	return (hash);
}

uint32_t	f_db_hash1(const char *key)
{
	uint32_t	hash;

	hash = 2166136261U;
	while (*key)
	{
		hash ^= (uint8_t) * key;
		hash *= 16777619U;
		key++;
	}
	return (hash);
}

// TODO eine loeschen