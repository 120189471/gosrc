package main

import "github.com/lxn/walk"

type myDialogUI struct {
	labelAcc       *walk.Label
	labelNo        *walk.Label
	labelErr       *walk.Label
	pushButtonAcc  *walk.PushButton
	pushButtonMoney *walk.PushButton
	lineEditAcc    *walk.LineEdit
	lineEditNo     *walk.LineEdit
}


func (w *MyDialog)init(owner walk.Form)(err error){
	if w.Dialog,err=walk.NewDialog(owner);err!=nil{
		return err
	}

	succseeded:=false

	defer func() {
		if !succseeded{
			w.Dispose()
		}
	}()

	var font *walk.Font
	if font==nil{
		font =nil
	}

	w.SetName("GreatAccount")
	if err:=w.SetClientSize(walk.Size{300,200});err!=nil{
		return err
	}

	if err:=w.SetTitle("GreatAccount");err!=nil{
		return err
	}

	//account
	w.ui.labelAcc.SetName("labelAcc")
	if err:=w.ui.labelAcc.SetBounds(walk.Rectangle{20,40,30,20});err!=nil{
		return err
	}
	if err:=w.ui.labelAcc.SetText("账号");err!=nil{
		return err
	}
	if err:=w.ui.labelAcc.SetMinMaxSize(walk.Size{30,20},walk.Size{30,20});err!=nil{
		return err
	}

	//number
	w.ui.labelNo.SetName("labelNo")
	if err:=w.ui.labelNo.SetBounds(walk.Rectangle{20,80,30,20});err!=nil{
		return err
	}
	if err:=w.ui.labelNo.SetText("个数");err!=nil{
		return err
	}
	if err:=w.ui.labelNo.SetMinMaxSize(walk.Size{30,20},walk.Size{30,20});err!=nil{
		return err
	}

	//error
	w.ui.labelErr.SetName("labelErr")
	if err:=w.ui.labelErr.SetBounds(walk.Rectangle{30,160,250,20});err!=nil{
		return	err
	}
	if err:=w.ui.labelErr.SetMinMaxSize(walk.Size{250,20},walk.Size{250,20});err!=nil{
		return err
	}

	//lineEdit account
	w.ui.lineEditAcc.SetName("lineEditAcc")
	if err:=w.ui.lineEditAcc.SetBounds(walk.Rectangle{90,40,120,20});err!=nil{
		return err
	}
	if err:=w.ui.lineEditAcc.SetMinMaxSize(walk.Size{120,20},walk.Size{120,20});err!=nil{
		return err
	}

	//lineEdit noumber
	w.ui.lineEditNo.SetName("lineEditNo")
	if err:=w.ui.lineEditNo.SetBounds(walk.Rectangle{90,80,120,20});err!=nil{
		return err
	}
	if err:=w.ui.lineEditNo.SetMinMaxSize(walk.Size{120,20},walk.Size{120,20});err!=nil{
		return err
	}

	//pushbutton great account
	w.ui.pushButtonAcc.SetName("pushButtonAcc")
	if err:=w.ui.pushButtonAcc.SetBounds(walk.Rectangle{40,120,70,30});err!=nil{
		return err
	}
	if err:=w.ui.pushButtonAcc.SetText("生成账号");err!=nil{
		return err
	}
	if err:=w.ui.pushButtonAcc.SetMinMaxSize(walk.Size{70,30},walk.Size{70,30});err!=nil{
		return err
	}

	//pushbutton Recharge
	w.ui.pushButtonMoney.SetName("pushButtonMoney")
	if err:=w.ui.pushButtonMoney.SetBounds(walk.Rectangle{160,120,70,30});err!=nil{
		return err
	}
	if err:=w.ui.pushButtonMoney.SetText("补蓝");err!=nil{
		return err
	}
	if err:=w.ui.pushButtonMoney.SetMinMaxSize(walk.Size{70,30},walk.Size{70,30});err!=nil{
		return err
	}

succseeded=true
return nil

}