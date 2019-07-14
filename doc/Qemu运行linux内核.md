
1. 需要准备哪些内容？
u-boot + kernel + rootfs
qemu + gdb


u-boot是一种bootloader
Booting a Linux System Is a Three-Act Play:

    Boot loader mainly sets up the groundwork for the board to be able to load the kernel. Just like an opening, the boot loader paves the way for the kernel, going as far to load it from a remote server into memory so it can be executed. After it’s in memory, the boot loader hands execution to the kernel and exits. The kernel then has its own bootstrapping process (which duplicates what the boot loader did in some cases) that readies the hardware, loads drivers, and starts its processes to manage the system. When it’s in a running state, the kernel hands off control to an init program. The kernel and init then share the stage until you shut down the system

- qemu - 怎样配置模拟哪个环境？？？
- BusyBox ????
 
根文件系统：Linux内核启动后第一个挂载的文件系统，主要由基本的shell命令、各种库、字符设备、配置脚本组成，提供了根目录/，RFS可以放在：nor/nand flash、SD卡、磁盘、网络空间上.
    什么是busybox

        一个集成100多个Linux常用命令和工具的软件

        一个适合制作嵌入式文件系统的软件工具
2. 启动的顺序是怎样的？

- 编译linux kernel
Compiling Kernel for QEMU 还需要什么编译选项吗？

Do not forget to turn debugging on for better experience.
编译内核的时候需要带调试信息的选项，在哪？

QEMU目前可以模拟vexpress Cortex A9四核处理器开发板。
Here I am using the Versatile Express product to emulate because it’s well supported by the mainline Linux kernel,by the mainline UBoot and by mainline QEMU.

模拟arm需要的交叉编译工具

- 运行qemu和gdb 

Start GDB in another window

- Add -s and -S options while invoking QEMU
    - -s enables the gdb stub 
    - -S instructs QEMU to stop after system restart 
        - Waits for gdb to connect


## 编译busybox
1. 什么是busybox?
     （1）busybox是Linux上的一个应用程序(application)，即只有一个ELF文件头。

     （2）它整合了许多Linux上常用的工具和命令（utilities)， 如rm, ls, gzip, tftp等。对于这些工具和命令，busybox中的实现可能不是最全的，但却是最常用的，因此它的特点就是短小精悍，特别适合对尺寸很敏感的嵌入式系统。

     （3）busybox的官方网站是http://www.busybox.net/，在这里你可以找到与busybox相关的所有资料。

参考资料：
https://www.cnblogs.com/baiduboy/p/6228003.html


自己之前一直没搞清楚这两个交叉编译器到底有什么问题,特意google一番,总结如下,希望能帮到道上和我有同样困惑的兄弟…..
一. 什么是ABI和EABI
1) ABI: 二进制应用程序接口(Application Binary Interface (ABI) for the ARM Architecture)
在计算机中，应用二进制接口描述了应用程序（或者其他类型）和操作系统之间或其他应用程序的低级接口.
ABI涵盖了各种细节，如：
数据类型的大小、布局和对齐;
调用约定（控制着函数的参数如何传送以及如何接受返回值），例如，是所有的参数都通过栈传递，还是部分参数通过寄存器传递；哪个寄存器用于哪个函数参数；通过栈传递的第一个函数参数是最先push到栈上还是最后；
系统调用的编码和一个应用如何向操作系统进行系统调用；
以及在一个完整的操作系统ABI中，目标文件的二进制格式、程序库等等。
一个完整的ABI，像Intel二进制兼容标准 (iBCS) ，允许支持它的操作系统上的程序不经修改在其他支持此ABI的操作体统上运行。
ABI不同于应用程序接口（API），API定义了源代码和库之间的接口，因此同样的代码可以在支持这个API的任何系统中编译，ABI允许编译好的目标代码在使用兼容ABI的系统中无需改动就能运行。
2) EABI: 嵌入式ABI
嵌入式应用二进制接口指定了文件格式、数据类型、寄存器使用、堆积组织优化和在一个嵌入式软件中的参数的标准约定。
开发者使用自己的汇编语言也可以使用EABI作为与兼容的编译器生成的汇编语言的接口。
支持EABI的编译器创建的目标文件可以和使用类似编译器产生的代码兼容，这样允许开发者链接一个由不同编译器产生的库。
EABI与关于通用计算机的ABI的主要区别是应用程序代码中允许使用特权指令，不需要动态链接（有时是禁止的），和更紧凑的堆栈帧组织用来节省内存。广泛使用EABI的有Power PC和ARM.
二. gnueabi相关的两个交叉编译器: gnueabi和gnueabihf
在debian源里这两个交叉编译器的定义如下:
gcc-arm-linux-gnueabi – The GNU C compiler for armel architecture
gcc-arm-linux-gnueabihf – The GNU C compiler for armhf architecture
可见这两个交叉编译器适用于armel和armhf两个不同的架构, armel和armhf这两种架构在对待浮点运算采取了不同的策略(有fpu的arm才能支持这两种浮点运算策略)
其实这两个交叉编译器只不过是gcc的选项-mfloat-abi的默认值不同. gcc的选项-mfloat-abi有三种值soft,softfp,hard(其中后两者都要求arm里有fpu浮点运算单元,soft与后两者是兼容的，但softfp和hard两种模式互不兼容)：
soft : 不用fpu进行浮点计算，即使有fpu浮点运算单元也不用,而是使用软件模式。
softfp : armel架构(对应的编译器为gcc-arm-linux-gnueabi)采用的默认值，用fpu计算，但是传参数用普通寄存器传，这样中断的时候，只需要保存普通寄存器，中断负荷小，但是参数需要转换成浮点的再计算。
hard : armhf架构(对应的编译器gcc-arm-linux-gnueabihf)采用的默认值，用fpu计算，传参数也用fpu中的浮点寄存器传，省去了转换, 性能最好，但是中断负荷高。
把以下测试使用的c文件内容保存成mfloat.c：
#include <stdio.h>
int main(void)
{
double a,b,c;
a = 23.543;
b = 323.234;
c = b/a;
printf(“the 13/2 = %f\n”, c);
printf(“hello world !\n”);
return 0;
}
1)使用arm-linux-gnueabihf-gcc编译，使用“-v”选项以获取更详细的信息:
# arm-linux-gnueabihf-gcc -v mfloat.c
COLLECT_GCC_OPTIONS=’-v’ ‘-march=armv7-a’ ‘-mfloat-abi=hard’ ‘-mfpu=vfpv3-d16′ ‘-mthumb’
-mfloat-abi=hard，可看出使用hard硬件浮点模式。
2)使用arm-linux-gnueabi-gcc编译:
# arm-linux-gnueabi-gcc -v mfloat.c
COLLECT_GCC_OPTIONS=’-v’ ‘-march=armv7-a’ ‘-mfloat-abi=softfp’ ‘-mfpu=vfpv3-d16′ ‘-mthumb’
-mfloat-abi=softfp，可看出使用softfp模式。
三. 拓展阅读
下文阐述了ARM代码编译时的软浮点(soft-float)和硬浮点(hard-float)的编译以及链接实现时的不同。从VFP浮点单元的引入到软浮点(soft-float)和硬浮点(hard-float)的概念
VFP (vector floating-point)
从ARMv5开始，就有可选的 Vector Floating Point (VFP) 模块，当然最新的如 Cortex-A8, Cortex-A9 和 Cortex-A5 可以配置成不带VFP的模式供芯片厂商选择。
VFP经过若干年的发展，有VFPv2 (一些 ARM9 / ARM11)、 VFPv3-D16（只使用16个浮点寄存器，默认为32个）和VFPv3+NEON (如大多数的Cortex-A8芯片) 。对于包含NEON的ARM芯片，NEON一般和VFP公用寄存器。
硬浮点Hard-float
编译器将代码直接编译成发射给硬件浮点协处理器（浮点运算单元FPU）去执行。FPU通常有一套额外的寄存器来完成浮点参数传递和运算。
使用实际的硬件浮点运算单元FPU当然会带来性能的提升。因为往往一个浮点的函数调用需要几个或者几十个时钟周期。
软浮点 Soft-float
编译器把浮点运算转换成浮点运算的函数调用和库函数调用，没有FPU的指令调用，也没有浮点寄存器的参数传递。浮点参数的传递也是通过ARM寄存器或者堆栈完成。
现在的Linux系统默认编译选择使用hard-float，即使系统没有任何浮点处理器单元，这就会产生非法指令和异常。因而一般的系统镜像都采用软浮点以兼容没有VFP的处理器。
armel ABI和armhf ABI
在armel中，关于浮点数计算的约定有三种。以gcc为例，对应的-mfloat-abi参数值有三个：soft,softfp,hard。
soft是指所有浮点运算全部在软件层实现，效率当然不高，会存在不必要的浮点到整数、整数到浮点的转换，只适合于早期没有浮点计算单元的ARM处理器；
softfp是目前armel的默认设置，它将浮点计算交给FPU处理，但函数参数的传递使用通用的整型寄存器而不是FPU寄存器；
hard则使用FPU浮点寄存器将函数参数传递给FPU处理。
需要注意的是，在兼容性上，soft与后两者是兼容的，但softfp和hard两种模式不兼容。
默认情况下，armel使用softfp，因此将hard模式的armel单独作为一个abi，称之为armhf。
而使用hard模式，在每次浮点相关函数调用时，平均能节省20个CPU周期。对ARM这样每个周期都很重要的体系结构来说，这样的提升无疑是巨大的。
在完全不改变源码和配置的情况下，在一些应用程序上，使用armhf能得到20%——25%的性能提升。对一些严重依赖于浮点运算的程序，更是可以达到300%的性能提升。
Soft-float和hard-float的编译选项
在CodeSourcery gcc的编译参数上，使用-mfloat-abi=name来指定浮点运算处理方式。-mfpu=name来指定浮点协处理的类型。
可选类型如fpa，fpe2，fpe3，maverick，vfp，vfpv3，vfpv3-fp16，vfpv3-d16，vfpv3-d16-fp16，vfpv3xd，vfpv3xd-fp16，neon，neon-fp16，vfpv4，vfpv4-d16，fpv4-sp-d16，neon-vfpv4等。
使用-mfloat-abi=hard (等价于-mhard-float) -mfpu=vfp来选择编译成硬浮点。使用-mfloat-abi=softfp就能兼容带VFP的硬件以及soft-float的软件实现，运行时的连接器ld.so会在执行浮点运算时对于运算单元的选择，
是直接的硬件调用还是库函数调用，是执行/lib还是/lib/vfp下的libm。-mfloat-abi=soft （等价于-msoft-float）直接调用软浮点实现库。
在ARM RVCT工具链下，定义fpu模式：
–fpu softvfp
–fpu softvfp+vfpv2
–fpu softvfp+vfpv3
–fpu softvfp+vfpv_fp16
–fpu softvfp+vfpv_d16
–fpu softvfp+vfpv_d16_fp16.
定义浮点运算类型
–fpmode ieee_full : 所有单精度float和双精度double的精度都要和IEEE标准一致，具体的模式可以在运行时动态指定；
–fpmode ieee_fixed ： 舍入到最接近的实现的IEEE标准，不带不精确的异常；
–fpmode ieee_no_fenv ：舍入到最接近的实现的IEEE标准，不带异常；
–fpmode std ：非规格数flush到0、舍入到最接近的实现的IEEE标准，不带异常；
–fpmode fast ： 更积极的优化，可能会有一点精度损失。

## 参考资料
- https://blog.csdn.net/jasonLee_lijiaqi/article/details/80967912
- https://blog.csdn.net/absurd/article/details/78984244
- https://learningfromyoublog.wordpress.com/2016/11/27/u-boot-arm-versatile-express-emulation-on-qemu-with-nfs-as-rootfs/
- https://learningfromyoublog.wordpress.com/2016/04/05/131/