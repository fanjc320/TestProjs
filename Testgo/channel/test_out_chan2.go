package main

import "fmt"
import "time"

var closeChan = make(chan int,10)

// A退出后，进入B的10个goroutine也退出
func A(){
	defer func(){
		for i:=0;i<10;i++{
			closeChan <-1
		}
	}()
	time.Sleep(time.Second*3)
}

func B(i int){
	for{
		flag := <-closeChan
		if flag==1{
			fmt.Println("b getout:",i)
			return
		}
	}
}

func main() {

	go A()
	for i:=0;i<10;i++{
		go B(i)
	}

	time.Sleep(time.Second * 30)
}