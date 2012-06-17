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

/* montanharussa <número de passageiros> <número de carrinhos> <taxa de chegada de passageiros> */
void read_parameters(int argc, char* argv[]){
    if (argc < 4){
        std::cerr << "Erro na leitura da entrada. Argumentos esperados: "
                    "<número de passageiros> <número de carrinhos> <taxa de chegada de passageiros>"
                  << std::endl;
        exit (-1);
    }
    
    C = (unsigned int) atoi(argv[2]);
    m = (unsigned int) atoi(argv[1]);
    taxa = (float) atof(argv[3]);
    std::cout << "taxa: " << taxa << " m: " << m << " C: " << C << std::endl;
}

int main(int argc, char* argv[]){
    unsigned int iseed = (unsigned int) time(NULL);
    read_parameters (argc,argv);
    srand (iseed);
    RollerCoasterMonitor rcm(m);
    Thread t;
    std::cout << t.start () << std::endl;
    Car c(&rcm, C);
    rcm.setCar(0, &c);
    std::cout << c.start () << std::endl;

    Passenger p(&rcm);
    std::cout << p.start () << std::endl;
    
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 500;
    nanosleep(&tim , &tim2);
    
    ConditionVariable<Thread> cv(3);
    cv.insert (t,2);
    cv.insert (c,0);
    cv.remove ();
    cv.remove ();

    return 0;
}
