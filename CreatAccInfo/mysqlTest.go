package main

import (
	_ "github.com/go-sql-driver/mysql"
"database/sql"
	"fmt"
)


type DBWorker struct{
	Dsn string
}

func checkerr(err error){
	if err!=nil{
		panic(err)
	}
}

type DBlinkinfo struct{
	DBType string
	DBUser string
	DBPWD	string
	DBIP string
	DBPort string
	DBTableName string

}

type treadUserInfo struct{
	seq int
	userid string
	name string
	password string
	isActive uint8
	create_time	string
	lasstUpdata_time string
}

func main() {
	dblinkinfo:=DBlinkinfo{"mysql","root","3edcXSW@1qaz","127.0.0.1","3306","qmcounter"}
	//db,err:=sql.Open("mysql","root:3edcXSW@1qaz@tcp(127.0.0.1:3306)/qmcounter")
	db,err:=sql.Open(dblinkinfo.DBType,dblinkinfo.DBUser+":" +dblinkinfo.DBPWD+"@tcp("+dblinkinfo.DBIP+":"+dblinkinfo.DBPort+")/"+dblinkinfo.DBTableName)
	checkerr(err)
	defer db.Close()
	//dbins,err:=db.Prepare("INSERT mc_setting SET setting_key =test,setting_value=1.11")

	//插入命令
	//var treaduserinfo treadUserInfo
	userseq,err:=db.Query("SELECT max(Seq) from mc_user")
	checkerr(err)
	fmt.Println(userseq)
	if userseq.Scan()==nil{
		fmt.Print("userdeq=nil")
	}else {
		fmt.Print("判断错误")
	}



//	treaduserinfo:=treadUserInfo{}
//	stmt err:=db.Prepare("INSERT ")

}















