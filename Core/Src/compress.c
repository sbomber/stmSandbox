/********************************************************************
 *
 * File         :   compress.c
 *
 * Description: :
 *
 * Author:      :   Dan Bomsta (support@9ktech.org)
 *
 * Date         :   3/9/2019, 3:57:39 PM
 *
 * Copyright 2019 9K Tech, LLC.
 *******************************************************************/
#include "compress.h"

#define MAX_DICT_SIZE                                     (1024U)

static uint16_t             dict[ MAX_DICT_SIZE ];

static volatile uint32_t    dict_cnt                      = 0;

/******************** Static Prototypes ****************************/

void initDict( void );
int8_t isInDict( uint16_t value, uint32_t * foundIndex );
int8_t addToDict( uint16_t value );

/******************** End Static Prototypes *************************/


int16_t Compress(   const uint8_t   * input,
                    uint32_t        in_len,
                    uint8_t         * output,
                    uint32_t        * out_len )
{
  int8_t      dictFull      = 0;
  int16_t     status        = -255;
  uint16_t    value         = 0;
  uint32_t    procLen       = 0U;
  uint32_t    outIndex      = 0U;
  uint32_t    foundIndex    = 0U;

  /*  Initialize storage  */
  initDict();

  do
  {
    if( procLen == 0U )
    {
      value = ( uint16_t )( input[ procLen++ ] << 8 );
      value += ( uint16_t )input[ procLen++ ];
    }

    if( ( isInDict( value, &foundIndex ) ) ||
        ( dictFull == COMPR_DICT_FULL ) )
    {
      /*  Already exists, output dict index */
      output[ outIndex++ ] = foundIndex;
    }
    else
    {
      /* Add to dictionary */
      dictFull = addToDict( value );
    }


  } while( procLen < in_len );

  *out_len = outIndex - 1;

  return status;
}



/******************** Static Function ****************************/

/**
 * @brief Initializes dictionary to all zeros
 *
 */
void initDict( void )
{
  for( uint16_t i = 0; i < MAX_DICT_SIZE; i++ )
  {
    dict[ i ] = 0U;
  }
}

/**
 * @brief Determines if value is in dictionary
 *
 * @param value     - value of interest
 * @return int8_t   - 0 - in dictionary ,
 *                    1 - not in dictionary,
 *                    negative - error
 */
int8_t isInDict(uint16_t value, uint32_t *foundIndex)
{
  int8_t      inDict      = COMPR_NOT_IN_DICT;
  uint32_t    cnt         = 0U;

  do
  {
    if( dict[ cnt ] == value )
    {
      inDict        = 1;
      *foundIndex   = cnt;
      break;
    }

    cnt++;
  } while ( cnt < MAX_DICT_SIZE );

  return inDict;
}

/**
 * @brief Adds new dictionary entry
 *
 * @param value     - value to add
 * @return int8_t   - 0 - success
 *                    -1 - dictionary full
 */
int8_t addToDict(uint16_t value)
{
  int8_t    err        = COMPR_SUCCESS;

  if( dict_cnt >= MAX_DICT_SIZE )
  {
    err = COMPR_DICT_FULL;
  }

  if( err == COMPR_SUCCESS )
  {
    dict[ dict_cnt++ ] = value;
  }

  return err;
}

/******************** End Static Functions *************************/