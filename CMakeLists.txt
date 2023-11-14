cmake_minimum_required(VERSION 3.17)
project(Gioco_Meccaniche C)

set(CMAKE_C_STANDARD 99)

add_executable(Gioco_Meccaniche main.c gamemecs.c gamemecs.h fight.c fight.h eqchange.c eqchange.h enemies.c enemies.h story.c story.h)