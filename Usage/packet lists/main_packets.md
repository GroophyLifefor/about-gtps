**PACKETS**

OnAddNotification: appendString "tile location", appendString "Message", appendString "sound location", appendInt 0.

**OnConsoleMessage: appendString "message".**

OnCountryState: appendString "tile location" & `memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);`

**OnDialogRequest: appendString: "dialog string".**

OnDisguiseChanged: appendIntx blockid. & `memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);`

**OnGuildDataChanged: appendIntx 41179607, appendIntx 41179607, appendIntx flag, appendIntx 0.**

OnInvis: appendInt 1 or 0 (bool) & `memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);`

**OnItemEffect: appendIntx effectid.**

OnParticleEffect: appendIntx effectid, appendFloat x and y.

**OnParticleEffectV2: appendIntx effectid, appendFloat x and y.**

OnSetBux: appendInt gemamount.

**OnSetClothing: appendFloat (cloth_hair, cloth_shirt, cloth_pants), appendFloat (cloth_feet, cloth_face, cloth_hand), appendFloat (cloth_back, cloth_mask, cloth_necklace), appendIntx skinColor, appendFloat (cloth_ances, 0.0f, 0.0f) & `memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);`**

OnSetCurrentWeather: appendInt weatherid.

**OnSetFreezeState: appendIntx 1-0 (bool).**

OnSetPos: appendFloat (x, y).

**OnTalkBubble: appendIntx netid, appendString text, appendIntx 0.**

OnTextOverlay: appendString text.
