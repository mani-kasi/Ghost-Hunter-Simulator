#include "defs.h"

/*
purpose: to Initialize a hunter
in: name, room, equipment
in/out: hunter
*/
void initHunter(HunterType** hunter, char* name, RoomType* room, EvidenceClassType equipment){
  (*hunter) = malloc(sizeof(HunterType));
  strcpy((*hunter)->name, name);
  (*hunter)->currRoom = room;
  (*hunter)->equipment = equipment;
  initEvidenceList(&(*hunter)->currEvidence);
  (*hunter)->fear = 0;
  (*hunter)->boredomTimer = BOREDOM_MAX;

}

/*
purpose: to add a hunter to the given hunter array
in/out: arr, hunter
*/
void addHunter(HunterArrayType* arr, HunterType* hunter){
  arr->hunters[arr->size] = hunter;
  arr->size ++;
}

/*
purpose: to see if hunter is in same room as ghost, if they are increase fear and reset boredomTimer
in/out: arr, hunter
*/
void sameRoomAsGhost(HunterType* hunter){
  if(hunter->currRoom->ghost != NULL){
    hunter->fear ++;
    hunter->boredomTimer = BOREDOM_MAX;
    printf("%s is in the same room as the ghost! FEAR + 1\n", hunter->name);
    return;
  }
  printf("%s is not in the same room as the ghost.\n", hunter->name);
}

/*
purpose: to randomly generate an action for the given hunter depending on the situation (if there is another hunter in the same room)
in: arr
in/out: hunter
*/
void hunterAction(HunterType* hunter, HunterArrayType* arr){
  bool flag = false;
  int action;
  for(int i = 0; i < arr->size; i++){
    if(arr->hunters[i]->currRoom == hunter->currRoom || arr->hunters[i]->name != hunter->name){
      flag = true;
      break;
    }
  }
  //action 1 is collection evidence in room, 2 is move rooms, 3 is to share evidence if another hunter in room
  if(flag){
    action = randInt(1,4);
  }
  else{
    action = randInt(1,3);
  }
  if(action == 1){
    printf("\n%s: CHECK AND COLLECTED EVIDENCE WAS THE ACTION!\n", hunter->name);
    checkAndCollectEvidence(hunter);
  }
  else if(action == 2){
    printf("\n%s: HUNTER MOVE ROOMS WAS THE ACTION!\n", hunter->name);
    hunterMoveRooms(hunter);
  }
  else{
    printf("%s: SHAREDEVIDENCE WAS THE ACTION! commented out function due to problems we explained in the comments in hunter.c\n\n", hunter->name);
    //shareEvidence(&hunter->currEvidence, hunter->currRoom, hunter);
  }
}

/*
purpose: moves hunter to adjacent room and update room's hunters HunterArray
in/out: hunter
*/
//not sure why, although majority of the time this function works properly, once in awhile it randomly segs faults, could not figure out why this was happening.
//Still included it in the main because it only rarely happens and wanted to show the functionailty.
void hunterMoveRooms(HunterType* hunter) {
    // Check if the current room has connected rooms
    if (hunter->currRoom == NULL || hunter->currRoom->connectedRooms.head == NULL) {
        printf("Error: Current room or connected rooms list is NULL.\n");
        return;
    }

    // Get the number of connected rooms
    int numConnectedRooms = hunter->currRoom->connectedRooms.size;

    // Check if there are any connected rooms
    if (numConnectedRooms == 0) {
        printf("Error: No connected rooms found.\n");
        return;
    }

    // Randomly select a room to move to
    int randRoomIndex = randInt(0, numConnectedRooms - 1);

    // Traverse the connected rooms list to find the selected room
    RoomNodeType* nextRoomNode = hunter->currRoom->connectedRooms.head;
    for (int i = 0; i < randRoomIndex; i++) {
        if (nextRoomNode == NULL) {
            printf("Error: Invalid connected rooms list.\n");
            return;
        }
        nextRoomNode = nextRoomNode->next;
    }

    // Check if the selected room node is NULL
    if (nextRoomNode == NULL || nextRoomNode->room == NULL) {
        printf("Error: Selected room node or room is NULL.\n");
        return;
    }

    // Update hunter's current room
    if (hunter->currRoom->huntersList.size > 0) {
        // Remove hunter from current room's hunter list
        for (int i = 0; i < hunter->currRoom->huntersList.size; i++) {
            if (hunter->currRoom->huntersList.hunters[i] == hunter) {
                hunter->currRoom->huntersList.hunters[i] = NULL;
                break;
            }
        }
        hunter->currRoom->huntersList.size--;
    }

    // Update hunter's current room and add hunter to the new room's hunter list
    hunter->currRoom = nextRoomNode->room;
    hunter->currRoom->huntersList.hunters[hunter->currRoom->huntersList.size] = hunter;
    hunter->currRoom->huntersList.size++;
}

/*
purpose: check if a hunter has 3 pieces of ghostly data and returns a C_OK or C_NOK accordingly
in/out: hunter
*/
int checkEvidenceCollected(HunterType* hunter){
  NodeType* curr = hunter->currEvidence.head;
  bool flag1 = false;
  bool flag2 = false;
  bool flag3 = false;
  bool flag4 = false;
  int counter = 0;

  if(curr == NULL){
    return C_NOK;
  }
  else{
    while(curr != NULL){
      if(curr->data->evidenceType == 0){
        if(isGhostlyData(curr->data) == C_OK){
          flag1 = true;
          counter ++;
        }
      }

      else if(curr->data->evidenceType == 1){
        if(isGhostlyData(curr->data) == C_OK){
          flag2 = true;
          counter ++;
        }
      }

      else if(curr->data->evidenceType == 2){
        if(isGhostlyData(curr->data) == C_OK){
          flag3 = true;
          counter ++;
        }
      }

      else{
        if(isGhostlyData(curr->data) == C_OK){
          flag4 = true;
          counter ++;
        }
      }
      curr = curr->next;
    }

    if(counter == 3){
      if(flag1 && flag2 && flag3)
        return 1;
      else if(flag1 && flag2 && flag4)
        return 2;
      else if(flag1 && flag3 && flag4)
        return 3;
      else
        return 4;

    }
    else{
      return C_NOK;
    }
  }
}

/*
purpose: clean up the given hunter array list
in/out: arr
*/
void cleanUpHunterArray(HunterArrayType* arr){
  for(int i = 0; i < arr->size; i ++){
    cleanUpEvidenceList(&(arr->hunters[i])->currEvidence);
    free(arr->hunters[i]);
  }
}

/*
purpose: to use a helper function to check if any of the hunters have enough evidence to speculate a ghost type,if one does it returns the ghost type as a string, if none do, gives back N/A
in/out: hunter
*/
char* getSpeculatedGhost(HunterArrayType* arr){
  for(int i = 0; i < arr->size; i++){
    if (checkEvidenceCollected(arr->hunters[i]) == 1){
      return "POLTERGEIST";
    }
    else if (checkEvidenceCollected(arr->hunters[i]) == 2){
      return "BANSHEE";
    }
    else if (checkEvidenceCollected(arr->hunters[i]) == 3){
      return "BULLIES";
    }
    else if (checkEvidenceCollected(arr->hunters[i]) == 4){
      return "PHANTOM";
    }
  }
  return "N/A";
}
