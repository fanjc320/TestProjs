package main

import (
    "fmt"
    "time"
)

func main() {
    running := true
    f := func() {
        for running {
            fmt.Println("sub proc running...")
            time.Sleep(1 * time.Second)
        }
        fmt.Println("sub proc exit")
    }
    go f()
    go f()
    go f()
    time.Sleep(2 * time.Second)
    running = false
    time.Sleep(3 * time.Second)
    fmt.Println("main proc exit")
}

// 全局变量的优势是简单方便，不需要过多繁杂的操作，通过一个变量就可以控制所有子goroutine的开始和结束；缺点是功能有限，由于架构所致，该全局变量只能是多读一写，否则会出现数据同步问题，当然也可以通过给全局变量加锁来解决这个问题，但那就增加了复杂度，另外这种方式不适合用于子goroutine间的通信，因为全局变量可以传递的信息很小；还有就是主进程无法等待所有子goroutine退出，因为这种方式只能是单向通知，所以这种方法只适用于非常简单的逻辑且并发量不太大的场景，一旦逻辑稍微复杂一点，这种方法就有点捉襟见肘。
// --------------------- 
// 作者：panjf2000 
// 来源：CSDN 
// 原文：https://blog.csdn.net/u013029603/article/details/81232395 
// 版权声明：本文为博主原创文章，转载请附上博文链接！