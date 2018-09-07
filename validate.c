#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include <string.h>

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
    point,
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

            else
                return NULL;

            break;

        case character:
            if (c == '/')
                state = slash;

            else if (!isalpha(c))
                return NULL;

            break;

        case asterisk:
            if (c == '/')
                state = slash;

            else
                return NULL;

            break;

        case slash:

            if (isalpha(c))
                state = character2;

            else if (c == '*')
                state = asterisk2;

            else
                return NULL;

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
                return NULL;

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
                return NULL;

            break;

        case semicolon:
            if (c == 'q')
                state = q;

            break;

        case q:
            if (c == '=')
                state = equal;

            else
                return NULL;

            break;

        case equal:
            if (c == '1')
                state = one;

            else if (c == '0')
                state = cero;

            else
                return NULL;

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
                return NULL;

            break;

        case cero:
            if (c == '.')
            {
                state = point;
            }
            else
            {
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
                return NULL;
            }
            break;
        }
        i++;
    }
}

// int validateType()
// {
//     char c;
//     int state = begin;

//     while ((c = getchar()) != EOF)
//     {
//         printf("%c", c);

//         switch (state)
//         {
//         case begin:
//             if (isalpha(c))
//                 state = character;

//             else
//                 return NULL;
//             break;

//         case character:
//             if (c == '/')
//                 state = slash;

//             else if (!isalpha(c))
//                 return NULL;
//             break;

//         case slash:
//             if (isalpha(c))
//                 state = character2;

//             else
//                 return NULL;

//             break;

//         case character2:
//             if (c == '\n')
//                 state = begin;

//             else if (c == ';')
//                 state = semicolon;

//             else if (!isalpha(c))
//                 return NULL;

//             break;

//         case semicolon:
//             if (isalpha(c))
//                 state = character3;
//             else
//                 return NULL;

//             break;

//         case character3:
//             if (c == '=')
//                 state = equal;

//             else if (!isalpha(c))
//                 return NULL;

//             break;

//         case equal:
//             if (isalpha(c))
//                 state = character4;

//             else
//                 return NULL;

//             break;

//         case character4:
//             if (c == '\n')
//                 state = begin;

//             else if (!isalpha(c))
//                 return NULL;

//             break;
//         }
//     }
//     return 1;
// }
