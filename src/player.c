/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 17:07:29 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/06 17:07:31 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rogue.h"

static int	move(int dir)
{
	int dr, dc, moved;

	moved = 0;
	switch (dir)
	{
		case 0:
			dr = -1;
			dc = 0;
			break;
		case 1:
			dr = 0;
			dc = 1;
			break;
		case 2:
			dr = 1;
			dc = 0;
			break;
		case 3:
			dr = 0;
			dc = -1;
			break;
		default:
			return (0);
			break;
	}
	if (!GETL(P_R + dr, P_C + dc).solid)
	{
		g_player.loc->trailindex = TRAIL_PLAYER;
		P_R += dr;
		P_C += dc;
		g_player.loc = &GETL(P_R, P_C);
		moved = 1;
	}
	if (moved && GETL(P_R, P_C).has_loot && GETL(P_R, P_C).entity)
	{
		if (((t_loot*)GETL(P_R, P_C).entity)->type == UP_WITNESS)
			g_player.witness += 2;
		else if (((t_loot*)GETL(P_R, P_C).entity)->type == UP_SANITY)
			g_player.sanity += (g_player.san_max - g_player.sanity) / 2;
		else if (((t_loot*)GETL(P_R, P_C).entity)->type == UP_ACTIONS)
			g_player.actions++;
		else if (((t_loot*)GETL(P_R, P_C).entity)->type == UP_XP)
		{
			g_player.xp += 3;
			if (g_player.xp >= g_player.xp_til_ding)
			{
				g_player.level++;
				g_player.xp_til_ding += g_player.level + 2;
				g_player.xp = 0;
				g_player.san_max += g_player.level + 4;
				g_player.sanity = g_player.san_max;
				if (g_player.cur_health < g_player.max_health)
				{
					g_player.max_health += g_player.level + 1;
					g_player.cur_health += (g_player.max_health -
						g_player.cur_health) / 2;
				}
				else if (g_player.cur_health == g_player.max_health)
				{
					g_player.max_health += g_player.level + 1;
					g_player.cur_health = g_player.max_health;
				}
			}
		}
		else if (((t_loot*)GETL(P_R, P_C).entity)->type == UP_HEALTH)
		{
			if (g_player.cur_health < g_player.max_health)
			{
				g_player.cur_health += 2;
				if (g_player.cur_health > g_player.max_health)
					g_player.cur_health = g_player.max_health;
			}
			else
			{
				g_player.max_health++;
				g_player.cur_health++;
			}
		}
		GETL(P_R, P_C).entity = 0;
		GETL(P_R, P_C).has_loot = 0;
	}
	return (moved);
}

void		parser(char *s)
{
	char	c;
	int		dr, dc, i, moved, dir;

	i = 0;
	while (*s && i++ < (int)g_player.actions)
	{
		moved = 0;
		switch (*s)
		{
			case 'w':
			case 'W':
				move(0);
				break;
			case 'a':
			case 'A':
				move(3);
				break;
			case 's':
			case 'S':
				move(2);
				break;
			case 'd':
			case 'D':
				move(1);
				break;
			case 'r':
			case 'R':
				c = *(++s);
				switch (c)
				{
					case 'w':
					case 'W':
						dir = 0;
						break;
					case 'a':
					case 'A':
						dir = 3;
						break;
					case 's':
					case 'S':
						dir = 2;
						break;
					case 'd':
					case 'D':
						dir = 1;
						break;
					default:
						dir = -1;
						break;
				}
				if (dir == -1)
					break;
				do
				{
					moved = move(dir);
				} while (moved);
				break;
			case 'o':
			case 'O':
				c = *(++s);
				switch (c)
				{
					case 'w':
					case 'W':
						dr = -1;
						dc = 0;
						break;
					case 'a':
					case 'A':
						dr = 0;
						dc = -1;
						break;
					case 's':
					case 'S':
						dr = 1;
						dc = 0;
						break;
					case 'd':
					case 'D':
						dr = 0;
						dc = 1;
						break;
					default:
						dr = 0;
						dc = 0;
						break;
				}
				if (ABS(dr + dc) != 1)
					break;
				if (GETL(P_R + dr, P_C + dc).tiletype == TILE_DOOR_C)
				{
					GETL(P_R + dr, P_C + dc).tiletype = TILE_DOOR_O;
					GETL(P_R + dr, P_C + dc).solid = 0;
				}
				break;
			case 'c':
			case 'C':
				c = *(++s);
				switch (c)
				{
					case 'w':
					case 'W':
						dr = -1;
						dc = 0;
						break;
					case 'a':
					case 'A':
						dr = 0;
						dc = -1;
						break;
					case 's':
					case 'S':
						dr = 1;
						dc = 0;
						break;
					case 'd':
					case 'D':
						dr = 0;
						dc = 1;
						break;
					default:
						dr = 0;
						dc = 0;
						break;
				}
				if (ABS(dr + dc) != 1)
					break;
				if (GETL(P_R + dr, P_C + dc).tiletype == TILE_DOOR_O)
				{
					GETL(P_R + dr, P_C + dc).tiletype = TILE_DOOR_C;
					GETL(P_R + dr, P_C + dc).solid = 1;
				}
				break;
		}
		s++;
	}
}
