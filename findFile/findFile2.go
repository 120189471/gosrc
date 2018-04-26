package main

import (
	"fmt"
	"os"
	"path/filepath"
	"bufio"
	"io"
	"test"

)

func check(e error) {
	if e != nil {
		panic(e)
	}
}
func addcfg(fp string) {
	//dat,err:=ioutil.ReadFile(fp)
	f, err := os.Open(fp)
	defer f.Close()
	check(err)

	br:=bufio.NewReader(f)
	for {
		a,_,c:=br.ReadLine()
		if c==io.EOF{
			break
		}




	}
}

func lint(path string, f os.FileInfo, err error) error {

	if f.Name() == "counterlist.ini" {
		fmt.Print(path)
		fmt.Println("\t", f.Name(), "\t", f.Mode(), "\t", f.IsDir())

		addcfg(path)

	}

	return nil
}

func main() {

	fmt.Println(filepath.Walk("D:\\Projects\\go\\src\\findFile", lint))

}
