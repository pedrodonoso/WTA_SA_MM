#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstring>
#include <fstream>
#include <random>
#include <math.h>
using namespace std;

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

/* Asignamos vectores seteados en cero para los vectores p y v. */
// vector<vector<double>> p(0, vector<double>(0));
// vector<double> v(0);

/* Para generar un número random.*/
std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
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
    print_p_vector(p_vector, dimension);
    print_v_vector(v_vector, dimension);

    /* Seteo de vectores p y v en la estructura de datos Problem */
    (*problem).p = p_vector;
    (*problem).v = v_vector;
}
/* =============== */
Solution make_movement(Solution *s_current)
{

    Solution s_next = *s_current;
    int dimension = s_next.x.size();

    int q = random(0, dimension - 1);
    int r = random(0, dimension - 1);
    cout << "RANDOM q: " << q << endl;
    cout << "RANDOM r: " << r << endl;

    // vector<int> null_vector = vector<int>(dimension,0);

    int aux_q = (s_next.x)[q];
    int aux_r = (s_next.x)[r];

    (s_next.x)[q] = aux_r;
    (s_next.x)[r] = aux_q;

    // cout << "se realiza el movimiento: " << endl;
    // *s_current = s_next;
    // (*s_current).q = q;
    // (*s_current).r = r;

    (s_next).q = q;
    (s_next).r = r;
    // cout << "MAKING MOVE" << endl;
    // print_x_vector(s_next.x);
    // print_x_vector((*s_current).x);
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
    // return (1 / (1 + (exp(delta/max(T)))));
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

// void evaluation_function(Solution s) {
bool evaluation_function(double *s_prev, double *new_solution)
{
    // y retorna true si es mejor que s_prev o false si es peor!
    cout << "Se evalua s_current: " << *s_prev << endl;
    return false;
}

// void evaluation_function(Solution s) {
bool acceptance_function(double delta, double T_current)
{
    if (P(delta, T_current) > random(0, 1))
        return true;
    return false;
}

void accept_solution(Problem *problem, Solution *new_solution)
{
    // *new_solution = *new_solution + 1;
    // *s_prev = *new_solution;
    // memcpy(s_prev, new_solution, 100 * sizeof(int));
    // vector<int> s_x(new_solution.x.size());
    // copy(new_solution.x.begin(), new_solution.x.end(), s_x.begin());

    // print_x_vector((*(*problem).solution).x);
    // print_x_vector((*new_solution).x);
    (*problem).solution = new_solution;

    // cout << "Se acepta!: " << *s_prev << ": :" << *new_solution << endl;
    cout << "Se acepta!" << endl;
    return;
}

void reject_solution()
{
    cout << "Se rechaza!" << endl;
    return;
}

double delta_evaluate(Problem problem, Solution new_solution)
{
    int q = (new_solution).q;
    int r = (new_solution).r;
    cout << "Q: " << q << " R: " << r << endl;
    double delta = problem.v[q] * (problem.p[q][q] - problem.p[r][q]) + problem.v[r] * (problem.p[r][r] - problem.p[q][r]);

    // valor de destrucción de q * (probabilidad de destrucción después del movimiento - probabilidad de destrucción antes del movimiento)
    // valor de destrucción de r * (probabilidad de destrucción después del movimiento - probabilidad de destrucción antes del movimiento)

    // probabilidad arma_q -> obj_q AHORA
    // probabilidad arma_r -> obj_q ANTES
    // probabilidad arma_r -> obj_r AHORA
    // probabilidad arma_q -> obj_r ANTES

    // Problem new_problem = problem;
    // new_problem.solution = &new_solution;
    // double delta = f(new_problem) - f(problem);
    // // return f(new_problem) - f(problem); // min
    // cout << "Delta: " << delta << endl;
    return delta; // min
    // return f(s_prev) - f(s_current); // max
}

// k : parámetro de recocido.
void change_temperature(double *T, double k)
{
    *T = *T * k;
}

int main(int argc, char *argv[])
{
    /*  INITIAL PARAMETERS */
    double T_initial = 1000;
    double k = 0.8; // usualmente entre 0.8 y 0.9999
    int max_iterations = 5;
    double T_min = 1e-10;
    double T_current = T_initial;

    cout << "Bienvenidx a la implementación de SA con MM para el problema WTA!" << endl;

    /* Define dimensión entregada por argumento */
    string str_dimension = argv[1];
    /* Transformación de la dimensión en entero */
    int int_dimension = stoi(str_dimension);
    /* Definición del nombre de archivo para la entrada de la instancia */
    string file_name = "WTA/wta" + str_dimension + ".txt";
    cout << "Escenario de dimensión: " << file_name << endl;

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

    /* Imprime solucion inicial */
    print_x_vector((*problem.solution).x);

    /* ======================= */
    /* ALGORITHM */

    /* Generar vecindario */
    /* Escoger el mejor vecino respecto a la solución actual con la evaluación de sus deltas*/
    /* Consultar función de aceptación de la solución escogida */
    /* Cambiar temperatura */

    double f_current = f(problem);
    cout << "FUNCION OBJETIVO : " << f_current << endl;

    // Iteracion
    // movimiento -> dos numeros random de armas y swap
    // calcular delta f = v_q (p_qq - p_rq) + v_r (p_rr - p_qr)
    // aceptar o rechazar la s_new usando P( delta f)
    // si s_new es aceptada entonces setea la solucion s_current y sigue a GOTO
    // si s_new es rechazada entonces si f< f_best : f_best = f_new y s_best = s_new

    double delta = 0;
    Solution new_solution = Solution(int_dimension);
    /*
    - si se llegan a las maximas iteraciones
    - temperatura tiende a cero o una temperatura minima
    - tiempo máximo
    */
    for (int i = 0; (i <= max_iterations) && (T_current >= T_min); i++)
    {
        cout << "Iteracion: " << i << " , T: " << T_current << endl;
        // print_x_vector((*problem.solution).x);
        cout << "Realizar movimiento" << endl;
        new_solution = make_movement(problem.solution);

        /* Generar vecindario */
        for (int j = 0; j < 5; j++)
        {
            /* Generar vecino */

            /* Evaluar delta */
            /* Guardar el mejor delta */
        }

        /* Consultar función de aceptación de la solución escogida */

        cout << "Calcular delta: " << endl;
        delta = delta_evaluate(problem, new_solution);

        cout << "Decision: " << endl;
        if (acceptance_function(delta, T_current))
            accept_solution(&problem, &new_solution);
        else
            reject_solution();

        print_x_vector((*problem.solution).x);
        cout << "FUNCION OBJETIVO : " << f(problem) << endl;
        change_temperature(&T_current, k);
    }

    cout << "Hasta pronto!" << endl;
    return 0;
}