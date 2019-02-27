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

func TestCh_Range1() {
	cs := make(chan string)
    go receiveCakeAndPack1(cs)
	go makeCakeAndSend1(cs, 10)
	fmt.Println("===============")
	go makeCakeAndSend1(cs, 5)

    //sleep for a while so that the program doesn’t exit immediately
    time.Sleep(3 * 1e9)
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
	//TestCh_Err()
	TestCh_Err1()
}