package TestFunc
import (
	"fmt"
	"strconv"
)

type Animal interface{
	Speak()string
}

type Cat struct{}
func (c Cat)Speak()string{
	return "cat"
}

type Dog struct{}
func (d Dog)Speak()string{
	return "dog"
}

func Test(params interface{}){
	fmt.Println(params)
}

//fjc []interface代表可被迭代？不止！
func PrintAll(vals []interface{}) {
    for _, val := range vals {
        fmt.Println(val)
    }
}

func TestInterface(){
	animals := []Animal{Cat{},Dog{}}
	for _, animal := range animals {
		fmt.Println(animal.Speak())	
	}
	Test("string")
	Test(123)
	Test(true)

	names := []string{"stanley", "david", "oscar"}
	//cannot use names (type []string) as type []interface {} in argument to PrintAll
	//PrintAll(names)
	vals := make([]interface{}, len(names))
    PrintAll(vals)
    for i, v := range names {
        vals[i] = v
    }
    PrintAll(vals)
}

//===========================================================================
//以上代码中，定义了Animal为接口，而Cat和Dog两个结构体分别实现了接口中定义的方法。
//当interface{}作为函数形参时，可以接受不同类型的参数。

//1
type I interface {    
    Get() int
    Set(int)
}

//2
type S struct {
    Age int
}

func(s S) Get()int {
    return s.Age
}

func(s *S) Set(age int) {
    s.Age = age
}

//3
func f(i I){
    i.Set(10)
    //fmt.Println(i.Get())
}

func TestInterface1() {
    s := S{} 
	f(&s)  //4

	//这段代码在 #1 定义了 interface I，在 #2 用 struct S 实现了 I 定义的两个方法，
	//接着在 #3 定义了一个函数 f 参数类型是 I，S 实现了 I 的两个方法就说 S 是 I 的实现者，
	//执行 f(&s) 就完了一次 interface 类型的使用。
	//
	//interface 的重要用途就体现在函数 f 的参数中，如果有多种类型实现了某个 interface，
	//这些类型的值都可以直接使用 interface 的变量存储。

	fmt.Println("------------------------");
	s1 := S{}
	var i I //声明 i 
	i = &s1 //赋值 s 到 i
	fmt.Println(i.Get())

	//不难看出 interface 的变量中存储的是实现了 interface 的类型的对象值，这种能力是 duck typing。
	//在使用 interface 时不需要显式在 struct 上声明要实现哪个 interface ，只需要实现对应 interface 中的方法即可，
	//go 会自动进行 interface 的检查，并在运行时执行从其他类型到 interface 的自动转换，即使实现了多个 interface，
	//go 也会在使用对应 interface 时实现自动转换，这就是 interface 的魔力所在。

}
   
//golang interface的使用和实现（翻译整理）

type Stringer interface{
	String()string
}

//any值有个静态的类型interface{}，意味着不保证有任何方法：可以包含任何类型。
func ToString(any interface{})string{
	//在if语句中的 v, ok = any.(Stringer); 赋值语句询问是否可以将any变量转换为Stringer类型（有String方法）。
	//（这里any查看any.tab->type 是否 是Stringer 类型，如果是，返回any.data）
	//如果是，该语句的正文将调用该方法来获取要返回的字符串。
	//否则，在放弃前，使用switch语句检查是否是其他类型可以转换为字符串来返回。
	//if v,ok:= any.(Stringer);ok {
	//	return v.String()	
	//}
	switch v:= any.(type) {
	case Stringer:
		return "type:Stringer"
	case int:
		return strconv.Itoa(v)	
	case float64:
		//return strconv.Ftoa(v,'g',-1) //undefined: strconv.Ftoa
		return strconv.FormatFloat(v,'f',5,64)
	case float32:
		//cannot use v (type float32) as type float64 in argument to strconv.FormatFloat
		//return strconv.FormatFloat(v,'f',5,32)
		return "type:float32"
	}
	return "???"
}

type Binary uint64
func (i Binary)String()string{
	//return strconv.Uitob64(i.Get(),2)
	return "==uint64====" 
}
func (i Binary)Get()uint64{
	return uint64(i)
}
//Binary类型的值可以传递给ToString，ToString将会使用String方法格式化，即使程序从未说明Binary将会实现Stringer。
//没必要那样做，因为：运行时可以看到Binary有String方法，因此它实现了Stringer，即使Binary的作者从未听说过Stringer。
//这些例子展示了，即使在编译时检查了所有的隐式转换，显示的interface-to-interface转换也可以在运行时查询方法集。

func TestInterface2(){
	bb := Binary(200);
	fmt.Println("testInterface2 binary:",bb)

	fmt.Println("testInterface2 binary tostring:",ToString(bb))
	fmt.Println("testInterface2 int tostring:",ToString(200))
	fmt.Println("testInterface2 float tostring:",ToString(200.12))
	fmt.Println("testInterface2 float tostring:",ToString(float32(200.56)))
}

