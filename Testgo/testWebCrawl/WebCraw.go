package main

import(
    "fmt"
    "sync"
    "time"
    "runtime"
)

type Fetcher interface{
    Fetch(url string)(body string,urls []string,err error)
}

// 有点递归的感觉，但是是并发的，顺序不定，更像是树状的，理论每个分支可以有n多分支(即n个groutine)，但分支的终点只有几个return，
//这里的end<-true只能在每个groutine的执行终点调用，但是最后一个groutine的终点是不知道的
//也不好在main中用waitgroup等待，因为groutine的个数不定
//由于goroutine的并发，后产生的groutine可能先执行完毕
func Crawl(url string,depth int,fetcher Fetcher,crawled Crawled,out chan string,end chan bool){
    //todo :并行抓取url
    //todo: 不重复抓取页面
    if depth <=0{
        println("depth:",depth,"depth<=0 ulr:",url)
        end<-true
        time.Sleep(100*time.Millisecond)
        return
    }

    crawled.mux.Lock()
    if _,ok := crawled.crawled[url];ok{
        crawled.mux.Unlock()
        println("depth:",depth,"crawled ulr ",url)
        time.Sleep(100*time.Millisecond)
        end<-true
        return
    }

    crawled.crawled[url]=1
    crawled.mux.Unlock()

    _,urls,err := fetcher.Fetch(url)
    if err != nil{
        fmt.Println(err)
        end <-true
        println("depth:",depth,"no url:",url)
        time.Sleep(100*time.Millisecond)
        runtime.Gosched() 
        return
    }

    out <- url
    //fmt.Println("found:",url,body)
    for _,u := range urls{
        go Crawl(u,depth-1,fetcher,crawled,out,end)
    }
    time.Sleep(100*time.Millisecond)
    for i:=0;i<len(urls);i++{
        <-end
        //test:= <-end
        println("depth:",depth,"<-end-----------")
    }
    //println("end<-true")
    //end<-true
    //end<-false
    return
}

type Crawled struct{
    crawled map[string]int
    mux sync.Mutex
}

func main(){
    crawled := Crawled{make(map[string]int),sync.Mutex{}}
    out := make(chan string)
    end := make(chan bool)
    go Crawl("http://golang.org/",4,fetcher,crawled,out,end)

    for{
        select{
        case url := <-out:
            fmt.Println("found:",url)
        case <- end:
            fmt.Println("#=============")//会执行多次，并没有遍历所有url，这个程序是不对的
            //return //去掉return deadLock!!!!!,换成break也不行
            //break
        }
    }
    print("~~~~~~~~~~~~  END ~~~~~~~~~~~~~")
}

type fakeFetcher map[string]*fakeResult

type fakeResult struct{
    body string
    urls []string
}

func (f fakeFetcher)Fetch(url string)(string,[]string,error){
    if res,ok := f[url];ok{
        return res.body,res.urls,nil
    }
    return "",nil,fmt.Errorf("not found:%s",url)
}

//fetcher 是填充后的fakeFetcher
var fetcher = fakeFetcher{
    "http://golang.org/":&fakeResult{
        "The Go Programmming Language",
        []string{
            "http://golang.org/pkg/",
            "http://golang.org/cmd/",
        },
    },
    "http://golang.org/pkg/": &fakeResult{
        "Packages",
        []string{
            "http://golang.org/",
            "http://golang.org/cmd/",
            "http://golang.org/pkg/fmt/",
            "http://golang.org/pkg/os/",
        },
    },
    "http://golang.org/pkg/fmt/": &fakeResult{
        "Package fmt",
        []string{
            "http://golang.org/",
            "http://golang.org/pkg/",
        },
    },
    "http://golang.org/pkg/os/": &fakeResult{
        "Package os",
        []string{
            "http://golang.org/",
            "http://golang.org/pkg/",
        },
    },
}