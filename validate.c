#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include <string.h>
#include "validate.h"

#define BLOCK 5

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
    slash2,
    semicolon,
    equal,
    q,
    one,
    cero,
    number,
    point
};

queueADT validateRange(char const *argv)
{
    char c;
    int i = 0;
    int j = 0;
    int state = begin;
    char *buffer;
    queueADT queue = createQueue();

    if (queue == NULL)
        return NULL;

    while (1)
    {
        c = argv[i];

        switch (state)
        {
        case begin:
            if (isalpha(c))
                state = character;

            else if (c == '*')
                state = asterisk;

            else if (c == '\0')
                return queue;

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case character:
            if (c == '/')
                state = slash;

            else if (!isalpha(c))
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case asterisk:
            if (c == '/')
                state = slash2;

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case slash:
            if (isalpha(c))
                state = character2;

            else if (c == '*')
                state = asterisk2;

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case slash2:
            if (c == '*')
            {
                emptyQueue(queue);
                enqueue(queue, "*");
                state = begin;
            }

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case character2:
            if (c == '\0')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                return queue;
            }

            else if (c == ';')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                state = semicolon;
            }

            else if (c == ',')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                j = i + 1;

                state = begin;
            }

            else if (!isalpha(c))
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case asterisk2:
            // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
            if (c == '\0')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                return queue;
            }

            else if (c == ';')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                j = i + 1;

                state = semicolon;
            }

            else if (c == ',')
            {
                buffer = malloc((i - j + 1) * sizeof(*buffer));
                memcpy(buffer, &argv[j], i - j);
                buffer[i - j] = '\0';

                if (buffer == NULL || !enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                j = i + 1;

                state = begin;
            }

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case semicolon:
            if (c == 'q')
                state = q;

            break;

        case q:
            if (c == '=')
                state = equal;

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case equal:
            if (c == '1')
                state = one;

            else if (c == '0')
                state = cero;

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case one:
            // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
            if (c == '\0')
                return queue;

            else if (c == ',')
            {
                j = i + 1;
                state = begin;
            }

            else
            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case cero:
            if (c == '.')
            {
                state = point;
            }
            else

            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case point:
            if (isdigit(c))
            {
                state = number;
            }
            else

            {
                deleteQueue(queue);
                return NULL;
            }

            break;

        case number:
            // Puede terminar, tener en cuenta de guardar el ultimo valor de entrada
            if (c == '\0')
                return queue;

            else if (c == ',')
            {
                j = i + 1;

                state = begin;
            }
            else

            {
                deleteQueue(queue);
                return NULL;
            }

            break;
        }
        i++;
    }
}

queueADT validateType()
{
    int c;
    int bufferLenght = 0;
    int state = begin;
    char *buffer = NULL;
    queueADT queue = createQueue();

    if (queue == NULL)
        return NULL;

    while ((c = getchar()) != EOF)
    {
        bufferLenght++;
        switch (state)
        {
        case begin:
            if (isalpha(c))
                state = character;

            else
            {
                isNull(queue);
                state = begin;
            }

            buffer = (char *)malloc((sizeof(*buffer)));
            bufferLenght = 1;

            if (buffer == NULL)
            {
                deleteQueue(queue);
                return NULL;
            }

            if (!addCharacter(buffer, c, bufferLenght))
            {
                deleteQueue(queue);
                free(buffer);

                return NULL;
            }

            break;

        case character:
            if (c == '/')
                state = slash;

            else if (!isalpha(c))
            {
                if (c != '\n')
                    isNull(queue);

                else
                {
                    char *null = (char *)malloc(sizeof(char));
                    strncpy(null, "N", 1);
                    enqueue(queue, null);
                }

                state = begin;
            }

            if (!addCharacter(buffer, c, bufferLenght))
            {
                deleteQueue(queue);
                free(buffer);

                return NULL;
            }

            break;

        case slash:
            if (isalpha(c))
                state = character2;

            else
            {
                isNull(queue);
                state = begin;
            }

            if (!addCharacter(buffer, c, bufferLenght))
            {
                deleteQueue(queue);
                free(buffer);

                return NULL;
            }

            break;

        case character2:
            if (c == '\n')
            {
                if (/*!addCharacter(buffer, '\0', bufferLenght) || */!enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                state = begin;
            }

            else if (c == ';')
                state = semicolon;

            else if (!isalpha(c))
            {
                isNull(queue);
                state = begin;
            }

            else
            {
                if (!addCharacter(buffer, c, bufferLenght))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }
            }

            break;

        case semicolon:
            if (isalpha(c))
                state = character3;
            else
            {
                isNull(queue);
                state = begin;
            }

            break;

        case character3:
            if (c == '=')
                state = equal;

            else if (!isalpha(c))
            {
                isNull(queue);
                state = begin;
            }

            break;

        case equal:
            if (isalpha(c))
                state = character4;

            else
            {
                isNull(queue);
                state = begin;
            }

            break;

        case character4:
            if (c == '\n')
            {
                if (/*!addCharacter(buffer, '\0', bufferLenght) || */!enqueue(queue, buffer))
                {
                    deleteQueue(queue);
                    free(buffer);

                    return NULL;
                }

                state = begin;
            }

            else if (!isalpha(c))
            {
                isNull(queue);
                state = begin;
            }

            break;
        }
    }
    return queue;
}

int addCharacter(char *buffer, char c, const int bufferLenght)
{
    if (bufferLenght % 5 == 0)
    {
        buffer = (char *)realloc(buffer, (sizeof(*buffer) * bufferLenght) + BLOCK);

        if (buffer == NULL)
            return 0;

    }

    buffer[bufferLenght - 1] = c;

    return 1;
}

void isNull(queueADT queue)
{
    char *null = (char *)malloc(sizeof(char));

    strncpy(null, "N", 1);

    enqueue(queue, null);

    while (getchar() != '\n')
    {
        //Consumo lo que queda de esa linea
    }
}

void check(queueADT mediaRangeQueue, queueADT mediaTypesQueue)
{
    const char *generic = "*";
    int found;
    node *rangeNode = mediaRangeQueue->first;
    node *typesNode = mediaTypesQueue->first;

    if (rangeNode->element == generic)
    {
        while (typesNode != NULL)
        {
            if (strcmp(typesNode->element, "N") == 0)
                printf("Null\n");
            else
                printf("True\n");

            typesNode = typesNode->next;
        }
    }
    else
    {
        while (typesNode != NULL)
        {
            if (strcmp(typesNode->element, "N") == 0)
                printf("Null\n");
            else
            {
                rangeNode = mediaRangeQueue->first;
                found = 0;

                while (rangeNode != NULL && !found)
                {
                    if (mediaStringCompare(typesNode->element, rangeNode->element) == 0)
                        found = 1;

                    else
                        rangeNode = rangeNode->next;
                }

                if (found)
                    printf("True\n");
                else
                    printf("False\n");
            }

            typesNode = typesNode->next;
        }
    }
}

int mediaStringCompare(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        if (*str2 == '/' && *(str2 + 1) == '*')
            return 0;
        str1++, str2++;
    }

    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
