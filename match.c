#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum state
{
  begin,
  character,
  character2,
  asterisk,
  asterisk2,
  slash,
  semicolon,
  equal,
  q,
  one,
  cero,
  number,
  end
};

int validateRange(char const *argv);

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    printf("Error: Wrong number of parameters\n");
    return 1;
  }

  if (validateRange(argv[1]))
  {
    //Continue
  }
  else
  {
    printf("Error: Wrong media-range\n");
  }

  return 0;
}

int validateRange(char const *argv)
{
  char c;
  int i = 0;
  int state = begin;

  while ((c = argv[i]) != '\0')
  {
    printf("\n%c\n", c);

    switch (state)
    {
    case begin:
      if (isalpha(c))
        state = character;

      else if (c == '*')
        state = asterisk;

      else
        return 0;

      break;

    case character:
      if (c == '/')
        state = slash;

      else if (!isalpha(c))
        return 0;

      break;

    case asterisk:
      if (c == '/')
        state = slash;

      else
        return 0;

      break;

    case slash:
      if (isalpha(c))
        state = character2;

      else if (c == '*')
        state = asterisk2;

      else
        return 0;

      break;

    case character2:
      // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
      if (c == ';')
        state = semicolon;

      else if (c == ',')
        state = begin;

      else if (!isalpha(c))
        return 0;

      break;

    case asterisk2:
      // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
      if (c == ';')
        state = semicolon;

      else if (c == ',')
        state = begin;

      else
        return 0;

      break;

    case semicolon:
      if (c == 'q')
        state = q;

      else
        return 0;

      break;

    case q:
      if (c == '=')
        state = equal;

      else
        return 0;

      break;

    case equal:
      if (c == '1')
        state = one;

      else if (c == '0')
        state = cero;

      else
        return 0;

      break;

    case one:
      // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
      if (c == ',')
        state = begin;

      else
        return 0;

      break;

      //case cero:
    }

    i++;
  }

  return 1;
}
