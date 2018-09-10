#ifndef VALIDATE_H
#define VALIDATE_H

#include "queue.h"

void isNull(queueADT queue, char *buffer);
char *addCharacter(char *buffer, char c, const int bufferLenght);
queueADT validateRange(char const *argv);
queueADT validateType();
void check(queueADT mediaRangeQueue, queueADT mediaTypesQueue);
int mediaStringCompare(const char *str1, const char *str2);

#endif
