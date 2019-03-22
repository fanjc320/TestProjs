package main

import(
	"flag"
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"sync"
	"time"
)

//一个已经被关闭的channel不会阻塞，已经被关闭的channel会实时返回
//goroutine退出，关闭done来进行广播
var done = make(chan struct{})

////判断done是否关闭，即是否执行goroutine退出
func cancelled()bool{
	select{
	case<-done:
		return true
	default:
		return false
	}
}

//获取目录dir下的文件大小
func walkDir(dir string,wg *sync.WaitGroup,fileSizes chan<- int64){
	defer wg.Done()
	if cancelled(){
		return
	}
	for _,entry := range dirents(dir){
		if entry.IsDir(){
			wg.Add(1)
			subDir := filepath.Join(dir,entry.Name())
			println("dirname:",entry.Name())
			go walkDir(subDir,wg,fileSizes)
		}else{
			println("filename:",entry.Name())
			fileSizes<-entry.Size()
		}
	}
}

//sema is a counting semaphore for limiting concurrency in dirents
var sema = make(chan struct{},20)

//读取目录dir下的文件信息
func dirents(dir string)[]os.FileInfo{
	select{
	case sema<-struct{}{}://acquire token
	case <-done:
		return nil//cancelled
	}
	defer func(){<-sema}()//release token
	entries,err := ioutil.ReadDir(dir)
	if err!=nil{
		fmt.Fprintf(os.Stderr,"du:%v\n",err)
		return nil
	}
	return entries
}

////输出文件数量的大小
func printDiskUsage(nfiles,nbytes int64){
	fmt.Printf("%d files %.1f GB\n",nfiles,float64(nbytes)/1e9)
}

//提供-v 参数会显示程序进度信息
var verbose = flag.Bool("v",false,"show verbose progress messages")

func Start(){
	flag.Parse()
	roots:=flag.Args()//需要统计的目录
	if len(roots)==0{
		roots = []string{"."}
	}
	fileSizes := make(chan int64,5)
	var wg sync.WaitGroup
	for _,root := range roots{
		wg.Add(1)
		go walkDir(root,&wg,fileSizes)
	}
	go func(){
		os.Stdin.Read(make([]byte,1))////从标准输入读取一个字符，执行goroutine退出
		close(done)
	}()
	go func(){
		wg.Wait()////等待goroutine结束
		close(fileSizes)
	}()
	var tick <- chan time.Time
	if *verbose{
		tick = time.Tick(100*time.Millisecond)//输出时间间隔
	}
	var nfiles,nbytes int64
loop:
	for{
		select{
		case<-done:
			 //to allow existing goroutines to finish
			 for range fileSizes{ //fileSizes关闭时，for循环会自动结束
				//Do nothing
			 }
			 return
		case size,ok:=<-fileSizes:
			if !ok{
				break loop
			}
			nfiles++
			nbytes+=size
		case <-tick:
			printDiskUsage(nfiles,nbytes)
		}
	}
	printDiskUsage(nfiles,nbytes)
}

func main(){
	Start()

	var name int = 0
	fmt.Scanf("%d",&name)
	println("name:",name)
}