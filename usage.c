#include "./libft/libft.h"

int main(int argc, char **argv)
{
  if (argc == 1)
	ft_putstr("usage:\tfillit source_file\n\tno input file\n");
  if (argc > 2)
	ft_putstr("usage:\tfillit source_file\n\ttoo many input files\n");
//if (read_file == NULL)
  //	ft_putstr("usage:\tfillit source_file\n\tunvalid file\n");
  return (0);
}
