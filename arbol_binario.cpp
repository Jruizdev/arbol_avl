#include <iostream>
#include <math.h>

using namespace std;

// Estructura de un nodo
class Nodo 
{
	
	public:
		
		int dato;
		Nodo *padre;
		Nodo *izq;
		Nodo *der;
	
};


// Estructura de un árbol binario
class ArbolBinario 
{
	
	public:
		
		// Crar nueva raiz del árbol
		void crearArbol (int raiz) 
		{
			raiz_arbol = crearNodo (raiz);
		}
		
		// Imprimir elementos del árbol (in-orden)
		void recorrerArbol () 
		{
			if (raiz_arbol == NULL) return;
			inOrden (raiz_arbol);
		}
		
		// Agregar nuevo elemento al árbol
		int agregarNodo (int dato) 
		{
			return insertar (raiz_arbol, dato);
		}
		
		int eliminarNodo (int dato) 
		{
			Nodo *elemento = buscarNodo (raiz_arbol, dato);
			
			// El elemento a eliminar se encuentra en el árbol
			if (elemento != NULL) {
				return eliminar (elemento);
			}
			// El elemento a eliminar no se encuentra en el árbol
			else {
				cout << "\n\t[!]: El elemento a eliminar no se encuentra en el arbol." << endl;
			}
			return -1;
						
		}
		
		void calcularBalanceo () 
		{
			if(raiz_arbol == NULL) {
				cout << "\n\t[!]: El arbol se encuentra vacio." << endl;
				return;
			}
			// Calcular diferencia entre los nodos de los sub-árboles
			int diferencia = cantidadNodos (raiz_arbol->der) - cantidadNodos(raiz_arbol->izq);
			int nodos_necesarios = diferencia / 2;
			
			// Validar si sobrepasa el límite del balanceo
			if(diferencia > 1 || diferencia < -1) {
				// Es necesario balancear
				cout << "\n\tEs necesario mover:\n\t" << abs(nodos_necesarios) << " nodos a al ";
				if(nodos_necesarios < 2) 
					cout << "sub-arbol derecho para balancear." << endl;
				else 
					cout << "sub-arbol izquierdo para balancear." << endl;
			}
			// No es necesario balancear 
			else {
				cout << "\n\tEl arbol se encuentra balanceado." << endl;
			}
		}
		
	private:
		
		// Raíz del árbol
		Nodo *raiz_arbol;
		
		Nodo *crearNodo (int dato) 
		{
			Nodo *nuevo = new Nodo();
			nuevo->dato = dato;
			
			return nuevo;
		}
		
		void destruirNodo (Nodo *nodo) 
		{
			
			nodo->izq = NULL;
			nodo->der = NULL;
			
			delete nodo;
		}
		
		// Calcular cantidad de nodos asociados a un elemento (raiz)
		int cantidadNodos (Nodo *raiz) 
		{
			
			if (raiz != NULL) {
				int izq = cantidadNodos (raiz->izq);
				int der = cantidadNodos (raiz->der);
				int _raiz = 1;
				
				return _raiz + izq + der;
			}
			return 0;
		}
		
		// Recorrido In-Orden del árbol
		void inOrden (Nodo *raiz) 
		{
			
			if (raiz->izq != NULL) inOrden (raiz->izq);
			cout << raiz->dato << " ";
			if (raiz->der != NULL) inOrden (raiz->der);
			
		}
		
		// Buscar un elemento específico
		Nodo *buscarNodo (Nodo *raiz, int dato) 
		{
			
			// Dato no encontrado
			if (raiz == NULL) return NULL;
			
			// Dato encontrado
			if (dato == raiz->dato) return raiz;
			
			// Buscar elemento a la izquierda
			if (dato < raiz->dato) {
				if (raiz->izq != NULL) return buscarNodo (raiz->izq, dato);
			}
			// Buscar elemento a la derecha
			else if (dato > raiz->dato) {
				if (raiz->der != NULL) return buscarNodo (raiz->der, dato);
			}
			
			return NULL;
		}
		
		int insertar (Nodo *raiz, int dato) 
		{
			
			if (raiz == NULL) {
				crearArbol (dato);
				return 1;
			}
			
			// Buscar espacio en el sub-árbol izquierdo
			if (dato < raiz->dato) {
				if (raiz->izq != NULL) return insertar (raiz->izq, dato);
				else {
					raiz->izq = crearNodo (dato);
					raiz->izq->padre = raiz;
					return 1;
				}
			}
			// Buscar espacio en el sub-árbol derecho
			else if (dato > raiz->dato) {
				if (raiz->der != NULL) return insertar (raiz->der, dato);
				else {
					raiz->der = crearNodo (dato);
					raiz->der->padre = raiz;
					return 1;
				}
			}
			return -1;
		}
		
		int eliminar (Nodo *nodo_eliminar) 
		{
			
			if (nodo_eliminar == NULL) return -1;
			
			// El nodo a eliminar contiene hijo izquierdo y derecho
			if(nodo_eliminar->izq != NULL && nodo_eliminar->der != NULL) {
				Nodo *reemplazo;
				reemplazo = nodo_eliminar->izq;
				
				while (reemplazo->der != NULL) {
					reemplazo = reemplazo->der;
				}
				nodo_eliminar->dato = reemplazo->dato;
				return eliminar (reemplazo);
			}
			// El nodo a eliminar solo contiene hijo izquierdo
			else if (nodo_eliminar->izq != NULL) {
				reemplazarNodo (nodo_eliminar, nodo_eliminar->izq);
				destruirNodo (nodo_eliminar);
				return 1;
			}
			// El nodo a eliminar solo contiene hijo derecho
			else if (nodo_eliminar->der != NULL) {
				reemplazarNodo (nodo_eliminar, nodo_eliminar->der);
				destruirNodo (nodo_eliminar);
				return 1;
			}
			// El nodo a eliminar no contiene hijos
			else {
				reemplazarNodo (nodo_eliminar, NULL);
				destruirNodo (nodo_eliminar);
				return 1;
			}
			
			return -1;
		}
		
		void reemplazarNodo (Nodo *anterior, Nodo *nuevo) 
		{
			
			if (anterior->padre != NULL) {
				// El nodo anterior se encuentra en el sub-árbol izquierdo de su padre
				if (anterior == anterior->padre->izq) {
					anterior->padre->izq = nuevo;
				}
				// El nodo anterior se encuentra en el sub-árbol derecho de su padre
				else if (anterior == anterior->padre->der) {
					anterior->padre->der = nuevo;
				}
			}
			// Se debe reemplazar con la raíz del árbol
			else {
				raiz_arbol = nuevo;
			}
			
			// Asignar padre del elemento a reemplazar
			if (nuevo != NULL) {
				nuevo->padre = anterior->padre;
			}
			
		}
	
};

// PROTOTIPOS DE MÉTODOS DEL PROGRAMA PRINCIPAL
void crearNodo (ArbolBinario*);
void eliminarNodo (ArbolBinario*);
void conteo (ArbolBinario*);
void recorrerArbol (ArbolBinario*);


// ** PROGRAMA PRINCIPAL ** //
int main () 
{
	ArbolBinario *arbol = new ArbolBinario ();
	
	char _opcion[] = "";
	int opcion;
	bool salir;
	
	while (!salir) {
		// Mostrar menú
		cout << "\n\t---------------------------------------------------------" << endl;
		cout << "\t|\tARBOLES BINARIOS BALANCEADOS\t\t\t|" << endl;
		cout << "\t---------------------------------------------------------" << endl;
		cout << "\t|\tOpciones disponibles:\t\t\t\t|" << endl;
		cout << "\t|\t\t\t\t\t\t\t|" << endl;
		cout << "\t|\t1) Crear nuevo nodo.\t\t\t\t|" << endl;
		cout << "\t|\t2) Eliminar nodo.\t\t\t\t|" << endl;
		cout << "\t|\t3) Conteo de nodos para balanceo de arbol.\t|" << endl;
		cout << "\t|\t4) Recorrer arbol.\t\t\t\t|" << endl;
		cout << "\t|\t5) Salir del programa.\t\t\t\t|" << endl;
		cout << "\t|\t\t\t\t\t\t\t|" << endl;
		cout << "\t---------------------------------------------------------\n" << endl;
		cout << "\tSeleccione la opcion deseada: ";
		
		cin >> _opcion;
		opcion = atoi(_opcion);
		system("cls");
		
		switch (opcion) {
			// Crear nuevo nodo
			case 1:
				crearNodo(arbol);
				break;
			// Eliminar nodo
			case 2:
				eliminarNodo(arbol);
				break;
			// Conteo de nodos para el balanceo
			case 3:
				conteo (arbol);
				break;
			// Recorrer árbol (imprimir elementos)
			case 4:
				recorrerArbol (arbol);
				break;
			// Salir
			case 5:
				salir = true;
				break;

			// Opcion no válida
			default:
				cout << "\n\t[!]: La opcion ingresada no es valida." << endl;
		}
		
	}
	
	return 0;
}


// ** MÉTODOS DEL PROGRAMA ** //
void crearNodo (ArbolBinario *arbol){
	
	char _dato[] = "";
	int dato;
	
	cout << "\n\t-------------------------------------------------" << endl;
	cout << "\t|\tCREAR NUEVO NODO\t\t\t|" << endl;
	cout << "\t-------------------------------------------------" << endl;
	cout << "\t> Ingrese el nuevo elemento: ";
	
	cin >> _dato;
	dato = atoi(_dato);
	system ("cls");
	
	if (arbol->agregarNodo(dato) == 1) 
		cout << "\n\tEl elemento " << dato << " fue creado y agregado correctamente." << endl;
	else 
		cout << "\n\t[Error]: El elemento no pudo ser creado" << endl;
}

void eliminarNodo (ArbolBinario *arbol){
	
	char _dato[] = "";
	int dato;
	
	cout << "\n\t-------------------------------------------------" << endl;
	cout << "\t|\t\tELIMINAR NODO\t\t\t|" << endl;
	cout << "\t-------------------------------------------------" << endl;
	cout << "\t> Que nodo o elemento desea eliminar? : ";
	
	cin >> _dato;
	dato = atoi(_dato);
	system ("cls");
	
	if (arbol->eliminarNodo(dato) == 1) 
		cout << "\n\tEl elemento " << dato << " fue eliminado del arbol." << endl;
	else 
		cout << "\n\t[Error]: El elemento no pudo ser eliminado" << endl;
	
}

void conteo (ArbolBinario *arbol){
	arbol->calcularBalanceo();
}

void recorrerArbol (ArbolBinario *arbol){
	
	cout << "\n\tElementos contenidos en el arbol:\n\t";
	arbol->recorrerArbol();
	cout << endl;
	
}