// This sample program demonstrates how to create goroutines and
// how the goroutine scheduler behaves with two logical processor.
package main

import (
	"fmt"
	"runtime"
	"sync"
)

var wg sync.WaitGroup

func TestSched(s string){
	defer wg.Done()
	for i:=0;i<5;i++{
		//runtime.Gosched()
		fmt.Println(s)
	}
}


// main is the entry point for all Go programs.
func main() {
	// Allocate two logical processors for the scheduler to use.
	runtime.GOMAXPROCS(1)

	wg.Add(2)
	go TestSched("world")
	TestSched("hello")//开始的时候可能连续执行不止一次，因为world还没准备好，准备好后，交替执行
	wg.Wait()

	//如果没有wg.Wait机制,这里最后输出的world，可能就不一定有，如果有，和下面的代码的顺序也不确定


	//runtime.GOMAXPROCS(2)

	// wg is used to wait for the program to finish.
	// Add a count of two, one for each goroutine.
	//var wg sync.WaitGroup
	wg.Add(2)

	fmt.Println("---------------------------")

	counter := 3
	// Declare an anonymous function and create a goroutine.
	go func() {
		// Schedule the call to Done to tell main we are done.
		defer wg.Done()

		// Display the alphabet three times.
		for count := 0; count < counter; count++ {
			for char := 'a'; char < 'a'+26; char++ {
				fmt.Printf("%c ", char)
			}
		}
	}()

	// Declare an anonymous function and create a goroutine.
	go func() {
		// Schedule the call to Done to tell main we are done.
		defer wg.Done()

		// Display the alphabet three times.
		for count := 0; count < counter; count++ {
			for char := 'A'; char < 'A'+26; char++ {
				fmt.Printf("%c ", char)
			}
		}
	}()

	// Wait for the goroutines to finish.
	fmt.Println("Waiting To Finish")
	wg.Wait()

	fmt.Println("\n==============Terminating Program=============")
}
