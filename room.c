#include "defs.h"

/*
purpose: to Initialize the given room
in: name
in/out: room
*/
void initRoom(RoomType** room, char* name){
  (*room) = (RoomType*)malloc(sizeof(RoomType));
  strcpy((*room)->name, name);
  (*room)->ghost = NULL;
  initEvidenceList(&(*room)->roomEvidence);
}

/*
purpose: to connect the given room to a room's connectRooms(all the rooms a room is adjacent to)
in/out: list, roomToConnect(the room that are we connecting to)
*/
void connectRooms(RoomNodeListType* list, RoomType* roomToConnect){
    RoomNodeType* curr = list->head;

    if (curr == NULL) {
        curr = (RoomNodeType*)malloc(sizeof(RoomNodeType));
        curr->room = roomToConnect;
        list->head = curr;
        list->size = 1; // Update size when adding the first room
        return;
    }

    while(curr != NULL){
        if(curr->next == NULL){
            RoomNodeType* new = (RoomNodeType*)malloc(sizeof(RoomNodeType));
            new->room = roomToConnect;
            curr->next = new;
            list->size++; // Increment size when adding a new room
            return;
        }
        else{
            curr = curr->next;
        }
    }
}

/*
purpose: to add given room to a room list
in/out: list, newRoom (node of the new room)
*/
void appendRoom(RoomNodeListType* list, RoomNodeType* newRoom){
    RoomNodeType* curr = list->head;

    if (curr == NULL) {
        list->head = newRoom;
        list->size = 1; // Update size when adding the first room
        return;
    }

    while(curr != NULL){
        if(curr->next == NULL){
            curr->next = newRoom;
            list->size++; // Increment size when adding a new room
            return;
        }
        else{
            curr = curr->next;
        }
    }
}

/*
purpose: to clean up the given Room List
in/out: list
*/
void cleanUpRoomList(RoomNodeListType *list) {
  //referenced code from lecture 13
  RoomNodeType* curr = list->head;
  RoomNodeType* nextNode = NULL;

  while(curr != NULL){
    nextNode = curr->next;
    cleanUpEvidenceList(&curr->room->roomEvidence);
    free(curr->room);
    free(curr);
    curr = nextNode;
  }
}

/*
purpose: to get a random room from the list
in: List
out: random room from the list
*/
struct Room* getRandomRoom(RoomNodeListType* list){
  RoomNodeType* curr = list->head;
  //to get count of rooms in list
  int count = -1;
  while(curr != NULL){
    count ++;
    curr = curr->next;
  }
  //gets a random room number
  int randRoom = randInt(0, count + 1);
  count = 0;
  //resets count and curr to loop to find room corrsponding to randRoom
  curr = list->head;
  while(curr != NULL){
    if(count == randRoom){
      break;
    }
    else{
      count ++;
      curr = curr->next;
    }
  }
  return (curr->room);
}
