package TestFunc

import(
	"fmt"
)

type VowelsFinder interface{
	FindVowels()[]rune
}

type MyString string

func (ms MyString) FindVowels()[]rune{
	var vowels []rune
	for _,rune := range ms{
		if rune == 'a'||rune == 'e'||rune=='i'|| rune=='o'||rune=='u'{
			vowels = append(vowels,rune)
		}
	}
	return vowels
}

func TestInterface_new(){
	name := MyString("Sam Anderson")
	var v VowelsFinder
	v = name
	fmt.Printf("Vowels are %c \n",name.FindVowels())
	fmt.Printf("Vowels are %c \n",v.FindVowels())
}

//假设某公司有两个员工，一个普通员工和一个高级员工， 但是基本薪资是相同的，高级员工多拿奖金。计算公司为员工的总开支。
type SalaryCalculator interface{
	CalculateSalary()int
}

type Contract struct{
	empId int
	basicpay int
}

type Permanent struct{
	empId int
	basicpay int
	jj int //奖金
}

func (c Contract)CalculateSalary()int{
	return c.basicpay
}

func (p Permanent)CalculateSalary()int{
	return p.basicpay + p.jj
}

func totalExpense(s []SalaryCalculator){
	expense := 0
	for _,v := range s{
		expense = expense + v.CalculateSalary()
	}
	fmt.Printf("总开支 $%d",expense)
}

func TestInterface_Salary(){
	pemp1 := Permanent{1,3000,10000}
	pemp2 := Permanent{2,3000,20000}
	cont1 := Contract{3,3000}
	employees := []SalaryCalculator{pemp1,pemp2,cont1}
	totalExpense(employees)
}
