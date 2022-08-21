else if (str == "/magic")
{
    if (((PlayerInfo)(peer->data))->adminLevel > 5)
    {
        if (!world)
            continue;
        float x = ((PlayerInfo)(peer->data))->x;
        float y = ((PlayerInfo)(peer->data))->y;
        ENetPeer currentPeer;
        for (currentPeer = server->peers;
             currentPeer < &server->peers[server->peerCount];
             ++currentPeer)
        {
            if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
                continue;
            Player::OnParticleEffect(currentPeer, 105, x, y, 105);
        }

        bool found = false;
        for (currentPeer = server->peers;
             currentPeer < &server->peers[server->peerCount];
             ++currentPeer)
        {
            if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
                continue;
            if (isHere(peer, currentPeer))
            {
                bool isRev = false;
                sendSound(peer, "magic.wav");
                sendSound(currentPeer, "magic.wav");
                for (int i = 5; i < 45; i++)
                {
                    if (isRev == false)
                    {
                        Player::OnParticleEffect(currentPeer, 3, x + i * (rand() % 5), y + i * (rand() % 7), i * 150);
                        Player::OnParticleEffect(currentPeer, 2, x + i * (rand() % 5), y + i * (rand() % 8), i * 150);
                        Player::OnParticleEffect(currentPeer, 1, x + i * (rand() % 5), y + i * (rand() % 9), i * 150);
                        isRev = true;
                    }
                    else
                    {
                        Player::OnParticleEffect(currentPeer, 3, x - i * (rand() % 5), y - i * (rand() % 5), i * 150);
                        Player::OnParticleEffect(currentPeer, 2, x + i * (rand() % 5), y + i * (rand() % 5), i * 150);
                        Player::OnParticleEffect(currentPeer, 1, x + i * (rand() % 5), y + i * (rand() % 5), i * 150);
                        isRev = false;
                    }
                }
            }
        }
    }
}