package channel

import(
    "fmt"
)

func worker(start chan bool,index int){
    <- start // 从start中取出数据后，调用20行的case语句 //接收并将其丢弃
    fmt.Println("This is Worker:",index)
}

func TestGoroutine(){
    start := make(chan bool)
    for i:=1;i<=10;i++{
        go worker(start,i)
    }
}
