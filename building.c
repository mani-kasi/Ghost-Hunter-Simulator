
#include "defs.h"


/*
purpose: To Initialize the building
in/out: building
*/
void initBuilding(BuildingType** building){
  (*building) = (BuildingType*) malloc(sizeof(BuildingType));
  (*building)->roomList.head = NULL;
  (*building)->huntersList.size = -1;
  (*building)->ghost = NULL;
}

/*
purpose: To populate the building with rooms
in/out: building
*/
void populateRooms(BuildingType* building) {
    RoomType* van = calloc(1, sizeof(RoomType));
    initRoom(&van, "Van");
    RoomType* hallway = calloc(1, sizeof(RoomType));
    initRoom(&hallway, "Hallway");
    RoomType* master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(&master_bedroom, "Master Bedroom");
    RoomType* boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(&boys_bedroom, "Boy's Bedroom");
    RoomType* bathroom = calloc(1, sizeof(RoomType));
    initRoom(&bathroom, "Bathroom");
    RoomType* basement = calloc(1, sizeof(RoomType));
    initRoom(&basement, "Basement");
    RoomType* basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(&basement_hallway, "Basement Hallway");
    RoomType* right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(&right_storage_room, "Right Storage Room");
    RoomType* left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(&left_storage_room, "Left Storage Room");
    RoomType* kitchen = calloc(1, sizeof(RoomType));
    initRoom(&kitchen, "Kitchen");
    RoomType* living_room = calloc(1, sizeof(RoomType));
    initRoom(&living_room, "Living Room");
    RoomType* garage = calloc(1, sizeof(RoomType));
    initRoom(&garage, "Garage");
    RoomType* utility_room = calloc(1, sizeof(RoomType));
    initRoom(&utility_room, "Utility Room");

    RoomNodeType* van_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    van_node->room = van;
    RoomNodeType* hallway_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    hallway_node->room = hallway;
    RoomNodeType* master_bedroom_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    master_bedroom_node->room = master_bedroom;
    RoomNodeType* boys_bedroom_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    boys_bedroom_node->room = boys_bedroom;
    RoomNodeType* bathroom_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    bathroom_node->room = bathroom;
    RoomNodeType* basement_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    basement_node->room = basement;
    RoomNodeType* basement_hallway_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    basement_hallway_node->room = basement_hallway;
    RoomNodeType* right_storage_room_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    right_storage_room_node->room = right_storage_room;
    RoomNodeType* left_storage_room_node =  (RoomNodeType*)malloc(sizeof(RoomNodeType));
    left_storage_room_node->room = left_storage_room;
    RoomNodeType* kitchen_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    kitchen_node->room = kitchen;
    RoomNodeType* living_room_node = (RoomNodeType*)malloc(sizeof(RoomNodeType));
    living_room_node->room = living_room;
    RoomNodeType* garage_node =  (RoomNodeType*)malloc(sizeof(RoomNodeType));
    garage_node->room = garage;
    RoomNodeType* utility_room_node =  (RoomNodeType*)malloc(sizeof(RoomNodeType));
    utility_room_node->room = utility_room;

    appendRoom(&building->roomList, van_node);
    appendRoom(&building->roomList, hallway_node);
    appendRoom(&building->roomList, master_bedroom_node);
    appendRoom(&building->roomList, boys_bedroom_node);
    appendRoom(&building->roomList, bathroom_node);
    appendRoom(&building->roomList, basement_node);
    appendRoom(&building->roomList, basement_hallway_node);
    appendRoom(&building->roomList, right_storage_room_node);
    appendRoom(&building->roomList, left_storage_room_node);
    appendRoom(&building->roomList, kitchen_node);
    appendRoom(&building->roomList, living_room_node);
    appendRoom(&building->roomList, garage_node);
    appendRoom(&building->roomList, utility_room_node);

    //realized only after we made our connect room function it only connects one way, so need to do it twice for two rooms to both be connected to each other
    connectRooms(&building->roomList.head->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->room->connectedRooms, master_bedroom);
    connectRooms(&building->roomList.head->next->room->connectedRooms, boys_bedroom);
    connectRooms(&building->roomList.head->next->room->connectedRooms, bathroom);
    connectRooms(&building->roomList.head->next->room->connectedRooms, kitchen);
    connectRooms(&building->roomList.head->next->room->connectedRooms, basement);
    connectRooms(&building->roomList.head->next->next->next->next->next->room->connectedRooms, basement_hallway);
    connectRooms(&building->roomList.head->next->next->next->next->next->room->connectedRooms, right_storage_room);
    connectRooms(&building->roomList.head->next->next->next->next->next->room->connectedRooms, left_storage_room);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->next->next->room->connectedRooms, living_room);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->next->next->room->connectedRooms, garage);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->next->next->next->next->next->room->connectedRooms, utility_room);

    connectRooms(&building->roomList.head->next->room->connectedRooms, van);
    connectRooms(&building->roomList.head->next->next->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->next->next->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->next->next->next->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->next->next->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->next->next->next->next->room->connectedRooms, hallway);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->room->connectedRooms, basement);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->room->connectedRooms, basement_hallway);
    connectRooms(&building->roomList.head->next->next->next->next->next->next->next->next->room->connectedRooms, basement_hallway);
}


/*
purpose: to clean up the building and everything inside it
in/out: building
*/
void cleanUpBuilding(BuildingType* building){
  cleanUpHunterArray(&(building->huntersList));
  cleanUpRoomList(&building->roomList);
}


/*
purpose: to print the final result of the program
in: Building
out: text printed in the console
*/
void printFinalResults(BuildingType* building){
  int count = 0;
  char* ghost = ghostTypeString(building->ghost->ghostType);
  printf("\nComplete! Here are the results:\n");
  for(int i = 0; i < building->huntersList.size; i++){
    if((building->huntersList.hunters[i])->fear >= 100){
      count ++;
      printf("- %s fear is %d and has ran away in fear!\n", (building->huntersList.hunters[i])->name, (building->huntersList.hunters[i])->fear);
    }
  }
  if(count == 4){
    printf("\nAll the hunters has ran away in fear!");
    printf("\nTHE GHOST HAS WON! The Ghost type was:%s\n", ghost);
  }
  else{
    count = 0;
    for(int i =0; i < building->huntersList.size; i++){
      if((building->huntersList.hunters[i])->boredomTimer <= 0){
        count ++;
        printf("- %s boredom timer is %d and has left the building!\n", (building->huntersList.hunters[i])->name, (building->huntersList.hunters[i])->boredomTimer);
      }
    }
    if(count == 4){
      printf("\nAll the hunters has got bored and left the building!");
      printf("\nEVERYONE LEFT THE BUILDING OUT OF BOREDOM, IT'S A TIE!\n");
    }
    else{
      char* speculatedGhost = getSpeculatedGhost(&building->huntersList);
      if(strcmp(speculatedGhost, "N/A") == 0){
        printf("\nAt least one hunter is still sane. The hunter(s) left did not have enough data to speculate a ghost.");
        printf("\nTHE GHOST HAS WON! The Ghost type was: %s\n", ghost);
      }
      else{
        printf("\nAt least one hunter is still sane. The speculated ghost type is:%s", speculatedGhost);
        printf("\nThe real ghost type is:%s", ghost);

        if(ghost == speculatedGhost){
           printf("\nThe speclate ghost was correct! THE HUNTERS HAS WON!");
        }
      }
    }
  }
}
