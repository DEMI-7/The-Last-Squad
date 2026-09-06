#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    std::cout << "=== DETECTOR DE INPUTS ===" << std::endl;
    std::cout << "Presiona teclas o botones del joystick..." << std::endl;
    std::cout << "Presiona ESC para salir." << std::endl;

    sf::Window ventana(sf::VideoMode({400, 300}), "Detector");

    bool botonesAnteriores[32] = {};
    float povXAnterior = 0.f;
    float povYAnterior = 0.f;

    while (ventana.isOpen())
    {
        while (const auto evento = ventana.pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
            {
                ventana.close();
            }

            if (const auto* key = evento->getIf<sf::Event::KeyPressed>())
            {
                std::cout << "TECLADO - codigo: "
                          << static_cast<int>(key->code)
                          << std::endl;

                if (key->code == sf::Keyboard::Key::Escape)
                {
                    ventana.close();
                }
            }
        }

        // Buscar joysticks conectados
        for (unsigned int joystick = 0; joystick < 8; joystick++)
        {
            if (!sf::Joystick::isConnected(joystick))
                continue;

            // BOTONES
            unsigned int cantidadBotones =
                sf::Joystick::getButtonCount(joystick);

            for (unsigned int boton = 0;
                 boton < cantidadBotones && boton < 32;
                 boton++)
            {
                bool presionado =
                    sf::Joystick::isButtonPressed(joystick, boton);

                if (presionado && !botonesAnteriores[boton])
                {
                    std::cout
                        << "JOYSTICK " << joystick
                        << " - BOTON: " << boton
                        << std::endl;
                }

                botonesAnteriores[boton] = presionado;
            }

            // POV X
            float povX =
                sf::Joystick::getAxisPosition(
                    joystick,
                    sf::Joystick::Axis::PovX
                );

            if (povX != povXAnterior)
            {
                std::cout
                    << "JOYSTICK " << joystick
                    << " - POV X: "
                    << povX
                    << std::endl;

                povXAnterior = povX;
            }

            // POV Y
            float povY =
                sf::Joystick::getAxisPosition(
                    joystick,
                    sf::Joystick::Axis::PovY
                );

            if (povY != povYAnterior)
            {
                std::cout
                    << "JOYSTICK " << joystick
                    << " - POV Y: "
                    << povY
                    << std::endl;

                povYAnterior = povY;
            }
        }
    }

    return 0;
}