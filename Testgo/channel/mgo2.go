package main

import (
  "fmt"
//   "labix.org/v2/mgo"
//   "labix.org/v2/mgo/bson"
    "gopkg.in/mgo.v2"
    "gopkg.in/mgo.v2/bson"
)

type Person struct {
  Name  string
  pHone string
}
type Men struct {
  Persons []Person
}
const (
//   URL = "192.168.2.175:27017"
  URL = "localhost:27017"
)
func main() {

  session, err := mgo.Dial(URL)  //连接数据库
  if err != nil {
    panic(err)
  }
  defer session.Close()
  session.SetMode(mgo.Monotonic, true)

  db := session.DB("mydb")	 //数据库名称
  collection := db.C("person") //如果该集合已经存在的话，则直接返回


  //*****集合中元素数目********
  countNum, err := collection.Count()
  if err != nil {
    panic(err)
  }
  fmt.Println("Things objects count: ", countNum)

  //*******插入元素*******
  temp := &Person{
    pHone: "18811577546",
    Name:  "zhangzheHero",
  }
//   注意User的字段首字母大写，不然不可见。通过bson:”name”这种方式可以定义MongoDB中集合的字段名，如果不定义，mgo自动把struct的字段名首字母小写作为集合的字段名。如果不需要获得id_，Id_可以不定义，在插入的时候会自动生成。
    //一次可以插入多个对象 插入两个Person对象
  err = collection.Insert(&Person{"Ale", "+55 53 8116 9639"}, temp)
  if err != nil {
    panic(err)
  }

  //*****查询单条数据*******
  result := Person{}
  err = collection.Find(bson.M{"phone": "18811577546"}).One(&result)// 全字匹配,区分大小写
  fmt.Println("Phone:", result.Name, result.pHone)

  //*****查询多条数据*******
  var personAll Men  //存放结果
  iter := collection.Find(nil).Iter()
  for iter.Next(&result) {
    fmt.Printf("Result: %v\n", result.Name)
    personAll.Persons = append(personAll.Persons, result)
  }

  //*******更新数据**********
  err = collection.Update(bson.M{"name": "ccc"}, bson.M{"$set": bson.M{"name": "ddd"}})
  err = collection.Update(bson.M{"name": "ddd"}, bson.M{"$set": bson.M{"phone": "12345678"}})
  err = collection.Update(bson.M{"name": "Ale"}, bson.M{"phone": "1245", "namE": "BbB"})

  //******删除数据************
  _, err = collection.RemoveAll(bson.M{"name": "zhangzheHero"})
}