#include "Gato.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//Funcion de control de las barras de estados
void ControlDeBarras(float posicionx, float posiciony,int Contador, sf::Texture& Barra, sf::RenderWindow &ventana) {
    
    sf::RectangleShape Rectangulo(sf::Vector2f(32.f, 12.f));
    Rectangulo.setTexture(&Barra);
    Rectangulo.setPosition(posicionx, posiciony);
    sf::Vector2u Matriz = Barra.getSize();
    Matriz.x = Matriz.x / 2;
    Matriz.y = Matriz.y / 3;

    switch (Contador)
    {
    case 10: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 0, Matriz.y * 0, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);

    }break;
    case 8: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 1, Matriz.y * 0, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);
    }break;
    case 6: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 0, Matriz.y * 1, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);
    }break;
    case 4: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 1, Matriz.y * 1, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);
    }break;
    case 2: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 0, Matriz.y * 2, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);
    }break;
    case 0: {
        Rectangulo.setTextureRect(sf::IntRect(Matriz.x * 1, Matriz.y * 2, Matriz.x, Matriz.y));
        Rectangulo.setScale(4.f, 4.f);
        ventana.draw(Rectangulo);
    }break;
    }
}

//El constructor pide el nombre
Gato::Gato(string StringNombre = "Miguel") {
    nombre = StringNombre;
    return;
}

// Reducción de los Estados

//quita 2 de hambre
void Gato::QuitarHambre() {
    if (ContHambre >= 2)
        ContHambre = ContHambre - 2;
    else
        ContHambre = 0;
    return;
}
//quita 2 de energia
void Gato::QuitarEnergia() {

    if (ContEnergia >= 2)
        ContEnergia = ContEnergia - 2;
    else
        ContEnergia = 0;
    return;
    
}
//quita 2 de aburrimiento
void Gato::QuitarAburrimiento() {

    if (ContAburrimiento >= 2)
        ContAburrimiento = ContAburrimiento - 2;
    else
        ContAburrimiento = 0;
    return;
}


// Aumento de los Estados

    //Suma 2 de Hambre al gato
void Gato::Alimentar()
{
    if (ContHambre + 2 <= 10)
    {
        ContHambre = ContHambre + 2;
    }
    else
    {
        ContHambre = 10;
    }
    return;
}
    //Suma 2 puntos de sueño al gato
void Gato::Dormir()
{
    if (ContEnergia + 2 <= 10)
    {
        ContEnergia = ContEnergia + 2;
    }
    else
    {
        ContEnergia = 10;
    }
    return;
}
    //Suma 2 de aburrimiento al gato 
void Gato::Jugar()
{
    if (ContAburrimiento + 2 <= 10)
    {
        ContAburrimiento = ContAburrimiento + 2;
    }
    else
    {
        ContAburrimiento = 10;
    }
    return;
}

//Cambia el valor de la variable estado directamente
void Gato::Chequeo(int &Estado) {
   
    if (ContHambre == 0 || ContEnergia == 0)
    {
        Estado = 4;
        return;
    }
    if ((ContHambre < 6) && (ContHambre > 0))
    {
        Estado = 1;
        return;
    }
    if ((ContEnergia < 6) && (ContEnergia > 0))
    {
        Estado = 2;
        return;
    }
    if ((ContAburrimiento < 6) && (ContAburrimiento > 0))
    {
        Estado = 3;
        return;
    }
    else
    {
        Estado = 5;
        return;
    }
    
}
//Consulta en el archivo el max score   
int Gato::ConsultarMaxScore() {
    int MaxScore;
    ifstream InGuardado;
    InGuardado.open("guardar/salvado.txt");
    if (InGuardado.is_open())
    {
        InGuardado >> MaxScore;
        InGuardado >> MaxScore;
        InGuardado >> MaxScore;
        InGuardado >> MaxScore;
        InGuardado >> MaxScore;
    }
    else
    {
        cout << "NO SE CONSIGUIO EL MAX SCORE! " << endl;
        return -1;
    }
    InGuardado.close();
    if (ScoreMax != 0 && ScoreMax >= MaxScore) {
        return ScoreMax;
    }
    else {
        return MaxScore;
    }
}
//Guarda en archivo los contadores de estado del gato
void Gato::GuardarEstado() {

    int Max = ConsultarMaxScore();
    ofstream OutGuardado;
    OutGuardado.open("guardar/salvado.txt");

    if (OutGuardado.is_open())
    {
        OutGuardado << ContHambre << endl;
        OutGuardado << ContEnergia << endl;
        OutGuardado << ContAburrimiento << endl;
        OutGuardado << Score << endl;
        if (Score > Max)
        {
            Max = Score;
            OutGuardado << Max << endl;
        }
        else
        {
            OutGuardado << Max << endl;
        }
        
    }
    else
    {
        cout << "NO SE GUARDOOOOO! " << endl;
        return;
    }
    OutGuardado.close();
    return;
}
//Recupera el estado del gato desde el archivo
void Gato::RecuperarEstado() {

    ifstream InGuardado;
    InGuardado.open("guardar/salvado.txt");
    if (InGuardado.is_open()) {

        InGuardado >> ContHambre;
        InGuardado >> ContEnergia;
        InGuardado >> ContAburrimiento;
        InGuardado >> Score;
        InGuardado >> ScoreMax;

    }
    else
    {
        cout << "NO SE RECUPERO NADA! " << endl;
        return;
    }

    InGuardado.close();
    return;
}
//Control de barras de estados
void Gato::MostrarEstados(int estado, sf::RenderWindow &Ventana,sf::Texture& TextBarraHMB, sf::Texture& TextBarraJU, sf::Texture& TextBarraSU) {
    ControlDeBarras(25.f,70.f,ContHambre,TextBarraHMB,Ventana);
    ControlDeBarras(175.f, 70.f, ContAburrimiento, TextBarraJU, Ventana);
    ControlDeBarras(325.f,70.f, ContEnergia, TextBarraSU, Ventana);
    return;
}
//Restaura los estados del gato a 10
void Gato::ResetearEstados() {
    ContAburrimiento = 10;
    ContEnergia = 10;
    ContHambre = 10;
    Score = 0;
    return;
}
void Gato::SumarScore() {
    Score = Score + 10;
    return;
}
int Gato::ConsultarScore() {
    return Score;
}



