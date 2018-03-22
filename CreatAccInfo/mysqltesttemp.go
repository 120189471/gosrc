package main

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
)

func main() {
	db, err := sql.Open("mysql", "root:3edcXSW@1qaz@tcp(127.0.0.1:3306)/qmcounter")
	//查询命令
	rows, err := db.Query("select * from mc_setting")
	checkerr(err)

	for rows.Next() {
		var setting_key, setting_value string
		err = rows.Scan(&setting_key, &setting_value)
		checkerr(err)
		fmt.Print(setting_key + "  ")
		fmt.Println(setting_value)
	}

}
