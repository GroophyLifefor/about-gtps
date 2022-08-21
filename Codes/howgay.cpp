if (str == "/howgay")
{

    int restartefe = rand() % 100;
    Player::OnConsoleMessage(peer, "Are You Know You are `2%" + string_to(restartefe) + " Gays.");
    Player::OnTalkBubble(peer, static_cast<PlayerInfo *>(peer->data)->netID, "Are You Know You are `2%" + string_to(restartefe) + " Gays.", 0, false);
}