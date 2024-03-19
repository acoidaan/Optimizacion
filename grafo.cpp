 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"
#include <cassert>

void GRAFO :: destroy() {
	for (unsigned i=0; i< n; i++) {
		LS[i].clear();
		A[i].clear();
		if(dirigido == 1) {
            LP[i].clear();
        };
	  }
	LS.clear();
	LP.clear();
	A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura) {
  ElementoLista dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
        // leemos los m arcos
		for (k=0;k<m;k++) {
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			dummy.j = j - 1;
      LS[i - 1].push_back(dummy);
      if (dirigido == 1) {
        dummy.j = i - 1;
        LP[j - 1].push_back(dummy);
      } else {
        assert( i != j);
        dummy.j = i - 1;
        LS[j - 1].push_back(dummy);
      }
    }
    textfile.close();
    errorapertura = 0;
      
      
      //damos los valores a dummy.j y dummy.c
			//situamos en la posici�n del nodo i a dummy mediante push_back
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			//pendiente la construcci�n de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
			//...}
  }
}

GRAFO::~GRAFO() {
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
	build (nombrefichero, errorapertura);
}

void GRAFO::actualizar(char nombrefichero[85], int &errorapertura) {
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido() {
  return dirigido;
}

void GRAFO::Info_Grafo() {
  cout << "Información del grafo: " << endl;
  cout << "Número de nodos: " << n << endl;
  cout << "Número de arcos/aristas: " << m << endl;
  if (dirigido == 1) {
    cout << "El grafo es dirigido." << endl;
  } else {
    cout << "El grafo no es dirigido. " << endl;
  }
}

void Mostrar_Lista(vector<LA_nodo> L) {
  for (const auto &nodo : L) {
    for (const auto &elemento : nodo) {
      cout << "Nodo: " << elemento.j + 1 << "Peso: " << elemento.c << endl;
    }
  }
}

void GRAFO::Mostrar_Listas (int l) {
  if (l == -1) { // Si el grafo es no dirigido o queremos mostrar predecesores 
    if(Es_dirigido()) { // Si es dirigido, mostramos predecesores
      cout << "Lista de predecesores por nodo: " << endl;
      for(unsigned i = 0; i < LP.size(); ++i) {
        cout << "Nodo " << i + 1 << " :";
        for (auto &adyacente : LP[i]) {
          cout << " " << adyacente.j + 1 << "(Coste: " << adyacente.c << ")";
        }
        cout << endl;
      }
    } else { // Si el grafo es no dirigido, mostramos la lista de adyacencia
      cout << "Lista de adyacencia por nodo: " << endl;
      for(unsigned i = 0; i < LS.size(); ++i) {
        cout << "Nodo " << i + 1 << " :";
        for(auto &adyacente : LS[i]) {
          cout << " " << adyacente.j + 1 << "(Coste: " << adyacente.c << ")";
        }
        cout << endl;
      }
    }
  } else if (l == 1) {  // Si queremos mostrar sucesores
    cout << "Lista de sucesores por nodo: " << endl;
    for(unsigned i = 0; i < LS.size(); ++i) {
      cout << "Nodo " << i + 1 << " :";
      for (auto &adyacente : LS[i]) {
        cout << " " << adyacente.j + 1 << "(Coste: " << adyacente.c << ")";
      }
      cout << endl;
    }
  } else if (l == 0) {  // Mostrar solo la lista de adyacencia
  cout << "Lista de adyacencia por nodo: " << endl;
  for (unsigned i = 0; i < A.size(); ++i) {
    cout << "Nodo " << i + 1 << " :";
    for(auto &adyacente : A[i]) {
      cout << " " << adyacente.j + 1 << "(Coste " << adyacente.c << ")";
    }
    cout << endl;
  }
  } else {
  cout << "El parametro introducido no es valido" << endl;
  }
}

void GRAFO::Mostrar_Matriz() {//Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes

}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) {//Recorrido en profundidad recursivo con recorridos enum y postnum
	visitado[i] = true;
  prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
  for (unsigned j=0;j<L[i].size();j++) {
    if (!visitado[L[i][j].j]) {
      dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
    };
  postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}
}

void GRAFO::RecorridoProfundidad() {
  vector<bool> visitado;
  visitado.resize(n, false);

  vector<unsigned> prenum;
  prenum.resize(n, 0);
  vector<unsigned> postnum;
  postnum.resize(n, 0);

  unsigned prenum_ind = 0;
  unsigned postnum_ind = 0;

  unsigned i;

  cout << "Introduzca el nodo inicial: ";
  cin >> (unsigned &) i;

  dfs_num(i - 1, LS, visitado, prenum, prenum_ind, postnum, postnum_ind);
  // Imprimir prenum y postnum
}

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) {//vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola

    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);
    visitado[i] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i] = i;
    d[i] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1
    while (!cola.empty()) {//al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
      unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
      cola.pop(); //lo sacamos de la cola
      //Hacemos el recorrido sobre L desde el nodo k+1
      for (unsigned j = 0; j < L[k].size(); j++) {
        //Recorremos todos los nodos u adyacentes al nodo k+1
        //Si el nodo u no est� visitado
        if (!visitado[L[k][j].j]) {
        //Lo visitamos
          visitado[L[k][j].j] = true;
        //Lo metemos en la cola
          cola.push(L[k][j].j);
        //le asignamos el predecesor
          pred[L[k][j].j] = k;
        //le calculamos su etiqueta distancia
          d[L[k][j].j] = d[k] + 1;
        }
      }
        //Hemos terminado pues la cola está vacía
    };
}

void GRAFO::RecorridoAmplitud() { //Construye un recorrido en amplitud desde un nodo inicial
  unsigned i;
  vector<unsigned> pred;
  vector<unsigned> d;

  cout << "Introduzca el nodo inicial (1<= nodo <= n): ";
  cin >> (unsigned &) i;

  bfs_num(i - 1, LS, pred, d);

  
}