/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:05:26 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/04 23:38:37 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

typedef struct s_bmp_header
{
	unsigned short int	file_type;
	unsigned long int	file_size;
	unsigned short int	reserved1;
	unsigned short int	reserved2;
	unsigned long int	offset;
	unsigned long int	dib_header_size;
	long int			image_width;
	long int			image_height;
	unsigned short int	num_color_planes;
	unsigned short int	bits_per_pixel;
	unsigned long int	compression_type;
	unsigned long int	image_bytes_size;
	long int			x_resolution_ppm;
	long int			y_resolution_ppm;
	unsigned long int	num_colors;
	unsigned long int	important_colors;
}						t_bmp_header;

typedef struct s_bmp_image
{
	t_bmp_header	header;
	unsigned char	*data;
}					t_bmp_image;

#endif
