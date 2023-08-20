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
 * @file      main.c
 * @brief     main source file
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

#include "driver_sgp41_basic.h"
#include "driver_sgp41_register_test.h"
#include "driver_sgp41_read_test.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     sgp41 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t sgp41(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"humidity", required_argument, NULL, 1},
        {"temperature", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    float rh = 50.0f;
    float temp = 25.0f;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* rh */
            case 1 :
            {
                rh = atof(optarg);
                
                break;
            }
             
            /* temperature */
            case 2 :
            {
                temp = atof(optarg);
                
                break;
            }
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (sgp41_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (sgp41_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        int32_t voc_gas_index;
        int32_t nox_gas_index;
        
        /* init */
        res = sgp41_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            sgp41_interface_delay_ms(1000);
            
            /* read data */
            res = sgp41_basic_read(temp, rh, &voc_gas_index, &nox_gas_index);
            if (res != 0)
            {
                (void)sgp41_basic_deinit();
                
                return 1;
            }
            
            /* output */
            sgp41_interface_debug_print("sgp41: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            sgp41_interface_debug_print("sgp41: voc gas index is %d.\n", voc_gas_index);
            sgp41_interface_debug_print("sgp41: nox gas index is %d.\n", nox_gas_index);
        }
        
        /* deinit */
        (void)sgp41_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read-without-compensation", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        int32_t voc_gas_index;
        int32_t nox_gas_index;
        
        /* init */
        res = sgp41_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            sgp41_interface_delay_ms(1000);
            
            /* read data */
            res = sgp41_basic_read_without_compensation(&voc_gas_index, &nox_gas_index);
            if (res != 0)
            {
                (void)sgp41_basic_deinit();
                
                return 1;
            }
            
            /* output */
            sgp41_interface_debug_print("sgp41: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            sgp41_interface_debug_print("sgp41: voc gas index is %d.\n", voc_gas_index);
            sgp41_interface_debug_print("sgp41: nox gas index is %d.\n", nox_gas_index);
        }
        
        /* deinit */
        (void)sgp41_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_serial-id", type) == 0)
    {
        uint8_t res;
        uint16_t id[3];
        
        /* init */
        res = sgp41_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* get serial id */
        res = sgp41_basic_get_serial_id(id);
        if (res != 0)
        {
            (void)sgp41_basic_deinit();
            
            return 1;
        }
        
        /* output */
        sgp41_interface_debug_print("sgp41: serial id 0x%04X 0x%04X 0x%04X.\n", (uint16_t)(id[0]), (uint16_t)(id[1]), (uint16_t)(id[2]));
        
        /* deinit */
        (void)sgp41_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        sgp41_interface_debug_print("Usage:\n");
        sgp41_interface_debug_print("  sgp41 (-i | --information)\n");
        sgp41_interface_debug_print("  sgp41 (-h | --help)\n");
        sgp41_interface_debug_print("  sgp41 (-p | --port)\n");
        sgp41_interface_debug_print("  sgp41 (-t reg | --test=reg)\n");
        sgp41_interface_debug_print("  sgp41 (-t read | --test=read) [--times=<num>]\n");
        sgp41_interface_debug_print("  sgp41 (-e read | --example=read) [--times=<num>] [--temperature=<temp>] [--humidity=<rh>]\n");
        sgp41_interface_debug_print("  sgp41 (-e read-without-compensation | --example=read-without-compensation) [--times=<num>]\n");
        sgp41_interface_debug_print("  sgp41 (-e serial-id | --example=serial-id)\n");
        sgp41_interface_debug_print("\n");
        sgp41_interface_debug_print("Options:\n");
        sgp41_interface_debug_print("  -e <read | read-without-compensation | serial-id>, --example=<read | read-without-compensation | serial-id>\n");
        sgp41_interface_debug_print("                                          Run the driver example.\n");
        sgp41_interface_debug_print("  -h, --help                              Show the help.\n");
        sgp41_interface_debug_print("      --humidity=<rh>                     Set the humidity.([default: 50.0f])\n");
        sgp41_interface_debug_print("      --temperature=<temp>                Set the temperature.([default: 25.0f])\n");
        sgp41_interface_debug_print("  -i, --information                       Show the chip information.\n");
        sgp41_interface_debug_print("  -p, --port                              Display the pin connections of the current board.\n");
        sgp41_interface_debug_print("  -t <reg | read>, --test=<reg | read>    Run the driver test.\n");
        sgp41_interface_debug_print("      --times=<num>                       Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        sgp41_info_t info;
        
        /* print sgp41 info */
        sgp41_info(&info);
        sgp41_interface_debug_print("sgp41: chip is %s.\n", info.chip_name);
        sgp41_interface_debug_print("sgp41: manufacturer is %s.\n", info.manufacturer_name);
        sgp41_interface_debug_print("sgp41: interface is %s.\n", info.interface);
        sgp41_interface_debug_print("sgp41: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sgp41_interface_debug_print("sgp41: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sgp41_interface_debug_print("sgp41: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sgp41_interface_debug_print("sgp41: max current is %0.2fmA.\n", info.max_current_ma);
        sgp41_interface_debug_print("sgp41: max temperature is %0.1fC.\n", info.temperature_max);
        sgp41_interface_debug_print("sgp41: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        sgp41_interface_debug_print("sgp41: SCL connected to GPIO3(BCM).\n");
        sgp41_interface_debug_print("sgp41: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = sgp41(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        sgp41_interface_debug_print("sgp41: run failed.\n");
    }
    else if (res == 5)
    {
        sgp41_interface_debug_print("sgp41: param is invalid.\n");
    }
    else
    {
        sgp41_interface_debug_print("sgp41: unknown status code.\n");
    }

    return 0;
}
