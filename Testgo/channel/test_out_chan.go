package main
import (
    "fmt"
    "os"
    "os/signal"
    "sync"
    "syscall"
    "time"
)
func consumer(stop <-chan bool) {
    for {
        select {
        case b_stop := <-stop:
            fmt.Println("exit sub goroutine ",b_stop)
            return
        case <-stop:
            fmt.Println("exit sub goroutine")
            return
        default:
            fmt.Println("running...")
            time.Sleep(500 * time.Millisecond)
        }
    }
}
func main() {
        stop := make(chan bool)
        var wg sync.WaitGroup
        // Spawn example consumers
        for i := 0; i < 3; i++ {
            wg.Add(1)
            go func(stop <-chan bool) {
                defer wg.Done()
                consumer(stop)
            }(stop)
        }
        waitForSignal()
        close(stop)//回想stop管道发送消息
        fmt.Println("stopping all jobs!")

        var input string
        fmt.Scanln(&input)

        wg.Wait()
        fmt.Println("=================stopping all jobs!")
}
func waitForSignal() {
    sigs := make(chan os.Signal)
    signal.Notify(sigs, os.Interrupt)
    signal.Notify(sigs, syscall.SIGTERM)
    <-sigs
}
 