
post部分那个空行必须有
AT命令引号要转译用反斜杠\
如果用mySerial.println("AT")不需要加换行\r\n,如果用的mySerial.print("AT\r\n")需要加换行\r\n
loop里面调两遍post()，因为我这边调试就要点两次才能发送成功，不知道是我这边模块问题还是那边平台问题。