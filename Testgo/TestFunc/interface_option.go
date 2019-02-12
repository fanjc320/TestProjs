package TestFunc
import(
    "fmt"
)

type IPeople interface{
    GetName() string
}

type IPeople2 interface{
    GetName() string
    GetAge() int
}

type person struct{
    name string
    age int
}

func (p* person)GetName() string{
    return p.name
}

type person2 struct{
    name string
    age int
}

func (p* person2)GetName() string{
    return p.name
}

func (p* person2)GetAge() int{
    return p.age
}

func isTypeOf(){

}

func TestInterface_option(){

    var pa IPeople = &person{"jack_IPeople",28}
    var pb IPeople = &person2{"jack_IPeople2",28}
    // cannot use person literal (type *person) as type IPeople2 in assignment:
	//*person does not implement IPeople2 (missing GetAge method)
    // var pc IPeople2 = &person{"mary_a",23}
    var pd IPeople2 = &person2{"mary_b",23}

    var v = func(param interface{}){
        if p,ok := param.(IPeople);ok{
            fmt.Println(p.GetName()," satisfy IPeople!")//pp接口指向的对象实例是否是*person类型,*不能忘
        }
        if p,ok := param.(IPeople2);ok{
            fmt.Println(p.GetName()," satisfy IPeople22222222!")//pp接口指向的对象实例是否是*person类型,*不能忘
        }
    }

    v(pa)
    v(pb)
    v(pd)

    fmt.Println("======================================================")

    var ppp IPeople = &person{"alen",30}
    if pp2,ok := ppp.(*person);ok{
        fmt.Println(pp2.GetName(),"person statisfy IPeople!")
    }

    switch ppp.(type) {
    case IPeople:
        fmt.Println("IPeople")
    case IPeople2:
        fmt.Println("IPeople2")
    default:
        fmt.Println("can't found")
    }

    var ii interface{} = 43//默认int类型
    switch ii.(type){
    case int:
        fmt.Println("int")
    default:
        fmt.Println("can't found")
    }
}