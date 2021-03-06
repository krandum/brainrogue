/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 21:57:28 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/30 21:57:31 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rogue.h"

#include <stdio.h>

t_mob	*g_mobs;

static int	sees_player(t_mob mob)
{
	int		dr, dc;
	double	approx;

	//	Simple pythagorean theorem distance formula
	dr = ABS(mob.row - P_R);
	dc = ABS(mob.col - P_C);
	approx = sqrt(pow((double)dr, 2.0) + pow((double)dc, 2.0));
	if ((int)approx <= mob.vis_rad)
		return (1);
	else
		return (0);
}

static void	slime_action(t_mob *slime)
{
	int		angry;
	int		dr, dc, i;

	//	Slimes are dumb. They will go in the general direction of the player.
	//	Their trail deals damage though :(
	angry = sees_player(*slime);
	i = 0;
	while (i < slime->speed)
	{
		if (angry)
		{
			slime->dir = -1;
			//	Find our deltas
			dr = P_R - slime->row;
			dc = P_C - slime->col;
			//	Go in general direction
			if (dr < 0 && ABS(dr) > ABS(dc) &&
				!GETL(slime->row - 1, slime->col).solid)
				slime->dir = 0;
			else if (dc >= 0 && ABS(dc) > ABS(dr) &&
				!GETL(slime->row, slime->col + 1).solid)
				slime->dir = 1;
			else if (dr >= 0 && ABS(dr) > ABS(dc) &&
				!GETL(slime->row + 1, slime->col).solid)
				slime->dir = 2;
			else if (dc < 0 && ABS(dc) > ABS(dr) &&
				!GETL(slime->row, slime->col - 1).solid)
				slime->dir = 3;
			//	If at first we don't succeed, try again!
			if (slime->dir == -1)
			{
				if (dr < 0 && !GETL(slime->row - 1, slime->col).solid)
					slime->dir = 0;
				else if (dc >= 0 && !GETL(slime->row, slime->col + 1).solid)
					slime->dir = 1;
				else if (dr >= 0 && !GETL(slime->row + 1, slime->col).solid)
					slime->dir = 2;
				else if (dc < 0 && !GETL(slime->row, slime->col - 1).solid)
					slime->dir = 3;
			}
			//	Alright nevermind I'm not angry anymore (slime cornered)
			if (slime->dir == -1)
				angry = 0;
		}
		if (!angry)
		{
			//	Let's get out of this room slowly, yeah?
			//	If we aren't next to a wall, lets get to one
			if (!GETL(slime->row, slime->col).wall_adjacent)
			{
				if (slime->dir == -1)
					slime->dir = rand() % 4;
			}
			else
			{
				//	Slimes hug the right wall of the room until they find an exit!
				if (GETL(slime->row - 1, slime->col).solid &&
					!GETL(slime->row, slime->col - 1).solid)
					slime->dir = 3;
				else if (GETL(slime->row, slime->col + 1).solid &&
					!GETL(slime->row - 1, slime->col).solid)
					slime->dir = 0;
				else if (GETL(slime->row + 1, slime->col).solid &&
					!GETL(slime->row, slime->col + 1).solid)
					slime->dir = 1;
				else if (GETL(slime->row, slime->col - 1).solid &&
					!GETL(slime->row + 1, slime->col).solid)
					slime->dir = 2;
				else
				{
					int		corners;
					//	Okay so we need to go through a door.... we need to find
					//	some corners.

					corners = 0;
					//	TR is 1, BR is 2, BL is 4, TL is 8
					if (GETL(slime->row - 1, slime->col + 1).solid)
						corners += 1;
					if (GETL(slime->row + 1, slime->col + 1).solid)
						corners += 2;
					if (GETL(slime->row + 1, slime->col - 1).solid)
						corners += 4;
					if (GETL(slime->row - 1, slime->col - 1).solid)
						corners += 8;
					if (slime->wild == 0)
					{
						if (corners == 9)
							slime->dir = 0;
						else if (corners == 3)
							slime->dir = 1;
						else if (corners == 6)
							slime->dir = 2;
						else if (corners == 12)
							slime->dir = 3;
						slime->wild = 1;
					}
					else
					{
						if (corners == 9)
							slime->dir = 3;
						else if (corners == 3)
							slime->dir = 0;
						else if (corners == 6)
							slime->dir = 1;
						else if (corners == 12)
							slime->dir = 2;
						slime->wild = 0;
					}
				}
			}
		}
		if (slime->dir != -1)
		{
			int		trail;

			trail = rand() % 3;
			if (trail == 0)
				GETL(slime->row, slime->col).trailindex = TRAIL_SLIME;
			GETL(slime->row, slime->col).has_mob = 0;
			GETL(slime->row, slime->col).entity = 0;
			switch (slime->dir)
			{
				case 0:
					slime->loc = &GETL(slime->row - 1, slime->col);
					slime->row--;
					break;
				case 1:
					slime->loc = &GETL(slime->row, slime->col + 1);
					slime->col++;
					break;
				case 2:
					slime->loc = &GETL(slime->row + 1, slime->col);
					slime->row++;
					break;
				case 3:
					slime->loc = &GETL(slime->row, slime->col - 1);
					slime->col--;
					break;
			}
			GETL(slime->row, slime->col).has_mob = 1;
			GETL(slime->row, slime->col).entity = slime;
			i++;
		}
	}
}

void		mob_actions(void)
{
	int		i;

	i = 0;
	while (g_mobs[i].loc)
	{
		if (g_mobs[i].mobtype == MOB_SLIME)
			slime_action(&g_mobs[i]);
		i++;
	}
}

void		init_mobs(void)
{
	int		total_mobs;
	int		r, c, i;

	total_mobs = NUM_SLIMES;
	g_mobs = (t_mob*)malloc(sizeof(t_mob) * (total_mobs + 1));
	i = 0;
	while (i < total_mobs)
	{
		if (i < NUM_SLIMES)
		{
			r = rand() % (g_rows - 2) + 1;
			c = rand() % (g_cols - 2) + 1;
			if (!GETL(r, c).wall_adjacent || ABS(r - P_R) < 10 || ABS(c - P_C) < 10)
				continue;
			g_mobs[i].mobtype = MOB_SLIME;
			g_mobs[i].vis_rad = 4;
			g_mobs[i].speed = 3;
			g_mobs[i].health = 5;
			g_mobs[i].kill_xp = 2;
			g_mobs[i].wild = 0;
		}
		g_mobs[i].dir = -1;
		g_mobs[i].loc = &GETL(r, c);
		g_mobs[i].row = r;
		g_mobs[i].col = c;
		GETL(r, c).entity = g_mobs + i;
		GETL(r, c).has_mob = 1;
		i++;
	}
	g_mobs[i].loc = 0;
}
