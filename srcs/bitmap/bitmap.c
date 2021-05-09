/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:31:53 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/09 23:41:59 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include "cub3d.h"

#define HEADER_SIZE 54
#define DIP_HEADER_SIZE 40
#define BMP_TYPE 0x4d42
#define NOT_USED 0x0

int	ft_write_data(int fd, char *image, unsigned long int size)
{
	write(fd, image, size);
	return (1);
}

int	ft_open_file(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 777);
	return (fd);
}

int	ft_write_header(int fd, t_bmp_header header)
{
	write(fd, &header.file_type, 2);
	write(fd, &header.file_size, 4);
	write(fd, &header.reserved1, 2);
	write(fd, &header.reserved2, 2);
	write(fd, &header.offset, 4);
	write(fd, &header.dib_header_size, 4);
	write(fd, &header.image_width, 4);
	write(fd, &header.image_height, 4);
	write(fd, &header.num_color_planes, 2);
	write(fd, &header.bits_per_pixel, 2);
	write(fd, &header.compression_type, 4);
	write(fd, &header.image_bytes_size, 4);
	write(fd, &header.x_resolution_ppm, 4);
	write(fd, &header.y_resolution_ppm, 4);
	write(fd, &header.num_colors, 4);
	write(fd, &header.important_colors, 4);
	return (1);
}

t_bmp_header	ft_create_header(long int width, long int height)
{
	t_bmp_header	header;
	long int		data_size;

	data_size = abs(width * height * 4);
	header.file_type = BMP_TYPE;
	header.file_size = HEADER_SIZE + data_size;
	header.reserved1 = NOT_USED;
	header.reserved2 = NOT_USED;
	header.offset = HEADER_SIZE;
	header.dib_header_size = DIP_HEADER_SIZE;
	header.image_width = width;
	header.image_height = height;
	header.num_color_planes = 1;
	header.bits_per_pixel = 32;
	header.compression_type = NOT_USED;
	header.image_bytes_size = data_size;
	header.x_resolution_ppm = NOT_USED;
	header.y_resolution_ppm = NOT_USED;
	header.num_colors = NOT_USED;
	header.important_colors = NOT_USED;
	return (header);
}

int	ft_write_bmp_file(t_vars *vars)
{
	t_bmp_header	header;
	int				fd;

	header = ft_create_header(vars->game.resolution.width,
			vars->game.resolution.height * (-1));
	fd = ft_open_file("cub3D.bmp");
	if (!fd)
		ft_save_error_message("Could not create .bmp file", vars);
	ft_write_header(fd, header);
	ft_write_data(fd, vars->image.address, header.image_bytes_size);
	close(fd);
	return (1);
}
