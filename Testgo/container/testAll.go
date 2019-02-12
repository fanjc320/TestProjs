package container

import (
	"fmt"
)
//定义一个接收字符串类型参数的函数类型
type handle func(str string)

//exec函数，接收handle类型的参数
func exec(f handle){
	f("hello")
}

func TestHandle(){
	var p = func(str string){
		fmt.Println("first",str)
	}
	exec(p)

	exec(func(str string){
		fmt.Println("second",str)
	})
}