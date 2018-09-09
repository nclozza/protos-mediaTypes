#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include "validate.h"

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    printf("Error: Wrong number of parameters\n");
    return 1;
  }

  queueADT mediaRangeQueue = validateRange(argv[1]);

  if (mediaRangeQueue != NULL)
  {
    queueADT mediaTypesQueue = validateType();

    if (mediaTypesQueue != NULL)
    {
      printf("\n");
      check(mediaRangeQueue, mediaTypesQueue);
      deleteQueue(mediaRangeQueue);
      deleteQueue(mediaTypesQueue);
    }
    else
    {
      printf("\nError: Out of memory\n");
    }
  }
  else
  {
    printf("\nError: Wrong media-range\n");
  }


  return 0;
}