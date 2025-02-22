#pragma region Librerias y nameSpace
#include <iostream>// Proporciona funciones para entrada y salida estándar (cin, cout, cerr) en la consola.
#include <vector>// Proporciona el contenedor dinámico std::vector para manejar listas de elementos.
#include <string> // Proporciona la clase std::string para manejar cadenas de texto.
#include <fstream>// Proporciona funciones para leer y escribir archivos (ifstream, ofstream).
#include <chrono>// Proporciona utilidades para manejar el tiempo.
#include <sstream>// Proporciona std::stringstream para manipular cadenas de texto como flujos.
#include <stack>// Proporciona el contenedor std::stack para manejar pilas (LIFO).
#include <regex>// Proporciona soporte para expresiones regulares, que se utilizan para validar patrones en cadenas de texto, como fechas y horas.
#include <ctime>// Proporciona funciones para manejar fechas y horas (time_t, struct tm).
using namespace std;// Acorta la utilización de "STD".
#pragma endregion
#pragma region Estructuras y Menus
enum class DiaSemana //Representacion de los dias laborales del profesional.
{ 
                                Lunes, 
                                Martes, 
                                Miercoles, 
                                Jueves, 
                                Viernes, 
                                Sabado, 
                                Domingo 
};
template <typename T>
bool existeId(const vector<T>& lista, int id) {
    for (const auto& objeto : lista) {
        if (objeto.getId() == id) {
            return true;
        }
    }
    return false;
}//Se ingresa el id a buscar y la lista. Recorre la lista y si encuentra un id igual al ingresado devuelve TRUE, sino lo encuentra devuelve FALSE.
int obtenerEnteroValido() {
    int valor;
    while (!(cin >> valor)) { // Mientras la entrada no sea un número
        cin.clear(); // Limpiar el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
        cout << "Entrada no valida. Por favor, ingrese un numero: ";
    }
    return valor;
}//Verifica que el valor ingresado sea un numero entero.
int mostrarMenu(void (*menu)()) {
    menu();
    int opcion;
    cout << "Ingrese una opcion: ";
    return obtenerEnteroValido();
}// Función para mostrar un menú y obtener la opción seleccionada
void menuPrincipal() {
    cout << "\n=== Menu Principal ===\n";
    cout << "1. Administradores\n";
    cout << "2. Profesionales\n";
    cout << "3. Pacientes\n";
    cout << "4. Turnos\n";
    cout << "0. Salir\n";
}
void menuAdministradores() {
    cout << "\n=== Menu Administradores ===\n";
    cout << "1. Crear administrador\n";
    cout << "2. Modificar administrador\n";
    cout << "3. Eliminar administrador\n";
    cout << "4. Mostrar administradores\n";
    cout << "0. Volver\n";
}
void menuProfesionales() {
    cout << "\n=== Menu Profesionales ===\n";
    cout << "1. Crear profesional\n";
    cout << "2. Modificar profesional\n";
    cout << "3. Eliminar profesional\n";
    cout << "4. Mostrar profesionales\n";
    cout << "0. Volver\n";
}
void menuPacientes() {
    cout << "\n=== Menu Pacientes ===\n";
    cout << "1. Crear paciente\n";
    cout << "2. Modificar paciente\n";
    cout << "3. Eliminar paciente\n";
    cout << "4. Mostrar pacientes\n";
    cout << "0. Volver\n";
}
void menuTurnos() {
    cout << "\n=== Menu Turnos ===\n";
    cout << "1. Crear turno\n";
    cout << "2. Modificar turno\n";
    cout << "3. Eliminar turno\n";
    cout << "4. Mostrar turnos\n";
    cout << "0. Volver\n";
}
#pragma endregion
#pragma region Clases
#pragma region Persona::
    class Persona //Representacion general de las personas involucradas en el sistema
    {
    protected:
        int                     p_id;
        string                  p_nombre, 
                                p_apellido;
    public:
        Persona                (int id, 
                                string nombre, 
                                string apellido)

            :                   p_id       (id), 
                                p_nombre   (nombre),
                                p_apellido (apellido)
        {}// Constructor de la clase.
        ~Persona(){}// Destructor de la clase.
        virtual void mostrarDatos() const {
            cout << "ID: " 
                 << p_id 
                 << "\nNombre: " 
                 << p_nombre 
                 << "\nApellido: " 
                 << p_apellido << endl;
        }// Metodo sobrescribible para el resto de clase.
        template <typename T>
        static int generarId(const vector<T>& lista) {
            if (lista.empty()) {
                return 1; // Si la lista está vacía, empezar desde 1
            }
            int maxId = 0;
            for (const auto& objeto : lista) {
                if (objeto.getId() > maxId) {
                    maxId = objeto.getId();
                }
            }
            return maxId + 1; // Devolver el mayor ID encontrado + 1
        }// Metodo que toma una lista como parametro. Al crear un nuevo objeto en la lista, genera 
        //  un id mayor al id mas grande de los objetos de la lista o, si la lista esta vacia, 
        //  crea un objeto con id = 1.
        
        // Getters
        int getId() const { return p_id; }
        string getNombre() const { return p_nombre; }
        string getApellido() const { return p_apellido; }
        // Setters
        void setNombre(const string& _nombre) { p_nombre = _nombre; }
        void setApellido(const string& _apellido) { p_apellido = _apellido; }
    };
#pragma endregion
#pragma region Administrador
    class Administrador : public Persona //Representacion del administrador (heredara de persona) 
    {
        //Propiedades
        string                  p_usuario, 
                                p_contrasenia;

    public:
        //Constructor
        Administrador          (int    id,
                                string nombre, 
                                string apellido, 
                                string usuario, 
                                string contrasenia)

            : Persona           (id, 
                                nombre, 
                                apellido), 
              p_usuario         (usuario), 
              p_contrasenia     (contrasenia) 
        {}
        string getUsuario() const { return p_usuario; }
        string getContrasenia() const { return p_contrasenia; }
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_nombre << "," << p_apellido << "," << p_usuario << "," << p_contrasenia;
            return ss.str();
        } //Metodo que toma todos los datos de una instancia y genera un ss de texto para ingresar en el archivo con formato CSV.
        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "Usuario: " 
                 << p_usuario 
                 << "\n";
        }// Muestra los datos del administrador.
        static Administrador crearAdministrador(const vector<Administrador>& lista) {
            string nombre, apellido, usuario, contrasenia;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese usuario: "; cin >> usuario;
            cout << "Ingrese contrasenia: "; cin >> contrasenia;
            int nuevoId = Persona::generarId(lista); // Generar el ID basado en la lista
            return Administrador(nuevoId, nombre, apellido, usuario, contrasenia);
        } // Crea un nuevo administrador pidiendo los datos al usuraio.
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo nombre: "; cin >> p_nombre;
            cout << "Ingrese nuevo apellido: "; cin >> p_apellido;
            cout << "Ingrese nuevo usuario: "; cin >> p_usuario;
            cout << "Ingrese nueva contrasenia: "; cin >> p_contrasenia;
        } // Modifica los datos del administrador desde la consola.
        void fromCsv(const string& linea) {
            stringstream ss(linea);
            string id, nombre, apellido, usuario, contrasenia;
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, usuario, ',');
            getline(ss, contrasenia, ',');
            this->p_id = stoi(id);
            this->p_nombre = nombre;
            this->p_apellido = apellido;
            this->p_usuario = usuario;
            this->p_contrasenia = contrasenia;
        }//Metodo que toma todos los datos de un ss y genera una instancia para ingresar en la lista.
    };
#pragma endregion
#pragma region Profesional
    class Profesional : public Persona //Representacion del profesional (heredara de persona)
    {
        string                  p_dni,
                                p_especialidad,
                                p_telefono,
                                p_email;
        vector <DiaSemana>      p_diaLaboral;// Días laborales del profesional.

    public:
        Profesional            (int    id,
                                string nombre, 
                                string apellido, 
                                string dni, 
                                string especialidad, 
                                string telefono,
                                string email, 
                                vector<DiaSemana> diaLaboral)

            : Persona          (id, 
                                nombre, 
                                apellido), 
              p_dni            (dni), 
              p_especialidad   (especialidad), 
              p_telefono       (telefono), 
              p_email          (email), 
              p_diaLaboral     (diaLaboral) 
        {

        }// Constructor.

        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "DNI: "
                << p_dni
                << "\nEspecialidad: "
                << p_especialidad
                << "\nTelefono: "
                << p_telefono
                << "\nEmail: "
                << p_email
                << "\nDias Laborales: ";

            const vector<string> dias = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sábado", "Domingo" };
            for (size_t i = 0; i < p_diaLaboral.size(); ++i) {
                cout << static_cast<int>(p_diaLaboral[i]) << " - " << dias[static_cast<int>(p_diaLaboral[i])];
                if (i < p_diaLaboral.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "\n";
        }// Muestra los datos del profesional.
        const vector<DiaSemana>& getDiasLaborales() const {
            return p_diaLaboral;
        }// Devuelve los días laborales del profesional.
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_nombre << "," << p_apellido << ","
                << p_dni << "," << p_especialidad << "," << p_telefono << "," << p_email << ",";
            for (size_t i = 0; i < p_diaLaboral.size(); ++i) {
                ss << static_cast<int>(p_diaLaboral[i]);
                if (i < p_diaLaboral.size() - 1) {
                    ss << ";";
                }
            }
            return ss.str();
        }// Convierte los datos del profesional a formato CSV.
        static Profesional crearProfesional(const vector<Profesional>& lista) {
            string nombre, apellido, dni, especialidad, telefono, email;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese DNI: "; cin >> dni;
            cout << "Ingrese especialidad: "; cin >> especialidad;
            cout << "Ingrese telefono: "; cin >> telefono;
            cout << "Ingrese email: "; cin >> email;
            // Solicitar días laborales
            vector<DiaSemana> diasLaborales;
            int cantidadDias;
            cout << "¿Cuantos dias laborales tiene el profesional? "; cin >> cantidadDias;
            for (int i = 0; i < cantidadDias; ++i) {
                int dia;
                cout << "Ingrese el día " << (i + 1) << " (0 = Lunes, 1 = Martes, ..., 6 = Domingo): ";
                cin >> dia;
                // Validar que el día esté en el rango correcto
                if (dia >= 0 && dia <= 6) {
                    diasLaborales.push_back(static_cast<DiaSemana>(dia));
                }
                else {
                    cout << "Día no válido. Debe ser un número entre 0 y 6.\n";
                    --i; // Repetir la entrada para este día
                }
            }
            int nuevoId = Persona::generarId(lista); // Generar el ID basado en la lista
            return Profesional(nuevoId, nombre, apellido, dni, especialidad, telefono, email, diasLaborales);
        }// Crea un nuevo profesional.
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo nombre: "; cin >> p_nombre;
            cout << "Ingrese nuevo apellido: "; cin >> p_apellido;
            cout << "Ingrese nuevo DNI: "; cin >> p_dni;
            cout << "Ingrese nueva especialidad: "; cin >> p_especialidad;
            cout << "Ingrese nuevo telefono: "; cin >> p_telefono;
            cout << "Ingrese nuevo email: "; cin >> p_email;
            // Modificar días laborales
            p_diaLaboral.clear(); // Limpiar días laborales existentes
            int cantidadDias;
            cout << "¿Cuantos dias laborales tiene el profesional? "; cin >> cantidadDias;
            for (int i = 0; i < cantidadDias; ++i) {
                int dia;
                cout << "Ingrese el día " << (i + 1) << " (0 = Lunes, 1 = Martes, ..., 6 = Domingo): ";
                cin >> dia;
                // Validar que el día esté en el rango correcto
                if (dia >= 0 && dia <= 6) {
                    p_diaLaboral.push_back(static_cast<DiaSemana>(dia));
                }
                else {
                    cout << "Día no válido. Debe ser un número entre 0 y 6.\n";
                    --i; // Repetir la entrada para este día
                }
            }
        }// Modifica los datos del profesional desde la consola.
        void fromCsv(const string& csvLine) {
            stringstream ss(csvLine);
            string id, nombre, apellido, dni, especialidad, telefono, email, diasLaboralesStr;
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, apellido, ',');
            getline(ss, dni, ',');
            getline(ss, especialidad, ',');
            getline(ss, telefono, ',');
            getline(ss, email, ',');
            getline(ss, diasLaboralesStr, ',');
            this->p_id = stoi(id);
            this->p_nombre = nombre;
            this->p_apellido = apellido;
            this->p_dni = dni;
            this->p_especialidad = especialidad;
            this->p_telefono = telefono;
            this->p_email = email;
            // Convertir diasLaboralesStr a vector<DiaSemana>
            this->p_diaLaboral.clear();
            stringstream diasStream(diasLaboralesStr);
            string dia;
            while (getline(diasStream, dia, ';')) {
                int diaInt = stoi(dia);
                if (diaInt >= 0 && diaInt <= 6) { // Validar que sea un día válido
                    this->p_diaLaboral.push_back(static_cast<DiaSemana>(diaInt));
                }
            }
        }// Carga los datos del profesional desde una línea CSV.
    };
#pragma endregion
#pragma region Paciente
    class Paciente : public Persona //Representacion del paciente (heredara de persona)
    {
        string                  p_dni,
                                p_telefono,
                                p_email, 
                                p_fechaNacimiento;

    public:
        Paciente               (int    id,
                                string nombre, 
                                string apellido, 
                                string dni, 
                                string telefono, 
                                string email, 
                                string fechaNacimiento)

            : Persona          (id, 
                                nombre, 
                                apellido), 
              p_dni            (dni), 
              p_telefono       (telefono), 
              p_email          (email), 
              p_fechaNacimiento(fechaNacimiento) 
        {}// Constructor.
        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "DNI: " 
                 << p_dni 
                 << "\nTelefono: " 
                 << p_telefono << "\nEmail: " 
                 << p_email << "\nFecha de Nacimiento: " 
                 << p_fechaNacimiento << "\n";
        }// Muestra los datos del paciente.
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_nombre << "," << p_apellido << ","
                << p_dni << "," << p_telefono << "," << p_email << "," << p_fechaNacimiento;
            return ss.str();
        }// Método toCsv: Convierte los datos del paciente a formato CSV para su almacenamiento.
        static Paciente crearPaciente(const vector<Paciente>& lista) {
            string nombre, apellido, dni, telefono, email, fechaNacimiento;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese DNI: "; cin >> dni;
            cout << "Ingrese telefono: "; cin >> telefono;
            cout << "Ingrese email: "; cin >> email;
            cout << "Ingrese fecha de nacimiento (DD/MM/YEAR): "; cin >> fechaNacimiento;
            int nuevoId = Persona::generarId(lista); // Generar el ID basado en la lista
            return Paciente(nuevoId, nombre, apellido, dni, telefono, email, fechaNacimiento);
        } // Método estático crearPaciente: Crea un nuevo paciente solicitando los datos por consola.
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo nombre: "; cin >> p_nombre;
            cout << "Ingrese nuevo apellido: "; cin >> p_apellido;
            cout << "Ingrese nuevo DNI: "; cin >> p_dni;
            cout << "Ingrese nuevo telefono: "; cin >> p_telefono;
            cout << "Ingrese nuevo email: "; cin >> p_email;
            cout << "Ingrese nueva fecha de nacimiento (DD/MM/YEAR): "; cin >> p_fechaNacimiento;
        } // Método modificarDesdeConsola: Permite modificar los datos del paciente desde la consola.
        void fromCsv(const string& csvLine) {
            stringstream ss(csvLine);
            char delim;
            ss >> p_id >> delim;
            getline(ss, p_nombre, ',');
            getline(ss, p_apellido, ',');
            getline(ss, p_dni, ',');
            getline(ss, p_telefono, ',');
            getline(ss, p_email, ',');
            getline(ss, p_fechaNacimiento, ',');
        }// Método fromCsv: Carga los datos de un paciente desde una línea en formato CSV.
    };
#pragma endregion
#pragma region Turnos
    // Clase Turno: Representa un turno en el sistema.
    class Turno {
        int p_id, p_idAdministrador, p_idProfesional, p_idPaciente;
        string p_fechaTurno, p_horaTurno, p_estado;
    public:
        Turno(int id, int idAdministrador, int idProfesional, int idPaciente,
            const string& fechaTurno, const string& horaTurno, const string& estado)
            : p_id(id), p_idAdministrador(idAdministrador), p_idProfesional(idProfesional),
            p_idPaciente(idPaciente), p_fechaTurno(fechaTurno), p_horaTurno(horaTurno),
            p_estado(estado) {
        }// Constructor: Inicializa un objeto Turno con los datos proporcionados.
        // Métodos set: Permiten modificar los atributos del turno.
        void setId(int id) {
            p_id = id;
        }
        void setIdAdministrador(int idAdministrador) {
            p_idAdministrador = idAdministrador;
        }
        void setIdProfesional(int idProfesional) {
            p_idProfesional = idProfesional;
        }
        void setIdPaciente(int idPaciente) {
            p_idPaciente = idPaciente;
        }
        void setFechaTurno(const string& fechaTurno) {
            p_fechaTurno = fechaTurno;
        }
        void setHoraTurno(const string& horaTurno) {
            p_horaTurno = horaTurno;
        }
        void setEstado(const string& estado) {
            p_estado = estado;
        }
        void mostrarDatos() const {
            cout << "ID Turno: " << p_id
                << "\nID Administrador: " << p_idAdministrador
                << "\nID Profesional: " << p_idProfesional
                << "\nID Paciente: " << p_idPaciente
                << "\nFecha: " << p_fechaTurno
                << "\nHora: " << p_horaTurno
                << "\nEstado: " << p_estado << "\n";
        }// Método mostrarDatos: Muestra los datos del turno.
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_idAdministrador << "," << p_idProfesional << ","
                << p_idPaciente << "," << p_fechaTurno << "," << p_horaTurno << "," << p_estado;
            return ss.str();
        }// Método toCsv: Convierte los datos del turno a formato CSV para su almacenamiento.
        int getId() const { return p_id; } // Método getId: Devuelve el ID del turno.
        static int generarId(const vector<Turno>& lista) {
            if (lista.empty()) {
                return 1; // Si la lista está vacía, empezar desde 1
            }
            int maxId = 0;
            for (const auto& objeto : lista) {
                if (objeto.getId() > maxId) {
                    maxId = objeto.getId();
                }
            }
            return maxId + 1; // Devolver el mayor ID encontrado + 1
        }// Método estático generarId: Genera un nuevo ID para un turno basado en la lista de turnos existentes.
        static Turno crearTurno(const vector<Turno>& listaTurnos,
            const vector<Administrador>& listaAdministradores,
            const vector<Profesional>& listaProfesionales,
            const vector<Paciente>& listaPacientes) {
            int idAdministrador, idProfesional, idPaciente;
            string fechaTurno, horaTurno, estado;
            // Mostrar lista de administradores
            cout << "\n=== Lista de Administradores ===\n";
            for (const auto& admin : listaAdministradores) {
                admin.mostrarDatos();
                cout << "-------------\n";
            }
            // Solicitar ID del administrador y validar que exista
            do {
                cout << "Ingrese ID del administrador: "; cin >> idAdministrador;
                if (!existeId(listaAdministradores, idAdministrador)) {
                    cout << "Error: ID de administrador no válido.\n";
                }
            } while (!existeId(listaAdministradores, idAdministrador));
            // Solicitar fecha del turno y validar que no sea inferior a la fecha actual
            do {
                cout << "Ingrese fecha del turno (DD-MM-YYYY): "; cin >> fechaTurno;
                if (!validarFecha(fechaTurno)) {
                    cout << "Error: Formato de fecha no válido.\n";
                }
                else if (fechaEsInferiorActual(fechaTurno)) {
                    cout << "Error: La fecha no puede ser inferior a la fecha actual.\n";
                }
            } while (!validarFecha(fechaTurno) || fechaEsInferiorActual(fechaTurno));
            // Mostrar lista de profesionales disponibles en la fecha
            cout << "\n=== Lista de Profesionales Disponibles ===\n";
            for (const auto& profesional : listaProfesionales) {
                if (profesionalDisponible(profesional, fechaTurno)) {
                    profesional.mostrarDatos();
                    cout << "-------------\n";
                }
            }
            // Solicitar ID del profesional y validar que esté disponible en la fecha
            do {
                cout << "Ingrese ID del profesional: "; cin >> idProfesional;
                if (!existeId(listaProfesionales, idProfesional)) {
                    cout << "Error: ID de profesional no válido.\n";
                }
                else if (!profesionalDisponible(listaProfesionales, idProfesional, fechaTurno)) {
                    cout << "Error: El profesional no está disponible en la fecha seleccionada.\n";
                }
            } while (!existeId(listaProfesionales, idProfesional) ||
                !profesionalDisponible(listaProfesionales, idProfesional, fechaTurno));
            // Mostrar lista de pacientes
            cout << "\n=== Lista de Pacientes ===\n";
            for (const auto& paciente : listaPacientes) {
                paciente.mostrarDatos();
                cout << "-------------\n";
            }
            // Solicitar ID del paciente y validar que exista
            do {
                cout << "Ingrese ID del paciente: "; cin >> idPaciente;
                if (!existeId(listaPacientes, idPaciente)) {
                    cout << "Error: ID de paciente no válido.\n";
                }
            } while (!existeId(listaPacientes, idPaciente));
            // Solicitar hora del turno y validar que no sea inferior a la hora actual
            do {
                cout << "Ingrese hora del turno (HH:MM): "; cin >> horaTurno;
                if (!validarHora(horaTurno)) {
                    cout << "Error: Formato de hora no válido.\n";
                }
                else if (fechaTurno == obtenerFechaActual() && horaEsInferiorActual(horaTurno)) {
                    cout << "Error: La hora no puede ser inferior a la hora actual.\n";
                }
            } while (!validarHora(horaTurno) || (fechaTurno == obtenerFechaActual() && horaEsInferiorActual(horaTurno)));
            // Validar que no haya turnos superpuestos
            if (existeTurnoSuperpuesto(listaTurnos, fechaTurno, horaTurno)) {
                cout << "Error: Ya existe un turno en la misma fecha y hora.\n";
                return Turno(0, 0, 0, 0, "", "", ""); // Retornar un turno vacío
            }
            cout << "Ingrese estado del turno: "; cin >> estado;
            int nuevoId = generarId(listaTurnos); // Generar el ID basado en la lista
            return Turno(nuevoId, idAdministrador, idProfesional, idPaciente, fechaTurno, horaTurno, estado);
        }// Método estático crearTurno: Crea un nuevo turno solicitando los datos por consola.
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo ID del administrador: "; cin >> p_idAdministrador;
            cout << "Ingrese nuevo ID del profesional: "; cin >> p_idProfesional;
            cout << "Ingrese nuevo ID del paciente: "; cin >> p_idPaciente;
            // Validar fecha en formato DD-MM-YYYY
            do {
                cout << "Ingrese nueva fecha del turno (DD-MM-YYYY): "; cin >> p_fechaTurno;
                if (!validarFecha(p_fechaTurno)) {
                    cout << "Error: Formato de fecha no válido.\n";
                }
            } while (!validarFecha(p_fechaTurno));
            // Validar hora en formato HH:MM
            do {
                cout << "Ingrese nueva hora del turno (HH:MM): "; cin >> p_horaTurno;
                if (!validarHora(p_horaTurno)) {
                    cout << "Error: Formato de hora no válido.\n";
                }
            } while (!validarHora(p_horaTurno));
            cout << "Ingrese nuevo estado del turno: "; cin >> p_estado;
        }// Método modificarDesdeConsola: Permite modificar los datos del turno desde la consola.
        void fromCsv(const string& csvLine) {
            stringstream ss(csvLine);
            char delim;
            ss >> p_id >> delim;
            ss >> p_idAdministrador >> delim;
            ss >> p_idProfesional >> delim;
            ss >> p_idPaciente >> delim;
            getline(ss, p_fechaTurno, ',');
            getline(ss, p_horaTurno, ',');
            getline(ss, p_estado, ',');
        }// Método fromCsv: Carga los datos de un turno desde una línea en formato CSV.
        // Método para validar el formato de la fecha (DD-MM-YYYY)
        static bool validarFecha(const string& fecha) {
            regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
            return regex_match(fecha, formatoFecha);
        }
        // Método para validar el formato de la hora (HH:MM)
        static bool validarHora(const string& hora) {
            regex formatoHora(R"(\d{2}:\d{2})");
            return regex_match(hora, formatoHora);
        }
        // Método para verificar si hay turnos superpuestos
        static bool existeTurnoSuperpuesto(const vector<Turno>& listaTurnos, const string& fecha, const string& hora) {
            for (const auto& turno : listaTurnos) {
                if (turno.p_fechaTurno == fecha && turno.p_horaTurno == hora) {
                    return true; // Ya existe un turno en la misma fecha y hora
                }
            }
            return false; // No hay turnos superpuestos
        }
        // Método genérico para verificar si un ID existe en una lista
        template <typename T>
        static bool existeId(const vector<T>& lista, int id) {
            for (const auto& objeto : lista) {
                if (objeto.getId() == id) {
                    return true;
                }
            }
            return false;
        }
        static int obtenerDiaSemana(const string& fecha) {
            int dia, mes, anio;
            char sep;
            stringstream ss(fecha);
            ss >> dia >> sep >> mes >> sep >> anio;
            // Ajustar mes y año para el cálculo
            if (mes < 3) {
                mes += 12;
                anio--;
            }
            // Cálculo del día de la semana usando el algoritmo de Zeller
            int k = anio % 100;
            int j = anio / 100;
            int diaSemana = (dia + 13 * (mes + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
            // Ajustar el resultado para que 0 = Domingo, 1 = Lunes, ..., 6 = Sábado
            return (diaSemana + 5) % 7;
        }// Metodo para saber que dia de la semana es (lunes, martes, etc)
        // Método para verificar si un profesional está disponible en una fecha
        static bool profesionalDisponible(const Profesional& profesional, const string& fecha) {
            int diaSemana = obtenerDiaSemana(fecha);
            for (const auto& dia : profesional.getDiasLaborales()) {
                if (static_cast<int>(dia) == diaSemana) {
                    return true; // El profesional trabaja en ese día
                }
            }
            return false; // El profesional no trabaja en ese día
        }
        // Método para verificar si un profesional está disponible en una fecha (sobrecarga para ID)
        static bool profesionalDisponible(const vector<Profesional>& listaProfesionales, int idProfesional, const string& fecha) {
            for (const auto& profesional : listaProfesionales) {
                if (profesional.getId() == idProfesional) {
                    return profesionalDisponible(profesional, fecha);
                }
            }
            return false; // Profesional no encontrado
        }
        // Método para verificar si una fecha es inferior a la fecha actual
        static bool fechaEsInferiorActual(const string& fecha) {
            string fechaActual = obtenerFechaActual();
            return fecha < fechaActual;
        }
        // Método para obtener la fecha actual en formato DD-MM-YYYY
        static string obtenerFechaActual() {
            auto now = chrono::system_clock::now();
            time_t now_time = chrono::system_clock::to_time_t(now);
            struct tm tm;
#ifdef _WIN32
            localtime_s(&tm, &now_time); // Versión segura en Windows
#endif
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tm);
            return string(buffer);
        }
        static string obtenerHoraActual() {
            auto now = chrono::system_clock::now();
            time_t now_time = chrono::system_clock::to_time_t(now);
            struct tm tm;
#ifdef _WIN32
            localtime_s(&tm, &now_time);
#endif
            char buffer[6];
            strftime(buffer, sizeof(buffer), "%H:%M", &tm);
            return string(buffer);
        }
        // Método para verificar si una hora es inferior a la hora actual
        static bool horaEsInferiorActual(const string& hora) {
            string horaActual = obtenerHoraActual();
            return hora < horaActual;
        }
    };
#pragma endregion
#pragma region Gestor
    class gestorCsvArchivos // Gestor de archivos 
    {
        const string archivoAdministrador = "Administrador.txt";
        const string archivoProfesional = "Profesional.txt";
        const string archivoPaciente = "Paciente.txt";
        const string archivoTurno = "Turnos.txt";
        //archivos de escritura y lectura.
        fstream A_Administradores;
        fstream A_Profesionales;
        fstream A_Pacientes;
        fstream A_Turnos;
        Administrador administradorActual; // Almacena el administrador actual
    public:
        gestorCsvArchivos() : administradorActual(0, "", "", "", "")
        {
            cout << "\nVerificando integridad de los archivos: \n\n";
            VerificacionDeArchivo(archivoAdministrador,A_Administradores);
            VerificacionDeArchivo(archivoProfesional,A_Profesionales);
            VerificacionDeArchivo(archivoPaciente,A_Pacientes);
            VerificacionDeArchivo(archivoTurno, A_Turnos);
        }// Constructor: Verifica la integridad de los archivos al iniciar.
        template <typename T>
        void ConvertirInformacionDeListaYGuardarlaEnElArchivo(const string& nombreArchivo, const vector<T>& lista) {
            ofstream file(nombreArchivo);
            if (!file.is_open()) {
                cerr << "Error al abrir el archivo para escritura." << endl;
                return;
            }
            for (const auto& objeto : lista) {
                file << objeto.toCsv() << "\n";  // Llamamos al método toCsv() del objeto
            }
            file.close();
        }// Método ConvertirInformacionDeListaYGuardarlaEnElArchivo: Guarda una lista de objetos en un archivo CSV.

        // Métodos para cargar datos desde archivos CSV.
        vector<Administrador> cargarAdministradoresDesdeArchivo() {
            vector<Administrador> administradores;
            ifstream archivo(archivoAdministrador);
            if (!archivo.is_open()) {
                cerr << "Error al abrir el archivo: " << archivoAdministrador << "\n";
                return administradores;
            }
            string linea;
            while (getline(archivo, linea)) {
                Administrador admin(0, "", "", "", ""); // Crear un objeto temporal
                admin.fromCsv(linea); // Cargar datos desde la línea CSV
                administradores.push_back(admin); // Agregar a la lista
            }
            archivo.close();
            return administradores;
        }
        vector<Profesional> cargarProfesionalesDesdeArchivo() {
            vector<Profesional> profesionales;
            ifstream archivo(archivoProfesional);
            if (!archivo.is_open()) {
                cerr << "Error al abrir el archivo: " << archivoProfesional << "\n";
                return profesionales;
            }
            string linea;
            while (getline(archivo, linea)) {
                Profesional profesional(0, "", "", "", "", "", "", {}); // Crear un objeto temporal
                profesional.fromCsv(linea); // Cargar datos desde la línea CSV
                profesionales.push_back(profesional); // Agregar a la lista
            }
            archivo.close();
            return profesionales;
        }
        vector<Paciente> cargarPacientesDesdeArchivo() {
            vector<Paciente> pacientes;
            ifstream archivo(archivoPaciente);
            if (!archivo.is_open()) {
                cerr << "Error al abrir el archivo: " << archivoPaciente << "\n";
                return pacientes;
            }
            string linea;
            while (getline(archivo, linea)) {
                Paciente paciente(0, "", "", "", "", "", ""); // Crear un objeto temporal
                paciente.fromCsv(linea); // Cargar datos desde la línea CSV
                pacientes.push_back(paciente); // Agregar a la lista
            }
            archivo.close();
            return pacientes;
        }
        vector<Turno> cargarTurnosDesdeArchivo() {
            vector<Turno> turnos;
            ifstream archivo(archivoTurno);
            if (!archivo.is_open()) {
                cerr << "Error al abrir el archivo: " << archivoTurno << "\n";
                return turnos;
            }
            string linea;
            while (getline(archivo, linea)) {
                Turno turno(0, 0, 0, 0, "", "", ""); // Crear un objeto temporal
                turno.fromCsv(linea); // Cargar datos desde la línea CSV
                turnos.push_back(turno); // Agregar a la lista
            }
            archivo.close();
            return turnos;
        }
        // Método para realizar el login
        bool login(const vector<Administrador>& listaAdministradores) {
            string usuario, contrasenia;
            cout << "=== Login ===\n";
            cout << "Ingrese su usuario: ";
            cin >> usuario;
            cout << "Ingrese su contrasenia: ";
            cin >> contrasenia;

            // Buscar el administrador con las credenciales ingresadas
            for (const auto& admin : listaAdministradores) {
                if (admin.getUsuario() == usuario && admin.getContrasenia() == contrasenia) {
                    cout << "Login exitoso. Bienvenido, " << admin.getNombre() << "!\n";
                    administradorActual = admin; // Almacenar el administrador actual
                    return true; // Credenciales válidas
                }
            }

            // Si no se encontró un administrador con las credenciales ingresadas
            cout << "Error: Usuario o contrasenia incorrectos.\n";
            return false; // Credenciales inválidas
        }
        bool solicitarContrasenia() {
            string contrasenia;
            cout << "Ingrese su contrasenia para continuar: ";
            cin >> contrasenia;

            // Verificar la contraseña del administrador actual
            if (administradorActual.getContrasenia() == contrasenia) {
                return true; // Contraseña correcta
            }
            else {
                cout << "Error: Contrasenia incorrecta.\n";
                return false; // Contraseña incorrecta
            }
        }// Método solicitarContrasenia: Solicita la contraseña del administrador actual.
        // Método para mostrar administradores
        static void mostrarAdministradores(const vector<Administrador>& listaAdministradores) {
            cout << "Lista de Administradores:\n";
            for (const auto& administrador : listaAdministradores) {
                administrador.mostrarDatos();
                cout << "-------------\n";
            }
        }
        // Método para mostrar profesionales
        static void mostrarProfesionales(const vector<Profesional>& listaProfesionales) {
            cout << "Lista de Profesionales:\n";
            for (const auto& profesional : listaProfesionales) {
                profesional.mostrarDatos();
                cout << "-------------\n";
            }
        }
        // Método para mostrar pacientes
        static void mostrarPacientes(const vector<Paciente>& listaPacientes) {
            cout << "Lista de Pacientes:\n";
            for (const auto& paciente : listaPacientes) {
                paciente.mostrarDatos();
                cout << "-------------\n";
            }
        }
        // Método para mostrar turnos
        static void mostrarTurnos(const vector<Turno>& listaTurnos) {
            cout << "Lista de Turnos:\n";
            for (const auto& turno : listaTurnos) {
                turno.mostrarDatos(); 
                cout << "-------------\n";
            }
        }
        template <typename T>
        void mostrarYeliminarPorId(vector<T>& lista, const string& nombreArchivo) {
            // Mostrar la lista de objetos
            cout << "Lista de " << typeid(T).name() << ":\n";
            for (const auto& objeto : lista) {
                objeto.mostrarDatos();
                cout << "-------------\n";
            }
            // Solicitar el ID del objeto a eliminar
            int idEliminar;
            cout << "Ingrese el ID del objeto que desea eliminar: ";
            cin >> idEliminar;
            // Buscar y eliminar el objeto con el ID especificado
            auto it = lista.begin();
            while (it != lista.end()) {
                if (it->getId() == idEliminar) {
                    cout << "Objeto con ID " << idEliminar << " eliminado.\n";
                    it = lista.erase(it); // Eliminar el objeto y actualizar el iterador
                }
                else {
                    ++it; // Avanzar al siguiente objeto
                }
            }
            // Sobrescribir el archivo con la lista actualizada
            ConvertirInformacionDeListaYGuardarlaEnElArchivo(nombreArchivo, lista);
        } // Métodos para eliminar objetos por ID.
        template <typename T>
        void mostrarYmodificarPorId(vector<T>& lista, const string& nombreArchivo) {
            // Mostrar la lista de objetos
            cout << "Lista de " << typeid(T).name() << ":\n";
            for (const auto& objeto : lista) {
                objeto.mostrarDatos();
                cout << "-------------\n";
            }
            // Solicitar el ID del objeto a modificar
            int idModificar;
            cout << "Ingrese el ID del objeto que desea modificar: ";
            cin >> idModificar;
            // Buscar el objeto con el ID especificado
            auto it = lista.begin();
            while (it != lista.end()) {
                if (it->getId() == idModificar) {
                    // Mostrar los datos actuales del objeto
                    cout << "Datos actuales del objeto:\n";
                    it->mostrarDatos();
                    cout << "-------------\n";
                    // Modificar los atributos del objeto
                    cout << "Ingrese los nuevos datos:\n";
                    it->modificarDesdeConsola(); // Modificar el objeto directamente
                    cout << "Objeto con ID " << idModificar << " modificado.\n";
                    break;
                }
                ++it;
            }
            // Sobrescribir el archivo con la lista actualizada
            ConvertirInformacionDeListaYGuardarlaEnElArchivo(nombreArchivo, lista);
        }// Métodos para modificar objetos por ID.
        void mostrarYmodificarTurnoPorId(vector<Turno>& listaTurnos,
                                 const vector<Administrador>& listaAdministradores,
                                 const vector<Profesional>& listaProfesionales,
                                 const vector<Paciente>& listaPacientes,
                                 const string& nombreArchivo) {
            // Mostrar la lista de turnos
            cout << "Lista de Turnos:\n";
            for (const auto& turno : listaTurnos) {
                turno.mostrarDatos();
                cout << "-------------\n";
            }
            // Solicitar el ID del turno a modificar
            int idModificar;
            cout << "Ingrese el ID del turno que desea modificar: ";
            cin >> idModificar;
            // Buscar el turno con el ID especificado
            auto it = listaTurnos.begin();
            while (it != listaTurnos.end()) {
                if (it->getId() == idModificar) {
                    // Mostrar los datos actuales del turno
                    cout << "Datos actuales del turno:\n";
                    it->mostrarDatos();
                    cout << "-------------\n";
                    // Modificar los atributos del turno
                    cout << "Ingrese los nuevos datos:\n";
                    // Mostrar lista de administradores
                    cout << "\n=== Lista de Administradores ===\n";
                    for (const auto& administrador : listaAdministradores) {
                        administrador.mostrarDatos();
                        cout << "-------------\n";
                    }
                    // Solicitar ID del administrador y validar que exista
                    int idAdministrador;
                    do {
                        cout << "Ingrese ID del administrador: ";
                        cin >> idAdministrador;
                        if (!existeId(listaAdministradores, idAdministrador)) {
                            cout << "Error: ID de administrador no válido.\n";
                        }
                    } while (!existeId(listaAdministradores, idAdministrador));
                    // Solicitar fecha del turno y validar que no sea inferior a la fecha actual
                    string fechaTurno;
                    do {
                        cout << "Ingrese fecha del turno (DD-MM-YYYY): ";
                        cin >> fechaTurno;
                        if (!Turno::validarFecha(fechaTurno)) {
                            cout << "Error: Formato de fecha no válido.\n";
                        } else if (Turno::fechaEsInferiorActual(fechaTurno)) {
                            cout << "Error: La fecha no puede ser inferior a la fecha actual.\n";
                        }
                    } while (!Turno::validarFecha(fechaTurno) || Turno::fechaEsInferiorActual(fechaTurno));
                    // Mostrar lista de profesionales disponibles en la fecha
                    cout << "\n=== Lista de Profesionales Disponibles ===\n";
                    for (const auto& profesional : listaProfesionales) {
                        if (Turno::profesionalDisponible(profesional, fechaTurno)) {
                            profesional.mostrarDatos();
                            cout << "-------------\n";
                        }
                    }
                    // Solicitar ID del profesional y validar que esté disponible en la fecha
                    int idProfesional;
                    do {
                        cout << "Ingrese ID del profesional: ";
                        cin >> idProfesional;
                        if (!existeId(listaProfesionales, idProfesional)) {
                            cout << "Error: ID de profesional no válido.\n";
                        } else if (!Turno::profesionalDisponible(listaProfesionales, idProfesional, fechaTurno)) {
                            cout << "Error: El profesional no está disponible en la fecha seleccionada.\n";
                        }
                    } while (!existeId(listaProfesionales, idProfesional) ||
                             !Turno::profesionalDisponible(listaProfesionales, idProfesional, fechaTurno));
                    // Mostrar lista de pacientes
                    cout << "\n=== Lista de Pacientes ===\n";
                    for (const auto& paciente : listaPacientes) {
                        paciente.mostrarDatos();
                        cout << "-------------\n";
                    }
                    // Solicitar ID del paciente y validar que exista
                    int idPaciente;
                    do {
                        cout << "Ingrese ID del paciente: ";
                        cin >> idPaciente;
                        if (!existeId(listaPacientes, idPaciente)) {
                            cout << "Error: ID de paciente no válido.\n";
                        }
                    } while (!existeId(listaPacientes, idPaciente));
                    // Solicitar hora del turno y validar que no sea inferior a la hora actual
                    string horaTurno;
                    do {
                        cout << "Ingrese hora del turno (HH:MM): ";
                        cin >> horaTurno;
                        if (!Turno::validarHora(horaTurno)) {
                            cout << "Error: Formato de hora no válido.\n";
                        } else if (fechaTurno == Turno::obtenerFechaActual() && Turno::horaEsInferiorActual(horaTurno)) {
                            cout << "Error: La hora no puede ser inferior a la hora actual.\n";
                        }
                    } while (!Turno::validarHora(horaTurno) || (fechaTurno == Turno::obtenerFechaActual() && Turno::horaEsInferiorActual(horaTurno)));
                    // Validar que no haya turnos superpuestos (excepto el turno actual)
                    if (Turno::existeTurnoSuperpuesto(listaTurnos, fechaTurno, horaTurno)) {
                        cout << "Error: Ya existe un turno en la misma fecha y hora.\n";
                        return; // No modificar el turno si hay superposición
                    }
                    // Solicitar el estado del turno
                    string estado;
                    cout << "Ingrese estado del turno: ";
                    cin >> estado;
                    // Actualizar los atributos del turno
                    it->setIdAdministrador(idAdministrador);
                    it->setIdProfesional(idProfesional);
                    it->setIdPaciente(idPaciente);
                    it->setFechaTurno(fechaTurno);
                    it->setHoraTurno(horaTurno);
                    it->setEstado(estado);
                    cout << "Turno con ID " << idModificar << " modificado.\n";
                    break;
                }
                ++it;
            }
            // Sobrescribir el archivo con la lista actualizada
            ConvertirInformacionDeListaYGuardarlaEnElArchivo(nombreArchivo, listaTurnos);
        }
        void VerificacionDeArchivo(const string& nombreArchivo, fstream& archivo)
        {
            archivo.open(nombreArchivo, ios::in);
            if (!archivo)
            {
                cout << "\nEl archivo " << nombreArchivo << " no existe, se creara: "
                     << nombreArchivo << endl;
                archivo.open          (nombreArchivo, ios::out);
                archivo.close();
            }
            else
            {
                archivo.close();
            }
            archivo.open(nombreArchivo, ios::in | ios::out | ios::app);
            if (!archivo)
            {
                cout << "Error al abrir o crear el archivo: " 
                     << nombreArchivo << "\n\n";
            }
            else
            {
                cout << "Se abrio correctamente el archivo: " 
                     << nombreArchivo << "\n\n";
                archivo.close();
            }
        }
    };//Verifica si los archivos existen. Si existen los abren y sino los crean
#pragma endregion
#pragma endregion
int main()
{
    gestorCsvArchivos gestor; //Constructor de gestor: Verifica la creacion e integridad de los archivos
    std::vector<Turno> listaTurnos = gestor.cargarTurnosDesdeArchivo();
    std::vector<Profesional> listaProfesionales = gestor.cargarProfesionalesDesdeArchivo();
    std::vector<Paciente> listaPacientes = gestor.cargarPacientesDesdeArchivo();
    std::vector<Administrador> listaAdministradores = gestor.cargarAdministradoresDesdeArchivo();
    bool loginExitoso = false;
    int intentos = 3;
    if (listaAdministradores.empty())
    {
        cout << "\nNo existen administradores en el archivo.\n";
        cout << "Registre un nuevo administrador para entrar con el el Log In.\n";
        listaAdministradores.push_back(Administrador::crearAdministrador(listaAdministradores));
        gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Administrador.txt", listaAdministradores);
    }
    do {
        loginExitoso = gestor.login(listaAdministradores);
        if (!loginExitoso) {
            cout << "\nIntente nuevamente.\n";
            intentos--;
            cout << intentos << "\n intentos restantes...\n";
        }
    } while (!loginExitoso && intentos > 0);
    if(intentos == 0) 
    {
        // Si el login es fallido, finaliza el programa
        cout << "\nAcceso denegado. Cerrando el programa.\n";
        return 0;
    }
    else
    {
        // Si el login es exitoso, continuar con el programa
        cout << "\nAcceso concedido. Bienvenido al sistema.\n";
    }  
    stack<void (*)()> pilaMenus; // Pila para gestionar los menús
    pilaMenus.push(menuPrincipal); // Iniciar con el menú principal
    while (!pilaMenus.empty()) {
        void (*menuActual)() = pilaMenus.top(); // Obtener el menú actual
        int opcion = mostrarMenu(menuActual); // Mostrar el menú y obtener la opción
        switch (opcion) {
        case 1:
            if (menuActual == menuPrincipal) {
                system("cls");
                pilaMenus.push(menuAdministradores); // Ir al menú de administradores
            }
            else if (menuActual == menuAdministradores) {
                cout << "\nCreando administrador...\n\n";
                listaAdministradores.push_back(Administrador::crearAdministrador(listaAdministradores));
                gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Administrador.txt", listaAdministradores);
            }
            else if (menuActual == menuProfesionales) {
                cout << "\nCreando profesional...\n\n";
                listaProfesionales.push_back(Profesional::crearProfesional(listaProfesionales));
                gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Profesional.txt", listaProfesionales);
            }
            else if (menuActual == menuPacientes) {
                cout << "\nCreando paciente...\n\n";
                listaPacientes.push_back(Paciente::crearPaciente(listaPacientes));
                gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Paciente.txt", listaPacientes);
            }
            else if (menuActual == menuTurnos) {
                cout << "\nCreando turno...\n\n";
                Turno nuevoTurno = Turno::crearTurno(listaTurnos, listaAdministradores, listaProfesionales, listaPacientes);
                if (nuevoTurno.getId() != 0) { // Verificar si el turno se creó correctamente
                    listaTurnos.push_back(nuevoTurno);
                    cout << "Turno creado exitosamente.\n";
                    gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Turnos.txt", listaTurnos);
                }
                else {
                    cout << "Error: No se pudo crear el turno.\n";
                }
            }
            break;
        case 2:
            if (menuActual == menuPrincipal) {
                system("cls");
                pilaMenus.push(menuProfesionales); // Ir al menú de profesionales
            }
            else if (menuActual == menuAdministradores) {
                gestor.solicitarContrasenia();
                cout << "\nModificando administrador...\n\n";
                gestor.mostrarYmodificarPorId(listaAdministradores, "Administrador.txt");
            }
            else if (menuActual == menuProfesionales) {
                gestor.solicitarContrasenia();
                cout << "\nModificando profesional...\n\n";
                gestor.mostrarYmodificarPorId(listaProfesionales, "Profesional.txt");
            }
            else if (menuActual == menuPacientes) {
                gestor.solicitarContrasenia();
                cout << "\nModificando paciente...\n\n";
                gestor.mostrarYmodificarPorId(listaPacientes, "Paciente.txt");
            }
            else if (menuActual == menuTurnos) {
                gestor.solicitarContrasenia();
                cout << "\nModificando turno...\n\n";
                gestor.mostrarYmodificarTurnoPorId(listaTurnos,listaAdministradores,listaProfesionales,listaPacientes, "Turnos.txt");
            }
            break;
        case 3:
            if (menuActual == menuPrincipal) {
                system("cls");
                pilaMenus.push(menuPacientes); // Ir al menú de pacientes
            }
            else if (menuActual == menuAdministradores) {
                gestor.solicitarContrasenia();
                cout << "\nEliminando administrador...\n\n";
                gestor.mostrarYeliminarPorId(listaAdministradores,"Administrador.txt");
            }
            else if (menuActual == menuProfesionales) {
                gestor.solicitarContrasenia();
                cout << "\nEliminando profesional...\n\n";
                gestor.mostrarYeliminarPorId(listaProfesionales, "Profesional.txt");
            }
            else if (menuActual == menuPacientes) {
                gestor.solicitarContrasenia();
                cout << "\nEliminando paciente...\n\n";
                gestor.mostrarYeliminarPorId(listaPacientes, "Paciente.txt");
            }
            else if (menuActual == menuTurnos) {
                gestor.solicitarContrasenia();
                cout << "\nEliminando turno...\n\n";
                gestor.mostrarYeliminarPorId(listaTurnos, "Turnos.txt");
            }
            break;
        case 4:
            if (menuActual == menuPrincipal) {
                system("cls");
                pilaMenus.push(menuTurnos); // Ir al menú de turnos
            }
            else if (menuActual == menuAdministradores) {
                system("cls");
                cout << "\nMostrando administradores...\n\n";
                gestor.mostrarAdministradores(listaAdministradores);
                cout << "\nPresione cualquier tecla para volver...\n";
                cin.ignore(); // Limpiar el buffer de entrada
                cin.get();    // Esperar a que el usuario presione una tecla
            }
            else if (menuActual == menuProfesionales) {
                system("cls");
                cout << "\nMostrando profesionales...\n\n";
                gestor.mostrarProfesionales(listaProfesionales);
                cout << "\nPresione cualquier tecla para volver...\n";
                cin.ignore(); // Limpiar el buffer de entrada
                cin.get();    // Esperar a que el usuario presione una tecla
            }
            else if (menuActual == menuPacientes) {
                system("cls");
                cout << "\nMostrando pacientes...\n\n";
                gestor.mostrarPacientes(listaPacientes);
                cout << "\nPresione cualquier tecla para volver...\n";
                cin.ignore(); // Limpiar el buffer de entrada
                cin.get();    // Esperar a que el usuario presione una tecla
            }
            else if (menuActual == menuTurnos) {
                system("cls");
                cout << "\nMostrando turnos...\n\n";
                gestor.mostrarTurnos(listaTurnos);
                cout << "\nPresione cualquier tecla para volver...\n";
                cin.ignore(); // Limpiar el buffer de entrada
                cin.get();    // Esperar a que el usuario presione una tecla
            }
            break;
        case 5:
            if (menuActual == menuPrincipal) {
                system("cls");
                pilaMenus.push(menuTurnos); // Ir al menú de turnos
            }
            break;
        case 0:
            pilaMenus.pop(); // Volver al menú anterior
            break;
        default:
            cout << "\nOpción no válida. Intente nuevamente.\n\n";
            cin.ignore(); // Limpiar el buffer de entrada
            cin.get();    // Esperar a que el usuario presione una tecla
        }
        system("cls");
    }

    cout << "\nSaliendo del programa.\n\n";
    return 0;
}

