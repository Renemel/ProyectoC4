#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


#define espacio 10
#define tam 50
#define filas 9
#define columnas 8
//butones 
#define filasB 1
#define columnasB 8
#define tamB 20

int m=1;
void x0(int, int, int);
int tablero[8][8];
Scalar negro(0, 0, 0);
Scalar blanco(255, 255, 255);
Scalar verde (0, 255, 0);
Scalar rojo (0,0,255);
bool bandera = false;
bool endgame = false;
void check(int);
void DibujarJuego();
bool turn = false; 

int alto = tam*columnas + espacio * 8.5;
int ancho = tam *filas + espacio -2 ;
Mat ventana(alto, ancho, CV_8UC3, negro);

//CODIGO DE AQUÍ EN ADELANTE ES ACERCA DEL JUEGO CONECT4 
void llenar(){
    for(int a =0;a < 8; a++){        //llenar con 0 ambos arreglos 
        for(int b = 0; b<8; b++)  
            tablero[a][b] = 0;}  
    }

void dibujarButtons(){
	//cuadros verdes en los cuales se trabajarán los botones, se deben hacer flechas verticales 
	//horizontales
	for (int i=0; i < filasB; i++) {
		Point inicioB(espacio, tam*i + espacio);
		Point finB(tam*columnasB+espacio, tam*i+espacio);
		line(ventana, inicioB, finB, verde);
	} // verticales
	for (int i = 0; i<9; i++){
			Point inicio2(tam*i + espacio, espacio);
		Point fin2(tam*i + espacio, tam*filasB + espacio);
		line(ventana, inicio2, fin2, verde);
	}
	}

void dibujartablero() {

	for (int i = 0; i < filas + 1; i++)	
	{
		Point inicio1(espacio, (tam*i + espacio));
		Point fin1(tam*columnas + espacio, tam*i + espacio);
		line(ventana, inicio1, fin1, blanco);
	}

	for (int i = 0; i < filas; i++)
	{
		Point inicio2(tam*i + espacio, espacio);
		Point fin2(tam*i + espacio, tam*filas + espacio);
		line(ventana, inicio2, fin2, blanco);
	}
	}

void arr() {
	cout<<"1 2 3 4 5 6 7 8\n";
    for(int a = 0; a<= 7; a++)
    {
        for(int b =0; b <= 7; b++) cout<<tablero[a][b]<<" ";
        cout<<'\n';   
	}}

void dibujarMaru(int x, int y){
	Point centro(x + tam / 2, y + tam / 2);
	int radio = tam / 2 - espacio;
	circle(ventana, centro, radio, (turn? verde:blanco)); }

void kakuempate(){
	Mat Empate(200, 400, CV_8UC3, blanco);
    putText(Empate, "-Empate-", Point(100, 100), FONT_HERSHEY_SIMPLEX, 3, verde);
    imshow("Empate", Empate);

    endgame = true;
}

void ganador(){

}
void Empate(){
	int lleno=0;
	for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (tablero[i][j] != 0) lleno++;
if ( !endgame && lleno==64)kakuempate();

}


void onMouse(int event, int x, int y, int, void*) {
	if (endgame) return;
	if(m==0){
		if (event == EVENT_LBUTTONUP) {
			for (int i = 0; i < filas; i++)
			{
				int valor = tam*i + espacio;
				if (x >= valor && x < valor + tam && y >= espacio && y <=tam + espacio) {
				int s=7;
				x = tam * ((x - espacio) / tam) + espacio;
                y = tam * ((y - espacio) / tam) + espacio;
				while (s>=0){
	 				if (tablero[s][i]==0){
	 					tablero[s][i]=(turn? 1:2);
	 					dibujarMaru(x,y);
	 					turn=!turn;
	 					break;
	 						}
	 				else if (tablero[s][i]!=0){
	 					s--;
	 						}
	 						}
				bandera = true;
			}
		}
		ganador();
		Empate();


		if (bandera) {
			arr();
			bandera = false;
		}
	}}
	else if (m==1){
		if (event==EVENT_LBUTTONUP){
			int valor = 74 ;
				if (x >= 75 && x < 314 && y >= 62 && y <=250) {
					m=0;
					DibujarJuego();
				}
				else if(x>=75 && x<314 && y>=156 && y <=230){
					m=0;
					DibujarJuego(); 
					//Aquí irá la pantalla de puntuaciones, todavía no está hecha!
				}
		}

	}

}



//CODIGO DE AQÚI EN ADELANTE ES SOBRE EL MENU!!!!!
void dibujarBmenu(Mat Menu){
	putText(Menu, "-Conect 4-", Point(10,50), FONT_HERSHEY_SCRIPT_SIMPLEX, 2, verde);
    //imshow("Empate", Menu);
	
	Rect recPlay (75,63,240,73); 
	rectangle(Menu, recPlay,rojo, CV_FILLED);
	putText(Menu,"Jugar!",Point(105,115), FONT_HERSHEY_SIMPLEX,2,blanco);
	Rect recScore (75,158,240,73);
	rectangle(Menu, recScore,rojo,CV_FILLED); 
	putText(Menu,"Puntuacion",Point(81,215), FONT_HERSHEY_SIMPLEX,1.3,blanco);
}



void Menu(){
	Mat Menu (400,400,CV_8UC3,negro);
	namedWindow("Ventana");
	int option=0;
	dibujarBmenu(Menu);
	setMouseCallback("Ventana", onMouse);


	while (option==0)
	{
		imshow("Ventana", Menu);
		if (waitKey(10) == 27) break;
		
	}
}


int main(int argc, char const *argv[]) {
	
	Menu();
	//DibujarJuego();

	
}


void check(int i){
 if (tablero[7][0]==tablero[7][1])
 	 endgame=true;

} 

void DibujarJuego(){
	namedWindow("Ventana");

	setMouseCallback("Ventana", onMouse);
	arr();
	dibujartablero();
	dibujarButtons();

	while (true)
	{
		imshow("Ventana", ventana);
		if (waitKey(10) == 27) {break;
		break;}
		
	}

}