package main
import(
    "fmt"
    "labix.org/v2/mgo"
    "labix.org/v2/mgo/bson"
)
  
typePersonstruct{
    Namestring
    Phonestring
}
func main(){
    session,err:=mgo.Dial("mongodb://localhost")
    iferr!=nil{
        panic(err)
    }
    defer session.Close()
    //Optional.Switchthesessiontoamonotonicbehavior.
    session.SetMode(mgo.Monotonic,true)
    c:=session.DB("test").C("people")
    err=c.Insert(&Person{"Ale","+555381169639"},
        &Person{"Cla","+555384028510"})
    iferr!=nil{
        panic(err)
    }
    result:=Person{}
    err=c.Find(bson.M{"name":"Ale"}).One(&result)
    iferr!=nil{
        panic(err)
    }
    fmt.Println("Phone:",result.Phone)
}
