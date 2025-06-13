#include "cub.h"
// // int main()
// // {
// //     void *mlx;
// //     void *win;

// //     mlx = mlx_init();
// //     win = mlx_new_window(mlx, 2300, 2100, "Cub3D");
// //     mlx_loop(mlx);
// // }
// // #include <fcntl.h>
// // #include <unistd.h>
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <stdio.h>
// // #include <stdlib.h>
// char *read_map(const char *filename)
// {
//     char *c = malloc(1024);
//     int fd = open(filename, O_RDONLY);
//     // char line[1024];
//     int sz = read(fd, c, 1023);
//     c[sz]= '\0';
//     // printf("%s\n", c);
//     close(fd);
//     return c;
// }
// int count_lines(char *map)
// {
//     int count =0;
//     int  i = 0;
//     while (map[i])
//     {
//         if(map[i]== '\0' || map[i] == '\n')
//             count++;
//         i++;
//     }
//     return (count);
    
// }
// char **create_arr_map(const char *filename)
// {
//     char *map = read_map(filename);
//     int lines = count_lines(map);
//     char **arr = malloc((lines + 1) * sizeof(char *));
//     int i = 0, j = 0, start = 0;

//     while (map[i])
//     {
//         if (map[i] == '\n' || map[i + 1] == '\0')
//         {
//             int len = (map[i] == '\n') ? i - start : i - start + 1;
//             arr[j] = malloc(len + 1);
//             for (int k = 0; k < len; k++)
//                 arr[j][k] = map[start + k];
//             arr[j][len] = '\0';
//             j++;
//             start = i + 1;
//         }
//         i++;
//     }
//     arr[j] = NULL;
//     free(map);
//     return arr;
// }
// // int main(int argc, char **argv)
// // {
// //     if(argc != 2)
// //     {
// //         printf("Error\n");
// //         return (1);
// //     }
// //     // printf("Map file: %s\n", argv[1]);
// //     // char *map = read_map(argv[1]);
// //     // free(map);
// //     char **arr = create_arr_map(argv[1]);
// //     printf("HEllo");
// //     for(int i = 0; arr[i]; i++)
// //         printf("%s\n",arr[i]);
// //     return (0);
// // }
// #include <stdlib.h>
// #define TILE_SIZE 32
// void draw_tile(void *mlx, void *win, int x, int y, int color)
// {
//     void *img;
//     int *data;
//     int bpp, size_line, endian;

//     img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
//     data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
//     for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++)
//         data[i] = color;
//     mlx_put_image_to_window(mlx, win, img, x * TILE_SIZE, y * TILE_SIZE);
//     mlx_destroy_image(mlx, img);
// }
// int count_width(char **argv)
// {
//     int i = 0;
//     while (argv[0][i])
//         i++;
//     return (i);
// }
// int count_height(char **argv)
// {
//     int i = 0;
//     while (argv[i])
//         i++;
//     return (i);
// }

// void draw_map(t_map *map)
// {
//     int w, h;
//     // game.img_player = mlx_xpm_file_to_image(game.mlx, "player.xpm", &w, &h);

//     for (int y = 0; map->map[y]; y++)
//     {
//         for (int x = 0; map->map[y][x]; x++)
//         {
//             if (map->map[y][x] == '1')
//                 draw_tile(map->mlx, map->win, x, y, 0xFFFFFF); // Белый цвет для стен
//             else if (map->map[y][x] == '0')
//                 draw_tile(map->mlx, map->win, x, y, 0x000000); // Черный цвет для проходов
//             else if (map->map[y][x] == 'N')
//                 draw_tile(map->mlx, map->win, x, y, 0x00FF00);
//         }
//     }
// }

// // void move(int keycode, void *mlx, void *win, char **map)
// // {

// // }
void create_map(char **argv)
{
    (void)argv;
    // t_map map;
    // map.map = create_arr_map(argv[1]);
    // int map_width = count_width(map.map);
    // int map_height = count_height(map.map);
    // printf("%d - %d", map_width, map_height);
    // map.mlx = mlx_init();
    // if (!map.mlx)
    //     return;
    // map.win = mlx_new_window(map.mlx, map_width * TILE_SIZE, map_height * TILE_SIZE, "Cub3D");
    // if (!map.win)
    //     return;
    // draw_map(&map);
    // // move(keycode, mlx, win, map);
    // mlx_loop(map.mlx);
    printf("%d", ft_atoi("634"));
}

