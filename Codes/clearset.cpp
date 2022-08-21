else if (str == "/clearset")
{
    ((PlayerInfo *)(peer->data))->cloth_hair = 0;
    ((PlayerInfo *)(peer->data))->cloth_shirt = 0;
    ((PlayerInfo *)(peer->data))->cloth_pants = 0;
    ((PlayerInfo *)(peer->data))->cloth_feet = 0;
    ((PlayerInfo *)(peer->data))->cloth_face = 0;
    ((PlayerInfo *)(peer->data))->cloth_hand = 0;
    ((PlayerInfo *)(peer->data))->cloth_back = 0;
    ((PlayerInfo *)(peer->data))->cloth_mask = 0;
    ((PlayerInfo *)(peer->data))->cloth_necklace = 0;
    ((PlayerInfo *)(peer->data))->effect = 8421376;
    send_state(peer); // here
    sendClothes(peer);
    sendPuncheffectpeer(peer, ((PlayerInfo *)(peer->data))->effect);
}