// interface{} 作为函数形参和 []interface{} 作为形参有很大区别，示例如下：

package main

import (
    "fmt"
)

func PrintAll(vals []interface{}) {
    for _, val := range vals {
        fmt.Println(val)
    }
}

func main() {
    names := []string{"stanley", "david", "oscar"}
    //PrintAll(names)//cannot use names (type []string) as type []interface {} in argument to PrintAll
    vals := make([]interface{},len(names))
    for i,v := range names{
        vals[i] = v
    }
    PrintAll(vals);
}