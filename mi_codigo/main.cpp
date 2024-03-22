  /*
  *  Programa principal.
  *
  *
  *               Autores : Antonio Sedeno Noda, Sergio Alonso.
  *               Cursos  : 2012-2021
  */

  #include <string.h>
  #include <limits>
  #include "grafo.h"

  void limpiarBufferEntrada() {
      // std::cin.ignore ignora el máximo número posible de caracteres
      // hasta que encuentra un salto de línea ('\n')
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }


  void menu (unsigned dirigido, char &opcion)
  //Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
  {
      cout << "Optimiza!cion en Grafos, 2023-2024 Acoidan Martín Conrado" << endl;
      cout << "c. [c]argar grafo desde fichero" << endl;
      if (dirigido == 0) //Grafo no dirigido
              {
              cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
              cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
              cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
              cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo" << endl;
              cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo" << endl;
              cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
              cout << "k. Mostrar arbol generador minimo coste, [k]ruskal" << endl;
              cout << "p. Mostrar arbol generador minimo coste, [p]rim" << endl;
        //Aqu� se a�aden m�s opciones al men� del grafo no dirigido
              }
      else
              {
              cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
              cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
              cout << "e. Mostrar la lista de pr[e]decesores del grafo" << endl;
              cout << "y. Mostrar la matriz de ad[y]acencia del grafo" << endl;
              cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sus sucesores" << endl;
              cout << "r. Realizar un recorrido en p[r]ofuncidad del grafo desde un nodo por sucesores" << endl;
              cout << "d. Caminos minimos: [d]ijkstra" << endl;
              cout << "v. Caminos minimos: Comparamos Dijkstra [v]s BellmanFordEnd" << endl;
              cout << "x. Caminos minimos: Modificacion de Pape y Dsopo" << endl;
              cout << "f. Caminos minimos [f]loyd-warshall" << endl;

        //Aqu� se a�aden m�s opciones al men� del grafo dirigido
              };
      cout << "q. Finalizar el programa" << endl;
      cout << "Introduce la letra de la accion a ejecutar  > ";
      cin >> opcion;
  };


  // El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
  int main(int argc, char *argv[])
  {
      int error_apertura{0};
      char nombrefichero[85], opcion;
      system("clear");
      //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
      if (argc > 1)
      {
    cout << "Cargando datos desde el fichero dado como argumento" << endl;
          strcpy(nombrefichero, argv[1]);
      }
      else
      {
          cout << "Introduce el nombre completo del fichero de datos" << endl;
          cin >> nombrefichero;
      };
      GRAFO G(nombrefichero, error_apertura);
      if (error_apertura == 1)
      {
          cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
          //pressanykey();
        system("clear");
      }
      else
      {
          cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
          // pressanykey();
          // system("clear");
          do
          {
              menu(G.Es_dirigido(), opcion);
              switch (opcion)
              {
                  case 'c' :
                      system("clear");
                cout << "Introduce el nombre completo del fichero de datos" << endl;
                      cin >> nombrefichero;
                      G.actualizar(nombrefichero, error_apertura);
                      if (error_apertura == 1)
                      {
                          cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                      }
                      else
                      {
                          cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                      };
                      // pressanykey();
                      // system("clear");
                      break;

                  case 'i' :
                    system("clear");
                      cout << "Grafo cargado desde " << nombrefichero << endl;
                      G.Info_Grafo();
                      limpiarBufferEntrada();
                      cout << endl << endl;
                      cout << "Introduce la letra [c] para continuar: ";
                      getchar();
                      system("clear");
                      break;

      //Situar aqu� el resto de opciones del men�
                  case 's':
                    system("clear");
                    cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Mostrar_Listas(1);
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;

                  case 'e':
                    system("clear");
                    G.Mostrar_Listas(-1);
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;

                  case 'y':
                    system("clear");
                    G.Mostrar_Matriz();
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;

                  case 'm':
                    system("clear");
                    G.RecorridoAmplitud();
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;
                  
                  case 'r':
                    system("clear");
                    G.RecorridoProfundidad();
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;

                  case 'a':
                    system("clear");
                    G.Mostrar_Listas(-1);
                    limpiarBufferEntrada();
                    cout << endl << endl;
                    cout << "Introduce la letra [c] para continuar: ";
                    getchar();
                    system("clear");
                    break;
                  // case 'o';
                  // case 'k';
                  // case 'p';
                  // case 'd':
                  // case 'v':
                  // case 'x':
                  // case 'f':
              }
      }
      while (opcion != 'q');
      }
      system("clear");
      cout << "Fin del programa" << endl;
      cout << "Saliendo" << endl;
    return(0);
  };
