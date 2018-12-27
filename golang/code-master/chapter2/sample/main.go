package main

import (
	"log"
	"os"

	//_ "E:/TestProjs/golang/code-master/chapter2/sample/matchers"
	//"E:/TestProjs/golang/code-master/chapter2/sample/search"
	_ "./matchers"
	"./search"
)

// init is called prior to main.
func init() {
	// Change the device for logging to stdout.
	log.SetOutput(os.Stdout)
}

// main is the entry point for the program.
func main() {
	// Perform the search for the specified term.
	search.Run("president")
}
