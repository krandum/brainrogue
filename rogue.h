/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rogue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 11:28:31 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/26 11:28:32 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROGUE_H
# define ROGUE_H

# include "libft.h"
# include <time.h>
# include <math.h>

# define GETL(r, c) (g_locs[(r) * g_cols + (c)])
# define ABS(x) ((x) < 0 ? -(x) : (x))

# define P_C (g_player.col)
# define P_R (g_player.row)

# define LOC_FLOOR_V "\e[0;38;5;255m."
# define LOC_FLOOR_S "\e[0;38;5;237m."
# define LOC_INVIS "\e[0m "
# define LOC_WALL_V "\e[0;38;5;39m%"
# define LOC_WALL_S "\e[0;38;5;18m%"
# define LOC_EDGE "\e[0;38;5;196m~"
# define LOC_DOOR_CV "\e[0;38;5;135m]"
# define LOC_DOOR_OV "\e[0;38;5;135m:"
# define LOC_DOOR_CS "\e[0;38;5;55m]"
# define LOC_DOOR_OS "\e[0;38;5;55m:"

# define LOOT_WITNESS "\e[1;38;5;27m+"
# define LOOT_SANITY "\e[1;38;5;135m+"
# define LOOT_ACTIONS "\e[1;38;5;46m+"
# define LOOT_XP "\e[1;38;5;226m+"
# define LOOT_HEALTH "\e[1;38;5;160m+"

# define SPRITE_PLAYER "\e[5;38;5;196m@"
# define PLAYER_TRAIL "\e[0;38;5;196m."
# define SPRITE_SLIME "\e[0;38;5;46ms"
# define SLIME_TRAIL "\e[0;38;5;46m."

# define UI_XP "	\e[1;38;5;226mExperience: "
# define UI_XP_LINE "\e[0;48;5;226m "
# define UI_XP_LINE_DARK "\e[0;48;5;130m "
# define UI_HEALTH "	\e[1;38;5;160mHealth: "
# define UI_HEALTH_LINE "\e[0;48;5;160m "
# define UI_HEALTH_LINE_DARK "\e[0;48;5;52m "

# define UI_LINE " \e[38;5;51m|\e[0m"

# define ROWS 251
# define COLS 251
# define BUILD_NUM 65
# define ACCESS_NUM 36
# define ROOM_DEN 65
# define ROOM_MIN 8
# define ROOM_MAX 14
# define CORR_MIN 8
# define CORR_MAX 12
# define NUM_UPGRADES 5
# define MAP_LOOT 30

# define NUM_SLIMES 15

//	TODO: inventory
//	TODO: basic mobs

typedef enum		e_tile
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_DOOR_O,
	TILE_DOOR_C,
	TILE_LADDER,
	TILE_EDGE
}					t_tile;

typedef enum		e_trail
{
	NO_TRAIL,
	TRAIL_PLAYER,
	TRAIL_SLIME
}					t_trail;

typedef struct		s_loc
{
	void			*entity;
	t_tile			tiletype; //	ID for tile, see above
	t_trail			trailindex; //	Trail type, 0 for no trail, 1 for player
	int				seen:1; //	Previously seen
	int				visible:1; //	Currently visible
	int				solid:1; //	Cannot see through and cannot move into
	int				wall_adjacent:1; //	Used for Dungeon generation
	int				has_loot:1;
	int				has_mob:1;
}					t_loc;

typedef enum		e_upgrade
{
	UP_WITNESS,
	UP_SANITY,
	UP_ACTIONS,
	UP_XP,
	UP_HEALTH
}					t_upgrade;

typedef struct		s_loot
{
	struct s_loc	*loc;
	t_upgrade		type;
	unsigned int	row;
	unsigned int	col;
}					t_loot;

typedef enum		e_monster
{
	MOB_SLIME
}					t_monster;

typedef struct		s_mob
{
	struct s_loc	*loc;
	unsigned int	row;
	unsigned int	col;
	uint8_t			vis_rad;
	uint8_t			speed;
	uint8_t			health;
	uint8_t			kill_xp;
	int				dir:3;
	t_monster		mobtype;
}					t_mob;

typedef struct		s_player
{
	struct s_loc	*loc;
	unsigned int	row;
	unsigned int	col;
	int				sanity;
	uint8_t			san_max;
	uint8_t			actions;
	uint8_t		 	witness;
	uint8_t			max_health;
	uint8_t			cur_health;
	uint8_t			level;
	uint8_t			xp;
	uint8_t			xp_til_ding;
}					t_player;

extern size_t		g_cols;
extern size_t		g_rows;
extern t_loc		*g_locs;
extern t_player		g_player;
extern t_mob		*g_mobs;
extern t_loot		*g_loot;

void				generate_map(void);
void				init_mobs(void);

#endif
