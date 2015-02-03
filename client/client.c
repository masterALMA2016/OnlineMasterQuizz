#include "client.h"

Client* Client_create(){

	Client* client = (Client*)malloc(sizeof(Client));

	if(client){
		client->socketID = -1;
        client->socketInfos = (sockaddr_in*) malloc(sizeof(sockaddr_in));

        if(client->socketInfos == NULL){
            free(client);
        }
	}

	return client;
}

bool Client_run(Client* client, char* serverName, int serverPort){

    hostent* serverInfos = gethostbyname(serverName);
    if (serverInfos == NULL) {
       perror("[Client/Run] Cannot find server from given hostname\n");
       return false;
    }

    // Fill socket infos with server infos
    bcopy((char*)serverInfos->h_addr, (char*)&client->socketInfos->sin_addr, serverInfos->h_length);
    client->socketInfos->sin_family = AF_INET;
    client->socketInfos->sin_port = htons(serverPort);

    // Socket configuration and creation
    printf("[Client/Run] Connect to server %s:%d\n", serverInfos->h_name, ntohs(client->socketInfos->sin_port));
        
    client->socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socketID < 0) {
        perror("[Client/Run] Unable to create socket connexion\n");
        return false;
    }
    
    if ((connect(client->socketID, (sockaddr*)(client->socketInfos), sizeof(sockaddr))) < 0) {
        perror("[Client/Run] Cannot connect to the server\n");
        return false;
    }
    printf("[Client/Run] Connection sucessfull\n\n");
    
    return true;
}

#include <arpa/inet.h>
void printr(int a, DataType_resp plid){
    if(a > 0){
        printf("answer %s\n", plid.answer); 
        printf("score %d\n", plid.score); 
        perror("recv succeed\n");        
    }
    else {
        perror("recv failed\n");
        exit(1);        
    }
}
void Client_waitForPLID(Client* client){

    // Display socket infos
    printf(
        "Socket desc: %d\nConnex type: %d\nOppenned port: %d\nIP adress: %s\n\n", 
        client->socketID, 
        client->socketInfos->sin_family, 
        ntohs(client->socketInfos->sin_port), 
        inet_ntoa(client->socketInfos->sin_addr)
    );

    // Receive data over socket connection    
    //DataType_plid plid;
    DataType_resp plid;

    //printr(read(client->socketID, &plid, sizeof(plid)), plid);


    printr(recv(
            client->socketID, 
            &plid, 
            sizeof(plid),
            0
    ), plid);
/*
    socklen_t size = sizeof(sockaddr_in);
    printr(recvfrom(
            client->socketID, 
            &plid, 
            sizeof(plid),
            0, 
            (sockaddr*)client->socketInfos,
            &size
    ), plid); 
*/   
}

void Client_waitForPNUM(Client* client){

}

void Client_sendDEFQ(Client* client, Question* question){

}

void Client_sendANSW(Client* client, int answer){

}

void Client_waitForELEC(Client* client){

}

void Client_waitForASKQ(Client* client){

}

void Client_waitForRESP(Client* client){
    
}

 /*  
    printf("envoi d'un message au serveur. \n");
      
    if ((write(socket_descriptor, mesg, strlen(mesg))) < 0) {
	perror("erreur : impossible d'ecrire le message destine au serveur.");
	exit(1);
    }
    

    sleep(3);
     
    printf("message envoye au serveur. \n");
                

    while((longueur = read(socket_descriptor, buffer, sizeof(buffer))) > 0) {
	printf("reponse du serveur : \n");
	write(1,buffer,longueur);
    }
    
    printf("\nfin de la reception.\n");
    
    close(socket_descriptor);
    
    printf("connexion avec le serveur fermee, fin du programme.\n");
    
    exit(0);
 */ 
    