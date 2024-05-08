#include "defs.h"

/*
purpose: to Initialize the evidence given
in: type, value
in/out: evidence
*/
void initEvidence(EvidenceType** evidence, EvidenceClassType type, float value){
  (*evidence) = (EvidenceType*) malloc(sizeof(EvidenceType));
  (*evidence)->evidenceType = type;
  (*evidence)->value = value;
}

/*
purpose: to Initialize the evidence list given
in/out: evidenceList
*/
void initEvidenceList(EvidenceListType* list){
  list->head = NULL;
}

/*
purpose: to add evidence to the given evidence list using its head and looping
in/out: list, newEvidence(new evidence that needs to be added)
*/
void addEvidence(EvidenceListType* list, EvidenceType* newEvidence){
  NodeType* curr = list->head;
  NodeType* new = NULL;

  new = (NodeType*) malloc(sizeof(NodeType));
  new->data = newEvidence;
  new->next = NULL;

  if(curr == NULL){
    list->head = new;
    return;
  }

  while(curr != NULL){
    if(curr->next == NULL){
      curr->next = new;
      break;
    }
    else{
      curr = curr->next;
    }
  }
}

/*
purpose: to let a hunter share evidence with a random hunter in the same room, only shares ghostly data
in/out: list(list of hunter's curr Evidence), room(the room to selete a random hunter and add evidence to that hunter's evidence list if there is ghostly data to be given), hunter (hunter sharing the evidence to make sure we dont accidently choose them to share the evidence with)
*/
//THIS FUNCTION DOES NOT WORK PROPERLY and we could not figure out why. We did not call it in the main so the program won't break. please give part marks where possible.
void shareEvidence(EvidenceListType* list, RoomType* room, HunterType* hunter){
  NodeType* curr = list->head;
  //gets a random hunter and makes sure the randHunter is not the same hunter sharing evidence
  int randHunter = randInt(0, room->huntersList.size + 1);
  while((room->huntersList.hunters[randHunter]) == hunter){
    randHunter = randInt(0, room->huntersList.size + 1);
  }

  if(curr == NULL){
    printf("/n%s has no evidence to share.", hunter->name);
    return;
  }
  while(curr != NULL){
    if(isGhostlyData(curr->data) == C_OK){
      addEvidence(&(room->huntersList.hunters[randHunter])->currEvidence, curr->data);
    }
    curr = curr->next;
  }
}

/*
purpose: to remove a room's evidence
in/out: list, evidence(evidence to be removed)
*/
void removeRoomEvidence(EvidenceListType* list, EvidenceType* evidence) {
  NodeType* curr = list->head;
  NodeType* nextNode = list->head->next;

//if the head is the evidence we want to be removed
  //if the head->next is not null, this works properly
  if(curr->data == evidence){
    if(nextNode != NULL){
      free(list->head->data);
      list->head = nextNode;
      return;
    }
    //if the head->next is null, this works properly
    free(list->head->data);
    list->head = NULL;
    return;
  }

  while(curr != NULL) {
    if (curr->data == evidence){
      if(nextNode != NULL){
        free(curr->data);
        curr = nextNode;
        return;
      }
      free(curr->data);
      curr = NULL;
      return;
    }
    else {
      curr = nextNode;
      nextNode = nextNode->next;
    }
  }
}

/*
purpose: to let the ghost drop evidence in it's current room
in: ghost
out: evidence in the ghost's current room's evidence list
*/
void dropEvidence(GhostType* ghost){
  //gets a random evidence and value depending on ghost
  EvidenceClassType type = randomEvidence(ghost->ghostType);
  float value = randomGhostEvidenceValue(type);
  //makes new evidence
  EvidenceType* newEvidence = (EvidenceType*) malloc(sizeof(EvidenceType));
  newEvidence->evidenceType = type;
  newEvidence->value = value;
  //adds evidence and prints a statments depending if ghostly data or not
  addEvidence(&ghost->currRoom->roomEvidence, newEvidence);
  if(isGhostlyData(newEvidence) == C_OK){
    printf("The ghost has left GHOSTLY %s evidence in the %s\n", evidenceString(type), ghost->currRoom->name);
  }
  else{
    printf("The ghost has left STANDARD %s evidence in the %s\n", evidenceString(type), ghost->currRoom->name);
  }
}

/*
purpose: to create standard evidence of the right type to add to the given hunter's evidence list
in: equipment
in/out: list
*/
void createStandardEvidence(EvidenceListType* list, EvidenceClassType equipment){
  EvidenceType* newEvidence = (EvidenceType*) malloc(sizeof(EvidenceType));
  newEvidence->evidenceType = equipment;
  if(equipment == 0){
    newEvidence->value = randFloat(0.00, 4.90);
    addEvidence(list, newEvidence);
    return;
  }
  else if(equipment == 1){
    newEvidence->value = randFloat(0.00, 27.00);
    addEvidence(list, newEvidence);
    return;
  }
  else if(equipment == 0){
    newEvidence->value = randInt(0.00, 1.00);
    addEvidence(list, newEvidence);
    return;
  }
  else{
    newEvidence->value = randFloat(40.00, 70.00);
    addEvidence(list, newEvidence);
    return;
  }

}
/*
purpose: to check if there is evidence in the curr room of the given hunter and to add evidence accordingly with the hunter's equipment type
in/out: hunter
*/
void checkAndCollectEvidence(HunterType* hunter){
  NodeType* curr = hunter->currRoom->roomEvidence.head;

  //if room evidence is empty, gives hunter random standard evidence
  if(curr == NULL){
    createStandardEvidence(&hunter->currEvidence, hunter->equipment);
      printf("%s has collected RANDOM %s evidence\n", hunter->name, evidenceString(hunter->equipment));
    return;
  }
  bool flag = false;
  while(curr != NULL){
    //if found evidence in room that same type as hunter's equipment, adds evidence to hunters evidence list
    if(curr->data->evidenceType == hunter->equipment){
      flag = true;
      addEvidence(&hunter->currEvidence,curr->data);
      removeRoomEvidence(&hunter->currRoom->roomEvidence, curr->data);
      printf("%s has collected %s evidence\n", hunter->name, evidenceString(hunter->equipment));
      if(isGhostlyData(curr->data) == C_OK){
        hunter->boredomTimer = BOREDOM_MAX;
      }
    }
    curr = curr->next;
  }
  //if flag is false, means there was evidence in the room but not same type as hunter, so makes random evidence for hunter
  if(flag == false){
    createStandardEvidence(&hunter->currEvidence, hunter->equipment);
    printf("%s has collected RANDOM %s evidence\n", hunter->name, evidenceString(hunter->equipment));
  }
  return;
}


/*
purpose: to choose a random evidence class type for the given ghost type
in: ghost type
out: a evidence class type
*/
EvidenceClassType randomEvidence(GhostClassType ghostType){
  int action;
  EvidenceClassType type;
  if(ghostType == POLTERGEIST){
    //action 1: EMF, 2: TEMPERATURE, 3: FINGERPRINTS
    action = randInt(1,4);

    if(action == 1){
      type = 0;
      return type;
    }
    else if(action == 2){
      type = 1;
      return type;
    }
    else{
      type = 2;
      return type;
    }
  }
  else if(ghostType == BANSHEE){
    //action 1: EMF, 2: TEMPERATURE, 3: SOUND
    action = randInt(1,4);

    if(action == 1){
      type = 0;
      return type;
    }
    else if(action == 2){
      type = 1;
      return type;
    }
    else{
      type = 3;
      return type;
    }
  }
  else if(ghostType == BULLIES){
    //action 1: EMF, 2: FINGERPRINTS, 3: SOUND
    action = randInt(1,4);

    if(action == 1){
      type = 0;
      return type;
    }
    else if(action == 2){
      type = 2;
      return type;
    }
    else{
      type = 3;
      return type;
    }
  }
  else{
    //action 1: TEMPERATURE, 2: FINGERPRINTS, 3: SOUND
    action = randInt(1,4);

    if(action == 1){
      type = 1;
      return type;
    }
    else if(action == 2){
      type = 2;
      return type;
    }
    else{
      type = 3;
      return type;
    }
  }
}

/*
purpose: to generate a random value for the given type of evidence that the ghost drops
in: type
out: a float value
*/
float randomGhostEvidenceValue(EvidenceClassType type){
  float value;
  if (type == 0){
    value = randFloat(4.70,5.00);
  }
  else if(type == 1){
    value = randFloat(-10.00, 1.00);
  }
  else if(type == 2){
    value = (1.00);
  }
  else{
    value = randFloat(65.00,75.00);
  }
  return value;
}

/*
purpose: to turn the given evidence class type into a string
in: type
out: type as a string
*/
char* evidenceString(EvidenceClassType type){
  if(type == 0){
    return "EMF";
  }
  else if(type == 1){
    return "TEMPERATURE";
  }
  else if(type == 2){
    return "FINGERPRINTS";
  }
  else{
    return "SOUND";
  }
}

/*
purpose: to clean up the given evidence list
in/out: head ( the head of the evidence list to clean up)
*/
void cleanUpEvidenceList(EvidenceListType* list) {
  //referenced code from lecture 13
  NodeType* curr = list->head;
  NodeType* nextNode = NULL;

  while (curr != NULL) {
    nextNode = curr->next;
    free(curr->data);
    free(curr);
    curr = nextNode;
  }
}
