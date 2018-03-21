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
	dblinkinfo := DBlinkinfo{"mysql", "root", "3edcXSW@1qaz", "127.0.0.1", "3306", "qmcounter"}
	//db,err:=sql.Open("mysql","root:3edcXSW@1qaz@tcp(127.0.0.1:3306)/qmcounter")
	db, err := sql.Open(dblinkinfo.DBType, dblinkinfo.DBUser+":"+dblinkinfo.DBPWD+"@tcp("+dblinkinfo.DBIP+":"+dblinkinfo.DBPort+")/"+dblinkinfo.DBTableName)
	checkerr(err)
	defer db.Close()
	//dbins,err:=db.Prepare("INSERT mc_setting SET setting_key =test,setting_value=1.11")

	//插入命令
	//var treaduserinfo treadUserInfo
	userseq, err := db.Query("SELECT * from mc_user")
	checkerr(err)
	for userseq.Next() {

	var treaduserinfo treadUserInfo
	fmt.Println(userseq)
	userseq.Scan(&(treaduserinfo.seq))

	fmt.Println(treaduserinfo.seq)
	fmt.Println(treaduserinfo.userid)
	}

	//intreaduserinfo:= treadUserInfo{2,"000102","000102","888888",1,"11111",""}
	//"+intreaduserinfo.seq+","+intreaduserinfo.userid+","+intreaduserinfo.name+","+intreaduserinfo.password+","+intreaduserinfo.isActive+","+intreaduserinfo.create_time+","+intreaduserinfo.lasstUpdata_time+")
	ret,err:=db.Exec("INSERT into mc_user (seq,user_id,name,password,is_active,create_time,lastUpdate_time) VALUE (2,"2","2)")

	checkerr(err)
	fmt.Println(ret)

}



//	treaduserinfo:=treadUserInfo{}
//	stmt err:=db.Prepare("INSERT ")















