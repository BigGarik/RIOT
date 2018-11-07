/*
 * Copyright (C) 2018 Unwired Devices [info@unwds.com]
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup
 * @ingroup
 * @brief
 * @{
 * @file		st95.h
 * @brief       driver for ST95
 * @author      Mikhail Perkov
 */
#ifndef ST95_H_
#define ST95_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "periph/gpio.h"
#include "periph/spi.h"

#define ST95_IDLE_STATE 0
#define ST95_READY_STATE 1

/* Offset definitions for global buffers */
#define ST95_COMMAND_OFFSET						0
#define ST95_LENGTH_OFFSET						1
#define ST95_DATA_OFFSET						2

#define ST95_TX_RATE_106                0
#define ST95_RX_RATE_106                0
#define ST95_TX_RATE_212                1
#define ST95_RX_RATE_212                1
#define ST95_TX_RATE_424                2
#define ST95_RX_RATE_424                2
#define ST95_TX_RATE_848                3
#define ST95_RX_RATE_848                3

/**
 * @brief ST95 return codes
*/
#define ST95_OK			0
#define ST95_WAKE_UP ST95_OK
#define ST95_ERROR		1
#define ST95_NO_DEVICE	2

/**
 * @brief   ST95 hardware and global parameters.
 */
typedef struct {
    uint8_t spi;        /**< SPI device */
    gpio_t cs_spi;      /**< SPI NSS pin */
    gpio_t irq_in;      /**< Interrupt input */
    gpio_t irq_out;     /**< Interrupt output */
    gpio_t ssi_0;       /**< Select serial communication interface */
    gpio_t ssi_1;       /**< Select serial communication interface */
    gpio_t vcc;         /**< Vcc enable */
} st95_params_t;

/**
 * @brief   ST95 wake up callback
 */
typedef void (*st95_cb_t)(void *);

/**
 * @brief   ST95 device descriptor
 */
typedef struct {
    st95_params_t params;
    st95_cb_t cb;
} st95_t;
/**
 * @brief ST95 bus driver initialization routine
 *
 * @param[in] Device (SPI) to be used for ST95 communication
 *
 * @return 1 if initialization succeeded
 * @return <0 in case of an error
 */
int st95_init(st95_t *dev, st95_params_t * params);

void st95_sleep(st95_t * dev);

int st95_is_wake_up(const st95_t * dev);

int st95_idn(const st95_t * dev, uint8_t * idn, uint8_t * length);

int st95_get_uid(const st95_t * dev, uint8_t * length_uid, uint8_t * uid, uint8_t * sak);

int _st95_cmd_send_receive(const st95_t * dev, uint8_t *data_tx, uint8_t size, uint8_t params, uint8_t * rxbuff);
#endif /* ST95_H_ */