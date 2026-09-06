#include "../include/MenuPrincipal.h"
#include "../include/Juego.h"
#include "../include/Gameplay.h"
#include "../include/MenuSeleccionPersonaje.h"
#include <iostream>

#include "../include/extra/GamepadMgr.h"

/*
    Vector de botones:
    0. Boton Jugar
    1. Boton Configuracion.
    2. Boton Creditos
*/

MenuPrincipal::MenuPrincipal(Juego* juego) : Pantalla(juego), spriteFondoMenu(texturaFondoMenu) {
    
    GamepadMgr::Instance().Initialize();
    
    if(texturaFondoMenu.loadFromFile("assets/menu_bg.png")) {
        std::cout << "se importo bien" << std::endl;
    } else {
        std::cout << "fallo carga imagen" << std::endl;
    }

    spriteFondoMenu.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(texturaFondoMenu.getSize().x), static_cast<int>(texturaFondoMenu.getSize().y) }));
    spriteFondoMenu.move(sf::Vector2f(192,26));

    vectorBotones.reserve(10);

    vectorBotones.emplace_back(1, 0, "assets/varios/boton_Jugar_450_84.png");
    vectorBotones[0].setearTamanioSprite(225, 84);
    vectorBotones[0].escalarSprite(0.7f, 0.7f); // Escalar el sprite a la mitad de su tamaño original
    vectorBotones[0].ajustarHitboxAlSprite(); // Ajustar la hitbox al tamaño del sprite
    vectorBotones[0].centrarOrigen();
    vectorBotones[0].setPosicionCentrado(960.f, 540.f); // Posición centrada en la ventana

    vectorBotones.emplace_back(1, 1, "assets/varios/botonSheet_32x12.png");
    vectorBotones[1].mover(0, 100.f);
    vectorBotones[1].setearTamanioSprite(32, 12);
    vectorBotones[1].escalarSprite(5.f, 5.f); // Escalar el sprite a la mitad de su tamaño original
    vectorBotones[1].ajustarHitboxAlSprite(); // Ajustar la hitbox al tamaño del sprite
    vectorBotones[1].centrarOrigen();
    vectorBotones[1].setPosicionCentrado(960.f, 640.f); // Posición centrada en la ventana

    vectorBotones.emplace_back(1, 2, "assets/varios/botonSheet_32x12.png");
    vectorBotones[2].mover(0, 200.f);
    vectorBotones[2].setearTamanioSprite(32, 12);
    vectorBotones[2].escalarSprite(5.f, 5.f); // Escalar el sprite a la mitad de su tamaño original
    vectorBotones[2].ajustarHitboxAlSprite(); // Ajustar la hitbox al tamaño del sprite
    vectorBotones[2].centrarOrigen();
    vectorBotones[2].setPosicionCentrado(960.f, 740.f); // Posición centrada en la ventana
}

void MenuPrincipal::manejarEventos(const sf::Event& evento) {
    // Cerrar con escape
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        juego->getVentana().close();
        return;
    }

    // enter para pasar harcodear gameplay
    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>()) {
        if (tecla->code == sf::Keyboard::Key::L) {
            juego->cambiarPantalla(new Gameplay(juego));
        }
    }

    
    
}

void MenuPrincipal::actualizar(float deltaTime) {
    input.actualizar(juego->getVentana());
    
    /*
    // ----- Movimiento en el menu
    if (input.abajo()) {
        botonSeleccionado++;
    }
    
    if (input.arriba()) {
        botonSeleccionado--;
    }
    
    if (botonSeleccionado < 0) {
        botonSeleccionado = vectorBotones.size() - 1;
    }
    if (botonSeleccionado >= vectorBotones.size()) {
        botonSeleccionado = 0;
    }
    
    // ----- Interaccion con botones teclado y joystik
    if (input.aceptar() && botonSeleccionado == 0){
        juego->cambiarPantalla(new Gameplay(juego));
    }
    */

    Gamepad* jug1 = GamepadMgr::Instance().GamepadOne();
    if (jug1 != nullptr) {
        if (jug1->isButtonPressed(Gamepad::GAMEPAD_BUTTON::btn_a)) {
            botonSeleccionado++;
        }
        if (jug1->isButtonPressed(Gamepad::GAMEPAD_BUTTON::btn_b)) {
            botonSeleccionado--;
        }

        float dirX = jug1->getAxisPosition(Gamepad::GAMEPAD_AXIS::leftStick_X);
        float dirY = jug1->getAxisPosition(Gamepad::GAMEPAD_AXIS::leftStick_Y);

        if (dirY > 50.f) {
            botonSeleccionado++;
        }
        if (dirY < -50.f) {
            botonSeleccionado--;
        }

    }

    if (botonSeleccionado < 0) {
        botonSeleccionado = vectorBotones.size() - 1;
    }
    if (botonSeleccionado >= vectorBotones.size()) {
        botonSeleccionado = 0;
    }

    
    // ----- Cambiar la actualizacion de los botones ajustado a mouse o teclas
    if (input.usandoMouse()) {
        for (auto& boton : vectorBotones) {
            boton.actualizar(deltaTime, juego->getVentana());
        }
        
        // Interaccion de botones mouse
        if (vectorBotones[0].fueClickeado()) {
            std::cout << "Botón 0 clickeado" << std::endl;
            juego->cambiarPantalla(new Gameplay(juego));
        }
        if (vectorBotones[1].fueClickeado()) {
            std::cout << "Botón 1 clickeado" << std::endl;
        }
        if (vectorBotones[2].fueClickeado()) {
            std::cout << "Botón 2 clickeado" << std::endl;
        }
        
    }
    else {
       for (auto& boton : vectorBotones) {
           boton.actualizar(deltaTime, juego->getVentana(), botonSeleccionado);
        }
    }
    
}

void MenuPrincipal::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteFondoMenu);

    for (auto& boton : vectorBotones) {
        boton.dibujar(ventana);
    }
}