package TestFunc

import(
	"fmt"
)

//==================================================

type TestI interface{
	Tester()
}

type MyFloat float64

func (m MyFloat)Tester(){
	fmt.Println(m)
}

func describe(t TestI){
	fmt.Printf("Interface 类型 %T,值：%v \n",t,t)
}

func TestInterface_TV(){
	var t TestI
	f := MyFloat(89.7)
	t = f
	describe(t)
	describe(f)
	t.Tester()
}

//================================================================
func assert(i interface{}){
	//s := i.(int) //断言性质，如果i不是int会panic
	//fmt.Println(s)
	v,ok := i.(int) //如果i不是int,程序不会panic
	fmt.Println(v,ok)
}

func findType(i interface{}){
	switch i.(type) {
	case string:
		fmt.Printf("String :%s\n",i.(string))	
	case int:
		fmt.Printf("Int :%d\n",i.(int))	
	default:
		fmt.Printf("Unknown type\n")	
	}
}

func TestInterface_Type(){
	var s interface {} = 55
	assert(s)
	assert(66)
	assert("test")
	
	findType("nice")
	findType(77)
	findType(77.77)
}

//===========================================

type Describer interface{
	Describe()
}

type Person struct{
	name string
	age int
}

func (p Person)Describe(){
	fmt.Printf("%s is %d years old",p.name,p.age)
}

func findType_Compare(i interface{}){
	switch v:=i.(type) {
	case Describer:
		v.Describe()	
	case string:
		fmt.Printf("string type\n")
	default:
		fmt.Printf("unknown type\n")
	}
}

func TestInterface_compare(){
	findType_Compare("fjc")
	p := Person{
		name: "fjc x",
		age:30,
	}
	findType_Compare(p)
}

