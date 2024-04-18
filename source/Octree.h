#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    double valorX;
    double valorY;
    double valorZ;
    /*
    Point(){
        valorX = -1.0;
        valorY = -1.0;
        valorZ = -1.0;
    }
     */

    Point(double _valorX, double _valorY, double _valorZ) {
        valorX = _valorX;
        valorY = _valorY;
        valorZ = _valorZ;
    }
};

class OcTree{
private:

    Point *extremoMin;
    double longitudLado; //Point *extremoMax;

    int maxNumPoints; // GRANULARIDAD: el numero maximo de puntos que soportara un cubo

    OcTree *hijos[8]; // Cada uno de sus 8 hijos seran de tipo Octree
    Point *puntos;
    int nPoints; // numero de puntos insertados
    //int profundidad;
    bool isLeaf;
    bool haveChildrens;


public:

    vector< vector<double> > allSizes; // Se guardaran todos puntos para hacer el cuadrante
    /*
    // Constructor para los hijos
    OcTree(){
        puntos = new Point();
    }
     */

    // MAIN CONSTRUCTOR
    OcTree(double xMin, double yMin, double zMin, double _longitudLado, int granularidad){

        maxNumPoints = granularidad;
        extremoMin = new Point(xMin, yMin, zMin);
        longitudLado = _longitudLado;

        puntos = new Point(-1,-1,-1);

        //nPoints = _nPoints;
        nPoints = 0;
        //profundidad = 0;
        isLeaf = true;
        haveChildrens = false;
    }

    void PrintEnds(){
        cout << "-------------------------------------" << endl;
        cout << "Minimos:" << endl;
        cout << "X:" << extremoMin->valorX << " y Y: " << extremoMin->valorY << endl;
        cout << "Maximos:" << endl;
        cout << "X:" << longitudLado << " y Y: " << longitudLado << endl;
        cout << "-------------------------------------" << endl;
    }

    void splitOctree(OcTree &nodoActual){

        double longitudLadoAux = nodoActual.longitudLado/2;

        // Cubos de abajo
        double x_min0 = nodoActual.extremoMin->valorX;
        double y_min0 = nodoActual.extremoMin->valorY;
        double z_min0 = nodoActual.extremoMin->valorZ;
        nodoActual.hijos[0] = new OcTree(x_min0, y_min0, z_min0, longitudLadoAux, maxNumPoints);
        vector<double> aux0;
        aux0.push_back( x_min0 );
        aux0.push_back( y_min0 );
        aux0.push_back( z_min0 );
        aux0.push_back( longitudLadoAux );
        allSizes.push_back(aux0);

        double x_min1 = nodoActual.extremoMin->valorX + nodoActual.longitudLado/2;
        double y_min1 = nodoActual.extremoMin->valorY;
        double z_min1 = nodoActual.extremoMin->valorZ;
        nodoActual.hijos[1] = new OcTree(x_min1, y_min1, z_min1, longitudLadoAux, maxNumPoints);
        vector<double> aux1;
        aux1.push_back( x_min1 );
        aux1.push_back( y_min1 );
        aux1.push_back( z_min1 );
        aux1.push_back( longitudLadoAux );
        allSizes.push_back(aux1);

        double x_min2 = nodoActual.extremoMin->valorX;
        double y_min2 = nodoActual.extremoMin->valorY + nodoActual.longitudLado/2;
        double z_min2 = nodoActual.extremoMin->valorZ;
        nodoActual.hijos[2] = new OcTree(x_min2, y_min2, z_min2,longitudLadoAux, maxNumPoints);
        vector<double> aux2;
        aux2.push_back( x_min2 );
        aux2.push_back( y_min2 );
        aux2.push_back( z_min2 );
        aux2.push_back( longitudLadoAux );
        allSizes.push_back(aux2);

        double x_min3 = nodoActual.extremoMin->valorX + nodoActual.longitudLado/2;
        double y_min3 = nodoActual.extremoMin->valorY + nodoActual.longitudLado/2;
        double z_min3 = nodoActual.extremoMin->valorZ;
        nodoActual.hijos[3] = new OcTree(x_min3, y_min3, z_min3, longitudLadoAux, maxNumPoints);
        vector<double> aux3;
        aux3.push_back( x_min3 );
        aux3.push_back( y_min3 );
        aux3.push_back( z_min3 );
        aux3.push_back( longitudLadoAux );
        allSizes.push_back(aux3);

        // Cubos de arriba
        double x_min4 = nodoActual.extremoMin->valorX;
        double y_min4 = nodoActual.extremoMin->valorY;
        double z_min4 = nodoActual.extremoMin->valorZ + nodoActual.longitudLado/2;
        nodoActual.hijos[4] = new OcTree(x_min4, y_min4, z_min4, longitudLadoAux, maxNumPoints);
        vector<double> aux4;
        aux4.push_back( x_min4 );
        aux4.push_back( y_min4 );
        aux4.push_back( z_min4 );
        aux4.push_back( longitudLadoAux );
        allSizes.push_back(aux4);

        double x_min5 = nodoActual.extremoMin->valorX + nodoActual.longitudLado/2;
        double y_min5 = nodoActual.extremoMin->valorY;
        double z_min5 = nodoActual.extremoMin->valorZ + nodoActual.longitudLado/2;
        nodoActual.hijos[5] = new OcTree(x_min5, y_min5, z_min5, longitudLadoAux, maxNumPoints);
        vector<double> aux5;
        aux5.push_back( x_min5 );
        aux5.push_back( y_min5 );
        aux5.push_back( z_min5 );
        aux5.push_back( longitudLadoAux );
        allSizes.push_back(aux5);

        double x_min6 = nodoActual.extremoMin->valorX;
        double y_min6 = nodoActual.extremoMin->valorY + nodoActual.longitudLado/2;
        double z_min6 = nodoActual.extremoMin->valorZ + nodoActual.longitudLado/2;
        nodoActual.hijos[6] = new OcTree(x_min6, y_min6, z_min6, longitudLadoAux, maxNumPoints);
        vector<double> aux6;
        aux6.push_back( x_min6 );
        aux6.push_back( y_min6 );
        aux6.push_back( z_min6 );
        aux6.push_back( longitudLadoAux );
        allSizes.push_back(aux6);


        double x_min7 = nodoActual.extremoMin->valorX + nodoActual.longitudLado/2;
        double y_min7 = nodoActual.extremoMin->valorY + nodoActual.longitudLado/2;
        double z_min7 = nodoActual.extremoMin->valorZ + nodoActual.longitudLado/2;
        nodoActual.hijos[7] = new OcTree(x_min7, y_min7, z_min7, longitudLadoAux, maxNumPoints);
        vector<double> aux7;
        aux7.push_back( x_min7 );
        aux7.push_back( y_min7 );
        aux7.push_back( z_min7 );
        aux7.push_back( longitudLadoAux );
        allSizes.push_back(aux7);

        cout << "** Divicion completada **" << endl;
    }

    bool isIn(OcTree &nodoActual, Point puntosAux,int pos){
        //cout << nodoActual.hijos[pos]->extremoMin->valorX << endl;
        double extremoX = nodoActual.hijos[pos]->extremoMin->valorX;
        double extremoY = nodoActual.hijos[pos]->extremoMin->valorY;
        double extremoZ = nodoActual.hijos[pos]->extremoMin->valorZ;
        double longitud = nodoActual.hijos[pos]->longitudLado;

        double pntoX = puntosAux.valorX;
        double pntoY = puntosAux.valorY;
        double pntoZ = puntosAux.valorZ;

        cout << extremoX << " < " << pntoX << " < " << extremoX+longitud << "?" << endl;
        if( pntoX >= extremoX && pntoX <= extremoX+longitud ){
            cout << "Si en x" << endl;
            cout << extremoY << " < " << pntoY << " < " << extremoY+longitud << "?" << endl;
            if( pntoY >= extremoY && pntoY <= extremoY+longitud ){
                cout << "Si en y" << endl;
                cout << extremoZ << " < " << pntoZ << " < " << extremoZ+longitud << "?" << endl;
                if( pntoZ >= extremoZ && pntoZ <= extremoZ+longitud ){
                    cout << "Si en z" << endl;
                    cout << "Entroooo" << endl;
                    return true;
                }
            }
        }
        cout << "no entra" << endl;
        return false;
    }

    int chooseGroup(OcTree &nodoActual, Point puntosAux){
        cout << "Eligiendo para: " << puntosAux.valorX << " - " << puntosAux.valorY << " - " << puntosAux.valorZ << endl;

        for(int i = 0; i < 8; i++){ // Recorre los 8 hijos
            cout << "Analizando cuadrante " << i << endl;
            //cout << nodoActual.hijos[i]->extremoMin->valorX << endl;
            if( isIn(nodoActual, puntosAux, i) ){ // Pregunta si el nodo pertenece al grupo i
                cout << "Entra en el cuadrado " << i << endl;
                return i;
            }
        }
        cout << "No se encontro un cuadrante para insertarlo. Saliendo del programa" << endl;
        exit(1);
    }

    void insert(double xPoint, double yPoint, double zPoint, OcTree &nodoActual){

        cout << "Insertando: " << xPoint << " - " << yPoint << " - " << zPoint << endl;
        cout << "NPuntos(Antes): " << nodoActual.nPoints << endl;

        // solo entra si el nodo actual es una hoja y si NO supera el maximo de puntos
        if (nodoActual.isLeaf == true && nodoActual.nPoints < maxNumPoints){
            cout << "Es hoja + limite aceptado" << endl;

            Point *aux = new Point(xPoint, yPoint, zPoint);
            nodoActual.puntos[nodoActual.nPoints].valorX = aux->valorX;
            nodoActual.puntos[nodoActual.nPoints].valorY = aux->valorY;
            nodoActual.puntos[nodoActual.nPoints].valorZ = aux->valorZ;
            cout << "**Dato insertado **" << endl;

            nodoActual.nPoints++;
            cout << "NPuntos(Ahora): " << nodoActual.nPoints << endl;
        }
        else{
            cout << "Supera granularidad" << endl;
            if(nodoActual.isLeaf == true){ // si es una hoja -> DIVIDE y reinserta
                cout << " ** Es una hoja - Dividiendo **  " << endl;

                splitOctree(nodoActual);
                nodoActual.isLeaf = false;
                nodoActual.haveChildrens = true;

                cout << "------------ Cuadrantes -------------" << endl;
                cout << "Con Longitud:" << (nodoActual.longitudLado)/2 << endl;
                for(int i = 0; i < 8; i++){
                    cout << "Cuadrante " << i << " -> " << nodoActual.hijos[i]->extremoMin->valorX << " - " << nodoActual.hijos[i]->extremoMin->valorY << " - " << nodoActual.hijos[i]->extremoMin->valorZ << endl;
                }
                cout << "-------------------------------------" << endl;

                // ###################### REINSERTAR NODOS #################################
                cout << "Insertando Temporalmente al nuevo dato 1" << endl; 
                nodoActual.puntos[nodoActual.nPoints].valorX = xPoint;
                nodoActual.puntos[nodoActual.nPoints].valorY = yPoint;
                nodoActual.puntos[nodoActual.nPoints].valorZ = zPoint;

                nodoActual.nPoints++;
                cout << "NPuntos(Ahora): " << nodoActual.nPoints << endl;

                for(int i = 0; i < nodoActual.nPoints; i++){
                    cout << "** ReInsert " << i+1 << " **" << endl;
                    //cout << nodoActual.puntos[i].valorX << " - " << nodoActual.puntos[i].valorY << endl;

                    cout << "------------ Cuadrantes aux -------------" << endl;
                    cout << "Con Longitud:" << (nodoActual.longitudLado)/2 << endl;
                    for(int i = 0; i < 8; i++){
                        cout << "Cuadrante " << i << " -> " << nodoActual.hijos[i]->extremoMin->valorX << " - " << nodoActual.hijos[i]->extremoMin->valorY << " - " << nodoActual.hijos[i]->extremoMin->valorZ << endl;
                    }
                    cout << "-------------------------------------" << endl;

                    int group = chooseGroup( nodoActual, nodoActual.puntos[i]);
                    cout << "Grupo al que pertenece: " << group << endl;

                    insert(nodoActual.puntos[i].valorX, nodoActual.puntos[i].valorY, nodoActual.puntos[i].valorZ, *nodoActual.hijos[group] );
                    //sleep(1);
                    cout << "--------------- FIN DEL REINSERT ----------------------" << endl;
                }

                // Eliminar Nodos ya re insertados:
                cout << "------ para eliminar 1-----------" << endl;
                cout << "Actualmente hay: " << nodoActual.nPoints <<  " puntos"<< endl;
                int auxDelete = nodoActual.nPoints;
                for(int i = 0; i < auxDelete ; i++){
                    nodoActual.nPoints = nodoActual.nPoints - 1;
                    //delete
                }
                cout << "naw: " << nodoActual.nPoints <<  " puntos"<< endl;

            }
            else{ // Si no es una hoja -> recorre sus hijos
                cout << " ** Recorriendo hojas **" << endl;
                cout << "Insertando Temporalmente al nuevo dato 2" << endl;

                nodoActual.puntos[nodoActual.nPoints].valorX = xPoint;
                nodoActual.puntos[nodoActual.nPoints].valorY = yPoint;
                nodoActual.puntos[nodoActual.nPoints].valorZ = zPoint;

                nodoActual.nPoints++;
                cout << "NPuntos(Ahora): " << nodoActual.nPoints << endl;

                cout << "Viendo a que hijo ira el dato temporal" << endl;

                cout << "Para puntos: " << nodoActual.puntos[nodoActual.nPoints-1].valorX << " - " << nodoActual.puntos[nodoActual.nPoints-1].valorY << " - " << nodoActual.puntos[nodoActual.nPoints-1].valorZ << endl;

                cout << "------------ Cuadrantes aux -------------" << endl;
                cout << "Con Longitud:" << (nodoActual.longitudLado)/2 << endl;
                for(int i = 0; i < 8; i++){
                    cout << "Cuadrante " << i << " -> " << nodoActual.hijos[i]->extremoMin->valorX << " - " << nodoActual.hijos[i]->extremoMin->valorY << " - " << nodoActual.hijos[i]->extremoMin->valorZ << endl;
                }
                cout << "-------------------------------------" << endl;
                
                int group = chooseGroup(nodoActual, nodoActual.puntos[nodoActual.nPoints-1]);
                cout << "El nuevo dato pertenece al cuadrante " << group <<  endl;

                insert(nodoActual.puntos[nodoActual.nPoints-1].valorX, nodoActual.puntos[nodoActual.nPoints-1].valorY, nodoActual.puntos[nodoActual.nPoints-1].valorZ, *nodoActual.hijos[group]);

                cout << "------ para eliminar 2-----------" << endl;
                cout << "Actualmente hay: " << nodoActual.nPoints <<  " puntos"<< endl;
                int auxDelete = nodoActual.nPoints;
                for(int i = 0; i < auxDelete ; i++){
                    nodoActual.nPoints = nodoActual.nPoints - 1;
                    //delete
                }
                cout << "naw: " << nodoActual.nPoints <<  " puntos"<< endl;
            }
        }
        cout << "--------------- FIN DEL INSERT ----------------------" << endl;
    }

    void getMinimunSizes(OcTree nodoActual, int i){
        cout << "Verificando hijo: "<< i << endl;
        if(nodoActual.haveChildrens == false){
            cout << "NOOOO tiene hijos" << endl;
            return;
        }
        else{
            cout << "SII tiene hijos" << endl;

            for(int z = 0; z < 8; z++){
                cout << "crear Vector "<< z << endl;
                vector<double> aux;
                aux.push_back( nodoActual.hijos[z]->extremoMin->valorX );
                aux.push_back( nodoActual.hijos[z]->extremoMin->valorY );
                aux.push_back( nodoActual.hijos[z]->extremoMin->valorZ );
                aux.push_back( nodoActual.hijos[z]->longitudLado );

                cout << "fin" << endl;

                cout << "x:" << nodoActual.hijos[z]->extremoMin->valorX << " y: " << nodoActual.hijos[z]->extremoMin->valorY << " z: " << nodoActual.hijos[z]->extremoMin->valorZ << " len: " << nodoActual.hijos[z]->longitudLado << endl;

                allSizes.push_back(aux);
                cout << "+1" << endl;
            }

            for(int y = 0; y < 8; y++){
                cout << "antes "<< endl;
                getMinimunSizes(*nodoActual.hijos[y], i);
            }
        }
    }
};

/*


work
130.123 130.15 100.123
100.12 50.65 43.16
170.12 40.54 14.3412
200.6534 200.165 76.473
50.145 80.47 94.256
30.564 29.489 92.345
100.378 110.198 12.189
20.19 115.01 32.74
10.72 113.893 42.634
*/