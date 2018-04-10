package main

import (
	"log"
)
import (
	"github.com/lxn/walk"
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
	dlg := new(MyDialog)
	if err := dlg.init(owner); err != nil {
		return 0, err
	}

	return dlg.Run(), nil
}
