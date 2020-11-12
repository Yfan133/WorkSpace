#include<iostream>
//Linux不以文件后缀区分，加后缀和颜色是为用户区分
//环境变量:就是一个变量,用于存储系统运行的环境参数
//操作指令:env set echo 查看环境变量 export 设置环境变量 unset 删除环境变量
//作用:
//1)通过修改环境变量的值,灵活的配置系统运行参数
//2)子进程会继承父进程的环境变量

///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Linux下以.为开头的文件默认不显示(隐藏文件)
//磁盘至少有两个分区：文件交换分区，文件系统分区（且交换分区只有一个，系统分区可以有多个）
//交换分区:作为交换内存使用，通常大小在16G以内，是内存的两倍，超过时相等即可
//文件系统分区：作为文件存储使用
//程序运行，运行信息占用的是内存，内存不够用了，把非活跃区内的数据放入磁盘上（文件交换分区）这样内存就有空间加载新的数据进行处理
//windows下磁盘分了多少分区，就可以有多少盘符，每个盘符都是一个大目录（给某个空间分配文件夹）
//linux下目录结构是惟一的，不会随着分区多少而改变（给某个目录分配空间）
//挂载是指：给某个目录分配一块磁盘空间，这个目录下的文件数据存储的时候就会存储到这个空间中

//目录操作
//绝对路径：以根目录作为起始表达的路径 例：./workspace/
//相对路径：是以某个路径
// .	表示目录自身
// ..	表示目录上一层
//mkdir -p 层层递进创建目录 rmdir -p 层层删除空目录(哪层为空就删除哪一层)
//rm -rf  删除目录及目录内所有文件
//批量删除以.h为后缀的文件 rm *.h
//cp -r  层层拷贝目录(文件)
//mv   (剪切)移动目录的位置

//文件操作
//touch  若文件不存在则创建，若存在则刷新文件的时间属性
//cat  分页显示文件内容
//head -n 显示文件前n行
//tail -n 显示文件尾n行
//echo  打印字符串，将数据写入标准输出(显示器设备文件)"sjk666" >> filename 把sjk666写入文件
//stat  查看文件状态
//>>或者>  重定向符号，进行数据流的重定向，文件重定向(echo "1" >> file将原本要写入标准输出的数据写入文件，改变数据的流向)
//>  先清空在输入数据
//>> 直接追加数据
//|  管道符连接两个命令（head -n 23 | tail -n 1）输出第12行

//打包指令
//压缩：将一个文件按压缩算法，将数据从多变少
/*
zip
gzip
bzip2
*/
//打包：将多个文件合并成一个文件
/*
tar  Linux下使用度很高的打包解包工具
-c打包 -x解包 -z打包同时进行gzip格式的压缩解压缩 -j打包同时进行bzip2格式的压缩解压缩 -v显示打包解包信息 -f用于指定tar包的名称，通常作为最后一个选项
tar -czvf new_name file	file				打包
tar -xvf  file(不加解包格式，则自动检测格式)	解包(默认解压到当前目录下)
*/
//单引号（会消除字符里特殊字符的特殊含义）双引号不会
//grep  从文件里查找匹配的行(文件里找函数)
//-v  反向匹配(不包含的行) -R  对某个目录进行层层寻找(每个文件都要查找)
//例：grep -i "sjk" ./op
//find  在目录中查找指定名称/大小/时间/类型的文件
//find ./ -name"*test*" (**为模糊匹配)  
//find ./ -type d 通过文件类型查找文件 -d -
//find ./ -size -10M  通过文件大小查找10M以内文件--+10M查找超过10M大小的文件
//find ./ -mmin -10  通过文件时间查找 --cmin,mmin,amin--分钟为单位
//
//		  -前面都有一个减号，为**以内
//tab  快捷键，文件名自动补全
//ctrl+c --中断当前操作

//shell的理解
//操作系统内核与用户之间的桥梁---命令行解释器
//shell会捕捉用户的标准输入，得到字符串，通过字符串判断用户想要干什么
//终端能执行命令就是因为运行了一个程序--shell--命令行解释器
//Windows下的shell就是操作界面(和操作内核沟通的桥梁)
//权限：限制用户权利的东西
//文件权限对用户：所有者-u，所属组-g，其他用户-o
//文件权限对操作：可读-r，可写-w，可执行-x
//在系统中权限的存储：使用二进制
// rw-rw-r--  --> 110 110 100  占用空间小，易操作
//也可以用八进制表示用户的权限110 110 100  --> 6 6 4

//文件访问权限指令
//umask -S(人性化显示) 查看或者设置文件的创建权限掩码
//umask 八进制掩码(显示的和权限八进制相反)，权限计算方法：777-八进制掩码
//创建好的文件进行权限修改
//chmod 777 hello.txt 直接使用八进制数进行修改
//chmod a-x hello.txt 对某个用户进行权限修改
//文件用户信息修改
//chown username filename 修改文件所有者(只能使用root修改)
//chgrp username filename 修改文件所属组
//文件权限沾滞位：特殊的权限位--主要用于设置目录沾滞位，其他用户在这个目录下能够创建文件，可以删除自己的文件，但不能删除别人的
//chmod +t filename

//vim 是一个命令行编辑器，不能使用鼠标(使用鼠标是无效的)
//vim具有多种操作模式：12种，常用的三种：插入模式，普通模式，底行模式
//普通模式：进行文本常见的操作-复制，剪切，粘贴，删除，撤销，返回，文本对齐，光标的快速移动
//底行模式：进行文本的保存退出，以及文本的匹配查找替换操作
//vim filename 若文件不存在创建，存在则打开，打开后处于普通模式
//:q!强制退出(不保存)
//i进入插入模式，a后移一个并插入，o新建一行并插入
//光标移动：hjkl上下左右，w/b按单词移动，ctrl+f/b上下翻页
//文本操作：yy/nyy-复制；p/P-粘贴,dd/ndd删除/剪切,x-删除光标所在字符,dw-删除单词
//u-撤销，ctrl+r-反撤销，gg=G--全文对齐

//编译器：gcc/g++
//gcc是C语言的编译器;g++是C++的编译器
/*编译过程											   -o 指定生成文件名称
预处理：将代码展开（引入头文件，宏替换，删除注释....） gcc-E filename 只进行预处理
编译：纠错，并将高级代码解释为汇编代码				   gcc-S		  只进行编译
汇编：将汇编代码解释成机器指令						   gcc-c		  只进行汇编
链接：将所有用到的机器指令文件打包到一起，生成可执行程序,不仅仅是我们的代码文件，还包括库文件(a.c文件引用了b.h中的函数)
*/

//链接库文件的时候有两种链接方式：动态链接与静态链接
//动态链接：链接动态库，在可执行程序中记录函数符号信息表，生成可执行程序比较小，但是运行时需要加载动态库，多个程序可以使用同一库，不会在内存中造成代码冗余
//静态链接：链接静态库，直接将使用的函数写入可执行程序中，生成的可执行程序比较大，运行时不需要额外加载库，多个程序使用了相同的静态库，运行时会造成内存的代码冗余
//gcc默认链接方式：动态链接
//gcc -g a.c b.h -o main
//调试器:gdb
//加载调试：gdb ./main
//开始调试：run  直接运行 start  逐步调试
//流程控制：n  下一步(逐过程)  s  下一步(逐语句)
//			l a.c:25  查看调试行附近代码  until a.c:25  直接运行到指定行
//			c 继续运行直到断点
//断点控制：break a.c:9  给第9行打断点  watch a  给变量打断点，当变量的值发生改变时停下来  d  删除断点
//内存操作：p a 查看变量数据 backtrace查看程序运行调用栈信息，程序一旦崩溃，查看调用栈可以快速定位崩溃位置--栈顶函数

//make/Makefile
//Makefile:普通的文本文件，用于记录
//$@:表示目标对象  main
//$^:表示所有依赖对象 a.c b.c
//$<:表示所有依赖对象中的第一个依赖对象
//wildcard/patsubst 关键字的使用
//make clean 清除make生成的对象
//伪对象的使用：
//.PHONY:目标对象名称
//伪对象的作用:不管对象是否最新，每次都要重新生成
//Makefile中
/*
.PHONY:clean
clean:
	rm -rf main.o main
*/

//git：项目版本管理工具
//1.git clone +链接  从远程仓库克隆到本地 
//2.git add ./*    添加本地文件
//3.git commit -m"删除了一个无效文件"  把文件保存到本地git
//4.git push origin master			   推送到git上

//进程概念：
//冯诺依曼体系结构---现代计算机的硬件体系结构
//现代计算机的硬件体系结构：五大硬件单元
//输入设备：采集数据的，如键盘
//存储器：进行中间数据缓冲， 
//运算器：进行数据处理  运算器+控制器=CPU中央处理器
//控制器：进行设备控制
//所有设备都是围绕存储器工作的：
//CPU不会直接从输入设备获取数据进行处理，而是先把数据放到存储器中，CPU从存储里中获取数据处理
//CPU不会直接将数据交给输出设备进行输出，而是把数据放入存储器，控制输出设备从存储器中获取数据并输出
//存储器就是运行内存，因为CPU从内存中读取数据速度是硬盘的十数倍。但内存中存储的数据在掉电之后就消失了，而硬盘掉电之后数据不会丢失，因此存储数据还是用硬盘。

//操作系统：是一个搞管理的软件（安装在计算机上的一个程序），管理计算机上的软硬件资源
//操作系统组成：内核(负责系统的核心功能-软硬件管理,内存管理,文件管理)+外部应用
//用户不能直接访问操作系统内核（危险性太高），为了控制风险，系统内核提供了一些访问的接口，每个接口完成的功能都是固定的---系统调用接口
//用户
//->系统调用接口：操作系统向用户提供访问内核的接口(shell指令,库函数封装了一系列系统调用接口)
//->操作系统
//->硬件驱动
//->（键盘鼠标等）


//什么是进程？为什么是这样？
//进程：进行中的程序，
//一个程序运行起来，有数据以及指令需要被CPU执行处理，数据会被加载到内存中，然后CPU从内存中获取数据
//操作系统中的进程都是同时运行的，但CPU只有一个，如何做到多个程序同时运行?
//CPU的分时机制：实现CPU轮询处理每一个运行中的程序，其实CPU只负责执行指令并处理数据（具体处理哪个程序CPU不管），而程序运行调度由操作系统进行管理，CPU处理运行的程序时，并不会一次性处理完毕，而是每个程序都只执行一个时间段(片)(该时间片由操作系统分配)，一个程序执行完一个时间片之后，下一个拿到时间片的程序开始执行
//调度：操作系统控制CPU该处理哪一个程序了

//操作系统的具体管理思路：操作系统将每个程序的运行信息保存下来,这样进行管理调度时就能知道这个程序上一次运行到了哪里
//对于操作系统来说，进程就是PCB，是一个程序运行的动态描述，通过PCB就能实现程序的运行的调度管理
//PCB内的描述信息：（Linux下的PCB就是一个struct task_struct结构体）
/*
内存指针：能够让操作系统调度程序运行的时候，知道程序对应的指令和数据在内存中的位置
上下文数据：CPU处理过的程序的指令和数据，正在处理中的指令和数据，即将要处理的指令和数据，操作系统进行调度让CPU处理程序上次未处理完成的数据，切换时保存正在执行的指令以及数据信息
程序计数器：也属于上下文数据，保存的就是指令位置，切换回来知道从哪里继续运行
标识符：能够让操作系统识别唯一的运行中的程序
IO信息,状态信息，优先级，记账信息
并发：CPU资源不够的情况下，采用CPU分时机制，CPU轮询处理数据（十个人过独木桥）
并行：多核CPU上，多个进程同时占据CPU进行数据处理（十个人并排过马路）
*/

//进程状态:每个进程PCB中都会描述一个运行的状态信息，通过状态信息，告诉操作系统这个进程现在应该干什么
//时间片：操作系统给每个程序分配的CPU处理时间，时间片运行完了就切换另一个程序
//进程状态：就绪，运行，阻塞(拿到时间片也不会运行)

//进程状态在Linux下分的更细
//(-R)运行状态-R：包含就绪以及运行，也就说正在运行的，以及拿到时间片就能运行的都称之为运行状态，操作系统读取PCB的状态信息之后就能调度运行
//休眠：暂时没有被CPU调度运行，让出CPU资源，休眠有唤醒条件，操作系统调度运行时会查看状态，满足唤醒条件则运行，不满足则切换下一个程序
//(-S)可中断休眠状态-S：可以被打断的休眠，满足运行条件或者被一些中断打断休眠之后进入运行状态
//(-D)不可中断休眠状态-D:只能通过满足运行条件之后，自然进入运行状态
//(-T)停止-T：与休眠不同(操作系统会查看进程是否满足唤醒条件，而停止只能手动唤醒)
//(-Z)僵尸状态-Z：一个进程已经退出，但是该进程的资源没有完全被释放，等待处理的一种状态
//僵尸进程：退出了但是资源没有完全释放的进程
/*
僵尸进程
危害：资源泄露（可能导致正常进程起不来）
产生原因：一个进程先于父进程退出，父进程没有关注子进程退出状态，导致子进程资源无法完全被释放，进入僵尸状态
解决：进程等待--一直关注子进程的状态

进程的创建：pid_t fork(void) --通过复制调用fork进程，创建一个新的进程
进程就是PCB，创建一个进程就是创建了一个PCB，上面复制调用了fork这个进程的PCB信息(内存指针，程序计数器，上下文数据)，新进程的运行代码和fork的一样，并且运行位置也一样
两个进程运行的程序相同：哪个是调用进程(父进程)，哪个是新建进程(子进程)？
在父进程中返回子进程的pid（pid_t pid=fork( )），大于0的；在子进程中返回0;但返回-1表示创建子进程失败

子进程从pid=fork()之后开始运行，因为父子进程运行代码的数据一样，所以无法直接分辨，只能通过返回值判断
对于父进程fork返回值>0  对于子进程返回值==0
fork创建子进程之后，父子进程谁先运行不一定，操作系统调度到谁谁就运行
为什么子进程会从fork()之后开始执行？
父子进程pcb一模一样，子进程pcb中的程序计数器(记录程序执行到哪里了，接下来该执行什么代码)记录的就是fork()这一行代码，因此从fork以下开始执行
getpid()获取调用进程的标识符pid
孤儿进程：父进程先于子进程退出，子进程就会成为孤儿进程
特性：让出终端，进入系统后台运行并且父进程成为1号进程，1号进程在centos7之前叫init进程，之后叫systemd，系统中父进程是1号进程的进程，通常以d结尾，表示它在后台运行
课后调研：守护进程、精灵进程
守护进程：特殊的孤儿进程，不但运行在后台，父进程成为1号进程，并且还与登录终端以及会话脱离关系(为了一个进程稳定不受影响的运行在后台)
*/
//查看进程信息
//ps -ef|head -1 && ps -ef|grep fork 显示fork进程ppid父进程,pid子进程
//ps -aux | grep test	aux详细显示，会显示进程当前状态
//前台进程：当前占据了终端的进程，

//环境变量：终端shell中进行系统运行环境配置的变量
//作用：1.可以使系统环境配置更加灵活(不像修改配置文件后还得加载配置问题)  2.可以通过环境变量向子程序传递数据
//操作指令：env -查看所有环境变量 echo--直接打印某个变量的内容  echo $PATH($表示后面的字符串是一个变量名称)export PATH=$PATH:. set-查看所有变量，不只是环境变量 export声明定义一个环境变量 unset-删除一个变量，也可以是环境变量
//export MYVAL=100;
//PATH：当前搜索程序运行路径
//运行一个程序的时候，如果没有指定程序路径，只有名称则shell会去PATH环境变量保存的路径中去找这个程序
//代码操作：char *getenv(char *key)
//在终端中运行的程序，父进程都是bash，也就是shell程序
//在终端中运行一个程序，其实是shell创建了一个进程，让这个进程去调度我们要运行的程序，这样做可以提高稳定性，创建出的进程崩溃了，shell还可以继续运行

//环境变量可以1.配置系统运行环境参数 2.向子程序传递一些数据(子进程会拥有与父进程相同的环境变量)
//环境变量一直都存在，可以在main函数参数列表中写出来，用于接收环境变量，一般嫌麻烦而省略了main函数的参数列表(不定参函数)
//main函数的三个参数：int main(int argc, char *argv[], char *env[])
//extern char **environ; 库中的全局变量，每个节点指向一个环境变量，但是使用时需要声明，告诉编译器有这个变量
//这种临时创建的环境变量，在重新打开终端之后就没有了，想持久配置就把信息加入到配置文件中
//课后调研：设置环境变量  setenv()/putenv()
/*
//////////////////////////////////////////////
通过代码查看(获取)环境变量
argc-->程序运行参数个数
argv[]-->用于执行程序中各个环境变量的一个字符串指针数组
./env -l -a  [./env]是第0个参数，[-l]是第一个参数，[-a]是第二个参数
env[]用于指向程序各个环境变量的一个字符串指针数组
1.
int main(int argc, char *argv[], char *env[])
{
	int i;
	for(i=0;env[i]!=NULL;i++)
		printf("environment:[%s]\n",env[i]);
}
2.
extern char **environ;
int i;
for(i=0;env[i]!=NULL;i++)
	printf("environment:[%s]\n",env[i]);
*/

//程序地址空间（进程地址空间）
//地址:内存地址---对内存以字节为存储单元的一个编号,32位内存大小4G(也就是0x0000 0000到0xffff ffff)
/*
内核空间
环境变量,运行参数
栈(往下生长)
...
...(共享区)
堆(往上生长)
未初始化全局
初始化全局
代码段
*/
//在父子进程fork()代码中父子进程代码共享，数据独有，但打印的父子进程地址相同，子进程内g_val=200，为什么呢？
//其实我们访问的地址都是虚拟地址--并非真正的内存地址，打印出来的都是虚拟地址，但其实在内存中地址不同
//若进程直接访问物理内存有哪些缺点：1.无法动态获知哪块内存是否被使用，程序编译时，编译器会给指令和数据进行地址编号，但如果该地址被使用程序就运行不起来了
//									2.如果该进程中有一个野指针，在直接访问物理内存时可能会改变其它地址的数据，造成其它程序崩溃
//									3.程序运行加载需要一块连续的内存空间，对物理内存利用率很低
//通过虚拟地址空间映射到物理内存空间，可以提高物理内存利用率,虚拟内存是连续的,每个进程都会拥有自己的一块连续的空间，但实际上在物理内存中是离散存储的
//如何通过虚拟空间地址找到物理地址空间？
//操作系统的内存管理方式:分段式(段号)，分页式(页表)，段页式
/*
分段式:
通过段号在段表中查到初始内存地址,再用初始内存地址+段内偏移量找到对应的物理内存单元
分段式中每个段内数据的起始内存地址都是相同的，也就是说还是用了连续的物理内存空间无法离散式存储，未解决内存利用率低的问题
分页式:
通过页号查到初始内存地址,再用初始内存地址+页内偏移量找到对应的物理内存单元
优点:物理内存块大小跟虚拟内存页大小一样,物理内存块比较小,并且不要求同一进程的多个数据必须在同一个块内,因此分页式实现了数据在物理内存中的离散式存储,提高了内存利用率
页表会在进行内存访问时会进行内存访问权限查询(页表和)
十进制计算方法：虚拟地址/页表大小  ->找到对应物理地址+虚拟地址%页表大小
十六进制计算方法：虚拟地址高二十位是页号 ->找到对应物理地址+低二十位
页号占据的是高位，有2^20个页表所以占高20位，低20位为偏移量
32位操作系统 内存4G/4k == 页表项(页号)的个数 == 2^20  页表大小4096=4*1024=4k
段页式：将内存进行分段(代码段，数据段，堆，栈，环境变量等等)，在每个段内采用分页式管理
页表中有一个中断位--缺页中断，表示当前虚拟地址要找的数据是否在物理内存中(如果没在则会触发缺页中断)
一个进程的数据怎么会不在内存中呢？
内存管理：磁盘在分区的时候，至少有两个分区--交换分区和文件系统分区(用于文件数据存储)，内存不够时将内存中的某些不活跃的数据腾出来放到交换分区中，腾出空间给紧急的数据，等到使用该数据触发缺页中断时再交换回来/文件系统分区--用于文件数据存储
课后调研：内存置换算法:最久未使用（怎么快速定位最久未使用的数据）

进程控制：创建，终止，等待，程序替换
创建：如何创建一个进程？
	pid_t pid fork()；
	子进程复制父进程pcb，页表，虚拟地址空间都一样，所以刚开始父子进程除了个别数据(标识符pid)之外都是一样的，并且父子进程的数据指向同一块物理内存
	写时拷贝技术：子进程创建出来之后，与父进程映射访问同一物理内存，当某个物理内存中数据即将发生改变时(父进程数据发生改变或者子进程)重新为子进程开辟物理内存，拷贝数据过去。好处：防止给子进程创建空间，但子进程不用，降低了进程的创建效率，且造成内存冗余数据
	返回值：父进程pid>0，子进程pid==0，pid<0错误，通过返回值可以区分父子进程
	pid_t pid=vfork():
	也是创建子进程，但一个父进程使用vfork创建子进程之后，vfork的调用并不会立即返回(通常说会阻塞父进程)而是让子进程先运行，直到子进程退出，或者进行程序替换之后，父进程才能运行
	在程序运行中每调用一个函数，就会进行一次函数压栈---函数调用栈,vfork父子进程可能会造成栈混乱
	vfork的父子进程使用的同一块虚拟地址空间，也就是说使用了同一个栈，若父子进程同时运行则会造成调用栈混乱，因此让父进程等待子进程退出或者程序替换后，有了自己的地址空间(在原有的地址空间中子进程的调用就都出栈了)才开始运行
	pid_t vfork(void)  会造成死循环(vfork创建的子进程，不能在main函数中使用return退出，因为子进程使用return退出时释放了所有资源,父进程运行的时候资源是错误的)
	当父进程在main函数中调用fork函数创建子进程，fork运行完毕之后，父进程应该从调用fork函数的下一步开始执行
	fork父子进程各有各的栈，vfork父子进程共用同一块栈区
	总之vfork父子进程同一空间，fork父子进程不同空间
	问题：为什么vfork会造成无限循环？个人猜测：return释放资源后，父进程混乱
终止：如何退出一个进程？
	main函数中的return
	exit();可以在任何位置退出程序，库函数，exit退出进程时会刷新缓冲区，将缓冲区的数据写入标准输出
	_exit();					   系统调用接口，_exit退出进程直接释放资源，不会刷新缓冲区
	printf打印数据，实际上是把数据交给显示器，让显示器显示。先放入数据缓冲区，等积累到一定数量之后一次性输出(缓冲区满了)，这样做会提高程序运行效率。
	(\n)除了换行的作用之外，还有刷新缓冲区的作用，标准输出（使数据输出），\r回车
	fflush(stdout);刷新缓冲区
*/
/*
进程等待：为了获取退出子进程返回值，父进程等待子进程退出，释放退出子进程的所有资源，避免产生僵尸进程
僵尸进程产生原因：子进程先于父进程退出，而父进程没有关注子进程的退出信息，子进程为了保存退出返回值，而无法完全释放资源产生的
int wait(int *status);  阻塞接口，若没有子进程退出，则父进程阻塞，一直等待直到有子进程退出才会调用返回
int waitpid(int pid,int *status;int option);与wait不同，默认为非阻塞，父进程不会等待子进程退出，若没有子进程退出waitpid返回-1
	阻塞：为了完成一个功能，发起一个调用，若不具备完成功能的条件，则调用一直等待
	非阻塞：为了完成一个功能，发起一个调用，若不具备完成功能的条件，则调用立即报错并返回
	返回值：成功则返回处理过的子进程的pid，失败则返回-1(比如没有子进程退出)
正常退出：程序运行到return或者exit自然退出，
异常退出：程序在运行过程中崩溃而退出
子进程退出而父进程没有等待处理，都会变成僵尸进程
wait和waitpid的不同之处：
1.wait等待任意一个子进程退出后,就处理子进程并返回
  waitpid可以等待指定子进程，也可以等待任意一个子进程，通过第一个参数确定(第一个参数pid==-1则表示等待任意)
2.wait是阻塞接口（没有子进程退出则一直等待）
  waitpid可以默认成阻塞，也可设置为非阻塞，通过第三个参数确定(option==0表示默认阻塞，option==WNOHANG表示非阻塞)
进程等待返回值：成功返回退出，则子进程的pid，没有子进程退出返回0，错误返回-1
非阻塞操作通常循环处理，直到有子进程退出，处理并返回大于0的数

一个进程在运行中突然崩溃，这是由于一些异常引起的，进程自己怎么知道自己发生了异常呢？
由操作系统检测，操作系统检测到进程的低7位异常退出信号，则通知进程退出
怎么判断一个进程是否正常退出，取出低七位；用status & 0x7f ==0则正常退出
0x7f == 0111 1111
怎么取出返回值---低16位中的高8位？(status>>8) & 0xff
返回值只用8位(一个字节)保存，因此退出返回值不要大于255，即exit(255);最大了
if((status & 0x7f)==0)
	printf("退出返回值：%d\n",(status>>8) & 0xff);
用系统调用接口取出返回值：
if(WIFEXITED(status))
	printf("退出返回值：%d\n",WEXITSTATUS(status));
查看错误在哪里:#include<errno.h> #include<string.h>
int res=wait(NULL);
if(res<0){
	printf("%s\n",strerror(errno)); //errno是一个全局变量-保存上一次系统调用的错误编号
	perror("wait error");
}
core dump---核心转储
当一个程序崩溃之后，我们想要调试找到程序崩溃位置，以及崩溃原因，core dump会保存异常退出信息
gdb wait进入调试，输入core-file+拷贝文件名，就能定位出错位置了，bt查看堆栈信息
*/

/*
进程程序替换：替换一个进程，正在调度运行的程序
将当前进程的数据段和代码段进行替换，替换成为其他程序的数据和代码，并且更新堆栈数据
进程替换其实是修改了映射关系，把本来映射到内存中main的重新定位到test，这样也就修改了数据和代码
fork创建一个子进程，代码共享数据独有---父子进程做的事一样，但通常创建一个子进程是为了让子进程运行其他程序
execl("./a",NULL,NULL)；在当前目录下找a，不定参数为NULL
程序替换之后将会看到：1.进程标识符 pid 是没有变化的
					  2.
#include<unistd.h>
extern char**environ;
int execl("路径"，字符串，)  execl("ls的路径","ls","-l",NULL);不加路径则当前路径
int execlp					 execlp("ls","ls","-l",NULL);在PATH下寻找
int execle
l和v的区别：参数赋予方式不同
有没有p的区别：新的程序文件的名称是否需要带路径
有没有e的区别：是否自定义环境变量
int execv("路径"，指针数组)
int execvp
int execve
若程序替换失败则运行原本的代码
问题：程序替换之后，如果子程序执行时间比较长，而父进程很快就执行完毕了，会不会造成僵尸进程？
	不会进程替换之后，子进程不再是子进程了，而是一个新的进程
问题：为什么execlp("ls","ls","l",NULL);要写两次"ls"才能执行ls -l
Linux下一切皆文件，pwd在shell上是指令，其实就是一个可执行程序(文件)
32位操作系统内核：4G
1G	内核空间			 0x FFFF FFFF	
3G						 0x C000 0000
	命令行参数和环境变量
		栈
		.
		共享区
		.				 
		堆
		数据段
		代码段			 0x 0000 0000
*/
//minishell的工作
//1.能够从标准输入当中接收用户输入的命令
//2.创建子进程
//3.子进程进行程序替换
/////////////////////////////////////////////////////////////////////
//perror();非常好用的一个判断错误



/*
基础IO
1.C语言操作文件接口
	fopen(const char *Path，const char *mode);Path:文件地址+文件名称，Way读取方式
	FILE* fp=fopen("./Demo","r");
	fwrite(* ptr,size,nmemb,* stream);ptr:往文件里写的内容，size;写入的大小，nmemb：数量，stream：文件指针
	一般把size设置为1，则nmemb为字节大小,fwrite("aaa",1,3,fp);fwrite返回的是写成功的数量
	fread(* ptr,size,nmemb,* stream);ptr将读到的内容保存的位置
	fread(b, size, N, fp);从文件读取内容并保存到数组b，返回读的数量
	"linux_57" 这个字符串常量最后面有一个'\0'
	fseek(* stream,offset,whence);offset偏移量,whence:SEEK_SET:头部 SEEK_CUR:偏移到指定位置 SEEK_END:末尾
	调整文件指针偏移量
2.系统调用函数的操作文件接口 open,read,write,lseek,close
	open(* pathname,int flags,mode_t mode);		返回值：打开成功返回文件描述符，失败返回-1
	O_RDONLY	只读			八进制0		
	O_WRONLY	只写				  1
	O_RDWR		可读写				  2
	O_CREAT		不存在则创建文件	  100
	int fd = open("path",O_RDWR | O_CREAT,0664）可读写，没有创建，权限664(八进制)->对应二进制 110 110 100
	O_RDWR | O_CREAT
	00000000 00000000 00000000 00000010		八进制2	  可读可写
	00000000 00000000 00000000 01000010		八进制100 创建
	按位或(有1则为1)
	00000000 00000000 00000000 01000010
								^    ^
	这八个比特位表示不同的打开文件方式，当前是可读可写且创建
	read(fd,* buf,count);fd文件描述符，open的返回值,buf读到哪里去，count最大可以读多少个，返回写成功的大小
	lseek()
	close()

	int fd=open()		->文件描述符
	write(fd,"linux-57",8);
	lseek(fd,0,SEEK_SET);
	char buf[1024]={0};
	read(fd,buf,sizeof(buf)-1);	//buf最后面要留一个'\0'的位置
3.文件描述符  fd
	cd /proc/
	ll /proc/标识符/fd
	操作系统会给每个进程在磁盘中创建一个以进程号(pid:进程标识符)命名的文件夹，该文件下有一个fd文件夹，保存的是文件描述符
	新创建的进程会打开三个文件描述符，分别对应，标准输入(0)，标准输出(1)，标准错误(2)，不关闭前三个则打开其他（3），没有关闭会造成句柄泄露
	创建一个进程相当于创建了一个task_struct结构体，这个结构体里有叫files的结构体指针，指向叫files_struct的结构体，这个结构体内有数组fd_array保存着很多文件描述符（struct file*）（保存着文件原信息，文件大小，权限等等），数组fd_array[]的下标
	文件描述符是一个正整数，close(0);关闭了标准输入，再fp=open()打开文件则给fd分配0，按从零开始最小数分配
	
	FILE是typedef struct _IO_FILE，里面保存着读写缓冲区(C库中的东西)，最下面还有一个指针int _fileno，保存的就是文件描述符的数值，exit()退出时刷新缓冲区就是读缓冲区，操作的是文件流指针，而_exit()无法刷新是因为它是系统调用接口
	不同的文件流指针，在C库中会创建不同的struct _IO_FILE，
4.文件描述符和文件流指针的区别，文件流指针也就是FILE* fp中有一个指针int _fileno；保存的就是文件描述符的数值
	1)文件流指针是fopen函数返回的，是库函数维护的
	2)文件描述符是open函数返回的，是内核维护的
	C语言中FILE 在操作系统中其实是struct _IO_FILE 结构体：
	不同文件流指针会创建不同的IO结构体，保存了不同的文件描述符，文件流指针里保存着很多文件描述符
	c库维护的exit函数在退出时，会刷新缓冲区，而操作系统接口_exit函数不会刷新缓冲区
5.重定向接口
	>>和>
	重新让标准输出，由屏幕指向文件，相当于把指向文件描述符 0 的指针转为指向文件描述符 1
	dup2(int oldfd，int newfd)；newfd拷贝oldfd的值
	dup2(fd,1);关闭1号文件描述符，并拷贝fd的文件描述符，也就是把原本标准输出到屏幕的，重新输入到文件中
	修改fd相当于修改了本进程的文件描述符，进程最多打开1024-3个文件，其实那三个指向同一个设备文件/dev/pts/2

当打开一个文件时，系统会给程序分配一个文件描述符，如果使用完毕没有关闭文件，就会造成文件句柄泄露，
一个进程当中最大打开的文件数量是多少？
1.默认打开文件数量1024   其实真实不是1024，（3~1023）要减去默认的三个文件，0：标准输入，1：标准输出，2：标准错误 实际打开文件1021
2.ulimit -n[num]更改最大打开数量为num，ulimit -a 查看设置权限
	ulimit -n2020

	
动态库和静态库
查看当前程序依赖的动态库文件：ldd+可执行程序
	例：ldd vfork  libc.so.6 ---> C动态库 包括(ls,mv等等)
	ldd+静态链接文件 not a dynamic executable
查看文件属性：file+可执行程序
	file vfork
	1.动态库
	libc.so.6 => /lib64/libc.so.6 (0x00007fc458bb9000) C动态库
	生成动态库
	gcc/g++ 库文件.c -shared -fPIC -o 库.o  
	生成动态库相当于头文件指向函数的实现文件，函数声明都在.h头文件，函数实现在.c库文件，然后生成库
	
	指定动态库
	gcc main.c -o main -L ./ -l库里面的函数 
	编译动态库的源码中不能出现main函数
	编译可执行程序时，必须告诉编译器链接的动态库是哪个？，否则发生链接错误。指定链接动态库所在路径和名字，
	gcc main.c -o main -L . -lfunc  (-L+路径，-l+库的名称)，可执行程序在找动态库时会默认在当前路径下寻找
	若把动态库移到别的地方：移回来或者把位置放到环境变量中，就不会发生链接错误
	
静态库  必须加static 不然就是动态链接
	Windows中静态库是以.lib为后缀的，动态库为.dll，编译依赖.lib库文件，运行时依赖.dll文件
	生成
	gcc/g++
	shared fPIC
	-o后面生成的动态库名字
		前缀：lib
		后缀：io
	ar -rc libfunc.a test.c   用源码会报错
	先gcc -c test.c -o test.o  生成汇编
	ar -rc libfunc.a test.o（这个依赖文件为.o汇编之后的，不是原文件）
	使用
	gcc main.c -o main -L . -lfunc 
	
动态链接和静态链接最大区别：有没有static
静态库用动态方式链接，文件会很大，但把生成的库删除，仍然可以执行

文件系统
线性存储方式可能会导致磁盘利用率较低，离散式存储能提高磁盘利用率，ext2文件系统就是采用了离散式存储，每个比特位表示Data blocks中块的使用情况，为1表示占用，0表示空闲

文件存储：在BlockBitMap中查找空闲block块，将文件存储在空闲的block块当中，再通过inode BitMap获取空闲的inode节点，在空闲的inode节点描述文件在DataBlock区域当中存储的位置
inode

软硬链接
	软链接(类似快捷方式或者说别名)：In -s hello aaa 
	它只会在你选定的位置上（不写位置默认当前路径下）生成一个文件的镜像，不会占用磁盘空间
	ll -i 可以看到两个的inode节点号不同，软链接文件具有独立的inode节点号
	在删除软链接文件或者软链接文件指向的原文件时，两者都应该同时删除
	硬链接：In hello bbb
	ll- i 可以看到两个的inode节点一模一样，一个文件生成了两个有效路径
	问题：为什么删除原文件之后，硬链接的文件仍然存在？
	因为硬链接是在选定的位置上生成一个和源文件大小相同的文件，硬连接的作用是允许一个文件拥有多个有效路径名，这样用户就可以建立硬连接到重要文件，以防止“误删”的功能
无论是软链接还是硬链接，文件都保持同步变化
*/

/*
进程间通信
为什么需要进程间通信？
进程都拥有自己独立的虚拟地址空间，造成了进程的独立性，通过进程间通信，可以让不同进程进行协作(数据交换或者进程控制)，例QQ中交流
网络就是一个进程间通信，信息在不同进程中传递
1.管道
	管道符 | 链接两个命令，把第一个输出的结果给第二个命令作为输入
	管道本质就是在内核当中开辟的一块内存，也可以称之为内核缓冲区，这段空间没有标识符，因此其他进程也就无法
	用户态        ps aux | grep xxx
	内核态             缓冲区	ps -aux被加载到缓冲区，然后给grep xxx
匿名管道
	在内核中创建出来的一块内存是没有标识符的,所以管道开辟的内存没有
	如何创建一个管道？int pipe(int  fd[2])；fd[2]整形数组，保存的是文件描述符(新创建两个文件描述符fd[0]=3读端,fd[1]=4写端，0：标准输入，1：标准输出，3：标准错误)，两个元素。fd[0]：读端，读匿名内存,fd[1]：写端，数据流向由写端--->流向读端
	fd是输出型参数，用时不需要输入值
	成功返回0；失败-1
	int fd[2]; int a=pipe(fd);
	闪烁原因：1.指向内核的内存 2.不存在
	
进程标识符也就是进程号，也就是pid
每个进程(task_struct)，其实都是一个双向链表将所有进程链接，优点:方便CPU调度，当一个进程结束，则这个双向链表清除一个节点，但有一个特殊的，僵尸进程！！尽管退出但不会被双向链表清除
在pipe的程序中，写入操作，写入了内存的缓冲区(之前一直在想管道是连接两个进程，那写入了哪一个进程呢，其实没有写入进程，而是写入了匿名管道)，读出来之后缓冲区中的就没了
查看进程调用栈：pstack + 进程号，应该从下往上看，可以看到25行卡住调用栈，因为管道中没有内容了。

因为读端读过之后，内存缓冲区就没数据了，所以管道的数据流只能是从写-->读，但读端可以决定每次读多少字节
管道生命周期跟随进程退出而结束
用于获取进程标识符的信息，int flag=fcntl(int fd，int cmd，...)...是可变参数列表
flag = 0代表只读，1代表写，f[0]读端--->O_RDONLY，f[1]写端--->O_WRONLY，
因为管道在内存缓冲区中是没有pid的，所以必须是具有亲缘关系的(父子进程)才能操作同一个内存缓冲区，因此必须先创建管道，再创建子进程(拷贝task_struct结构体,里面有files_struct结构体，里面放着文件描述符)
子进程输入，父进程读取，这就是进程间通信

管道在内存的缓冲区有多大（能存多少字节）：64k  pipe_buf==4k 同时写入时，最大写入4k就要切换另一个，写入4k，再切换回来，写入小于4k则保证原子性
临界资源：同一时刻，当前的资源是能被一个进程所访问，如果多个进程同时去修改临界资源，可能会导致数据二义性
如何保证对临界资源访问的合理性，即不会造成数据二义？
互斥：同一时刻，保证只能有一个进程访问
同步：保证了进程对临界访问的合理性
读写端默认为阻塞(写入的数据，读两次，第二次读会阻塞)，非阻塞O_NONBLOCK
int flag = fcntl(fd,F_GETFL);	F_GETFL:获取文件描述符的属性
fcntl(fd,F_SETFL,flag | NONBLOCK); F_SETFL：设置文件属性（当前是读且非阻塞）因为每一个比特位都表示不同含义
为什么要与，NONBLOCK八进制是400，转换成二进制有1的位置是代表非阻塞，和flag与就能非阻塞还带有flag的属性
写端为非阻塞(子进程一直写),读端关闭(父进程)，当管道满了，程序会把write的进程退出(子进程)，但这时父进程还在while无限循环，造成僵尸进程
	
阻塞了的进程会退出吗？
不会退出，进程会一直卡住
下来测试父子进程中都输出，多次运行看父子进程谁先走，两个依次while循环
测试结果父子进程不一定谁先运行

下面是4种情况
1.写端非阻塞
	1.读端关闭，写端一直写，写满后，write收到管道破裂信号SIGPIPE，进程直接被退出，如果子进程是写端可能会造成僵尸进程
	2.读端不关闭，但也不读，write一直写，写到满时返回-1并报错资源不可用
2.读端非阻塞
	1.写端关闭，读端一直读，read返回0
	2.写端不关闭，读端一直读，read返回-1，表示资源不可用(管道为空)

命名管道：
创建：
命名管道标识符大小为0，它只是一个管道文件，真正存储的位置在内核缓冲区
int ret = mkfifo("./fifo.test",0664); //在当前目录创建fifo.test为名管道，权限0664
if(ret<0)
{
	perror("mkfifo");
	return -1;
}
int fd = open("./fifo.test",O_RDONLY);以只读打开命名管道
特点：
1.生命周期：跟随程序(进程)
2.具有标识符(fifo)，因此两个进程不需要具有亲缘关系，就可以进行进程间通信
3.其它特点：匿名管道相同
//////////////////////////////////////////////////////////////////////////////////////////////

共享内存：
虽然不同进程具有不同的虚拟内存空间，但映射同一块物理内存，而且虚拟地址中间有一块共享区，
这块共享区映射了物理内存的一块共享内存，操作这段共享区则可实现进程间通信。具体操作方式：
在共享内存开辟一段空间，不同的进程可以把这段空间附加到自己的共享区中，这些进程可以通过
共享区来交换数据。
	画一个图来解释这个现象
共享区操作原理:
1.先在物理内存中开辟一段空间
2.各个进程通过页表把这段物理内存映射到自己的虚拟内存地址
3.不同进程对共享内存区域进行读之后，这段内存的数据并不会被清除

1.创建：
	int shmget(key_t key，size_t size，int shmflg)；
	int shmid=shmget(KEY,1024,IPC_CREAT|0664); 
	key：共享内存段的名字，可以任意设置，但不能和操作系统中其它内存段名字一样 
		用例:#define key 0x9999999
	size：共享内存大小，单位为字节
	shmflg：用或的结果
	IPC_CREAT：不存在则创建共享内存，如果存在则返回共享内存的造作句柄（有点类似文件描述符）
	IPC_EXCL：是一个辅助，提示信息
	IPC_CREAT | IPC_EXCL：1.以key为名的共享内存已存在，则报错。2.不存在并创建，返回操作句柄
返回值：返回共享内存的操作句柄（有点类似文件描述符）
问题：标识符key用来表示共享内存，它是一个地址吗？
不是，在Linux中可以把它理解成一个内存段的名字，

共享内存段名和共享内存的操作句柄的区别：
操作句柄(shmget的返回值ret)：通过句柄，进程可以对共享内存进行操作(附加，分离，删除等)
内存段名(key)：不同进程通过内存段名可以找到共享内存，是用来识别共享内存的

2.删除共享内存：
	ipcrm -m+[操作句柄]
3.将共享内存附加到一个进程：
	void* shmat(int shmid，const void* shmaddr，int shmflg);
	void* lp=shmat(shmid,NULL,0);
	shmid:共享内存操作句柄
	shmaddr：指定将物理内存映射到哪一个虚拟地址，一般都写NULL操作系统自动选择一个虚拟地址，并把进程附加到共享内存中
	shmflg：一般都为0：可读可写
	SHM_RDONLY：只读

返回值：成功返回指针，指向共享内存的地址，操作这个地址就可以操作物理内存了。失败返回-1
用例：void* lp = shmat(shmid，NULL，0)；0代表可读可写，返回的lp是一个地址，
4.将共享内存段和当前进程分离：
	int shmdt(const void* shmaddr);
	shmaddr:由shmat返回的指针
注意注意！！：将共享内存段与当前进程脱离不等于删除共享内存段
5.操作共享内存
	int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	shmid:由shmget返回的共享内存句柄
	cmd:将要采取的动作（有三个可取值），
获取	IPC_STAT：读取当前共享内存的属性信息(比如共享内存的大小，创建时间等等)，放在buf里
设置	IPC_SET：设置共享内存的属性信息，创建一个结构体shmid_ds buf，用他的内容去设置
删除	IPC_RMID：删除共享内存，buf可为NULL
	buf:字符数组
	用例：删除：shmctl(shmid，IPC_RMID，NULL)；
获取共享内存信息：shmctl(shmid，IPC_STAT，&buf)；printf("shm_size=%d\n"，buf.segsz);输出结构体buf中segsz(共享内存大小)

到此删除共享内存有了两种方法：1.ipcrm -m+[操作句柄] 2.shmctl(操作句柄, IPC_RMID, NULL);
需要注意的是：有错误！
1.删除之后共享内存就被释放了，所以其它附加的进程再进行读写操作会报错，共享内存名(key)被设置成0x00000000，状态被设为dest
2.删除之后，若还有其它进程附加在这段共享内存上，则用ipcs -m任然可以查看到这个共享内存的存在
两个进程附加到共享区，一个进程删除共享区并分离，查看共享区任然存在，但是状态是destroy，另一个进程也分离或退出则该共享区被销毁，找不见

删除共享内存总结：
1.将该共享内存的状态标记为dest，将标识符设置为0x00000000，任何进程都不能再进行附加，同时会释放共享内存
2.风险：如果还有进程附加在该被删除的共享内存上，有可能访问到非法的内存，导致程序越界并崩溃。输入ipcs -m仍然可以看到这块共享内存
3.当附加程序全部分离或者退出，操作系统内核也会随之将描述共享内存的结构体释放掉，也就是说ipcs -m看不到我们所创建的了
查看共享区：ipcs -m
key(标识符) shmid(操作句柄) 拥有者 权限 空间大小 附加进程数量 状态
结论：
1.生命周期：跟随操作系统内核
2.进程在读取共享内存之后，共享内存内容不变，类似拷贝
3.一个进程删除共享内存后，共享内存被释放，其它未附加的进程找不见这段内存，但ipcs -m任可以看到这段共享内存，等所有附加进程都分离时，该共享内存就找不见了

消息队列：底层实现就是内核当中创建的链表
1.保存着不同类型，不同类型优先级不同
2.同一类型先进先出 
特性：
1.生命周期是跟随内核的
2.可以进行双工通信，因为数据有明显的数据边界了，克服了管道当中无格式的字节流的缺点
信号量：
	system V版本 sem
	posix sem(多线程)
	信号量的底层是一个计数器，信号量是用来进程控制的
临界资源：多个进程都能访问的资源，被称为临界资源
		  多线程中，多个线程都能访问到的资源，被称为临界资源
临界区：访问临界资源的那一块代码

面试题：列举你所知的进程间通信（管道，共享内存，消息队列，信号，网络，unix域套接字，信号量）
*/
/*
	SHELL是命令行解释器的统称，bash是一个可执行程序(命令行解释程序)也可以说是一个进程，而输入的命令也是可执行程序，
	在bash中输入一个命令，bash先创建一个子进程，然后进程程序替换成该命令的代码并运行，bash就自动切换到后台了。
	问题：不是都已经程序替换了嘛，为什么bash还会回收他的资源，那程序替换之后会不会有僵尸进程？
	把一个进程放到后台去运行，在启动命令之后加&
	fg：就把刚才放到后台的进程，再放到前台运行

进程信号，信号概念，产生，注册，注销，捕捉处理，自定义信号处理函数
概念：
	查看信号列表：kill -l
	1.信号是一个软件中断，打断当前正在运行的进程，让该进程去处理信号的事件
	2.信号的种类：
		1-31：非可靠信号，当前信号可能会丢失(例：多个2号信号进入，可能只处理一个2号信号) 
		34-64可靠信号，该信号不会丢失
	3.信号产生：
	硬件产生：ctrl + c (退出一个进程)：SIGINT(2号信号)，这是发送给前台进程的。
			  ctrl + Z：SIGTSTP（20号信号）
			  ctrl + |：SIGQUIT（3号信号），会产生核心转储文件coredump
			  核心转储：core dumped，存储程序崩溃之后错误的原因
		执行并查看：gdb+可执行程序+coredump文件
		产生coredump文件条件：
			1.ulimit -a中没有限制coredump文件大小，且磁盘空间大小够用
			2.崩溃条件：解引用空指针，内存访问越界，且越界的位置别的进程正在占用，崩溃就会收到（11号信号SIGSEGV），并产生coredump
			3.崩溃条件：多次free释放空间（6号信号SIGABRT），free（NULL）不会崩溃
	软件产生信号：
		int kill(pid_t pid,int signo)或在bash中输入kill -信号种类+pid
		例：kill(getpid(),2);给当前进程发送一个2号信号，2号信号中断
			pid：进程标识符
			signo：信号种类
		abort(pid_t pid)函数：当进程调用到这个函数时就会收到6号信号SIGABRT(double free)，底层封装了kill(getpid(),6);
		man手册中2是系统调用函数，3是库函数
		echo &？：上次如何退出进程的
		alarm定时器函数，alarm(int sec) SIGALRM 时间到了结束进程
		11号信号：SIGSEGV 段错误信号--->可能访问了空指针或访问越界
	4.信号注册的过程
	1个位图(sig[]的比特位)+1个sigqueue队列
	内核源码：find /usr -name sched.h，找到一个include\linux里面有task_struct结构体，ctrl+]可以跳转，task_struct大概在1300行
	创建一个进程则task_struct结构体下有一个struct sigpending结构体叫pending，里有一个双向链表list和sigset_t(位图)结构体内部，保存着数组sig[]，数组中的都是无符号长整型long，每个比特位都表示不同的信号。
	位图sig数组不是按照long类型来使用的，而是按照bit位来使用，每一个信号在该位图中都存在一个比特位对应，为1则表示收到信号
	位图sig数组里有两个元素，代表两个无符号长整型一共128位，从0位开始，但没有0号信号
	非可靠信号：1-31
		更改数组sig[]位图中对应的比特位为1，在sigqueue队列中增加sigqueue节点，多次收到同类型信号时，检查发现sigset_t位图中该比特位已经置1了，则丢弃第二次的信号，不增加sigqueue队列节点。
	可靠信号：34-64，
		更改sig位图当中对应的比特位为1，并且在sigqueue队列中增加对应信号的节点，当多次收到同样信号时，则再次在sigqueue队列中增加对应信号的节点
	5.信号注销的过程
	非可靠信号：
		操作系统先将sigqueue队列当中信号对应的节点拿出来，再将sig位图中对应比特位置0，操作系统是拿着节点去处理信号的。
		注意：这里是先删除再拿着信号节点去处理信号
	可靠信号：
		先将sigqueue队列当中信号对应的节点拿出来，再检查sigqueue队列是否还有同类型节点，有则不改变sig位图对应比特位的1，等待下次处理，无则直接将sig位图对应比特位置0。再拿着sigqueue节点处理信号
	6.信号捕捉处理
	信号有哪些处理方式？
	默认处理方式：SIG_DEL --->执行一个动作(函数)
	忽略处理：SIG_IGN --->不干任何事
		为什么僵尸进程？-->子进程退出时，会给父进程发送一个SIGCHLD（17号）信号，而操作系统对SIGCHLD的信号处理方式为忽略
		僵尸进程无法通过发送kill信号结束！！！
		面试技巧：僵尸进程 扯到--> 信号(忽略处理)--->继续扯到 解决(进程等待、信号处理、信号各种点等等)
	自定义处理：自定义信号的处理函数
1）	sighandler_t signal(int signum，sighandler)：内部也调用了sigaction函数
			signum:需要自定义哪一个信号
			handler：函数指针类型的参数，函数名，该函数可以改变信号处理的方式
	程序运行完这条语句之后，就会记录下，当收到signum号信号时，调用该函数(称为回调函数)
	返回值：sighandler_t：函数指针

	详细说自定义信号处理流程：
	task_struct下有一个结构体指针struct sighand_struct，该结构体里有结构体数组action[]，数组中每个都是struct k_sigaction结构体（这些结构体对应了每一个信号的处理逻辑），里又有结构体struct action sa，里有_sighandler _t类型的元素，这个sighandler_t是一个函数指针类型。_sighandler _t就是函数指针void(*sighandler_t)(int)类型，sa_handler原始指向--->默认处理方式SIG_DEL，修改之后就指向我们自定义的函数了
	操作系统默认对信号的处理：
	当sigset_t位图中收到某个信号则相应比特位被置为1，操作系统处理该信号时，就会从PCB(task_struct)中寻找sighand_struct这个结构体，从而找到sa_handler函数指针，操作系统会通过函数指针保存的地址来调用函数
	自定义信号处理函数
	signal修改的就是函数指针sa_handler保存的函数地址，这样操作系统在处理信号时，通过sa_handler地址就能调用我们自定义的函数
	struct sigaction 结构体
	{
		void  (*sa_handler)(int):函数指针，保存了内核对信号的处理方式
		void  (*as_sigaction)(int,siginfo_t*,void*);要搭配sa_flags使用，为SA_SIGINFO是调用该函数地址
		sigset_t sa_mask 保存的是当进程在处理信号时，收到的信号，也就是位图
		int   sa_flags:要怎么修改 ，一般为0
			值为SA_SIGINFO时，操作系统在处理信号时，调用的就是sa_sigaction函数指针中保存的值
			0在处理信号的时候，调用sa_handler函数指针中保存的函数
		void  (*sa_restorer)(void)预留信息
	}
	问题：signal函数进行信号修改，怎么都会有效呢？？
	谁保存了，这几个信号产生时调用handler所指函数，的信息呢？
	那是谁调用的回调函数呢？
	目前这段代码只有一个主线程，主线程执行main函数中的，当收到2号信号时，执行回调函数的是内核执行流。
	signal是内核在执行的，当收到信号时，打断当前的执行流，去执行内核中的执行流

2） sigaction函数更改信号为自定义处理方式，sigaction结构体里都是以sa_开头的，因此这个结构体叫sa，全称struct sigaction sa
	int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact)
	signum：待更改信号的值
	act：将信号处理函数改为act，act.sa_mask的初始化状态必须是全零，意思是没有收到信号
	oldact：信号之前的处理方式
	位图操作函数：
	int sigemptyset(sigset_t *set);将位图的所有比特位清0
	int sigfillset(sigset_t *set);将位图的所有比特位置1
	int sigaddset(sigset_t *set,int signo);
	int sigdelset(sigset_t *set,int signo);
	int sigismember(const sigset_t *set,int signo);
	问题：在另一个SSH中输入kill -3+pid程序直接运行了起来，getchar（）接收了一个什么？
	getchar()目的是让程序阻塞，接收什么并不用关心
	总结：
	1.signal是改函数指针sa_handler,内部也调用了sigaction函数
	2.sigaction函数是改sigaction结构体

	7.信号的捕捉流程：
	画一个图
	用户态：执行自己定义的代码
		sys_return函数：返回用户空间
	内核态：执行操作系统接口或库函数封装的系统调用函数
		1.要从内核空间到用户空间必定调用do_signal函数：检查(pending中的位图)有没有收到信号，有：则去处理信号，无，则调用sys_return函数返回用户空间。处理完成之后继续调用do_signal函数检查
		2.若有收到信号，1)该信号处理方式是系统调用(例：默认处理方式)，则继续在内核中处理 2)该信号处理方式是我们自定义的，则跳转到用户空间处理信号，处理完成之后调用sig_return函数返回内核，继续调用do_signal检查。
	也就是整个流程分两种：1.执行完系统调用函数之后，调用do_signal函数检查是否收到信号，无则返回
						  2.有则看是哪种处理方式，1.自定义 2.系统调用
	什么时候进入到内核空间：调用系统调用函数的时候，或者调用库函数的时候（库函数底层大多数都是系统调用函数）
	free(NULL)不会崩溃，因为NULL在底层是0
	
	8.信号阻塞 block （9号SIGKILL信号和19号SIGSTOP不能阻塞）
	信号未决(sigpending)：信号从产生到递达之间的状态，递达是实际执行信号处理的动作
	问题：未决信号集就是我们所说的sigqueue队列吗？？？
	是的，未决信号集就是sigqueue队列，但为什么不是先进先出？
	sigset_t位图，操作系统中有两个位图1.pending中：sig[] 2.block中：sig[]，位图也可以自己创建也就是struct k_action sa结构体中的sa_mask位图
	被阻塞的信号产生时，将保持在未决状态，直到进程解除对此信号的阻塞，才能执行递达动作
	阻塞和忽略是不同的概念，阻塞：是在递达之前的动作，阻止递达，忽略：是递达之后可选择的动作
	在task_struct结构体里，有三个信号标志位block阻塞，pending未决，handler函数指针
	画个图！
	注意：
		1.信号的阻塞并不会干扰信号的注册，该注册还是注册，只不过当前进程不能立即处理了
		2.当block位图中对应信号的bit位为1，则表示进程阻塞该信号，当进程进入到内核空间，准备返回用户空间时，调用do_signal函数，这时候不会立即去处理该信号了，之后会处理
		3.收到多个非可靠信号，只会添加一次sigqueue节点，所以处理信号时只处理了一次
		  收到多个可靠信号，会添加多次sigqueue节点，所以处理了多次
	int sigprocmask(int how,const sigset_t *set,sigset_t *oldset);
	读取或更改进程的信号屏蔽字（阻塞信号集）
	how：告诉sigprocmask函数应该做什么操作，注意：下面操作的都是位图！
	SIG_BLOCK：设置某个信号为阻塞
		block(new)=block(old)|set -->按位与
	SIG_UNBLOCK：解除对某个信号的阻塞
		block(new)=block(old)&(~set) -->先取反在按位或
	SIG_SETMASK：替换阻塞位图
		block(new)=set
	set：用来设置阻塞位图
	oldset：原来的阻塞位图

竞态条件：多个执行流访问同一个资源的情况下，会对程序产生二义性的结果，称为竞态条件
	可重入：多个执行流访问同一资源，但不对程序结果产生影响
	不可重入：多个执行流访问同一资源，并且产生了二义性
	在这里每接收一次ctrl+c，内核执行流都会执行一次自定义函数让g_val--，造成了结果的二义性
SIGCHLD：
	子进程退出就会给父进程发送SIGCHLD信号，配合signal处理机制处理
	自定义处理SIGCHLD信号的函数，在函数中用wait处理子进程，这样做可以在收到子进程退出信号时进行处理(内核执行流去调用自定义函数处理)，并且父进程不会因为wait一直等待处理完子进程，才执行
	注意：不能让17号信号SIGCHLD之外的信号定义为调用该函数，若其它信号的sa_handler也指向这个自定义函数，收到该信号时就会阻塞内核执行流(没有子进程退出)
volatile:使变量保持内存可见性，即从内存中读取值，摒弃编译器优化
	-O2优化后一般为了提高执行效率，CPU是在寄存器中取值，但其实该值在内存中内已经改变了，寄存器里的没有改变
	使用volatile可以一直都取出的是内存中的值 
*/
/*
多线程：
为什么要有多线程？
	创建一个线程相当于创建了一个执行流，程序中不仅仅只有一个main函数的执行流，而是有很多个执行流在同一时刻拿着不同的CPU进行运算，称为并行。同一时间有多个执行流同时执行代码，程序的运行效率可以大大提高
线程是什么？
	线程就是创建出来的执行流，在内核中创建了一块PCB（task_struct结构体）
	1.创建子进程(fork,vfork)
		fork:子进程拷贝父进程的PCB创建出来一块PCB，PCB被内核用双向链表管理起来，此时父子进程用了同一块虚拟地址空间，当父子进程发生改变时给子进程新开辟一块内存空间
		vfork:子进程拷贝父进程的PCB，两个PCB一模一样，指向同一块虚拟内存空间
		调用栈混乱问题：vfork提前退出并释放了资源
	2.创建线程
		pthreat_creat:在内核中创建一个PCB(task_struct)结构体，这个线程(执行流)的PCB和当前进程共用同一块虚拟地址空间，在虚拟地址空间的共享区，线程会有自己独有的东西
		内核中其实是没有线程概念(C库中的概念)，叫轻量级进程，线程的接口都是C库提供的，底层调用clone接口
		在bash中输入ps aux 看到的pid其实是tgid(thread group id)线程组，而pid是线程的id，每个线程的pid都是不一样的。1）当一个进程中只有一个执行流（main函数执行流）时，我们称这个tgid也是pid。
		相当于进程是一个大家，而线程是家里的成员(每个成员id不同)，当家里只有一个人，也称这个人就是家。
		线程是操作系统调度的最小单位，进程是操作系统分配资源的最小单位
		现在用ps aux看到的pid，我们只能称其为进程id，它在内核中其实是tgid(线程组id)
线程的优点：
	1.创建一个线程比创建进程的开销小(不用创建虚拟地址空间，页表，段表等等)
	2.不同线程可以并行，提高了进程运行效率
线程的缺点：
	1.健壮性/鲁棒性低
	2.多线程的程序即有多个执行流，当其中一个执行流异常，会导致整个执行流异常(抢鸡腿)
	3.缺乏访问控制，(造成程序结果二义性)
	4.编程难度高，多个执行流可以并发的执行，也就可能会访问到同一临界资源，我们需要对访问临界资源的顺序进行控制，防止程序产生二义性
		万恶之源：内核中创建一个线程也就相当于在内核中创建了一块PCB，内核进行调度PCB时，由于并行式运行，所以可能导致程序结果产生二义性，也就是抢占式执行
	5.性能损失，一个进程拥有多个线程时，操作系统会不停的进行切换调度，而每次切换都要保存当前代码执行信息等，回调时占用CPU执行上下文信息，程序计数器

线程的独有和共享：画一个图
独有：(共享区内一块独有的)
	1.tid:线程id
	2.栈：因此线程不会造成vfork父子进程的调用栈混乱，因为每个线程共享区都有独有的栈
	3.信号屏蔽字:个人猜测-->信号阻塞的位图每个线程都不同
	4.调度优先级：哪一个线程先运行
	5.errno：收到的错误信息
	6.一组寄存器：进程切换时的上下文信息，程序计数器等
共享：(虚拟地址空间其它的)
	1.共享当前进程的虚拟地址空间
	2.文件描述符表：(struct file_struct结构体中保存的)
	3.当前进程的工作路径，例运行程序时./test
	4.用户ID和用户组ID

线程和进程的区别：
	多进程：1.每个进程拥有自己的虚拟地址空间，且一个进程异常不会影响其他进程，
			2.多进程也能提高程序运行效率(本质也是增加执行流)，但需要用到进程间通信(访问共享内存，命名管道)
	多线程：1.每个线程都共用了一块虚拟地址空间，且只要有一个线程异常崩溃则整个进程崩溃
			2.多线程可提高程序运行效率，程序健壮性低，但代码编写复杂因为要避免二义性(并发执行带来的后果)

线程控制：创建，终止，等待，分离
	前提：线程控制当中的接口都是库函数，所以线程控制的接口需要链接线程库，线程库的名称叫pthread，链接的时候增加lpthread
	创建：
		int pthread_creat(pthread_t* thread,const pthread_attr,void* (*thread_start)(void*),void* arg);
			thread:线程标识符pthread_t，是一个出参，和线程id并不是一回事，pthread_t是线程在共享区独有空间的首地址，通过这个标识符可以对当前线程进行操作，调用pthread_creat作为出参返返回给调用者
			attr:线程属性,pthread_attr_t是一个结构体，这个结构体完成对新创建线程属性的设置。(NULL是默认属性，一般都是用NULL)
				属性有：线程栈的大小、线程栈的起始位置、线程的分离属性、线程的优先级调度属性
			thread_start:线程入口函数，接收一个函数地址(可以自定义)，这个函数的返回值是void*，参数也是void*
			arg：给线程入口函数传递的参数的值,类型是void* 
				注意：不能传递临时变量，arg不能接收临时变量，可以传递在堆上开辟的内存
			返回值：==0创建成功，<0创建失败
	注意：
	1.agr不能接收临时变量否则会造成二义性，(传i时输出混乱的)
	2.在传一个堆上开辟的结构体指针时，发现输出并不是先执行0号线程，而是随机执行，这就是抢占式执行，但要在线程函数结束的位置释放掉堆上申请的空间
问题：堆上的空间是共享的还是独有的?如果是共享的，那一个线程释放，别的线程释放不会崩溃？
在这段代码里面，他在for循环开辟了多段堆空间，所以传进去的每个堆地址都不同，因此每次释放的地址都不一样

线程终止的方式：
	1.线程入口函数的return返回
	2.pthread_exit(void* retval)：谁调用谁退出
		retval：当前线程退出信息，可以是NULL
		当主线程(也就是main函数的线程)调用pthread_exit退出的时候，进程并不会退出，因此主线程变成了"僵尸线程"，而工作线程的状态还是R或者S
	3.pthread_cancel(pthread_t thread)：结束指定的线程，结束传入的线程标识的那个线程，也就是线程标识符为thread的线程，这个标识符可以是pthread_create()函数的出参，也可以用pthread_t pthread_self()获取
		thread:线程的标识符
		pthread_t pthread_self()：获取当前线程的标识符
	pthread_t线程标识符：一定得记住！！！

	注意：线程在默认创建的时候，默认属性当中认为线程是joinable的
		joinable:当线程在退出的时候，需要其他线程来回收该线程的资源，如果没有线程回收，则共享区中对于退出线程的空间还是保留的，退出资源没有完全释放造成内存泄露

线程等待：为了释放线程退出资源，防止内存泄露
	pthread_join(pthread_t,void**) 阻塞接口
		pthread_t：线程标识符
		void**：获取线程退出的什么东西
			return:入口函数return返回的内容
			pthread_exit:获取pthread_exit(void*)的参数
			pthread_cancel：获取到一个常数，PTHERAD_CANCELED

线程分离：改变线程的joinable属性，变成detach，从而该线程退出时不需要其他线程来回收该线程的资源
	
	
*/
//1.传临时变量的代码
//2.传结构体指针的代码
//3.把循环创建放在外面，在入口函数释放看代码崩溃不？
//会的！！直接显示double free
//4.20秒后两个线程只剩了一个
//5.僵尸主线程
//6.在函数里面结束线程
//7.用出参结束创建的线程
//8.
int main()
{
	return 0;
}