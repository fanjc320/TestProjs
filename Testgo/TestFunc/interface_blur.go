package main

type TestI interface{
	show()
}

type TestI2 interface{
	show()
}

type Person struct{
	Name string
	age int32
	Work string 
}

//同时实现了TestI和TestI2两个接口,go不存在明确的实现接口，只要实现了接口里的所有方法，就是实现了接口，就可以被赋值给接口
func (p Person)show(){
	println("name:",p.Name,"age:",p.age)
}

//并非接口
func (p Person)work(){
	println("name:",p.Name,"work:",p.Work)
}

func Test1(){
	p := Person{"Test1",29,"cpper"}
	p.show()
}

func Test2(){
	var ii TestI
	p := Person{"Test2",30,"javaer"}
	ii = p
	ii.show()
	p.show()
}

func Test3(){
	var ii TestI2
	p := Person{"Test3",30,"gopher"}
	ii = p
	ii.show()
	p.show()
	p.work()
}

func main(){
	//var ii TestI2
	//Test1()
	println("-----------------------------")
	//Test2()
	println("-----------------------------")
	Test3()

}