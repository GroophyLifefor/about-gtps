# A story of ps(Growtopia Private Server)
# i made 4-5 month ago but i forget to share so i lose ready folder, sorry

## First step(Create an enet project): 
 - Create a c++ console project
 - add enet folder to project folder
 - open project properties and do Linker->Input->Additional Dependencies->
 - for 32|86x type: **winmm.lib;ws2_32.lib;enet.lib;**
 - for 64x type: **winmm.lib;ws2_32.lib;enet64.lib;**
 - back to code and add **#include "enet/enet.h"**

## Second step(Create an server with enet): 
 - a template for server
```cpp
#include <iostream>
#include "enet/enet.h"
using namespace std;

ENetHost* server;

int main()
{
    enet_initialize();
	ENetAddress address;
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	enet_address_set_host(&address, "0.0.0.0");
	//address.host = ENET_HOSconT_ANY;
	/* Bind the server to port 1234. */
	address.port = 17091;
	server = enet_host_create(&address /* the address to bind the server host to */,
		1024      /* allow up to 32 clients and/or outgoing connections */,
		10      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		while (1);
		exit(EXIT_FAILURE);
	}
	server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(server);

	ENetEvent event;
	for (int i = 0; i < 1;)
	{
		while (enet_host_service(server, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);
				/* Store any relevant client information here. */
				event.peer->data = "Client information";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->data,
					event.channelID);
				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(event.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				/* Reset the peer's client information. */
				event.peer->data = NULL;
			}
		}
	}
}
```
 - looks pretty good
## Third step(Somethings for ps): 
 - we need to receive packet code
 ```cpp
int GetMessageTypeFromPacket(ENetPacket* packet)
{
	int result;

	if (packet->dataLength > 3u)
	{
		result = *(packet->data);
	}
	else
	{
		cout << "Bad packet length, ignoring message" << endl;
		result = 0;
	}
	return result;
}
```

```cpp
case ENET_EVENT_TYPE_RECEIVE:
	int messageType = GetMessageTypeFromPacket(event.packet);
```

 - [Packet Docs](https://github.com/GroophyLifefor/about-gtps/tree/main/Usage/packets)
 - New Library **#include string** for to_string function
 - umm an error of swicht
  
```cpp
switch (event.type)
			{
				printf("A new data \n");
			case ENET_EVENT_TYPE_CONNECT:
			{

			}
				break;
			case ENET_EVENT_TYPE_RECEIVE:
			{
				int messageType = GetMessageTypeFromPacket(event.packet);
				cout << to_string(messageType) << endl;

				enet_packet_destroy(event.packet);

			}
				break;
			case ENET_EVENT_TYPE_DISCONNECT:

			{
				event.peer->data = NULL;
			}
			}
```

 - fixed with do {} after case
 - now time to playerinfo
 - New Library **#include vector** for playerinventory
```cpp
struct ItemSharedUID {
	int actual_uid = 1;
	int shared_uid = 1;
};

struct InventoryItem {
	__int16 itemID;
	__int8 itemCount;
};

struct PlayerInventory {
	vector<InventoryItem> items;
	int inventorySize = 100;
};

#define cloth0 cloth_hair
#define cloth1 cloth_shirt
#define cloth2 cloth_pants
#define cloth3 cloth_feet
#define cloth4 cloth_face
#define cloth5 cloth_hand
#define cloth6 cloth_back
#define cloth7 cloth_mask
#define cloth8 cloth_necklace
#define cloth9 cloth_ances

struct PlayerInfo {
	bool isIn = false;
	int netID;
	bool haveGrowId = false;
	string tankIDName = "";
	string tankIDPass = "";
	string requestedName = "";
	string rawName = "";
	string displayName = "";
	string country = "";
	int adminLevel = 0;
	string currentWorld = "EXIT";
	bool radio = true;
	int x;
	int y;
	int x1;
	int y1;
	bool isRotatedLeft = false;
	bool RotatedLeft = false;
	string charIP = "";
	bool isUpdating = false;
	bool joinClothesUpdated = false;

	bool hasLogon = false;

	bool taped = false;

	int cloth_hair = 0; // 0
	int cloth_shirt = 0; // 1
	int cloth_pants = 0; // 2
	int cloth_feet = 0; // 3
	int cloth_face = 0; // 4
	int cloth_hand = 0; // 5
	int cloth_back = 0; // 6
	int cloth_mask = 0; // 7
	int cloth_necklace = 0; // 8
	int cloth_ances = 0; // 9

	bool canWalkInBlocks = false; // 1
	bool canDoubleJump = false; // 2
	bool isInvisible = false; // 4
	bool noHands = false; // 8
	bool noEyes = false; // 16
	bool noBody = false; // 32
	bool devilHorns = false; // 64
	bool goldenHalo = false; // 128
	bool isFrozen = false; // 2048
	bool isCursed = false; // 4096
	bool isDuctaped = false; // 8192
	bool haveCigar = false; // 16384
	bool isShining = false; // 32768
	bool isZombie = false; // 65536
	bool isHitByLava = false; // 131072
	bool haveHauntedShadows = false; // 262144
	bool haveGeigerRadiation = false; // 524288
	bool haveReflector = false; // 1048576
	bool isEgged = false; // 2097152
	bool havePineappleFloag = false; // 4194304
	bool haveFlyingPineapple = false; // 8388608
	bool haveSuperSupporterName = false; // 16777216
	bool haveSupperPineapple = false; // 33554432
	bool isGhost = false;
	//bool 
	int skinColor = 0x8295C3FF; //normal SKin color like gt!

	PlayerInventory inventory;

	long long int lastSB = 0;

	//hacky dropped item stuff :(
	vector<ItemSharedUID> item_uids;
	int last_uid = 1;
};
```
 - now need data ready
```cpp
	case ENET_EVENT_TYPE_CONNECT:
			{
				//event.peer->data = new PlayerInfo;
				char clientConnection[16];
				enet_address_get_host_ip(&peer->address, clientConnection, 16);
				((PlayerInfo*)(peer->data))->charIP = clientConnection;
				sendData(peer, 1, 0, 0);
			}
```
 - why **sendData(peer, 1, 0, 0);** because we say **Hello** to client with type 1 (credit:iProgramInCpp)
```cpp
void sendData(ENetPeer* peer, int num, char* data, int len)
{
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket* packet = enet_packet_create(0,
		len + 5,
		ENET_PACKET_FLAG_RELIABLE);
	/* Extend the packet so and append the string "foo", so it now */
	/* contains "packetfoo\0"                                      */
	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	memcpy(packet->data, &num, 4);
	if (data != NULL)
	{
		memcpy(packet->data + 4, data, len);
	}
	char zero = 0;
	memcpy(packet->data + 4 + len, &zero, 1);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(server);
}
```
 - lets make switch for messagetype
```cpp
switch (messageType) {
				case 2: //text packet
				{ //commands etc

				}
				case 3: //text packet.
				{// act (join world exit bla bla)

				}
				case 4: //packet structure https://github.com/GrowtopiaNoobs/GrowDocs/blob/master/enet_server/packet_type4.md
				{
					//wear / move etc
				}
				case 5: //unknown
				{

				}
				case 6: //text packet.
				{

				}
				}
```
 - we need to received data true? lets do
```cpp
char* GetTextPointerFromPacket(ENetPacket* packet)
{
	char zero = 0;
	memcpy(packet->data + packet->dataLength - 1, &zero, 1);
	return (char*)(packet->data + 4);
}
```
```cpp
case ENET_EVENT_TYPE_RECEIVE:
			{
				int messageType = GetMessageTypeFromPacket(event.packet);
				cout << to_string(messageType) << endl;
				switch (messageType) {
				case 2: //text packet
				{ //commands etc
					string cch = GetTextPointerFromPacket(event.packet);
					cout << cch << endl;
				}
				...
```
 - case 3 has login request so fill the case 3
 - New Library **#include sstream** for stringstream
```cpp
case 3: //text packet.
				{// act (join world exit bla bla)
					stringstream ss(GetTextPointerFromPacket(event.packet));
					string to;
					bool isJoinReq = false;

					while (getline(ss, to, '\n')) {
						string id = to.substr(0, to.find("|"));
						string act = to.substr(to.find("|") + 1, to.length() - to.find("|") - 1);
						if (id == "name" && isJoinReq)
						{
#ifdef TOTAL_LOG
							cout << "Entering some world..." << endl
#endif
						}
						if (id == "action")
						{

							if (act == "join_request")
							{
								isJoinReq = true;
							}
							if (act == "quit_to_exit")
							{
								//sendPlayerLeave(peer, (PlayerInfo*)(event.peer->data));
								((PlayerInfo*)(peer->data))->currentWorld = "EXIT";
								//sendWorldOffers(peer);

							}
							if (act == "quit")
							{
								enet_peer_disconnect_later(peer, 0);
							}
						}
					}
					break;
				}
```
 - we need the authentica(login)
 - we need onsuperlogin, items.dat, coredata etc. lets do
```cpp
int itemdathash;
	std::ifstream file("items.dat", std::ios::binary | std::ios::ate);
	itemsDatSize = file.tellg();
	itemsDat = new BYTE[60 + itemsDatSize];
	string asdf = "0400000010000000FFFFFFFF000000000800000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(itemsDat + (i / 2), &x, 1);
		if (asdf.length() > 60 * 2) throw 0;
	}
	memcpy(itemsDat + 56, &itemsDatSize, 4);
	file.seekg(0, std::ios::beg);

	if (file.read((char*)(itemsDat + 60), itemsDatSize))
	{
		uint8_t* pData;
		int size = 0;
		const char filename[] = "items.dat";
		size = filesize(filename);
		pData = getA((string)filename, &size, false, false);
		cout << "Updating items data success! Hash: " << HashString((unsigned char*)pData, size) << endl;
		itemdathash = HashString((unsigned char*)pData, size);
		file.close();
	}
	else {
		cout << "Updating item data failed!" << endl;
	}
	buildItemsDatabase();
```
```cpp
void buildItemsDatabase()
{
	int current = -1;
	std::ifstream infile("config/CoreData.txt");
	for (std::string line; getline(infile, line);)
	{
		if (line.length() > 8 && line[0] != '/' && line[1] != '/')
		{
			vector<string> ex = explode("|", line);
			ItemDefinition def;
			def.id = atoi(ex[0].c_str());
			def.name = ex[1];
			def.rarity = atoi(ex[2].c_str());
			string gay = ex[3];
			if (gay == "MultiFacing") {
				def.MultiFacing = ex[3];
			}
			else if (gay == "MultiFacing, Wrenchable") {
				def.MultiFacing = "MultiFacting";
			}
			string bt = ex[4];
			if (bt == "Foreground_Block") {
				def.blockType = BlockTypes::FOREGROUND;
			}
			else if (bt == "Seed") {
				def.blockType = BlockTypes::SEED;
			}
			else if (bt == "Consummable") {
				def.blockType = BlockTypes::CONSUMABLE;
			}
			else if (bt == "Pain_Block") {
				def.blockType = BlockTypes::PAIN_BLOCK;
			}
			else if (bt == "Main_Door") {
				def.blockType = BlockTypes::MAIN_DOOR;
			}
			else if (bt == "Bedrock") {
				def.blockType = BlockTypes::BEDROCK;
			}
			else if (bt == "Door") {
				def.blockType = BlockTypes::DOOR;
			}
			else if (bt == "Fist") {
				def.blockType = BlockTypes::FIST;
			}
			else if (bt == "Sign") {
				def.blockType = BlockTypes::SIGN;
			}
			else if (bt == "Background_Block") {
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Sheet_Music") {
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Wrench") {
				def.blockType = BlockTypes::WRENCH;
			}
			else if (bt == "Checkpoint") {
				def.blockType = BlockTypes::CHECKPOINT;
			}
			else if (bt == "Lock") {
				def.blockType = BlockTypes::LOCK;
			}
			else if (bt == "Gateway") {
				def.blockType = BlockTypes::GATEWAY;
			}
			else if (bt == "Clothing") {
				def.blockType = BlockTypes::CLOTHING;
			}
			else if (bt == "Platform") {
				def.blockType = BlockTypes::PLATFORM;
			}
			else if (bt == "SFX_Foreground") {
				def.blockType = BlockTypes::SFX_FOREGROUND;
			}
			else if (bt == "Gems") {
				def.blockType = BlockTypes::GEMS;
			}
			else if (bt == "Toggleable_Foreground") {
				def.blockType = BlockTypes::TOGGLE_FOREGROUND;
			}
			else if (bt == "Treasure") {
				def.blockType = BlockTypes::TREASURE;
			}
			else if (bt == "Deadly_Block") {
				def.blockType = BlockTypes::DEADLY;
			}
			else if (bt == "Trampoline_Block") {
				def.blockType = BlockTypes::TRAMPOLINE;
			}
			else if (bt == "Animated_Foreground_Block") {
				def.blockType = BlockTypes::ANIM_FOREGROUND;
			}
			else if (bt == "Portal") {
				def.blockType = BlockTypes::PORTAL;
			}
			else if (bt == "Random_Block") {
				def.blockType = BlockTypes::RANDOM_BLOCK;
			}
			else if (bt == "Bouncy") {
				def.blockType = BlockTypes::BOUNCY;
			}
			else if (bt == "Chest") {
				def.blockType = BlockTypes::CHEST;
			}
			else if (bt == "Switch_Block") {
				def.blockType = BlockTypes::SWITCH_BLOCK;
			}
			else if (bt == "Magic_Egg") {
				def.blockType = BlockTypes::MAGIC_EGG;
			}
			else if (bt == "Mailbox") {
				def.blockType = BlockTypes::MAILBOX;
			}
			else if (bt == "Bulletin_Board") {
				def.blockType = BlockTypes::BULLETIN_BOARD;
			}
			else if (bt == "Faction") {
				def.blockType = BlockTypes::FACTION;
			}
			else if (bt == "Component") {
				def.blockType = BlockTypes::COMPONENT;
			}
			else if (bt == "Weather_Machine") {
				def.blockType = BlockTypes::WEATHER;
			}
			else {
				def.blockType = BlockTypes::UNKNOWN;
			}
			def.breakHits = atoi(ex[7].c_str());
			def.growTime = atoi(ex[8].c_str());
			string cl = ex[9];
			if (cl == "None") {
				def.clothType = ClothTypes::NONE;
			}
			else if (cl == "Hat") {
				def.clothType = ClothTypes::HAIR;
			}
			else if (cl == "Shirt") {
				def.clothType = ClothTypes::SHIRT;
			}
			else if (cl == "Pants") {
				def.clothType = ClothTypes::PANTS;
			}
			else if (cl == "Feet") {
				def.clothType = ClothTypes::FEET;
			}
			else if (cl == "Face") {
				def.clothType = ClothTypes::FACE;
			}
			else if (cl == "Hand") {
				def.clothType = ClothTypes::HAND;
			}
			else if (cl == "Back") {
				def.clothType = ClothTypes::BACK;
			}
			else if (cl == "Hair") {
				def.clothType = ClothTypes::MASK;
			}
			else if (cl == "Chest") {
				def.clothType = ClothTypes::NECKLACE;
			}
			else if (cl == "Ances") {
				def.clothType = ClothTypes::ANCES;
			}
			else {
				def.clothType = ClothTypes::NONE;
			}

			if (++current != def.id)
			{
				cout << "Critical error! Unordered database at item " << std::to_string(current) << "/" << std::to_string(def.id) << "!" << endl;
			}

			itemDefs.push_back(def);
		}
	}
	int current = -1;
	std::ifstream infile("Descriptions.txt");
	for (std::string line; getline(infile, line);)
	{
		if (line.length() > 3 && line[0] != '/' && line[1] != '/')
		{
			vector<string> ex = explode("|", line);
			ItemDefinition def;
			if (atoi(ex[0].c_str()) + 1 < itemDefs.size())
			{
				itemDefs.at(atoi(ex[0].c_str())).description = ex[1];
				if (!(atoi(ex[0].c_str()) % 2))
					itemDefs.at(atoi(ex[0].c_str()) + 1).description = "This is a tree.";
			}
		}
	}
}
```
 - New Library **#include "somevoids"** for better code
```cpp
struct gamepacket_t
{
private:
	int index = 0;
	int len = 0;
	byte* packet_data = new byte[61];

public:
	gamepacket_t(int delay = 0, int NetID = -1) {

		len = 61;
		int MessageType = 0x4;
		int PacketType = 0x1;
		int CharState = 0x8;

		memset(packet_data, 0, 61);
		memcpy(packet_data, &MessageType, 4);
		memcpy(packet_data + 4, &PacketType, 4);
		memcpy(packet_data + 8, &NetID, 4);
		memcpy(packet_data + 16, &CharState, 4);
		memcpy(packet_data + 24, &delay, 4);
	};
	~gamepacket_t() {
		delete[] packet_data;
	}

	void Insert(string a) {
		byte* data = new byte[len + 2 + a.length() + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x2;
		int str_len = a.length();
		memcpy(data + len + 2, &str_len, 4);
		memcpy(data + len + 6, a.data(), str_len);
		len = len + 2 + a.length() + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(int a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x9;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(unsigned int a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x5;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a) {
		byte* data = new byte[len + 2 + 4];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x1;
		memcpy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a, float b) {
		byte* data = new byte[len + 2 + 8];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x3;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		len = len + 2 + 8;
		index++;
		packet_data[60] = (byte)index;
	}
	void Insert(float a, float b, float c) {
		byte* data = new byte[len + 2 + 12];
		memcpy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x4;
		memcpy(data + len + 2, &a, 4);
		memcpy(data + len + 6, &b, 4);
		memcpy(data + len + 10, &c, 4);
		len = len + 2 + 12;
		index++;
		packet_data[60] = (byte)index;
	}
	void CreatePacket(ENetPeer* peer) {
		ENetPacket* packet = enet_packet_create(packet_data, len, 1);
		enet_peer_send(peer, 0, packet);
	}
};
```
```cpp
#pragma once
uint32_t HashString(unsigned char* str, int len)
{
	if (!str) return 0;

	unsigned char* n = (unsigned char*)str;
	uint32_t acc = 0x55555555;

	if (len == 0)
	{
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			acc = (acc >> 27) + (acc << 5) + *n++;
		}
	}
	return acc;

}

int ch2n(char x)
{
	switch (x)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		break;
	}
}
std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

unsigned char* getA(string fileName, int* pSizeOut, bool bAddBasePath, bool bAutoDecompress)
{
	unsigned char* pData = NULL;
	FILE* fp = fopen(fileName.c_str(), "rb");
	if (!fp)
	{
		cout << "File not found" << endl;
		if (!fp) return NULL;
	}

	fseek(fp, 0, SEEK_END);
	*pSizeOut = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pData = (unsigned char*)new unsigned char[((*pSizeOut) + 1)];
	if (!pData)
	{
		printf("Out of memory opening %s?", fileName.c_str());
		return 0;
	}
	pData[*pSizeOut] = 0;
	fread(pData, *pSizeOut, 1, fp);
	fclose(fp);

	return pData;
}

vector<string> explode(const string& delimiter, const string& str)
{
	vector<string> arr;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;//no change

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}
```
 - we need check isupdateing
```cpp
case ENET_EVENT_TYPE_RECEIVE:
			{
				if (((PlayerInfo*)(peer->data))->isUpdating)
				{
					cout << "packet drop" << endl;
					continue;
				}
```
 - i added gamepacket bcuz more modern TO packetvoids.h
```cpp
struct GamePacket
{
	BYTE* data;
	int len;
	int indexes;
};

int ch2n(char x)
{
	switch (x)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		break;
	}
}


GamePacket appendFloat(GamePacket p, float val)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 1;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

GamePacket appendFloat(GamePacket p, float val, float val2)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + 8];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 3;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	p.len = p.len + 2 + 8;
	p.indexes++;
	return p;
}

GamePacket appendFloat(GamePacket p, float val, float val2, float val3)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + 12];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 4;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	memcpy(n + p.len + 10, &val3, 4);
	p.len = p.len + 2 + 12;
	p.indexes++;
	return p;
}

GamePacket appendInt(GamePacket p, int val)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 9;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

GamePacket appendIntx(GamePacket p, int val)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 5;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

GamePacket appendString(GamePacket p, string str)
{
	//p.data[56] += 1;
	BYTE* n = new BYTE[p.len + 2 + str.length() + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 2;
	int sLen = str.length();
	memcpy(n + p.len + 2, &sLen, 4);
	memcpy(n + p.len + 6, str.c_str(), sLen);
	p.len = p.len + 2 + str.length() + 4;
	p.indexes++;
	return p;
}

GamePacket createPacket()
{
	BYTE* data = new BYTE[61];
	string asdf = "0400000001000000FFFFFFFF00000000080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
		if (asdf.length() > 61 * 2) throw 0;
	}
	GamePacket packet;
	packet.data = data;
	packet.len = 61;
	packet.indexes = 0;
	return packet;
}

GamePacket packetEnd(GamePacket p)
{
	BYTE* n = new BYTE[p.len + 1];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	char zero = 0;
	memcpy(p.data + p.len, &zero, 1);
	p.len += 1;
	*(int*)(p.data + 56) = p.indexes;//p.len-60;//p.indexes;
	*(BYTE*)(p.data + 60) = p.indexes;
	//*(p.data + 57) = p.indexes;
	return p;
}
```
 - we need packettype 4 (this fking take my +15day, **BIG Thanks iProgramİnCpp** for motivation)
```cpp
				case 4: //packet structure https://github.com/GrowtopiaNoobs/GrowDocs/blob/master/enet_server/packet_type4.md
				{
					//wear / move etc
					BYTE* tankUpdatePacket = /*error*/GetStructPointerFromTankPacket(event.packet);

					if (tankUpdatePacket)
					{
						/*error*/PlayerMoving* pMov = /*error*/unpackPlayerMoving(tankUpdatePacket);
					}
				}
```
 - we need add GetStructPointerFromTankPacket and unpackPlayerMoving to somevoids.h 
 - we need add PlayerMoving structes.h
```cpp
/*somevoids.h*/
BYTE* GetStructPointerFromTankPacket(ENetPacket* packet)
{
	unsigned int packetLenght = packet->dataLength;
	BYTE* result = NULL;
	if (packetLenght >= 0x3C)
	{
		BYTE* packetData = packet->data;
		result = packetData + 4;
		if (*(BYTE*)(packetData + 16) & 8)
		{
			if (packetLenght < *(int*)(packetData + 56) + 60)
			{
				cout << "[!] Packet too small for extended packet to be valid" << endl;
				cout << "[!] Sizeof float is 4.  TankUpdatePacket size: 56" << endl;
				result = 0;
			}
		}
		else
		{
			int zero = 0;
			memcpy(packetData + 56, &zero, 4);
		}
	}
	return result;
}

PlayerMoving* unpackPlayerMoving(BYTE* data)
{
	PlayerMoving* dataStruct = new PlayerMoving;
	dataStruct->packetType = *(int*)(data);
	dataStruct->netID = *(int*)(data + 4);
	dataStruct->characterState = *(int*)(data + 12);
	dataStruct->plantingTree = *(int*)(data + 20);
	dataStruct->x = *(float*)(data + 24);
	dataStruct->y = *(float*)(data + 28);
	dataStruct->XSpeed = *(float*)(data + 32);
	dataStruct->YSpeed = *(float*)(data + 36);
	dataStruct->punchX = *(int*)(data + 44);
	dataStruct->punchY = *(int*)(data + 48);
	return dataStruct;
}
```
#### For people using C++17 and higher:
```cpp
/*somevoids.h*/
char* GetStructPointerFromTankPacket(ENetPacket* packet)
{
	unsigned int packetLenght = packet->dataLength;
	BYTE* result = NULL;
	if (packetLenght >= 0x3C)
	{
		BYTE* packetData = packet->data;
		result = packetData + 4;
		if (*(BYTE*)(packetData + 16) & 8)
		{
			if (packetLenght < *(int*)(packetData + 56) + 60)
			{
				cout << "[!] Packet too small for extended packet to be valid" << endl;
				cout << "[!] Sizeof float is 4.  TankUpdatePacket size: 56" << endl;
				result = 0;
			}
		}
		else
		{
			int zero = 0;
			memcpy(packetData + 56, &zero, 4);
		}
	}
	char* cresult = (char*)result;
	return cresult;
}

PlayerMoving* unpackPlayerMoving(char* data)
{
	PlayerMoving* dataStruct = new PlayerMoving;
	dataStruct->packetType = *(int*)(data);
	dataStruct->netID = *(int*)(data + 4);
	dataStruct->characterState = *(int*)(data + 12);
	dataStruct->plantingTree = *(int*)(data + 20);
	dataStruct->x = *(float*)(data + 24);
	dataStruct->y = *(float*)(data + 28);
	dataStruct->XSpeed = *(float*)(data + 32);
	dataStruct->YSpeed = *(float*)(data + 36);
	dataStruct->punchX = *(int*)(data + 44);
	dataStruct->punchY = *(int*)(data + 48);
	return dataStruct;
}
```
```cpp
/*structes.h*/
struct PlayerMoving {
	int packetType;
	int netID;
	float x;
	float y;
	int characterState;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int punchX;
	int punchY;
	int secondnetID;
};
```
 - lets edit case 4
 - we need add "sendPData", "updateAllClothes", "sendCollect", "getPlyersWorld", "getItemDef", "sendPlayerLeave", "sendWorldOffers", "sendState", "sendClothes", "sendTileUpdate", "isHere", "SendPacketRaw", "packPlayerMoving", "worldDB"(class) umm lets start to add in somevoids.h
 - i added sendPData, updateAllClothes, getPlyersWorld, isHere, SendPacketRaw, packPlayerMoving, worldDB
```cpp
/*somevoids.h*/
BYTE* packPlayerMoving(PlayerMoving* dataStruct)
{
	BYTE* data = new BYTE[64];
	for (int i = 0; i < 64; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}

bool isHere(ENetPeer* peer1, ENetPeer* peer2)
{
	return ((PlayerInfo*)(peer1->data))->currentWorld == ((PlayerInfo*)(peer2->data))->currentWorld;
}

void SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
{
	ENetPacket* p;

	if (peer) // check if we have it setup
	{
		if (a1 == 4 && *((BYTE*)packetData + 12) & 8)
		{
			p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
			int four = 4;
			memcpy(p->data, &four, 4);
			memcpy((char*)p->data + 4, packetData, packetDataSize);
			memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
			enet_peer_send(peer, 0, p);

		}
		else
		{
			if (a1 == 192) {
				a1 = 4;
				p = enet_packet_create(0, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
			else {
				p = enet_packet_create(0, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);


			}
		}
	}

	delete packetData;
}

void sendPData(ENetPeer* peer, PlayerMoving* data)
{
	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				data->netID = ((PlayerInfo*)(peer->data))->netID;

				SendPacketRaw(4, packPlayerMoving(data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

void updateAllClothes(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			gamepacket_t p(0, ((PlayerInfo*)(peer->data))->netID);
			p.Insert("OnSetClothing");
			p.Insert(((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants);
			p.Insert(((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand);
			p.Insert(((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace);
			p.Insert(((PlayerInfo*)(peer->data))->skinColor);
			p.Insert(((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f);
			p.CreatePacket(currentPeer);

			gamepacket_t p2(0, ((PlayerInfo*)(peer->data))->netID);
			p2.Insert("OnSetClothing");
			p2.Insert(((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants);
			p2.Insert(((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand);
			p2.Insert(((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace);
			p2.Insert(((PlayerInfo*)(peer->data))->skinColor);
			p2.Insert(((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f);
			p2.CreatePacket(peer);
		}
	}
}

WorldInfo* getPlyersWorld(ENetPeer* peer)
{
	try {
		return worldDB.get2(((PlayerInfo*)(peer->data))->currentWorld).ptr;
	}
	catch (int e) {
		return NULL;
	}
}
```
```cpp
/*structes.h*/
WorldInfo generateWorld(string name, int width, int height)
{
	WorldInfo world;
	world.name = name;
	world.width = width;
	world.height = height;
	world.items = new WorldItem[world.width * world.height];
	for (int i = 0; i < world.width * world.height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50)) { world.items[i].foreground = 10; }
		else if (i >= 3700 && i < 5400) {
			if (i > 5000) {
				if (i % 7 == 0) { world.items[i].foreground = 4; }
				else { world.items[i].foreground = 2; }
			}
			else { world.items[i].foreground = 2; }
		}
		else if (i >= 5400) { world.items[i].foreground = 8; }
		if (i >= 3700)
			world.items[i].background = 14;
		if (i == 3650)
			world.items[i].foreground = 6;
		else if (i >= 3600 && i < 3700)
			world.items[i].foreground = 0; //fixed the grass in the world!
		if (i == 3750)
			world.items[i].foreground = 8;
	}
	return world;
}

struct AWorld {
	WorldInfo* ptr;
	WorldInfo info;
	int id;
};

class WorldDB {
public:
	WorldInfo get(string name);
	AWorld get2(string name);
	void flush(WorldInfo info);
	void flush2(AWorld info);
	void save(AWorld info);
	void saveAll();
	void saveRedundant();
	vector<WorldInfo> getRandomWorlds();
	WorldDB();
private:
	vector<WorldInfo> worlds;
};

WorldDB::WorldDB() {
	// Constructor
}

namespace packet {
	//removed
}

string getStrUpper(string txt) {
	string ret;
	for (char c : txt) ret += toupper(c);
	return ret;
}

AWorld WorldDB::get2(string name) {
	if (worlds.size() > 200) {
#ifdef TOTAL_LOG
		cout << "Saving redundant worlds!" << endl;
#endif
		saveRedundant();
#ifdef TOTAL_LOG
		cout << "Redundant worlds are saved!" << endl;
#endif
	}
	AWorld ret;
	name = getStrUpper(name);
	if (name.length() < 1) throw 1; // too short name
	for (char c : name) {
		if ((c < 'A' || c>'Z') && (c < '0' || c>'9'))
			throw 2; // wrong name
	}
	if (name == "EXIT") {
		throw 3;
	}
	if (name == "CON" || name == "PRN" || name == "AUX" || name == "NUL" || name == "COM1" || name == "COM2" || name == "COM3" || name == "COM4" || name == "COM5" || name == "COM6" || name == "COM7" || name == "COM8" || name == "COM9" || name == "LPT1" || name == "LPT2" || name == "LPT3" || name == "LPT4" || name == "LPT5" || name == "LPT6" || name == "LPT7" || name == "LPT8" || name == "LPT9") throw 3;
	for (int i = 0; i < worlds.size(); i++) {
		if (worlds.at(i).name == name)
		{
			ret.id = i;
			ret.info = worlds.at(i);
			ret.ptr = &worlds.at(i);
			return ret;
		}

	}
	std::ifstream ifs("worlds/" + name + ".json");
	if (ifs.is_open()) {

		json j;
		ifs >> j;
		WorldInfo info;
		info.name = j["name"].get<string>();
		info.width = j["width"];
		info.height = j["height"];
		info.owner = j["owner"].get<string>();
		info.isPublic = j["isPublic"];
		json tiles = j["tiles"];
		int square = info.width * info.height;
		info.items = new WorldItem[square];
		for (int i = 0; i < square; i++) {
			info.items[i].foreground = tiles[i]["fg"];
			info.items[i].background = tiles[i]["bg"];
		}
		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;
	}
	else {
		WorldInfo info = generateWorld(name, 100, 60);

		worlds.push_back(info);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;
	}
	throw 1;
}

WorldInfo WorldDB::get(string name) {

	return this->get2(name).info;
}

void WorldDB::flush(WorldInfo info)
{
	std::ofstream o("worlds/" + info.name + ".json");
	if (!o.is_open()) {
		cout << GetLastError() << endl;
	}
	json j;
	j["name"] = info.name;
	j["width"] = info.width;
	j["height"] = info.height;
	j["owner"] = info.owner;
	j["isPublic"] = info.isPublic;
	json tiles = json::array();
	int square = info.width * info.height;

	for (int i = 0; i < square; i++)
	{
		json tile;
		tile["fg"] = info.items[i].foreground;
		tile["bg"] = info.items[i].background;
		tiles.push_back(tile);
	}
	j["tiles"] = tiles;
	o << j << std::endl;
}

void WorldDB::flush2(AWorld info)
{
	this->flush(info.info);
}

void WorldDB::save(AWorld info)
{
	flush2(info);
	delete info.info.items;
	worlds.erase(worlds.begin() + info.id);
}

void WorldDB::saveAll()
{
	for (int i = 0; i < worlds.size(); i++) {
		flush(worlds.at(i));
		delete[] worlds.at(i).items;
	}
	worlds.clear();
}

vector<WorldInfo> WorldDB::getRandomWorlds() {
	vector<WorldInfo> ret;
	for (int i = 0; i < ((worlds.size() < 10) ? worlds.size() : 10); i++)
	{ // load first four worlds, it is excepted that they are special
		ret.push_back(worlds.at(i));
	}
	// and lets get up to 6 random
	if (worlds.size() > 4) {
		for (int j = 0; j < 6; j++)
		{
			bool isPossible = true;
			WorldInfo world = worlds.at(rand() % (worlds.size() - 4));
			for (int i = 0; i < ret.size(); i++)
			{
				if (world.name == ret.at(i).name || world.name == "EXIT")
				{
					isPossible = false;
				}
			}
			if (isPossible)
				ret.push_back(world);
		}
	}
	return ret;
}

void WorldDB::saveRedundant()
{
	for (int i = 4; i < worlds.size(); i++) {
		bool canBeFree = true;
		ENetPeer* currentPeer;

		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->currentWorld == worlds.at(i).name)
				canBeFree = false;
		}
		if (canBeFree)
		{
			flush(worlds.at(i));
			delete worlds.at(i).items;
			worlds.erase(worlds.begin() + i);
			i--;
		}
	}
}
WorldDB worldDB;
```
```cpp
				case 4: //packet structure https://github.com/GrowtopiaNoobs/GrowDocs/blob/master/enet_server/packet_type4.md
				{
					//wear / move etc
					BYTE* tankUpdatePacket = GetStructPointerFromTankPacket(event.packet);

					if (tankUpdatePacket)
					{
						PlayerMoving* pMov = unpackPlayerMoving(tankUpdatePacket);
						if (((PlayerInfo*)(event.peer->data))->isGhost) {
							((PlayerInfo*)(event.peer->data))->isInvisible = true;
							((PlayerInfo*)(event.peer->data))->x1 = pMov->x;
							((PlayerInfo*)(event.peer->data))->y1 = pMov->y;
							pMov->x = -1000000;
							pMov->y = -1000000;
						}

						switch (pMov->packetType)
						{
						case 0:
							((PlayerInfo*)(event.peer->data))->x = pMov->x;
							((PlayerInfo*)(event.peer->data))->y = pMov->y;
							((PlayerInfo*)(event.peer->data))->isRotatedLeft = pMov->characterState & 0x10;
							sendPData(peer, pMov);
							if (!((PlayerInfo*)(peer->data))->joinClothesUpdated)
							{
								((PlayerInfo*)(peer->data))->joinClothesUpdated = true;
								updateAllClothes(peer);
							}
							break;

						default:
							break;
						}
						PlayerMoving* data2 = unpackPlayerMoving(tankUpdatePacket);
						}
						delete data2;
						delete pMov;
					}
				}
```
![perfect](https://user-images.githubusercontent.com/77299279/136676108-92e662e3-41d2-4b17-9eee-373ca1cca68b.PNG)

 - woah
 - we need left add "sendCollect", "checkForUIDMatch", "getSharedUID", "getItemDef", "sendPlayerLeave", "getPlayersCountInWorld", "sendWorldOffers", umm lets start to add in somevoids.h
```cpp
/*structes.h*/
WorldInfo* getPlyersWorld(ENetPeer* peer)
{
	try {
		return worldDB.get2(((PlayerInfo*)(peer->data))->currentWorld).ptr;
	}
	catch (int e) {
		return NULL;
	}
}

int getSharedUID(ENetPeer* peer, int itemNetID) {
	auto v = ((PlayerInfo*)(peer->data))->item_uids;
	for (auto t = v.begin(); t != v.end(); ++t) {
		if (t->actual_uid == itemNetID) {
			return t->shared_uid;
		}
	}
	return 0;
}

int checkForUIDMatch(ENetPeer* peer, int itemNetID) {
	auto v = ((PlayerInfo*)(peer->data))->item_uids;
	for (auto t = v.begin(); t != v.end(); ++t) {
		if (t->shared_uid == itemNetID) {
			return t->actual_uid;
		}
	}
	return 0;
}

void sendCollect(ENetPeer* peer, int netID, int itemNetID) {
	ENetPeer* currentPeer;
	PlayerMoving data;
	data.packetType = 14;
	data.netID = netID;
	data.plantingTree = itemNetID;
	data.characterState = 0;
	cout << "Request collect: " << std::to_string(itemNetID) << endl;
	WorldInfo* world = getPlyersWorld(peer);
	for (auto m_item = world->droppedItems.begin(); m_item != world->droppedItems.end(); ++m_item) {
		if ((checkForUIDMatch(peer, itemNetID)) == m_item->uid) {
			cout << "Success!" << endl;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer)) {
					data.plantingTree = getSharedUID(currentPeer, m_item->uid);
					BYTE* raw = packPlayerMoving(&data);
					SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
				}
			}
			world->droppedItems.erase(m_item);
			m_item--;
			return;
		}
	}
}

ItemDefinition getItemDef(int id)
{
	if (id < itemDefs.size() && id > -1)
		return itemDefs.at(id);
	throw 0;
	return itemDefs.at(0);
}

int getPlayersCountInWorld(string name)
{
	int count = 0;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (((PlayerInfo*)(currentPeer->data))->currentWorld == name)
			count++;
	}
	return count;
}

void sendPlayerLeave(ENetPeer* peer, PlayerInfo* player)
{
	ENetPeer* currentPeer;
	gamepacket_t p;
	p.Insert("OnRemove");
	p.Insert("netID|" + std::to_string(player->netID) + "\n");
	gamepacket_t p2;
	p2.Insert("OnConsoleMessage");
	p2.Insert("`5<`w" + player->displayName + "`` left, `w" + std::to_string(getPlayersCountInWorld(player->currentWorld) - 1) + "`` others here>``");
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			{
				p.CreatePacket(peer);

				{
					p.CreatePacket(currentPeer);
				}

			}
			{
				p2.CreatePacket(currentPeer);
			}
		}
	}
}

void sendWorldOffers(ENetPeer* peer)
{
	if (!((PlayerInfo*)(peer->data))->isIn) return;
	vector<WorldInfo> worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0) {
		worldOffers += worlds[0].name;
	}

	worldOffers += "\nadd_button|Showing: `wWorlds``|_catselect_|0.6|3529161471|\n";
	/*for (int i = 0; i < worlds.size(); i++) {
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|0.55|3529161471\n";
	}*/
	worldOffers += "add_floater|Groophy|0|0.55|3529161471\n";
	worldOffers += "add_floater|and|0|0.55|3529161471\n";
	worldOffers += "add_floater|iProgramInCpp|0|0.55|3529161471\n";
	packet::requestworldselectmenu(peer, worldOffers);
}
```
 - we need left add "sendState", "getState", "sendClothes", "sendTileUpdate", "sendNothingHappened", umm lets start to add in somevoids.h
```cpp
int getState(PlayerInfo* info) {
	int val = 0;
	val |= info->canWalkInBlocks << 0;
	val |= info->canDoubleJump << 1;
	val |= info->isInvisible << 2;
	val |= info->noHands << 3;
	val |= info->noEyes << 4;
	val |= info->noBody << 5;
	val |= info->devilHorns << 6;
	val |= info->goldenHalo << 7;
	val |= info->isFrozen << 11;
	val |= info->isCursed << 12;
	val |= info->isDuctaped << 13;
	val |= info->haveCigar << 14;
	val |= info->isShining << 15;
	val |= info->isZombie << 16;
	val |= info->isHitByLava << 17;
	val |= info->haveHauntedShadows << 18;
	val |= info->haveGeigerRadiation << 19;
	val |= info->haveReflector << 20;
	val |= info->isEgged << 21;
	val |= info->havePineappleFloag << 22;
	val |= info->haveFlyingPineapple << 23;
	val |= info->haveSuperSupporterName << 24;
	val |= info->haveSupperPineapple << 25;
	return val;
}

void sendState(ENetPeer* peer) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	ENetPeer* currentPeer;
	int state = getState(info);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = 0; // animation
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = 0x808000; // placing and breking
			memcpy(raw + 1, &var, 3);
			float waterspeed = 125.0f;
			memcpy(raw + 16, &waterspeed, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

void sendClothes(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	gamepacket_t p(0, ((PlayerInfo*)(peer->data))->netID);
	p.Insert("OnSetClothing");
	p.Insert(((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants);
	p.Insert(((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand);
	p.Insert(((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace);
	p.Insert(((PlayerInfo*)(peer->data))->skinColor);
	p.Insert(((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			p.CreatePacket(currentPeer);
		}

	}
}

void sendNothingHappened(ENetPeer* peer, int x, int y) {
	PlayerMoving data;
	data.netID = ((PlayerInfo*)(peer->data))->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
	if (tile > itemDefs.size()) {
		return;
	}
	PlayerMoving data;
	//data.packetType = 0x14;
	data.packetType = 0x3;

	//data.characterState = 0x924; // animation
	data.characterState = 0x0; // animation
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = causedBy;
	data.plantingTree = tile;

	WorldInfo* world = getPlyersWorld(peer);

	if (getItemDef(tile).blockType == BlockTypes::CONSUMMABLE) return;

	if (world == NULL) return;
	if (x<0 || y<0 || x>world->width - 1 || y>world->height - 1 || tile > itemDefs.size()) return; // needs - 1
	sendNothingHappened(peer, x, y);
	//if (!isSuperAdmin(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass))
	{
		if (world->items[x + (y * world->width)].foreground == 6 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 3760)
			return;
		if (tile == 6 || tile == 8 || tile == 3760 || tile == 6864)
			return;
	}
	if (world->name == "ADMIN"/* && !getAdminLevel(((PlayerInfo*)(peer->data))->rawName, ((PlayerInfo*)(peer->data))->tankIDPass)*/)
	{
		if (world->items[x + (y * world->width)].foreground == 758)
			//sendRoulete(peer, x, y);
		return;
	}
	if (world->name != "ADMIN") {
		if (world->owner != "") {
			if (((PlayerInfo*)(peer->data))->rawName == world->owner) {
				// WE ARE GOOD TO GO
				if (tile == 32) {
					if (world->items[x + (y * world->width)].foreground == 242 or world->items[x + (y * world->width)].foreground == 202 or world->items[x + (y * world->width)].foreground == 204 or world->items[x + (y * world->width)].foreground == 206 or world->items[x + (y * world->width)].foreground == 2408 or world->items[x + (y * world->width)].foreground == 5980 or world->items[x + (y * world->width)].foreground == 2950 or world->items[x + (y * world->width)].foreground == 5814 or world->items[x + (y * world->width)].foreground == 4428 or world->items[x + (y * world->width)].foreground == 1796 or world->items[x + (y * world->width)].foreground == 4802 or world->items[x + (y * world->width)].foreground == 4994 or world->items[x + (y * world->width)].foreground == 5260 or world->items[x + (y * world->width)].foreground == 7188)
					{
						packet::dialog(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wShould this world be publicly breakable?``|left|242|\n\nadd_spacer|small|\nadd_button_with_icon|worldPublic|Public|noflags|2408||\nadd_button_with_icon|worldPrivate|Private|noflags|202||\nadd_spacer|small|\nadd_quick_exit|\nadd_button|chc0|Close|noflags|0|0|\nend_dialog|wl_edit|||"); // Added dialog name
					}
				}
			}
			else if (world->isPublic)
			{
				if (world->items[x + (y * world->width)].foreground == 242)
				{
					return;
				}
			}
			else {
				return;
			}
			if (tile == 242) {
				return;
			}
		}
	}
	if (tile == 32) {
		// TODO
		return;
	}
	if (tile == 822) {
		world->items[x + (y * world->width)].water = !world->items[x + (y * world->width)].water;
		return;
	}
	if (tile == 3062)
	{
		world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
		return;
	}
	if (tile == 1866)
	{
		world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
		return;
	}
	ItemDefinition def;
	try {
		def = getItemDef(tile);
		if (def.blockType == BlockTypes::CLOTHING) return;
	}
	catch (int e) {
		def.breakHits = 4;
		def.blockType = BlockTypes::UNKNOWN;
#ifdef TOTAL_LOG
		cout << "Ugh, unsupported item " << tile << endl;
#endif
	}

	if (tile == 18) {
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		//data.netID = -1;
		int tool = ((PlayerInfo*)(peer->data))->cloth_hand;
		data.packetType = 0x8;
		data.plantingTree = (tool == 98 || tool == 1438 || tool == 4956) ? 8 : 6;
		int block = world->items[x + (y * world->width)].foreground > 0 ? world->items[x + (y * world->width)].foreground : world->items[x + (y * world->width)].background;
		//if (world->items[x + (y*world->width)].foreground == 0) return;
		using namespace std::chrono;
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 4000)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 0; // TODO
			if (world->items[x + (y * world->width)].foreground == 758)
			{
				//sendRoulete(peer, x, y);
			}
		}
		if (y < world->height)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel += (int)((tool == 98 || tool == 1438 || tool == 4956) ? 8 : 6); // TODO
		}


		if (y < world->height && world->items[x + (y * world->width)].breakLevel >= getItemDef(block).breakHits * 6) { // TODO
			data.packetType = 0x3;// 0xC; // 0xF // World::HandlePacketTileChangeRequest
			data.plantingTree = 18;
			world->items[x + (y * world->width)].breakLevel = 0;
			if (world->items[x + (y * world->width)].foreground != 0)
			{
				if (world->items[x + (y * world->width)].foreground == 242)
				{
					world->owner = "";
					world->isPublic = false;
				}
				world->items[x + (y * world->width)].foreground = 0;
			}
			else {
				world->items[x + (y * world->width)].background = 6864;
			}

		}


	}
	else {
		for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
		{
			if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == tile)
			{
				if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > 1)
				{
					((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount--;
				}
				else {
					((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);

				}
			}
		}
		if (def.blockType == BlockTypes::BACKGROUND)
		{
			world->items[x + (y * world->width)].background = tile;
		}
		else {
			if (world->items[x + (y * world->width)].foreground != 0)return;
			world->items[x + (y * world->width)].foreground = tile;
			if (tile == 242) {
				world->owner = ((PlayerInfo*)(peer->data))->rawName;
				world->isPublic = false;
				ENetPeer* currentPeer;

				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer)) {
						packet::consolemessage(peer, "`3[`w" + world->name + " `ohas been World Locked by `2" + ((PlayerInfo*)(peer->data))->displayName + "`3]");
					}
				}
			}

		}

		world->items[x + (y * world->width)].breakLevel = 0;
	}

	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);

		//cout << "Tile update at: " << data2->punchX << "x" << data2->punchY << endl;
	}
}
```
 - and yeah... nothing not changed bcuz we need edit case 2
```cpp
if (pStr.substr(0, 17) == "action|enter_game" && !((PlayerInfo*)(event.peer->data))->isIn)
					{
#ifdef TOTAL_LOG
						cout << "And we are in!" << endl;
#endif
						ENetPeer* currentPeer;
						((PlayerInfo*)(event.peer->data))->isIn = true;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
								continue;

							GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "Player `o" + ((PlayerInfo*)(event.peer->data))->tankIDName + "`o just entered the game..."));
							ENetPacket * packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(currentPeer, 0, packet);

							enet_host_flush(server);
							delete p.data;
						}
						sendWorldOffers(peer);

						gamepacket_t  p;
						p.Insert("OnEmoticonDataChanged");
						p.Insert(201560520);
						p.Insert("(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ģ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&");
						p.CreatePacket(peer);


						packet::consolemessage(peer, "Server made by Groophy, Thanks you iProgramInCpp for motivation and help.");
						/*gamepacket_t  p;
						p.Insert("OnEmoticonDataChanged");
						p.CreatePacket(peer);*/

						PlayerInventory inventory;
						for (int i = 0; i < 200; i++)
						{
							InventoryItem it;
							it.itemID = (i * 2) + 2;
							it.itemCount = 200;
							inventory.items.push_back(it);
						}
						((PlayerInfo*)(event.peer->data))->inventory = inventory;

						{
							//news
							/*GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wNews``|left|5016|\nend_dialog|gazette||OK|"));
							ENetPacket* packet = enet_packet_create(p.data,
								p.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet);
							delete p.data;*/
						}
					}
```
 - perfect

![yesss](https://user-images.githubusercontent.com/77299279/136676670-febcc040-ca19-4f4d-a1f7-a75ee8914e34.PNG)

 - its custom offer world
 - if you want auto world sendworldoffer to
```cpp
void sendWorldOffers(ENetPeer* peer)
{
	if (!((PlayerInfo*)(peer->data))->isIn) return;
	vector<WorldInfo> worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0) {
		worldOffers += worlds[0].name;
	}

	worldOffers += "\nadd_button|Showing: `wWorlds``|_catselect_|0.6|3529161471|\n";
	for (int i = 0; i < worlds.size(); i++) {
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|0.55|3529161471\n";
	}
	packet::requestworldselectmenu(peer, worldOffers);
}
```
 - well?
