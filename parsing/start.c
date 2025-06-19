#include "../include/cub3d.h"

void draw_tile(t_game *game, int x, int y, int color)
{
    int *data;
    int bpp, size_line, endian;

    game->img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
    data = (int *)mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
    for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++)
        data[i] = color;
    mlx_put_image_to_window(game->mlx, game->win, game->img, x * TILE_SIZE, y * TILE_SIZE);

}
void draw_map(t_game *game)
{
    // int w, h;
    // game.img_player = mlx_xpm_file_to_image(game.mlx, "player.xpm", &w, &h);

    for (int y = 0; game->map->map[y]; y++)
    {
        for (int x = 0; game->map->map[y][x]; x++)
        {
            if (game->map->map[y][x] == '1')
                draw_tile(game, x, y, 0xFFFFFF);
            else if (game->map->map[y][x] == '0')
                draw_tile(game, x, y, 0x000000); // Черный цвет для проходов
            else if (game->map->map[y][x] == 'N')
                draw_tile(game, x, y, 0x00FF00);
        }
    }
}

int close_window(t_game *game)
{
    free_game(game);
    exit(0);
    return (0);
}

void init_window(int argc, char **argv)
{
    t_game game;
    t_map *map = malloc(sizeof(t_map));
    game.map = map;

    if ((check_exten(argc, argv[1]) == 1) || (get_map(map, argv[1]) == 1))
        return;
    map->path = malloc(sizeof(t_path));
    if (!map->path)
        return;
    map->path->ceiling_color = -1;
    map->path->floor_color = -1;
    get_path(map->path, argv[1]);
    get_color(map->path, argv[1]);

    // printf("%d\n", map.path->ceiling_color);
    // printf("%d\n", map.path->floor_color);
    // free_map(&map);
    game.mlx = mlx_init();
    if (!game.mlx)
        return;

    game.win = mlx_new_window(game.mlx, map->col * TILE_SIZE, map->row * TILE_SIZE, "Cub3D");
    if (!game.win)
        return;
    draw_map(&game);
    mlx_hook(game.win, 17, 0, close_window, &map);
    mlx_loop(game.mlx);
    // free_map(&map);
    mlx_destroy_display(game.mlx);
}


