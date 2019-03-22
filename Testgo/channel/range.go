package main
import (
	"fmt"
	"time"
	"strconv"
)

func TestCh_Range(){
	ch := make(chan int ,10)
	//ch := make(chan int)//all goroutines are asleep - deadlock!
	ch <- 11
	ch <- 12

	//如果注释掉close ,引发下面的range fatal error: all goroutines are asleep - deadlock!
	close(ch)

	//x,ok := <- ch
	//fmt.Println(x,ok)

	for x := range ch{
		fmt.Println(x)
	}

	x,ok := <- ch
	fmt.Println(x,ok)

	//没有这个形式
	/*
	for x,ok := range ch{
		fmt.Println(x)
	}*/

	fmt.Println("-----########----------")
}

func TestCh_Range1() {
	cs := make(chan string)
    go receiveCakeAndPack1(cs)
	go makeCakeAndSend1(cs, 10)
	fmt.Println("===============")
	go makeCakeAndSend1(cs, 5)

    //sleep for a while so that the program doesn’t exit immediately
    time.Sleep(3 * 1e9)
}


//数据接受者总是面临这样的问题：何时停止等待数据？还会有更多的数据么，还是所有内容都完成了？我应该继续等待还是该做别的了？
//对于该问题，一个可选的方式是，持续的访问数据源并检查channel是否已经关闭，但是这并不是高效的解决方式。Go提供了range关键字，将其使用在channel上时，会自动等待channel的动作一直到channel被关闭

func TestCh_Range2(){
	data := make(chan int)
	exit := make(chan bool)
	
	go func(){
		for v:= range data{
			println(v)
		}

		println("receive over")
		exit <- true
	}()

	data <- 1
	data <- 2
	data <- 3

	time.Sleep(1*time.Second)
	close(data)

	println("send over")
	<-exit
}

func makeCakeAndSend1(cs chan string, count int) {
    for i := 1; i <= count; i++ {
        cakeName := "Strawberry Cake " + strconv.Itoa(i)
        cs <- cakeName //send a strawberry cake
	}   
	
	// 需要加上close(cs),才是正确关闭
}

func receiveCakeAndPack1(cs chan string) {
    for s := range cs {
        fmt.Println("Packing received cake: ", s)
    }
}

//实际上，有经验的Gopher一眼就能发现，示例代码1中的channel是没有正确关闭的，在for range语句的执行一直没有停止因为channel一直存在而没有被关闭，只不过随着time.Sleep()结束，main函数退出，所有的goroutine被关闭，该语句也被结束了而已
//正确的解决步骤：
//a)发送器一旦停止发送数据后立即关闭channel
//b)接收器一旦停止接收内容，终止程序
//c)移除time.Sleep语句

//在测试go channel时出现如下错误提示：fatal error: all goroutines are asleep - deadlock!
//出错信息的意思是在main goroutine线中，期待从其他goroutine线放入数据，但是其他goroutine线都已经执行完了(all goroutines are asleep)，那么就永远不会有数据放入管道。 
//所以，main goroutine线在等一个永远不会来的数据，那整个程序就永远等下去了。 这个时候就会报上述错误。验证
 
func TestCh_Err(){
	ch1 := make(chan int)
	for{
		select{
		case <-ch1: //fatal error: all goroutines are asleep - deadlock!
			{
				fmt.Println("ch1 pop one")
			}
		}
	}
}
//在上面代码中加一个goroutine并sleep，代码会等待该gorutine结束后再打印该错误
//说明在groutine都结束后，channel就没有开着的必要，需要关闭，否则试图读取就会报错
func TestCh_Err1(){
	ch1 := make(chan int)
	ch2 := make(chan int)
	go func(){
		fmt.Println("sleep 1")
		time.Sleep(5*time.Second)
		fmt.Println("sleep 2")
	}()

	for{
		select{
		case <-ch2:
			{

			}
		case <- ch1:
			{
				fmt.Println("ch1 pop one")
			}
		}
	}
}

func main(){
	//TestCh_Range()
	//TestCh_Range1()
	TestCh_Range2()
	//TestCh_Err()
	//TestCh_Err1()
}

//fjc
//函数里的每一步代码都可能是转到别的许多go程运行之后再回来的结果，别的go程肯能运行的也是这个函数
//只有在本go程之内，代码的执行顺序才是顺序的

//同一段代码启动的go程，不能判定先后执行顺序
//要假设groutine的生命周期是很长的，a和b两个goroutine,因为groutine的结束只能有自身决定，1.a在结束的同时启动b，
//2.别的goroutine在channel中收到a结束，之后再启动b 那么a和b在运行时就可能是存在生命周期交集的
//由于存在生命周期交集，那么并发的问题都可能有
//一个go程在运行一段代码后运行新的go程，那么新代码部分是并发的
//并行和并发除了效率上的不同，对程序员来说在编程时都是不能假定顺序的
//两个go程的声明周期可能存在交集，就要考虑并发的影响