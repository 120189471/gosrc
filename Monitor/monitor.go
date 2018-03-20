package main

import (
	"github.com/therecipe/qt/widgets"
	"os"
)

func main() {
	app := widgets.NewQApplication(len(os.Args),os.Args)

	windows := widgets.NewQMainWindow(nil,0)

	windows.SetWindowTitle("监控器")
	windows.SetMinimumSize2(1024,768)

	//windows.SetWindowIcon(QIcon("MockDemo.ico"))

	layout:=widgets.NewQVBoxLayout()
	about_btn:=widgets.NewQPushButton2("关于",nil)

	layout.AddWidget(about_btn,0,0)

	//about_btn:=





	windows.Show()
	app.Exec()

}
