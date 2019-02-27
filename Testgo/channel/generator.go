package main
import(
	"fmt"
	"time"
)

const exetime(
	timeA = 100,
	timeB = 100
)

func xrange() chan int{
	var ch chan int = make(chan int)

	go func(){
		for i:=0;;i++{
			time.Sleep(timeA*time.Millisecond)
			fmt.Println("-before i:%d",i)//总是在flag_A前执行
			ch<-i  //会阻塞
			fmt.Println("------------after i:%d",i)//可能在flag_A前执行，执行顺序不定
		}
	}()
	return ch
}

func main(){
	generator := xrange()
	for i:=0;i<50;i++{
		time.Sleep(timeB*time.Millisecond)
		fmt.Println("-----:%d",<-generator)//会阻塞 flag_A
	}
}