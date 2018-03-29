package main

import (
	"log"
	"github.com/lxn/walk"
)

func main() {
	if _ ,err:=RunMyDialog(nil);err!=nil{
		log.Fatal()
	}
}


type MyDialog struct{
	*walk.Dialog
	ui myDialogUI
}

func RunMyDialog(owner walk.Form)(int,error){
	dlg:=new(MyDialog)
	if err:=dlg.init(owner);err!=nil{
		return 0,err
	}
	/*
	dlg.ui.pushButtonAcc.Clicked().Attach(func(){

	})
*/
return dlg.Run(),nil
}