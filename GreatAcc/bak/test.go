package main

import (
	"bufio"
	"fmt"
	"io"
	"io/ioutil"
	"os"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	data, err := ioutil.ReadFile("accountlist.ini")
	check(err)
	fmt.Print(string(data))

	fmt.Println("************************************")

	f, err := os.Open("accountlist.ini")
	check(err)
	defer f.Close()

	rd := bufio.NewReader(f)
	for {
		line, err := rd.ReadSlice('\n')

		if err != nil || io.EOF == err {
			break
		}
		fmt.Println(string(line))
		fmt.Print("--------")
	}

}
