fl2440 uboot
====

  该代码是根据 fl2440 官方源码修改来，开源出来之后希望同志同道合的同学一起维护下。
  
  新版的uboot的板級編譯配置是boards.cfg中進行配置的，其解析方式還是同老版本的uboot一樣，是通過mkconfig腳本來進行配置的。因此mkconfig文件需要具有可執行的權限。
  
    tools 中包含了一些工具
  
	mtd	其中存放了mtd相关内容，mtd/util 中还有mkfs.jffs2等相关工具（make && make install 即可安装）
	easylogo   方便创建 logo的工具
	logo	其中存放了video相关的工具

    功能列表
    
    	1.  USB Host 部分，读取 U 盘数据等
	2.  按钮中断控制 led 灯

 编译方法
------------------------------
  
  本人使用的是 arm-linux-gcc，版本为 3.4.1
  
    $ arm-linux-gcc -v
    Reading specs from /usr/local/arm/3.4.1/lib/gcc/arm-linux/3.4.1/specs
    Configured with: /work/crosstool-0.27/build/arm-linux/gcc-3.4.1-glibc-2.3.2/gcc-3.4.1/configure --target=arm-linux --host=i686-host_pc-linux-gnu --prefix=/usr/local/arm/3.4.1 --with-headers=/usr/local/arm/3.4.1/arm-linux/include --with-local-prefix=/usr/local/arm/3.4.1/arm-linux --disable-nls --enable-threads=posix --enable-symvers=gnu --enable-__cxa_atexit --enable-languages=c,c++ --enable-shared --enable-c99 --enable-long-long
    Thread model: posix
    gcc version 3.4.1

  如果不是使用arm-linux-gcc的同学，需要修改下Makefile中:
  
    143   ifeq ($(ARCH),arm)
    144   CROSS_COMPILE = arm-linux- 

将144行中的 CROSS_COMPILE 的内容，修改为对应的编译器名称即可。(当然最好将其加入到PATH中咯～)

  当环境没有问题的时候，可以使用如下命令来编译uboot
  
    $ make fl2440_config && make

  即可编译了。

注意：目前可以支持 jffs2 文件系统

部分宏定义说明
------------------------------

CONFIG_SYS_CONSOLE_IS_IN_ENV       如果不定义，只能在 LCD 上显示，而tty没有显示

部分功能说明
------------------------------

使用 USB 存储功能使用

    fl2440 > usb help
    USB is stopped. Please issue 'usb start' first.

    fl2440 > usb start
    (Re)start USB...
    USB:   scanning bus for devices... cannot reset port 2!?
    2 USB Device(s) found
    scanning bus for storage devices... 1 Storage Device(s) found

    fl2440 > usb storage
    Device 0: Vendor: USB 2.0  Rev: 5.00 Prod: Flash Drive
    Type: Removable Hard Disk
    Capacity: 1012.5 MB = 0.9 GB (2073600 x 512)

    fl2440 > usb part 0
    print_part of 0
    Partition Map for USB device 0  --   Partition Type: DOS
    Partition     Start Sector     Num Sectors     Type
    1                   32         2073568       b

    fl2440 > fatload usb 0:1 0x30008000 uImage_T35
    reading uImage_T35
    ................................................................................
    ................................................................................
    .....................................
    2022412 bytes read

    fl2440 > bootm 0x30008000
    Booting kernel from Legacy Image at 30008000 ...
    Image Name:   fl2440_linux
    Created:      2011-05-12   3:37:00 UTC
    Image Type:   ARM Linux Kernel Image (uncompressed)

可以看到内核开始启动了。
