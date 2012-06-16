#include <cstdlib>
#include <iostream>
#include "thread.h"

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
  read_parameters (argc,argv);
  Thread t;
  std::cout << t.start () << std::endl;
  return 0;
}
