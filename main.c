#include "../include/cub3d.h"

static void	check_file(int argc, char **argv)
{
	int	fd;

	cub_perror(inv_argc, NULL, NULL, argc != 2);
	if (!ft_strncmp(argv[1], "-h", 3) || \
		!ft_strncmp(argv[1], "--help", 7))
		cub_usage(0);
	fd = open(argv[1], O_RDONLY);
	close(fd);
	cub_perror(inv_file, NULL, argv[1], fd < 0);
	if (ft_strrncmp(".cub", argv[1], 4))
		cub_perror(inv_ext, NULL, NULL, 1);
}

void	init_sprites(t_game *g)
{
	g->win_img.i = NULL;
	g->win_g.i = NULL;
	g->win_r.i = NULL;
	g->minimap.i = NULL;
	g->tex.n = NULL;
	g->tex.n_bak = NULL;
	g->tex.s = NULL;
	g->tex.s_bak = NULL;
	g->tex.e = NULL;
	g->tex.e_bak = NULL;
	g->tex.w = NULL;
	g->tex.w_bak = NULL;
	g->tex.b = mlx_load_img(g->mlx, "textures/black.xpm");
	if (!g->tex.b || !g->tex.b->i)
	{
		fprintf(stderr, "⚠️  Warning: black.xpm not found or failed to load.\n");
		// можно присвоить g->tex.b = NULL; или заглушку
	}
	// if (!g->tex.b || !g->tex.b->i)
	// 	cub_perror(inv_pwd, g, NULL, 1);
}

static t_game	cub_init(void)
{
	t_game	g;

	g.width = 0;
	g.fd = -1;
	g.height = 0;
	g.nframes = 0;
	
	g.map = malloc(sizeof(t_map));
	if (!g.map)
		cub_perror(no_memory, NULL, NULL, 1);
	ft_bzero(g.map, sizeof(t_map));

	g.map = NULL;
	g.pl.dir = 0;
	g.mlx = NULL;
	g.win = NULL;
	g.mlx = mlx_init();
	init_sprites(&g);
	g.tex.floor = -1;
	g.tex.ceiling = -1;
	g.pl.x = -1;
	g.pl.y = -1;
	g.pl.speed = 0.12;
	//g.pl.door_cooldown = 0;
	ft_bzero(&g.pl.keys, sizeof(t_key));
	g.mouse_x = 0;
	//g.neg = -1;
	g.rate = 30;
	return (g);
}

int	main(int argc, char **argv)
{
	t_game	g;
	char	**temp;

	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Working directory: %s\n", cwd);
	else
		perror("getcwd() error");
	check_file(argc, argv);
	g = cub_init();
	read_map(argv[1], &g);
	cub_perror(inv_tex, &g, NULL, !g.tex.n || !g.tex.s || !g.tex.e || \
		!g.tex.w);
	cub_perror(inv_color, &g, NULL, g.tex.floor == -1 || g.tex.ceiling == -1);
	temp = square_map(&g);
	ft_free_matrix(&g.map->map);
	g.map->map = temp;
	check_map(&g);
	game_init(&g);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;
// 	t_map	map;
// 	//char	**temp;

// 	ft_bzero(&map, sizeof(t_map));
// 	// Базовая инициализация
// 	printf("Start program\n");

// 	game = cub_init();
// 	printf("cub_init done\n");

// 	game.map = &map;
// 	if ((check_exten(argc, argv[1]) == 1)
// 		|| (get_map(&map, argv[1]) == 1))
// 		return (cub_perror(inv_map, &game, NULL, 1));
// 	printf("Map loaded\n");

// 	// temp = map.map;
// 	// free_game_map(&game);
// 	// //ft_free_matrix(&(game.map->map));
// 	// game.map->map = temp;

// 	if (init_game_data(&game, argv[1]) == 1)
// 		return (cub_perror(inv_tex, &game, NULL, 1));
// 	printf("Game data initialized\n");

// 	// cub_perror(inv_tex, &game, NULL, !game.tex.n || !game.tex.s || !game.tex.e || !game.tex.w);
// 	// cub_perror(inv_color, &game, NULL, game.tex.floor == -1 || game.tex.ceiling == -1);
// 	//printf("Texture and color checks done\n");

// 	game_init(&game);
// 	printf("Game initialized, entering main loop\n");

// 	return (0);
// }

// int main(int argc, char **argv)
// {
// 	t_game	game;
// 	t_map	map;

// 	game.map = &map;
// 	if ((check_exten(argc, argv[1]) == 1)
// 		|| (get_map(&map, argv[1]) == 1))
// 		return (1);
// 	if (init_game_data(&game, argv[1]))
// 		return (1);
// 	free_game_map(&game);
//     return (0);
// }
