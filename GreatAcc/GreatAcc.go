package main

import (
	"log"
)
import (
	"database/sql"
	_ "github.com/go-sql-driver/mysql"
	"github.com/lxn/walk"
	"io"
	"os"
	"time"
)

type DBlinkinfo struct {
	DBType      string
	DBUser      string
	DBPWD       string
	DBIP        string
	DBPort      string
	DBTableName string
}

type treadUserInfo struct {
	userid           string
	name             string
	password         string
	isActive         int
	create_time      string
	lasstUpdata_time string
}

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

	/*
		Trace = log.New(ioutil.Discard, "TRACE: ", log.Ltime|log.Lshortfile)
		Info = log.New(os.Stdout, "Info: ", log.Ltime|log.Lshortfile)
		Warning = log.New(os.Stdout, "Warning: ", log.Ltime|log.Lshortfile)
		Error = log.New(io.MultiWriter(file, os.Stderr),  "Error", log.Ltime|log.Lshortfile)
	*/
	Info = log.New(io.MultiWriter(file, os.Stderr), "[Info]\t\t", log.Ldate|log.Ltime)
	Warning = log.New(io.MultiWriter(file, os.Stderr), "[Warning]\t", log.Ldate|log.Ltime)
}

func main() {
	Info.Println("程序初始化")
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
		WiriteFile(dlg.ui.lineEditAcc.Text(), accfile)
		addAcc(dlg.ui.lineEditAcc.Text())
		dlg.ui.labelMsg.SetText("账号生成成功")
	})

	dlg.ui.pushButtonMoney.Clicked().Attach(func(){
		if dlg.ui.stockChkBox.CheckState()==1{
			addMoney(dlg.ui.lineEditAcc.Text(),"1")
		}
		if dlg.ui.optChkBox.CheckState()==1{
			addMoney(dlg.ui.lineEditAcc.Text(),"3")
		}
		if dlg.ui.futChkBox.CheckState()==1{
			addMoney(dlg.ui.lineEditAcc.Text(),"3")
		}

	})


	return dlg.Run(), nil
}

func WiriteFile(qwin_account string, filePath string) (oerr error) {

	//创建目录
	accfilePath := filePath + "/" + qwin_account
	err := os.Mkdir(accfilePath, os.ModePerm)
	Warning.Println(err)
	if err != nil {
		return err
	}

	//创建文件
	file, err := os.Create(accfilePath + "/" + "accountlist.ini")
	Warning.Println(err)
	if err != nil {
		return err
	}

	defer file.Close()
	Info.Println("account:" + qwin_account)

	//写入内容
	file.WriteString("[main]\r\n")
	file.WriteString("count=3\r\n")
	file.WriteString("rememberpwd=1\r\n")
	file.WriteString("[user0]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=0\r\n")
	file.WriteString("investortype=1\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12544,12545,12800,12801\r\n")
	file.WriteString("[user1]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=1\r\n")
	file.WriteString("investortype=3\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=12547,12803\r\n")
	file.WriteString("[user2]\r\n")
	file.WriteString("ispasscheck=1\r\n")
	file.WriteString("userid=" + qwin_account + "\r\n")
	file.WriteString("investor=\r\n")
	file.WriteString("line=2\r\n")
	file.WriteString("investortype=4\r\n")
	file.WriteString("password=123456\r\n")
	file.WriteString("ontimepassword=\r\n")
	file.WriteString("comclass=13058,13059,13314,13570,13826,13315,13571,13827\r\n")
	Info.Println("账号文件创建成功")
	return
}

func addAcc(account string) (err error){
	dbinfo := DBlinkinfo{"mysql", "root", "3edcXSW@1qaz", "192.168.3.190", "5873", "qmcounter"}
	//db,err:=sql.Open("mysql","root:3edcXSW@1qaz@tcp(127.0.0.1:3306)/qmcounter")
	db, err := sql.Open(dbinfo.DBType, dbinfo.DBUser+":"+dbinfo.DBPWD+"@tcp("+dbinfo.DBIP+":"+dbinfo.DBPort+")/"+dbinfo.DBTableName)
	if err != nil {
		Warning.Println(err)
		return err
	}
	defer db.Close()
	//dbins,err:=db.Prepare("INSERT mc_setting SET setting_key =test,setting_value=1.11")

	tm := time.Now().Format("2006-01-02 15:04:05")
	//intreaduserinfo := treadUserInfo{account, account, "888888", 1, tm, tm}
	Info.Println("INSERT into mc_user (user_id,name,password,is_active,create_time) VALUE (\"" + account + "\",\"" + account + "\",\"888888\",\"1\",\"" + tm + "\")")
	//ret, err := db.Exec("INSERT into mc_user (user_id,name,password,is_active,create_time) VALUE (\""+account + "\",\"" + account + "\",\"888888\",\"1\",\"" + intreaduserinfo.create_time + "\")")
	//Info.Println("INSERT into mc_account (tradingday, user_id, account_type, inv_id, pre_balance, balance, available, create_time) VALUE (" + "'2000-1-1',\"" + account + "\",\"3\",\"" + account + "\",\"100000000\",\"100000000\",\"100000000\"," + tm + ")")
	ret, err :=db.Exec("INSERT into mc_account (tradingday, user_id, account_type, inv_id, pre_balance, balance, available, create_time) VALUE (" + "'2000-1-1',\"" + account + "\",\"1\",\"" + account + "\",\"100000000\",\"100000000\",\"100000000\",'" + tm + "')")
	Info.Println(ret)
	ret, err =db.Exec("INSERT into mc_account (tradingday, user_id, account_type, inv_id, pre_balance, balance, available, create_time) VALUE (" + "'2000-1-1',\"" + account + "\",\"3\",\"" + account + "\",\"100000000\",\"100000000\",\"100000000\",'" + tm + "')")
	Info.Println(ret)
	ret, err =db.Exec("INSERT into mc_account (tradingday, user_id, account_type, inv_id, pre_balance, balance, available, create_time) VALUE (" + "'2000-1-1',\"" + account + "\",\"4\",\"" + account + "\",\"100000000\",\"100000000\",\"100000000\",'" + tm + "')")
	Info.Println(ret)
	if err != nil {
		Warning.Println(err)
		panic(err)
	}
	//ins_id, _ := ret.LastInsertId()
	//fmt.Println(ins_id)
	return
}

func addMoney(account string, acctype string)(oerr error){
	dbinfo := DBlinkinfo{"mysql", "root", "3edcXSW@1qaz", "192.168.3.190", "5873", "qmcounter"}
	db,err:=sql.Open(dbinfo.DBType,dbinfo.DBUser+":"+dbinfo.DBPWD+"@tcp("+dbinfo.DBIP+":"+dbinfo.DBPort+")/"+dbinfo.DBTableName)
	if err!=nil{
		Warning.Println(err)
		return err
	}
	defer db.Close()

	tm:=time.Now().Format("2006-01-02 15:04:05")
	ret, err :=db.Exec("insert into mc_transfer(tradingday,user_id,account_type,inv_id,trans_amount,direct,insert_datetime) value("+tm+","+account+","+acctype+","+account+","+tm)
	Info.Println(ret)
	if err!=nil{
		Warning.Println(err)
		panic(err)
	}
	return
}