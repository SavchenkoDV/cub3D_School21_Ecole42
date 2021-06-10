/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:34:49 by buthor            #+#    #+#             */
/*   Updated: 2021/06/10 18:11:25 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "minilibx_mms_20200219/mlx.h"
# include "math.h"

# define SYM0	" 012NWSE"
# define SYM1	"NWSE"
# define SYM2	"02"
# define SUD	0.08
# define TMS	0.08

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			wsx;
	int			wsy;
}				t_mlx;

typedef struct s_pixput
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_pixput;

typedef struct s_header
{
	char		*range;
	int			rw;
	int			rh;
	void		*buf;
	char		*addr_buf;
	int			w_texture_buf;
	int			h_texture_buf;
	int			line_len_buf;
	int			bpp_buf;
	int			end_buf;
	void		*no;
	char		*addr_no;
	int			w_texture_no;
	int			h_texture_no;
	int			line_len_no;
	int			bpp_no;
	int			end_no;
	void		*so;
	char		*addr_so;
	int			w_texture_so;
	int			h_texture_so;
	int			line_len_so;
	int			bpp_so;
	int			end_so;
	void		*we;
	char		*addr_we;
	int			w_texture_we;
	int			h_texture_we;
	int			line_len_we;
	int			bpp_we;
	int			end_we;
	void		*ea;
	char		*addr_ea;
	int			w_texture_ea;
	int			h_texture_ea;
	int			line_len_ea;
	int			bpp_ea;
	int			end_ea;
	void		*s;
	char		*addr_s;
	int			w_texture_s;
	int			h_texture_s;
	int			line_len_s;
	int			bpp_s;
	int			end_s;
	char		*floor;
	int			hex_floor;
	char		*ceiling;
	int			hex_ceiling;
}				t_header;

typedef struct s_raycast
{
	int			hit;
	int			side;
	int			stepx;
	int			stepy;
	double		ddx;
	double		ddy;
	int			map_x;
	int			map_y;
	double		sdx;
	double		sdy;
	double		rdy;
	double		rdx;
	int			drw_str;
	int			drw_end;
	int			h_line;
	double		cam_x;
	double		pwd;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		oldir_x;
	double		oldplane_x;
	double		*zbuf;
}				t_raycast;

typedef struct s_texdata
{
	int			tex_x;
	double		wall_x;
}				t_texdata;

typedef struct s_dsp
{
	double		x;
	double		y;
}				t_dsp;

typedef struct s_sp
{
	int			*sp_ord;
	double		*sp_dist;
	double		spx;
	double		spy;
	double		id;
	double		tform_x;
	double		tform_y;
	int			spscreenx;
	int			sp_h;
	int			sp_w;
	int			str_y;
	int			end_y;
	int			str_x;
	int			end_x;
	int			tex_x;
	int			tex_y;

}				t_sp;

typedef struct s_norm
{
	char		*line;
	int			res;
	int			resgnl;
	int			tmp;
	int			fd;
	int			check_read;
	char		sym;
	int			i;
	char		*new_line;
	int			counter;
	int			f;
	int			c;
	int			r;
	int			g;
	int			b;
}				t_norm;

typedef struct s_data
{
	int			x_map;
	int			y_map;
	double		y_pers;
	double		x_pers;
	int			count_sp;
	char		**map;
	int			av;
	t_mlx		mlx;
	t_pixput	img;
	t_header	header;
	t_raycast	rc;
	t_dsp		*dsp;
	t_texdata	txd;
	t_sp		sp;
	t_norm		norm;
}				t_data;

void	dvs_putstr(char *s);
int		ft_strlen(char *s);
int		dvs_atoi(char **str, char sym);
char	*dvs_join(char *before_line, char sym);
int		get_next_line(char **line, int fd);
void	dvs_free_map(t_data *data);
int		dvs_strchr(char *s, int c);
void	draw_background(t_data *data, int w, int h);
void	init_others_norm(t_data *data);
void	init_others(t_data *data);
void	init_data_raycast(t_data *data);
void	init_data_and_mlx_pixput(t_data *data);
void	init_header_first(t_data *data);
void	init_header_second(t_data *data);
void	init_header(t_data *data);
int		check_error_file(int nbroferror);
int		get_color_bmp(t_data *p, int x, int y);
void	init_head_bmp(unsigned char *buf, int len, t_data *data, int temp);
void	get_screen(t_data *data, int fd, int tmp);
void	make_screenshot(t_data *data, int count, int size);
void	fast_mlx_pixel_put(t_pixput *img, int x, int y, int color);
void	rotate_pers(int keycode, t_data *data);
void	move_pers_ver(int keycode, t_data *data);
void	move_pers_hor(int keycode, t_data *data);
int		calculation(int keycode, t_data *data);
void	write_count_sort_sp(t_data *data, int dtmp, int i, int j);
void	transp_pos_to_rel_to_cam(t_data *data, int i);
void	calc_h_and_w_sprite(t_data *data);
void	rend_sp(t_data *data, int y, int d);
void	draw_sp(t_data *data, int i);
int		rendering(t_data *data);
void	prepare_sprite(t_data *data, int i, int j);
int		tern_to_pars(int res);
int		fill_and_check_map(t_data *data, char *map_addres, int result);
int		pars_and_check_file(char *map_addres, t_data *data);
int		close_win(void);
void	check_acav(t_data *data, char **av, int ac);
int		main(int argc, char **argv);
int		check_all_and_fist_line_map(t_data *data, char first_sym);
int		check_line(t_data *data, char *line, int i);
int		pars_and_check_header_norm25(t_data *data, int fd, int cntr);
int		pars_and_check_header(char *map_addres, t_data *data, int cntr, int fd);
int		check_range(t_data *data, char *line);
int		check_fc_comma(char **line);
int		check_fc(t_data *data, char *line, char **ceiling_or_floor, char sym);
int		tern_s(int nbr, int ret, int elret);
int		check_no(t_data *data, char *line, int i, int flag);
int		check_so(t_data *data, char *line, int i, int flag);
int		check_we(t_data *data, char *line, int i, int flag);
int		check_ea(t_data *data, char *line, int i, int flag);
int		check_s(t_data *data, char *line, int i, int flag);
int		check_for_opening_and_reading(char *addres);
int		check_and_write_texture_norm25(t_data *data, char nsweo);
void	fill_data_no_to_struct(t_data *data, char *address);
void	fill_data_so_to_struct(t_data *data, char *address);
void	fill_data_we_to_struct(t_data *data, char *address);
void	fill_data_ea_to_struct(t_data *data, char *address);
void	fill_data_sp_to_struct(t_data *data, char *address);
int		check_and_write_texture(t_data *data, char nsweo, char *address);
int		caw_texture(t_data *data, char *line, int len, char nsweo);
int		tern_z(int nbr, int ret, int elret);
int		x_size_map_norm(int fl, int check_read, int fd);
int		x_size_map(char *map_addres, int fl);
int		y_size_map(char *map_addres, int fl, int y, t_data *data);
char	**allocate_map(t_data *data);
int		check_map(t_data *data);
void	write_pos_pers(t_data *data, char sym);
void	fill_map_count_sp_and_write_pos_pers(t_data	*data, int i, int j);
void	fill_map_with_spaces(t_data *data);
int		fill_map_with_data(t_data *data, int fd, int fl, int check_read);
int		fill_map(char *map_addres, t_data *data, int fl);
int		map_space_check(t_data *data, int x, int y);
int		tern_f(int nbr, int ret, int elret);
int		check_map_body(t_data *data, int x, int y, int pers);
void	calc_rp_and_rd(t_data *data, int x);
void	init_step_and_calc_side_dist(t_data *data);
void	dda_algoritm(t_data *data);
void	preparation_to_draw(t_data *data);
void	init_data_buff(t_data *data);
void	init_data_bufs(t_data *data);
void	find_pix_tex_and_wall(t_data *data);
void	rend(t_data *data, double step_increase, double start_tex_pos, int x);
void	draw_wall(t_data *data);
void	screenshot(t_data	*data);
void	write_count_sort_sp_norm(t_data *data, int i);
void	check_fc_norm(t_data *data, int sym);
void	check_acav_norm(int i);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	check_cub(char *av, int i);

#endif
