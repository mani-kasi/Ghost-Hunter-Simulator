#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99
#define C_OK                0
#define C_NOK              -1

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

typedef struct {
  GhostClassType ghostType;
  struct Room *currRoom;
  int boredomTimer;
}GhostType;

typedef struct {
  EvidenceClassType evidenceType;
  float value;
}EvidenceType;

typedef struct RoomNode{
   struct Room *room;
   struct RoomNode *next;
 } RoomNodeType;

 typedef struct Node {
   EvidenceType *data;
   struct Node *next;
 } NodeType;

 typedef struct RoomNodeList{
   RoomNodeType *head;
   int size;
 } RoomNodeListType;

 typedef struct EvidenceList{
   NodeType *head;
 } EvidenceListType;

typedef struct Hunter{
  struct Room* currRoom;
  EvidenceClassType equipment;
  EvidenceListType currEvidence;
  char name[MAX_STR];
  int fear;
  int boredomTimer;
}HunterType;

typedef struct HunterArray{
  HunterType* hunters[MAX_HUNTERS];
  int size;
}HunterArrayType;

typedef struct Room{
  char name[MAX_STR];
  GhostType *ghost;
  HunterArrayType huntersList;
  RoomNodeListType connectedRooms;
  EvidenceListType roomEvidence;
} RoomType;

 typedef struct Building{
   GhostType *ghost;
   HunterArrayType huntersList;
   RoomNodeListType roomList;
 } BuildingType;



int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms

//Initialize a room
void initRoom(RoomType**, char*);
//adds a room to a room list
void appendRoom(RoomNodeListType*, RoomNodeType*);
//takes in two rooms and connects them together
void connectRooms(RoomNodeListType*, RoomType*);
//clean up given room list
void cleanUpRoomList(RoomNodeListType*);
//get random room in room list;
struct Room* getRandomRoom(RoomNodeListType*);

// Initialize an evidence
void initEvidence(EvidenceType**, EvidenceClassType, float);
//Initialize an evidence list
void initEvidenceList(EvidenceListType*);
//cleans up an evidence list
void cleanUpEvidenceList(EvidenceListType*);
//removes a piece of evidence from a room
void removeRoomEvidence(EvidenceListType*, EvidenceType*);
//adds evidence to an evidence lis#t
void addEvidence(EvidenceListType*, EvidenceType*);
//share evidence of ghostly data between two hunters
void shareEvidence(EvidenceListType*, RoomType*, HunterType*);
//makes hunter checks if evidence #in a room and collects evidence if there is
void checkAndCollectEvidence(HunterType*);
//makes a ghost drop evidence in current Room
void dropEvidence(GhostType*);
//makes a random standard evidence data depending on given type and adds it to hunter evidence list
void createStandardEvidence(EvidenceListType*, EvidenceClassType);
//randomly generators a type of evidence depending on ghost
EvidenceClassType randomEvidence(GhostClassType);
//randomly generators a random value depending on evidence type
float randomGhostEvidenceValue(EvidenceClassType);
//returns a string of the evidence types
char* evidenceString(EvidenceClassType);


//Initialize a ghost
void initGhost(GhostType**, GhostClassType, RoomType*);
//Generates an action for a ghost randomly (unless hunter is in the same room, then ghost stays)
void ghostAction(GhostType*, HunterArrayType*);
//gives a string of the ghost type
char* ghostTypeString(GhostClassType);
//check if the given evidence is ghostly data or not
int isGhostlyData(EvidenceType*);
//moves ghost to adjacent room and updates room's ghost pointer
void ghostMoveRooms(GhostType*);


//Initialize hunter
void initHunter(HunterType**, char*, RoomType*, EvidenceClassType);
//randomly generated a action for a given hunter
void hunterAction(HunterType*, HunterArrayType*);
//add hunter to hunter array
void addHunter(HunterArrayType*, HunterType*);
//cleans up hunter array
void cleanUpHunterArray(HunterArrayType*);
//gives a string of the speculatedGhost using the given hunter's data
char* getSpeculatedGhost(HunterArrayType*);
//moves hunter to adjacent room and update room's hunters HunterArray
void hunterMoveRooms(HunterType*);
//check if a hunter has 3 pieces of ghostly data and returns a C_OK or C_NOK accordingly
int checkEvidenceCollected(HunterType*);
//increases fear and reset board timer if in same room as ghostType
void sameRoomAsGhost(HunterType*);

// Initialize building
void initBuilding(BuildingType**);
//cleans up building
void cleanUpBuilding(BuildingType*);
//prints final results of building after all threading is done for ghost and hunters.
void printFinalResults(BuildingType *);
