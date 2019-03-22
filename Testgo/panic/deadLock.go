package main

import (
	"fmt"
	"time"
	"runtime"
)

func f1() {
	fmt.Println("call f1...")
	runtime.Gosched()
	time.Sleep(1000*time.Millisecond)
	println("f1 is out")
/*
	for{
		fmt.Println("-")
	}
	*/
}


//deadlock 
	//ch := make(chan int)
	//ch <- 1
	//close(ch) //是否有这句都报错
	//<-ch //是否有这句都报错

//deadlock
	//ch := make(chan int)
	//ch <- 1
	//<-ch //是否有这句都一样
	//close(ch) //如

//ok
	//ch := make(chan int)
	//close(ch) 

//deadlock
	//ch := make(chan int,1)
	//ch <- 1//all goroutines are asleep - deadlock! 必须在groutine结束前，向channel中发送或接收数据，否则报错
	//<-ch//同上
	//<-ch//同上
	//close(ch) 

//ok
	//ch := make(chan int,1)
	//ch <- 1//all goroutines are asleep - deadlock! 必须在groutine结束前，向channel中发送或接收数据，否则报错
	//close(ch) 
	//<-ch//同上
	//<-ch//同上


func main() {
	//go f1()//有没有这句都一样，除非f1里是死循环
	//ch := make(chan int,1)//ok
	ch := make(chan int)
	ch <- 1//all goroutines are asleep - deadlock! 必须在groutine结束前，向channel中发送或接收数据，否则报错
	close(ch) 
	<-ch//同上
	<-ch//同上
	// 通道就是在goroutine使用的，价值在于在goutine和goutine或主线程间传递数据，否则没有意义
	// 所以必须在groutine都结束前发送或接收数据
	println("main is out ")
}
