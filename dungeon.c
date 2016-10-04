/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dungeon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:03:50 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/28 15:03:52 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rogue.h"
#include <stdio.h>

t_loot		*g_loot;

static void		set_wall(int r, int c)
{
	GETL(r, c).tiletype = TILE_WALL;
	GETL(r, c).solid = 1;
}

static void		set_floor(int r, int c)
{
	GETL(r, c).tiletype = TILE_FLOOR;
	GETL(r, c).solid = 0;
}

static void		add_loot(int r, int c, t_upgrade upgrade)
{
	int i;

	i = 0;
	while (g_loot[i].loc)
		i++;
	g_loot[i].loc = &GETL(r, c);
	g_loot[i].type = upgrade;
	g_loot[i].row = r;
	g_loot[i].col = c;
	GETL(r, c).has_loot = 1;
	GETL(r, c).entity = &(g_loot[i]);
	g_loot[i + 1].loc = 0;
}

static void		set_door(int r, int c)
{
	int		rng;

	rng = rand() % 100;
	if (rng < 25)
	{
		GETL(r, c).tiletype = TILE_DOOR_O;
		GETL(r, c).solid = 0;
	}
	else if (rng < 60)
	{
		GETL(r, c).tiletype = TILE_DOOR_C;
		GETL(r, c).solid = 1;
	}
	else
		set_floor(r, c);
}

static void		set_wall_line(int r, int c, int length, int dir)
{
	int i;

	i = -1;
	while (++i < length)
	{
		switch (dir)
		{
			case 0:
				set_wall(r - i, c);
				break;
			case 1:
				set_wall(r, c + i);
				break;
			case 2:
				set_wall(r + i, c);
				break;
			case 3:
				set_wall(r, c - i);
				break;
		}
	}
}

static int		make_room(int r0, int c0, int r1, int c1)
{
	int		t, i;
	int		tr, tc;

	//	make sure (r0, c0) is the top-left point
	//	make sure (r1, c1) is the top-right point
	if (r0 > r1)
	{
		t = r0;
		r0 = r1;
		r1 = t;
	}
	if (c0 > c1)
	{
		t = c0;
		c0 = c1;
		c1 = t;
	}
	//	possible to build
	if (r1 - r0 < 2)
		return (0);
	if (c1 - c0 < 2)
		return (0);
	//	check space
	tr = r0;
	while (++tr < r1)
	{
		tc = c0;
		while (++tc < c1)
			if (GETL(tr, tc).tiletype != TILE_FLOOR)
				return (0);
	}
	//	set walls
	set_wall(r0, c0);
	set_wall(r0, c1);
	set_wall(r1, c0);
	set_wall(r1, c1);
	i = 0;
	while (++i < c1 - c0)
	{
		set_wall(r0, c0 + i);
		GETL(r0 + 1, c0 + i).wall_adjacent = 1;
		set_wall(r1, c0 + i);
		GETL(r1 - 1, c0 + i).wall_adjacent = 1;
	}
	i = 0;
	while (++i < r1 - r0)
	{
		set_wall(r0 + i, c0);
		GETL(r0 + i, c0 + 1).wall_adjacent = 1;
		set_wall(r0 + i, c1);
		GETL(r0 + i, c1 - 1).wall_adjacent = 1;
	}
	return (1);
}

static int		gen_room(int row, int col, int height, int width, int dir)
{
	int		t, cen_r, cen_c, rad, rng;

	dir %= 4; // Just in case
	// TODO: add room diversity
	switch (dir)
	{
		case 0:
			t = make_room(row - height, col - width / 2, row, col + width / 2);
			cen_r = row - height / 2;
			cen_c = col;
			break;
		case 1:
			t = make_room(row - height / 2, col, row + height / 2, col + width);
			cen_r = row;
			cen_c = col + width / 2;
			break;
		case 2:
			t = make_room(row, col - width / 2, row + height, col + width / 2);
			cen_r = row + height / 2;
			cen_c = col;
			break;
		case 3:
			t = make_room(row - height / 2, col - width, row + height / 2, col);
			cen_r = row;
			cen_c = col - width / 2;
			break;
	}
	if (!t)
		return (0);
	set_door(row, col);
	rad = height / 2;
	rng = rand() % 100;
	if (height == width && height > (ROOM_MAX - ROOM_MIN) / 2 && height > 12
		&& rng > 30)
	{
		set_wall(cen_r - rad + 4, cen_c - rad + 4);
		set_wall(cen_r - rad + 4, cen_c + rad - 4);
		set_wall(cen_r + rad - 4, cen_c - rad + 4);
		set_wall(cen_r + rad - 4, cen_c + rad - 4);
	}
	return (1);
}

static int		gen_corr(int row, int col, int length, int dir)
{
	int		i;

	i = 0;
	while (++i < length - 1)
	{
		switch (dir)
		{
			case 0:
				if (GETL(row - i, col).tiletype != TILE_FLOOR)
					return (0);
				break;
			case 1:
				if (GETL(row, col + i).tiletype != TILE_FLOOR)
					return (0);
				break;
			case 2:
				if (GETL(row + i, col).tiletype != TILE_FLOOR)
					return (0);
				break;
			case 3:
				if (GETL(row, col - i).tiletype != TILE_FLOOR)
					return (0);
				break;
		}
	}
	i = -1;
	while (++i < length - 1)
	{
		switch (dir)
		{
			case 0:
				GETL(row - i, col).wall_adjacent = 1;
				break;
			case 1:
				GETL(row, col + i).wall_adjacent = 1;
				break;
			case 2:
				GETL(row + i, col).wall_adjacent = 1;
				break;
			case 3:
				if (GETL(row, col - i).tiletype != TILE_FLOOR)
				break;
		}
	}
	switch (dir)
	{
		case 0:
			set_wall_line(row, col - 1, length, dir);
			set_wall_line(row, col + 1, length, dir);
			if (GETL(row - length, col).tiletype != TILE_FLOOR ||
				!GETL(row - length, col).wall_adjacent)
				set_wall(row - length + 1, col);
			break;
		case 1:
			set_wall_line(row - 1, col, length, dir);
			set_wall_line(row + 1, col, length, dir);
			if (GETL(row, col + length).tiletype != TILE_FLOOR ||
				!GETL(row, col + length).wall_adjacent)
				set_wall(row, col + length - 1);
			break;
		case 2:
			set_wall_line(row, col - 1, length, dir);
			set_wall_line(row, col + 1, length, dir);
			if (GETL(row + length, col).tiletype != TILE_FLOOR ||
				!GETL(row + length, col).wall_adjacent)
				set_wall(row + length - 1, col);
			break;
		case 3:
			set_wall_line(row - 1, col, length, dir);
			set_wall_line(row + 1, col, length, dir);
			if (GETL(row, col - length).tiletype != TILE_FLOOR ||
				!GETL(row, col - length).wall_adjacent)
				set_wall(row, col - length + 1);
			break;
	}
	set_door(row, col);
	return (1);
}

static int		bust_wall_hor(int r, int c)
{
	int		sc;

	sc = c;
	//	Go left
	while (GETL(r - 1, c).wall_adjacent && GETL(r + 1, c).wall_adjacent &&
		GETL(r, c).tiletype == TILE_WALL)
		c--;
	if (GETL(r, c).tiletype != TILE_WALL)
		return (0);
	// Go right
	c = sc;
	while (GETL(r - 1, c).wall_adjacent && GETL(r + 1, c).wall_adjacent &&
		GETL(r, c).tiletype == TILE_WALL)
		c++;
	if (GETL(r, c).tiletype != TILE_WALL)
		return (0);
	c = sc;
	set_door(r, c);
	return (1);
}

static int		bust_wall_ver(int r, int c)
{
	int		sr;

	sr = r;
	//	Go up
	while (GETL(r, c - 1).wall_adjacent && GETL(r, c + 1).wall_adjacent &&
		GETL(r, c).tiletype == TILE_WALL)
		r--;
	if (GETL(r, c).tiletype != TILE_WALL)
		return (0);
	// Go down
	r = sr;
	while (GETL(r, c - 1).wall_adjacent && GETL(r, c + 1).wall_adjacent &&
		GETL(r, c).tiletype == TILE_WALL)
		r++;
	if (GETL(r, c).tiletype != TILE_WALL)
		return (0);
	r = sr;
	set_door(r, c);
	return (1);
}

void		generate_map(void)
{
	int		built_num, build_type;
	int		access, i, tmp;
	int		r, c, dir, dr, dc;
	int		w, h, l;
	int		lootnum, upgrade;

	g_loot = (t_loot*)malloc(sizeof(t_loot) * (MAP_LOOT + 1));
	g_loot[0].loc = 0;
	lootnum = MAP_LOOT;
	make_room(P_R - 8, P_C - 8, P_R + 8, P_C + 8);
	set_wall_line(P_R - 5, P_C - 5, 3, 1);
	set_wall_line(P_R - 5, P_C - 5, 3, 2);
	set_wall_line(P_R - 5, P_C + 5, 3, 3);
	set_wall_line(P_R - 5, P_C + 5, 3, 2);
	set_wall_line(P_R + 5, P_C - 5, 3, 1);
	set_wall_line(P_R + 5, P_C - 5, 3, 0);
	set_wall_line(P_R + 5, P_C + 5, 3, 3);
	set_wall_line(P_R + 5, P_C + 5, 3, 0);
	srand(time(NULL));
	built_num = 0;
	while (built_num < BUILD_NUM)
	{
		//	get random location
		r = rand() % (g_rows - 2) + 1;
		c = rand() % (g_cols - 2) + 1;
		//	if not wall, try again
		if (GETL(r, c).tiletype != TILE_WALL)
			continue ;
		//	if wall, find direction to build using wall_adjacent
		dir = 0;
		if (GETL(r + 1, c).wall_adjacent)
			dir += 1;
		if (GETL(r, c - 1).wall_adjacent)
			dir += 2;
		if (GETL(r - 1, c).wall_adjacent)
			dir += 4;
		if (GETL(r, c + 1).wall_adjacent)
			dir += 8;
		if (dir == 1)
			dir = 0;
		else if (dir == 2)
			dir = 1;
		else if (dir == 4)
			dir = 2;
		else if (dir == 8)
			dir = 3;
		else
			continue ;
		//	if wall, decide on another room or corridor
		build_type = rand() % 100;
		//	create room or corridor
		if (build_type < ROOM_DEN)
		{
			//	find room's size
			h = rand() % (ROOM_MAX - ROOM_MIN) + ROOM_MIN;
			w = rand() % (ROOM_MAX - ROOM_MIN) + ROOM_MIN;
			if (gen_room(r, c, h, w, dir))
				built_num++;
		}
		else
		{
			l = rand() % (CORR_MAX - CORR_MIN) + CORR_MIN;
			if (gen_corr(r, c, l, dir))
				built_num++;
			else
				continue;
			//	immediately put something at end of corridor.
			//  if it fails, try another direction from the end
			switch (dir)
			{
				case 0:
					r -= l - 2;
					dr = 1;
					dc = 0;
					break;
				case 1:
					c += l - 2;
					dr = 0;
					dc = -1;
					break;
				case 2:
					r += l - 2;
					dr = -1;
					dc = 0;
					break;
				case 3:
					c -= l - 2;
					dr = 0;
					dc = 1;
					break;
			}
			h = rand() % (ROOM_MAX - ROOM_MIN) + ROOM_MIN;
			w = rand() % (ROOM_MAX - ROOM_MIN) + ROOM_MIN;
			tmp = gen_room(r + dr, c + dc, h, w, dir);
			if (tmp)
			{
				built_num++;
				continue;
			}
			if (build_type < (100 - ROOM_DEN) / 2)
				dir--;
			else
				dir += 2;
			dir %= 4;
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
			}
			tmp = gen_room(r + dr, c + dc, h, w, dir);
			if (tmp)
			{
				built_num++;
				continue;
			}
			if (build_type < (100 - ROOM_DEN) / 2)
				dir += 2;
			else
				dir--;
			dir %= 4;
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
			}
			tmp = gen_room(r + dr, c + dc, h, w, dir);
			if (tmp)
			{
				built_num++;
				continue;
			}
			if (lootnum > 0)
			{
				upgrade = rand() % NUM_UPGRADES;
				add_loot(r, c, (t_upgrade)upgrade);
				lootnum--;
			}
		}
		//repeat
	}
	//	Lets bust some walls open so the different branches can have access with
	//	each other.
	i = 0;
	access = 0;
	while (access < ACCESS_NUM && i++ < 100000)
	{
		//	get random location
		r = rand() % (g_rows - 2) + 1;
		c = rand() % (g_cols - 2) + 1;
		dir = 0;
		if (GETL(r, c).tiletype != TILE_WALL)
			continue ;
		if (GETL(r + 1, c).wall_adjacent)
			dir += 1;
		if (GETL(r, c - 1).wall_adjacent)
			dir += 2;
		if (GETL(r - 1, c).wall_adjacent)
			dir += 4;
		if (GETL(r, c + 1).wall_adjacent)
			dir += 8;
		if (dir == 5)
		{
			printf("attempting bust_wall_hor\n");
			if (bust_wall_hor(r, c))
				access++;
		}
		else if (dir == 10)
		{
			printf("attempting bust_wall_ver\n");
			if (bust_wall_ver(r, c))
				access++;
		}
	}
	init_mobs();
}
