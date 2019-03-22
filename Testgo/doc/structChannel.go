//此文件不用来运行，只用来说明
package main

import(

)


 //=========================================
//等待某任务的结束：
done := make(chan struct{})
go func(){
	//doSomething
	close(done)
}()
/ do some other bits
// wait for that long running thing to finish
<-done
// do more things

//==========================================
//同一时刻启动多个任务：
start := make(chan struct{})
for i:=0;i<10000;i++{
	go func(){
		<-start //// wait for the start channel to be closed
		doWork(i) // do something
	}()
}

// at this point, all goroutines are ready to go - we just need to 
// tell them to start by closing the start channel
close(start)
//在Go语言中，有一种特殊的struct{}类型的channel，它不能被写入任何数据，只有通过close()函数进行关闭操作，才能进行输出操作。。struct类型的channel不占用任何内存！！！


//==============================================
//停止某事件：
//一旦关闭了stop，整个循环就会终止。这在Golang的官方包io.pipe中有应用
loop:
for{
	select{
	case m:= <-email:
		sendEmail(m)
	}
case <-stop: // triggered when the stop channel is closed
	break loop //exit
}

/*
func main(){
	var sig = make(chan struct{})
	close(sig)//// 必须进行close，才能执行<-sig，否则是死锁
	<-sig
}

*/