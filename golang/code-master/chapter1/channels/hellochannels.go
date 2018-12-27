package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func printer(ch chan int) {
	for i := range ch {
		fmt.Printf("Received %d ", i)
	}
	wg.Done()
}

// main is the entry point for the program.
func main() {
	c := make(chan int)
	go printer(c)
	wg.Add(1)

	// Send 10 integers on the channel.
	for i := 1; i <= 10; i++ {
		c <- i
	}

	close(c)
	wg.Wait()
}


// = 使用必须使用先var声明例如：
//var a
//a=100
//或
//var b = 100
//或
//var c int = 100
 
// := 是声明并赋值，并且系统自动推断类型，不需要var关键字
//d := 100

