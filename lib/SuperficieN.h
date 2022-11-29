#ifndef SUPERFICIE_N
#define SUPERFICIE_N

#include "BaseN.h"
class Superficie{
protected:
	Albero* Valbero;
	Lista<Vertice>* V;
	Lista<Lato>* L;
	Lista<Poligono>* P;
	bool typePoligoni[2];
	Vettore<std::string> layersPol;
	Vettore<double>* limit;

	virtual Vertice* creaVertice(const Punto& p);
	virtual Lato* creaLato(Vertice*a,Vertice*b);
	virtual Poligono* creaPoligono(std::vector<Lato*> ls);
public:
	Superficie();
	Superficie(const Superficie& s);
	virtual ~Superficie();
	Superficie& operator=(const Superficie& s);
	void readSTL(std::string nomeFile);
	void writeSTL(std::string nomeFile);
	void writeSTLMulti(std::string nomeFile,bool separated=false);
	void print();
	void addPoligono(std::vector<Punto> ls,std::string layer="");
	int numeroVertici();
	int numeroLati();
	int numeroPoligoni();
	int numeroBoundary();
	void rotazione(Punto asse, Punto origine, double angolo);
	void traslazione(Punto vettore);
	void scala(Punto origine,Punto fattore);
	void specchia(Punto origine,Punto asse,bool copy=false);
	Vettore<double> Hydrostatic(Punto Origine,Punto Normale); //Volum,BX,BY,BZ,Superface
	Vettore<double> HydrostaticFast(Punto Origine,Punto Normale); //Volum,BX,BY,BZ,Superface
	Vettore<double> Section(Punto Origine,Punto Normale); //Area,FX,FY,FZ,Ix,Iy,Lwl,Bwl
	Vettore<double> SectionFast(Punto Origine,Punto Normale); //Area,FX,FY,FZ,Ix,Iy,Lwl,Bwl
	Superficie Cut(Punto Origine,Punto Normale); //It use the same algorithm of Hydrostatic but it provides the hull sectioned.
	bool isclosed();
	void coherencedNormals();
	void flipNormals();
	Vettore<double> bounds(); //xmax,ymax,zmax,xmin,ymin,zmin
};
#endif
