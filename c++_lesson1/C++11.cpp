/*
1.列表初始化：支持内置类型列表的初始化
	内置类型：
		 int array[] = { 1, 3, 2 };
		 int a{1};
		 double d{1};
	vector:
		 vector<int> array{ 1, 3, 2 };
	或者 vector<int> array = { 1, 3, 2 };
	map:
		 map<int, int> m = {{1,1}, {2,2}, {3,3}};
		 pair<int, int> p = {1,1};

	自定义类型：只能对应构造函数的参数，而不能直接初始化。可以对构造进行改造，显示定义参数类型为initializer_list<T>
		 A a = {1,2};
	或者 A a2(2, 3);

进行改造：之后就支持列表初始化了
	Vector(const initializer_list<T>& lst)
		:_array(new T[lst.size()])
		, _size(0)
		, _capacity(lst.size())
	{
		for (auto& e : lst)
			_array[_size++] = e;
	}
	
	initializer_list：本质是迭代器，进行了构造
	Vector<int> vec = { 1, 2, 3 };

2.语法糖：
	auto：在编译时，根据初始化表达式进行类型的推导
		  若运行时才能体现类型，就不能使用auto
		std::map<std::string, std::string>::iterator it = m.begin();
		auto it = m.begin();

	decltype：运行时进行类型识别
		decltype(1 + 2) a;		根据1 + 2推演出a的类型为 int
		decltype(func(10)) b;	根据func的返回值类型，推演b的类型为int
		decltype(func);			推到为func的接口类型 int func(int) 

3.范围for

4.
	final： 修饰类：该类不能被继承
			修饰虚函数：不能被重写
	override：编译期间检测当前虚函数是否被重写，如果没有则报错
	
5.智能指针
	
6.容器
	静态数组array：创建时就开辟好空间了，存放在栈空间
	forward_list：单链表
	无序容器：unordered_map：哈希映射
			  unordered_set：哈希集合
			  查找效率很高O(1)，采用链地址法处理哈希冲突

7.
	delete  修饰类成员函数：声明该函数不能被使用
		Date(const Date& d) = delete;
		效果：禁止拷贝

	default 修饰类成员函数：让编译器生成一个默认的函数
		Date() = default;
		效果：生成一个默认构造

8.右值引用：左值右值是一个值！！
	左值：可以出现在=的左右两边或者取地址
		int a = 10;
		int b = a;
		int* p = &a;

	右值：只能出现在=的右边，或者说不可以取地址
		10 = 20；		
		int* p = &10;
		这里 10 就是右值
	
	纯右值：常量、临时变量
	将亡值：生命周期即将结束
		func(a) = b;
		int* p = &(func(a));
		Date()
		临时变量：函数以值返回的变量
		匿名变量：调用构造创建的变量
*/
/*
左值引用：引用实体既可以是左值也可以是右值
	int a = 10;
	int& ra = a;		
	const int& rb = 10;

右值引用：引用实体只能是右值，不能引用左值！！
	int&& lr = 10;
	int&& lr2 = Date(a); <--> const int& r3 = Date(a);

	匿名对象也是右值！
	Date&& rc = Date(10);

	// 做了两件事：1.构造 2.拷贝构造
	// 因为匿名对象是右值，左值引用的引用实体不能是右值
	Date& rc = Date(20)
*/
/*
1.56
右值引用的应用：
	1.返回值为自定义类型，并且用返回值给对象赋值时，系统按理调用两次拷贝构造
	2.而用右值拷贝构造，则只需要一次。右值拷贝是浅拷贝！
	3.右值拷贝构造和左值拷贝构造可以并存，右值构造被称为移动构造，功能提高拷贝效率
		也就是用临时对象或者将亡值进行拷贝构造，系统才会去调用移动构造
自己写一个右值引用的String类：注意给str赋空，移动赋值！

小结：
	1.左值引用和右值引用都是一个变量的别名
	2.左值引用：既可以引用左值也可以引用右值
				如果引用的是右值，则需要const修饰 const char* ar = "qwer";
	3.右值引用：只能引用右值
	4.右值应用的作用：
				拷贝构造时，指向的实体为右值，则实体的资源可以直接被拿走，提高拷贝效率，本质上是浅拷贝

移动构造：参数类型是右值引用，提高了拷贝效率
	1.相对于拷贝构造，可以在浅拷贝的基础上不产生错误
	2.右值引用指向的实体一般是生命周期即将结束的，可以直接获取右值引用所指向的实体资源，而不需要深拷贝

移动赋值：也是浅拷贝，相较于深拷贝(开辟空间并拷贝)，而言效率大大提高

移动语义：需要保证属性被修改的左值，后续不会被使用
	int&& b = move(a);	将左值变成右值
	作用：在组合场景中，把右值对象中的成员变量也变成右值，提高类中移动构造的效率
	否则：移动构造中，类对象的成员变量调用的还是拷贝构造

*/

/*
完美转发：forward 类型，参数类型在传递过程中没有发生任何变化。
	快递的例子：完美转发：快递在运输过程中没有损坏(改变参数类型)
注意：模板参数 + T&& -》未定义引用类型
	template <class T>
	void Test(T &&t)
	{
		Fun(std::forward<T>(t));
	}

小结：右值引用的优点
	1.实现移动构造和移动赋值，在浅拷贝不出错的基础上实现高效率拷贝
*/

/*
排序一个自定义类型：
	1.在类中重载>和<
	2.仿函数
	3.
lambda表达式：匿名函数
	[](const A& a1, const A& a2)->bool 
	{
		return left > right;
	}

	[](){}
	中括号：捕捉列表：捕捉父类作用域中的变量
	小括号：参数列表，可以选择不要
	大括号：函数体，不能修改括号中捕捉到的变量
加mutable：把捕捉列表中的变量属性改成非const
	用法：
		auto func = [a, b](int num)mutable->int{a = 100; b = 20; return a + b + num;};
		func(a, b);

	捕捉列表的使用：
		1.捕捉指定变量 [a, b]
		2.捕捉所有变量 [=] ：传的是一份拷贝，修改了的值不能带出去
			注意：必须捕捉表达式之前已经定义的变量
			[=](){a = 10; a = 20; return a + b;};
		3.捕捉变量引用 [&] ：传的是引用，不需要mutable也可以改变父类中的值
			[&](){a = 10; b = 20; return a + b;};
		4.部分以引用传值 [=, &a]

	注意：lambda表达式不能赋值，但可以拷贝
	auto func1 = [](){};
	auto func2 = [](){};

	不能： func1 = func2
	可以： func3(func2); 或者 auto func4(func2);
		   或者 int (*fptr)(int a, int b);
				fptr = func2;

C++实现lambda表达式的方法：创建一个仿函数的类
*/

/*
C++11的线程库：C++通过构造一个线程对象管理线程
头文件 #include <thread>
注：如果不回收资源，则程序崩溃
1.创建一个线程对象 == 创建了一个新的线程
	thread t1(tfunc1);				// 
	thread t2(tfunc2, 1);
	thread t3(tfunc3, 1, 2, 3);
2.RAII 设计模式：
	1.在构造期间管理
	2.析构期间调用join
3.线程的入口函数是：成员函数
	thread t1(&ThreadClass::func, &tc, 10);
	注意：第一个函数入口地址，第二个参数对象地址(this)，第三个传参
4.线程栈
	1.线程入口函数参数为引用，也不能通过线程函数中修改外部的值
		根本原因：线程具有自己的栈空间，传进函数的是线程栈中拷贝的一份
		因此：需要用 thread t1(func, ref(a)); 用进行ref转换
	2.线程入口函数参数为指针，可以修改外部变量的值

现象：
	1.没有调用 join回收资源时，程序直接崩溃
	2.
*/
/*
1.原子性全局变量：本质是一个模板
	两种写法：atomic<int> a(1);		// 建议写法
			  atomic_int  a{1};
	1.所有线程访问这个变量都是串行的
	2.对变量加锁操作影响程序效率（加锁、开锁）

2.使自定义类型的成员变量具有原子性：
	atomic<number> atomic_number(n);

3.加锁和解锁
	mutex mtx;	互斥锁
	加锁：mtx.lock();	
		  mtx.try_lock_for()：等一段时间
		  mtx.try_lock_until()：等到具体某个时间点
		  mtx.trylock();	如果锁资源被占用，不会阻塞而是返回加锁失败
	解锁：mtx.unlock();		阻塞直到拥有锁

	注意：
		1.同一个线程在拥有锁资源的情况下，再次加同一锁则代码崩溃。(死锁)
		2.Linux中不会崩溃但是程序永久阻塞，直到发送信号而进程退出

4.守卫锁：是一个对象，作用：为了在线程发生异常时也能进行解锁操作
	1.在构造时进行加锁
	2.析构时进行解锁
	3.声明拷贝为delete函数，也就是不能拷贝构造
		lockGuard(const lockGuard<Mutex>&) = delete;
		lockGuard& operator=(const lockGuard<Mutex>&) = delete;

template <class Mutex>	//模板类型!!!
class lockGuard
{
	lockGuard()
	{}
	~lockGuard()
	{}
};

作用：减少人为的加锁解锁失误，这个对象在构造时解锁，析构时解锁
*/
/*
多线程安全：
	1.原子性操作：指令不会被打断，线程安全操作，效率比较高
		atomic<T>：把 T 类型的数据封装成原子性操作
	2.加锁：通过多线程之间的加锁阻塞，保证线程安全，效率低下，相对原子性操作加锁解锁耗时
		mutex, recrusive_mutex, timed_mutex, recrusive_timed_mutex
	lock_guard, unique_lock：RAII实现
		通过对象的生命周期控制锁的生命周期
		构造函数：加锁 
		析构函数：解锁
		用delete修饰成员函数，代表拷贝和赋值不能被使用

小结：C++11 重点
	列表初始化
	右值引用
*/

/*
异常处理：
	malloc 申请失败返回空指针
	 new   申请失败就抛出异常 bad_alloc，程序直接崩溃

	1.常用关键字：try、catch、throw
		  try：受保护的代码
		throw：抛出异常
		catch：捕获异常
try
{
	func();
}
catch(int n)
{
	cout << "char" << endl;
}
	2.异常捕捉特点：
		1.异常由 throw 抛出
		2.根据就近原则，也就是如果受保护代码中有函数嵌套，则被最近的catch()所捕获
		3.抛出异常后，会生成一个异常对象的拷贝
		4.catch(...)可以捕获所有异常

	3.异常抛出流程
		1.若第一层 catch 不能够处理。则往上层栈中跳转，如果还是不能处理。则跳到主函数抛异常，程序崩溃
		2.如果第一层 catch 处理掉异常了，则顺序向下执行不会跳栈
	自己测试：上层处理完成之后，会回到原始栈中吗？？
		并不会！！！会忽略之前的所有调用栈！(也符合栈的思想，只能出栈栈顶元素才能访问栈下面的元素)

	4.抛出的异常一定要处理！！就算不知道怎么处理，也不要让程序崩溃，最多重置一下，增加程序的鲁棒性。
		面试常考考点！！
	
	5.重新抛出异常！！
		1.当一个调用栈中申请了空间，但是内层调用栈中发生异常，并且当前层无法处理
		2.则必须有 catch(...) 将异常捕获，并清理申请的资源，然后将异常继续抛出

		注意：
			1.若没有处理申请空间会造成内存泄露
			2.析构中若出现异常可能造成内存泄露，则析构中药重新抛出，先释放资源
			3.构造中若抛出了异常可能造成初始化工作没有完成，对象残缺
	
	6.多个异常被抛出：throw(A, B, C, D);
	                  throw(bad_alloc);
					  throw();

	7.工程上异常处理：
		继承基类的异常处理方式：C++ std::exception
		try
		{
			vector<int> vec;
			char* ptr = new char[0x7fffffff]
		}
		catch(exception& e)	// 指针或者引用则可以体现多态性！！！！
		{
			cout << e.what() << endl;
		}
		catch(...)
		{
			cout << "未知异常" << endl;
		}
		用所有异常的根基类的引用或者指针进行捕获，可以匹配所有继承体系的所有类型
		通过根基类虚函数的重写，完成多态的逻辑，最终完成多态行为，完成异常的精确处理
	
	异常优点：
		1.增强鲁棒性
	异常缺点：
		1.
	异常使用：
		基类：其他类去继承基类，然后对虚函数进行重写，构成多态
*/

/*
RAII思想的三次使用：根据对象的生命周期控制资源的生命周期
	1.线程创建和析构：对象创建时创建线程，析构时回收线程
	2.线程锁：对象构建时加锁，析构时解锁
	3.智能指针：构造函数对资源进行链接，析构函数进行释放

智能指针：垃圾回收机制，防止内存泄露

template <class T>
class smartPtr
{
public:
	smartPtr(T* ptr)
		:_ptr(ptr)
	{}
	smartPtr(smartPtr<T>& sp)	// 管理权转移
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}
	~smartPtr
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
	smartPtr<T>& operator=(smartPtr<T>& sp)
	{
		if (this != &sp)
		{
			if (_ptr)
				delete _ptr;
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		rerturn *_ptr;
	}
	T* operator->()		// -> 的使用：如果T类型是自定义类型，则->可以直接访问
	{
		return _ptr;
	}
private:
	T* _ptr;
};

正确使用：smartPtr<int> sp(new int);	// 构造一个匿名对象，因此只能sp指向
错误示范：
		  int* ptr = new int(1);
		  smartPtr<int> sp1(ptr);
		  smartPtr<int> sp2(ptr);	// 这里ptr所指空间会因为被释放两次而程序崩溃

2.库中的智能指针：auto_ptr
	#include <>
	auto_ptr<Date> ap(new Date);
	auto_ptr<Date> ap2 = ap;		// 管理权转移，ap已经被赋空
	cout << ap->_year << endl;		// 代码崩溃
	注意：
		1.拷贝时发生管理权转移，源指针不在拥有资源，否则代码崩溃！
		2.auto_ptr：有解引用异常的风险(空指针)，一般不使用

3.unique_ptr：不会有管理权转移的问题
	解决方法：将拷贝用delete修饰，因此不能使用拷贝，即防拷贝
	

	模拟实现：
tempalte <class T>
class Unique_ptr
{
	Unique_ptr(const Unique_ptr<T>& upt) = delete;
};


4.share_ptr：可以拷贝和赋值，本质是用了引用计数和浅拷贝(自己模拟实现一下！)
	使用实例：
		shared_ptr<Date> sp(new Date);
		shared_ptr<Date> sp1(sp);		// 拷贝构造
		shared_ptr<Date> sp3(new Date);
		sp3 = sp;						// 赋值重载
		
	注意：这三个智能指针指向同一空间
	内部方法：析构时先判断引用计数，类似写时拷贝技术，本质是浅拷贝
		use_count：引用计数

	析构方法：
		1.先对引用计数--，判断引用计数，若为0则析构。不为0则不析构。
	构造方法：
		1.对引用计数++
	赋值方法：
		1.对引用计数--，然后判断若为0则调用析构。并调整指向，使计数++

	问题：引用计数的类型？
		int可以吗？
			不可以！作用范围太小！引用类型不同步！意思是新的拷贝到来之后不能使它++
		static int 可以吗？
			不可以！作用范围太大！造成所有智能指针都用的一个引用计数
		int*：只能使用指针类型，所有拷贝和赋值对象都指向同一堆空间！

	注意：
		优化：判断是否是同一对象资源给同一对象资源赋值
		简而言之：管理资源是否相同
		if (_ptr != sp._ptr)	原来的写法  if (this != &sp){...}
		{
			....
		}

5.多线程下的智能指针：auto_ptr 和 unique_ptr 不会出现多线程二义性，因为本质上没有赋值和拷贝！！
	shared_ptr：会使引用计数++--操作，而这个操作是由多条指令完成的，写入内存可能被打断，因此需要保证线程安全！

	解决：加锁！什么锁？？
		全局锁？不行！在赋值的场景：我只是修改的别的智能指针，不应能因为赋值而被阻塞
		类的成员锁！
	具体操作：
		1.增加成员变量锁资源，在构造，拷贝构造，复制重载中需要初始化锁，在析构中解锁
		2.在类中增加addRef()和 subRef 的方法！
		3.对每个操作引用计数的地方都要改造，改造成 addRef() 和 subRef()，在这两个方法中增加枷锁解锁语句

	shard_ptr不能保证其他资源线程安全？？？

循环引用：
template <class T>
struct ListNode
{
	shared_ptr<ListNode<T>> _prev;
	shared_ptr<ListNode<T>> _next;
};

void Test()
{
	
}

造成的问题：
	1.

解决：
	1.将ListNode中的左右指针域改成：weak_ptr<ListNode<T>>
	2.weak_ptr 的引用，不会使引用计数++ --

注意：
	weak_ptr 不能单独使用，只能使用 shared_ptr 进行初始化，专门解决 shared_ptr 的循环引用问题

定制删除器：
	智能指针的第二个参数
	shared_ptr：默认采用 delete 去释放资源，因此


智能指针小结：
	1.实现：
		1.RAI 思想：
		2.实现指针的类似功能，解引用和箭头
	2.auto_ptr
		由于赋值和拷贝时，会发生权限转移，当前指针为空，因此不能使用
	3.unique_ptr
		防拷贝：用delete修饰了拷贝构造和赋值重载
		不涉及智能指针拷贝的情况下可使用
	4.shared_ptr
		通过引用计数解决拷贝问题，拷贝++，析构--，直到为0则释放
		特殊场景：循环引用造成的问题，需要用 weak_ptr 解决
		线程安全：shared_ptr 的实现是线程安全的，但是智能指针所管理的资源需要用户去保证线程安全！

*/

/*
特殊类
	1.只能在堆上创建对象
		1.构造函数是私有的
		2.在内部写一个函数，返回堆上开辟空间的首地址
			注意：这个函数得是static修饰的静态成员函数
		3.防拷贝：将拷贝构造用delete修饰，或者声明为私有

	2.只能在栈上创建对象
		第一种
		1.构造函数是私有的
		2.在内部写一个函数，返回匿名对象
		第二种
		1.构造函数是私有的
		2.将关键字 new 用 delete修饰

	3.一个类不能拷贝
		1.拷贝构造和赋值用delete修饰
		或者拷贝和赋值为私有

	4.不能被继承的类
		1.构造为私有或者用final修饰父类

	5.只能创建一个对象(单例模式)
	饿汉模式
		1.构造函数私有
		2.成员变量：静态的单例成员
			注意：必须给静态的，原因：静态不是类成员，在计算大小时不计算静态的，静态在数据段
		3.给一个函数获取，当前单例的地址。
			注意：这个函数要是静态的
		4.需要在类外对静态变量进行初始化
		5.防拷贝和赋值

	优点：实现简单，并且在多线程下效率很高，不需要枷锁解锁
	缺点：程序启动慢，程序启动时创建好一个对象，多个单例对象初始化顺序无法控制
		
	懒汉模式
		1.构造函数时私有的
		2.成员变量该类的静态指针
			注意：静态指针赋空
		3.给一个函数，判断如果指针为空，则创建对象，否则返回指针
		4.拷贝构造和赋值用delete修饰
		5.保证线程安全，双检查提高效率

	优点：延迟加载，程序启动快，可以指定多个单例对象的初始化顺序(第一次调用时才创建)

	线程安全问题：
		饿汉模式下不会出现问题，因为程序启动单例就被创建好了
		懒汉模式会去判断指针是否为空，如果为空则创建对象，则可能多个线程都创建了对象
			解决：在判断指针是否空的地方进行加锁和解锁
		优化：双判断，先进行一次判断指针是否为空，如果为空则加锁继续判断是否为空，为空则创建对象。
			  如此：后序的线程不会因为加锁解锁影响程序运行效率

*/

/*
类型装换：

隐式类型转换：意义比较接近
	char c = 'a';
	int a = c;
	float f = 1.2f;
	int d = f;

强制类型转换：意义差别大
	int* ptr = &a;
	int e = (int)ptr;
	int *ptr2 = (int*)a;

1.static_cast：(静态转换)支持所有隐式类型转换
	int m = static_cast<int>(c);
	int d2 = static_cast<int>(f);

2.reinterpret_cast：支持强制类型转换
	int* ptr3 = reinterpret_cast<int*> (a);

3.const_cast：去掉const属性
	const int ca = 10;
	int* ptr = const_cast<int*> (&ca);
	*ptr = 20;	// 此时内存中ca的值变成了20，
				   但是由于const修饰，因此编译器是在寄存器中或者缓存中读取了，结果还是10
	cout << ca << endl;		// 结果10，内存中20
				如果加volatile修饰ca，则输出还是20

4.dynamic_cast：(动态转换)只能用于多态转换，进行向下转型：进行安全转换，如果不安全则返回空
	A* pa = new A;
	A* pb = new B;

	B* pb2 = (B*)pa;				// 有问题，若子类中新增的，基类中没有则会发生越界访问。本质按照子类指针解析
	B* pb3 = dynamic_cast<B*> (pa);	// 会转换失败，因为不安全，返回nullptr

	B* pb4 = dynamic_cast<B*> (pb);	// 转换成功，因为是安全的

	// 用静态转换static_cast，不安全
	B* pb5 = static_cast(B*) (pb);

5.explicit：阻止进行隐式转换？？什么意思？？


6.RTTI：运行时类型识别
	typeid：判断数据的类型
	dynamic_cast

*/

/*
STL空间配置器：
	解决以下问题：
		1.申请的内存可能忘记释放
		2.频繁的申请和释放，影响效率
		3.造成内存碎片化，空间利用率低

一级空间配置器：
	1.对malloc和free的封装，以及对空间不足的处理方式
	2.处理方式：oom_malloc (out_of_memory)，去内存中寻找

二级空间配置器：管理小于等于 128 比特的空间
	1.管理一个内存池(分配一块较大的内存)
		问题：怎么管理回收空间的顺序？	
	2.用哈希桶管理小块内存(16个桶，8的整数倍)
		第一个位置：8字节
		第二个位置：16字节
		第三个：	24字节
		  。
		  。
		  。
		最后		128字节

	问题：为什么要分配8的整数倍？
		为了方便内存对齐

	3.申请流程：
		1.计算大小
		2.在哈希桶中找对应大小的内存块，拿去内存块

	4.如果桶中没有对应的空间的内存块，则

整个申请流程：n byte
	1.进行内存大小向上对齐：round_up
	2.根据对齐的内存大小计算哈希桶号
		a.如果对应的哈希桶中有内存块，分配给用户一块内存，空间申请结束
		b.如果对应的哈希桶中没有内存块，则向内存池申请：chunk_alloc(n, njobs)
			首先计算需要申请的总空间大小：int total = n * njobs;
			然后计算内存池中剩余的空间大小：int left = finish - start;
			if (left > rotal)
				从内存中划出需要的空间
				更新 start += total
			else if (left > n)
				重新计算可以分配的njobs(块):njobs = left / n;
				从内存池中划出重新计算的空间

			else：剩余的空间不足用户需要的大小
				1.如果内存池中还有空间：将剩余空间挂到对应哈希桶中
				2.向系统申请空间
					if 申请成功：放入内存池，继续调用chunck_alloc
					if 申请失败(系统没有空间)：
						从更大的哈希桶中寻找空间(之前是没有找哈希桶的，而是直接去内存池中找)
							if 有：取出一块放入内存池，继续调用chunck_alloc
							if 没有：
								调用一级空间配置器(里面有空间不足应对措施)
									if 申请成功：放入内存池，继续调用chunck_alloc
									if 申请失败：抛出异常 _bad_alloc
		c.把第一块给用户

二级空间配置器申请空间顺序：
		1.哈希桶找
		2.内存池找
		3.系统中找
		4.更大的哈希桶找
		5.调用一级空间配置器

内存池是缓慢变大的，在





*/