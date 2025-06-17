#include "cub.h"

void draw_tile(t_map *map, int x, int y, int color)
{
    int *data;
    int bpp, size_line, endian;

    map->img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
    data = (int *)mlx_get_data_addr(map->img, &bpp, &size_line, &endian);
    for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++)
        data[i] = color;
    mlx_put_image_to_window(map->mlx, map->win, map->img, x * TILE_SIZE, y * TILE_SIZE);

}
void draw_map(t_map *map)
{
    // int w, h;
    // game.img_player = mlx_xpm_file_to_image(game.mlx, "player.xpm", &w, &h);

    for (int y = 0; map->map[y]; y++)
    {
        for (int x = 0; map->map[y][x]; x++)
        {
            if (map->map[y][x] == '1')
                draw_tile(map, x, y, 0xFFFFFF); // Белый цвет для стен
            else if (map->map[y][x] == '0')
                draw_tile(map, x, y, 0x000000); // Черный цвет для проходов
            else if (map->map[y][x] == 'N')
                draw_tile(map, x, y, 0x00FF00);
        }
    }
}

int close_window(t_map *map)
{
    free_map(map);
    exit(0);
    return (0);
}

void init_window(int argc, char **argv)
{
    t_map map;


    if ((check_exten(argc, argv[1]) == 1) || (get_map(&map, argv[1]) == 1))
        return;
    map.path = malloc(sizeof(t_path));
    if (!map.path)
        return;
    map.path->ceiling_color = -1;
    map.path->floor_color = -1;
    get_path(map.path, argv[1]);
    get_color(map.path, argv[1]);

    // printf("%d\n", map.path->ceiling_color);
    // printf("%d\n", map.path->floor_color);
    // free_map(&map);
    map.mlx = mlx_init();
    if (!map.mlx)
        return;

    map.win = mlx_new_window(map.mlx, map.col * TILE_SIZE, map.row * TILE_SIZE, "Cub3D");
    if (!map.win)
        return;
    draw_map(&map);
    mlx_hook(map.win, 17, 0, close_window, &map);
    mlx_loop(map.mlx);
    // free_map(&map);
    mlx_destroy_display(map.mlx);
}


