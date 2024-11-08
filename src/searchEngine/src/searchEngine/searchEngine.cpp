#include "searchEngine.h"

map<string, vector<Document>> invertedIndex;    // Índice invertido

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

vector<Document> buscar(const vector<string>& queryWords, int topK) {
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

    if (resultados.size() > topK) {
        resultados.resize(topK);
    }

    return resultados;
}

void procesarConsulta(int client_socket, int topK) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    if (valread < 0) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }

    string query(buffer);
    stringstream ss(query);
    vector<string> queryWords;
    string word;

    while (ss >> word) {
        queryWords.push_back(word);
    }

    vector<Document> resultados = buscar(queryWords, topK);

    string respuesta = "Resultados:\n";
    for (const auto& doc : resultados) {
        respuesta += "Documento: " + doc.name + " Puntaje: " + to_string(doc.score) + "\n";
    }

    send(client_socket, respuesta.c_str(), respuesta.size(), 0);
}

void iniciarServidorBusqueda(int topK) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket fallido");
        exit(EXIT_FAILURE);
    }

    // Configuración de la dirección
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket con la dirección
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind fallido");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Escuchar fallido");
        exit(EXIT_FAILURE);
    }
    cout << "Esperando conexiones en el puerto " << PORT << "..." << endl;

    // Aceptar una conexión
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Falló al aceptar conexión");
        exit(EXIT_FAILURE);
    }

    // Leer datos enviados desde el cliente
    int valread = read(new_socket, buffer, 1024);
    if (valread < 0) {
        perror("Lectura fallida");
        exit(EXIT_FAILURE);
    }

    cout << "Consulta recibida: " << buffer << endl;

    // Procesar la consulta (enviar la respuesta de búsqueda)
    vector<string> queryWords;
    istringstream queryStream(buffer);
    string word;
    while (queryStream >> word) {
        queryWords.push_back(word);
    }

    vector<Document> resultados = buscar(queryWords, topK);
    stringstream respuesta;
    for (const auto& doc : resultados) {
        respuesta << "Documento: " << doc.name << " Puntaje: " << doc.score << "\n";
    }

    // Enviar la respuesta al cliente
    send(new_socket, respuesta.str().c_str(), respuesta.str().length(), 0);

    close(new_socket);
    close(server_fd);
}

void iniciarMotorBusqueda(const string& indexPath, int topK) {
    cargarIndiceInvertido(indexPath);

    // Procesar la entrada de búsqueda
    cout << "Ingrese la consulta de búsqueda: ";
    string queryLine;
    getline(cin, queryLine);

    istringstream queryStream(queryLine);
    vector<string> queryWords;
    string word;
    while (queryStream >> word) {
        queryWords.push_back(word);
    }

    vector<Document> resultados = buscar(queryWords,topK);

    // Imprimir los resultados 
    cout << "Resultados de la búsqueda:" << endl;
    for (const auto& doc : resultados) {
        cout << "Documento: " << doc.name << " | Puntaje: " << doc.score << endl;
    }
}
