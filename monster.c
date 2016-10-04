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

static void	slime_action(t_mob slime)
{
	int		angry;
	int		dr, dc, i;

	//	Slimes are dumb. They will go in the general direction of the player.
	//	Their trail deals damage though :(
	angry = sees_player(slime);
	i = 0;
	while (i < slime.speed)
	{
		if (angry)
		{
			dir = -1;
			//	Find our deltas
			dr = P_R - slime.row;
			dc = P_C - slime.col;
			//	Go in general direction
			if (dr < 0 && ABS(dr) > ABS(dc) &&
				!GETL(slime.row - 1, slime.col).solid)
				dir = 0;
			else if (dc >= 0 && ABS(dc) > ABS(dr) &&
				!GETL(slime.row, slime.col + 1).solid)
				dir = 1;
			else if (dr >= 0 && ABS(dr) > ABS(dc) &&
				!GETL(slime.row + 1, slime.col).solid)
				dir = 2;
			else if (dc < 0 && ABS(dc) > ABS(dr) &&
				!GETL(slime.row, slime.col - 1).solid)
				dir = 3;
			//	If at first we don't succeed, try again!
			if (dir == -1)
			{
				if (dr < 0 && !GETL(slime.row - 1, slime.col).solid)
					dir = 0;
				else if (dc >= 0 && !GETL(slime.row, slime.col + 1).solid)
					dir = 1;
				else if (dr >= 0 && !GETL(slime.row + 1, slime.col).solid)
					dir = 2;
				else if (dc < 0 && !GETL(slime.row, slime.col - 1).solid)
					dir = 3;
			}
			//	Alright nevermind I'm not angry anymore (slime cornered)
			if (dir == -1)
				angry = 0;
		}
		if (!angry)
		{
			//	Let's get out of this room slowly, yeah?
			//	Slimes hug the right wall of the room until they find an exit!
		}
		i++;
	}
}

void		mob_actions(void)
{
	int		i;

	i = 0;
	while (g_mobs[i].loc)
	{
		if (g_mobs[i].mobtype == MOB_SLIME)
			slime_action(g_mobs[i]);
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
			g_mobs[i].vis_rad = 6;
			g_mobs[i].speed = 3;
			g_mobs[i].health = 5;
			g_mobs[i].kill_xp = 2;
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
