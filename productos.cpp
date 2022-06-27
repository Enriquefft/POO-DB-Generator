#include <random>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <iomanip>

using namespace std;

// Stock = (min,max)
const pair<int,int> STOCK_DESPENSA = make_pair(10,1000);
const pair<float,float> COSTO_DESPENSA = make_pair(10,100);

const pair<int,int> STOCK_BEBIDAS = make_pair(10,1000);
const pair<float,float> COSTO_BEBIDAS = make_pair(8,20);

const pair<int,int> STOCK_BOTANAS = make_pair(10,1000);
const pair<float,float> COSTO_BOTANAS = make_pair(2,20);

const pair<int,int> STOCK_CONFITERIA = make_pair(10,1000);
const pair<float,float> COSTO_CONFITERIA = make_pair(1,10);

const pair<int,int> STOCK_JARCIERIA = make_pair(10,1000);
const pair<float,float> COSTO_JARCIERIA = make_pair(20,50);

const pair<int,int> STOCK_HIGIENE = make_pair(10,1000);
const pair<float,float> COSTO_HIGIENE = make_pair(10,20);

const pair<int,int> STOCK_HARINAS = make_pair(10,1000);
const pair<float,float> COSTO_HARINAS = make_pair(12,25);

const pair<int,int> STOCK_FRUTAS = make_pair(10,1000);
const pair<float,float> COSTO_FRUTAS = make_pair(5,17);

const pair<int,int> STOCK_CARNES = make_pair(10,1000);
const pair<float,float> COSTO_CARNES = make_pair(10,50);

const pair<int,int> STOCK_DOMESTICOS = make_pair(10,1000);
const pair<float,float> COSTO_DOMESTICOS = make_pair(40,100);

// 166 productos unicos
const size_t n_productos = 166;

const pair<float, float> MULTIPLICADOR_PRECIO = make_pair(1, 1.5);

const pair<int, int> rango_codigo = make_pair(9000000, 9999999);


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


vector<int> GenerarNumericaSimple(size_t tamano_muestra, pair<int, int> rango){

    vector<int>new_vec(tamano_muestra);

    for(size_t i = 0; i < tamano_muestra; i++){
        size_t randint = GenerarRandomNum<int>(rango);
        new_vec[i] = randint;
    }
    return new_vec;
}
pair<float,float> CalcularCosto(string categoria){

    if(categoria == "despensa general"){
        return STOCK_DESPENSA;
    }
    if(categoria == "bebidas"){
        return STOCK_BEBIDAS;
    }
    if(categoria == "botanas"){
        return STOCK_BOTANAS;
    }
    if(categoria == "confitería"){
        return STOCK_CONFITERIA;
    }
    if(categoria == "jarciería"){
        return STOCK_JARCIERIA;
    }
    if(categoria == "higiene personal"){
        return STOCK_HIGIENE;
    }
    if(categoria == "harina y pan"){
        return STOCK_HARINAS;
    }
    if(categoria == "frutas y verduras"){
        return STOCK_FRUTAS;
    }
    if(categoria == "carnes y embutidos"){
        return STOCK_CARNES;
    }
    if(categoria == "uso doméstico"){
        return STOCK_DOMESTICOS;
    }
    else{
        cout << categoria << endl;
        throw runtime_error("Categoria no valida");
    }

}

pair<int,int> CategoryStock(string categoria){

    if(categoria == "despensa general"){
        return STOCK_DESPENSA;
    }
    if(categoria == "bebidas"){
        return STOCK_BEBIDAS;
    }
    if(categoria == "botanas"){
        return STOCK_BOTANAS;
    }
    if(categoria == "confitería"){
        return STOCK_CONFITERIA;
    }
    if(categoria == "jarciería"){
        return STOCK_JARCIERIA;
    }
    if(categoria == "higiene personal"){
        return STOCK_HIGIENE;
    }
    if(categoria == "harina y pan"){
        return STOCK_HARINAS;
    }
    if(categoria == "frutas y verduras"){
        return STOCK_FRUTAS;
    }
    if(categoria == "carnes y embutidos"){
        return STOCK_CARNES;
    }
    if(categoria == "uso doméstico"){
        return STOCK_DOMESTICOS;
    }
    else{
        cout << categoria << endl;
        throw runtime_error("Categoria no valida");
    }

}

int main (int argc, char *argv[])
{
    
    ifstream original_file("productos_original.csv");
    ofstream output_file("productos.csv");

    string original_string;

    // Verify correct opening of files
    if(!original_file){
        throw runtime_error("No se pudo abrir el archivo original\n");
    }
    if(!output_file){
        throw runtime_error("No se pudo abrir el archivo final\n");
    }

    unordered_set<int> code_check;

    // Get 1st line && remove ^M
    string header;
    getline(original_file, header);
    header = header.substr(0,header.size() - 1);
    output_file << header << endl;

    // Generate set of codes
    while(code_check.size() < n_productos){
        code_check.insert(GenerarRandomNum<int>(rango_codigo));
    }
    // Iterate over codes
    unordered_set<int>::iterator code_iterator;
    code_iterator = code_check.begin();

    // Iterate over file
    while(getline(original_file, original_string)){

        // Remove ^M
        original_string = original_string.substr(0,original_string.size() - 1);

        // Get category
        size_t index;
        string categoria;
        index = original_string.find(',');
        categoria = original_string.substr(0, index);

        // Categoria, Descripcion, 
        output_file << original_string;

        // Codigo, 
        output_file << *code_iterator << ", ";

        // Stock, 
        output_file << GenerarRandomNum<int>(CategoryStock(categoria)) << ", ";
        float costo = GenerarRandomNum<float>(CalcularCosto(categoria));

        // Costo, 
        output_file << fixed << setprecision(2) << costo << ", ";
        float precio = costo * GenerarRandomNum<float>(MULTIPLICADOR_PRECIO);

        // Precio
        output_file << fixed << setprecision(2) << precio;
        output_file << '\n';

        code_iterator++;

    }

    original_file.close();
    output_file.close();

    return 0;

}
