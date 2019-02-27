package main
import (
	"fmt"
	"runtime"
	"time"
)


func A(qid int,rchan chan int){
	var dat int
	t := time.Tick(time.Second)
	for{
		select{
		case d:= <-rchan:
			limitChan <- true
			dat += d
			go showNum(qid,dat)
		case <-t:
			showGoNum(qid)
		}
	}
}

func showNum(qid,i int){
	defer func(){
		<-limitChan
	}()
	time.Sleep(time.Millisecond*100)
}

func showGoNum(qid int){
	fmt.Printf("%d====numGo:===%d\n",qid,runtime.NumGoroutine())
}

var (
	chanNum = 3 
	readChan = make(chan int)
	limitChan = make(chan bool,50)
)

func init(){
	for i:=0;i<chanNum;i++{
		go A(i,readChan)
	}
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
