#include "searchEngine.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <ruta_del_indice_invertido> <TOPK>" << endl;
        return EXIT_FAILURE;
    }

    string indexPath = argv[1];            // Ruta del archivo de índice invertido
    int topK = atoi(argv[2]);              // Número de resultados a devolver
    int PORT = stoi(argv[3]);

    iniciarServidorBusqueda(topK, PORT, indexPath);

    return EXIT_SUCCESS;
}
