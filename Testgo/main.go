package main
import "fmt"
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


	//channel.TestGoroutine()

	//channel.TestCh0()

//	channel.TestCh1(0)
//	fmt.Println("----------------------------")
//	channel.TestCh1(3)

	channel.TestCh_Select()


}