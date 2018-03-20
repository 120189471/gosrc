package main

import (
	"os"
	"fmt"
	"strconv"
)

func main() {
	//常量
	//路径
	filePath:="D:/Projects/go/src/CreatAccInfo"
	var temppath string
	var accountNumber ,tradAccount int
	accountNumber=1

	//获取写入的账号
	fmt.Print("输入文件生成路径，默认为："+filePath)
	fmt.Scanln(&temppath)
	if temppath!="" {
		filePath=temppath
	}
	//获取生成账号的个数
	fmt.Print("输入需要生成的账号数：默认为："+strconv.Itoa(accountNumber))
	fmt.Scanln((&accountNumber))

	//获取生成的第一个账号
	fmt.Print("输入需要生成的第一个账号：")
	fmt.Scan(&tradAccount)

	//创建文件
	fmt.Println("生成路径： "+filePath)
	fmt.Println("生成个数： "+strconv.Itoa(accountNumber))


	for i:=0;i<accountNumber ; i++ {
		qwin_account:=strconv.Itoa(tradAccount+accountNumber*10)
		fmt.Println("正在生成第"+strconv.Itoa(i+1)+"个账号："+qwin_account)
		wiritefile(qwin_account,filePath)
	}


}

func wiritefile(qwin_account string,filePath string){

	//创建目录
	accfilePath:=filePath+"/"+qwin_account
	err:=os.Mkdir(accfilePath,os.ModePerm)
	if err!=nil{
		fmt.Println(err)
	}

	//创建文件
	file,err:=os.Create(accfilePath+"/"+"accountlist.ini")
	check(err)
	defer file.Close()

	//写入内容
	file.WriteString("[main]\r\n")
	file.WriteString("count=3\r\n")
	file.WriteString("rememberpwd=1\r\n")
	file.WriteString("[user0]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid="+qwin_account+"01\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=0\r\n")
	file.WriteString("investortype=1\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12544,12545,12800,12801\r\n")
	file.WriteString("[user1]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid="+qwin_account+"02\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=1\r\n")
	file.WriteString("investortype=3\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12547,12803\r\n")
	file.WriteString("[user2]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid="+qwin_account+"03\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=2\r\n")
	file.WriteString("investortype=4\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=13058,13059,13314,13570,13826,13315,13571,13827\r\n")
}