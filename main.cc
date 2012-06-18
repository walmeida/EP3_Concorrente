#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include "thread.h"
#include "car.h"
#include "passenger.h"
#include "conditionvariable.h"
#include "rollercoastermonitor.h"
#include "passengercreator.h"

#include </opt/local/include/valgrind/memcheck.h>

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
    RollerCoasterMonitor rcm (m);
    
    /* Inicializa os cars - pode ser abstraido */
    std::vector<Car> cars;
    for (int i = 0; i < m; i++) {
        cars.push_back (Car (&rcm, C));
        rcm.setCar (i, &cars[i]);
    }

    for (int i = 0; i < m; i++) {
        if (cars[i].start ()) {
            std::cout << "ERRO CRIANDO CARRO!!!" << std::endl;
            exit (EXIT_FAILURE);
        }
    }
    
    /* Criando os Passageiros */
    PassengerCreator pc (&rcm);
    pc.start ();
    
    struct timespec tim, tim2;
    tim.tv_sec = 3;
    tim.tv_nsec = 500;
    nanosleep(&tim , &tim2);
    for (unsigned int i = 0; i < 10; ++i) {
        i--;
        VALGRIND_DO_LEAK_CHECK;
        i++;
    }
    // SEGFAULT!
    //volatile int *p = reinterpret_cast<volatile int*>(0);
    //*p = 0x1337D00D;
    


    return 0;
}
