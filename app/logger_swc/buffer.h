#ifndef BUFFER_GUARD
#define BUFFER_GUARD
/*! @file buffer.h
    @brief declaration of buffer type
*/
#include <stdint.h>

#define BUFFER_INIT 0U

#define buffer(buff) buff = {{BUFFER_INIT}, BUFFER_INIT}
#define clear(buff) buff.data_length = BUFFER_INIT
#define push(buff, val) (buff).data[(buff).data_length]=(val); \
                        (buff).data_length++

typedef struct Small_Buffer_Tag{
    char data[BUFFER_SIZE_SMALL];
    uint8_t data_length;
}Small_Buffer_T;

typedef struct Medium_Buffer_Tag{
    char data[BUFFER_SIZE_MEDIUM];
    uint8_t data_length;
}Medium_Buffer_T;

typedef struct Large_Buffer_Tag{
    char data[BUFFER_SIZE_LARGE];
    uint8_t data_length;
}Large_Buffer_T;

#endif /* BUFFER_GUARD */
