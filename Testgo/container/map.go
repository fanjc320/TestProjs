package container 

import "fmt"
/* 声明变量，默认 map 是 nil *
//var map_variable map[string]int

/* 使用 make 函数 */
//map_variable := make(map[string]int)

func TestMap(){
    var countryCapitalMap map[string]string;
	countryCapitalMap = make(map[string]string)
	countryCapitalMap["France"] = "Paris"
	countryCapitalMap["Italy"] = "罗马"
	countryCapitalMap["India"] = "新德里"

	for country := range countryCapitalMap {
		fmt.Println(country,"首都是",countryCapitalMap[country])
	}

	capital,ok := countryCapitalMap["美国"]
	if(ok){
		fmt.Println("美国首都是",capital)
	}else{
		fmt.Println("美国的首都不存在")
	}
   
}