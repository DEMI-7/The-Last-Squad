# UTN-TP-juego
# THE LAST SQUAD

# Estructura
En assets va todo los graficos y audio (mp3, png, etc)
En build van los archivos temporales de compilacion y los .exe
En include van todos los .h
En src todo el codigo fuente
Gitignore es para no subir archivos basura de la compilacion

# compilar
g++ -std=c++20 -Iinclude src/main.cpp src/Juego.cpp src/MenuPrincipal.cpp src/Gameplay.cpp src/boton.cpp src/ObjetoGrafico.cpp src/MenuSeleccionPersonaje.cpp src/archivoPersonaje.cpp src/personaje.cpp src/Entidad.cpp src/Arma.cpp src/Proyectil.cpp src/archivoArma.cpp src/ProyectilPool.cpp src/ObjetoMapa.cpp src/Zombie.cpp src/GestorOleada.cpp src/Input.cpp -o build/NuevoMenu.exe -lsfml-graphics -lsfml-window -lsfml-system

g++ -std=c++20 -Iinclude src/main.cpp src/Juego.cpp src/MenuPrincipal.cpp src/Gameplay.cpp src/boton.cpp src/ObjetoGrafico.cpp src/MenuSeleccionPersonaje.cpp src/archivoPersonaje.cpp src/personaje.cpp src/Entidad.cpp src/Arma.cpp src/Proyectil.cpp src/archivoArma.cpp src/ProyectilPool.cpp src/ObjetoMapa.cpp src/Zombie.cpp src/GestorOleada.cpp src/Input.cpp src/extra/Gamepad.cpp src/extra/GamepadMgr.cpp -o build/NuevoMenu.exe -lsfml-graphics -lsfml-window -lsfml-system -lxinput

# ejecuta
.\build\juego.exe

.\build\NuevoMenu.exe

### Instalación de SFML

Abrir la terminal `MSYS2 UCRT64` y ejecutar:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

Las estructura de la herencia es la siguiente
ObjetoGrafico
│
├── Entidad
│   ├── Jugador
│   └── Enemigo (FALTA)
│
├── ObjetoMapa
│
├── Arma
│
└── Proyectil


## ObjetoGrafico
Se encarga de todas las funciones relacionadas a la posicion, a las texturas/sprites y la hitbox, las clases que la hereden tienen que hacer override a la funcion "actualizar" si quieren tener su propia logica

## Entidad
Hereda de [ObjetoGrafico](#objetografico), se encarga de las caracteristicas tipicas de cualquier objeto con "vida" dentro del juego

## Personaje
Hereda de [Entidad](#entidad), tiene toda la logica del jugador principal.

## ObjetoMapa
Hereda de [ObjetoGrafico](#objetografico), se usa para elementos decorativos o que bloquean el paso a entidades.

## Arma
Hereda de [ObjetoGrafico](#objetografico), su pricipal funcion es seguir al jugador, y tiene funciones para detectar cuando quiere disparar o recargar, gestiona la municion y genera proyectiles.

## Proyectil 
Hereda de [ObjetoGrafico](#objetografico), su funcion es como indica el nombre ser un proyectil que se desplaza por la pantalla, dentro de juego hay un vector que almacena este tipo de objeto, eso sirve para que los enemigos por ejemplo lo reciban y comparen la hitbox para morir o recibir daño o para que al chocar con un elemento del mapa de destruya.


========================================
MAPEO JOYSTICK - THE LAST SQUAD
========================================

Joystick detectado por SFML:
Joystick 0

----------------------------------------
BOTONES
----------------------------------------

SFML 0 = A
          Equivalente PlayStation: X

SFML 1 = B
          Equivalente PlayStation: O

SFML 2 = X
          Equivalente PlayStation: □

SFML 3 = Y
          Equivalente PlayStation: △

SFML 4 = L1

SFML 5 = R1

SFML 6 = Start

SFML 7 = Botón adicional / desconocido


----------------------------------------
BOTONES NO DETECTADOS
----------------------------------------

R2 = no detectado como botón
L2 = no detectado como botón

Probablemente están expuestos por SFML
como ejes analógicos.


----------------------------------------
D-PAD
----------------------------------------

El D-pad NO aparece como botones.

SFML lo detecta mediante:

PovX
PovY

Valores observados:

D-PAD ARRIBA:
PovY = +100

D-PAD ABAJO:
PovY = -100

D-PAD IZQUIERDA:
PovX = -100

D-PAD DERECHA:
PovX = +100

Al volver al centro puede aparecer algún
valor flotante extremadamente pequeño,
por ejemplo:

4.88762e-05
-8.74228e-06
-4.37114e-06

Estos valores deben considerarse 0.


----------------------------------------
INPUT LÓGICO QUE QUEREMOS
----------------------------------------

arriba()
    Teclado: W / Flecha arriba
    Joystick: D-pad arriba

abajo()
    Teclado: S / Flecha abajo
    Joystick: D-pad abajo

izquierda()
    Teclado: A / Flecha izquierda
    Joystick: D-pad izquierda

derecha()
    Teclado: D / Flecha derecha
    Joystick: D-pad derecha

aceptar()
    Teclado: Enter / Space
    Joystick: A (SFML 0)

cancelar()
    Teclado: Escape
    Joystick: B (SFML 1)


----------------------------------------
NOTAS
----------------------------------------

- Los números corresponden a ESTE joystick
  según las pruebas realizadas con SFML.
- No asumir que otro joystick tendrá el mismo
  mapeo.
- El D-pad debe detectarse mediante PovX/PovY.
- Más adelante se agregará el stick analógico.
- Más adelante se implementará la asignación
  de dispositivos a P1/P2/P3/P4.