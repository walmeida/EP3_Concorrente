#include <cstdlib>
#include <iostream>
#include <time.h>
#include "thread.h"
#include "car.h"
#include "passenger.h"
#include "conditionvariable.h"
#include "rollercoastermonitor.h"

/* Número de Carrinhos */
int m;
/* Número de Passageiros em cada Carrinho */
int C;
/* Taxa de chegada de Passageiros */
float taxa;

/* montanharussa <capacidade do carrinho> <número de carrinhos> <taxa de chegada de passageiros> */
void read_parameters(int argc, char* argv[]){
    if (argc < 4){
        std::cerr << "Erro na leitura da entrada. Argumentos esperados: "
                    "<capacidade do carrinho> <número de carrinhos> <taxa de chegada de passageiros>"
                  << std::endl;
        exit (-1);
    }
    
    C = (unsigned int) atoi(argv[1]);
    m = (unsigned int) atoi(argv[2]);
    taxa = (float) atof(argv[3]);
    std::cout << "taxa: " << taxa << " m: " << m << " C: " << C << std::endl;
}

int main(int argc, char* argv[]){
    unsigned int iseed = (unsigned int) time(NULL);
    read_parameters (argc,argv);
    srand (iseed);
    RollerCoasterMonitor rcm(m);
    Car c(&rcm, C);
    rcm.setCar(0, &c);
    c.start ();

    Passenger p(&rcm);
    p.start ();
    Passenger p2(&rcm);
    p2.start ();
    Passenger p3(&rcm);
    p3.start ();
    Passenger p4(&rcm);
    p4.start ();
    
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 500;
    nanosleep(&tim , &tim2);

    return 0;
}
