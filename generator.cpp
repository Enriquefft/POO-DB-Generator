// Formato
// Fecho, DNI, Nombre, Sexo, Edad, Codigo_Producto, descripcion_producto, Cantidad_Producto, Precio_Unitario, precio_total

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <string>
#include <sstream>

#include <unordered_set>

using namespace std;

const size_t TAMANO_MUESTRA = 5;

using CATEGORICAL = unordered_set<string>;
using NUMERICAL_CONTINUOUS = unordered_set<float>;
using NUMERICAL_DISCRETE = unordered_set<int>;

const pair<int, int> rango_edades = make_pair(17, 35);
const pair<int, int> rango_cantidad = make_pair(1, 19);
const pair<float, float> rango_precio = make_pair(0.99, 99.99);

template <typename T>
T GenerarRandomNum(pair<T, T> rango){

    random_device r_d;
    default_random_engine  generator(r_d());

    T ranum;
    if constexpr(is_same<T, int>::value){
        uniform_int_distribution<T> rand_num(rango.first, rango.second);
        ranum = rand_num(generator);
    }
    else if constexpr(is_same<T, float>::value){
        uniform_real_distribution<T> rand_num(rango.first, rango.second);
        ranum = rand_num(generator);
    }

    return ranum;   
}


string FormatFileName(string file_name){

    size_t size = file_name.size();
    if(size < 4 or file_name.substr(size - 4) != ".csv"){
        string new_name = file_name + ".csv";
        return new_name;
    }
    else{
        return file_name;
    }

}

NUMERICAL_CONTINUOUS GenerarNumericaContinua(size_t tamano_muestra, pair<float, float> rango){

    NUMERICAL_CONTINUOUS new_vec(tamano_muestra);

    for(size_t i = 0; i < tamano_muestra; i++){

        float randint = GenerarRandomNum<float>(rango);
        new_vec[i] = randint;
    }
    return new_vec;
}
NUMERICAL_DISCRETE GenerarNumericaSimple(size_t tamano_muestra, pair<int, int> rango){

    NUMERICAL_DISCRETE new_vec(tamano_muestra);

    for(size_t i = 0; i < tamano_muestra; i++){
        size_t randint = GenerarRandomNum<size_t>(rango);
        new_vec[i] = randint;
    }
    return new_vec;
}

CATEGORICAL GenerarCategoricaSimple(CATEGORICAL vec, size_t tamano_muestra){

    CATEGORICAL new_vec(tamano_muestra);
    pair<int, int> rango = make_pair(0, vec.size() - 1);

    for(size_t i = 0; i < tamano_muestra; i++){
        size_t randint = GenerarRandomNum<int>(rango);
        new_vec[i] = vec[randint];
    }
    return new_vec;
}

template <typename T>
void ImprimirVector(vector<T> vec){
    for(T elem : vec){
        cout << elem << ", ";
    }
    cout << endl;
}

vector<float> MultiplicarVector(vector<float> precio, vector<int> cantidad){
    size_t tamano = precio.size();
    vector<float> new_vec(tamano);
    for(size_t i = 0; i < tamano; i++){
        new_vec[i] = precio[i] * cantidad[i];

    }
    return new_vec;
}

pair<string, int> GetDescriptionCode(string line){
    // Categoría,Producto,Codigo,Stock
    string descripcion;
    int codigo;

    size_t index;
    index = line.find(',');
    line = line.substr(index + 1, line.size());
    index = line.find(',');
    descripcion = line.substr(0, index);
    line = line.substr(index + 1, line.size());
    index = line.find(',');
    codigo = stoi(line.substr(0,index));

    return make_pair(descripcion, codigo);
}

int main (int argc, char *argv[])
{

    // Initialize values

    // TODO fecha
    CATEGORICAL dni;
    CATEGORICAL descripcion_producto;

    CATEGORICAL sexo = {"M", "F"};
    NUMERICAL_DISCRETE edad;
    NUMERICAL_DISCRETE cantidad;
    NUMERICAL_CONTINUOUS precio;
    NUMERICAL_CONTINUOUS precio_total;

    unordered_set<string> nombre;
    ifstream unisex_names("unisex_names.csv");

    if(!unisex_names.is_open()){
        throw runtime_error("Could not open file");
    }

    string line;
    getline(unisex_names, line);

    stringstream ss(line);
    string tmp_word;
    
    while(getline(ss, tmp_word, ',')){
        nombre.insert(tmp_word);
    }

    sexo = GenerarCategoricaSimple(sexo, TAMANO_MUESTRA);
    nombre = GenerarCategoricaSimple(nombre, TAMANO_MUESTRA);
    edad = GenerarNumericaSimple(TAMANO_MUESTRA, rango_edades);
    cantidad = GenerarNumericaSimple(TAMANO_MUESTRA, rango_cantidad);
    precio = GenerarNumericaContinua(TAMANO_MUESTRA, rango_precio);
    precio_total = MultiplicarVector(precio, cantidad);

    // Verify file_name exists
    if(argc !=  2){
        cout << "Ingrese el nombre del archivo como unico argumento" << endl;
        return 1;
    }

    // Verify and correct output file name
    string file_name = argv[1];
    file_name = FormatFileName(file_name);
    
    ofstream database(file_name);

    for(size_t i = 0; i < TAMANO_MUESTRA; i++){
    }

    database.close();
    return 0;
}
