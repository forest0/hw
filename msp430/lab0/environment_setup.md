# msp430 开发环境搭建

个人环境: ubuntu 14.04

## 安装工具链

```sh
$ sudo apt-get install msp430mcu msp430-libc mspdebug gcc-msp430 gdb-msp430
```

<!-- libsrecord-dev -->
<!-- libgmp-dev -->

## 权限配置

使用 mspdebug 需要 root 权限, 很烦

```sh
$ lsusb
Bus 001 Device 005: ID 0451:f432 Texas Instruments, Inc. eZ430 Development Tool

# assign idVendor and idProduct according to your output from lsusb
$ sudo echo 'ATTRS{idVendor}=="0451", ATTRS{idProduct}=="f432", MODE="0660", GROUP="plugdev"' > /etc/udev/rules.d/71-persistent-msp430.rules

$ sudo restart udev
# and you may need re-plug your device

# add yourself to group plugdev
$ sudo usermod -a -G plugdev your_user_name_here
```

注销再重新登录后就可以愉快地使用 mspdebug 而且不需要 root 权限了.

## led blink

led.c 源码如下

```c
#include <msp430x20x3.h>

int main(void) {

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    P1DIR |= 0x01;                            // Set P1.0 to output direction

    for (;;) {

        volatile unsigned long i;

        P1OUT ^= 0x01;                        // Toggle P1.0 using exclusive-OR

        i = 99999;                            // Delay

        do {
            i--;
        } while (i != 0);

    }

}
```

编译

```bash
$ msp430-gcc -mmcu=msp430g2553 -g -o led.elf led.c
```

烧录

```bash
$ mspdebug rf2500 'prog led.elf'
```

看到 LED1 闪烁说明成功.

## debug

```sh
$ mspdebug gdb

# open a new terminal
$ target remote localhost:2000

$ file led.elf
$ load led.elf
$ break main
$ continue
$ ^C
$ next
```

## 参考

[Setup Build and Debug environment for MSP430 MCUs using mspgcc and mspdebug in Ubuntu Linux](http://karuppuswamy.com/wordpress/2010/10/14/setup-build-and-debug-environment-for-msp430-mcus-using-mspgcc-and-mspdebug-in-ubuntu-linux/)
