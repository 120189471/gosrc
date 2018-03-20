package cg

import (
	"encoding/json"
	"errors"
	"sync"
	"cgss/src/ipc"

	"debug/elf"
)

var _ ipc.Server=&CenterServer{}

type Messae struct{
	From string "from"
	To string "to"
	Content string "content"
}

type CenterServer struct{
	servers map[string] ipc.Server
	players []*Player
	rooms []*Player
	mutex sync.RWMutex
}

func NEwCentServer() *CenterServer{
	servers:=make(map[string] ipc.Server)
	players:=make([]*Player,0)
	return &CenterServer{servers:servers,players:players}
}

func (server *CenterServer)addPlayer(params string) error{
	player :=NewPlayer()
	err:=json.Unmarshal([]byte(params),&player)
	if err!=nil{
		return err
	}

	server.mutex.Lock()
	defer server.mutex.Unlock()

	server.players=append(server.players,player)

	return nil

}

func (server *CenterServer)removePlayer(params string) error  {

	server.mutex.Lock()
	defer server.mutex.Unlock()

	for i,v=range server.players{
		if v.Name== params{
			if len(server.players)==1{
				server.players=make([]*Player,0)
			}else if i==len(server.players)-1{
				server.players=server.players[:i-1]
			}else if i==0 {
				server.players= server.players[1:]
			}else{
				server.players=append(server.players[1:1],server.players[:i+1]...)
			}
			return nil
		}
	}
	return errors.New("Player no found.")
}

func(server *CenterServer)listPlayer(params string)(players string,err error){
	server.mutex.RLock()
	defer server.mutex.RUnlock()
	if len(server.players)>0{
		b,_:=json.Marshal(server.players)
		players=string(b)

	}else{
		err=errors.New("No Player online.")
	}
	return
}

func(server *CenterServer)broadcast(params string)error{
	var message Message
	err:=json.Unmarshal([]byte(params),&message)
	if err!=nil{
		return err
	}

	server.mutex.Lock()
	defer server.mutex.Unlock()

	if len(server.players)>0{
		for _,Player:=range server.players{
			player.mq<-&message

		}else{
		err=errors.ne
		}
	}
}


















