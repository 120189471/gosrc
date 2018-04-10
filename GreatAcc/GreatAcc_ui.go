package main

import "github.com/lxn/walk"

type myDialogUI struct {
	labelAcc *walk.Label
	labelNo        *walk.Label
	labelErr       *walk.Label
	pushButtonAcc  *walk.PushButton
	pushButtonMoney *walk.PushButton
	lineEditAcc    *walk.LineEdit
	lineEditNo     *walk.LineEdit
}

func (w *MyDialog) init(owner walk.Form) (err error) {
	if w.Dialog, err = walk.NewDialog(owner); err != nil {
		return err
	}

	succeeded := false

	defer func() {
		if !succeeded {
			w.Dispose()
		}
	}()

	var font *walk.Font
	if font == nil {
		font = nil
	}

	w.SetName("GreatAccount")
	if err := w.SetClientSize(walk.Size{300, 200}); err != nil {
		return err
	}
	if err := w.SetTitle(`GreatAccount`); err != nil {
		return err
	}

	//account
	if w.ui.labelAcc,err=walk.NewLabel(w);err!=nil{
		return err
	}
	w.ui.labelAcc.SetName("labelAcc")
	if err := w.ui.labelAcc.SetBounds(walk.Rectangle{20, 40, 30, 20}); err != nil {
		return err
	}
	if err := w.ui.labelAcc.SetText("账号"); err != nil {
		return err
	}
	if err := w.ui.labelAcc.SetMinMaxSize(walk.Size{30, 20}, walk.Size{30, 20}); err != nil {
		return err
	}
	//number
	if w.ui.labelNo,err=walk.NewLabel(w);err!=nil{
		return err
	}
	w.ui.labelNo.SetName("labelNo")
	if err := w.ui.labelNo.SetBounds(walk.Rectangle{20, 80, 30, 20}); err != nil {
		return err
	}
	if err := w.ui.labelNo.SetText("个数"); err != nil {
		return err
	}
	if err := w.ui.labelNo.SetMinMaxSize(walk.Size{30, 20}, walk.Size{30, 20}); err != nil {
		return err
	}

	//error
	if w.ui.labelErr,err=walk.NewLabel(w);err!=nil{
		return err
	}
	w.ui.labelErr.SetName("labelErr")
	if err := w.ui.labelErr.SetBounds(walk.Rectangle{30, 160, 250, 20}); err != nil {
		return err
	}
	if err := w.ui.labelErr.SetMinMaxSize(walk.Size{250, 20}, walk.Size{250, 20}); err != nil {
		return err
	}

	//lineEdit account
	if w.ui.lineEditAcc,err=walk.NewLineEdit(w);err!=nil{
		return err
	}
	w.ui.lineEditAcc.SetName("lineEditAcc")
	if err := w.ui.lineEditAcc.SetBounds(walk.Rectangle{90, 40, 120, 20}); err != nil {
		return err
	}
	if err := w.ui.lineEditAcc.SetMinMaxSize(walk.Size{120, 20}, walk.Size{120, 20}); err != nil {
		return err
	}

	//lineEdit noumber
	if w.ui.lineEditNo,err=walk.NewLineEdit(w);err!=nil{
		return err
	}
	w.ui.lineEditNo.SetName("lineEditNo")
	if err := w.ui.lineEditNo.SetBounds(walk.Rectangle{90, 80, 120, 20}); err != nil {
		return err
	}
	if err := w.ui.lineEditNo.SetMinMaxSize(walk.Size{120, 20}, walk.Size{120, 20}); err != nil {
		return err
	}

	//pushbutton great account
	if w.ui.pushButtonAcc,err=walk.NewPushButton(w);err!=nil{
		return err
	}
	w.ui.pushButtonAcc.SetName("pushButtonAcc")
	if err := w.ui.pushButtonAcc.SetBounds(walk.Rectangle{40, 120, 70, 30}); err != nil {
		return err
	}
	if err := w.ui.pushButtonAcc.SetText("生成账号"); err != nil {
		return err
	}
	if err := w.ui.pushButtonAcc.SetMinMaxSize(walk.Size{70, 30}, walk.Size{70, 30}); err != nil {
		return err
	}

	//pushbutton Recharge
	if w.ui.pushButtonMoney,err=walk.NewPushButton(w);err!=nil{
		return err
	}
	w.ui.pushButtonMoney.SetName("pushButtonMoney")
	if err := w.ui.pushButtonMoney.SetBounds(walk.Rectangle{160, 120, 70, 30}); err != nil {
		return err
	}
	if err := w.ui.pushButtonMoney.SetText("补蓝"); err != nil {
		return err
	}
	if err := w.ui.pushButtonMoney.SetMinMaxSize(walk.Size{70, 30}, walk.Size{70, 30}); err != nil {
		return err
	}

	succeeded = true
	return nil

}
