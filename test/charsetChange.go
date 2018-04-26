//GBK 与 UTF8相互转换测试

package main


import "golang.org/x/text/encoding/simplifiedchinese"

type Charset string

const UTF8  =Charset("UTF-8")
const GB18030  = Charset("GBK1830")

func ConvertByte2String(byte []byte,charset Charset)string{
	var str string
	switch charset{
	case GB18030:
		var decodeBytes,_=simplifiedchinese.GB18030.NewDecoder().Bytes(byte)
		str=string(decodeBytes)
	case UTF8:
		fallthrough
	default:
		str=string(byte)
	}
	return str
}
