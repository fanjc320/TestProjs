package main

import (
    "fmt"
    "log"

    "gopkg.in/mgo.v2"
    "gopkg.in/mgo.v2/bson"
)

type Person struct {
    Name  string
    Phone string
}

func main() {
    session, err := mgo.Dial("localhost:27017")
    if err != nil {
        panic(err)
    }
    defer session.Close()

    // Optional. Switch the session to a monotonic behavior.
    session.SetMode(mgo.Monotonic, true)

    c := session.DB("test1").C("people")
    err = c.Insert(&Person{"superWang", "13478808311"},
        &Person{"David", "15040268074"})
    if err != nil {
        log.Fatal(err)
    }

    result := Person{}
    // err = c.Find(bson.M{"name": "superWang"}).One(&result)
    err = c.Find(bson.M{"name": "superKang"}).One(&result)
    if err != nil {
		fmt.Println("name not found!")
        log.Fatal(err)
    }

    fmt.Println("Name:", result.Name)
	fmt.Println("Phone:", result.Phone)
	

	
}