#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

enum state
{
  begin,
  character,
  character2,
  character3,
  character4,
  asterisk,
  asterisk2,
  slash,
  semicolon,
  equal,
  q,
  one,
  cero,
  number,
  coma,
};

int validateRange(char const *argv);
int validateType();

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    printf("Error: Wrong number of parameters\n");
    return 1;
  }

  newQueue();

  if (validateRange(argv[1]))
  {
    //Continue
  }
  else
  {
    printf("\nError: Wrong media-range\n");
  }

  if (validateType())
  {
    //Continue
  }
  else
  {
    printf("\nError: Wrong media-type\n");
  }

  return 0;
}

int validateRange(char const *argv)
{
  char c;
  int i = 0;
  int state = begin;

  while (1)
  {
    c = argv[i];
    printf("%c", c);

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
      if (c == '\0')
        return 1;

      else if (c == ';')
        state = semicolon;

      else if (c == ',')
        state = begin;

      else if (!isalpha(c))
        return 0;

      break;

    case asterisk2:
      // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
      if (c == '\0')
        return 1;

      else if (c == ';')
        state = semicolon;

      else if (c == ',')
        state = begin;

      else
        return 0;

      break;

    case semicolon:
      if (c == 'q')
        state = q;

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
      if (c == '\0')
        return 1;

      else if (c == ',')
        state = begin;

      else
        return 0;

      break;

    case cero:
      if (c == ',')
      {
        state = coma;
      }
      else
      {
        return 0;
      }
      break;

    case coma:
      if (isdigit(c))
      {
        state = number;
      }
      else
      {
        return 0;
      }
      break;

    case number:
      // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
      if (c == '\0')
        return 1;

      else if (c == ',')
      {
        state = begin;
      }
      else
      {
        return 0;
      }
      break;
    }
    i++;
  }

  return 1;
}

int validateType()
{
  char c;
  int state = begin;

  while ((c = getchar()) != EOF)
  {
    printf("%c", c);

    switch (state)
    {
    case begin:
      if (isalpha(c))
        state = character;

      else
        return 0;
      break;

    case character:
      if (c == '/')
        state = slash;

      else if (!isalpha(c))
        return 0;
      break;

    case slash:
      if (isalpha(c))
        state = character2;
      
      else
        return 0;

      break;

    case character2:
      if (c == '\n')
        state = begin;

      else if(c == ';')
        state = semicolon;

      else if(!isalpha(c))      
        return 0;

      break;

    case semicolon:
      if (isalpha(c))
        state = character3;
      else
        return 0;

      break;

    case character3:
      if (c == '=')
       state = equal;

      else if (!isalpha(c))
        return 0;

      break;

    case equal:
      if (isalpha(c))
        state = character4;

      else 
        return 0;

      break;

    case character4:
      if (c == '\n')
        state = begin;

      else if(!isalpha(c))                         
        return 0;
       
      break;
    }
  }
  return 1;
}
