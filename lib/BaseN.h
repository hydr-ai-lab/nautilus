
#ifndef BASE_N
#define BASE_N

#include<iostream>
#include<fstream>
#include<string>
#include <assert.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
const double SMALL=0.000001;

class Lato;
class Poligono;
class Vertice;
template<typename T> class Lista;
class Albero;
class NodoAlbero;

template<typename T>
class Vettore{
private:
	std::vector<T> dati;
	int numero;
	int iterator;

public:
	Vettore(){
		//std::cout<<"Vettore()"<<std::endl;
		numero=0;
		iterator=0;
	}
	Vettore(const Vettore& c){
		//std::cout<<"Vettore(Copia)"<<std::endl;
		numero=c.numero;
		iterator=0;
		dati=c.dati;
	}
	Vettore(const T a){
		//std::cout<<"Vettore("<<&a<<")"<<std::endl;
		dati.push_back(a);
		numero=1;
		iterator=0;
	}
	~Vettore(){
		//std::cout<<"~Vettore()"<<std::endl;
	}
	Vettore& operator=(const Vettore& c){
		clear();
		numero=c.numero;
		iterator=0;
		dati=c.dati;
		return *this;
	}
	Vettore& operator+=(const Vettore& c){
		numero+=c.numero;
		iterator=0;
		for(int i=0;i<c.numero;++i)
			dati.push_back(c.dati[i]);
		return *this;
	}
	void add(const T a){
		dati.push_back(a);
		numero++;
	}
	void cancel(const T a){
		for(int i=0;i<numero;++i)
			if(dati[i]==a){
				dati.erase(dati.begin()+i);
				numero--;
				return;
			}
	}
	void cancel(int index){
		if(index<numero){
			dati.erase(dati.begin()+index);
			numero--;
		}
	}
	void cancelFirst(){
		dati.erase(dati.begin());
		numero--;
	}
	void cancelLast(){
		dati.pop_back();
		numero--;
	}
	int size() const{
		return numero;
	}
	T& operator [](int i){
		assert(i<numero && i>=0);
		return dati[i];
	}
	T operator [](int i) const{
		assert(i<numero && i>=0);
		return dati[i];
	}
	T& first(){
		return dati.front();
	}
	T& last(){
		return dati.back();
	}
	bool exist(int i) const{
		if(numero>i)return true;
		return false;
	}
	bool existElement(T a) const{
		for(int i=0;i<(int)dati.size();++i)
			if(dati[i]==a){
				return true;
			}
		return false;
	}
	int getIndexElement(T a) const{
		for(int i=0;i<(int)dati.size();++i)
			if(dati[i]==a){
				return i;
			}
		return -1;
	}
	void start(T iniz){
		for(int i=0;i<numero;++i){
			if(iniz==dati[i]){
				iterator=i;
				return;
			}
		}
		int i=0;
		assert(i!=0);
	}
	T& next(int i){
		if(iterator+i>=numero)
			return next(i-numero);
		else if(iterator+i<0)
			return next(i+numero);
		else
			return dati[iterator+i];
	}
	void clear(){
		numero=0;
		dati.clear();
	}
	T& getElementCirular(int i){
		if(i>=numero){
			return getElementCirular(i-numero);
		}else if(i<0){
			return getElementCirular(i+numero);
		}else
			return dati[i];
	}
	std::vector<T>convert(){
		return dati;
	}
};
class Punto{
protected:
	double x,y,z;
public:
	Punto();
	Punto(double xi,double yi,double zi);
	Punto(const Punto& a);
	~Punto();
	void printPosition(bool Acapo=false) const;
	double getX() const;
	double getY() const;
	double getZ() const;
	//double& operator()(int coord);
	inline double& operator()(int coord){
		assert(coord>=0&&coord<=2);
		if(coord==0) return x;
		if(coord==1) return y;
		if(coord==2) return z;
		return x;
	}
	void assign(const Punto& v);
	Punto& operator=(const Punto& v);
	Punto operator+(const Punto& v) const;
	void operator+=(const Punto& v);
	Punto operator-(const Punto& v) const;
	void operator-=(const Punto& v);
	Punto operator*(double c) const;
	void operator*=(double c);
	void operator*=(const Punto& c);
	Punto operator/(double c) const;
	void operator/=(double c);
	bool equal(double xi,double yi,double zi) const;
	bool equal(const Punto& a) const;
	bool operator==(const Punto& a) const;
	double operator*(const Punto& c) const;
	Punto operator^(const Punto& c) const;
	double modulo() const;
	void rotazione(double angolo, Punto asse); //angolo [rad], asse any length;
	bool isNan();

};
template<typename T>
class OggettoLista{
	friend class Lista<T>;
protected:
	Lista<T>* lista;
	OggettoLista<T>* next;
	OggettoLista<T>* previous;

	OggettoLista(const OggettoLista&);
	OggettoLista(OggettoLista& c);
	OggettoLista& operator=(const OggettoLista&);
public:
	OggettoLista():next(0),previous(0){
		//std::cout<<"OggettoLista(OggettoLista&)"<<std::endl;
		lista=0;
	}
	virtual ~OggettoLista(){				//Virtuale per distruggere anche le classi derivate dalla Lista!
		//std::cout<<"~OggettoLista()"<<std::endl;
	}
	virtual OggettoLista* check()=0;		//Verifica se esiste già nella lista/maglia/albero...dalle derivate in poi!
	virtual void print(){					//Virtuale per fare il PrintAll() nella Lista!
		//std::cout<<"OggettoLista::print()"<<std::endl;
	}
	virtual void cancel(){					//Delinka il nodo dalla Lista e si occupa del delete!
		if(next)
			next->previous=previous;
		else
			lista->last=previous;
		if(previous)
			previous->next=next;
		else
			lista->first=next;
		lista->numero--;
		if(lista->iterator==this)
			lista->iterator=previous;
		delete this;
	}
	virtual void link()=0;					//Chiama il link per le derivate per agganciare tutto il resto! (il Link alla lista lo fa la Lista)
	/*Lista<T> getLista(){
		return lista;
	}*/
	OggettoLista<T>*& Next(){
		return next;
	}
	OggettoLista<T>*& Previous(){
		return previous;
	}
};
template<typename T>
class Lista{
	friend class OggettoLista<T>;
protected:
	OggettoLista<T>* first;
	OggettoLista<T>* last;
	int numero;
	OggettoLista<T>* iterator;

	void push(OggettoLista<T>* p,OggettoLista<T>* after,bool before){	//Sostituisce il OggettoLista::link()
		if(numero==0) {
			first=p;
			last=p;
			p->next=0;
			p->previous=0;
			numero=1;
			return;
		}
		if(after && !before){
			p->previous=after;
			p->next=after->next;
			if(after->next){
				after->next->previous=p;
			}else{
				last=p;
			}
			after->next=p;
			numero++;
			return;
		}
		if(after && before){
			p->next=after;
			p->previous=after->previous;
			if(after->previous){
				after->previous->next=p;
			}else{
				first=p;
			}
			after->previous=p;
			numero++;
			return;
		}
		last->next=p;
		p->previous=last;
		p->next=0;
		last=p;
		numero++;
	}
	Lista(const Lista<T>&);
	Lista<T>& operator=(const Lista<T>&);
public:
	Lista(){
		//std::cout<<"Lista()"<<std::endl;
		first=0;
		last=0;
		numero=0;
		iterator=0;
	}
	~Lista(){
		//std::cout<<"~Lista()"<<std::endl;
		for(OggettoLista<T>* p=first; p; p=first){
			first=p->next;
			delete p;			///???? non è meglio chiamare il cancel()?????
		}
	}
	T* add(T* a,T* after=0,bool before=false){
		push(a,after,before);
		a->lista=this;
		a->link();
		return a;
	}
	T* addCheck(T* a,T* after=0,bool before=false){
		//std::cout<<"T* addCheck(T*,T*,bool)"<<std::endl;
		a->lista=this;
		T* b=a->check();
		if(!b){
			push(a,after,before);
			a->link();
			return a;
		}else{
			delete a;
			return b;
		}
	}
	void printLista(){
		std::cout<<this<<" List of OggettoLista: "<<numero<<std::endl;
		std::cout<<"First: "<<first<<" Last: "<<last<<" Iter: "<<iterator<<std::endl;
		for (OggettoLista<T>* p=first; p; p=p->next){
			std::cout<<"  "<<p<<" prev: "<<p->previous<<" next: "<<p->next<<std::endl;
		}
	}
	void printAll(){
		std::cout<<this<<" Lista: "<<numero<<std::endl;
		for (OggettoLista<T>* p=first; p; p=p->next){
			p->print();
		}
	}
	int size(){
		return numero;
	}
	T* start(){
		return dynamic_cast<T*>(iterator=first);
	}
	T* next(){
		if(iterator)
			return dynamic_cast<T*>(iterator=iterator->next);
		else
			return dynamic_cast<T*>(iterator=first);
	}
	T* end(){
		return dynamic_cast<T*>(iterator=last);
	}
	T* previous(){
		if(iterator)
			return dynamic_cast<T*>(iterator=iterator->previous);
		else
			return dynamic_cast<T*>(iterator=last);
	}
};
class OggettoAlbero{
	friend class Albero;
	friend class NodoAlbero;
	friend class Poligono;
	friend class Vertice;
protected:
	NodoAlbero* nodo;
	Albero* albero;
	int tipo;
public:
	OggettoAlbero(int type);	//1-Vertice,2-Lato,3-Poligono
	virtual ~OggettoAlbero();
	virtual void linkA()=0;
	void setAlbero(Albero* Av);
	Albero* getAlbero();
};
class NodoAlbero{
	friend class Albero;
	friend class OggettoAlbero;
	friend class Vertice;
	friend class Lato;
	friend class Poligono;
protected:
	const unsigned int treashold=64;
	std::list<Vertice*> datiV;
	std::list<Lato*> datiL;
	std::list<Poligono*> datiP;
	Punto limMin;
	Punto limMax;
	NodoAlbero* figli[8];
	NodoAlbero* padre;
	int level;
	Albero* albero;
public:
	NodoAlbero(Punto min,Punto max,NodoAlbero* father=0);
	~NodoAlbero();
	void subdivide();
	void fuse();
	void print(int space);
	void datiforVTK(std::vector<Punto>& a);
	std::list<Vertice*>& collectV();
	std::list<Lato*>& collectL();
	std::list<Poligono*>& collectP();
	NodoAlbero* getCommonNodo(NodoAlbero* o);
	Punto getLim(int i);
	NodoAlbero* getNodo(Punto&);
	void insert(OggettoAlbero* dato,int tipo);
	void cancel(OggettoAlbero* dato, int tipo);
	int getNumAllVertici();
	bool rayIntersect(Punto o,Punto tg);
	bool plainIntersect(Punto o,Punto n);
	bool underPlain(Punto o,Punto n);
	void getNodiIntersectLinea(Punto o,Punto tg,std::vector<NodoAlbero*>&);
	void getNodiIntersectPiano(Punto o,Punto n,std::vector<NodoAlbero*>&);
	void getNodiUnderPiano(Punto o,Punto n,std::vector<NodoAlbero*>&);
	std::list<Poligono*>& getPoligoni();
};
class Albero{
	friend class OggettoAlbero;
	friend class NodoAlbero;
	friend class Vertice;
protected:
	NodoAlbero* first;
	int Nsub;
	int nElementi;
public:
	Albero();
	~Albero();
	void reSize(Punto min,Punto max);
	void print();
	void writeVTK(std::string nomeFile);
	Punto getLim(int n);
	NodoAlbero* getCommonNodo(std::vector<NodoAlbero*> o);
	NodoAlbero* getNodo(Punto);
	std::vector<NodoAlbero*> getNodiIntersectLinea(Punto o,Punto tg);
	std::vector<NodoAlbero*> getNodiIntersectPiano(Punto o,Punto tg);
	std::vector<NodoAlbero*> getNodiUnderPiano(Punto o,Punto tg);
	NodoAlbero* getNodoPoligono(Poligono* p);
};
class Vertice:public OggettoLista<Vertice>,public OggettoAlbero,public Punto{
	friend class Lato;
	friend class Poligono;
protected:
	Vettore<Lato*> lati;
	Vettore<Poligono*> poligoni;
	int name;
	Vertice* tmp;

	Vertice& operator=(const Vertice&);
	void operator+=(const Punto& v);
	void operator-=(const Punto& v);
	void operator*=(double c);
	void operator*=(const Punto& c);
	void operator/=(double c);
public:
	Vertice();
	Vertice(const Punto& a);
	Vertice& operator=(const Punto& v);
	void assign(const Punto& v);
	virtual ~Vertice();							//Distrugge quello giusto!
	virtual Vertice* check();					//Verifica se esiste già nella lista!
	virtual void print();
	virtual void cancel();						//Lo delinka dalla maglia di appartenenza (cancello i lati connessi)!
	virtual void link();						//Fa il down-casting per usare il link del Nodo + aggiunge il Vertice all'albero!
	virtual void linkA();						//Linka L'albero;
	Lato* getLato(int i);
	int getNumLati();
	Poligono* getPoligono(int i);
	int getNumPoligoni();
	void setNome(int nome);
	int getNome();
	Lato* isConnected(Vertice* a);
	void setTemp(Vertice* a);
	Vertice* getTemp();
	bool hasLato(Lato* l);
	bool hasPoligono(Poligono* p);
};
class Lato:public OggettoLista<Lato>,public OggettoAlbero{
	friend class Poligono;
protected:
	Vertice* vertici[2];
	Vettore<Poligono*> poligoni;
	Punto tangential;
	int name;
	Lato* tmp;

	Lato();
	Lato(const Lato&);
	Lato& operator=(const Lato&);
public:
	Lato(Vertice* a,Vertice* b);
	virtual ~Lato();						//Distrugge quello giusto!
	virtual Lato* check();					//Verifica se esiste già nella maglia!
	virtual void print();
	virtual void cancel();					//Cancello i poligoni e delinko i vertici connessi!
	virtual void erase();					//Chiamo cancell() e se Lati solitari li cancello!
	virtual void link();						//Linko ai vertici connessi, fa il down-casting per usare il link del Nodo!
	virtual void linkA();					//Linka L'albero;
	bool equal(Vertice*a, Vertice*b);
	bool equal(Lato &l);
	bool equal(const Punto& a, const Punto& b);
	Vertice* verticeComune(Lato* l);
	Vertice* getVertice(int i);
	Vertice* getAltroVertice(Vertice* v);
	Punto getTangential();
	void flipTangential();
	double getLenght();
	bool hasVertice(Vertice* v);
	bool hasPoligono(Poligono* p);
	void setNome(int nome);
	int getNome();
	void setTemp(Lato* a);
	Lato* getTemp();
	Poligono* poligonoComune(Lato* l);
	Poligono* getPoligono(int i);
	int getNumPoligoni();
	bool isBoundary();
	bool isNonManifold();
	Poligono* getAltroPoligono(Poligono* p);
};
class Poligono:public OggettoLista<Poligono>,public OggettoAlbero{
protected:
	Vettore<Lato*> lati;
	Vettore<Vertice*> vertici;
	Punto normal;
	int name;
	Poligono* tmp;
	std::string layer;

	Poligono();
	Poligono(const Poligono&);
	Poligono& operator=(const Poligono&);
public:
	Poligono(std::vector<Lato*> ls);
	virtual ~Poligono();							//Distrugge quello giusto!
	virtual Poligono* check();						//Verifica se esiste già nella maglia!
	virtual void print();
	virtual void cancel();							//Delinko i Lati connessi! Elimino solo il poligono
	virtual void erase();							//Chiamo cancell() e se Lati solitari li cancello!
	virtual void link();							//Linko ai Lati connessi, fa il down-casting per usare il link del Nodo!
	virtual void linkA();							//Linka L'albero;
	bool equal(Lato *a, Lato *b,Lato *c);
	bool equal(Lato *a, Lato *b,Lato *c,Lato* d);
	Lato* getLato(int i,bool circular=false);
	int getNumLati();
	Vertice* getVertice(int i,bool circular=false);
	int getNumVertici();
	Punto getNormal();
	void flipNormal();
	void setNome(int nome);
	int getNome();
	void setTemp(Poligono* a);
	Poligono* getTemp();
	bool hasVertice(Vertice* v);
	bool hasLato(Lato* v);
	Lato* altroLato(Lato* l,Vertice* v);
	Vertice* verticeOpposto(Lato* l);
	Vertice* verticeOpposto(Vertice* v);
	void setLayer(std::string);
	std::string getLayer();
	double getArea();
	Punto getCentro();
	Lato* latoComune(Poligono* p);
	Poligono* coherencedNormals();
};
#endif
