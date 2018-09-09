#ifndef VALIDATE_H
#define VALIDATE_H

#include "queue.h"

void isNull(queueADT queue);
int addCharacter(char *buffer, char c);
queueADT validateRange(char const *argv);
queueADT validateType();

#endif
