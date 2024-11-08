#include "cache.h"

void iniciarCache(int memory_size) {
    // Crear el socket para el servidor
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Crear el socket TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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

    // Aceptar conexiones entrantes
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    cout << "Conexión establecida con un cliente\n";

    // Leer el mensaje recibido
    while (true) {
        int valread = read(new_socket, buffer, 1024);
        if (valread < 0) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }

        cout << "Mensaje recibido: " << buffer << endl;
        
        // Si se recibe el mensaje "SALIR AHORA", cerramos el proceso
        if (strcmp(buffer, "SALIR AHORA") == 0) {
            cout << "Cerrando el proceso CACHE...\n";
            close(new_socket);
            break;
        }

        // Limpiar el buffer para la próxima lectura
        memset(buffer, 0, sizeof(buffer));
    }
    close(server_fd);
}

void manejarConexion(int new_socket,int memory_size) {
    char buffer[1024] = {0};
    
    // Leer el mensaje recibido
    int valread = read(new_socket, buffer, 1024);
    if (valread < 0) {
        perror("read failed");
        close(new_socket);
        return;
    }

    string query(buffer);

    // Verificar si la respuesta está en la caché
    if (cacheMap.find(query) != cacheMap.end()) {
        cout << "Respuesta encontrada en la caché: " << cacheMap[query] << endl;
        send(new_socket, cacheMap[query].c_str(), cacheMap[query].size(), 0);
    } else {
        // La respuesta no está en la caché, consultar al MOTOR DE BÚSQUEDA
        string response = "Respuesta del MOTOR DE BÚSQUEDA";  // Simulamos la respuesta

        // Si la memoria caché está llena, eliminar la respuesta más antigua
        if (cacheMap.size() >= memory_size) {
            string oldestQuery = cacheQueue.front();  // Eliminar el elemento más antiguo
            cacheQueue.pop();
            cacheMap.erase(oldestQuery);  // Borrar la entrada del mapa
        }

        // Almacenar la nueva respuesta en la caché
        cacheMap[query] = response;
        cacheQueue.push(query);  // Añadir la nueva consulta a la cola

        cout << "Respuesta no encontrada en la caché, consultando MOTOR DE BÚSQUEDA...\n";
        send(new_socket, response.c_str(), response.size(), 0);
    }

    // Limpiar el buffer para la próxima lectura
    memset(buffer, 0, sizeof(buffer));
}
