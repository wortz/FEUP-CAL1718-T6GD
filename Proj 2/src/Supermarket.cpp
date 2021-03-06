/*
 * Supermarkets.cpp
 *
 *  Created on: 03/04/2018
 *      Author: Asus
 */

#include "Supermarket.h"

using namespace std;

Supermarket::Supermarket(Vertex* node, string cadeia){
	this->node=node;
	this->id=-1;
	this->cadeia=cadeia;
}

void Supermarket::setId(int id){
	this->id=id;
}

void Supermarket::addClient(Client * client){
	clients.push_back(client);
}

Vertex * Supermarket::getNode(){
	return this->node;
}

int Supermarket::getId(){
	return this->id;
}

bool Supermarket::removeClient(Client * c){
	for(unsigned int i=0;i<clients.size();i++)
			if(c->getNodeId()==clients[i]->getNodeId()){
				clients.erase(clients.begin()+i);
				return true;
			}
	return false;
}

long long int Supermarket::closestClient() {
	int distmin = -1;
	Client * c;
	for (auto client : clients) {
		if(client->isVisited())
				continue;
		if (distmin == -1||distmin > client->getVertex()->getDist()) {
			distmin = client->getVertex()->getDist();
			c = client;
		}
	}
	c->setVisited(true);
	return c->getNodeId();
}

unsigned int Supermarket::getNrClients(){
	return clients.size();
}

void Supermarket::eraseClients(){
	clients.clear();
}

void Supermarket::resetAllVisited(){
	for(auto it:clients)
		it->setVisited(false);
}

string Supermarket::getCadeia(){
	return this->cadeia;
}


