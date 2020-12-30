/*
(多态就是对继承的扩展，既想拥有基类的一部分内容，又想在某些函数中添加独立的处理方式)
1.什么是多态？(标明环境)
	通俗来说就是多种形态，完成某种行为时，不同对象去完成时会产生不同的结果
2.多态分类
3.多态实现条件
	前提：必须在继承方式下
		1.基类中必须有虚函数，子类必须要对基类中的虚函数进行"重写"
		2.虚函数调用：通过"基类的指针"或者"引用"来调用虚函数，因为基类的指针是可以指向子类对象的
4.多态体现：
	1.程序运行时才能体现多态，根据指针或者引用指向不同类的对象调用对应类的虚函数
	2.编译阶段，只进行语法检测,编译器不知道指针指向的是哪一个类对象

5.重写 he 虚函数
	虚函数：被virtual关键字修饰的成员函数称之为虚函数
	重写：
		1.一定是子类对基类中的虚函数进行重写，如果基类的成员函数不是虚函数则一定不是重写
		2.子类虚函数必须要与基类虚函数的原型一致，返回值类型、函数名(参数列表)必须完全一致
			特例：
				协变："基类"虚函数返回"基类的"指针或者引用，"子类"虚函数返回"子类的"指针或者引用
				析构函数：只要基类中的析构函数是虚函数，子类析构函数给出之后就对基类析构进行重写了(函数名不同，但也构成重写)
注意事项：
	1.如果子类涉及资源管理，基类中析构函数必须设置为虚函数，否则可能造成内存泄露
		原因：基类指针指向动态开辟的子类地址，delete时如果基类中的析构不是虚函数(没有构成重写)，子类的动态资源则不能完全释放
		编译器会先调用子类中的析构函数，再调用基类的析构函数
	2.重写后，子类虚函数和基类的虚函数访问权限可以不同，也不影响调用
		
6.检测虚函数是否重写成功
	override 和 final
	override：让编译器在编译期间，帮助检测子类是否对基类的虚函数重写成功
		virtual void TestFunc() override
	编译器在编译期间：回到基类中找virtual void TestFunc()
		找到：重写成功，通过编译
		没找到：重写失败，编译失败
	override关键字只能修改子类中的虚函数
	
	final：
		1.可以修改类，表明该类不允许被继承
		2.可以修饰虚函数，表明虚函数不能被子类重写
7.函数重载，同名隐藏(重定义)，重写(覆盖)的区别
	1.函数重载：相同的作用域，函数名相同，参数列表不同则构成重载，与返回值无关
		在继承体系下函数的作用域不同，因此不是函数重载
	2.同名隐藏：成员变量或者成员函数
	  重写：只能是成员函数
	  在继承体系中，基类和子类中两个成员函数名相同，则不是重写就是同名隐藏
注意：
	1.如果没有写 virtual 则产生同名隐藏
	2.引用不可缺！！！
	3.子类涉及资源管理，基类析构必须为虚函数
*/
/*
抽向类：将包含纯虚函数的类 称之为

虚表中的虚拟地址是无法修改的
子类的虚表先继承父类的虚表，再将对应重写的函数改成自己的函数入口地址
*/


/*
多态在强转时不会生成新的一份拷贝！！
但其他的按理说会生成一份拷贝

*/