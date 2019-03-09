#ifndef H__compress__
#define H__compress__
/********************************************************************
 *
 * File         :   compress.h
 *
 * Description: :
 *
 * Author:      :   Dan Bomsta (support@9ktech.org)
 *
 * Date         :   3/9/2019, 3:57:48 PM
 *
 * Copyright 2019 9K Tech, LLC.
 *******************************************************************/
#include "FreeRTOSConfig.h"

#define COMPR_ERR                   (-1)
#define COMPR_IN_DICT               (0)
#define COMPR_SUCCESS               (0)
#define COMPR_NOT_IN_DICT           (1)
#define COMPR_DICT_FULL             (2)


/**
 * @brief
 *
 * @param input
 * @param in_len
 * @param output
 * @param out_len
 * @return int16_t
 */
int16_t Compress(const uint8_t *input,
                 uint32_t in_len,
                 uint8_t *output,
                 uint32_t *out_len);

#endif /* H__compress__ */