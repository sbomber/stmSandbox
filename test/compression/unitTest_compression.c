/********************************************************************
 *
 * File         :   unitTest_compression.c
 *
 * Description: :
 *
 * Author:      :   Dan Bomsta (support@9ktech.org)
 *
 * Date         :   3/9/2019, 3:49:22 PM
 *
 * Copyright 2019 9K Tech, LLC.
 *******************************************************************/
#include "unity.h"
#include "compress.h"

#define TEST_DATA_SIZE          (100U)
#define REPEAT_DATA_SIZE        (10U)

uint8_t test_data[TEST_DATA_SIZE];
uint8_t comp_data[TEST_DATA_SIZE];

/**
 * @brief Setup function required by Unity
 *
 */
void setUp( void )
{
  uint8_t count     = 0U;

  /*  Create our uncompressed test data */
  do
  {
    for (uint8_t i = 0; i < REPEAT_DATA_SIZE; i++)
    {
      test_data[i] = i;
      count++;
    }
  } while( count < TEST_DATA_SIZE );
}

/**
 * @brief Tear down function required by Unity
 *
 */
void tearDown( void )
{}

void test_Compression( void )
{
  int16_t     status        = -255;
  uint32_t    compSize      = 0U;

  status = Compress( ( const uint8_t * )&test_data,
                      ( uint32_t )TEST_DATA_SIZE,
                      comp_data,
                      &compSize );
}