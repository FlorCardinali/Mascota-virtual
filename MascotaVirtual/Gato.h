#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Gato
{
private:

    //Estados
    int ContHambre = 10;
    int ContEnergia = 10;
    int ContAburrimiento = 10;
    int Score = 0;
    int ScoreMax;
    

public:
 //Nombre del Gato
    string nombre;

//Constructor:
    //seteo del nombre del gato
    Gato(string);
    
//Restar estados:
 
    //Quita 2 de hambre
    void QuitarHambre();
    //Quita 2 de Energia
    void QuitarEnergia();
    //Quita 2 de aburrimeinto
    void QuitarAburrimiento();

//sumar estados:
    //suma 2 a hambre
    void Alimentar(); //listo funcionando
    //suma 2 a aburrimiento
    void Jugar();
    //suma 2 a Energia
    void Dormir();

//chequeo de estados
    void Chequeo(int &Estado);

//Score
    void SumarScore();
    int ConsultarScore();
    int ConsultarMaxScore();

// Guardado 
    //Guarda los contadores de estado en el archivo
    void GuardarEstado();
    //Recupera el valor de los contadores de estado del archivo
    void RecuperarEstado();
    //Mostrar estados (metoo de control)
    void MostrarEstados(int estado,sf::RenderWindow &Ventana, sf::Texture &TextBarraHMB,sf::Texture &TextBarraJU, sf::Texture &TextBarraSU);
    //Resetea los estados a 10
    void ResetearEstados();
};

