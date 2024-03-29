#include "menu.h"

void mostrar_menu_principal(){
    cout << WHITE << " 1.Modificar edificio por nombre." << endl;
    cout << WHITE << " 2.Listar todos los edificios." << endl;
    cout << WHITE << " 3.Mostrar mapa." << endl;
    cout << WHITE << " 4.Comenzar partida." << endl;
    cout << WHITE << " 5.Guardar y salir." << endl;
}

void mostrar_menu_partida(){
    
    cout <<  WHITE << " 1.Construir edificio por nombre." << endl;
    cout <<  WHITE << " 2.Listar los edificios construidos." << endl;
    cout <<  WHITE << " 3.Demoler un edificio por coordenada." << endl;
    cout <<  WHITE << " 4.Atacar un edificio por coordenada" << endl;
    cout <<  WHITE << " 5.Reparar un edificio por coordenada." << endl;
    cout <<  WHITE << " 6.Comprar bombas." << endl;
    cout <<  WHITE << " 7.Consultar coordenada." << endl;
    cout <<  WHITE << " 8.Mostrar inventario." << endl;
    cout <<  WHITE << " 9.Mostrar objetivos." << endl;
    cout <<  WHITE << " 10.Recolectar recursos producidos." << endl;
    cout <<  WHITE << " 11.Moverse a una coordenada." << endl;
    cout <<  WHITE << " 12.Finalizar turno." << endl;
    cout <<  WHITE << " 13.Guardar y salir." << endl;

}

bool opcion_valida(int opcion){
    if ( opcion <= 0 || opcion > GUARDAR_SALIR){
        return false;
    }else {
        return true;
    }
}

int elegir_opcion(){
    // validar la opcion elegida por el usuario: 
    int opcion;

    cout << " -> ";
    cin >> opcion;

    while (!opcion_valida(opcion)){
        cout << "Ingrese una opcion valida: ";
        cin >> opcion;
    }

    system(CLR_SCREEN);

    return opcion;
}

void procesar_opcion_principal(int opcion, Mapa * mapa, Jugador * j1, Jugador * j2){

    switch (opcion)
    {

    case P_MODIFICAR_EDIFICIO:
        mapa -> modificar_edificios();
        break;
    
    case P_LISTAR_TODOS_EDIFICIOS:
            mapa->listar_todos_edificios();
        break;
    
    case P_MOSTRAR_MAPA:
            mapa->mostrar_mapa();
        break;
    
    case P_COMENZAR_PARTIDA:
            empezar_partida(mapa, j1, j2);
        break;
    
    case P_GUARDAR_SALIR:
            cout << "Guardar y Salir" << endl;
        break;
    }
}

void procesar_opcion_jugador(int opcion, Mapa * mapa, Jugador * jugador,bool recolecto){

    switch (opcion)
    {
    case CONSTRUIR_EDIFICIO:
            cout << LGREEN << "\n\t SECCION : CONSTRUIR EDIFICIO \n" << endl;
            mapa -> construir_edificio_nombre(jugador);
        break;

    case LISTAR_EDIFICIOS_CONSTRUIDOS:
            cout << LGREEN << "\n\t SECCION : LISTAR EDIFICIOS CONSTRUIDOS \n" << endl;
            mapa -> listar_edificios_construidos(jugador);
        break;

    case DEMOLER_EDIFICIO:
            cout << LGREEN << "\n\t SECCION : DEMOLER EDIFICIO \n" << endl;
            mapa -> demoler_edificio(jugador);
        break;

    case ATACAR_EDIFICIO:
            cout << LGREEN << "\n\t SECCION : DEMOLER EDIFICIO \n" << endl;
            mapa -> atacar_edificios(jugador);
        break;

    case REPARAR_EDIFICIO:
            cout << LGREEN << "\n\t SECCION : REPARAR EDIFICIO \n" << endl;
            mapa -> reparar_edificios(jugador);
        break;

    case COMPRAR_BOMBAS:
            cout << LGREEN << "\n\t SECCION : COMPRAR BOMBAS \n" << endl;
            mapa -> comprar_bombas(jugador);
        break;

    case CONSULTAR_COORDENADA:
            cout << LGREEN << "\n\t SECCION : CONSULTAR COORDENADA \n" << endl;
            mapa -> consultar_coordenada();
        break;

    case MOSTRAR_INVENTARIO:
            cout << LGREEN << "\n\t SECCION : MOSTRAR INVENTARIO \n" << endl;
            mapa -> mostrar_inv(jugador);
        break;

    case MOSTRAR_OBJETIVOS:
            cout << LGREEN << "\n\t SECCION : MOSTRAR OBJETIVOS \n" << endl;
            mapa -> mostrar_objetivos_jugadores(jugador);
        break;

    case RECOLECTAR_RECURSOS:
            cout << LGREEN << "\n\t SECCION : RECOLECTAR RECURSOS \n" << endl;
            if (!recolecto){
                    jugador->sumar_materiales_recolectados();}
            else{cout << "\nUsted ya recolecto los materiales en este turno.\n" << endl;}
        break;

    case MOVERSE:
            cout << LGREEN << "\n\t SECCION : MOVERSE \n" << WHITE << endl;
            mapa -> moverse(jugador);
        break;

    case FINALIZAR_TURNO:
            jugador->sumar_energia(20);
            cout << "\n\tSu turno ha finalizado.\n" << endl;
        break;
    
    case GUARDAR_SALIR:
            cout << "Guardar y Salir" << endl;
        break;
    }
}

void empezar_partida(Mapa * mapa, Jugador * j1, Jugador * j2){
    int fila1, columna1, fila2, columna2, opcion_jugador;
    cout << "\n\t ### SECCION PARA INGRESAR JUGADORES Y SUS COORDENADAS ###" << endl;
    cout << "\n Ingrese el jugador que desea ser ( opciones : 1 o 2 ) -> ";
    cin >> opcion_jugador;
    cout << "\n INGRESEN JUGADORES SUS POSICIONES DONDE INICIARAN LA PARTIDA . " << endl;
    cout << "\n Jugador 1 : " << endl;
    mapa -> validar_coordenada(fila1, columna1);
    cout << "\n Jugador 2 : " << endl;
    mapa -> validar_coordenada(fila2, columna2);

    while (fila1 == fila2 && columna1 == columna2){
        cout << "Error: No podes poner al jugador 2 en las mismas coordenadas que el jugador 1" << endl;
        mapa -> validar_coordenada(fila2, columna2);
    }

    j1 -> vaciar_inventario();
    j2 -> vaciar_inventario();
    mapa -> insertar_jugador_mapa(j1 -> obtener_id(),j1,j2, fila1, columna1);
    mapa -> insertar_jugador_mapa(j2 -> obtener_id(),j1,j2, fila2, columna2);
    partida(mapa, j1 , j2);
}

void partida(Mapa * mapa, Jugador * j1, Jugador * j2){

    int opcion;
    int turno = 1;
    randomizador_de_turnos(j1,j2);

    do {
        bool recolecto = false;
        verificar_lluvia_de_materiales(turno, mapa);

        Jugador * jugador = verificar_turno_jugador(turno, j1, j2);

        cout << ORANGE << "\n\t .: Es el turno del jugador : "<< jugador ->dar_numero() << " :. \n" <<endl;

        mapa->almacenar_recursos_producidos(jugador);

        do{
            mostrar_menu_partida();
            opcion = elegir_opcion();
            procesar_opcion_jugador(opcion, mapa, jugador,recolecto);
            if (opcion == RECOLECTAR_RECURSOS){
                recolecto = true;
            }
            //if(mapa -> ganar_partida(jugador))
            //{
            //    mensaje_ganador(jugador);
            //    opcion = GUARDAR_SALIR;
            //}
        }
        while(opcion != FINALIZAR_TURNO && opcion != GUARDAR_SALIR );
        
        turno++;
    }
    while ( opcion != GUARDAR_SALIR );
}

void selector_de_menu(Mapa * mapa, Jugador * j1, Jugador * j2){

    int opcion;
    if (mapa -> verificar_partida_empezada()){
        
        cout << CYAN << "\n ¡ BIENVENIDOS DE VUELTA A ANDYPOLIS ! \n" << endl;
        partida(mapa, j1, j2);

    }

    else{
    cout << CYAN << "\n ¡ BIENVENIDOS A ANDYPOLIS ! \n" << endl;
        do {
            
            mostrar_menu_principal();
            opcion = elegir_opcion();
            procesar_opcion_principal(opcion, mapa, j1, j2);

        }while ( opcion != P_GUARDAR_SALIR );
    }
}

void verificar_lluvia_de_materiales(int turno, Mapa * mapa){
    if (turno % 2 == 1){
        mapa -> lluvia_recursos();
    }
}

void randomizador_de_turnos(Jugador * j1, Jugador * j2){  
    srand( (unsigned)time(0) );
    int jugador_que_empieza = rand() % 2 + 1;

    if (jugador_que_empieza == 1){
        j1 -> establecer_turno(JUGADOR_1);
        j2 -> establecer_turno(JUGADOR_2);
    }
    else{
        j1 -> establecer_turno(JUGADOR_2);
        j2 -> establecer_turno(JUGADOR_1);
    }
}

Jugador * verificar_turno_jugador(int turno, Jugador * j1, Jugador * j2){
    if (turno % 2 == j1 -> obtener_turno() % 2)
        return j1;
    else
        return j2;
}

void mensaje_ganador(Jugador * jugador)
{
    if (jugador -> dar_numero() == 1)
    {
        cout << "\n¡FELICIDADES JUGADOR 1, HAS GANADO EL JUEGO!\n" << endl;
    }
    else {
        cout << "\n¡FELICIDADES JUGADOR 2, HAS GANADO EL JUEGO!\n" << endl;
    }
}