[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SGP41

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sgp41/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SGP41是一款數位氣體感測器，設計用於輕鬆集成到空氣淨化器或按需控制的通風系統中。 Sensionon的CMOSens ® 科技在單個晶片上提供了一個完整、易於使用的感測器系統，該系統具有數位I2C介面和溫度控制的微型加熱板，可提供一個VOC和一個基於NOx的室內空氣品質訊號。 傳感元件和氣體指數算灋都具有對現實世界應用中存在的污染氣體無與倫比的魯棒性，能够實現獨特的長期穩定性和低漂移。 非常小的2.44 x 2.44 x 0.85毫米3 DFN封裝可在有限的空間內應用。 Sensionon最先進的生產工藝保證了高再現性和可靠性。 膠帶和卷軸包裝以及對標準SMD組裝工藝的適用性使SGP41註定適用於大批量應用。

LibDriver SGP41是LibDriver推出的SGP41全功能驅動，該驅動提供VOC、NOX讀取、溫濕度矯正等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver SGP41的源文件。

/interface目錄包含了LibDriver SGP41與平台無關的IIC總線模板。

/test目錄包含了LibDriver SGP41驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver SGP41編程範例。

/doc目錄包含了LibDriver SGP41離線文檔。

/datasheet目錄包含了SGP41數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/sgp41/index.html](https://www.libdriver.com/docs/sgp41/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。