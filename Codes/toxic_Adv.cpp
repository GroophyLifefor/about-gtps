//int main function after builddatabase();
thread advs(adv); if (advs.joinable()) advs.detach();

//before main function
void adv()
{
	while (true)
	{
		Sleep(120000);
		ENetPeer* currentPeer;
		GamePacket p2 = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), "interface/tutorial/tut08_chat.rttex"), "`ohttps://discord.gg/RcTcXuZWCAWhy   \nyou don't come GTLF's Discord? Give me a Suggestion for new update :) \nhttps://discord.gg/RcTcXuZWCA"), "audio/tip_start.wav"), 1));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (!((PlayerInfo*)(currentPeer->data))->radio)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->rawName == "lercy" || ((PlayerInfo*)(currentPeer->data))->rawName == "groophy")
				continue;
			enet_peer_send(currentPeer, 0, packet2);


		}
		delete p2.data;
	}
}
