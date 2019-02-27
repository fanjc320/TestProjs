package channel

import(
	"fmt"
	"time"
	"sync"
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

//死锁
func TestCh_Block(){
	ch := make(chan string)
	
    // 在此处阻塞，然后程序会弹出死锁的报错
	//ch <- "hello"

	//放到groutine中则不会思索
	go func(){
		ch <- "hello"
	}()
	
	h := <- ch
    fmt.Println("channel has send data "+h)
}

func TestCh_Block1(){
	ch := make(chan string)
	go func(){
		// 在执行到这一步的时候main goroutine才会停止阻塞
        str := <- ch
        fmt.Println("receive data：" + str)
	}()

	ch <- "hello"
    fmt.Println("channel has send data")
}

func cal(a int,b int,n * sync.WaitGroup){
	c := a+b
	fmt.Printf("%d + %d = %d \n",a,b,c)
	defer n.Done()
}

func TestCh_Sync(){
	var go_sync sync.WaitGroup
	for i:=0;i<10;i++{
		go_sync.Add(1)//WaitGroup的计数加1
		go cal(i,i+1,&go_sync)
	}
	go_sync.Wait()//等待
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