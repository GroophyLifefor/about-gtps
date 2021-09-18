#Usage: \
end_dialog|
Example : 
 - end_dialog|dialog_name|Cancel|OK|

\
Usage :
 - add_text_input|text_input name|text_input text | default input text|max text length|

\
Example : 
 - add_text_input|item|Item Name||30|
 - end_dialog|findid|Cancel|Find the item!|

\
\
\
When clicked OK(Find the item!) you will get:
 - action|dialog_return|dialog_name|dialog_name(findid)

\
after this dialog

\
we goto **if (cch.find("action|dialog_return") == 0)** \
we add
```
bool isFindDialog = false;
string itemFind = "";
```
**names changeable :D**
after we goto down
we add
```
if (infoDat[0] == "dialog_name" && infoDat[1] == "dialog_name(findid)")
{
	 isFindDialog = true;
}
if (isFindDialog) {
  	if (infoDat[0] == "item") itemFind = infoDat[1];
}
```
goto more down and add
```c-plus-plus
else if (isFindDialog) {
//dialog area
Example: 
GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "You wanted itemid: " + itemFind));
ENetPacket* packet = enet_packet_create(p.data,
p.len,
ENET_PACKET_FLAG_RELIABLE);
enet_peer_send(peer, 0, packet);
delete p.data;
}
```

WELL DONE :D
