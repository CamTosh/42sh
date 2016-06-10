/*
** kalas.h for kalaSH in /home/rotaru_i/termi_kalaSH/inc
**
** Made by Iulian Rotaru
** Login   <rotaru_i@epitech.net>
**
** Started on  Wed May 25 17:00:59 2016 Iulian Rotaru
** Last update Sun Jun  5 07:53:04 2016 ROTARU Iulian
*/

#ifndef KALAS_H_
# define KALAS_H_

# define _XOPEN_SOURCE 600
# define _DEFAULT_SOURCE
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/select.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <lapin.h>

# define CLEAR_SEQ ("\033[3J\033[H\033[2J")
# define SCROLL_HISTORY (1000)

typedef struct		s_text
{
  int			police_size;
  unsigned int		fg;
  unsigned int		bg;
  t_bunny_position	pos;
  int			x;
  int			y;
}			t_text;

typedef struct		s_area_text
{
  int			x;
  int			y;
  int			i;
  int			j;
  int			ratio;
  t_bunny_position	blit;
  unsigned int		*ptrr;
  unsigned int		*ptr;
  t_bunny_pixelarray	*pix;
  t_bunny_pixelarray	*extract;
  t_bunny_position	*area;
  t_text		*text;
}			t_area_text;

typedef struct		s_intro
{
  double		slam;
  double		dezoom;
  t_bunny_position	blit;
  t_color		black;
  int			round;
  int			state;
}			t_intro;

typedef struct		s_pty
{
  int			fd_master;
  int			fd_slave;
  pid_t			child_pid;
  fd_set		fd_zero;
  int			child_status;
  struct termios	slave_save;
  struct termios	slave_new;
  struct termios	master_save;
  struct termios	master_new;
}			t_pty;

typedef struct	s_aff
{
  int		scroll;
  char		*read_buff;
  t_text	text;
  char		**term_buff;
  int		y_idx;
  int		x_idx;
}		t_aff;

typedef struct		s_kala
{
  int			round;
  char			*shell;
  char			*input;
  t_pty			pty;
  bool			pty_setup;
  t_bunny_window	*win;
  t_bunny_pixelarray	*pix;
  t_bunny_pixelarray	*font;
  t_bunny_pixelarray	*bar;
  t_bunny_position	win_pos;
  t_bunny_picture	*logo;
  t_bunny_picture	*shard;
  t_bunny_picture	*bg;
  t_bunny_pixelarray	*bg_pix;
  t_bunny_pixelarray	*bg_filtre;
  t_bunny_music		*draa;
  bool			pressed;
  t_intro		intro;
  char			**env;
  t_aff			buff;
}			t_kala;

void			my_blitstr(char *str,
				   t_bunny_pixelarray *pix,
				   t_bunny_pixelarray *text_pix,
				   t_text *text);
void			set_start_nb(t_bunny_position *pos,
				     t_text *text, int ratio, int j);
void			ratio_setter(int *ratio, t_text *text);
void			main_boucle(t_area_text *v);
void			my_bunny_blit(t_bunny_pixelarray *big,
				      t_bunny_pixelarray *small,
				      t_bunny_position *pos,
				      int mode);
unsigned int		color_mixer(unsigned int one,
			    unsigned int add);
t_bunny_response	kala_key(t_bunny_event_state state,
				 t_bunny_keysym sym,
				 t_kala *data);
t_bunny_response	kala_key_end(t_bunny_event_state state,
				     t_bunny_keysym sym,
				     t_kala *data);
int			writerr(char *str, int ret);
int			len(const char *str);
int			add_char(t_kala *data, char add);
void			nset(void *data, size_t t);
char			*sdup(const char *str);
int			summon_pty(t_kala *data);
int			slave_side(t_kala *data);
int			master_side(t_kala *data);
int			start_up_pty(t_kala *data);
void			check_clear(t_kala *data, int *i);
int			strcmp_start(const char *one, const char *two);
void			max_length_case(t_kala *data);
void			write_in_term(t_kala *data, int i);
void			check_if_y(t_kala *data);
void			aff_master(t_kala *data);
void			update_logo(t_kala *data);
void			fill(t_bunny_pixelarray *pix, unsigned int color);
void			check_master(t_kala *data);
void			process_readings(t_kala *data);
void			kala_setup_one(t_kala *data);
void			kala_zoom(t_kala *data);
void			kala_start_fade(t_kala *data);
t_bunny_response	kala_type(uint32_t unicode,
				  t_kala *data);
t_bunny_response	kala_loop(t_kala *data);
void			kala_end_fade(t_kala *data);
void			kala_afterslam(t_kala *data);
void			kala_afterslam_second(t_kala *data);
void			kala_slam(t_kala *data);
void			kala_slam_second(t_kala *data);
void			my_blitstr(char *str,
				   t_bunny_pixelarray *pix,
				   t_bunny_pixelarray *text_pix,
				   t_text *text);
void			analyse_codes(const char *str,
				      int *i,
				      t_text *text,
				      t_bunny_position *pos);
void			parse_glob(int *recup, int idx, t_text *text);
int			get_all_codes(const char *str, int i, int **recup);
void			add_nb(const char *str, int *out, int **recup);
int			nbr_plus(const char *nb, int *forward);
void			my_blitnbr(int nb,
				   t_bunny_pixelarray *pix,
				   t_bunny_pixelarray *text_pix,
				   t_text *text);
void			ps(t_bunny_position *pos, t_text *text);
void			copy_area(t_bunny_pixelarray *pix,
				  t_bunny_pixelarray *extract,
				  t_bunny_position *area,
				  t_text *text);

#endif /* !KALAS_H_ */
