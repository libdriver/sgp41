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
 * @file      driver_sgp41_register_test.c
 * @brief     driver sgp41 register test source file
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

#include "driver_sgp41_register_test.h"
#include <stdlib.h>

static sgp41_handle_t gs_handle;        /**< sgp41 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t sgp41_register_test(void)
{
    uint8_t res;
    uint16_t reg;
    uint16_t result;
    uint16_t id[3];
    float rh;
    float temp;
    sgp41_info_t info;
    
    /* link functions */
    DRIVER_SGP41_LINK_INIT(&gs_handle, sgp41_handle_t);
    DRIVER_SGP41_LINK_IIC_INIT(&gs_handle, sgp41_interface_iic_init);
    DRIVER_SGP41_LINK_IIC_DEINIT(&gs_handle, sgp41_interface_iic_deinit);
    DRIVER_SGP41_LINK_IIC_WRITE_COMMAND(&gs_handle, sgp41_interface_iic_write_cmd);
    DRIVER_SGP41_LINK_IIC_READ_COMMAND(&gs_handle, sgp41_interface_iic_read_cmd);
    DRIVER_SGP41_LINK_DELAY_MS(&gs_handle, sgp41_interface_delay_ms);
    DRIVER_SGP41_LINK_DEBUG_PRINT(&gs_handle, sgp41_interface_debug_print);
    
    /* sgp41 info */
    res = sgp41_info(&info);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        sgp41_interface_debug_print("sgp41: chip is %s.\n", info.chip_name);
        sgp41_interface_debug_print("sgp41: manufacturer is %s.\n", info.manufacturer_name);
        sgp41_interface_debug_print("sgp41: interface is %s.\n", info.interface);
        sgp41_interface_debug_print("sgp41: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sgp41_interface_debug_print("sgp41: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sgp41_interface_debug_print("sgp41: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sgp41_interface_debug_print("sgp41: max current is %0.2fmA.\n", info.max_current_ma);
        sgp41_interface_debug_print("sgp41: max temperature is %0.1fC.\n", info.temperature_max);
        sgp41_interface_debug_print("sgp41: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    sgp41_interface_debug_print("sgp41: start register test.\n");
    
    /* sgp41 init */
    res = sgp41_init(&gs_handle);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: init failed.\n");
    
        return 1;
    }
    
    /* sgp41 soft reset test */
    sgp41_interface_debug_print("sgp41: sgp41_soft_reset test.\n");
    
    /* soft reset */
    res = sgp41_soft_reset(&gs_handle);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: soft failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    sgp41_interface_debug_print("sgp41: check soft reset %s.\n", res == 0 ? "ok" : "error");
    
    /* sgp41_get_measure_test test */
    sgp41_interface_debug_print("sgp41: sgp41_get_measure_test test.\n");
    
    /* get measure test */
    res = sgp41_get_measure_test(&gs_handle, &result);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: get measure test failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sgp41_interface_debug_print("sgp41: test result is 0x%04X.\n", result);
    
    /* sgp41_get_serial_id test */
    sgp41_interface_debug_print("sgp41: sgp41_get_serial_id test.\n");
    
    /* get serial id */
    res = sgp41_get_serial_id(&gs_handle, id);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: get serial id failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    sgp41_interface_debug_print("sgp41: check get serial id %s.\n", res == 0 ? "ok" : "error");
    sgp41_interface_debug_print("sgp41: serial id 0x%04X 0x%04X 0x%04X.\n", (uint16_t)(id[0]), (uint16_t)(id[1]), (uint16_t)(id[2]));
    
    /* sgp41_turn_heater_off test */
    sgp41_interface_debug_print("sgp41: sgp41_turn_heater_off test.\n");
    
    /* turn heater off */
    res = sgp41_turn_heater_off(&gs_handle);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: turn heater off failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    sgp41_interface_debug_print("sgp41: check turn heater off %s.\n", res == 0 ? "ok" : "error");
    
    /* sgp41_humidity_convert_to_register test */
    sgp41_interface_debug_print("sgp41: sgp41_humidity_convert_to_register test.\n");
    
    /* humidity convert to register */
    rh = (float)(rand() % 1000) / 10.0f;
    res = sgp41_humidity_convert_to_register(&gs_handle, rh, &reg);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: humidity convert to register failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    sgp41_interface_debug_print("sgp41: %0.2f%% humidity convert to register 0x%04X.\n", rh, reg);
    
    /* sgp41_temperature_convert_to_register test */
    sgp41_interface_debug_print("sgp41: sgp41_temperature_convert_to_register test.\n");
    
    /* temperature convert to register */
    temp = (float)(rand() % 500) / 10.0f;
    res = sgp41_temperature_convert_to_register(&gs_handle, temp, &reg);
    if (res != 0)
    {
        sgp41_interface_debug_print("sgp41: temperature convert to register failed.\n");
        (void)sgp41_deinit(&gs_handle);
        
        return 1;
    }
    sgp41_interface_debug_print("sgp41: %0.2fC temperature convert to register 0x%04X.\n", temp, reg);
    
    /* finish register test */
    sgp41_interface_debug_print("sgp41: finish register test.\n");
    (void)sgp41_deinit(&gs_handle);
    
    return 0;
}
