//golang中有2种方式同步程序，一种使用channel，另一种使用sync.WaitGroup
// 。最近在使用golang写一个比较简单的功能 ---- host1主机需要先在本机起一个TCP监听，起来后给host2主机发送指令，让其主动给host1主机监听的端口进行连接。最终使用了sync.WaitGroup实现了该功能。本篇就结合一些示例来看下两者的使用。
package main

import(
	"fmt"
	"time"
	"sync"
	"net/http"
	"io/ioutil"
	"log"
)

func TestForRange(){
	messages := make(chan int)
	//done := make(chan bool)
	go func(){
		time.Sleep(time.Second*3)
		messages <- 1
		println("one is done!")
		//done <- true
	}()
	go func(){
		time.Sleep(time.Second*2)
		messages <- 2
		//done <- true
	}()
	go func(){
		time.Sleep(time.Second*1)
		messages<-3
		//done <- true
	}()
	/*
	//a和b执行顺序不定，所以假如b先执行完毕，a不一定有机会执行完毕，所以输出可能不全,例如只输出3，2
	go func(){//a
		for i:= range messages{
			fmt.Println(i)
		}
	}()
	for i:=0;i<3;i++{//b
		<-done//会阻塞到3个go程执行完毕,发送给done
	}
	*/

	for i := range messages{//在取数据的时候，由于是同步的channel，必须要有对应的groutine，否则报错
		fmt.Println(i)
	}
}

func TestWaitGroup(){
	 messages := make(chan int)
    var wg sync.WaitGroup
    // you can also add these one at
    // a time if you need to
    wg.Add(3)//假如这里的个数大于wg.Done的go程个数，会deadlock，小于的话，则较晚的goroutine没有被等待
    go func() {
        defer wg.Done()
        time.Sleep(time.Second * 3)
        messages <- 1
    }()
    go func() {
        defer wg.Done()
        time.Sleep(time.Second * 2)
        messages <- 2
    }()
    go func() {
        defer wg.Done()// 假如注释掉一个，会deadlock
        time.Sleep(time.Second * 1)
        messages <- 3
    }()
    go func() {
        for i := range messages {
            fmt.Println(i)
        }
    }()
	wg.Wait()
	println("TestWaitGroup done!!!!")
}

//多线程采集
func TestMulti(){
	urls := []string{
		"http://api.douban.com/v2/book/isbn/9787218087351",
        "http://ip.taobao.com/service/getIpInfo.php?ip=202.101.172.35",
        "https://jsonplaceholder.typicode.com/todos/1",
	}
	jsonResponses := make(chan string)
	var wg sync.WaitGroup
	wg.Add(len(urls))
	for a, url := range urls{
		println("aaaaa:",a)
		go func(url string){
			defer wg.Done()
			res,err := http.Get(url)
			if err !=nil{
				println("------000-----")
				log.Fatal(err)
			}else{
				defer res.Body.Close()
				body,err := ioutil.ReadAll(res.Body)
				if err != nil{
					println("------111-----")
					log.Fatal(err)
				}else{
					println("------222-----")
					jsonResponses <- string(body)
				}
			}
		}(url)
	}
	/*//这样做的结果是，以上go程的channel塞入的数据无法被获取，因为下面的go程和上面的groutine没法时间上没有交集
	wg.Wait()
	*/
	wg.Add(1)//会强制主程等待所有jsonResponses的发送和接收,加入不等待这个go程，有部分数据还没打印出来就结束程序了
	go func(){//可以在这个go程里等待上面的go程的运行结束,通过waitgroup或者channel
		defer wg.Done()
		for response := range jsonResponses{//在本go程中阻塞
			fmt.Println(response)
		}
	}()
	wg.Wait()//要么在这里等待所有go程工作完毕，要么在上面的go程里等待上上面的go程
	/*
	for response := range jsonResponses{//会一直阻塞,因为jsonResponses没关闭
		fmt.Println(response)
	}*/
	println("=========end=========")
}

func main(){
	//TestForRange()
	//TestWaitGroup()
	TestMulti()
}

//在启动go程前的代码，一定在go程的代码前被执行
//主城在启动go程后到阻塞的channel之间的代码，和go程内开始和阻塞的代码的执行顺序就不定了