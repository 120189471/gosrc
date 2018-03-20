package main

import (
	"fmt"
	"github.com/therecipe/qt/widgets"
	"io"
	"io/ioutil"
	"os"
)

func main() {
	// Create application
	app := widgets.NewQApplication(len(os.Args), os.Args)

	// Create main window
	window := widgets.NewQMainWindow(nil, 0)
	window.SetWindowTitle("Hello World Example")
	window.SetMinimumSize2(200, 200)

	// Create main layout
	layout := widgets.NewQVBoxLayout()

	// Create main widget and set the layout
	mainWidget := widgets.NewQWidget(nil, 0)
	mainWidget.SetLayout(layout)

	input := widgets.NewQLineEdit(nil)
	input.SetPlaceholderText("请输入需要生成的账号")
	layout.AddWidget(input, 0, 0)

	outstr, err := ioutil.ReadFile("accountlist.ini")
	fmt.print(string(outstr))
	// Set main widget as the central widget of the window
	window.SetCentralWidget(mainWidget)

	// Show the window
	window.Show()

	// Execute app
	app.Exec()
}
