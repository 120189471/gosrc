package main

import (
	"log"
)
import (
	"fmt"
	"github.com/lxn/walk"
	"os"
)

func main() {
	if _, err := RunMyDialog(nil); err != nil {
		log.Fatal(err)
	}
}

type MyDialog struct {
	*walk.Dialog
	ui myDialogUI
}

func RunMyDialog(owner walk.Form) (int, error) {

	accfile := "D:/Projects/go/src/GreatAcc"

	dlg := new(MyDialog)
	if err := dlg.init(owner); err != nil {
		return 0, err
	}

	dlg.ui.pushButtonAcc.Clicked().Attach(func() {
		//创建目录
		qwin_account:=dlg.ui.lineEditAcc.Text()
		dlg.ui.labelErr.SetText(qwin_account)
		accfilePath := accfile + "/" + qwin_account
		err := os.Mkdir(accfilePath, os.ModePerm)
		if err != nil {
			fmt.Println(err)
		}

		//创建文件
		file, err := os.Create(accfilePath + "/" + "accountlist.ini")
		//check(err)
		defer file.Close()

		//写入内容
		file.WriteString("[main]\r\n")
		file.WriteString("count=3\r\n")
		file.WriteString("rememberpwd=1\r\n")
		file.WriteString("[user0]\r\n")
		file.WriteString("ispasscheck=1\r\n")
		file.WriteString("userid=" + qwin_account + "01\r\n")
		file.WriteString("investor=\r\n")
		file.WriteString("line=0\r\n")
		file.WriteString("investortype=1\r\n")
		file.WriteString("password=123456\r\n")
		file.WriteString("ontimepassword=\r\n")
		file.WriteString("comclass=12544,12545,12800,12801\r\n")
		file.WriteString("[user1]\r\n")
		file.WriteString("ispasscheck=1\r\n")
		file.WriteString("userid=" + qwin_account + "02\r\n")
		file.WriteString("investor=\r\n")
		file.WriteString("line=1\r\n")
		file.WriteString("investortype=3\r\n")
		file.WriteString("password=123456\r\n")
		file.WriteString("ontimepassword=\r\n")
		file.WriteString("comclass=12547,12803\r\n")
		file.WriteString("[user2]\r\n")
		file.WriteString("ispasscheck=1\r\n")
		file.WriteString("userid=" + qwin_account + "03\r\n")
		file.WriteString("investor=\r\n")
		file.WriteString("line=2\r\n")
		file.WriteString("investortype=4\r\n")
		file.WriteString("password=123456\r\n")
		file.WriteString("ontimepassword=\r\n")
		file.WriteString("comclass=13058,13059,13314,13570,13826,13315,13571,13827\r\n")

	})
	//WiriteFile(dlg.ui.lineEditAcc.Text(),accfile)

	return dlg.Run(), nil
}

func WiriteFile(qwin_account string, filePath string) {

	//创建目录
	accfilePath := filePath + "/" + qwin_account
	err := os.Mkdir(accfilePath, os.ModePerm)
	if err != nil {
		fmt.Println(err)
	}

	//创建文件
	file, err := os.Create(accfilePath + "/" + "accountlist.ini")
	//check(err)
	defer file.Close()

	//写入内容
	file.WriteString("[main]\r\n")
	file.WriteString("count=3\r\n")
	file.WriteString("rememberpwd=1\r\n")
	file.WriteString("[user0]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "01\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=0\r\n")
	file.WriteString("investortype=1\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12544,12545,12800,12801\r\n")
	file.WriteString("[user1]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "02\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=1\r\n")
	file.WriteString("investortype=3\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12547,12803\r\n")
	file.WriteString("[user2]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "03\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=2\r\n")
	file.WriteString("investortype=4\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=13058,13059,13314,13570,13826,13315,13571,13827\r\n")
}
