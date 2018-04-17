package main

import (
	"github.com/lxn/walk"
	. "github.com/lxn/walk/declarative"

	"strings"
)

func main() {

	var inTE, outTE *walk.TextEdit

	MainWindow{
		Title:   "GreatAcc",
		MinSize: Size{800, 600},
		MaxSize: Size{800, 600},
		Layout:  VBox{},
		Children: []Widget{
			HSplitter{
				Children: []Widget{
					Label{
						MinSize:Size{30,100},
						Text:"账号",



					},
					TextEdit{AssignTo: &inTE,},

					TextEdit{AssignTo: &outTE, ReadOnly: true},
				},
			},
			PushButton{
				Text: "SCREAM",
				OnClicked: func() {
					outTE.SetText(strings.ToUpper(inTE.Text()))
				},
			},
		},
	}.Run()






}
