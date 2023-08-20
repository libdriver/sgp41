/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sgp41.h
 * @brief     driver sgp41 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-08-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/08/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_SGP41_H
#define DRIVER_SGP41_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sgp41_driver sgp41 driver function
 * @brief    sgp41 driver modules
 * @{
 */

/**
 * @addtogroup sgp41_base_driver
 * @{
 */

/**
 * @brief sgp41 handle structure definition
 */
typedef struct sgp41_handle_s
{
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
} sgp41_handle_t;

/**
 * @brief sgp41 information structure definition
 */
typedef struct sgp41_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} sgp41_info_t;

/**
 * @}
 */

/**
 * @defgroup sgp41_link_driver sgp41 link driver function
 * @brief    sgp41 link driver modules
 * @ingroup  sgp41_driver
 * @{
 */

/**
 * @brief     initialize sgp41_handle_t structure
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] STRUCTURE is sgp41_handle_t
 * @note      none
 */
#define DRIVER_SGP41_LINK_INIT(HANDLE, STRUCTURE)            memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_IIC_INIT(HANDLE, FUC)             (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_IIC_DEINIT(HANDLE, FUC)           (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)    (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_IIC_READ_COMMAND(HANDLE, FUC)     (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an sgp41 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_SGP41_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup sgp41_base_driver sgp41 base driver function
 * @brief    sgp41 base driver modules
 * @ingroup  sgp41_driver
 * @{
 */

/**
 * @brief      get chip information
 * @param[out] *info points to an sgp41 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sgp41_info(sgp41_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an sgp41 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t sgp41_init(sgp41_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an sgp41 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 turn heater off failed
 * @note      none
 */
uint8_t sgp41_deinit(sgp41_handle_t *handle);

/**
 * @brief      get execute conditioning
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[out] *sraw_voc points to a raw tvoc buffer
 * @return     status code
 *             - 0 success
 *             - 1 get execute conditioning failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_execute_conditioning(sgp41_handle_t *handle, uint16_t *sraw_voc);

/**
 * @brief      get the measure raw result
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[in]  raw_humidity is the humidity raw data
 * @param[in]  raw_temperature is the temperature raw data
 * @param[out] *sraw_voc points to a raw tvoc buffer
 * @param[out] *sraw_nox points to a raw nox buffer
 * @return     status code
 *             - 0 success
 *             - 1 get measure raw failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_measure_raw(sgp41_handle_t *handle, uint16_t raw_humidity, uint16_t raw_temperature,
                              uint16_t *sraw_voc, uint16_t *sraw_nox);

/**
 * @brief      get the measure raw result without compensation
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[out] *sraw_voc points to a raw tvoc buffer
 * @param[out] *sraw_nox points to a raw nox buffer
 * @return     status code
 *             - 0 success
 *             - 1 get measure raw without compensation failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_measure_raw_without_compensation(sgp41_handle_t *handle, uint16_t *sraw_voc, uint16_t *sraw_nox);

/**
 * @brief      convert the humidity to the register data
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[in]  rh is the current relative humidity
 * @param[out] *reg points to a converted register data
 * @return     status code
 *             - 0 success
 *             - 1 humidity convert to register failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_humidity_convert_to_register(sgp41_handle_t *handle, float rh, uint16_t *reg);

/**
 * @brief      convert the temperature to the register data
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[in]  temp is the current temperature
 * @param[out] *reg points to a converted register data
 * @return     status code
 *             - 0 success
 *             - 1 temperature convert to register failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_temperature_convert_to_register(sgp41_handle_t *handle, float temp, uint16_t *reg);

/**
 * @brief      get the chip measure test
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[out] *result points to a test result buffer
 * @return     status code
 *             - 0 success
 *             - 1 measure test failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_measure_test(sgp41_handle_t *handle, uint16_t *result);

/**
 * @brief     soft reset the chip
 * @param[in] *handle points to an sgp41 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sgp41_soft_reset(sgp41_handle_t *handle);

/**
 * @brief     turn heater off
 * @param[in] *handle points to an sgp41 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 turn heater off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sgp41_turn_heater_off(sgp41_handle_t *handle);

/**
 * @brief      get the chip serial id
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_serial_id(sgp41_handle_t *handle, uint16_t id[3]);

/**
 * @}
 */

/**
 * @defgroup sgp41_extern_driver sgp41 extern driver function
 * @brief    sgp41 extern driver modules
 * @ingroup  sgp41_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an sgp41 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sgp41_set_reg(sgp41_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an sgp41 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sgp41_get_reg(sgp41_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
