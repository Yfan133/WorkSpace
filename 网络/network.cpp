/*
网络基础1：
	网络的任务：信息共享，信息交换
	网络协议：
		协议：通信双方对于通信进行约定，使用一种共同语言来进行有效沟通；
		网络协议：在网络当中通信双方对数据交换和数据传输做出决定
		计算机当中有很多网络协议，将这些网络协议联系在一起，称之为协议簇(TCP/IP)
		参考模型或者体系结构：在协议簇当中，定义各个协议之间的相互关系和协议需要完成的任务
		
	协议分层：
		协议分层就是一种封装，对不同的协议或者服务进行封装
		OSI参考模型(参考意义，实际工业上是没有使用的，因为分层太细节)
			口诀：物数网传会表应
			物理层，数据链路层，网络层，传输层，会话层，表示层，应用层
			前面6层已经被实现了，我们只关心应用层
		TCP/IP五层模型
			物理层，数据链路层，网络层，传输层，应用层(合并会话层，表示层)		

			1.应用层：负责应用层程序之间的数据传输，程序员就是工作在这一层面的，即代码在应用层
				典型的协议：HTTP协议，FTP协议，DNS协议，SMTP协议
			2.传输层：负责端与端之间的数据传输，理解端与端是知道是端口和端口之间传输(端口)
				典型协议：TCP协议和UDP协议
			3.网络层：负责路由选择和地址管理
				典型协议：IP协议，ARP协议，ICMP协议
				典型设备：路由器
			4.数据链路层：负责相邻设备之间的数据帧传输，差错控制，流量管理，链路管理
				典型协议：以太网协议(Ethernet)
				典型设备：交换机
			5.物理层：负责光电信号的传输
				典型协议：以太网协议
				典型设备：集线器

		计算机网络当中两台计算机如何进行通信？IP+Port
			IP地址：
				作用：在网络当中唯一标识一台主机
				本质：unit32_t值，无符号4个字节，范围0~42亿
					192.168.113.192 --》点分十进制表示方法，以点分割，每个字节最大能表示的数是255
					192.168.256.113 --》非法IP地址
				源IP地址：当前这个数据从哪一个机器上面来的
				目的IP地址：当前这个数据要去往哪一个机器
			
			Port：端口
				作用：在一台主机中标识一个进程
				本质：unit16_t，范围0~65536，无符号16位整数，一个端口只能被一个进程所占用，一个进程可以占用多个端口
				使用：网络当中的程序，通信时需要使用端口来进行
				知名端口：(0~1023)，被知名协议所占用
				http协议：80
				https协议：443
				ssh协议：22
				mysql：3306
				oracle：1521
				我们在开发应用程序的时候，杜绝占用知名端口，避免使用熟知软件使用的端口，因为一个端口只能被一个进程所占用

		网络通信中，每一条数据都是需要具备5个信息，我们称之为5元组 = 源IP + 源端口 + 目的ip + 目的端口 + protocol
			源IP地址：src_ip，当前这个数据从哪一个机器上面来的
			目的IP地址：dest_ip，当前这个数据要去往哪一个机器
			源端口：src_port，从源主机上面哪一个进程来的，当回复应答的时候，就知道回复到哪一个进程了
			目的端口：dest_port，去往哪一个主机上面的进程
			协议：protocol，标识使用什么协议

		画个图：网络传输：从数据的封装到分用
	
		ip协议分为两个版本：ipv4和ipv6(目前正在使用)
			1.ipv4和ipv6指的是不同版本的ip协议
			2.ipv6并不向下兼容ipv4，因为报头格式不同
			3.ipv4版本的IP地址不够用，无符号32位(0~2^32)大概42亿--》4字节  而当前有60亿人口
			  ipv6版本，无符号128位(0~2^128)--》16字节
	
	画个图：客户端与服务端
	客户端和服务端的概念是相对的
		客户端：主动发起请求的一方，称为客户端
		服务端：被动的在同一个位置上(位置)接收请求的一方，称为服务端
	注意：对外提供服务的端口一般不要变化，否则要通知所有用户来改变端口

	面试题：为什么不使用PID作为请求与主机当中查找进程的标准呢？
	原因：因为每次打开关闭一个进程的PID都不相同
	如何解决Ipv4版本资源枯竭：
		1.动态主机分配协议：DHCP，谁上网就给谁分配IP
		2.NAT地址转换协议，根本上解决枯竭问题

网络字节序：
	1.前提：
		字节序;CPU对内存当中的数据进行存取的顺序
			大端字节序：低地址存高位
			小端字节序：低地址存低位(小小小)
		如何区分大小端机器？
			union
			{
				int a;		//赋值一个01
				char b;		//如果是01则是小端，不是则大端
			}
		x86_64机器基本都是小端

	2.网络字节序：大端字节序
		小端机器和大端机器进行网络通信时，如果不转换字节序，则会使小端机器很小的数，经过网络传输，被大端机器读出来变成很大的数字
		我们在网络传输的过程当中都需要遵循网络字节序
		主机字节序：机器实际的字节序
	
	问题：为什么需要转换网络字节序？
	原因：1.绑定了IP和port等信息传送到目的端时，中间网络链路的解析是按大端字节序的，如果不是大端，则无法发送到目的地。
	      2.数据是不需要转换成网络字节序的，因为大多计算机都是小端。
	3.字节序转换：
		大端字节序的机器转换网络字节序---》无需做任何事
		小端字节序的机器转换网络字节序---》需要将小端转化为大端
				主机转换网络  host to net  --> hton
				网络转换主机  net  to host --> ntoh
				16位：加s ，32位：加l
			IP调用
			uint32_t htonl(unit32_t hostlong)：将32位主机字节序转化为网络字节序，引申含义：大端调用该接口什么都不会发生
			unit32_t ntohl(unit32_t netlong)；将32位的网络字节序转换为主机字节序

			端口调用
			unit16_t htons(unit16_t hostshort)；将16位的主机字节序转换为网络字节序
			unit16_t ntohs(unit16_t netshort)；将16位的网络字节序转换为主机字节序

	在ifconfig中看到的，172.16.99.129就是IP，它是以点分十进制表示的，比如一个IP是40000001转换成二进制，然后8位一分，总共四字节
	
	 TCP协议与UDP协议的区别：
		TCP
			面向连接：TCP通信双方在发送数据之前，需要先建立连接，才可以发送数据
			可靠传输：保证TCP数据包一定到达对端，原因：必须建立连接才能通信
			面向字节流：对于TCP数据可以随意的存取(不会刷新缓冲区)，每一条数据之间是没有间隔的，这也就是TCP粘包问题的万恶之源！
		UDP
			无连接：UDP通信双方在发送数据的之前，不需要建立连接，知道对端的IP和端口(port)就可以直接发送数据了
			不可靠：如果在网络传输当中，数据包丢掉了，那就丢掉了，不保证一定到达对端，原因：不用建立连接，对端可能没有接受数据
			面向数据报：UDP在发送数据的时候，是整条发送整条接收的，接受之后会刷新缓冲区

UDP通信流程&UDP编程接口：
	1.UDP通信流程
		(画个图UDP，画图更加清晰明了)
		客户端：client
			1.创建一个套接字
			2.绑定地址信息，不推荐自己绑定，系统分配可以打开多个端口
				一般让操作系统默认分配一个空闲的端口
				注意：一个端口只能被一个进程所绑定
			3.发送数据 ----》接收数据(服务端)
			4.接收数据《---- 发送数据(服务端)
			5.关闭套接字     关闭套接字(服务端)
		服务端：server
			1.创建一个套接字：将创建出来的套接字的进程和网卡建立联系，本质上在内核中是一个结构体struct socket{...};
			2.绑定地址信息：port+ip，将端口和进程联系起来，port表明服务端进程在哪一个端口上侦听数据；ip表明服务端进程在哪一个网卡上接收数据
			3.发送数据 ----》接收数据(客户端)
			4.接收数据《---- 发送数据(客户端)
			5.关闭套接字     关闭套接字(客户端)
	2.UDP编程套接字
		1.创建套接字
			int socket(int domain，int type，int protocor)；
				用例：sockfd = socket(AF_INET, SOCK_DGRAM, IPPORT_UDP);	//采用ipv4版本的UDP类型套接字
						或者   socket(AF_INET, SOCK_DGRAM, 0);
				domain：地址域，指定"网络层"(IP所在层)在使用什么协议						
					网络层：AF_INET：IPV4版本的ip协议
							AF_INET6：IPV6版本的ip协议
				type：套接字类型
					传输层：tcp/udp
					SOCK_STREAM：面向字节流套接字--》默认协议是TCP协议,不支持UDP协议
					SOCK_DGRAM：用户数据报套接字--》默认协议是UDP协议，不支持TCP协议
				protocol：指定套接字所使用的协议
					0：采用套接字的默认协议
					IPPROTO_TCP--》6     TCP协议
					IPPROTO_UDP--》17	 UDP协议
				返回值：返回套接字操作句柄，其实就是一个文件描述符，我们一般称之为套接字描述符
				画个图：(用户空间socket()，内核空间在files结构体指针中，fd_array[]新增了一个元素，相当于打开了一个文件，然后这个文件指向接收和发送缓冲区)
				ll  proc/PID/fd
		2.绑定地址信息：
			int bind(int sockfd，const struct sockaddr* addr，socklen_t addrlen)；
				用例：bind(sockfd，(struct sockaddr*)&addr，sizeof(addr))；
				sockfd：套接字操作句柄
				addr：地址信息 ip+port
				addrlen：地址信息的长度

				问题：为什么需要地址域？
				原因：通过地址域来确定结构体中后序空间应该如何读取。
				前提：struct sockaddr_in addr;		//创建一个结构体
						addr.sa_family = AF_INET;		//设置协议，ipv4
						addr.sin_port = htons(port);	//转换为网络字节序，设置端口地址
						addr.sin_addr.s_addr = inet_addr(ip.c_str());	//把字符类型ip转换成指针类型，再进一步转换成uint32,并设置ip地址为网络字节序
				协议的地址信息超过16字节，也没有问题，第三个参数就是传入结构体的长度
				struct sockaddr_in
				{
					_SOCKADDR_COMMON(sin_);		//地址域信息，2字节	    //这就是上面的sa_family
					
					in_port_t sin_port;			//2字节的无符号整数		//下面的共14字节就是上面char类型的数组,char[14]
					struct in_addr sin_addr;	//4字节的无符号整数		

												//8字节的保留空间
					unsigned char sin_zero[sizeof(struct sockaddr)-_SOCKADDR_COMMON_SIZE-sizeof(in_port_t)-sizeof(struct in_addr)];
				}
			对于上面的解释：
				bind接口在设计的时候为了通用各种协议，定义了一个结构体struct sockaddr；而在进行具体协议地址信息绑定的时候，填充不同的结构体，之后将结构体的对象的地址，强转传参给bind函数
				socklen：地址信息的长度，防止有的协议的地址信息长度大于16个字节，所以传递地址信息长度，告诉bind函数，应该如何解析地址信息

	3.发送数据
		ssize_t sendto(int sockfd，const void* buf，size_t len，int flags，const struct sockaddr* dest_addr，socklen_t addrlen)
			sockfd：套接字的操作句柄
			buf：要发送的数据，可以发送结构体，也可以发送字符串
			len：数据长度
			flags:
				0:阻塞发送
			dest_addr：目标主机的地址信息，要将数据发送到哪里去
				struct sockaddr_in:包含目标主机的IP地址和端口号(port)
			addr_len:地址信息长度
			返回值：返回实际发送的字节数量
		1.(UDP没有发送缓冲区)这句话是错的，只不过UDP是整条数据发送，所以在发送缓冲区当中打上UDP协议报头之后就提交给网络层了

	4.接收数据
		ssize_t recvfrom(int sockfd,void* buf,size_t len,int flag,struct sockaddr* src_addr,socklen_t* addrlen);
			sockfd:套接字操作句柄
			buf：将数据接收到哪里？
			len：最大接收的字节数
			flag：
				0：阻塞接收
			src_addr：数据源主机的IP地址和端口(source_addr ：源地址)
			addrlen：地址信息的长度(结构体的大小)

	5.关闭套接字：
		close(int sockfd);

客户端 和 服务端 代码：

问题：
socket文件描述符闪烁			原因：使用了内核缓冲区(管道)
不推荐lient绑定信息的			原因：一个端口只能被一个进程占用，如果运行多个client，绑定时报错并返回。一般都是绑定本机网卡信息，不管哪个server端发送信息都可以接收
为什么要地址域？		   		原因：内核根据地址域来对结构体中的空间进行解析
perr_addr_len在接收之前初始化	原因：不然内核不知道应该怎么去解析长度，于是默认给 sin_port 赋值65536

总结：一定记住sockaddr是结构体类型，他里面保存了IP地址和port端口信息，可以唯一识别一台主机中的一个进程

TCP编程流程&TCP接口
	TCP编程流程：
	（画个图清晰明了）
	客户端：
		1.创建套接字
		2.绑定地址信息
		3.发起连接    （第一次：发起握手）
		4.发送数据
		5.接收数据
		6.关闭套接字
	服务端：
		1.创建套接字(监听套接字)
		2.绑定地址信息
		3.监听		  （第二次握手）
			告知操作系统内核当前程序可以接收新连接了 ，三次握手是在监听的时候内核完成的！
	    4.获取连接	  （第三次握手）
			获取已经完成三次握手的连接，获取新创建的socket
			如果已完成连接队列当中没有新连接，则调用阻塞(双方发送数据之前的准备工作)
		5.接收数据
		6.发送数据
		7.关闭套接字
	TCP连接建立之后，双方都可以发送数据，不论先后顺序！

	完整解释TCP双方建立连接过程：(先开客户端，再开服务端看下现象)：无法建立连接，连接失败
		1.服务端创建监听套接字
		2.服务端绑定地址信息，调用监听接口，表示当前可以接收新的连接。
		3.如果有客户端发起连接，则内核进行三次握手，三次握手完成之后，通过监听套接字创建新的socket和客户端建立连接
		4.服务端调用accept接口，获取新创建的socket文件描述符
		5.通过新创建的socket和客户端进行发送和接收数据

	TCP编程接口：
		1.创建套接字：socket()
		2.绑定地址信息：bind()
		3.监听连接： 告诉操作系统内核已经可以接受连接了，然后操作系统去完成三次握手
			int listen(int sockfd，int backlog)；
				sockfd：套接字描述符
				backlog：已完成连接队列的大小，也就是完成三次握手之后的连接会被放进去
					这里最好画个图（未完成连接队列和已完成连接队列）
					1.未完成连接队列：处于三次握手过程当中的tcp连接
					2.已完成连接队列：三次握手完毕(连接建立完毕)同时没有被获取的连接
					backlog指定已经完成连接的队列大小，如果已完成连接队列被打满，处理方式就是丢弃掉新来的连接
		画个图：监听之后创建一个新的socket用于一对一服务
		面试题：backlog值为1时，能保存多少个已完成连接？
			1、backlog指的是某段时间内完全建立连接【即established】，监听队列的最大socket队列长度。
			2、监听队列的最大长度并不是backlog，而是 backlog + 1 。

		4.接收连接 阻塞接口！！(获取新的套接字，并1v1服务)
			int accept(int sockfd，struct sockaddr* addr，socklen_t* addrlen)
				sockfd：监听套接字操作句柄
				addr：客户端地址信息
				addrlen：客户端地址信息长度
			返回值：返回的是 "新连接" 创建出来的socket，通过新创建出来的socket和客户端进行数据的收发，一对一服务！
			注意：因为该接口是从已完成连接队列当中获取新的连接，所以，当已完成连接队列当中没有已经完成的，新的连接的时候，该接口调用就会阻塞，直到获取一个新的已完成连接的到来
		问题：为什么需要新创建出来的 socket 和 客户端进行通信
			如果只有一个socket，则无法区分是哪个客户端发送的数据，也无法在接收一个TCP连接通信起来之后，再接收新的连接
			因此：ser端只负责调配客户端和哪一个socket连接，每accept一次就创建出一个新的socket
		问题：创建新socket是在哪一步创建的？
			监听之后就建立了连接，调用accept接口才创建new_socket并返回，让用户可以通过操作new_socket进而和对端进行通信
		5.连接
			int connect(int sockfd，const struct socketaddr* addr，socket_t addrlen)；
				sockfd：套接字描述符
				addr：服务端地址信息，需要自己在代码中填充好，传递给connect
				addrlen：地址信息长度
		6.关闭套接字
			int close(int sockfd)
		
		命令 netstat -anp | grep PID
		tcp   0    0   172.16.99.129:19999   0.0.0.0:*     LISTEN   108683/./svr
		
	收发数据
		1.发送数据
			ssize_t send(int sockfd,const void* buf,size_t len.int flags);
				sockfd：
					客户端：socket的返回值
					服务端：accept函数的返回值，也就是新创建的套接字
				buf:要发送给对端的数据
				len:数据长度
				flag:
					0：阻塞发送
		2.接收数据
			ssize_t recv(int sockfd,void* buf,size_t len,int flags);
				sockfd:accept函数的返回值，新建的套接字
				buf：接收到的数据放到哪里去
				len：最大接收长度
				flag:
					0：阻塞接收，是把传输层接收缓冲区的数据给拿出来，也就清空了缓冲区len长度的数据
					MSG_PEEK：探测接收,根据len所描述的长度去传输层TPC接收缓冲区里"拷贝"，不会删除接收缓冲区当中的数据
				返回值：
					< 0：接收失败
					> 0：接收的数据字节大小
				   == 0：表示对端已经关闭了连接，对端调用了close

值得注意的点：(看一个现象侦听之后不accept，看proc文件描述符，中有没有，并没有！)
	1.listen：是通知内核当前可连接，如果有客户端发起连接则三次握手，如果没有则阻塞等待。三次握手是内核完成的，三次握手之后连接建立成功
	2.accept：获取新连接，返回新链接的套接字描述符
	3.recv：如果返回0，说明对端已经关闭了连接
	4.TCP和UDP端口是不同的概念，即时端口号一样也不影响
	5.远程无法连接时，可以用telnet + ip 确定端口是否开放
程序运行结果：
	两个现象：
		1.accept在while(1)外，和一个客户端无限聊(纵有万千只中意一人)。此时再打开一个新的客户端，尽管netstat -anp | grep 1999可以看到完成3次握手，但proc/PID/fd中并没有新的文件描述符，因为没有调用accept接收新的连接
		2.accept在while(1)里，和一个客户端聊一次之后，程序卡住，因为去接收新的连接了，原操作句柄丢失，内存泄漏！！(万花丛中过一片不留身)
	原因：
		1.accept函数在调用时，如果没有客户端发起连接，则会阻塞
		2.recv函数在连接上没有数据的时候，也会阻塞

	解决：多进程TCP，画个图多进程和多线程通信(66班lesson30)
		多线程，多执行流，每个执行流分别连接一个客户端
			1.多进程，父进程每接收一个新链接之后，就创建一个子进程，让子进程和客户端之间进行通信。也就是父进程调用accept，子进程调用recv和send。
			2.多线程，注意detouch分离
总结：
	1.TCP针对每个客户端都会创建一个新的套接字，进行1对1服务
	2.UDP是创建了一个套接字服务所有客户端
	3.UDP无法感知对端是否关闭了连接，而TCP对端在关闭连接之后
		1.客户端在send时关闭：服务端收到空，然后发送一条信息，再次收到空，再次发送信息之后程序退出？？？ 4次挥手？？？
		2.客户端在recv时关闭：服务端发送一条信息，收到空，再次发送信息之后程序退出？？？  3次？？
		3.服务端在这两种情况下关闭，现象和客户端是一样的。send处有四次，recv处三次
*/
/*
抓包工具：
1.win
	wireshark，
2.Linux
	tcpdump：任何在网络中传输的包都可以抓取
前提：抓取的数据包是从网卡设备中抓取的。网卡设备：接收和发送二进制数据，因此从网卡中抓取的数据都是二进制的
	ifonfig中ens33就是网卡信息
Linux下抓包：
	抓包命令：tcpdump -i any port [端口] -s 0 -w [文件] 
		tcpdump -i any port 19999 -s 0 -w 57.dat
		必须使用root用户进行抓包，先抓包再连接，抓到之后把文件用命令 sz 57.dat 传到win下
win下抓包：
	cmd：输入 telnet 192.168.0.88 19999 连接上刚刚打开的服务端
		因为windows和Linux的网卡是不同的
	两种过滤：
		ip.addr == 172.16.99.129 && tcp.port == 19999 
*/

/*
网络基础 2
自定制协议：
	1.TCP面向字节流：send并不是直接发送到对端，而是先放到缓冲区，因此每次的数据之间没有间隔造成TCP粘包
		TCP保证可靠并且有序，可靠：数据一定能到达对端  有序：应用层接收到的数据顺序一定和发送一致，即使B达到对端也会等待A接收之后，才接收B
		send 和 recv 都是工作在应用层的，send发送数据会先将数据放到传输层的发送缓冲区，recv也是从传输层的接收缓冲区中接收数据的
		接收缓冲区大概比3M大一些
			1.对于应用层调用send接口，只是负责将数据放到TCP的发送缓冲区当中，至于TCP如何发送到对端和之前应用层的发送规则没有任何关系
			2.好处是对于数据可以灵活的发送和接收，但是也带来了TCP粘包问题，对端无法区分发送信息的顺序
	2.怎么解决TCP粘包？
		自定制协议：工作在应用层，被程序员定义出来的协议，用于解决TCP粘包的问题，工业上使用的是 \r\n (0D 0A)来进行区分
		cat /proc/sys/net/ipv4/tcp_rmem ：查看 TCP 缓冲区大小，最小值，默认值，最大值
		对于应用层程序而言，1+10 这条数据并不能区分是否接收完毕，所以需要在应用层进行缓存，等待再次接收，将下一次接收的数据和刚才缓存的数据拼接起来
	3.具体方式：
		应用层数据报头(结构体或者数据结构) + 应用层数据 + 数据边界
			报头内容：定义应用层数据的长度，种类，属性
			例如下面两条数据：size=3|1+1|0D0A|size=4|12+2|0D0A
		小结：解决TCP粘包问题
			1.定长数据包 + 数据(有效载荷) + 分隔符
			2.定长的数据包当中包括：数据的长度、数据种类、属性等
			3.分隔符起到了定义数据边界的作用
		序列化：将对象转化为字节序列(二进制)的过程
			struct data{int a, int b}; data d; d.a = 10; d.b = 20;
			send(sockfd, d, sizeof(d), 0);
		反序列化：将字节序列转化为对象的过程
			struct data dd; 
			recv(sockfd, &dd, sizeof(dd), 0);
	
http协议：
	(https是加密版本的http协议)
	1.超文本传输协议
	2.URL的组成：http://user:passwd@www.baidu.com:80/dir/index.html?id=1&wd=C%2B%2B#ch1
		用浏览器访问我们写的客户端直接输入：ip + port
		1.http://				协议方案名
		2.user:passwd:			用户名和密码，为了保证安全性将它放在正文中去了，https还对密码进行了加密(加密规则？？)
		3.www.baidu.com			域名，最终会解析成为服务端ip
		4.80					http的端口号，https：443，通常被省略了
		5./dir/index.html		带层次的文件路径，表示的是浏览器要请求服务器的资源路径；
			注解：'/'并不是Linux操作系统的根目录，而是逻辑上的根目录，web服务器定义的根目录
		6.id=1&wd=C%2B%2B		查询字符串，格式为key=value&key=value 形式
			由于value当中可能具有普遍标识的字符，这些字符有可能会导致歧义，所以在查询字符串的时候，需要进行URLEncode(url编码)，服务端再进行url解码
			url编码：将特殊的字符按照"16进制"传输，例如C++ --》C%2B%3B，为了标识这个字符是经过url编码的，所以在编码完成的字符之前加上一个%，来标识后面的字符是进行过uel编码的，即C%2B%2B代表C++
			url解码：将16进制的字符解析成为正常的字符
		7.ch1					片断标识符，标识当前页面被浏览器加载之后，定位到什么位置
			
http 底层使用TCP协议
DNS	 底层使用UDP协议

http协议格式
	请求：
		请求首行  \r\n
		请求头部  key:value\r\nkey:value\r\n
			Content-Length:	正文长度
			Content-Type：	正文的编码格式
				text/plain：纯文本格式		appliation/json：json	数据格式
				text/html：	HTML格式		appliation/msword：word 文档格式
				text/png：	png图片格式
			referer：当前的页面从哪一个页面跳过来的
			Cookie：向服务器提交浏览器本地保存的认证信息，认证信息是之前登陆服务器的时候，服务器返回给浏览器的，浏览器进行缓存，在下一次请求的时候带上Cookie
			Tranfer-Encoding：针对正文而言，可以支持分块传输
			User-Agent：操作系统和浏览器的版本信息
			Location：搭配重定向使用
			Connection：keep-alive  保持长连接
				早期http是一个无状态短链接协议，http也持支长连接
				短链接：浏览器和服务端发送完数据，连接随即断开
				长连接：浏览器和服务端发完数据之后，连接不断开
			画个图：(重定向)浏览器去访问服务端，此时服务端出问题不能提供服务，返还另一个服务端的ip，浏览器用这个ip继续访问另一服务器
		空行	  \r\n
		正文

	请求方法：
	1.GET：从服务器上获取一个资源的方法
		1.Get方法并不是只能向服务器获取资源，其实也是可以在查询字符串当中提交数据到服务器
		2.提交的数据在URL当中，URL的长度针对不同浏览器是有不同限制的
	2.POST：向服务器去提交数据的方法，提交的数据在正文当中
	问题：
		POST方法比GET方法更安全吗？
			不是，POST方法比GET方法更加私密
		安全的做法是：使用https，即ssl加密，将传输的数据进行加密操作
	http协议的版本分类：
		HTTP 0.9、
		HTTP 1.0、
		HTTP 1.1、
		HTTP 2

响应
	响应首行  \r\n
		协议版本 状态码 状态码解释 \r\n		
			状态码分类：
			1XX：接收到请求了，正在处理
			2XX：请求成功处理完毕了；200，OK
			3XX：重定向的状态，表示浏览器需要进行附加操作，才能完成请求	(302：临时重定向，搭配Location一起使用)，烤鸭的例子
			4XX：服务器无法处理这个请求  (404：页面不存在 -》Page Not Found)
			5XX：服务器处理出错(502：Bad Geteway 坏的网关)
	响应头部  key:value\r\nkey:value:\r\n
		Content-Type:   正文类型
			text/html(页面，则不需要正文长度), application/json, text/plain
		Content-Length：正文长度
	空行	 \r\n
	正文

小结：
	1.http协议是应用层的协议，在传输层使用的是tcp协议，在网络层使用的是ip协议
	2.http是无状态的协议(不会记录刚才的请求的状态)，早期使用的tcp是短连接，现在也支持长连接
	3.http协议是没有加密的，加密可以使用https，用ssl tsl 非对称加密
	4.http协议使用的是 80 端口，https使用的是 443 端口

ctemplate：谷歌的渲染http
状态码：
	404：一般返回的是错误页面
	502：服务器内部错误
*/
/*
等下再看一下录屏密码怎么查看的？

UDP协议：(无连接 不可靠 面向数据报)
	无连接：	只要直到对端 ip 和 port 就可发数据
	不可靠：	在网络传输过程中数据包可能丢失，丢失部分之后传送到对端UDP校验和，检查错误会把包丢掉
	面向数据报：应用层在使用UDP协议的时候，程序员从UDP接收缓冲区当中拷贝数据或者将应用层数据拷贝到UDP的发送缓冲区当中都是一整条UDP报文进行拷贝的，不会存在两条数据并存在缓冲区当中

	UDP协议头部：（只有端口，因为UDP在传输层）
		struct udphdr	
		{
			uint16_t uh_sport;	//源端口
			uint16_t uh_dport;	//目的端口
			uint16_t uh_ulen;	//UDP数据报长度
			uint16_t uh_sum;	//校验和，不可靠根源
		}
	数据报长度：类型是uint16_t，最大表示的数值为 2^16 --> 65536 
				所能表示的范围(0~65536字节)包括：UDP协议头部 + UDP有效载荷(数据)
	面试问题
		1.使用UDP传输一个 100K 的数据可以吗？
			画个图：服务端在应用层先打上自定制协议包头，给传输层加上UDP包头，传给对端。对端再层层剥离
			可以，但是要分多次分发，自定制协议：先打上包头发50k，再打上包头发50k，对端接收两个之后剥离再拼接
		2.为什么说UDP不可靠？
			udp校验和：判断UDP数据在传输过程中是否有损坏？如果有损坏，则不会将数据递交给应用层，而是直接丢弃
		校验和原理(自行分析)：其他每个数据都进行(二进制)相加，把和放在校验和中，对端检查：把所有的二进制相加查看是否全为1.

	UDP缓冲区特点：
		1.对于应用层的数据是整条数据接收和发送的
		2.UDP协议在传输层是有发送缓冲区的，当应用层调用sendto之后，将数据递交给UDP协议的发送缓冲区之后，加上UDP报头，就直接递交给网络层
		3.对于接收缓冲区而言，应用层调用 recvfrom 函数从UDP的接收缓冲区当中获取数据
	UDP应用：
		DNS协议 ：域名解析协议，底层使用UDP
		DHCP协议：动态主机分配协议，谁上网给谁分配ip地址

TCP协议：
	面向连接  ：TCP通信双方发送数据之前，必须先完成三次握手建立连接
	可靠传输  ：保证TCP数据报一定能到达对端
	面向字节流：TCP协议下数据可以任意存取(不会刷新缓冲区)，这也是TCP粘包的根源
	1.面向连接  
		问题：谈谈你所理解的三次握手？
		   从下面三个方面回答：
			1.发送数据包的名称						SYN, SYN_ACK, ACK
			2.配合客户端和服务端的状态来进行描述	SYN_SENT, SYN_RECV, ESTABLISHED, ESTABLISHED
			3.包序管理								细讲一下包序 Seq：发送的包，Ack：请求的包
			客户端发起连接 SYN，服务端收到并发送 SYN_ACK，客户端回应ACK      ACK
			SYN：连接请求
			ACK：SYN的回复
			ACK + SYN：回复连接请求，并且也请求连接
		(画个图并解释)
	2.四次挥手
		问题：
			1.为什么会显示FIN_WAIT_2：因为服务端要关闭才会，发送FIN 然后变成 LAST_ACK
				也就是服务器并没有关闭，只有服务器关闭才会向所有发送FIN
			2.为什么会出现绑定重复（address already in use）？
//////////////////////////////////////////////////////////////////////////////////////////////////////////
				MSL：最大报文段生存时间，发送方认为TCP报文
			2MSL = 丢失的ACK 

	完整解释TCP的四次挥手过程：（图文详解）
		若第一次的ACK丢失，在第二个MSL中会再次发送FIN，然后回应ACK。再来2MSL的时间，若此时对端收到，则2MSL过后双方关闭
		超时重传：发送FIN的一端，在一定时间内没有收到ACK回复之后，会超时重传，即重新传FIN。对端收到后发送ACK继续等待2MSL
	
		如果说连接处于TIME_WAIT状态，是否还可以接收数据包？
			可以接收数据包，也就意味着端口并没有被释放
		如果主动断开连接方是 客户端，意味着客户端会有TIME_WAIT状态
		如果主动断开连接方是 服务端，意味着服务端会有TIME_WAIT状态
			如果现在连接处于TIME_WAIT状态，意味着端口还没有被释放
			如果服务端关闭

		地址复用：
			核心思想就是告诉内核，这个地址信息可以被复用
			int setsockopt(int sock, int level, int optname, const void* optval, sockelen_t len)
				sock：将要被设置的套接字
				level：指定套接字的层次
					SOL_SOCKET：通用套接字选项  --》 地址复用
					
				optname：
					SOL_SOCKET：通用套接字选项  --》地址复用


	TCP协议字段：
		16位的源端口：表示数据从哪一个端口来
		16位目的端口：表示
		32位序号：表示TCP源端向TCP目的端发送的数据字节流
		32位确认序号：标识TCP目的端期望TCP源端的下一个请求序号

		序号在TCP连接中是两套序号，客户端维护一套，服务端维护一套
			客户端给服务端发送数据，使用的是客户端序号，服务端确认的时候，期望客户端的下一个序号

		SYN(Seq=0)
		Seq=0:客户端维护的序号为0的包
		ACK(Ack=1) + SYN(Seq=0)
		Ack=1:服务端期望客户端下一个包为序号1的包
		Seq=0：服务端维护的序号为0的包

		包序管理规则：
			1.纯ACK数据包不占用数据包！！！
			2.确认序号 = 接收到的数据的起始序号 + 数据长度
		
	课后分析四次挥手，UDP校验原理


*/
/*
1.响应头部：

类C风格：
	snprintf(buf, sizeof(buf - 1), "")
	最后还要加空行 \r\n
C++方式：
	302状态码解释
	404只是一个状态码，并不妨碍服务端的数据传输
	502也不会妨碍服务端发送数据，在response header中可以看到502

只有加一个/aaa 才能返回 Linux too easy
*/

/*
nginx：
	查看：yum list | grep nginx
	安装：yum install -y nginx
	查看 nginx：ps -aux | grep nginx

	1.nginx的安装
	2.nginx启动/关闭/重启/热加载配置文件
		启动：systemctl start nginx
		重启：systemctl restart nginx，重启之后看到 nginx 的 PID 不同
		关闭：systemctl stop nginx
	3.守护进程：初衷：要求后台服务器不停机工作
		1.父进程：是守护进程，子进程：被创建出来之后去进程替换，完成 http 服务
		2.守护进程要一直关注子进程的状态(子进程是否还在运行)：通过共享内存：子进程一直往共享内存中写，父进程从中读，若某一时刻父进程读到的值没有变化，则说明子进程出问题了，父进程重新去fork子进程然后继续进程替换。
		3.若此时子进程挂掉，则守护进程重新fork子进程，继续进程替换
			画个图(守护进程的工作机制)
	3.进程模型
		master：守护进程
		worker：被守护进程(子进程)
		看一个现象：kill 一个worker进程之后，又出现另一个进程，它的父进程就是master。守护进程重新拉起来了一个进程
		ps -ef | grep nginx 看到 pid 和 ppid
		ps -aux | grep mysql，mysql 中，mysql_safe 是守护进程
		问题：
			1.一个端口只能被一个进程所绑定，那么多个worker进程怎么工作的呢？(用户输入ip)
				守护进程监听之后才创建出子进程，子进程拷贝父进程PCB(里面有文件描述符：侦听套接字)，子进程调用accept之后就和客户端进行通信。
			2.有多个worker进程时，连接池怎么保证负载均衡？(每一个work进程获取的连接大致都相等)
				nginx的连接池

		浏览器 --》nginx --》http 服务器
			  《--	 	《--
		84班 lesson32，nginx的代码

	3.nginx代码
		热加载：nginx -s reload
		启动两个服务端：
			19898  17777
		客户端直接访问 172.16.99.129/aaa
		vi nginx.conf
			在http最后添加： 
			upstream http_svr{
				server 172.16.99.129:19898 添加weight=2;则给19898发送两次请求，再给17777发送一个请求
				server 172.16.99.129:17777
			}
			向上连接哪些 http 服务器，相当于 nginx 会转发
		vi conf.d/default.conf
			注释 location
			然后自己添加 
				location /aaa {
					proxy_pass http://http_svr;
				}
		如果URL后面添加/aaa 则nginx会向上转发。

	4.灰度升级
		当一台服务器要升级停掉之后，nginx就只给正常的服务器转发请求，此时就可以给停掉的服务器升级。等服务器升级完成重新启动，nginx又会给新服务器转发请求。
*/