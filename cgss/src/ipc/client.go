package ipc

import (
	"encoding/json"
)

type IpcClient struct {
	conn chan string
}

func NewIpcClient(Server *IpcServer) *IpcClient {
	c := server.Connect()
	return &IpcClient{c}
}

func (client *IpcClient) Call(method, params string) (resp *Response, err error) {
	req := &Request{method, params}
	var b []byte
	b, err = json.Marshal(req)

	if err != nil {
		return
	}

	client.conn <- string(b)
	str := <-client.conn //等待返回值

	var respl Response
	err = json.Unmarshal([]byte(str), &respl)
	resp = &respl

	return
}

func (clinet *IpcClient) Close() {
	client.conn <- "CLOSE"
}
