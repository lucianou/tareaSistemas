#include "searchEngine.h"

map<string, vector<Document>> invertedIndex;
int TOPK;

void cargarIndiceInvertido(const string& indexPath) {
    ifstream file(indexPath);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de índice: " << indexPath << endl;
        exit(EXIT_FAILURE);
    }

    string line, word, doc;
    int score;
    while (getline(file, line)) {
        istringstream ss(line);
        ss >> word;
        vector<Document> docs;
        while (ss >> doc >> score) {
            docs.push_back({doc, score});
        }
        invertedIndex[word] = docs;
    }
    file.close();
    cout << "Índice invertido cargado correctamente." << endl;
}

vector<Document> buscar(const vector<string>& queryWords) {
    map<string, int> docScores;

    for (const auto& word : queryWords) {
        if (invertedIndex.find(word) != invertedIndex.end()) {
            for (const auto& doc : invertedIndex[word]) {
                docScores[doc.name] += doc.score;
            }
        }
    }

    vector<Document> resultados;
    for (const auto& entry : docScores) {
        resultados.push_back({entry.first, entry.second});
    }

    sort(resultados.begin(), resultados.end(), [](const Document& a, const Document& b) {
        return b.score < a.score;
    });

    if (resultados.size() > TOPK) {
        resultados.resize(TOPK);
    }

    return resultados;
}

void iniciarMotorBusqueda(string indexPath) {

    const char* topKEnv = getenv("TOPK");
    if (topKEnv) {
        TOPK = stoi(topKEnv);
    } else {
        cerr << "Variable de entorno TOPK no establecida." << endl;
        exit(EXIT_FAILURE);
    }

    cargarIndiceInvertido(indexPath);

    // Ejemplo de consulta
    vector<string> query = {"palabra1", "palabra2"};
    vector<Document> resultados = buscar(query);

    for (const auto& doc : resultados) {
        cout << "Documento: " << doc.name << " Puntaje: " << doc.score << endl;
    }
}