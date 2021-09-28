# example

```cpp
else if (str == "/doctor") {
    ((PlayerInfo*)(peer->data))->displayName = "`4Dr. " + ((PlayerInfo*)(peer->data))->displayName;
		string name2 = "`4Dr. " + ((PlayerInfo*)(peer->data))->displayName;
		((PlayerInfo*)(peer->data))->country = "id";
		((PlayerInfo*)(peer->data))->isNicked = true;

		GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), name2));
		memcpy(p7.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor

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
```
