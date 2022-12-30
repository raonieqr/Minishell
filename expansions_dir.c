#include "minishell.h"

char	**expand_dir(char **cmds)
{
	int		i;
	int 	j;

	i = 0;
  while(cmds[i])
  {
	  if (!is_quote(cmds[i]))
    {
      j = 0;
      while (cmds[i][j])
      {
        if (cmds[i][j] == '~')
        {
          if (cmds[i][j + 1] == ' ' || (!cmds[i][j + 1]))
            cmds[i] = change_var(cmds[i], "", getenv("HOME"), j);
          else if (cmds[i][j + 1] == '/')
            cmds[i] = change_var(cmds[i], "/", getenv("HOME"), j);
        }
        j++;
      }
    }
    i++;
  }
  return (cmds);
}

int is_quote(char *str)
{
  int   len;

  len = ft_strlen(str);
  if (str[0] == 39)
  { 	
    if(str[len - 1] == 39)
      return (1);
  }
  if (str[0] == '"' && str[len - 1] == '"')
      return (2);
  else
    return (0);
}

int    check_quote(char *input)
{
    int i;
    int    d_quote;
    int    s_quote;

    d_quote = 0;
    s_quote = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == 39 && !s_quote &&!d_quote)
            s_quote++;
        else if (input[i] == 39 && !d_quote)
            s_quote--;
        else if (input[i] == '"' && !s_quote && !d_quote)
            d_quote++;
        else if (input[i] == '"' && !s_quote)
            d_quote--;
        i++;
    }
    if (s_quote || d_quote)
    {
      printf("Error\n");
      return (1);
    }
    return (0);
}