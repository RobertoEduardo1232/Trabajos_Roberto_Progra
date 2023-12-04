#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

int main()
{
    
     int fuerza = 30, fuerzaPortero=40000;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(1200, 800), "Simulador de Penales");

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 7.0f);
    b2World mundo(vectorGravedad);

    // Crear un suelo estático
    b2BodyDef cuerpoPaloDef;
    cuerpoPaloDef.position.Set(1100, 300.0f); // Posición del centro del cuerpo
    b2Body *cuerpoPalo = mundo.CreateBody(&cuerpoPaloDef);

    // Crear una forma rectangular
    b2PolygonShape formaPalo;
    int PaloWidth = 30; // 600 pixeles de ancho
    int PaloHeight = 450;  // 10 pixeles de alto
    formaPalo.SetAsBox(PaloWidth / 2.0f, PaloHeight / 2.0f);




    b2BodyDef cuerpoSuperiorDef;
    cuerpoSuperiorDef.position.Set(1200, 100.0f); // Posición del centro del cuerpo
    b2Body *cuerpoSuperior = mundo.CreateBody(&cuerpoSuperiorDef);

    // Crear una forma rectangular
    b2PolygonShape formaSuperior;
    int SuperiorWidth = 115; // 600 pixeles de ancho
    int SuperiorHeight = 30;  // 10 pixeles de alto
    formaSuperior.SetAsBox(SuperiorWidth/ 2.0f, SuperiorHeight / 2.0f);
   


    // Crear un rectángulo en el lado derecho
    b2BodyDef cuerpoRectanguloDef;
    cuerpoRectanguloDef.type = b2_dynamicBody;
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
    fixtureRectanguloDef.density = 20.0f;
    fixtureRectanguloDef.friction = 0.007f;
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
    fixtureBolaDef.density = 0.1f;
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

        // Controlar el portero con el teclado
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        cuerpoRectangulo->ApplyLinearImpulse(b2Vec2(0, -fuerzaPortero), cuerpoRectangulo->GetWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        cuerpoRectangulo->ApplyLinearImpulse(b2Vec2(0, fuerzaPortero), cuerpoRectangulo->GetWorldCenter(), true);
 
        
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
        suelo.setFillColor(sf::Color::Green);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::White);
        bola.setPosition(
            cuerpoBola->GetPosition().x,
            cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        sf::RectangleShape portero(sf::Vector2f(rectWidth, rectHeight));
        portero.setOrigin(rectWidth / 2.0f, rectHeight / 2.0f); // El origen x,y está en el centro de la forma
        portero.setFillColor(sf::Color::Red);
        portero.setPosition(
            cuerpoRectangulo->GetPosition().x,
            cuerpoRectangulo->GetPosition().y);
        ventana.draw(portero);


        sf::RectangleShape palo(sf::Vector2f(PaloWidth, PaloHeight));
        palo.setOrigin(PaloWidth / 2.0f, PaloHeight / 2.0f); // El origen x,y está en el centro de la forma
        palo.setFillColor(sf::Color::White);
        palo.setPosition(
            cuerpoPalo->GetPosition().x,
            cuerpoPalo->GetPosition().y);
        ventana.draw(palo);

        sf::RectangleShape superior(sf::Vector2f(SuperiorWidth, SuperiorHeight));
        superior.setOrigin(SuperiorWidth / 1.0f, SuperiorHeight / 1.0f); // El origen x,y está en el centro de la forma
        superior.setFillColor(sf::Color::White);
        superior.setPosition(
            cuerpoSuperior->GetPosition().x,
            cuerpoSuperior->GetPosition().y);
        ventana.draw(superior);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
