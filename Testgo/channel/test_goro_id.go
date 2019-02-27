package main
import (
	"fmt"
	"runtime"
	"strconv"
	"strings"
	// "sync"
	"time"
)

var dic_ids map[int32]int32
var dic_numb [50] int32
var slice1 []int32 = make([]int32,50)
var numbers []int

func GoID() int {
	var buf [64]byte
	n := runtime.Stack(buf[:], false)
	idField := strings.Fields(strings.TrimPrefix(string(buf[:n]), "goroutine "))[0]
	id, err := strconv.Atoi(idField)
	if err != nil {
		panic(fmt.Sprintf("cannot get goroutine id: %v", err))
	}
	return id
}

func A(){
	if(len(numbers)>=50){
		print("\n too many numbers of groutine for A",)
		return
	}
	id := GoID()
	// print("numbers:",numbers)
	// slice1 = append(slice1,id)
	numbers= append(numbers,id)
	print("after numbers:",numbers)
	return
}

func B(qid int,rchan chan int){
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
	chanNum = 1 
	readChan = make(chan int)
	limitChan = make(chan bool,50)
)

func init(){
	for i:=0;i<chanNum;i++{
		go B(i,readChan)
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


	// fmt.Println("main", GoID())
	// var wg sync.WaitGroup
	// for i := 0; i < 60; i++ {
	// 	// i := i
	// 	wg.Add(1)
	// 	go A()
	// 	/*
	// 	go func() {
	// 		defer wg.Done()
	// 		fmt.Println(i, GoID())
	// 	}()
	// 	*/
	// }
	// wg.Wait()
}
