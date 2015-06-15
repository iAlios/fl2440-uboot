fl2440 uboot
====

  该代码是根据 fl2440 官方源码修改来，开源出来之后希望同志同道合的同学一起维护下。
  
  新版的uboot的板級編譯配置是boards.cfg中進行配置的，其解析方式還是同老版本的uboot一樣，是通過mkconfig腳本來進行配置的。因此mkconfig文件需要具有可執行的權限。
  
  编译方法
====
  
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




部分宏定义说明
CONFIG_SYS_CONSOLE_IS_IN_ENV       如果不定义，只能在 LCD 上显示，而tty没有显示

