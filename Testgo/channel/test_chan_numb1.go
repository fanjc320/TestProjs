package main
import (
	"fmt"
	"runtime"
)

var limitChan = make(chan bool,50)
func Test(){
	for i:=0;i<1000;i++{
		limitChan <- true
		go A()
	}
}

func A(){
	defer func(){
		<-limitChan
	}()
	showGoNum()
}

func showGoNum(){
	fmt.Printf("====numGo:===%d\n",runtime.NumGoroutine())
}

func init(){
	go Test()
}

func main() {

	var input string
	fmt.Scanln(&input)
}
