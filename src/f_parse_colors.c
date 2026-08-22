/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:12:51 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/20 17:57:24 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

bool f_extract_colors(t_db *db, t_color *colors);
bool f_border_control(t_color *colors);
char **f_free_rgb(char **rgb);

bool f_init_colors(t_color *colors)
{
    colors[0].key = 'F';
    colors[1].key = 'C';
    return (true);
}

bool f_parse_colors(t_db *db, t_color *colors)
{
    f_init_colors(colors);
    if (f_extract_colors(db, colors) == false)
        return (false);
    return (f_border_control(colors));
}

bool f_border_control(t_color *colors)
{
    int i;

    i = 0;
    while (i < 2)
    {
        if (colors[i].r == 600)
            return (false);
        if (colors[i].g == 600)
            return (false);
        if (colors[i].b == 600)
            return (false);
        i++;
    }
    return (true);
}


bool f_extract_colors(t_db *db, t_color *colors)
{
    char key_str[2];
    const char *val;
    char **rgb;
    int i;
    
    key_str[1] = '\0';
    i = -1;
    while (++i < 2)
    {
        key_str[0] = colors[i].key;
        val = db_get(db, key_str);
        if (!val)
            return (false);
        rgb = ft_split(val, ',');
        if (!rgb)
            return (ft_putstr_fd("Error\nAllocation.\n", 2), false);
        if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
            return (ft_putstr_fd("Error\nColors wrong.\n", 2), f_free_rgb(rgb), false);
        colors[i].r = f_catch_num(rgb[0]);
        colors[i].g = f_catch_num(rgb[1]);
        colors[i].b = f_catch_num(rgb[2]);
        rgb = f_free_rgb(rgb);
    }
    return (true);
}

char **f_free_rgb(char **rgb)
{
    int i;
    
    i = 0;
    if (!rgb)
        return (NULL);
    while (rgb[i])
    {
        free (rgb[i]);
        i++;
    }
    free (rgb);
    return (NULL);
}
