package channel

import(
	"fmt"
	"time"
	"os"
	"strconv"
)

func launch(){
	fmt.Println("nuclear launch detected")
}

func commencingCountDown(canLunch chan int){
	c := time.Tick(1*time.Second)
	for countDown := 20;countDown>0;countDown--{
		fmt.Println(countDown)
		<- c //阻塞一秒钟,fjc
	}
	canLunch <- -1
}

func isAbort(abort chan int){
	os.Stdin.Read(make([]byte,1))
	fmt.Println("isAbort stdin read a int")
	abort <- -1
}

//select关键字用于多个channel的结合，这些channel会通过类似于are-you-ready polling的机制来工作。select中会有case代码块，用于发送或接收数据——不论通过<-操作符指定的发送还是接收操作准备好时，channel也就准备好了。在select中也可以有一个default代码块，其一直是准备好的。那么，在select中，哪一个代码块被执行的算法大致如下：
//
//检查每个case代码块
//如果任意一个case代码块准备好发送或接收，执行对应内容
//如果多余一个case代码块准备好发送或接收，随机选取一个并执行对应内容
//如果任何一个case代码块都没有准备好，等待
//如果有default代码块，并且没有任何case代码块准备好，执行default代码块对应内容

func TestCh_Select(){
	fmt.Println("Commencing countdown")	

	abort := make(chan int)
	canLunch := make(chan int)
	go isAbort(abort)
	go commencingCountDown(canLunch)
	//只要执行了一个case或default，就不会阻塞，否则会阻塞
	select{
	case <- canLunch://会阻塞
	case <- abort:
		fmt.Println("Launch aborted!")
		return
	//default://会导致不阻塞
		//fmt.Println("select default!!!!!!!!") 
	}
	launch()
}

//===========================================
func makeCakeAndSend(cs chan string, flavor string, count int) {
    for i := 1; i <= count; i++ {
        cakeName := flavor + " Cake " + strconv.Itoa(i)
        cs <- cakeName //send a strawberry cake
    }   
    close(cs)
}

//们这里使用的多个返回值case cakeName, strbry_ok := <-strbry_cs，第二个返回值是一个bool类型，当其为false时说明channel被关闭了。
//如果是true，说明有一个值被成功传递了。我们使用这个值来判断是否应该停止等待
func receiveCakeAndPack(strbry_cs chan string, choco_cs chan string) {
    strbry_closed, choco_closed := false, false

    for {
        //if both channels are closed then we can stop
        if (strbry_closed && choco_closed) { return }
        fmt.Println("Waiting for a new cake ...")
        select {
        case cakeName, strbry_ok := <-strbry_cs:
            if (!strbry_ok) {
                strbry_closed = true
                fmt.Println(" ... Strawberry channel closed!") //实际上！strbry_ok不一定是关闭，只是处于阻塞状态而已
            } else {
                fmt.Println("Received from Strawberry channel.  Now packing", cakeName)
            }   
        case cakeName, choco_ok := <-choco_cs:
            if (!choco_ok) {
                choco_closed = true
                fmt.Println(" ... Chocolate channel closed!")
            } else {
                fmt.Println("Received from Chocolate channel.  Now packing", cakeName)
            }   
        }   
    }   
}

//在下面的程序中，我们扩展蛋糕制作工厂来模拟多于一种口味的蛋糕生产的情况——现在有草莓和巧克力两种口味！但是装箱机制还是同以前一样的。由于蛋糕来自不同的channel，而装箱器不知道确切的何时会有何种蛋糕放置到某个或多个channel上，这就可以用select语句来处理所有这些情况——一旦某一个channel准备好接收蛋糕/数据，select就会完成该对应的代码块内容
//注意，我们这里使用的多个返回值case cakeName, strbry_ok := <-strbry_cs，第二个返回值是一个bool类型，当其为false时说明channel被关闭了。如果是true，说明有一个值被成功传递了。我们使用这个值来判断是否应该停止等待

func TestCh_Select1() {
    strbry_cs := make(chan string)
    choco_cs := make(chan string)

    //two cake makers
    go makeCakeAndSend(choco_cs, "Chocolate", 3)  //make 3 chocolate cakes and send
    go makeCakeAndSend(strbry_cs, "Strawberry", 3)  //make 3 strawberry cakes and send

    //one cake receiver and packer
    go receiveCakeAndPack(strbry_cs, choco_cs)  //pack all cakes received on these cake channels

    //sleep for a while so that the program doesn’t exit immediately
    //time.Sleep(2 * 1e9)
}

