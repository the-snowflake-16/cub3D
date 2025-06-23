#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	game.map = &map;
	if ((check_exten(argc, argv[1]) == 1)
		|| (get_map(&map, argv[1]) == 1))
		return (1);
	if (init_game_data(&game, argv[1]))
		return (1);
	free_game_map(&game);
    return (0);
}
