#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstring>
#include <string>
#include <fstream>
#include <random>
#include <math.h>
#include <cstdio>
using namespace std;

unsigned t0, t1;

struct Solution
{
    vector<int> x; // variable de asignacion de arma a objetivo
    int q;
    int r;

    Solution(int dimension)
    {
        vector<int> x_vector(dimension, 0);
        this->x = x_vector;
        this->q = 0;
        this->r = 0;
    }
};

struct Problem
{
    vector<vector<double>> p; // probabilidades dadas inicialmente
    vector<double> v;         // peso destructivo de cada objetivo
    Solution *solution;       // variable de asignacion de arma a objetivo

    Problem(int dimension)
    {
        vector<vector<double>> p_vector(0, vector<double>(0));
        vector<double> v_vector(0);
        this->p = p_vector;
        this->v = v_vector;
    }
};

/* Para generar un número random.*/
std::random_device rd;
std::mt19937 gen(rd());

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

double random(int low, int high)
{
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(low, high);
    return distr(eng);
}

/* Genera una solucion inicial */
void make_init_sol(vector<int> *matrix, int dimension)
{
    cout << "Generación de solución inicial.. " << endl;
    for (int i = 0; i < dimension; i += 1)
    {
        (*matrix)[i] = i;
        // cout << "Arma: " << i << " Objetivo: " << j << " Probabilidad: " << (*matrix)[i][j] << endl;
    }
}

/* Imprime el vector V que contiene los valores detructivos de los objetivos */
void print_v_vector(vector<double> v_vector, int dimension)
{
    cout << "V Vector : " << endl;
    for (int i = 0; i < dimension; i += 1)
    {
        cout << "Valor Destructivo del objetivo " << i << " : " << v_vector[i] << endl;
    }
}

/* Imprime el vector P que contiene las probabilidad de destruccion de los objetivos */
void print_p_vector(vector<vector<double>> p_vector, int dimension)
{
    cout << "P Vector : " << endl;
    for (int i = 0; i < dimension; i += 1)
    {
        for (int j = 0; j < dimension; j += 1)
        {
            cout << "Arma: " << i << " Objetivo: " << j << " Probabilidad: " << p_vector[i][j] << endl;
        }
    }
}

/* Imprime el vector X solucion */
void print_x_vector(vector<int> p_vector)
{
    double dimension = p_vector.size();
    cout << "X vector (solución): " << endl;
    for (int i = 0; i < dimension; i += 1)
    {
        cout << "Arma: " << i << " Objetivo: " << p_vector[i] << endl;
    }
}

/* Lee la instancia */
void read_input(string file_name, Problem *problem, int int_dimension)
{
    ifstream file(file_name.c_str());

    string line;
    int n_line = 0;
    int p_i_dimension = 0;
    int p_j_dimension = 0;
    int dimension = int_dimension;
    vector<vector<double>> p_vector(dimension, vector<double>(dimension));
    vector<double> v_vector(dimension);

    /* Obtener línea de archivo, y almacenar contenido en "linea" */
    while (getline(file, line))
    {
        if (n_line > 0 && n_line < dimension + 1)
        {
            /* captura y seteo de valores de destruccion */
            v_vector[n_line - 1] = stod(line);
        }
        else if (n_line >= dimension + 1)
        {
            /* captura de probabilidades */
            if (p_j_dimension == dimension)
            {
                p_i_dimension += 1;
                p_j_dimension = 0;
            }
            /* seteo de probabilidades */
            p_vector[p_i_dimension][p_j_dimension] = stod(line);
            p_j_dimension += 1;
        }
        n_line += 1;
    }
    // print_p_vector(p_vector, dimension);
    // print_v_vector(v_vector, dimension);

    /* Seteo de vectores p y v en la estructura de datos Problem */
    (*problem).p = p_vector;
    (*problem).v = v_vector;
}

Solution make_movement(Solution *s_current, int q, int r)
{
    Solution s_next = *s_current;

    // cout << "Arma q: " << q << endl;
    // cout << "Arma r: " << r << endl;

    int aux_q = (s_next.x)[q];
    int aux_r = (s_next.x)[r];

    (s_next.x)[q] = aux_r;
    (s_next.x)[r] = aux_q;

    (s_next).q = q;
    (s_next).r = r;

    return s_next;
}

/*
- Un delta más grande que 0.5 conduce a una probabilidad
de aceptación más pequeña.
- Una T más pequeña conduce a una probabilidad de aceptación
más pequeña.
*/
double P(double delta, double T)
{
    if (delta < 0)
        return 1;
    return exp((-1 * delta) / T);
}

double f(Problem s)
{
    double sumatoria = 0;
    int n = (*s.solution).x.size();
    int m = (*s.solution).x.size();
    for (int j = 0; j < n; j++)
    {
        double productoria = 1;
        for (int i = 0; i < m; i++)
        {
            double q_j = 1 - s.p[i][j];
            int target_weapon_i = (*s.solution).x[i];
            if (target_weapon_i == j)
                productoria *= q_j;
        }

        sumatoria += (s.v[j] * productoria);
    }
    return sumatoria;
}

bool acceptance_function(double delta, double T_current)
{
    double rdm = random(0.0, 1.0);

    if (P(delta, T_current) > rdm)
        return true;
    return false;
}

void accept_solution(Problem *problem, Solution *new_solution)
{
    *((*problem).solution) = *new_solution;
    return;
}

double delta_evaluate(Problem problem, Solution new_solution)
{
    Problem new_problem = problem;
    new_problem.solution = &new_solution;

    double delta = f(new_problem) - f(problem);
    return delta;
}

void change_temperature(double *T, double k)
{
    *T = *T * k;
}

int main(int argc, char *argv[])
{
    /*  INITIAL PARAMETERS */
    double T_initial = 1000;
    double T_min, k;
    double T_current = T_initial;
    int max_iterations, movement, int_dimension;

    cout << "Bienvenidx a la implementación de SA con MM para el problema WTA!" << endl;

    /* Define dimensión entregada por argumento */
    string str_dimension = argv[1];
    string str_k = argv[2];
    string str_t_init = argv[3];
    string str_t_finish = argv[4];
    string str_max_iter = argv[5];
    string str_movement = argv[6];

    /* Transformación de la dimensión en entero */
    int_dimension = stoi(str_dimension);
    k = stod(str_k);
    T_initial = stod(str_t_init);
    T_min = stod(str_t_finish);
    max_iterations = stoi(str_max_iter);
    movement = stoi(str_movement);

    /* PARAMETROS */
    cout << "DIMENSION: " << int_dimension << endl;
    cout << "K: " << k << endl;
    cout << "T_init: " << T_initial << endl;
    cout << "T_finish: " << T_min << endl;
    cout << "Max_iter: " << max_iterations << endl;
    cout << "Movement: " << movement << endl;

    /* Definición del nombre de archivo para la entrada de la instancia */
    string file_name = "WTA/wta" + str_dimension + ".txt";
    cout << "Escenario de dimensión: " << file_name << endl;

    t0 = clock(); // inicia temporizador

    /* SET INITIAL VARIABLES */
    /* Instancia de la estructura de datos */
    Problem problem = Problem(int_dimension);
    Solution s_current = Solution(int_dimension);

    /* Generacion de solucion inicial */
    make_init_sol(&(s_current.x), int_dimension); // Asignamos el arma de tipo i al objetivo de indice i.
    s_current.x = (s_current.x);
    problem.solution = &s_current;

    /* Lectura de la instancia de entrada */
    read_input(file_name, &problem, int_dimension);

    /* ======================= */
    /* ALGORITHM */
    /* MOVIMIENTO : swap de dos armas random */

    /* Generar vecindario */
    /* Escoger el mejor vecino respecto a la solución actual con la evaluación de sus deltas*/
    /* Consultar función de aceptación de la solución escogida */
    /* Cambiar temperatura */

    /* ALGORITHM */
    /* ======================= */

    double f_current = f(problem);

    /* Condiciones de término de la busqueda */
    // - Máximo de iteraciones
    // - Temperatura tiende a cero o una temperatura minima
    // - Tiempo máximo
    // Solution best_solution = Solution(int_dimension);
    Solution best_solution = (*problem.solution);
    int iteraciones = 0;

    for (int i = 0; (i < max_iterations) && (T_current > T_min); i++)
    {
        cout << "Iteracion: " << i << " , T: " << T_current << " , F(X): " << f(problem) << endl;

        int pivot = random(0, int_dimension - 1);   // indice del objetivo pivot
        double best_delta = INFINITY;   //  mejor delta
        double best_f_nbh = INFINITY;   //  mejor funcion objetivo del vecindario

        /* Generar vecindario */
        for (int j = 0; j < int_dimension; j++)
        {
            if (movement == 1)
            {
                if (j == pivot)
                    continue;
            }

            /* Seteo de delta y nueva solución */
            double delta = 0.0;     // diferencia entre la función objetivo de la solución actual y el vecino generado.
            double f_new_problem = 0.0;     // valor de la función objetivo del vecino actual.

            Solution new_solution = Solution(int_dimension);

            /* Generar vecino */
            int r, q;
            if (movement == 0)
            {
                r = random(0, int_dimension - 1);
                q = random(0, int_dimension - 1);
            }
            else if (movement == 1)
            {
                q = j;
                r = pivot;
            }
            else if (movement == 2)
            {
                if (j == int_dimension - 1)
                    continue;
                q = j;
                r = j + 1;
            }
            new_solution = make_movement(problem.solution, q, r);

            /* Evaluar delta */
            delta = delta_evaluate(problem, new_solution);

            Problem new_problem = problem;
            new_problem.solution = &new_solution;
            f_new_problem = f(new_problem);

            /* Guardar el mejor delta */
            if ((best_f_nbh >= f_new_problem) && (delta < 0)) // si es mejor que la solucion actual y mejor del vecindario
            // best_f_nbh >= f_new_problem      =>  la  función objetivo del nuevo vecino es menor que la mejor del vecindario.
            // delta < 0    => la solución del vecino actual es mejor que la del vecino pivot.
            {
                /* Guarda el mejor delta y la mejor solucion del vecindario*/
                best_delta = delta;
                best_f_nbh = f_new_problem;
                best_solution = new_solution;
            }
        }
        best_f_nbh = INFINITY;

        if (acceptance_function(best_delta, T_current))
            accept_solution(&problem, &best_solution);

        change_temperature(&T_current, k);
        iteraciones = i;
    }

    // cout << "FUNCION OBJETIVO BEST: " << f(problem) << endl;

    t1 = clock();   // termina temporizador
    cout << "Hasta pronto!" << endl;

    double time = (double(t1 - t0) / CLOCKS_PER_SEC); // transformacion de clocks a segundos.

    /* Escribir en log los resultados */
    freopen("wta.csv", "a", stderr);
    // std::cerr << "DIM: " << str_dimension << ", T_i: " << T_initial << ", T_f: " << T_min << ", K: " << k << ", Max_iter: " << max_iterations << ", F: " << f(problem) << ", Movement: " << movement <<  ", TIME: " << time << endl;
    std::cerr << str_dimension << ", " << T_initial << ", " << T_min << ", " << k << ", " << max_iterations << ", " << f(problem) << ", " << movement << ", " << time << ", " << iteraciones << endl;
    fclose(stderr);
    t0 = 0;
    t1 = 0;

    return 0;
}