# KISS FFT [![Build Status](https://travis-ci.com/mborgerding/kissfft.svg?branch=master)](https://travis-ci.com/mborgerding/kissfft)

KISS FFT - A mixed-radix Fast Fourier Transform based up on the principle, 
"Keep It Simple, Stupid."

There are many great fft libraries already around.  Kiss FFT is not trying
to be better than any of them.  It only attempts to be a reasonably efficient, 
moderately useful FFT that can use fixed or floating data types and can be 
incorporated into someone's C program in a few minutes with trivial licensing.

## USAGE:

The basic usage for 1-d complex FFT is:

```c
    #include "kiss_fft.h"
    kiss_fft_cfg cfg = kiss_fft_alloc( nfft ,is_inverse_fft ,0,0 );
    while ...
    
        ... // put kth sample in cx_in[k].r and cx_in[k].i
        
        kiss_fft( cfg , cx_in , cx_out );
        
        ... // transformed. DC is in cx_out[0].r and cx_out[0].i 
        
    kiss_fft_free(cfg);
```
 - **Note**: frequency-domain data is stored from dc up to 2pi.
    so cx_out[0] is the dc bin of the FFT
    and cx_out[nfft/2] is the Nyquist bin (if exists)

Declarations are in "kiss_fft.h", along with a brief description of the 
functions you'll need to use. 

Code definitions for 1d complex FFTs are in kiss_fft.c.

You can do other cool stuff with the extras you'll find in tools/
> - multi-dimensional FFTs 
> - real-optimized FFTs  (returns the positive half-spectrum: 
    (nfft/2+1) complex frequency bins)
> - fast convolution FIR filtering (not available for fixed point)
> - spectrum image creation

The core fft and most tools/ code can be compiled to use float, double,
 Q15 short or Q31 samples. The default is float.

## BUILDING:

There are two functionally-equivalent build systems supported by kissfft:

 - Make (traditional Makefiles for Unix / Linux systems)
 - CMake (more modern and feature-rich build system developed by Kitware)

To build kissfft, the following build environment can be used:

 - GNU build environment with GCC, Clang and GNU Make or CMake (>= 3.6)
 - Microsoft Visual C++ (MSVC) with CMake (>= 3.6)

Additional libraries required to build and test kissfft include:

 - libpng for psdpng tool,
 - libfftw3 to validate kissfft results against it,
 - python 2/3 with Numpy to validate kissfft results against it.
 - OpenMP supported by GCC, Clang or MSVC for multi-core FFT transformations

Environments like Cygwin and MinGW can be highly likely used to build kissfft
targeting Windows platform, but no tests were performed to the date.

Both Make and CMake builds are easily configurable:

 - `KISSFFT_DATATYPE=<datatype>` (for Make) or `-DKISSFFT_DATATYPE=<datatype>`
   (for CMake) denote the principal datatype used by kissfft. It can be one
   of the following:

   - float (default)
   - double
   - int16_t
   - int32_t
   - SIMD (requires SSE instruction set support on target CPU)

 - `KISSFFT_OPENMP=1` (for Make) or `-DKISSFFT_OPENMP=ON` (for CMake) builds kissfft
   with OpenMP support. Please note that a supported compiler is required and this
   option is turned off by default.

 - `KISSFFT_STATIC=1` (for Make) or `-DKISSFFT_STATIC=ON` (for CMake) instructs
   the builder to create static library ('.lib' for Windows / '.a' for Unix or Linux).
   By default, this option is turned off and the shared library is created
   ('.dll' for Windows, '.so' for Linux or Unix, '.dylib' for Mac OSX)

 - `-DKISSFFT_TEST=OFF` (for CMake) disables building tests for kissfft. On Make,
   building tests is done separately by 'make testall' or 'make testsingle', so
   no specific setting is required.

 - `KISSFFT_TOOLS=0` (for Make) or `-DKISSFFT_TOOLS=OFF` (for CMake) builds kissfft
    without command-line tools like 'fastconv'. By default the tools are built.

    - `KISSFFT_USE_ALLOCA=1` (for Make) or `-DKISSFFT_USE_ALLOCA=ON` (for CMake)
       build kissfft with 'alloca' usage instead of 'malloc' / 'free'.

    - `PREFIX=/full/path/to/installation/prefix/directory` (for Make) or
      `-DCMAKE_INSTALL_PREFIX=/full/path/to/installation/prefix/directory` (for CMake)
      specifies the prefix directory to install kissfft into.

For example, to build kissfft as a static library with 'int16_t' datatype and
OpenMP support using Make, run the command from kissfft source tree:

```
make KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 all
```

The same configuration for CMake is:

```
mkdir build && cd build
cmake -DKISSFFT_DATATYPE=int16_t -DKISSFFT_STATIC=ON -DKISSFFT_OPENMP=ON ..
make all
```

To specify '/tmp/1234' as installation prefix directory, run:


```
make PREFIX=/tmp/1234 KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 install
```

or

```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/tmp/1234 -DKISSFFT_DATATYPE=int16_t -DKISSFFT_STATIC=ON -DKISSFFT_OPENMP=ON ..
make all
make install
```

## TESTING:

To validate the build configured as an example above, run the following command from
kissfft source tree:

```
make KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 testsingle
```

if using Make, or:

```
make test
```

if using CMake.

To test all possible build configurations, please run an extended testsuite from
kissfft source tree:

```
sh test/kissfft-testsuite.sh
```

Please note that the extended testsuite takes around 20-40 minutes depending on device
it runs on. This testsuite is useful for reporting bugs or testing the pull requests.

## BACKGROUND

I started coding this because I couldn't find a fixed point FFT that didn't 
use assembly code.  I started with floating point numbers so I could get the 
theory straight before working on fixed point issues.  In the end, I had a 
little bit of code that could be recompiled easily to do ffts with short, float
or double (other types should be easy too).  

Once I got my FFT working, I was curious about the speed compared to
a well respected and highly optimized fft library.  I don't want to criticize 
this great library, so let's call it FFT_BRANDX.
During this process, I learned:

> 1. FFT_BRANDX has more than 100K lines of code. The core of kiss_fft is about 500 lines (cpx 1-d).
> 2. It took me an embarrassingly long time to get FFT_BRANDX working.
> 3. A simple program using FFT_BRANDX is 522KB. A similar program using kiss_fft is 18KB (without optimizing for size).
> 4. FFT_BRANDX is roughly twice as fast as KISS FFT in default mode.

It is wonderful that free, highly optimized libraries like FFT_BRANDX exist.
But such libraries carry a huge burden of complexity necessary to extract every 
last bit of performance.

**Sometimes simpler is better, even if it's not better.**

## FREQUENTLY ASKED QUESTIONS:
> Q: Can I use kissfft in a project with a ___ license?</br>
> A: Yes.  See LICENSE below.

> Q: Why don't I get the output I expect?</br>
> A: The two most common causes of this are
> 	1) scaling : is there a constant multiplier between what you got and what you want?
> 	2) mixed build environment -- all code must be compiled with same preprocessor 
> 	definitions for FIXED_POINT and kiss_fft_scalar

> Q: Will you write/debug my code for me?</br>
> A: Probably not unless you pay me.  I am happy to answer pointed and topical questions, but 
> I may refer you to a book, a forum, or some other resource.


## PERFORMANCE
    (on Athlon XP 2100+, with gcc 2.96, float data type)

Kiss performed 10000 1024-pt cpx ffts in .63 s of cpu time.
For comparison, it took md5sum twice as long to process the same amount of data.
Transforming 5 minutes of CD quality audio takes less than a second (nfft=1024). 

**DO NOT:**
- use Kiss if you need the Fastest Fourier Transform in the World
- ask me to add features that will bloat the code

## UNDER THE HOOD

Kiss FFT uses a time decimation, mixed-radix, out-of-place FFT. If you give it an input buffer  
and output buffer that are the same, a temporary buffer will be created to hold the data.

No static data is used.  The core routines of kiss_fft are thread-safe (but not all of the tools directory).[

No scaling is done for the floating point version (for speed).  
Scaling is done both ways for the fixed-point version (for overflow prevention).

Optimized butterflies are used for factors 2,3,4, and 5. 

The real (i.e. not complex) optimization code only works for even length ffts.  It does two half-length
FFTs in parallel (packed into real&imag), and then combines them via twiddling.  The result is 
nfft/2+1 complex frequency bins from DC to Nyquist.  If you don't know what this means, search the web.

The fast convolution filtering uses the overlap-scrap method, slightly 
modified to put the scrap at the tail.

## LICENSE
    Revised BSD License, see COPYING for verbiage. 
    Basically, "free to use&change, give credit where due, no guarantees"
    Note this license is compatible with GPL at one end of the spectrum and closed, commercial software at 
    the other end.  See http://www.fsf.org/licensing/licenses
  
## TODO
 - Add real optimization for odd length FFTs 
 - Document/revisit the input/output fft scaling
 - Make doc describing the overlap (tail) scrap fast convolution filtering in kiss_fastfir.c
 - Test all the ./tools/ code with fixed point (kiss_fastfir.c doesn't work, maybe others)

## AUTHOR
    Mark Borgerding
    Mark@Borgerding.net
    
    
# KISS FFT [![构建状态](https://travis-ci.com/mborgerding/kissfft.svg?branch=master)](https://travis-ci.com/mborgerding/kissfft)
KISS FFT 是一个基于“保持简单，傻瓜式”原则的混合基快速傅里叶变换（FFT）库。市面上已经有许多优秀的FFT库。KISS FFT并不试图超越它们中的任何一个，只是尝试成为一个效率尚可、较为实用的FFT库，它可以使用定点或浮点数据类型，并且能在几分钟内以简单的许可协议整合到某人的C程序中。

## 用法
一维复数FFT的基本用法如下：

```c
#include "kiss_fft.h"
kiss_fft_cfg cfg = kiss_fft_alloc( nfft,is_inverse_fft,0,0 );
while...
   ... // 将第k个样本放入cx_in[k].r和cx_in[k].i中
    kiss_fft( cfg, cx_in, cx_out );
   ... // 变换完成。直流分量在cx_out[0].r和cx_out[0].i中
kiss_fft_free(cfg);
```
- **注意**：频域数据存储范围是从直流（DC）到2π。因此，cx_out[0]是FFT的直流分量频段，cx_out[nfft/2]是奈奎斯特频段（如果存在的话）。
声明在“kiss_fft.h”中，同时还有对所需使用函数的简要描述。一维复数FFT的代码定义在kiss_fft.c中。利用tools/目录下的额外内容，你还可以做其他很酷的事情：
 - 多维FFT
 - 实数优化的FFT（返回正半部分频谱：(nfft/2 + 1)个复数频域频段）
 - 快速卷积FIR滤波（定点数不可用）
 - 频谱图像创建
核心的FFT和大多数tools/目录下的代码可以编译为使用float、double、Q15短整型或Q31样本。默认是float。

## 构建
kissfft支持两种功能等效的构建系统：
 - Make（适用于Unix/Linux系统的传统Makefile）
 - CMake（由Kitware开发的更现代、功能更丰富的构建系统）
要构建kissfft，可以使用以下构建环境：
 - 带有GCC、Clang和GNU Make或CMake（>= 3.6）的GNU构建环境
 - 带有CMake（>= 3.6）的Microsoft Visual C++（MSVC）
构建和测试kissfft所需的其他库包括：
 - 用于psdpng工具的libpng
 - 用于与kissfft结果进行验证对比的libfftw3
 - 带有Numpy的Python 2/3，用于与kissfft结果进行验证对比
 - GCC、Clang或MSVC支持的OpenMP，用于多核FFT变换
像Cygwin和MinGW这样的环境很有可能用于针对Windows平台构建kissfft，但截至目前尚未进行测试。
Make和CMake构建都很容易配置：
 - `KISSFFT_DATATYPE=<数据类型>`（用于Make）或`-DKISSFFT_DATATYPE=<数据类型>`（用于CMake）指定kissfft使用的主要数据类型。它可以是以下之一：
    - float（默认）
    - double
    - int16_t
    - int32_t
    - SIMD（要求目标CPU支持SSE指令集）
 - `KISSFFT_OPENMP=1`（用于Make）或`-DKISSFFT_OPENMP=ON`（用于CMake）构建支持OpenMP的kissfft。请注意，这需要支持的编译器，并且此选项默认关闭。
 - `KISSFFT_STATIC=1`（用于Make）或`-DKISSFFT_STATIC=ON`（用于CMake）指示构建器创建静态库（Windows下为'.lib'，Unix或Linux下为'.a'）。默认情况下，此选项关闭并创建共享库（Windows下为'.dll'，Linux或Unix下为'.so'，Mac OSX下为'.dylib'）
 - `-DKISSFFT_TEST=OFF`（用于CMake）禁用kissfft的测试构建。在Make中，通过'make testall'或'make testsingle'单独进行测试构建，因此无需特定设置。
 - `KISSFFT_TOOLS=0`（用于Make）或`-DKISSFFT_TOOLS=OFF`（用于CMake）构建不包含'fastconv'等命令行工具的kissfft。默认情况下会构建这些工具。
 - `KISSFFT_USE_ALLOCA=1`（用于Make）或`-DKISSFFT_USE_ALLOCA=ON`（用于CMake）使用'alloca'而不是'malloc'/'free'来构建kissfft。
 - `PREFIX=/完整路径/到/安装/前缀/目录`（用于Make）或`-DCMAKE_INSTALL_PREFIX=/完整路径/到/安装/前缀/目录`（用于CMake）指定安装kissfft的前缀目录。
例如，要使用Make将kissfft构建为具有'int16_t'数据类型并支持OpenMP的静态库，从kissfft源代码树运行以下命令：
```
make KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 all
```
使用CMake进行相同配置的命令如下：
```
mkdir build && cd build
cmake -DKISSFFT_DATATYPE=int16_t -DKISSFFT_STATIC=ON -DKISSFFT_OPENMP=ON..
make all
```
要指定'/tmp/1234'作为安装前缀目录，运行：
```
make PREFIX=/tmp/1234 KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 install
```
或者
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/tmp/1234 -DKISSFFT_DATATYPE=int16_t -DKISSFFT_STATIC=ON -DKISSFFT_OPENMP=ON..
make all
make install
```

## 测试
要验证如上述示例配置的构建，从kissfft源代码树运行以下命令：
如果使用Make：
```
make KISSFFT_DATATYPE=int16_t KISSFFT_STATIC=1 KISSFFT_OPENMP=1 testsingle
```
如果使用CMake：
```
make test
```
要测试所有可能的构建配置，请从kissfft源代码树运行扩展测试套件：
```sh
test/kissfft-testsuite.sh
```
请注意，扩展测试套件根据运行设备的不同，大约需要20 - 40分钟。此测试套件对于报告错误或测试拉取请求很有用。

## 背景
我开始编写这个库是因为我找不到一个不使用汇编代码的定点FFT。我从浮点数开始，这样在处理定点问题之前我可以先把理论搞清楚。最后，我得到了一小段代码，可以轻松重新编译，以使用短整型、浮点型或双精度型（其他类型应该也不难）进行FFT。
一旦我的FFT能够工作，我就好奇它与一个备受尊敬且高度优化的FFT库相比速度如何。我不想批评这个很棒的库，所以我们就称它为FFT_BRANDX。在这个过程中，我了解到：
 - 1. FFT_BRANDX有超过10万行代码。而kiss_fft的核心大约是500行（一维复数）。
 - 2. 我花了长得令人尴尬的时间才让FFT_BRANDX正常工作。
 - 3. 使用FFT_BRANDX的一个简单程序大小为522KB。使用kiss_fft的类似程序大小为18KB（未进行大小优化）。
 - 4. 在默认模式下，FFT_BRANDX的速度大约是KISS FFT的两倍。
像FFT_BRANDX这样免费且高度优化的库的存在是很棒的。但是这样的库为了榨取每一点性能，背负着巨大的复杂性负担。**有时候，简单反而更好，即使它并非是最好的。**

## 常见问题解答
> 问：我可以在具有\_\_\_许可证的项目中使用kissfft吗？</br>
答：可以。请参阅下面的许可证。
> 问：为什么我没有得到预期的输出？</br>
答：最常见的两个原因是：
 - 1) 缩放：你得到的结果和你想要的结果之间是否有一个常数乘数？
 - 2) 混合构建环境 - 所有代码必须使用相同的预处理器定义进行编译，以确保FIXED_POINT和kiss_fft_scalar的一致性。
> 问：你会为我编写/调试代码吗？</br>
答：可能不会，除非你付钱给我。我很乐意回答有针对性和主题性的问题，但我可能会推荐你参考一本书、一个论坛或其他一些资源。

## 性能
（在Athlon XP 2100+上，使用gcc 2.96，浮点数据类型）
Kiss在0.63秒的CPU时间内完成了10000次1024点复数FFT。作为对比，md5sum处理相同数量的数据花费了两倍的时间。对5分钟CD质量的音频进行变换所需时间不到一秒（nfft = 1024）。
**请勿**：
 - 如果你需要世界上最快的傅里叶变换，请勿使用Kiss。
 - 请勿要求我添加会使代码膨胀的功能。

## 内部原理
Kiss FFT使用时间抽取、混合基、异地FFT。如果你给它的输入缓冲区和输出缓冲区相同，将会创建一个临时缓冲区来存储数据。不使用静态数据。kiss_fft的核心例程是线程安全的（但不是tools目录下的所有内容）。浮点版本不进行缩放（为了速度）。定点版本在正反两个方向都进行缩放（为了防止溢出）。对于因子2、3、4和5使用优化的蝶形运算。实数（即非复数）优化代码仅适用于偶数长度的FFT。它并行执行两个半长度的FFT（打包到实部和虚部），然后通过旋转因子将它们组合起来。结果是从直流到奈奎斯特的nfft/2 + 1个复数频域频段。如果你不知道这是什么意思，可以在网上搜索。快速卷积滤波使用重叠-舍弃方法，略有修改，将舍弃部分放在尾部。

## 许可证
修订后的BSD许可证，详细内容请参阅COPYING。基本上就是“可自由使用和修改，适当给予版权声明，不提供任何保证”。请注意，此许可证在频谱的一端与GPL兼容，在另一端与封闭的商业软件兼容。请参阅http://www.fsf.org/licensing/licenses。

## 待办事项
 - 为奇数长度的FFT添加实数优化
 - 记录/重新审视输入/输出FFT的缩放
 - 编写文档描述kiss_fastfir.c中的重叠（尾部）舍弃快速卷积滤波
 - 使用定点测试所有./tools/目录下的代码（kiss_fastfir.c不起作用，可能还有其他的）

## 作者
Mark Borgerding
Mark@Borgerding.net 
