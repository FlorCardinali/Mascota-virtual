// Autores: Francisco Cuschie, Florencia Cardinali.
// Mails: francuschie@gmail.com / florenciapaulacardinali@gmail.com
// Tema: Mascota virtual
// Fecha de entrega: 22/06/2022 19:00
// Concepto: Programacion 1, TUP - 2022, UTN.


#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "Gato.h"

using namespace std;
void Animacion(sf::Text MaxScore,sf::Text Score, sf::Texture& TextBarraHMB, sf::Texture& TextBarraJU, sf::Texture& TextBarraSU, Gato Miguel, int& estado, sf::RenderWindow& Ventana, sf::RectangleShape& Boton1, sf::RectangleShape& Boton2, sf::RectangleShape& Boton3, sf::Sprite& Fondo, sf::Texture& Textura, int Filas, int Columnas, sf::Text &Nombres);

int main()
{

 // Creacion 
    Gato Miguel("Miguel");
    Miguel.RecuperarEstado();
    int estado = 4;

//Tiempo SOLO DE LOS FRAMMES
    sf::Clock Reloj;
    sf::Time Tiempo;
  
 //Tiempo de los ESTADOS
    sf::Clock RelojHMB;
    sf::Time TiempoHMB;
    sf::Clock RelojDR;
    sf::Time TiempoDR;
    sf::Clock RelojJU;
    sf::Time TiempoJU;

// Datos y seteos de video y eventos
    sf::RenderWindow LaVentanita(sf::VideoMode(650, 650), "Gatito Game");
    sf::Event event;      

//Texto:
    //nombres
    sf::Font FuenteBoonita;
    FuenteBoonita.loadFromFile("fuentes/Solaris.ttf");
    sf::Text NombresText;
    NombresText.setFont(FuenteBoonita);
    sf::String Nombres = "Fran Cuschie - Flor Cardinali";
    NombresText.setString(Nombres);
    NombresText.setFillColor(sf::Color(0, 0, 0));
    NombresText.setCharacterSize(20);
    NombresText.setPosition(410, 620);
    //Score
    sf::Text Score;
    Score.setFont(FuenteBoonita);
    Score.setFillColor(sf::Color(0, 0, 0));
    Score.setCharacterSize(40);
    Score.setPosition(480.f, 3.f);
    //MaxScore
    sf::Text MaxScore;
    MaxScore.setFont(FuenteBoonita);
    MaxScore.setFillColor(sf::Color(0, 0, 0));
    MaxScore.setCharacterSize(40);
    MaxScore.setPosition(10.f, 3.f);
    

//Seteos del Fondo:
    sf::Texture TextFondo;
    TextFondo.loadFromFile("graficos/piso2.png");
    sf::Sprite Fondo(TextFondo);
    
// Datos y seteos del STAND BY:
    sf::Texture texturaSB;
    texturaSB.loadFromFile("graficos/standby.png"); 

///Seteo Animacion de Comer, 4x4
    sf::Texture texturaCOM;
    texturaCOM.loadFromFile("graficos/comer.png");
 
 //Seteo Animacion de hambre, 4x4  
    sf::Texture texturaHBR;
    texturaHBR.loadFromFile("graficos/hambre.png");

//Seteo Animacion de Sueño, 4x4
    sf::Texture texturaSUE;
    texturaSUE.loadFromFile("graficos/suenio.png");

//Seteo Animacion de jugar, 4x4  
    sf::Texture texturaJU;
    texturaJU.loadFromFile("graficos/jugar.png");
  
 //Seteo Animacion de Aburrimiento, 4x4  
    sf::Texture texturaABU;
    texturaABU.loadFromFile("graficos/aburrido.png");

//Seteo Animacion de acostarse y dormir, 7x7
    sf::Texture texturaDR;
    texturaDR.loadFromFile("graficos/Acostarse.png");

 //Seteo Animacion de Muerte, 4x4
    sf::Texture texturaMUERTE;
    texturaMUERTE.loadFromFile("graficos/muerte.png");
    sf::Sprite Muerte(texturaMUERTE);
    Muerte.setPosition(70.f, 250.f);

//Barras:
    //Barra de Hambre
    sf::Texture texturaBarraHMB;
    texturaBarraHMB.loadFromFile("graficos/barraHMB.png");
    //Barra de Jugar
    sf::Texture texturaBarraJU;
    texturaBarraJU.loadFromFile("graficos/barraJU.png");
    //Barra de Sueño
    sf::Texture texturaBarraSU;
    texturaBarraSU.loadFromFile("graficos/barraSU.png");
  
 //Botones:
    // Boton de Alimentar:
        sf::RectangleShape BotonA(sf::Vector2f(96.f, 96.f));
        BotonA.setPosition(480.f, 60.f);
        sf::Texture texturaBotA;
        texturaBotA.loadFromFile("graficos/botonalimentar.png");
        BotonA.setTexture(&texturaBotA);
        BotonA.setScale(1.7f,1.7f);
    //Boton de Jugar:
        sf::RectangleShape BotonJ(sf::Vector2f(96.f, 96.f));
        BotonJ.setPosition(480.f, 233.2f);
        sf::Texture texturaBotJ;
        texturaBotJ.loadFromFile("graficos/botonjugar.png");
        BotonJ.setTexture(&texturaBotJ);
        BotonJ.setScale(1.7f, 1.7f);
    //Boton de Dormir:
        sf::RectangleShape BotonD(sf::Vector2f(96.f, 96.f));
        BotonD.setPosition(480.f, 406.4f);
        sf::Texture texturaBotD;
        texturaBotD.loadFromFile("graficos/botondormir.png");
        BotonD.setTexture(&texturaBotD);
        BotonD.setScale(1.7f, 1.7f);
    //Boton de retry
        sf::RectangleShape BotonRT(sf::Vector2f(120.f, 32.f));
        BotonRT.setPosition(180.f, 60.f);
        sf::Texture texturaBotRT;
        texturaBotRT.loadFromFile("graficos/Retry.png");
        BotonRT.setTexture(&texturaBotRT);
        BotonRT.setScale(2.5f, 2.5f);
     

        //Variables de control de funcionamioento
        sf::Clock RelojPrueba;
        sf::Time TiempoPrueba;

 // Bucle principal
  while (LaVentanita.isOpen()) 
  {
      while (LaVentanita.pollEvent(event))
      {
          switch (event.type)
          {
          case sf::Event::EventType::Closed:
          {
              Miguel.GuardarEstado();
              LaVentanita.close();

          }
          case sf::Event::MouseButtonPressed:
          {
              //buscar las cordenadas del mosue
              sf::Vector2i DondeEstaElMouse_int = sf::Mouse::getPosition(LaVentanita);
              sf::Vector2f DondeEstaElMouse_float(static_cast<float>(DondeEstaElMouse_int.x), static_cast<float>(DondeEstaElMouse_int.y));

              if (estado != 4)
              {
                  //interaccion con Boton Alimentar
                  if (BotonA.getGlobalBounds().contains(DondeEstaElMouse_float))
                  {
                      Miguel.Alimentar();
                      Miguel.SumarScore();
                      Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaCOM, 4, 4, NombresText);
                  }


                  if (BotonD.getGlobalBounds().contains(DondeEstaElMouse_float))
                  {
                      Miguel.Dormir();
                      Miguel.SumarScore();
                      Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaDR, 7, 7, NombresText);
                  }

                  if (BotonJ.getGlobalBounds().contains(DondeEstaElMouse_float))
                  {
                      Miguel.Jugar();
                      Miguel.SumarScore();
                      Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaJU, 4, 4, NombresText);
                  }
              } //corchete del if
              else
              {
                  if (BotonRT.getGlobalBounds().contains(DondeEstaElMouse_float))
                  {
                      Miguel.ResetearEstados();
                      Fondo.setColor(sf::Color(255, 255, 255, 255));
                  }
              }
          }
          }//Switch 
      }//While pollEvent

      //Tiempo para el aburrimeinto
      TiempoJU = RelojJU.getElapsedTime();
      if (TiempoJU.asSeconds() > 20)
      {
          Miguel.QuitarAburrimiento();
          RelojJU.restart();
      }
      //Tiempo para el sueño
      TiempoDR = RelojDR.getElapsedTime();
      if (TiempoDR.asSeconds() > 30)
      {
          Miguel.QuitarEnergia();
          RelojDR.restart();
      }
      //Tiempo para el hambre
      TiempoHMB = RelojHMB.getElapsedTime();
      if (TiempoHMB.asSeconds() > 15)
      {
          Miguel.QuitarHambre();
          RelojHMB.restart();
      }
      
      Miguel.Chequeo(estado);
      Miguel.MostrarEstados(estado,LaVentanita,texturaBarraHMB,texturaBarraJU,texturaBarraSU);
      
      RelojPrueba.restart();
      switch (estado)
      {
      case 1: {
          //Animación de Hambre
          Animacion(MaxScore,Score,texturaBarraHMB,texturaBarraJU,texturaBarraSU, Miguel,estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaHBR, 4, 4, NombresText);
          break;
      }
      case 2: {
          // Animación de Sueño
          Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaSUE, 4, 4, NombresText);
          break;
      }
      case 3: {
          //Animación de aburrido
          Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaABU, 4, 4, NombresText);
          break;
      }
      case 4: {
          Miguel.GuardarEstado();
          Fondo.setColor(sf::Color(120, 120, 120, 255));
          LaVentanita.draw(Fondo);
          LaVentanita.draw(BotonRT);
          LaVentanita.draw(Muerte);
          LaVentanita.draw(NombresText);
          LaVentanita.display();
          break;
      }
      case 5:
      {
          //animacion stand by
          Animacion(MaxScore,Score,texturaBarraHMB, texturaBarraJU, texturaBarraSU, Miguel, estado, LaVentanita, BotonA, BotonJ, BotonD, Fondo, texturaSB, 4, 4, NombresText);
          break;
      }

      }//corchete swich

      //limpio la ventana
      LaVentanita.clear();

   }//Corchete del While principal
}// Corchete del main 

//Funcion encargada de mostrar y secuenciar los frames de cada animacion 
// Ventana, Boton1,Boton2,boton3, fondo, textura de la aniamcion, filas, columnas.
void Animacion(sf::Text MaxScore,sf::Text Score,sf::Texture& TextBarraHMB, sf::Texture& TextBarraJU, sf::Texture& TextBarraSU, Gato Miguel,int &estado,sf::RenderWindow &Ventana,sf::RectangleShape &Boton1, sf::RectangleShape &Boton2, sf::RectangleShape &Boton3,sf::Sprite &Fondo,sf::Texture &Textura, int Filas, int Columnas, sf::Text &Nombres)
{
    sf::Clock RelojFuncion;
    sf::Time TiempoFuncion;

    sf::RectangleShape Rectangulo(sf::Vector2f(384.f, 384.f));
    Rectangulo.setTexture(&Textura);
    sf::Vector2u Matriz = Textura.getSize();
    Matriz.x = Matriz.x / Columnas;
    Matriz.y = Matriz.y / Filas;
    Rectangulo.setPosition(70.f, 250.f);
    sf::Vector2i UltimoFrame(0, 0);
    while (!(UltimoFrame.x == (Columnas - 1) && UltimoFrame.y >= (Filas - 1)))
    {
        Score.setString("Score: " + to_string(Miguel.ConsultarScore()));
        MaxScore.setString("Max Score: " + to_string(Miguel.ConsultarMaxScore()));

        Ventana.draw(Fondo);
        Ventana.draw(Boton1);
        Ventana.draw(Boton2);
        Ventana.draw(Boton3);
        Ventana.draw(Nombres);
        Ventana.draw(MaxScore);
        Ventana.draw(Score);
        TiempoFuncion = RelojFuncion.getElapsedTime();
        if (TiempoFuncion.asSeconds() > 0.1)
        {
            if (UltimoFrame.x > (Columnas - 1))
            {
                UltimoFrame.x = 0;
                UltimoFrame.y = UltimoFrame.y + 1;
            }
            /*
            Cree un rectangulo que se llama SB, al que luego le puse la textura
            notese que:

            - Yo saque el tamaño de cada sprite de la consola:
            std::cout << "x = "<< matriz.x << " y = " << matriz.y;

            - "Vector2u" es un tipo de dato matriz o arreglo de dos dimenciones con unsigneds ints y
            "Vector2f" es un arreglo de dos dimenciuones con floats, por eso no use la variable "matriz".

            - "setTextureRect" asigna a mi cuadrado (SB) el segmento que necesitas de la textura y
            "IntRect" lo hace en base a:
            Parametro 1: El tamaño de x del segmento (matriz.x) * el x guardado en el arreglo UltimoFrame
            Parametro 2: El tamaño de y del segmento (matriz.y) *  el y guardado en el arreglo UltimoFrame
            Parametro 3: El tamaño del segmento en x (matriz.x)
            Parametro 4: el tamaño del segmento en y (matriz.y)
            */
            Rectangulo.setTextureRect(sf::IntRect(Matriz.x * UltimoFrame.x, Matriz.y * UltimoFrame.y, Matriz.x, Matriz.y));
            Ventana.draw(Rectangulo);
            UltimoFrame.x = UltimoFrame.x + 1;
            Miguel.MostrarEstados(estado, Ventana, TextBarraHMB, TextBarraJU, TextBarraSU);
            RelojFuncion.restart();
            Ventana.display();
        }
        Ventana.clear();
    }
}
