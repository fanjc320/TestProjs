package main

import "fmt"
import "time"

func main() {
	closeChan := make(chan int, 3)

	go func() {
		i := 0
		var flag int = 0
		go func() {
			flag = <-closeChan
		}()
		for flag == 0 {

			i++
			fmt.Println("goroutine 1", i)
			time.Sleep(time.Second * 1)
		}
	}()

	go func() {
		i := 0
		var flag int = 0
		go func() {
			flag = <-closeChan
		}()
		for flag == 0 {

			i++
			fmt.Println("goroutine 2", i)
			time.Sleep(time.Second * 1)
		}
	}()

	go func() {
		i := 0
		var flag int = 0
		go func() {
			flag = <-closeChan
		}()
		for flag == 0 {

			i++
			fmt.Println("goroutine 3", i)
			time.Sleep(time.Second * 1)
		}
	}()

	time.Sleep(time.Second * 10)
	closeChan <- 1 // 关闭1个

	time.Sleep(time.Second * 10)
	closeChan <- 1 // 关闭1个

	time.Sleep(time.Second * 10)
	closeChan <- 1 // 关闭1个

	time.Sleep(time.Second * 30)
}
// --------------------- 
// 作者：eclipser1987 
// 来源：CSDN 
// 原文：https://blog.csdn.net/eclipser1987/article/details/17224683 
// 版权声明：本文为博主原创文章，转载请附上博文链接！