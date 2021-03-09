#include "cub3d.h"

typedef struct	s_image_data {
	void	*image;
	char	*address;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_image_data;

typedef struct	s_vars {	
	void		*mlx;
	void		*window;
	t_image_data	image;
	int		x;
	int		y;
}		t_vars;

int	ft_initialize_window(void **mlx, void **window, t_image_data *image)
{
	if (!(*mlx = mlx_init()))
		ft_error("Error initializing minilibx");
	if (!(*window = mlx_new_window(*mlx, 500, 500, "cub3D")))
		ft_error("Error creating window");
	if (!(image->image = mlx_new_image(*mlx, 500, 500)))
		ft_error("Error creating image");
	image->address = mlx_get_data_addr(image->image, &image->bits_per_pixel, &image->line_length, &image->endian);
	return 1;
}

void	ft_put_pixel(t_image_data *image, int x, int y, int color)
{
	int	offset;
	int	bytes_per_pixel;
	char	*address;

	bytes_per_pixel = image->bits_per_pixel/8;
	offset = y * image->line_length + x * bytes_per_pixel;
	address = image->address + offset;
	*(unsigned int*)address = color;
}

void	rectangle_on_image(t_image_data *image, int x, int y, int width, int heigth, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < heigth)
	{
		j = -1;
		while (++j < width)
			ft_put_pixel(image, x + j, y + i, color);
	}
}


int	ft_x(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
	mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	exit (0);
}

int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 0xFF1B)
		ft_x(vars);
	return (1);
}

void	ft_render(t_vars *vars)
{
	rectangle_on_image(&vars->image, 100, 100, 30, 50,  0x00FF0000);	
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

void	ft_hooks(t_vars *vars)
{
	mlx_hook(vars->window, 2, 1L<<0, ft_close, vars);
	mlx_hook(vars->window, 33, 0, ft_x, vars);
}

void	ft_setup(t_vars *vars)
{
	vars->x = 50;
	vars->y = 50;
}

void	ft_update(t_vars *vars)
{
	(vars->x)++;
	(vars->y)++;
}

void	ft_loop(t_vars *vars)
{
	if (ft_initialize_window(&vars->mlx, &vars->window, &vars->image))
	{
		ft_hooks(vars);
		ft_render(vars);
		ft_update(vars);
	}
}

void	ft_minilibx()
{
	t_vars		vars;

	vars.mlx = NULL;
	vars.window = NULL;
	ft_setup(&vars);
	ft_loop(&vars);
	mlx_loop(vars.mlx);
}
