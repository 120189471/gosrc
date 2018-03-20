package main

import (
	"fmt"
	"os"

	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/uitools"
	"github.com/therecipe/qt/widgets"
)

func main() {
	widgets.NewQApplication(len(os.Args), os.Args)

	AccSetWindow().Show()
	widgets.QApplication_Exec()
}

func AccSetWindow() *widgets.QWidget {
	var widget = widget.NewQWidget(nil, 0)
	var loader = uitools.NewQUiLoader(nil)
	var file = core.NewqFile2(":/accountset.ui")

	file.Open(core.QIODEVICE_ReadOnly)
	var formWidget = loader.Load(file, widget)
	file.Close()

}
