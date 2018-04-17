package main

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"strconv"
	"time"
)

type DBWorker struct {
	Dsn string
}

func checkerr(err error) {
	if err != nil {
		panic(err)
	}
}

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

func main() {
	dblinkinfo := DBlinkinfo{"mysql", "root", "3edcXSW@1qaz", "127.0.0.1", "3306", "qmcounter"}
	//db,err:=sql.Open("mysql","root:3edcXSW@1qaz@tcp(127.0.0.1:3306)/qmcounter")
	db, err := sql.Open(dblinkinfo.DBType, dblinkinfo.DBUser+":"+dblinkinfo.DBPWD+"@tcp("+dblinkinfo.DBIP+":"+dblinkinfo.DBPort+")/"+dblinkinfo.DBTableName)
	checkerr(err)
	defer db.Close()
	//dbins,err:=db.Prepare("INSERT mc_setting SET setting_key =test,setting_value=1.11")

	//插入命令
	//var treaduserinfo treadUserInfo

	tm := time.Now().Format("2006-01-02 15:04:05")
	intreaduserinfo := treadUserInfo{"00010211", "000102", "888888", 1, tm, tm}

	ret, err := db.Exec("INSERT into mc_user (seq,user_id,name,password,is_active,create_time,lastUpdate_time) VALUE (null,\"" + intreaduserinfo.userid + "\",\"" + intreaduserinfo.name + "\",\"" + intreaduserinfo.password + "\",\"" + strconv.Itoa(intreaduserinfo.isActive) + "\",\"" + intreaduserinfo.create_time + "\",\"" + intreaduserinfo.lasstUpdata_time + "\")")

	ins_id, _ := ret.LastInsertId()
	fmt.Println(ins_id)

}

//	treaduserinfo:=treadUserInfo{}
//	stmt err:=db.Prepare("INSERT ")
