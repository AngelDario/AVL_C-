#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

struct NODE {
	int valor;
	int peso;
	NODE* nodes[2];

	NODE(int _valor) : valor(_valor) {
		peso = 0;
		nodes[0] = nodes[1] = 0;
	}
};

class CTREE {
public:
	NODE* m_root;
	int altura;

	CTREE(){
		m_root = 0;
		altura = 0;
	}

	bool find(int x, NODE**& p) {
		p = &m_root;
		while (*p && (*p)->valor != x) {
			p = &((*p)->nodes[x > (*p)->valor]);
		}
		return *p != 0;
	}

	//SOBRECARGA DEL METODO FIND PARA REGISTRAR EL RECORRIDO
	bool find(int x, NODE**& p, NODE***& recorrido, int& recorridoTam) {
		p = &m_root;
		int i = 0;
		recorrido[i] = p ;

		while (*p && (*p)->valor != x) {
			p = &((*p)->nodes[x > (*p)->valor]);
			i++;
			recorrido[i] = p;
			recorridoTam++;
		}

		return *p != 0;
	}

	bool insert(int x) {
		NODE** p;
		//HACIENDO LISTA CON EL RECORRIDO DEL NODO QUE SE VA A INSERTAR
		NODE*** recorrido = new NODE * *[100];
		int recorridoTam = 0;

		if (find(x, p, recorrido, recorridoTam)) {// FIND MODIFICADO CON EL TAMAÑO DEL RECORRIDO
			return 0;
		}
		
		*p = new NODE(x);
		recorrido[recorridoTam] = p; //INSERTANDO EL ULTIMO NODO EN EL RECORRIDO

		//AJUSTANDO PESOS DE LOS NODOS

		if (recorridoTam > altura) {
			for (int i = recorridoTam - 1; i >= 0; i--) {
				if (*(recorrido[i + 1]) == (*(recorrido[i]))->nodes[1]) {
					(*(recorrido[i]))->peso += 1;
					if ((*(recorrido[i]))->peso <= -2 && (*(recorrido[i]))->peso >= 2) {

					}
				}
				else {
					(*(recorrido[i]))->peso -= 1;
				}
			}
		}
		//if(recorridoTam > 0){
		//	if ((*(recorrido[recorridoTam - 1]))->nodes[0] == 0 && (*(recorrido[recorridoTam - 1]))->nodes[1] == 0) {
		//		for (int i = recorridoTam - 1; i >= 0; i--) {
		//			if (*(recorrido[i + 1]) == (*(recorrido[i]))->nodes[1]) {
		//				(*(recorrido[i]))->peso += 1;
		//			}
		//			else {
		//				(*(recorrido[i]))->peso -= 1;
		//			}
		//		}
		//	}
		//}

		//VERIFICANDO SI HAY ALGUN PESO FUERA DEL RANGO DE PESO

		//for (int i = 0; i < recorridoTam; i++) {
		//	if ((*(recorrido[i]))->peso <= -2 && (*(recorrido[i]))->peso >= 2) {
		//		//TIPO DE DESBALANCE


		//	}
		//}

		return 1;
	}

	NODE** REP(NODE** p) {
		srand(time(NULL));
		bool random = rand()%2;
		if ((*p)->nodes[random]) {
			p = &((*p)->nodes[random]);
			while((*p)->nodes[!random]){
				p = &((*p)->nodes[!random]);
			}
			return p;
		}
		p = &((*p)->nodes[!random]);
		while ((*p)->nodes[random]) {
			p = &((*p)->nodes[random]);
		}
		return p;
	}

	bool remove(int x) {
		NODE** p;
		if (!find(x, p)) {
			return 0;
		}
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			NODE** q = REP(p);
			(*p)->valor = (*q)->valor;
			p = q;
		}
		NODE* temp = *p;
		*p = (*p)->nodes[!(*p)->nodes[0]];
		delete temp;
		return 1;
	}

	void inorder(NODE* k) {
		if (!k) return;
		inorder(k->nodes[0]);
		cout << k->valor <<"<"<<k->peso<<">"<<"->";
		inorder(k->nodes[1]);
	}

	void pre_order(NODE* k) {
		if (!k) return;
		cout << k->valor << "->";
		pre_order(k->nodes[0]);
		pre_order(k->nodes[1]);
	}
	
	void post_order(NODE* k) {
		if (!k) return;
		post_order(k->nodes[0]);
		post_order(k->nodes[1]);
		cout << k->valor << "->";
	}

};

//n=(*p)->NODE

int main()
{
	CTREE arbol;
	int x;
	arbol.insert(2);
	arbol.insert(5);
	arbol.insert(4);
	arbol.insert(3);
	arbol.insert(1);
	arbol.insert(9);
	arbol.insert(8);
	arbol.insert(6);
	arbol.insert(7);
	while (1) {
		cout << "Inorder: ";
		arbol.inorder(arbol.m_root);
		cout << endl;
		cout << "Pre-order: ";
		arbol.pre_order(arbol.m_root);
		cout << endl;
		cout << "Post-order: ";
		arbol.post_order(arbol.m_root);
		cout << endl;
		cin >> x;
		arbol.remove(x);
		cout << endl;
	}

	return 0;
}
