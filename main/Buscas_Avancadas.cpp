#include"../search_methods/Hill_Climbing.cpp"
#include"../search_methods/Simulated_Annealing.cpp"
#include"../search_methods/Local_Beam.cpp"
#include"../search_methods/Genetic_Algorithm.cpp"
#include"../search_methods/GeneticAbel.cpp"
#include"../search_methods/Online_DFS.cpp"
#include"../search_methods/Online_Local_Search.cpp"

void PrintVector(std::vector<int> x) {

    //for (size_t i = 0; i < x.size(); i++)
    //{
    //    switch (x[i])
    //    {
    //    case 1:
    //        printf("%c", 26);
    //    case 2:
    //        printf("%c", 27);
    //    case 3:
    //        printf("%c", 24);
    //    case 4:
    //        printf("%c", 25);
    //    }
    //}
    //std::cout << std::endl;
    for (unsigned int i = 0; i < x.size(); i++)
    {
        std::cout << x[i];
    }
    std::cout << std::endl;
}

void PrintMatrix(std::vector<std::vector<int> > a) {
    for (unsigned int i = 0; i < a.size(); i++) {
        for (unsigned int j = 0; j < a[i].size(); j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Answer(Puzzle a) {
    std::cout << "-----------ESTADO FINAL----------\n";
    PrintMatrix(a.get_table());
    std::cout << "-----------MOVIMENTOS------------\n";
    PrintVector(a.get_movements());
    std::cout << "------HEURISTICA-----------\n";
    std::cout << a.get_heuristic() << "\n";
    std::cout << "N MOVIMENTOS: " << a.get_movements().size() << std::endl;
    system("pause");
}

void InicialProblem(Puzzle a) {
    std::cout << "-----------ESTADO INICIAL----------\n";
    PrintMatrix(a.get_table());
    std::cout << "-----------OBJETIVO------------\n";
    PrintMatrix(a.get_objective());
}

int main(){

    int searchType;
    //float value;


    std::cout << "-----------------ffffffBem Vindo!-----------------\n";
    std::cout << "Escolha o tipo de busca:\n\n";
    std::cout << "ENCERRAR O PROGRAMA - 0\nBUSCA DE SUBIDA DE ENCOSTA - 1\nTÊMPERA SIMULADA - 2\nFEIXE LOCAL -3\nALGORITMO GENETICO -4\nDFS ONLINE -5\nONLINE LOCAL SEARCH -6\n";
    std::cout << "Entre com a busca desejada: \n";
    //std::cin >> searchType;
    searchType = 2;

    //-----------SETA A BUSCA-------------------
    std::vector < std::vector<int>> initialState{ {4,2,3},{5,1,0},{7,8,6} };//{ {0,3,5}, {4,2,1}, {7,8,6} };//{ {0, 1, 2}, { 4,5,3 }, { 7,8,6 } };{ {7,4,1},{3,0,5},{8,6,2} };
    std::vector < std::vector<int>> objective{ {1, 2, 3}, {4,5, 6 }, {7,8,0 } };
    std::vector <int> moviments;
    Puzzle problem(initialState, objective, moviments);
    //-------------------------------------------
    Puzzle solution;
    InicialProblem(problem);

    switch(searchType) 
    {       
   
    case 0:
    {
        std::cout << "Programa encerrado.\n";
        break;
    }
    case 1:
    {
        std::cout << "A busca escolhida foi SUBIDA DE ENCOSTA\n";
        HillClimbing search_1(problem); //chamada da busca HillClimbing 
        solution = search_1.get_result();
        Answer(solution); //print out solucao
        break;
    }
    case 2:
    {
        std::cout << "A busca escolhida foi TÊMPERA SIMULADA\n";
        SimulatedAnnealing search_2(problem);
        solution = search_2.get_result(); 
        Answer(solution); //print out solucao
        break;
    }
    case 3:
    {
        std::cout << "A busca escolhida foi FEIXE LOCAL\n";
        LocalBeam search_3(problem); 
        solution = search_3.get_result();
        Answer(solution); //print out solucao
        break;
    }
    case 4:
    {
        std::cout << "A busca escolhida foi ALGORITMO GENETICO\n";
        GeneticAlgorithm search_4(problem); //chamada da busca HillClimbing 
        solution = search_4.get_result();
        Answer(solution); //print out solucao
        break;
    }
     case 5:
     {
         std::cout << "A busca escolhida foi ONLINE DFS\n";
         OnlineDFS search_5(problem); //chamada da busca HillClimbing 
         solution = search_5.get_result();
         Answer(solution); //print out solucao
         break;
     }
     case 6:
     {
         std::cout << "A busca escolhida foi ONLINE LOCAL SEARCH\n";
         OnlineLocalSearch search_6(problem); //chamada da busca HillClimbing 
         solution = search_6.get_result();
         Answer(solution); //print out solucao
         break;
     }
     case 7:
     {
         std::cout << "A busca escolhida foi Algoritmo Genético Abel\n";
         GeneticAbel search_7(problem); //chamada da busca HillClimbing 
         solution = search_7.get_result();
         Answer(solution); //print out solucao
         break;
     }
    default:
    {
        std::cout << "Tipo de busca nao encontrado!!!!\n";
        break;
    }
    }
    //system("pause");
    return 0;
}
