#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include "thread.h"
#include "car.h"
#include "passenger.h"
#include "conditionvariable.h"
#include "rollercoastermonitor.h"
#include "timemanager.h"
#include "passengercreator.h"

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
    TimeManager tm;
    
    /* Inicializa os cars - pode ser abstraido */
    std::vector<Car*> cars;
    for (int i = 0; i < m; i++) {
        Car *c = new Car (&rcm, &tm, C);
        cars.push_back (c);
        rcm.setCar (i, c);
    }

    for (int i = 0; i < m; i++) {
        if (cars[i]->start ()) {
            std::cout << "ERRO CRIANDO CARRO!!!" << std::endl;
            exit (EXIT_FAILURE);
        }
    }
    
    /* Criando os Passageiros */
    PassengerCreator pc (&rcm, &tm);
    pc.start ();
    
    while (1) {
        tm.advanceTime ();
    }

    for (int i = 0; i < m; i++) {
        delete cars[i];
        cars[i] = 0;
    }

    return 0;
}
