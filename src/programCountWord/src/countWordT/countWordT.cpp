#include "countWordT.h"

mutex coutMutex;                // Mutex para proteger la impresión en consola
atomic<int> totalPalabras(0);   // Contador atómico para las palabras

bool menuCWT( string extension, string pathEntrada, string pathSalida, string cantidadThreadsStr, string mapPath, string stopPath){
    int opcion;
    // Convertir cantidadThreads a entero
    int cantidadThreads = !cantidadThreadsStr.empty() ? stoi(cantidadThreadsStr) : 1; 
    // Valor predeterminado 1 si no se encuentra
    while (true) {
        cout << "------------------ [Contador de palabras con Threads] ------------------\n";
        cout << "   0 : Salir\n";
        cout << "   1 : Procesar\n";
        cout << "-----------------------------------------------\n";
        cout << "INGRESE OPCIÓN: ";
        cin >> opcion;
        cout << "-----------------------------------------------\n";
        cout << "\n";
        if (opcion == 1) {
            if (!pathEntrada.empty() && !pathSalida.empty() && !extension.empty()) {
                procesarArchivos(pathEntrada, pathSalida, extension, cantidadThreads, mapPath, stopPath);
                return true;
            } else {
                cerr << "Error: No se pudo obtener las variables necesarias.\n";
                return false;
            }
        } else if (opcion == 0) {
            return false;
        } else {
            cerr << "Opción no válida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

vector<string> cargarArchivos(const string& directorio, const string& extension, string mapPath) {
    vector<string> archivos;
    cout << directorio << endl;
    // Verificar si el directorio existe
    if (!fs::exists(directorio) || !fs::is_directory(directorio)) {
        cerr << "Error: El directorio no existe o no es un directorio válido.\n";
        return archivos; // Regresa un vector vacío
    }

    // Iterar sobre los archivos en el directorio
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + extension) {
            archivos.push_back(entry.path().string()); // Agregar el archivo al vector
        }
    }
    crearMap(extension, directorio, mapPath,archivos);

    // Mostrar la lista de archivos cargados (opcional)
    cout << "Archivos cargados con extensión '" << extension << "':\n";
    for (const auto& archivo : archivos) {
        cout << " - " << archivo << '\n';
    }

    return archivos;
}

void crearMap(string extension, string entradaPath, string mapPath, vector<string> archivos){
    string archivoMap = mapPath + "/map." + extension;
    ofstream outputFile(archivoMap);
    if (!outputFile) {
        cerr << "Error al crear el archivo de salida: " << archivoMap << endl;
        return;
    }
    string nombre;
    for(int i = 0; i<archivos.size() ; i++){
        nombre = archivos[i].erase(0, entradaPath.length()+1);
        nombre = archivos[i].erase(archivos[i].length()-extension.length()-1, extension.length()+1);
        outputFile << nombre << ", " << i << "\n";
    }
    outputFile.close();

}



// Función para contar palabras en un archivo
void contarPalabrasEnArchivo(const string& archivo, const string& pathSalida, string extension, int indice) {
    ifstream inputFile(archivo);
    if (!inputFile) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    // Crear el archivo de salida
    string archivoSalida = (fs::path(pathSalida) / to_string(indice)).string() + "."+ extension;
    ofstream outputFile(archivoSalida);
    if (!outputFile) {
        cerr << "Error al crear el archivo de salida: " << archivoSalida << endl;
        return;
    }

    // Mapa para almacenar las palabras y su cantidad
    map<string, int> contadorPalabras;

    string linea;
    // Leer cada línea del archivo
    while (getline(inputFile, linea)) {
        istringstream iss(linea);
        string palabra;

        // Leer cada palabra de la línea y contarla
        while (iss >> palabra) {
            //palabra.erase(std::remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
            palabra = limpiarPalabra(palabra);
            contadorPalabras[palabra]++;
        }
    }

    inputFile.close();

    // Escribir el conteo de palabras en el archivo de salida
    for (const auto& [palabra, cantidad] : contadorPalabras) {
        outputFile << palabra << "; " << cantidad << "\n";
    }

    outputFile.close();

    {
        lock_guard<mutex> guard(coutMutex);
        cout << "Archivo: " << archivo << " tiene " << contadorPalabras.size() << " palabras únicas.\n";
    }
}

// Función principal para contar palabras utilizando threads
void countWordThreads(const vector<string>& archivos, int cantidadThreads, const string& pathSalida, string extension, string stopWord) {
    vector<thread> threads;
    set<string> stopWords = leerPalabras(stopWord);
    if(stopWords.empty()) cout << "No hay palabras en stopword.txt, se procederá normalmente con el procesamiento." << endl;
    for (int i = 0; i<archivos.size() ; i++) {
        // Usamos una lambda para pasar correctamente los parámetros a la función
        threads.emplace_back([&archivos, &pathSalida, extension, stopWords, i]() {
            if(!stopWords.empty()) eliminarPalabras(archivos[i], stopWords);
            contarPalabrasEnArchivo(archivos[i], pathSalida, extension, i);
        });

        if (threads.size() >= cantidadThreads) {
            for (auto& th : threads) {
                th.join(); // Esperar a que el thread termine
            }
            threads.clear(); // Limpiar el vector de threads
        }
    }

    // Unir los threads restantes que no se han unido todavía
    for (auto& th : threads) {
        th.join();
    }

    cout << "Total de palabras en todos los archivos: " << totalPalabras.load() << endl;
}


void procesarArchivos(const string& inputPath, const string& outputPath, const string& extension, int cantidadThreads, string mapPath, string stopPath) {
    vector<string> archivos = cargarArchivos(inputPath, extension, mapPath);
    if (archivos.empty()) {
        cerr << "No se encontraron archivos con la extensión '" << extension << "' en el directorio '" << inputPath << "'.\n";
        return;
    }
    
    // Procesar los archivos con la función de threads
    countWordThreads(archivos, cantidadThreads, outputPath, extension, stopPath); // Pasamos también el path de salida
}

string limpiarPalabra(const std::string& palabra) {
    string limpia = palabra;
    
    // Eliminar puntuación al inicio (incluye ¿ y ¡)
    limpia.erase(limpia.begin(), std::find_if(limpia.begin(), limpia.end(), [](unsigned char ch) {
        return !ispunct(ch) && ch != '¡' && ch != '¿';
    }));

    // Eliminar puntuación al final (incluye ? y !)
    limpia.erase(std::find_if(limpia.rbegin(), limpia.rend(), [](unsigned char ch) {
        return !std::ispunct(ch) && ch != '!' && ch != '?';
    }).base(), limpia.end());

    return limpia;
}

set<string> leerPalabras(const string& archivoPalabras) {
    set<string> palabras;
    ifstream archivo(archivoPalabras);
    string palabra;

    if (archivo.is_open()) {
        while (archivo >> palabra) {
            palabras.insert(palabra);
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo de palabras: " << archivoPalabras << endl;
    }

    return palabras;
}

// Función para eliminar palabras de un archivo dado
void eliminarPalabras(const string& archivoObjetivo, const set<string>& palabrasAEliminar) {
    ifstream archivoEntrada(archivoObjetivo);
    stringstream buffer;
    string palabra;
    string resultado;

    if (archivoEntrada.is_open()) {
        buffer << archivoEntrada.rdbuf(); // Leemos todo el contenido del archivo
        archivoEntrada.close();
    } else {
        cerr << "Error al abrir el archivo objetivo: " << archivoObjetivo << endl;
        return;
    }

    stringstream ss(buffer.str());
    while (ss >> palabra) {
        // Si la palabra no está en el conjunto, la añadimos al resultado
        if (palabrasAEliminar.find(palabra) == palabrasAEliminar.end()) {
            resultado += palabra + " ";
        }
    }

    // Sobreescribimos el archivo con el contenido filtrado
    ofstream archivoSalida(archivoObjetivo);
    if (archivoSalida.is_open()) {
        archivoSalida << resultado;
        archivoSalida.close();
    } else {
        cerr << "Error al sobrescribir el archivo objetivo: " << archivoObjetivo << endl;
    }
}