# 基于ESP8266和Arduino的Socket内网穿透控制客户端

我正在学习Socket编程相关知识和硬件开发，最近想做一个使用手机控制开关的物联网设备，这只是这这一项目的一小步，主要是从服务端内网穿透控制客户端（Arduino）。

之前本人使用过一个物联云平台BigIoT，但是这个平台提供的内网穿透API过于臃肿，同时自己刚好也想试试自己的开发能力，所以这一次自己做内网穿透。
如果服务器与客户端处于同一子网内，数据传输相对容易一点，但是，当前的IPv4地址不够用，很多的客户端都是通过NAT转换连接到公网的，这就使得服务器不能直接向内网客户端发送数据。方法总是有的，由于客户端可以直接向公网服务器发送数据，而服务器在接收到数据之后，是可以向客户端回复一个数据的，这样一来，“回复”，便可以理解为服务器向内网客户端发送了数据。

本客户端的硬件部分主要采用Arduino Nano和ESP8266 Wi-Fi模块。

首先，Arduino向ESP8266发送请求连接远程服务器（TCP），在200ms延时内得到回复后，继续请求发送TCP数据包，而后传输数据（我这里只发送了一个“6”）。如果上面任意一步出现错误，错误指示灯将亮起，并且自动重新连接。如果连接无误，Arduino将会收到服务器回复的信息，“1”或“0”。这里我用“1”代表亮起被控制的LED，“0”代表熄灭它。

配合服务端的Socket程序，便可以实现简单的内网穿透通讯。

如果服务端回复的数据由另一个客户端提供（比如手机），那么就可以实现手机控制Arduino的行为了。
