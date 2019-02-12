package TestFunc
import "fmt"

type handler func(name string)int

func (h handler) add(name string)int{
	return h(name)+10
}

type adder interface{
	add(string)int
}

func process(a adder){
	fmt.Println("process:",a.add("taozs"))
}
func doubler(name string)int{
	return len(name)*2
}

type myint int
//go 没有显式的关键字用来实现 interface，只需要实现 interface 包含的方法即可。
func (i myint)add(name string)int{
	return len(name)+int(i)
}

func TestFunc(){
	var my handler = func(name string)int{
		return len(name)
	}
	fmt.Println(my("taozs"))//调用函数
	fmt.Println(my.add("taozs"))//调用函数对象的方法
	fmt.Println(handler(doubler).add("taozs"))//doubler函数显示转换成handler函数对象然后调用对象的add方法

	//以下是针对接口adder的调用
	process(my)//process函数需要adder接口类型参数
	process(handler(doubler))//因为process接受的参数类型是handler,所以这儿要强制转换
	process(myint(8))//实现adder接口不仅可以是函数也可以是结构体
}