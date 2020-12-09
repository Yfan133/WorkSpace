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
			4.数据链路层：负责相邻设备之间的数据帧传输
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

///////////////////////////////////////////////////////////////////////////////////
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

			地址信息解析
				struct sockaddr
				{
					sa_family_t sa_family；		//填充地址域，告诉bind函数，网络层使用什么协议,内核通过该变量确定传入的结构体应该如何来读取sa_data
					char sa_data[14]；			//14字节
				}
			具体：
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
		画个图：client(客户) 和 server(服务)
		1.(UDP没有发送缓冲区)这句话是错的，只不过UDP是整条数据发送，所以在发送缓冲区当中打上UDP协议报头之后就提交给网络层了

	4.接收数据
		ssize_t recvfrom(int sockfd,void* buf,size_t len,int flag,struct sockaddr* src_addr,socklen_t* addrlen);
			sockfd:套接字操作句柄
			buf：将数据接收到哪里？
			len：最大接收的字节数
			flag：
				0：阻塞接收
			src_addr：数据源主机的IP地址和端口
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
	  sockaddr_in：ipv4版本
	  sockaddr_in6：ipv6版本
	  这个结构体要初始化三个东西：
		1.版本信息：addr.sin_family = AF_INET;
		2.port端口：要先转换成网络字节序，用htons接口
			addr.sin_port = htons(port);
		3.ip地址：先转换成c字符串c_str，再转换成网络字节序inet_addr
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
								
UDP通信的小demo
	服务端：创建套接字，绑定地址信息，接收数据，发送数据，关闭套接字
	客户端：创建套接字，发送数据，接收数据，关闭套接字
封装接口：
	1.创建套接字
	2.接收&发送数据
	3.绑定地址信息
	4.关闭套接字的接口

画个图：客户端地址信息，服务端地址信息，还有他们之间的通信

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
		1.创建套接字
		2.绑定地址信息
		3.监听		  （第二次握手）
			告知操作系统内核当前程序可以接收新连接了 ，三次握手是在监听的时候内核完成的！
			获取新创建的socket，如果已完成连接队列当中没有新连接，则调用阻塞(双方发送数据之前的准备工作)
	    4.获取连接	  （第三次握手）
			从已完成连接队列当中获取连接
		5.接收数据
		6.发送数据
		7.关闭套接字

	TCP编程接口：
		1.创建套接字：socket()
		2.绑定地址信息：bind()
		3.监听连接：
			int listen(int sockfd，int backlog)；
				sockfd：套接字描述符
				backlog：已完成连接队列的大小，也就是完成三次握手之后的连接会被放进去
					1.未完成连接队列：处于三次握手过程当中的tcp连接
					2.已完成连接队列：处于握手完毕(连接建立完毕)同时没有被获取的连接
					backlog指定已经完成连接的队列大小，如果已完成连接队列被打满，处理方式就是丢弃掉新来的连接
					使用Recv，从已完成连接队列当中获取创建完成的新连接
		画个图：监听之后创建一个新的socket用于一对一服务
		4.接收连接
			int accept(int sockfd，struct sockaddr* addr，socklen_t* addrlen)
				sockfd：监听套接字操作句柄
				addr：客户端地址信息
				addrlen：客户端地址信息长度
			返回值：返回新创建出来的socket，通过新创建出来的socket和客户端进行数据的收发，一对一服务！
			注意：因为该接口是从已完成连接队列当中获取新的连接，所以，当已完成连接队列当中没有已经完成的，新的连接的时候，该接口调用就会阻塞，直到获取一个新的已完成连接的到来
			为什么需要新创建出来的socket 和 客户端进行通信
				如果只有一个socket，则无法区分是哪个客户端发送的数据，也无法在接收一个TCP连接通信起来之后，再接收新的连接
			因此：ser端只负责调配客户端和哪一个socket连接，每accept一次就创建出一个新的socket
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
				sockfd：accept函数的返回值，也就是新创建的套接字
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
		对于TCP版本的服务器而言：
			服务端：
				创建套接字：socket
				绑定地址信息：bind
				监听：listen
				获取连接：accept
				发送：send
				接收：recv
				关闭套接字：close
			客户端：
				创建套接字：
				绑定地址信息：
				监听：
				获取连接：
				发送数据：
				接收数据：
				关闭套接字：
			封装共同点：给服务端和客户端提供接口
		插入一个图：netstat -anp | grep 19999，既可以看到客户端也可以看到服务端

侦听套接字作用：
1.用来建立连接和发起连接，
2.一旦连接成功，新创建一个1对1的套接字描述符
1.TCP针对每个客户端都会创建一个新的套接字，进行1对1服务
2.UDP是创建了一个套接字服务所有客户端

程序运行结果：
	两个现象：
		1.accept在while(1)外，和一个客户端无限聊(纵有万千只中意一人)，此时再打开客户端，尽管netstat -anp | grep 1999可以看到完成3次握手，但还是不能通信
		2.accept在while(1)里，和一个客户端聊一次之后，程序卡住，因为去接收新的连接了，原操作句柄丢失！！(万花丛中过一片不留身)
	原因：
		1.accept函数在调用时，如果没有客户端发起连接，则会阻塞
		2.recv函数在连接上没有数据的时候，也会阻塞

对于单执行流的程序而言，基于以上两点：
	1.将

解决：多进程TCP，画个图多进程和多线程通信(66班lesson30)
	多线程，多执行流，每个执行流分别连接一个客户端
		1.多进程，父进程每接收一个新链接之后，就创建一个子进程，让子进程和客户端之间进行通信。也就是父进程调用accept，子进程调用recv和send
		2.多线程，

代码还是有问题：
	子进程退出会造成僵尸进程！
*/

/*
UDP调试：
前要：
	struct files_struct files;结构体指针，指向fd_array[]数组，每个下标都代表文件描述符，数组元素是文件的描述信息
	创建socket之后，返回7,3~6是gdb在占用，
udp:
调试：
l			查看前面几行
b 17		17行打断点
n			往下走
p us      查看
s			进去Revc
p sockfd_  查看
	运行Cli
输入hhh 
p buf		看到hhh
s			进入Send
p data
p data.size()
p *dest_addr


*/
//netstat -anp | grep 18888  查看连接状态，超重要！！
//问题：listen_sock 丢失了不会造成内存泄露吗？？

/*
网络基础 2
应用层：
	自定制协议：


*/