#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

int main()
{
    
     int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(1200, 800), "Ejemplo de Fisica con Box2D y SFML");

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 7.0f);
    b2World mundo(vectorGravedad);

    // Crear un rectángulo en el lado derecho
    b2BodyDef cuerpoRectanguloDef;
    cuerpoRectanguloDef.position.Set(1000.0f, 400.0f);
    b2Body *cuerpoRectangulo = mundo.CreateBody(&cuerpoRectanguloDef);

    // Crear una forma rectangular
    b2PolygonShape formaRectangulo;
    int rectWidth = 50;  // 100 pixeles de ancho
    int rectHeight = 150; // 200 pixeles de alto
    formaRectangulo.SetAsBox(rectWidth / 2.0f, rectHeight / 2.0f);
    


    // Agregar la forma al cuerpo
    b2FixtureDef fixtureRectanguloDef;
    fixtureRectanguloDef.shape = &formaRectangulo;
    fixtureRectanguloDef.friction = 1.0f;
    cuerpoRectangulo->CreateFixture(&fixtureRectanguloDef);
   
    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(-400, 500.0f); // Posición del centro del cuerpo
    b2Body *cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    // Crear una forma rectangular
    b2PolygonShape formaSuelo;
    int boxWidth = 11000; // 600 pixeles de ancho
    int boxHeight = 100;  // 10 pixeles de alto
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);


    // Agregar la forma al cuerpo
    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(400.0f, 300.0f);
    b2Body *cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma circular
    b2CircleShape formaBola;
    formaBola.m_radius = 15.0f;

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Bucle principal del juego
    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -fuerza), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, fuerza), cuerpoBola->GetWorldCenter(), true);

        // Restringir los límites de la bola a los límites de la pantalla
        b2Vec2 posicionBola = cuerpoBola->GetPosition();
        float radioBola = formaBola.m_radius;
        float limiteIzquierdo = radioBola;
        float limiteDerecho = ventana.getSize().x - radioBola;
        float limiteSuperior = radioBola;
        float limiteInferior = ventana.getSize().y - radioBola;

        if (posicionBola.x < limiteIzquierdo)
            cuerpoBola->SetTransform(b2Vec2(limiteIzquierdo, posicionBola.y), cuerpoBola->GetAngle());
        if (posicionBola.x > limiteDerecho)
            cuerpoBola->SetTransform(b2Vec2(limiteDerecho, posicionBola.y), cuerpoBola->GetAngle());
        if (posicionBola.y < limiteSuperior)
            cuerpoBola->SetTransform(b2Vec2(posicionBola.x, limiteSuperior), cuerpoBola->GetAngle());
        if (posicionBola.y > limiteInferior)
            cuerpoBola->SetTransform(b2Vec2(posicionBola.x, limiteInferior), cuerpoBola->GetAngle());

        // Actualizar el mundo de Box2D
        // Ajustar el valor de 1.0 / 60.0 para cambiar la velocidad de la simulación física
        mundo.Step(1.0f / 60.0f, 6, 2);
        cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 8.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x,
            cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        sf::RectangleShape portero(sf::Vector2f(rectWidth, rectHeight));
        portero.setOrigin(rectWidth / 2.0f, rectHeight / 2.0f); // El origen x,y está en el centro de la forma
        portero.setPosition(
            cuerpoRectangulo->GetPosition().x,
            cuerpoRectangulo->GetPosition().y);
        ventana.draw(portero);


        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
