package main

import (
	"os"
	"strings"
	"fmt"
	"path/filepath"
	"log"
	"io"
)

var (
	ostype=os.Getenv("GOOS")
)

var listfile []string

var (
	Trace   *log.Logger // 记录所有日志
	Info    *log.Logger // 重要的信息
	Warning *log.Logger // 需要注意的信息
	Error   *log.Logger // 致命错误
)

func init() {
	file, err := os.OpenFile("run.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0666)
	if err != nil {
		log.Fatalln("Failed to open error log file:", err)
	}

	Info = log.New(io.MultiWriter(file, os.Stderr), "[Info]\t\t", log.Ldate|log.Ltime)
	Warning = log.New(io.MultiWriter(file, os.Stderr), "[Warning]\t", log.Ldate|log.Ltime)
}

func Listfunc(path string,f os.FileInfo,err error)error{
	var strRet string
	strRet,_=os.Getwd()

	if ostype=="windows"{
		strRet+="\\"
	}else if ostype=="linux" {
		strRet+="/"
	}

	if f==nil{
		return err
	}
	if f.IsDir(){
		return err
	}

	strRet+=path
	if strings.HasSuffix(strRet,strRet){
		listfile=append(listfile,strRet)
	}

	fmt.Println(strRet)
	return nil
}

func getFileList(path string)string{
	err:=filepath.Walk(path,Listfunc)
	if err!=nil{
		fmt.Printf("filepath.Walk() returned %v\n",err)
	}
	return " "
}

func ListFileFunc(p []string){
	for index, value:=range p{
		fmt.Println("index = ",index," Value = ",value)
	}
}

func main(){
	var listpath string
	fmt.Scanf("%s",&listpath)
	getFileList(listpath)
	ListFileFunc(listfile)

}