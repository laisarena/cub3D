#include "cub3d.h"

void	ft_minilibx()
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 500, "cub3D");
	mlx_pixel_put(mlx, window, 1, 1, 0x00FF0000);

	mlx_loop(mlx);
}
