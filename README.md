[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SGP41

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sgp41/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The SGP41 is a digital gas sensor designed for easy integration into air purifier s or demand controlled ventilation systems. Sensirion’s CMOSens ® technology offers a complete , easy to use sensor system on a single chip featuring a digital I 2 C interface and temperature controlled micro hotplates, providing one VOC and one NO x based indoor air quality signal . Both sensing element and Gas Index Algorithm feature an unmatched robustness against contaminating gases present in real world applications enabling a unique long term stability as well as low drift. The very small 2.44 x 2.44 x 0.85 mm 3 DFN package enables applications in limited spaces. Sensirion’s state of the art production process guarantees high reproducibility and reliability. Tape and reel packaging together with suitability for standard SMD assembly processes make the SGP41 predestined for high volume applications.

LibDriver SGP41 is a full-featured driver for SGP41, launched by LibDriver.It provides VOC && NOX reading, temperature && humidity correction and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
    - [LibDriver](#LibDriver)
    - [Gas Index Algorithm](#Gas-Index-Algorithm)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver SGP41 source files.

/interface includes LibDriver SGP41 IIC platform independent template.

/test includes LibDriver SGP41 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver SGP41 sample code.

/doc includes LibDriver SGP41 offline document.

/datasheet includes SGP41 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_sgp41_basic.h"

uint8_t res;
uint32_t i;
uint16_t id[3];
int32_t voc_gas_index;
int32_t nox_gas_index;
uint32_t times = 3;
float rh = 50.0f;
float temp = 25.0f;

/* init */
res = sgp41_basic_init();
if (res != 0)
{
    return 1;
}

...
    
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
    
    ...
}

...

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
    
    ...
}

...
    
/* get serial id */
res = sgp41_basic_get_serial_id(id);
if (res != 0)
{
    (void)sgp41_basic_deinit();

    return 1;
}

/* output */
sgp41_interface_debug_print("sgp41: serial id 0x%04X 0x%04X 0x%04X.\n", (uint16_t)(id[0]), (uint16_t)(id[1]), (uint16_t)(id[2]));

...
    
/* deinit */
(void)sgp41_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/sgp41/index.html](https://www.libdriver.com/docs/sgp41/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

#### LibDriver

All original driver source code in this repository is Copyright (c) 2015 - present LibDriver. This source code is licensed under the MIT License (MIT)  as below.



Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

#### Gas Index Algorithm

The gas index algorithm source code(driver_sgp40_algorithm.c and driver_sgp40_algorithm.h) in this repository is Copyright (c) 2022, Sensirion AG . This source code is licensed under the BSD 3 - Clause License as below.



Copyright (c) 2022, Sensirion AG All rights reserved.



BSD 3 - Clause License



Redistribution and use in source and binary forms, with or without

modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this

   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,

   this list of conditions and the following disclaimer in the documentation

   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its

   contributors may be used to endorse or promote products derived from

   this software without specific prior written permission.

   

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"

AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE

IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE

DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE

FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL

DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR

SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER

CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,

OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE

OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

### Contact Us

Please send an e-mail to lishifenging@outlook.com.