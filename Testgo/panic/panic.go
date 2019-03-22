package main
import(
	"fmt"
)

//var c = make(chan int,10)

func main(){
	//var c = make(chan int,1)
	var c = make(chan int)//会deadlock
	c <-1
	close(c)
	v,ok:=<-c
	fmt.Println(v,ok)
	v,ok=<-c
	fmt.Println(v,ok)
	<-c
}

//close函数必须由Sender一方进行调用，当关闭一个channel后，Receiver可以继续将未读完的element从channel中读出来，当最后一个element被读出后，再进行读取操作会导致panic