#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime> 
// #include "sthread.h"
#include <cstring>
#include <fstream>
#include <random>
using namespace std;

// Para imprimir en consola
using std::cout; using std::endl;
using std::setw; using std::vector;

// Para generar un número rnd entre 0 y 1.
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<float> distr(0, 1);

void read_input(string file_name) {
    ifstream file(file_name.c_str());

    string line;
    // Obtener línea de archivo, y almacenar contenido en "linea"

    while (getline(file, line)) {
        // Lo vamos imprimiendo
        cout << "Una línea: ";
        cout << line << endl;
    }
}

double moviment(double s_prev) {
    double s_current = s_prev + 1;
    
    std::cout << "se realiza el movimiento: " << s_current << endl;
    return s_current;
}

double probability(double rho, double T) {
    return exp((-1 * rho) / T);
}

double gen_rand() {
    return distr(eng);
}

// void evaluation_function(Solution s) {
bool evaluation_function(double s_current) {
    std::cout << "Se evalua s_current: "<< s_current <<" y retorna true si es mejor que s_prev o false si es peor!" << endl;
    return true;
}

void accept_solution(double * s_prev, double * new_solution) {
    // *new_solution = *new_solution + 1;
    *s_prev = *new_solution;
    // memcpy(s_prev, new_solution, 100 * sizeof(int));
    
    std::cout << "Se acepta!: " << *s_prev << ": :" << *new_solution << endl;
    return;
}

void reject_solution() {
    std::cout << "Se rechaza!: " << endl;
    return;
}

double rho_evaluate(double s_current, double s_prev) {
    return evaluation_function(s_current) - evaluation_function(s_prev); // min
    // return f(s_prev) - f(s_current); // max
}

void change_temperature(double * T) {
    *T = *T - 1;
    std::cout << "Temperatura actual!: " << *T << endl;

}

int main(int argc, char *argv[]){
   
    double T_initial = 1000;
    // int max_iterations = 1000;

    double T_current = T_initial;
    double s_prev; double new_solution;
    
    s_prev = 0;

    std::cout << "Bienvenidx!" << endl;
    std::string str_dimension = argv[1];
    string file_name = "WTA/wta" + str_dimension + ".txt";
    std::cout << "Escenario de dimensión: " << file_name << endl;
    // read_input(file_name);

    new_solution = moviment(s_prev);

    if(evaluation_function(new_solution)) {
        std::cout << "Se acepta primera prev!: " << s_prev << ": :" << new_solution << endl;
        accept_solution(&s_prev, &new_solution);
        std::cout << "Se acepta primera post!: " << s_prev << ": :" << new_solution << endl;
    } else {
        double rho = rho_evaluate(new_solution, s_prev);
        if(probability(rho, T_current) > gen_rand()) {
            accept_solution(&s_prev, &new_solution);
        } else {
            reject_solution();
        }
    }
    
    change_temperature(&T_current);
    
    return 0;
}