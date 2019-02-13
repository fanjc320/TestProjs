package channel

import(
	"fmt"
	"time"
)


func TestCh0(){
	c := make(chan int)

	go func(){
		defer fmt.Println("子协程结束")
		fmt.Println("子协程正在运行")
		c <-666
	}()

	num := <-c

	fmt.Println("num= ",num)
	fmt.Println("协程结束")
}

func TestCh1(cp int){
	c := make(chan int,cp)
	fmt.Printf("len(c)=%d,cap(c)=%d\n",len(c),cap(c))
	
	go func(){
		defer fmt.Println("子协程结束")
		for i :=0;i < 4;i++ {
			c <- i	
			fmt.Printf("子协程正在运行[%d]:len(c)=%d,cap(c)=%d\n",i,len(c),cap(c))
		}
	}()

	time.Sleep(5*time.Second)

	for i :=0;i<4;i++{
		num := <-c
		fmt.Println("num=",num)
	}

	fmt.Println("main协程结束")
}

func TestCh(){
	ch := make(chan int ,10)
	ch <- 11
	ch <- 12

	close(ch)

	x,ok := <-ch
	fmt.Println(x,ok)

	for x := range ch{
		fmt.Println(x)
	}
}


func TestCh_Block(){
	ch_1 := make(chan int,3)
	// blocked, read from empty buffered channel
	<- ch_1
	ch_2 := make(chan int, 3)
	ch_2 <- 1
	ch_2 <- 2
	ch_2 <- 3
	// blocked, send to full buffered channel
	ch_2 <- 4
}

func TestCh_Range(){
	//channel 也可以使用 range 取值，并且会一直从 channel 中读取数据，直到有 goroutine 对改 channel 执行 close 操作，循环才会结束。
	ch := make(chan int,10)
	for x := range ch{
		fmt.Println(x)
	}
	//等价于
	for{
		x,ok := <- ch
		if !ok {
			break
		}
		fmt.Println(x)
	}
}


func TestCh_Timeout(){

}