/*
 * Graph.cpp
 *
 *  Created on: 09/04/2018
 *      Author: Asus
 */

#include "Graph.h"


/*VERTEX*/
Vertex::Vertex(long long int in,double lat,double lon,int index): info(in)  {
	this->lat=lat;
	this->lon=lon;
	this->dist=INF;
	this->indegree=0;
	this->index=index;
}

int Vertex::getIndex(){
	return index;
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}


Vertex * Vertex::getPrevious(){
	return path;
}


long long int Vertex::getInfo(){
	return info;
}

/*
 *  Returns the vertex lat
 */

double Vertex::getLat(){
	return this->lat;
}

/*
 *  Returns the vertex lon
 */

double Vertex::getLon(){
	return this->lon;
}


double Vertex::getDist(){
	return this->dist;
}

Edge Vertex::findEdgeTo(const long long int &dest){
	for(auto it:adj){
		if(dest==it.dest->getInfo())
			return it;
	}
	return Edge(0,0,false,"");
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

void Vertex::addEdge(Vertex *d, double w,bool oneway,string name) {
	adj.push_back(Edge(d, w,oneway,name));
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Vertex::removeEdgeTo(Vertex *d) {
	for (auto it = adj.begin(); it != adj.end(); it++)
		if (it->dest  == d) {
			adj.erase(it);
			return true;
		}
	return false;
}

vector<Edge > Vertex::getAdjacent(){
	return adj;
}



/*EDGE*/

Edge::Edge(Vertex *d, double w,bool oneway,string name): dest(d), weight(w), oneway(oneway),name(name) {}

bool Edge::isOneWay(){
	return oneway;
}

string Edge::getName(){
	return name;
}


/*GRAPH*/

int Graph::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const long long int &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const long long int &in,double lat,double lon,int index) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in,lat,lon,index));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const long long int &sourc, const long long int &dest, double w,bool oneway,string name) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w,oneway,name);
	if(!oneway)
		v2->addEdge(v1,w,oneway,name);
	return true;
}


Edge Graph::findEdge(const long long int &sourc,const long long int &dest){
	auto v1 = findVertex(sourc);
	return (v1->findEdgeTo(dest));

}


vector<Vertex *> Graph::getNodes(){
	vector<Vertex *> all;
	for(auto v:vertexSet){
		all.push_back(v);
	}
	return all;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */

bool Graph::removeEdge(const long long int &sourc, const long long int &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	return v1->removeEdgeTo(v2);
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

bool Graph::removeVertex(const long long int &in) {
	for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
		if ((*it)->info  == in) {
			auto v = *it;
			vertexSet.erase(it);
			for (auto u : vertexSet)
				u->removeEdgeTo(v);
			delete v;
			return true;
		}
	return false;
}

/**
* Initializes single
-
source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single
-
source shortest path algorithms.
*/

Vertex * Graph::initSingleSource(const long long int &origin) {
	for(auto v : vertexSet) {
		v->dist = INF;
		v->path =nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

/**
* Analyzes an edge in single
-
source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single
-
source shortest path algorithms.
*/

bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	} else
		return false;
}

/**
* Dijkstra algorithm.
*/

void Graph::dijkstraShortestPath(const long long int &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
	for (auto e : v->adj) {
		auto
		oldDist = e.dest->dist;
		if(relax(v, e.dest, e.weight)) {
			if(oldDist == INF)
				q.insert(e.dest);
			else
				q.decreaseKey(e.dest);
		}
	}
 }
}

/**
 * Gets the path from node origin to node dest
 * returns the vector of all the nodes
 */


vector<Vertex*> Graph::getPath(const long long int &origin, const long long int &dest) const {
	vector<Vertex*> res;
		long long int inf=dest;
		while(inf!=origin){
			res.push_back(this->findVertex(inf));
			inf=this->findVertex(inf)->path->info;
		}
		res.push_back(this->findVertex(inf));
		reverse(res.begin(),res.end());
		return res;
}



