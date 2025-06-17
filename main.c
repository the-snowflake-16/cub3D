#include "cub.h"

int main(int argc, char **argv)
{
    (void)argc;
    init_window(argc, argv);
}


// int main(void)
// {
//     void *mlx;
//     void *win;

//     mlx = mlx_init();                                // Инициализация библиотеки
//     win = mlx_new_window(mlx, 800, 600, "Cub3D"); 
//     (void)win;   // Создание окна
//     mlx_destroy_window(mlx, win);
//     mlx_loop(mlx);                                   // Основной цикл событий
// }
