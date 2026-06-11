cmake_minimum_required(VERSION 4.0)
project(Programacion_en_C C)

set(CMAKE_C_STANDARD 99)

# El único ejecutable del Tema 1 ahora apunta a tu nuevo archivo
add_executable(Tema_1 Tema1/tema1.c)
add_executable(Cobros Cobros/cobroscomunidad.c)
add_executable(PuertoDeValencia PuertoDeValencia/puertodevalencia.c)
add_executable(Tasca Tasca/plnatilla.c)
add_executable(PokemonGo LlanicosGo/llanicos_go.c)
add_executable(Biblioteca Biblioteca/biblio.c)