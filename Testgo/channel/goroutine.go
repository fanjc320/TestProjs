package channel

import(
    "fmt"
    "sync"
)

func worker(start chan bool,index int){
    <- start // 从start中取出数据后，调用20行的case语句 //接收并将其丢弃
    fmt.Println("This is Worker:",index)
}

func TestGoroutine(){
    start := make(chan bool)
    for i:=1;i<=10;i++{
        go worker(start,i)
    }
}

func Producotr(mychan chan int,data int,wait *sync.WaitGroup){
    mychan <- data
    fmt.Println("product data:",data)
    wait.Done()
}
func Consumer(mychan chan int,wait * sync.WaitGroup){
    a := <- mychan
    fmt.Println("consumer data:",a)
    wait.Done()
}

//goroutine本质上是协程，可以理解为不受内核调度，而受go调度器管理的线程。
//goroutine之间可以通过channel进行通信或者说是数据共享，当然你也可以使用全局变量来进行数据共享。
//示例：使用channel模拟消费者和生产者模式
func TestGoroutine_1(){
    datachan := make(chan int,100)
    var wg sync.WaitGroup
    for i:=0;i<10;i++{
        //go Producotr(datachan,i,&wg)
        go Consumer(datachan,&wg)
        wg.Add(1)
    }
    for j:=0;j<10;j++{
        //go Consumer(datachan,&wg)
        go Producotr(datachan,j,&wg)
        wg.Add(1)
    }
    wg.Wait()
}