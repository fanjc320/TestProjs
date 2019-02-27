package main
import (
	"fmt"
	"runtime"
	"time"
)

func Test(rchan chan int){
	var dat int
	t := time.Tick(time.Second)
	for{
		select{
		case d:= <-rchan:
			limitChan <- true
			go A()
		case <-t:
			showGoNum()
		}
	}
}

func A(){
	defer func(){
		<-limitChan
	}()
	time.Sleep(time.Millisecond*100)
}

func showGoNum(){
	fmt.Printf("====numGo:===%d\n",runtime.NumGoroutine())
}

var (
	readChan = make(chan int)
	limitChan = make(chan bool,50)
)

func init(){
	go Test(readChan)
}

func main() {

	go func(){
		for {
			readChan <- 1
		}
	}()

	var input string
	fmt.Scanln(&input)
}
