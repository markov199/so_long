#include <mlx.h>

int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./images/wall.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_png_file_to_image(mlx, relative_path, &img_width, &img_height);
}