package ipc

import "testing"

package center_go

import(
"testing"
"cgss/src/ipc"
)

type EchoServer struct{

}

func(server *EchoServer)Handle(request string) string{
	return "ECHO: "+request
}

func(server *EchoServer)Name()string{
	return "EchoServer"
}

func TestIpc(t *testing.T){
	server :=NewIpcServer(&EchoServer)
	client1:=NewIpcClient(server)
	client2:=NewIpcClient(server)
	resp1:=client1.Call("From Client1")
	resp2:=client2.Call("From Client2")

	if resp1!="Echo:FromeClient1"||resp2!="Echo:From Client2"{
		t.Error("IpcClient.Call failed. resp1:",resp1,"resp2:",resp2 )
	}
	client1.Close()
	client2.Close()
}
