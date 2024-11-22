#include "cache.h"

map<string, string> cacheMap;  // Definición real
queue<string> cacheQueue;      // Definición real

void iniciarCache(int memory_size, int PORT ) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
}

    // Permitir reutilizar el puerto
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);


    // Enlazar el socket a la dirección y puerto
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Escuchar las conexiones entrantes (máximo 3 conexiones en espera)
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Esperando conexiones en el puerto " << PORT << "...\n";

    // Bucle principal para aceptar y manejar conexiones
    while (true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;               // No salir en caso de fallo, seguir aceptando conexiones
        }

        manejarConexion(new_socket, memory_size);
        close(new_socket);          // Cerrar la conexión después de manejarla
    }

    close(server_fd);               // Cerrar el servidor al finalizar
}

void manejarConexion(int new_socket,int memory_size) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    if (valread < 0) {
        perror("read failed");
        return;
    }

    string query(buffer);

    // Verificar si la respuesta está en la caché
    if (cacheMap.find(query) != cacheMap.end()) {
        cout << "Respuesta encontrada en la caché: " << cacheMap[query] << endl;
        send(new_socket, cacheMap[query].c_str(), cacheMap[query].size(), 0);
    } else {
        cout << "Respuesta no encontrada en la caché, consultando MOTOR DE BÚSQUEDA...\n";
        string response = consultarMotorDeBusqueda(query);

        // Si la memoria caché está llena, eliminar la respuesta más antigua
        if (cacheMap.size() >= memory_size) {
            string oldestQuery = cacheQueue.front();    // Eliminar el elemento más antiguo
            cacheQueue.pop();
            cacheMap.erase(oldestQuery);                // Borrar la entrada del mapa
        }

        // Almacenar la nueva respuesta en la caché
        cacheMap[query] = response;
        cacheQueue.push(query);         // Añadir la nueva consulta a la cola

        cout << "Respuesta no encontrada en la caché, consultando MOTOR DE BÚSQUEDA...\n";
        send(new_socket, response.c_str(), response.size(), 0);
    }
}

string consultarMotorDeBusqueda(const string &query) {
    cout << "Consultando MOTOR DE BÚSQUEDA para: " << query << endl;
    string respuesta = "Resultado encontrado para la consulta: \"" + query + "\"";

    srand(static_cast<unsigned int>(time(0)));
    int resultadoAleatorio = rand() % 3;
    switch (resultadoAleatorio) {
        case 0:
            respuesta += " - Artículo relevante encontrado.";
            break;
        case 1:
            respuesta += " - Documento relacionado localizado.";
            break;
        case 2:
            respuesta += " - Ningún resultado exacto, mostrando coincidencias aproximadas.";
            break;
    }

    cout << "Respuesta generada por el MOTOR DE BÚSQUEDA: " << respuesta << endl;

    return respuesta;
}
