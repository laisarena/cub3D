#include "cub3d.h"

int	ft_initialize_window(void **mlx, void **window)
{
	if (!(*mlx = mlx_init()))
		ft_error("Error initializing minilibx");
	if (!(*window = mlx_new_window(*mlx, 500, 500, "cub3D")))
		ft_error("Error creating window ");
	return 1;
}

void	ft_minilibx()
{
	void	*mlx;
	void	*window;

	mlx = NULL;
	window = NULL;
	ft_initialize_window(&mlx, &window);
	mlx_pixel_put(mlx, window, 100, 100, 0x00FF0000);

	mlx_loop(mlx);
}
