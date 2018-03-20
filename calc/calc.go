package main

import (
	"calc/simplemath"
	"fmt"
	"os"
	"strconv"
)

var Usage = func() {
	fmt.Print("USAGE: calc command [arguments] ...")
	fmt.Print("\nThe commands are :\n\tadd\tAddition of two values.\n\tsqrt\tSquare" +
		"root of a non-negativ value.")

}

func main() {
	args := os.Args
	if args == nil || len(args) < 2 {
		Usage()
		return
	}
	switch args[0] {
	case "add":
		if len(args) != 3 {
			fmt.Print("USAGE: calc add<intger1><integer2>")
			return
		}

		v1, err1 := strconv.Atoi(args[1])
		v2, err2 := strconv.Atoi(args[2])
		if err1 != nil || err2 != nil {
			fmt.Print("USAGE: calc add<integer1><integer2>")
			return
		}
		ret := simplemath.Add(v1, v2)
		fmt.Print("Result: ", ret)
	case "sqrt":
		if len(args) != 2 {
			fmt.Print("USAGE: calc sqrt <integer>")
			return
		}
		v, err := strconv.Atoi(args[1])
		if err != nil {
			fmt.Println("USAGE: calc sqrt <integer>")
			return
		}
		ret := simplemath.Sqrt(v)
		fmt.Println("Result: ", ret)
	default:
		Usage()
	}
}
