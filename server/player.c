#include "player.h"

void Player_printClientInfos(Player* player){
    printf("* Remote IP: %s\n", inet_ntoa(player->socketInfos->sin_addr));    
    printf("* Remote port: %d\n\n", ntohs(player->socketInfos->sin_port));    
}

void* Player_sendPLID (void* params) {

    void** paramList = (void**) params;
    Player* player = (Player*) paramList[0];
    Server* server = (Server*) paramList[1];

    Server_sendPLID(server, player);

    bool isFirstClient = (player->playerID == 0) ? true : false;
    Server_sendPNUM(server, player, isFirstClient);

    if(isFirstClient){
        Server_waitForPNUM(server, player);
    }

    return NULL;
}

void* Player_sendELEC(void* params){
    void** paramList = (void**) params;
    Player* player = (Player*) paramList[0];
    Server* server = (Server*) paramList[1];

    bool elected = (server->electedPlayer != NULL && player->playerID == server->electedPlayer->playerID);
    Server_sendELEC(server, player, elected);


    if(!elected){
        Server_waitForANSW(server, player);
    }

    free(params);

    return NULL;
}

void* Player_sendASKQ(void* params){
    void** paramList = (void**) params;
    Player* player = (Player*) paramList[0];
    Server* server = (Server*) paramList[1];

    Server_sendASKQ(server, player);
/*
    while(bad answer && other player don't win){
        Server_waitForANSW(server, player);    

        if(good anwser){
            Server_notifyGoodANSW(server, player);
        }
    }
*/
    free(params);
    
    return NULL;
}

void* Player_sendRESP(void* params){
//  Server_sendRESP(server, player, anwserID);
    return NULL;
}

/*
    char buffer[256];
    int longueur;
   
    if ((longueur = read(clientSocket, buffer, sizeof(buffer))) <= 0) 
        return NULL;
    
    printf("message lu : %s \n", buffer);
    
    buffer[0] = 'R';
    buffer[1] = 'E';
    buffer[longueur] = '#';
    buffer[longueur+1] ='\0';
    
    printf("message apres traitement : %s \n", buffer);
    
    printf("renvoi du message traite.\n");

    sleep(3);
    
    write(clientSocket,buffer,strlen(buffer)+1);
    
    printf("message envoye. \n");   
    close(clientSocket); 
*/