rsrc -manifest GreatAcc.manifest -o rsrc.syso
go build -ldflags="-H windowsgui"
