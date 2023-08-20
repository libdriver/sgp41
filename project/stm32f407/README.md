### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SGP41

#### 3.1 Command Instruction

1. Show sgp41 chip and driver information.

   ```shell
   sgp41 (-i | --information)
   ```

2. Show sgp41 help.

   ```shell
   sgp41 (-h | --help)
   ```

3. Show sgp41 pin connections of the current board.

   ```shell
   sgp41 (-p | --port)
   ```

4. Run sgp41 register test.

   ```shell
   sgp41 (-t reg | --test=reg)
   ```

5. Run sgp41 read test, num means test times.

   ```shell
   sgp41 (-t read | --test=read) [--times=<num>]
   ```

6. Run sgp41 read without compensation function, num means read times.

   ```shell
   sgp41 (-e read-without-compensation | --example=read-without-compensation) [--times=<num>]
   ```

7. Run sgp41 read function, num means read times, temp means current temperature and rh means current relative humidity.

   ```shell
   sgp41 (-e read | --example=read) [--times=<num>] [--temperature=<temp>] [--humidity=<rh>]
   ```

8. Get sgp41 serial id.

   ```shell
   sgp41 (-e serial-id | --example=serial-id)
   ```

#### 3.2 Command Example

```shell
sgp41 -i

sgp41: chip is Sensirion SGP41.
sgp41: manufacturer is Sensirion.
sgp41: interface is IIC.
sgp41: driver version is 1.0.
sgp41: min supply voltage is 1.7V.
sgp41: max supply voltage is 3.6V.
sgp41: max current is 4.80mA.
sgp41: max temperature is 50.0C.
sgp41: min temperature is -10.0C.
```

```shell
sgp41 -p

sgp41: SCL connected to GPIOB PIN8.
sgp41: SDA connected to GPIOB PIN9.
```

```shell
sgp41 -t reg

sgp41: chip is Sensirion SGP41.
sgp41: manufacturer is Sensirion.
sgp41: interface is IIC.
sgp41: driver version is 1.0.
sgp41: min supply voltage is 1.7V.
sgp41: max supply voltage is 3.6V.
sgp41: max current is 4.80mA.
sgp41: max temperature is 50.0C.
sgp41: min temperature is -10.0C.
sgp41: start register test.
sgp41: sgp41_soft_reset test.
sgp41: check soft reset ok.
sgp41: sgp41_get_measure_test test.
sgp41: test result is 0xD400.
sgp41: sgp41_get_serial_id test.
sgp41: check get serial id ok.
sgp41: serial id 0x0000 0x03CC 0x11D5.
sgp41: sgp41_turn_heater_off test.
sgp41: check turn heater off ok.
sgp41: sgp41_humidity_convert_to_register test.
sgp41: 76.80% humidity convert to register 0xC49A.
sgp41: sgp41_temperature_convert_to_register test.
sgp41: 16.70C temperature convert to register 0x5A41.
sgp41: finish register test.
```

```shell
sgp41 -t read --times=3

sgp41: chip is Sensirion SGP41.
sgp41: manufacturer is Sensirion.
sgp41: interface is IIC.
sgp41: driver version is 1.0.
sgp41: min supply voltage is 1.7V.
sgp41: max supply voltage is 3.6V.
sgp41: max current is 4.80mA.
sgp41: max temperature is 50.0C.
sgp41: min temperature is -10.0C.
sgp41: start read test.
sgp41: execute conditioning test.
sgp41: raw voc is 0x5085 and gas index is 0.
sgp41: raw voc is 0x59E2 and gas index is 0.
sgp41: raw voc is 0x5DF9 and gas index is 0.
sgp41: measure raw test.
sgp41: raw voc is 0x601A and voc gas index is 0.
sgp41: raw nox is 0x3FAF and nox gas index is 0.
sgp41: raw voc is 0x61BF and voc gas index is 0.
sgp41: raw nox is 0x3FBE and nox gas index is 0.
sgp41: raw voc is 0x62DF and voc gas index is 0.
sgp41: raw nox is 0x3F6A and nox gas index is 0.
sgp41: measure raw without compensation test.
sgp41: raw voc is 0x63F2 and voc gas index is 0.
sgp41: raw nox is 0x3F35 and nox gas index is 0.
sgp41: raw voc is 0x649C and voc gas index is 0.
sgp41: raw nox is 0x3F0B and nox gas index is 0.
sgp41: raw voc is 0x653F and voc gas index is 0.
sgp41: raw nox is 0x3EE1 and nox gas index is 0.
sgp41: finish read test.
```

```shell
sgp41 -e read --temperature=25.0 --humidity=50.0 --times=3

sgp41: 1/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
sgp41: 2/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
sgp41: 3/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
```

```shell
sgp41 -e read-without-compensation --times=3

sgp41: 1/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
sgp41: 2/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
sgp41: 3/3.
sgp41: voc gas index is 0.
sgp41: nox gas index is 0.
```

```shell
sgp41 -e serial-id

sgp41: serial id 0x0000 0x03CC 0x11D5.
```

```shell
sgp41 -h

Usage:
  sgp41 (-i | --information)
  sgp41 (-h | --help)
  sgp41 (-p | --port)
  sgp41 (-t reg | --test=reg)
  sgp41 (-t read | --test=read) [--times=<num>]
  sgp41 (-e read | --example=read) [--times=<num>] [--temperature=<temp>] [--humidity=<rh>]
  sgp41 (-e read-without-compensation | --example=read-without-compensation) [--times=<num>]
  sgp41 (-e serial-id | --example=serial-id)

Options:
  -e <read | read-without-compensation | serial-id>, --example=<read | read-without-compensation | serial-id>
                                          Run the driver example.
  -h, --help                              Show the help.
      --humidity=<rh>                     Set the humidity.([default: 50.0f])
      --temperature=<temp>                Set the temperature.([default: 25.0f])
  -i, --information                       Show the chip information.
  -p, --port                              Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>    Run the driver test.
      --times=<num>                       Set the running times.([default: 3])
```

