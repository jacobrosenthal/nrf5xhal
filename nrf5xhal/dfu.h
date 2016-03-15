//DFUService.h takes ~100 bytes, grabbing underlying files instead

#ifndef NRF5XHAL_DFU_H
#define NRF5XHAL_DFU_H

#include <stdint.h>
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "bootloader_util.h"
#include "nrf_sdm.h"
#include "app_error.h"

#define IRQ_ENABLED            0x01                                     /**< Field that identifies if an interrupt is enabled. */
#define MAX_NUMBER_INTERRUPTS  32                                       /**< Maximum number of interrupts available. */


void bootloader_start(void);

#ifdef __cplusplus
}
#endif

#endif
