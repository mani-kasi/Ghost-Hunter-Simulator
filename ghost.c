#include "defs.h"

/*
purpose: to Initialize the given ghost
in: type, room
in/out: ghost
*/
void initGhost(GhostType** ghost, GhostClassType type, RoomType* room) {
  (*ghost) = malloc(sizeof(GhostType));
  (*ghost)->ghostType = type;
  (*ghost)->currRoom = room;
  (*ghost)->boredomTimer = BOREDOM_MAX;
}

/*
purpose: to randomly generate an action for the ghost depending on the situation(hunter in the room or not)
in: arr
in/out: ghost
*/
void ghostAction(GhostType* ghost, HunterArrayType* arr){
  int action;
  bool flag = false;
  for(int i = 0; i < arr->size; i++){
    if(ghost->currRoom == arr->hunters[i]->currRoom){
      flag = true;
      break;
    }
  }
  //action 1 is leave evidence, action 2 is stay and do nothing, action 3 is move
  //if flag is true that means a hunter is in the same room so ghost stays and either leaves evidence or does nothing
  if(flag){
    action = randInt(1,3);
    if(action == 1){
      printf("\nGHOST DROPPED EVIDENCE WAS THE ACTION!\n");
      dropEvidence(ghost);
    }
    else if(action ==2){
      printf("The Ghost decided to stay and do nothing.\n");
    }
  }
  else{
    action = randInt(1,4);
    if(action == 1){
      printf("\nGHOST DROPPED EVIDENCE WAS THE ACTION!\n");
      dropEvidence(ghost);
    }
    else if(action ==2){
      printf("The Ghost decided to stay and do nothing.\n");
    }
    else{
      printf("\nGHOST MOVE ROOMS WAS THE ACTION\n");
      ghostMoveRooms(ghost);
    }
    ghost->boredomTimer --;
    printf("There are no hunters with the ghost. The ghost boredom timer has decreased by 1.\n");
  }
}

/*
purpose: to return a string of the ghost type
in: ghostType
out: char* containing the ghost type
*/
char* ghostTypeString (GhostClassType ghostType){
  if (ghostType == 0){
    return "POLTERGEIST";
  }
  else if (ghostType == 1){
    return "BANSHEE";
  }
  else if (ghostType == 2){
    return "BULLIES";
  }
  else{
    return "PHANTOM";
  }
}

/*
purpose: to check if given evidence is ghostly data
in: evidence
out: int C_OK or C_NOK depending if it is ghostly data or not
*/
int isGhostlyData(EvidenceType* evidence){
  if(evidence->evidenceType == 0){
    if(evidence->value > 4.90){
      return C_OK;
    }
    return C_NOK;
  }
  else if(evidence->evidenceType == 1){
    if(evidence->value < 0.00){
      return C_OK;
    }
    return C_NOK;
  }
  else if(evidence->evidenceType == 0){
    if(evidence->value == 1.00){
      return C_OK;
    }
    return C_NOK;
  }
  else{
    if(evidence->value > 70.00){
      return C_OK;
    }
    return C_NOK;
  }
}


/*
purpose: moves ghost to adjacent room and updates room's ghost pointer
in/out: ghost
*/
void ghostMoveRooms(GhostType* ghost) {
    // Check if the current room is NULL
    if (ghost->currRoom == NULL) {
        printf("Error: Current room is NULL.\n");
        return;
    }

    // Check if the current room has connected rooms
    if (ghost->currRoom->connectedRooms.head == NULL) {
        printf("Error: Current room has no connected rooms.\n");
        return;
    }

    // Get a random connected room
    RoomType* room = getRandomRoom(&ghost->currRoom->connectedRooms);

    // Check if the randomly selected room is NULL
    if (room == NULL) {
        printf("Error: Randomly selected room is NULL.\n");
        return;
    }

    // Update ghost's current room and room's ghost pointer
    ghost->currRoom->ghost = NULL;
    ghost->currRoom = room;
    room->ghost = ghost;

    printf("The ghost has moved to the %s.\n", room->name);
}
