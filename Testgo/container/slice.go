package container
import "fmt"

//var identifier []int

//var slice1 []int = make([]int,len,10)
//var slice1 []int = make([]int,len)
//slice1 := make([]type,len)
//s := [] int {1,2,3}
//s := arr[:]
//s := arr

func TestRange(){
	nums := []int{2,3,4}
	sum := 0
	for _,num := range nums{
		sum += num
	}
	fmt.Println("sum:",sum)
	
	kvs := map[string]string{"a":"apple","b":"banana"}
	for k,v := range kvs {
		fmt.Printf("%s->%s\n",k,v)	
	}
	for i,c:= range "abc" {
		fmt.Println(i,c)	
	}
}


