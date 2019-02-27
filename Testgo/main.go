package main
import (
	"fmt"
	"time"
)
//import "./container"
//import "./TestFunc"
import "./channel"

func min(s ...int)int {
	if len(s) == 0 {
		return 0
	}
	min := s[0]
	for _, value := range s{
		if value < min {
			min = value
		}
	}
		
	return min
}

func main(){
	fmt.Println("----------------------------")
	//x := min(1,3,2,0,5)
	//fmt.Println("the minimum is:%d\n",x)

	//container.TestMap()
	//container.TestRange()
	//container.TestHandle()

	//----------------
	//TestFunc.TestFunc()
	//TestFunc.TestInterface()
	//TestFunc.TestInterface1()
	//TestFunc.TestInterface2()
	//TestFunc.TestInterface_option()

	//TestFunc.TestInterface_new()
	//TestFunc.TestInterface_Salary()
	//TestFunc.TestInterface_TV()
	//TestFunc.TestInterface_Type()
	//TestFunc.TestInterface_compare()



	//channel.TestCh0()

//	channel.TestCh1(0)
//	fmt.Println("----------------------------")
//	channel.TestCh1(3)

	//channel.TestCh_Block()
	//channel.TestCh_Block1()
	//channel.TestCh_Sync()
	//channel.TestCh_OneDirection()

	//channel.TestGoroutine()
	//channel.TestGoroutine_1()

	//channel.TestCh_Range1()
	channel.TestCh_Select1()

	//防止groutine没有运行完，程序过快退出
	for index := 0; index < 50; index++ {
		time.Sleep(1000*time.Millisecond)
		fmt.Printf("-")	
	}

	//每隔秒运行一次
	/*
	for range time.Tick(1000*time.Millisecond){
		fmt.Printf("=")
	}*/
	//因为time.Tick()返回的是一个channel,每隔指定的时间会有数据从channel中出来，
	//for range不仅能遍历map,slice,array还能取出channel中数据，range前面可以不用变量接收，所以可以简写成上面的形式。
}

