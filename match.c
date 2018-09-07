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
    printf("\n");
    printQueue(mediaRangeQueue);
    printf("\n");
    //Continue
  }
  else
  {
    printf("\nError: Wrong media-range\n");
  }

  // if (validateType())
  // {
  //   //Continue
  // }
  // else
  // {
  //   printf("\nError: Wrong media-type\n");
  // }

  return 0;
}

