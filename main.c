/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:17:28 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/26 12:17:29 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rogue.h"
#include <stdio.h>

#define BUF_SIZE 98304

size_t			g_cols;
size_t			g_rows;
t_loc			*g_locs;
t_player		g_player;

char			**g_table;

static void		init_locs(void)
{
	size_t	r;
	size_t	c;

	r = -1;
	while (++r < g_rows)
	{
		c = -1;
		while (++c < g_cols)
		{
			GETL(r, c).entity = 0;
			GETL(r, c).tiletype = TILE_FLOOR;
			GETL(r, c).seen = 0;
			if (!r || !c || r == g_rows - 1 || c == g_cols - 1)
			{
				GETL(r, c).tiletype = TILE_EDGE;
				GETL(r, c).solid = 1;
				GETL(r, c).seen = 1;
			}
			else
				GETL(r, c).solid = 0;
			GETL(r, c).visible = 0;
			GETL(r, c).wall_adjacent = 0;
			GETL(r, c).has_loot = 0;
			GETL(r, c).has_mob = 0;
		}
	}
	//	Not really initializing a location but a good place to initialize
	//	my UI.
	g_table = (char**)malloc(sizeof(char*) * 8);
	g_table[0] = ft_strdup("	Queue up actions then hit enter:");
	g_table[1] = ft_strdup("	Use [W][A][S][D] to move one space;");
	g_table[2] = ft_strdup(
		"	Use [R] and then a wasd direction to run in that direction;");
	g_table[3] = ft_strdup(
		"	Use [O] and [C], then a direction to open or close a door.");
	g_table[4] = ft_strdup("	Every turn will cost you sanity...");
	g_table[5] = ft_strdup(
		"	And you can only take as many actions as you have actions.");
	g_table[6] = ft_strdup(
		"	Level up to reset and increase your sanity!");
	g_table[7] = 0;
}

static void		display_map(void)
{
	int		r, c, i;
	char	*buf;
	char	*icon;

	buf = (char*)malloc(BUF_SIZE);
	buf[0] = 0;
	i = -60;
	r = (int)P_R - 50;
	if (r < 0)
		r = 0;
	while (r < (int)P_R + 50 && r < ROWS)
	{
		c = (int)P_C - 50;
		if (c < 0)
			c = 0;
		while (c < (int)P_C + 50 && c < COLS)
		{
			if (!GETL(r, c).seen)
				icon = LOC_INVIS;
			else if (GETL(r, c).trailindex == 0) //	Seen and not Traily
			{
				if (GETL(r, c).tiletype == TILE_FLOOR)
				{
					if (GETL(r, c).visible)
						icon = LOC_FLOOR_V;
					else
						icon = LOC_FLOOR_S;
				}
				else if (GETL(r, c).tiletype == TILE_WALL)
				{
					if (GETL(r, c).visible)
						icon = LOC_WALL_V;
					else
						icon = LOC_WALL_S;
				}
				else if (GETL(r, c).tiletype == TILE_EDGE)
					icon = LOC_EDGE;
				else if (GETL(r, c).tiletype == TILE_DOOR_O)
				{
					if (GETL(r, c).visible)
						icon = LOC_DOOR_OV;
					else
						icon = LOC_DOOR_OS;
				}
				else if (GETL(r, c).tiletype == TILE_DOOR_C)
				{
					if (GETL(r, c).visible)
						icon = LOC_DOOR_CV;
					else
						icon = LOC_DOOR_CS;
				}
			}
			else //	Seen and yes Traily
			{
				if (GETL(r, c).trailindex == TRAIL_PLAYER)
					icon = PLAYER_TRAIL;
				else if (GETL(r, c).trailindex == TRAIL_SLIME)
					icon = SLIME_TRAIL;
				if (GETL(r, c).trailindex != TRAIL_SLIME)
					GETL(r, c).trailindex = NO_TRAIL;
			}
			if (GETL(r, c).seen && GETL(r, c).has_loot)
			{
				if (GETL(r, c).entity)
				{
					if (((t_loot*)GETL(r, c).entity)->type == UP_WITNESS)
						icon = LOOT_WITNESS;
					else if (((t_loot*)GETL(r, c).entity)->type == UP_SANITY)
						icon = LOOT_SANITY;
					else if (((t_loot*)GETL(r, c).entity)->type == UP_ACTIONS)
						icon = LOOT_ACTIONS;
					else if (((t_loot*)GETL(r, c).entity)->type == UP_XP)
						icon = LOOT_XP;
					else if (((t_loot*)GETL(r, c).entity)->type == UP_HEALTH)
						icon = LOOT_HEALTH;
				}
			}
			if (GETL(r, c).visible && GETL(r, c).has_mob)
			{
				if (GETL(r, c).entity)
				{
					if (((t_mob*)GETL(r, c).entity)->mobtype == MOB_SLIME)
						icon = SPRITE_SLIME;
				}
			}
			if (r == (int)P_R && c == (int)P_C)
				icon = SPRITE_PLAYER;
			strlcat(buf, icon, BUF_SIZE);
			strlcat(buf, " ", BUF_SIZE);
			if (GETL(r, c).visible)
				GETL(r, c).visible = 0;
			c++;
		}
		strlcat(buf, UI_LINE, BUF_SIZE);
		if (i == -19)
		{
			strlcat(buf, UI_XP, BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.xp), BUF_SIZE);
			strlcat(buf, " / ", BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.xp_til_ding), BUF_SIZE);
		}
		else if (i == -18)
		{
			int		j;
			double	disp_frac, play_frac;
			char	*to_add;

			to_add = (char*)malloc(sizeof(char) * 4096);
			to_add[0] = 0;
			strlcat(to_add, "\t", 51);
			j = 0;
			play_frac = (double)g_player.xp /
				(double)g_player.xp_til_ding;
			while (j < 50)
			{
				disp_frac = (double)j / 50.0;
				if (disp_frac < play_frac)
					strlcat(to_add, UI_XP_LINE, 4096);
				else
					strlcat(to_add, UI_XP_LINE_DARK, 4096);
				j++;
			}
			strlcat(buf, to_add, BUF_SIZE);
			bzero(to_add, 4096);
			free(to_add);
		}
		else if (i == -16)
		{
			strlcat(buf, UI_HEALTH, BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.cur_health), BUF_SIZE);
			strlcat(buf, " / ", BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.max_health), BUF_SIZE);
		}
		else if (i == -15)
		{
			int		j;
			double	disp_frac, play_frac;
			char	*to_add;

			to_add = (char*)malloc(sizeof(char) * 4096);
			to_add[0] = 0;
			strlcat(to_add, "\t", 51);
			j = 0;
			play_frac = (double)g_player.cur_health /
				(double)g_player.max_health;
			while (j < 50)
			{
				disp_frac = (double)j / 50.0;
				if (disp_frac < play_frac)
					strlcat(to_add, UI_HEALTH_LINE, 4096);
				else
					strlcat(to_add, UI_HEALTH_LINE_DARK, 4096);
				j++;
			}
			strlcat(buf, to_add, BUF_SIZE);
			bzero(to_add, 4096);
			free(to_add);
		}
		else if (i == -12)
			strlcat(buf,
				"\t___________________________________________________________",
				BUF_SIZE);
		else if (i == -10)
			strlcat(buf, "	\e[1;37mPlayer Statistics: ", BUF_SIZE);
				else if (i == -8)
		{
			strlcat(buf, "	\e[1;38;5;46mActions: ", BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.actions), BUF_SIZE);
			strlcat(buf, " / ", BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.actions / 2), BUF_SIZE);
		}
		else if (i == -6)
		{
			strlcat(buf, "	\e[1;38;5;27mWitness: ", BUF_SIZE);
			strlcat(buf, ft_itoa((int)g_player.witness), BUF_SIZE);
		}
		else if (i == -4)
		{
			if (g_player.sanity > 0)
				strlcat(buf, "	\e[1;38;5;135mSanity: ", BUF_SIZE);
			else
				strlcat(buf, "	\e[1;5;38;5;135mSanity: ", BUF_SIZE);
			strlcat(buf, ft_itoa(g_player.sanity), BUF_SIZE);
		}
		else if (i == -2)
			strlcat(buf,
				"\t___________________________________________________________",
				BUF_SIZE);
		if (i >= 0 && g_table[i])
			strlcat(buf, g_table[i++], BUF_SIZE);
		if (i < 0)
			i++;
		strlcat(buf, "\e[0m\n", BUF_SIZE);
		r++;
	}
	write(1, buf, strlen(buf));
	bzero(buf, BUF_SIZE);
	free(buf);
}

static void		set_line(int x0, int y0, int x1, int y1)
{
	int		dx;
	int		dy;
	double	slope;
	double	delta;
	int		y;
	int		x;

	//	KNOWN BUG: Still some random dark wall spots. More info needed
	//	Have not spotted any such cases in a while. Keep eye out.
	x = x0;
	y = y0;
	dx = x1 - x0;
	dy = y1 - y0;
	if (dy == 0)
	{
		while (x != x1)
		{
			if (!GETL(y, x).seen || !GETL(y, x).visible)
			{
				GETL(y, x).visible = 1;
				GETL(y, x).seen = 1;
			}
			if (GETL(y, x).solid)
				return ;
			x += dx > 0 ? 1 : -1;
		}
		if (!GETL(y1, x1).seen || !GETL(y1, x1).visible)
		{
			GETL(y1, x1).visible = 1;
			GETL(y1, x1).seen = 1;
		}
		return ;
	}
	else if (dx == 0)
	{
		while (y != y1)
		{
			if (!GETL(y, x).seen || !GETL(y, x).visible)
			{
				GETL(y, x).visible = 1;
				GETL(y, x).seen = 1;
			}
			if (GETL(y, x).solid)
				return ;
			y += dy > 0 ? 1 : -1;
		}
		if (!GETL(y1, x1).seen || !GETL(y1, x1).visible)
		{
			GETL(y1, x1).visible = 1;
			GETL(y1, x1).seen = 1;
		}
		return ;
	}
	if (ABS(dx) > ABS(dy))
	{
		slope = ABS((double)dy / (double)dx);
		delta = slope - 1;
		while (x != x1)
		{
			if (!GETL(y, x).seen || !GETL(y, x).visible)
			{
				GETL(y, x).visible = 1;
				GETL(y, x).seen = 1;
			}
			if (GETL(y, x).solid)
				return ;
			if (delta >= 0)
			{
				y += dy > 0 ? 1 : -1;
				delta--;
			}
			x += dx > 0 ? 1 : -1;
			delta += slope;
		}
	}
	else
	{
		slope = ABS((double)dx / (double)dy);
		delta = slope - 1;
		while (y != y1)
		{
			if (!GETL(y, x).seen || !GETL(y, x).visible)
			{
				GETL(y, x).visible = 1;
				GETL(y, x).seen = 1;
			}
			if (GETL(y, x).solid)
				return ;
			if (delta >= 0)
			{
				x += dx > 0 ? 1 : -1;
				delta--;
			}
			y += dy > 0 ? 1 : -1;
			delta += slope;
		}
	}
	if (!GETL(y1, x1).seen || !GETL(y1, x1).visible)
	{
		GETL(y1, x1).visible = 1;
		GETL(y1, x1).seen = 1;
	}
}

static void		line_of_sight(void)
{
	int radius;
	int xc, yc;
	int x, y;
	int p;

	radius = (int)g_player.witness;
	xc = P_C;
	yc = P_R;
	for (int i = 0; i < (int)g_player.witness - 5; i++, radius--)
	{
		x = radius;
		y = 0;
		p = 1 - radius;
		while (x >= y)
		{
			set_line(xc, yc, xc + x, yc + y);
			set_line(xc, yc, xc + y, yc + x);
			set_line(xc, yc, xc - y, yc + x);
			set_line(xc, yc, xc - x, yc + y);
			set_line(xc, yc, xc - x, yc - y);
			set_line(xc, yc, xc - y, yc - x);
			set_line(xc, yc, xc + y, yc - x);
			set_line(xc, yc, xc + x, yc - y);
			if (x == y || (int)g_player.witness > 10)
			{
				set_line(xc, yc, xc + x, yc + y - 1);
				set_line(xc, yc, xc + y - 1, yc + x);
				set_line(xc, yc, xc - y + 1, yc + x);
				set_line(xc, yc, xc - x, yc + y - 1);
				set_line(xc, yc, xc - x, yc - y + 1);
				set_line(xc, yc, xc - y + 1, yc - x);
				set_line(xc, yc, xc + y - 1, yc - x);
				set_line(xc, yc, xc + x, yc - y + 1);
			}
			y++;
			p += 1 + 2 * y;
			if (2 * (p - x) + 1 > 0)
			{
				x--;
				p += 1 - 2 * x;
			}
		}
	}
}

static void		parser(char *s)
{
	char	c;
	int		dr, dc, i, moved;

	i = 0;
	while (*s && i++ < (int)g_player.actions)
	{
		moved = 0;
		switch (*s)
		{
			case 'w':
			case 'W':
				if (!GETL(P_R - 1, P_C).solid)
				{
					g_player.loc->trailindex = TRAIL_PLAYER;
					P_R--;
					g_player.loc = &GETL(P_R, P_C);
					moved = 1;
				}
				break;
			case 'a':
			case 'A':
				if (!GETL(P_R, P_C - 1).solid)
				{
					g_player.loc->trailindex = TRAIL_PLAYER;
					P_C--;
					g_player.loc = &GETL(P_R, P_C);
					moved = 1;
				}
				break;
			case 's':
			case 'S':
				if (!GETL(P_R + 1, P_C).solid)
				{
					g_player.loc->trailindex = TRAIL_PLAYER;
					P_R++;
					g_player.loc = &GETL(P_R, P_C);
					moved = 1;
				}
				break;
			case 'd':
			case 'D':
				if (!GETL(P_R, P_C + 1).solid)
				{
					g_player.loc->trailindex = TRAIL_PLAYER;
					P_C++;
					g_player.loc = &GETL(P_R, P_C);
					moved = 1;
				}
				break;
			case 'r':
			case 'R':
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
				while (!GETL(P_R + dr, P_C + dc).solid)
				{
					moved = 0;
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
						if (((t_loot*)GETL(P_R, P_C).entity)->type ==
							UP_WITNESS)
							g_player.witness += 2;
						else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
							UP_SANITY)
							g_player.sanity += (g_player.san_max -
								g_player.sanity) / 2;
						else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
							UP_ACTIONS)
							g_player.actions++;
						else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
							UP_XP)
						{
							g_player.xp += 3;
							if (g_player.xp >= g_player.xp_til_ding)
							{
								g_player.level++;
								g_player.xp_til_ding += g_player.level + 2;
								g_player.xp = 0;
								g_player.san_max += g_player.level + 4;
								g_player.sanity = g_player.san_max;
								g_player.max_health += g_player.level + 1;
								g_player.cur_health += (g_player.max_health -
									g_player.cur_health) / 2;
							}
						}
						else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
							UP_HEALTH)
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
				}
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
		if (moved && GETL(P_R, P_C).has_loot && GETL(P_R, P_C).entity)
		{
			if (((t_loot*)GETL(P_R, P_C).entity)->type ==
				UP_WITNESS)
				g_player.witness += 2;
			else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
				UP_SANITY)
				g_player.sanity += (g_player.san_max -
					g_player.sanity) / 2;
			else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
				UP_ACTIONS)
				g_player.actions++;
			else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
				UP_XP)
			{
				g_player.xp += 3;
				if (g_player.xp >= g_player.xp_til_ding)
				{
					g_player.level++;
					g_player.xp_til_ding += g_player.level + 2;
					g_player.xp = 0;
					g_player.san_max += g_player.level + 4;
					g_player.sanity = g_player.san_max;
					g_player.max_health += g_player.level + 1;
					g_player.cur_health += (g_player.max_health -
						g_player.cur_health) / 2;
				}
			}
			else if (((t_loot*)GETL(P_R, P_C).entity)->type ==
				UP_HEALTH)
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
		s++;
	}
}

int				main(void)
{
	char	*action_buffer;
	size_t	has_read;

	g_cols = COLS;
	g_rows = ROWS;
	g_locs = (t_loc*)malloc(sizeof(t_loc) * g_cols * g_rows);
	if (!g_locs)
	{
		ft_putstr_fd("Malloc error with size ", 2);
		ft_putnbr_fd((int)g_cols * (int)g_rows, 2);
		ft_putendl_fd("", 2);
		return (0);
	}
	ft_putendl("Allocated locations.");
	init_locs();
	ft_putendl("Initialized locations.");
	g_player.loc = &GETL(g_rows / 2, g_cols / 2);
	P_R = g_rows / 2;
	P_C = g_cols / 2;
	g_player.witness = 12;
	g_player.sanity = 30;
	g_player.san_max = 30;
	g_player.actions = 7;
	g_player.max_health = 10;
	g_player.cur_health = 10;
	g_player.level = 1;
	g_player.xp = 0;
	g_player.xp_til_ding = 3;
	generate_map();
	ft_putendl("Put walls where they belong.");
	init_mobs();
	action_buffer = (char*)malloc(128);
	line_of_sight();
	display_map();
	while ((has_read = read(1, action_buffer, 128)) != 0)
	{
		action_buffer[has_read] = 0;
		if (ft_strncmp("quit", action_buffer, 4) == 0)
			return (1);
		if (g_player.sanity <= 0 && g_player.cur_health != 0)
			g_player.cur_health--;
		g_player.sanity--;
		parser(action_buffer);
		line_of_sight();
		display_map();
		ft_strclr(action_buffer);
	}
}
