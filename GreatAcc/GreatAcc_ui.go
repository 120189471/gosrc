package main

import "github.com/lxn/walk"

type myDialogUI struct {
	labelMonUtil	*walk.Label
	labelMsg        *walk.Label
	pushButtonAcc   *walk.PushButton
	pushButtonMoney *walk.PushButton
	lineEditAcc     *walk.LineEdit
	lineEditMoney	*walk.LineEdit
	stockChkBox		*walk.CheckBox
	optChkBox		*walk.CheckBox
	futChkBox		*walk.CheckBox
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

	//label for money util
	if w.ui.labelMonUtil, err = walk.NewLabel(w); err != nil {
		return err
	}
	w.ui.labelMonUtil.SetName("labelMonUtil")
	if err := w.ui.labelMonUtil.SetBounds(walk.Rectangle{150, 110, 30, 20}); err != nil {
		return err
	}
	if err := w.ui.labelMonUtil.SetText("万元"); err != nil {
		return err
	}
	if err := w.ui.labelMonUtil.SetMinMaxSize(walk.Size{30, 20}, walk.Size{30, 20}); err != nil {
		return err
	}


	//error
	if w.ui.labelMsg, err = walk.NewLabel(w); err != nil {
		return err
	}
	w.ui.labelMsg.SetName("labelMsg")
	if err := w.ui.labelMsg.SetBounds(walk.Rectangle{30, 160, 250, 20}); err != nil {
		return err
	}
	if err := w.ui.labelMsg.SetMinMaxSize(walk.Size{250, 20}, walk.Size{250, 20}); err != nil {
		return err
	}

	//lineEdit account
	if w.ui.lineEditAcc, err = walk.NewLineEdit(w); err != nil {
		return err
	}
	w.ui.lineEditAcc.SetName("lineEditAcc")
	if err := w.ui.lineEditAcc.SetBounds(walk.Rectangle{30, 40, 120, 20}); err != nil {
		return err
	}
	if err := w.ui.lineEditAcc.SetMinMaxSize(walk.Size{120, 20}, walk.Size{120, 20}); err != nil {
		return err
	}

	//lineEdit Money
	if w.ui.lineEditMoney, err = walk.NewLineEdit(w); err != nil {
		return err
	}
	w.ui.lineEditMoney.SetName("lineEditMoney")
	if err := w.ui.lineEditMoney.SetBounds(walk.Rectangle{30, 110, 120, 20}); err != nil {
		return err
	}
	if err := w.ui.lineEditMoney.SetMinMaxSize(walk.Size{120, 20}, walk.Size{120, 20}); err != nil {
		return err
	}


	//pushbutton great account
	if w.ui.pushButtonAcc, err = walk.NewPushButton(w); err != nil {
		return err
	}
	w.ui.pushButtonAcc.SetName("pushButtonAcc")
	if err := w.ui.pushButtonAcc.SetBounds(walk.Rectangle{180, 40, 80, 23}); err != nil {
		return err
	}
	if err := w.ui.pushButtonAcc.SetText("生成账号"); err != nil {
		return err
	}
	if err := w.ui.pushButtonAcc.SetMinMaxSize(walk.Size{80, 23}, walk.Size{80, 23}); err != nil {
		return err
	}

	//pushbutton Recharge
	if w.ui.pushButtonMoney, err = walk.NewPushButton(w); err != nil {
		return err
	}
	w.ui.pushButtonMoney.SetName("pushBtnMoney")
	if err := w.ui.pushButtonMoney.SetBounds(walk.Rectangle{180, 110, 80, 23}); err != nil {
		return err
	}
	if err := w.ui.pushButtonMoney.SetText("补蓝"); err != nil {
		return err
	}
	if err := w.ui.pushButtonMoney.SetMinMaxSize(walk.Size{80, 23}, walk.Size{80, 23}); err != nil {
		return err
	}

	//checkBox stock
	if w.ui.stockChkBox,err=walk.NewCheckBox(w); err!=nil{
		return err
	}
	w.ui.stockChkBox.SetName("stockChkBox")
	if err:=w.ui.stockChkBox.SetBounds(walk.Rectangle{40,80,70,20});err!=nil{
		return err
	}
	if err:=w.ui.stockChkBox.SetText("Stock");err!=nil{
		return err
	}
	if err:=w.ui.stockChkBox.SetMinMaxSize(walk.Size{70,20},walk.Size{70,20});err!=nil{
		return err
	}

	//checkBox optinl
	if w.ui.optChkBox,err=walk.NewCheckBox(w); err!=nil{
		return err
	}
	w.ui.optChkBox.SetName("optChkBox")
	if err:=w.ui.optChkBox.SetBounds(walk.Rectangle{110,80,70,20});err!=nil{
		return err
	}
	if err:=w.ui.optChkBox.SetText("Opt");err!=nil{
		return err
	}
	if err:=w.ui.optChkBox.SetMinMaxSize(walk.Size{70,20},walk.Size{70,20});err!=nil{
		return err
	}

	//checkBox fut

	if w.ui.futChkBox,err=walk.NewCheckBox(w); err!=nil{
		return err
	}
	w.ui.futChkBox.SetName("futChkBox")
	if err:=w.ui.futChkBox.SetBounds(walk.Rectangle{180,80,70,20});err!=nil{
		return err
	}
	if err:=w.ui.futChkBox.SetText("Fut");err!=nil{
		return err
	}
	if err:=w.ui.futChkBox.SetMinMaxSize(walk.Size{70,20},walk.Size{70,20});err!=nil{
		return err
	}




	succeeded = true
	return nil

}
