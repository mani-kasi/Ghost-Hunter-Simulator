#include "defs.h"

int main(int argc, char *argv[])
{
  // Initialize a random seed for the random number generators
  srand(time(NULL));

  char nameH1[MAX_STR];
  char nameH2[MAX_STR];
  char nameH3[MAX_STR];
  char nameH4[MAX_STR];
  printf("\nPlease enter the first hunter name: ");
  scanf("%s", nameH1);
  printf("\nPlease enter the second hunter name: ");
  scanf("%s", nameH2);
  printf("\nPlease enter the third hunter name: ");
  scanf("%s", nameH3);
  printf("\nPlease enter the fourth hunter name: ");
  scanf("%s", nameH4);

  BuildingType* building;
  initBuilding(&building);
  printf("\nsuccessfully Initialize building.\n");

  populateRooms(building);
  printf("successfully populated building with rooms.\n");
  printf("The first room in building's roomlist: %s\n", building->roomList.head->room->name);

  HunterType* h1;
  EvidenceClassType equipment = 0;
  initHunter(&h1, nameH1, building->roomList.head->room, equipment);
  addHunter(&building->huntersList, h1);
  addHunter(&building->roomList.head->room->huntersList, h1);
  printf("\n%s got successfully Initialize and added to building's huntersList\n", h1->name);

  HunterType* h2;
  equipment = 1;
  initHunter(&h2, nameH2, building->roomList.head->room, equipment);
  addHunter(&building->huntersList, h2);
  addHunter(&building->roomList.head->room->huntersList, h2);
  printf("%s got successfully Initialize and added to building's huntersList\n", h2->name);

  HunterType* h3;
  equipment = 2;
  initHunter(&h3, nameH3, building->roomList.head->room, equipment);
  addHunter(&building->huntersList, h3);
  addHunter(&building->roomList.head->room->huntersList, h3);
  printf("%s got successfully Initialize and added to building's huntersList\n", h3->name);

  HunterType* h4;
  equipment = 3;
  initHunter(&h4, nameH4, building->roomList.head->room, equipment);
  addHunter(&building->huntersList, h4);
  addHunter(&building->roomList.head->room->huntersList, h4);
  printf("%s got successfully Initialize and added to building's huntersList\n", h4->name);

  RoomType* randRoom = getRandomRoom(&building->roomList);
  printf("\nsuccessfully got a random room in the building to put the ghost in, the room is: %s\n", randRoom->name);

  GhostClassType ghostType = (GhostClassType)randInt(0,4);
  initGhost(&building->ghost, ghostType, randRoom);
  randRoom->ghost = building->ghost;
  printf("successfully initialize the ghost.\n");

  printf("Now Calling ghostAction function to choose and make ghost do a action:\n");

  ghostAction(building->ghost, &building->ghost->currRoom->huntersList);

  // printf("\nghostAction worked properly. Calling ghostAction 3 more times.\n");
  // ghostAction(building->ghost, &building->ghost->currRoom->huntersList);
  // ghostAction(building->ghost, &building->ghost->currRoom->huntersList);
  // ghostAction(building->ghost, &building->ghost->currRoom->huntersList);

  // printf("\nNow displaying each of the two ghost actions directly just in case (last action is just doing nothing, so no need to display)\n");
  // printf("dropEvidence function:\n");
  // dropEvidence(building->ghost);
  // printf("ghostMoveRooms function:\n");
  // ghostMoveRooms(building->ghost);

  printf("\nNow will call hunterAction function once for each hunter:\n");
  printf("PS: wrote this in comments as well, not sure why but once in awhile hunterMoveRooms randomly seg faults, majority of the time it works properly.\n");

  hunterAction(h1, &h1->currRoom->huntersList);
  hunterAction(h2, &h2->currRoom->huntersList);
  hunterAction(h3, &h3->currRoom->huntersList);
  hunterAction(h4, &h4->currRoom->huntersList);

  printf("\nNow to show the sameRoomAsGhost function on each of the hunters (if the ghost is in same room, hunter's fear goes up, boredomTimer resets):\n");
  sameRoomAsGhost(h1);
  sameRoomAsGhost(h2);
  sameRoomAsGhost(h3);
  sameRoomAsGhost(h4);

  printf("\nLastly calling printFinalResults function that prints the final results of the program:\n");
  printFinalResults(building);

  printf("end of program, cleaning up building.\n");
  //commented out cleanUpBuilding because it does not work properly
  //cleanUpBuilding(building);
  return 0;
}


/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}
