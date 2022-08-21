else if (str.substr(0, 9) == "/copyset ")
{
    if (((PlayerInfo *)(peer->data))->adminLevel >= 777 || ((PlayerInfo *)(peer->data))->rawName == "admin")
    {

        string name = str.substr(9, cch.length() - 9 - 1);
        ENetPeer *currentPeer;

        for (currentPeer = server->peers;
             currentPeer < &server->peers[server->peerCount];
             ++currentPeer)
        {
            if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
                continue;

            if (((PlayerInfo *)(currentPeer->data))->rawName == name || ((PlayerInfo *)(currentPeer->data))->tankIDName == name)
            {

                ((PlayerInfo *)(peer->data))->cloth_hair = ((PlayerInfo *)(currentPeer->data))->cloth_hair;
                ((PlayerInfo *)(peer->data))->cloth_shirt = ((PlayerInfo *)(currentPeer->data))->cloth_shirt;
                ((PlayerInfo *)(peer->data))->cloth_pants = ((PlayerInfo *)(currentPeer->data))->cloth_pants;
                ((PlayerInfo *)(peer->data))->cloth_feet = ((PlayerInfo *)(currentPeer->data))->cloth_feet;
                ((PlayerInfo *)(peer->data))->cloth_face = ((PlayerInfo *)(currentPeer->data))->cloth_face;
                ((PlayerInfo *)(peer->data))->cloth_hand = ((PlayerInfo *)(currentPeer->data))->cloth_hand;
                ((PlayerInfo *)(peer->data))->cloth_back = ((PlayerInfo *)(currentPeer->data))->cloth_back;
                ((PlayerInfo *)(peer->data))->cloth_mask = ((PlayerInfo *)(currentPeer->data))->cloth_mask;
                ((PlayerInfo *)(peer->data))->cloth_necklace = ((PlayerInfo *)(currentPeer->data))->cloth_necklace;
                ((PlayerInfo *)(peer->data))->skinColor = ((PlayerInfo *)(currentPeer->data))->skinColor;
                sendClothes(peer);

                GamePacket p1 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`5[GTSS] `^You `9Copied `@Player `4" + ((PlayerInfo *)(currentPeer->data))->displayName + "`^ Clothes!"));
                string text = "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0\n";
                BYTE *data = new BYTE[5 + text.length()];
                BYTE zero = 0;
                int type = 3;
                memcpy(data, &type, 4);
                memcpy(data + 4, text.c_str(), text.length());
                memcpy(data + 4 + text.length(), &zero, 1);

                ENetPacket *packet1 = enet_packet_create(p1.data,
                                                         p1.len,
                                                         ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(peer, 0, packet1);

                ENetPacket *packet2 = enet_packet_create(data,
                                                         5 + text.length(),
                                                         ENET_PACKET_FLAG_RELIABLE);

                enet_peer_send(peer, 0, packet2);

                delete p1.data;
                delete data;
            }
        }
    }
}