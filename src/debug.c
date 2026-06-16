/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:20:57 by slambert          #+#    #+#             */
/*   Updated: 2026/06/16 15:42:17 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_keys(t_god *god)
{
	static long long x = 0;
	// if (x++ % 5 != 0)     //only print each 50th function call
	// 	return ;
	printf("Key: W | Status: %d\n", god->key_w);
	printf("Key: A | Status: %d\n", god->key_a);
	printf("Key: S | Status: %d\n", god->key_s);
	printf("Key: D | Status: %d\n", god->key_d);
	printf("Key: Left | Status: %d\n", god->key_left);
	printf("Key: Right | Status: %d\n", god->key_right);
	printf("Player x coordinate: %.2f\n", god->player_x);
	printf("Player y coordinate: %.2f\n", god->player_y);
	printf("Player Angle: %.3f\n", god->player_angle);
    printf("Player Angle min: %.3f\n", god->player_angle_min);
    printf("Player Angle max: %.3f\n", god->player_angle_max);
}

int **create_sample_map(t_god *p_god)
{
    int rows = 7;
    int cols = 6;
	
	p_god->rows = rows;
	p_god->cols = cols;
	//Player currently is 2
    int static_map[7][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 2, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1}
    };
    int **map = (int**)ft_calloc(rows + 1, sizeof(int*));
    if (!map)
        return NULL;
    for (int i = 0; i < rows; i++)
    {
        map[i] = (int*)ft_calloc(cols, sizeof(int));
        if (!map[i])
            return NULL; 
        for (int j = 0; j < cols; j++)
            map[i][j] = static_map[i][j];
    }
    return map;
}