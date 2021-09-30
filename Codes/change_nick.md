# example

```cpp
else if (str == "/doctor") {

if (((PlayerInfo*)(peer->data))->TotalSurg > 299)
{
	if ((PlayerInfo*)(peer->data))->isDrTitle = false;
	{

    ((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->displayName; // add title to displayname
		string name2 = "`4Dr. " + ((PlayerInfo*)(peer->data))->displayName; // a string for new displayname
		((PlayerInfo*)(peer->data))->country = "id"; 
		((PlayerInfo*)(peer->data))->isNicked = true; // used nickname is true

		GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2)); // a gamepacket for namechange
		memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor

		((PlayerInfo*)(peer->data))->displayName = name2;
		ENetPacket* packet7 = enet_packet_create(p7.data, //gamepacket to enetpacket
				p7.len,
		ENET_PACKET_FLAG_RELIABLE);
		
		ENetPeer* currentPeer;
			for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount]; //foreach peer in server
			++currentPeer)
			{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						if (isHere(peer, currentPeer)) //if in same world
					{
						enet_peer_send(currentPeer, 0, packet7); // send OnNameChanged packet
					}
				}
				delete p7.data;
	
	}
	else {
		((PlayerInfo*)(peer->data))->displayName = "`w" + ((PlayerInfo*)(peer->data))->displayName;
		string name2 = "`4Dr. " + ((PlayerInfo*)(peer->data))->displayName; 
		((PlayerInfo*)(peer->data))->country = "../"; 
		((PlayerInfo*)(peer->data))->isNicked = true;

		GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));
		memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);

		((PlayerInfo*)(peer->data))->displayName = name2;
		ENetPacket* packet7 = enet_packet_create(p7.data, 
				p7.len,
		ENET_PACKET_FLAG_RELIABLE);
		
		ENetPeer* currentPeer;
			for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
			{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
							continue;
						if (isHere(peer, currentPeer))
					{
						enet_peer_send(currentPeer, 0, packet7);
					}
				}
				delete p7.data;
		}
	}
	else {
	Player::OnConsoleMessage(peer, "`oYou Need `4300 Surg `oFor Use This Command");
	Player::OnTalkBubble(peer, "`oYou Need `4300 Surg `oFor Use This Command");
}
```
