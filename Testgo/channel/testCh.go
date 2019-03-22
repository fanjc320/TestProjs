package main 

import(
	"fmt"
	"time"
	"runtime"
)

func Test_Range(){
	ch := make(chan int,10)
	/*
	go func(){
		<- ch
	}()*/
	for i:=0;i<10;i++{
		ch<-i
		time.Sleep(10*time.Millisecond)
	}
	close(ch)
	//for循环中，如果循环变量不是指针，那么每次的变量是同一个，不过值变了,说明这里的v是副本,而且是一个值
	for v := range ch{
		fmt.Println(&v)//输出是同一个数
	}
}

//len and cap
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

//死锁 ======================================================= important ===============================
func TestCh_DeadLock(){
	ch := make(chan string)//dead lock!
	//ch := make(chan string,2)//ok
	
    // 在此处阻塞，然后程序会弹出死锁的报错

	//放到groutine中则不会思索
	go func(){
		runtime.Gosched()
		ch <- "hello"//假如别的go程没有塞入数据，但是至少有主go程，即使主go程不塞入数据，这里会一直阻塞到程序退出
		fmt.Println("func is done!!")
	}()
	
	//ch <- "hello" //此时gofunc进ch的内容没有被取出，ch如果再塞入，会阻塞，知道发现func已执行完，没有goroutine了,所以deadLock!!!!!
	//在往ch塞数据的时候，其他groutine已关闭，所以dead lock

	h := <- ch//此时如果groutine在，ch会阻塞等待groutine塞入数据，然后取出,如果groutine没有塞入数据就执行完毕，会deadlock
	//h1 := <- ch//同理，没有goroutine了之后，ch已被取空,所以阻塞，同时发现没有了别的groutine，所以dead lock
    fmt.Println("channel has send data "+h)
}

func TestCh_DeadLock1(){
	ch := make(chan int)
	go func(){
		ch <- 1
		time.Sleep(1)
	}()
}


//单向
func TestCh_OneDirection(){
	ch := make(chan string)
	go func(out chan<- string){
		out <- "hello"
	}(ch)
	
	go func(in <-chan string){
		fmt.Println(in)
		fmt.Println(<-in)
	}(ch)

	time.Sleep(2*time.Second)
}

//注意由于ragne的阻塞作用，输出内容的顺序
func TestBlock(){
	data := make(chan int)
    exit := make(chan bool)

    go func() {
        for v := range data {
            println(v)
        }

        println("receive over")
        exit <- true
    }()

    data <- 1
    data <- 2
    data <- 3
    close(data)

    println("send over")
    <-exit
}

//并发,面向channel编程
func main(){
	//TestCh1(10)
	//TestCh_Block()
	//TestCh_DeadLock()
	Test_Range()
}

//程序结束，只会执行所有主go程代码，并不会等待所有goroutine结束运行，除非使用sync.WaitGroup
// golang中的同步是通过sync.WaitGroup来实现的．WaitGroup的功能：它实现了一个类似队列的结构，可以一直向队列中添加任务，
// 当任务完成后便从队列中删除，如果队列中的任务没有完全完成，
// 可以通过Wait()函数来出发阻塞，防止程序继续进行，直到所有的队列任务都完成为止．
// WaitGroup的特点是Wait()可以用来阻塞直到队列中的所有任务都完成时才解除阻塞，而不需要sleep一个固定的时间来等待．
// 但是其缺点是无法指定固定的goroutine数目．但是其缺点是无法指定固定的goroutine数目．可能通过使用channel解决此问题。