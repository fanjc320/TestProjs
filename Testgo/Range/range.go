package main

import "fmt"
//这里的 value是副本,且是同一个变量,被赋不同的值
func Base(){
	slice := []int{0,1,2,3}
	myMap := make(map[int]*int)

	for index,value := range slice{
		myMap[index] = &value
		println("&value:%v",&value)
	}
	fmt.Println("====new map=====")
	prtMap(myMap)
}

func prtMap(myMap map[int]*int){
	for key,value := range myMap{
		fmt.Printf("map[%v]=%v\n",key,*value)
	}
}

// 但是由输出可以知道，映射的值都相同且都是3。其实可以猜测映射的值都是同一个地址，遍历到切片的最后一个元素3时，将3写入了该地址，所以导致映射所有值都相同。其实真实原因也是如此，因为for range创建了每个元素的副本，而不是直接返回每个元素的引用，如果使用该值变量的地址作为指向每个元素的指针，就会导致错误，在迭代时，返回的变量是一个迭代过程中根据切片依次赋值的新变量，所以值的地址总是相同的，导致结果不如预期。


//range表达式构建
//先来看看下面这段代码的输出是什么？这段代码会无限循环的执行下去吗？

func modifySlice() {
    v := []int{1, 2, 3, 4}
    //for i,item := range v {
    for i := range v {
        v = append(v, i)
        //fmt.Printf("Modify Slice: i:%d item:%d value:%v\n",i,item, v)
        fmt.Printf("Modify Slice: i:%d value:%v\n",i,v)
    }
}

// 可以看到每次循环在map中插入新的内容后，map的长度确实发生了变化，但是循环只执行了三次，正好是执行range前map的长度。说明range在执行之初就构建好了range表达式的内容了，虽然后面map的内容增加了，但是并不会影响初始构建的结果。官方文档对于range表达式的构建描述是这样的：
// The range expression x is evaluated once before beginning the loop, with one exception: if at most one iteration variable is present and len(x) is constant, the range expression is not evaluated.
// 就是说range表达式在开始执行循环之前就已经构建了，但是有一个例外就是：如果最多只有一个迭代变量，且len(x)表达的是值是一个常量的时候range表达式不会构建。
// 那什么时候len(x)是一个常量呢？按照通常的理解，len(string), len(slice), len(array)…的返回应该都是常量啊？事实上不是这样的，这其实是由数据结构的特性决定的。因为相比较于其他语言，对于这一类容器数据结构，在Go语言中不仅有长度属性可以通过内建函数len()获取，还有一个可以通过内建函数cap()获取的容量属性，尤其是slice，map这一类可变长的数据结构。所以对于常量的定义，Go官方文档Length and capacity有详细的说明。
// 如果到这里，你以为你已经理解了range的构建，并且一眼就能看出一个for-range循环的迭代方式和执行情况。前面可能就已经有一个大坑为你准备好了。这时候官方文档里面下面这样一段话可能就被你忽略了，让我先贴出来：
// The iteration order over maps is not specified and is not guaranteed to be the same from one iteration to the next. If a map entry that has not yet been reached is removed during iteration, the corresponding iteration value will not be produced. If a map entry is created during iteration, that entry may be produced during the iteration or may be skipped. The choice may vary for each entry created and from one iteration to the next. If the map is nil, the number of iterations is 0.
// 用中国话解释下，首先对于map的迭代来说，map中内容的迭代顺序没有指定，也不保证，简单的说就是迭代map的时候将以随机的顺序返回里面的内容。这个好理解，也就是说如果你想按顺序迭代一些东西，map就不要指望了，换其他数据结构吧。
// 然后就进入高潮部分了，如果一个map的key在还没有被迭代到的时候就被delete掉了，那么它所对应的迭代值就不会被产生了。然后对于在迭代过程中新增加的key，则它可能会被迭代到也可能不会。如何选择会根据key增加的时机以及从上一次到下一次的迭代而不同。你可能会想，What？你TM在逗我么，说好的提前构建的呢…但是很不幸，事实就是这样，将前面的示例代码改成使用map我执行了几次结果都不一样。所以这种坑还是绕过为好。至于为什么会这样，容我有空再研究研究，下次重开一篇文章介绍。

func modifyMap() {
    data := map[string]string{"a": "A", "b": "B", "c": "C"}
    for k, v := range data {
        data[v] = k
        fmt.Println("modify Mapping", data)
    }
}
 
// range string
// 使用range迭代字符串时，需要主要的是range迭代的是Unicode而不是字节。返回的两个值，第一个是被迭代的字符的UTF-8编码的第一个字节在字符串中的索引，第二个值的为对应的字符且类型为rune(实际就是表示unicode值的整形数据）。
// 总结下来就是使用range迭代string时，需要注意下面两点：
// 迭代的是Unicode不是字节，第一个返回值是UTF-8编码第一个字节的索引，所以索引值可能并不是连续的。
// 第二个返回值的类型为rune，不是string类型的，如果要使用该值需要格式化。
// 看下面代码：
//这段代码的输出如下，这里使用的string是只占用一个字节的字符的字符串，所以返回的第一个索引是连续的，可以看到第二个值都是整型数字。
func rangeString() {
    datas := "aAbB"

    for k, d := range datas {
        fmt.Printf("k_addr:%p, k_value:%v\nd_addr:%p, d_value:%v\n----\n", &k, k, &d, d)
    }
}

// range表达式是指针
// 前面说过range可以迭代的数据类型包括array，slice，map，string和channel。在这些数据类型里面只有array类型能以指针的形式出现在range表达式中。
// 具体参考下面的代码：

func rangePointer() {
    //compile error: cannot range over datas (type *string)
    //d := "aAbBcCdD"
    d := [5]int{1, 2, 3, 4, 5} //range successfully
    //d := []int{1, 2, 3, 4, 5} //compile error: cannot range over datas (type *[]int)
    //d := make(map[string]int) //compile error: cannot range over datas (type *map[string]int)
    datas := &d

    for k, d := range datas {
        fmt.Printf("k_addr:%p, k_value:%v\nd_addr:%p, d_value:%v\n----\n", &k, k, &d, d)
    }
} 

func main(){
	//Base()
	//modifySlice()
	//modifyMap()
	//rangeString()
	rangePointer()
}