# cpps script
cpps脚本是一个基于c++的脚本语言。

项目没有投资，没人使用，所以佛系更新，希望有哪家大企业看中可以投资我呀！！

其代码风格更像c++， 给那些跟我一样不喜欢py,lua,js做脚本的朋友一个很好的脚本语言。


2020-11-10 更新2

1.修复父类构造函数执行顺序

2.增加调用父类虚函数的功能

3.增加父类对名空间的支持

```
namespace cpps
{
	class C
	{
		C()
		{
			println("C class");
		}
		var test()
		{
			println("C->test()");
			
		}
	}
}
class A : cpps::C
{
	var name;
	A(int a){
		println("A class:"..name);
	}
	
	var test()
	{
		println("A->test()");
				
		println(name);
	}
}

class B:A
{
	var age;
	B(){
		A::constructor(10);
		println("B class");
	}
	var test()
	{
		println("B->test()");
		println(age);
		cpps::C::test();
	}
}


var b = new B(){
	name = "john",
	age = 32
};

b.test();

输出：
[Cpps 1.2.0 Copyright (C) 2015-2020 By Johnson, Pub-test]
C class
A class:john
B class
B->test()
32
C->test()
>
```

2020-11-10 更新

重写foreach 

老版本使用lambda 方式，很不好。

修改成 
```
var a = [1,2];

foreach(var item in a)
{
	println(item);
	foreach(var item2 in a)
	{
		println(item2);
	}
}

var b = {a:1,b:"2"};

foreach(var item in b)
{
	println(item.first());
	println(item.second());
}
```

增加 new 时设置变量功能类似c#

```
class A
{
    var name;
    var age;
}
var a = new A(){
    name = "john",
    age = 32
}
```

2020-1-28 更新

新年快乐~~ happy new year!

1.今天恢复了对linux gcc++ 的编译支持。

对linux实在不太熟悉。一堆警告。很糟心。

2.增加make lib 与 make install指令

3.cpps 默认工作目录为指定文件目录。

2020-1-21 更新

解决了&&与|| 未按照顺序执行导致逻辑错误的BUG。

2020-1-20 更新

增加const的支持。

const var abc = "10"; //不可修改。

2020-1-19 更新

1.增加调用函数参数支持到11个

2.增加支持构造函数。 c++ 部分需要注册一个名为constructor的函数当构造函数

3.并且修复多层名空间有错误的BUG。

4.增加类似js 当创建出匿名函数后并且调用的方法 例子：
```
[](var a){

	println(a);

}(123);
```


2019-12-7 更新

之前老版本是在函数结束后才调用GC，那么如果想在主函数写一个死循环执行逻辑就会造成内存永不会被GC释放，现在会在符合内存大小等限制情况下调用GC释放内存了。具体大小见CPPS_GEN0_CHECKSIZE ，等宏定义。

2019-11-01

修复lambda函数在传递时当前与偶发崩溃的BUG。

增加foreach 函数支持break操作

前面更新就不介绍了。乱七八糟的。

```
var i = toint(io.getc());

if(i == 10)
{
	println("i 等于 10");
}
else if(i > 10)
{
	println("i 大于 10");
}
else
{
	println("i 小于 10");
}

for(var i = 0;i < 10;i++)
{
	println(i);
}

class abc
{
	var a;
    var b = 10; //可以定义默认值
    var testfunc(var c)
    {
    	println(c);
        println(a);
        println(this.b);
    }
}
var obj = new abc;
obj.testfunc(10);

//继承关系
class abcd : abc
{
	var d = 10;
}

var obj2 = new abcd;
obj2.testfunc(20);
println(obj2.d);

var str = "hello world"; //字符串类型
var i = 10; //整数类型
var n = 3.1415926; //浮点类型
var b = true; //布尔类型
var g = new map; //对象类型
class abc
{
	var a = 10;
}
var a = new abc; //类对象类型
// 2-9日更新 可定义多个变量
var a1 = 0, a2 = 10,a3 = 20;
//8月31日更新
var b = 0xffff;

var str = "hello";
println(str.."world");

var o = str.."haha".."ooo"..str;
println(o);

var testfunc(var i)
{
	println(i);
}

testfunc(10);

更多例子，请查看脚本文档。。。


```

脚本文档在

http://www.kancloud.cn/johnsonyl/cpps/260361

QQ群：

CPPS脚本交流群 282081601

作者Q：88481106

有兴趣可以加群或者QQ聊聊。

脚本完全是自己的兴趣开发，不建议商用，可以当学习和娱乐使用。


