//library
#include <thread>

//under the library
int resultnbr1 = 0;
int resultnbr2 = 0;
int hasil = 0;
int prize = 0;
long long int quest = 0;

//int main add after BuildItemsDatabase();
thread math(updateAnswer); if (math.joinable()) math.detach();

//updateAnswer void (before than int main)
void updateAnswer()
{
	while (updateAnswer)
	{
		using namespace std::chrono;
		if (quest + 300000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
		{
			quest = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();

			int userMaxRand = 500, userLowRand = 0;

			resultnbr2 = rand() % userMaxRand + userLowRand + 1;
			srand(time(0));
			resultnbr1 = rand() % userMaxRand + userLowRand + 1; // Randomizes between the numbers you choose.

			hasil = resultnbr1 + resultnbr2;
			prize = (rand() % 300) + 100;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				sendConsole(currentPeer, "`9** GTLF Daily : `3'" + to_string(resultnbr1) + " + " + to_string(resultnbr2) + "'`9 = ? Prize: `2" + to_string(prize) + "`9 (gems) ! `o(/a <answer>).");
				sendSound(currentPeer, "startopia_tool_droid.wav");
			}
			cout << " ** GTLF Daily : '" + to_string(resultnbr1) + " + " + to_string(resultnbr2) + "' = ? Prize: " + to_string(prize) + " gems ! `o(/a answer)." << endl;
		}
	}

}

//answer command
else if (str.substr(0, 3) == "/a ") {
						ENetPeer * currentPeer;
						int imie = atoi(str.substr(3, cch.length() - 3 - 1).c_str());

						if (imie == 0) continue;
						if (imie == hasil) {
							resultnbr1 = 0;
							resultnbr2 = 0;
							hasil = 0;

							((PlayerInfo*)(peer->data))->gem = ((PlayerInfo*)(peer->data))->gem + prize;
							prize = 0;

							GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), ((PlayerInfo*)(peer->data))->gem));
							ENetPacket * packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);

							enet_peer_send(peer, 0, packet);
							delete p.data;
							savejson(peer);
							string nama = ((PlayerInfo*)(peer->data))->displayName;
							ENetPeer * currentPeer;

							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
									continue;
								sendConsole(currentPeer, "`w** `eGTLF Private Server `1Daily Math: (party) Math Event Winner is `w" + nama + "`9!");
								sendSound(currentPeer, "pinata_lasso.wav");

							}
						}
						else
						{
							sendConsole(peer, "Math Event not Found Please Wait New Math Event");
						}
						}



//other functions
void sendConsole(ENetPeer* x, string e) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), e));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(x, 0, packet);
	delete p.data;
}

void sendSound(ENetPeer* peer, string sound)
{
	string text = "action|play_sfx\nfile|audio/" + sound + "\ndelayMS|0\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);

	ENetPacket * packet2 = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);

	enet_peer_send(peer, 0, packet2);
	delete data;
}
