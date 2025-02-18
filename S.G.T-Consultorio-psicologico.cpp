#pragma region Librerias y nameSpace
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h> // Para crear directorios en Linux y Windows
#include <direct.h> // Para _getcwd
#include <cstring>  // Para strlen
#include <chrono>
#include <sstream>
using namespace std;
#pragma endregion
#pragma region Estructuras
enum class DiaSemana //Representacion de los dias laborales del profesional
{ 
                                Lunes, 
                                Martes, 
                                Miercoles, 
                                Jueves, 
                                Viernes, 
                                Sabado, 
                                Domingo 
};
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
        {
        
        }
        ~Persona()
        {
        
        }
        virtual void mostrarDatos() const {
            cout << "ID: " 
                 << p_id 
                 << "\nNombre: " 
                 << p_nombre 
                 << "\nApellido: " 
                 << p_apellido << endl;
        }
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
        }

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
        string                  p_usuario, 
                                p_contrasenia;

    public:
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
        {

        }
        string getUsuario() const { return p_usuario; }
        string getContrasenia() const { return p_contrasenia; }
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_nombre << "," << p_apellido << "," << p_usuario << "," << p_contrasenia;
            return ss.str();
        }
        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "Usuario: " 
                 << p_usuario 
                 << "\n";
        }
        static Administrador crearAdministrador(const vector<Administrador>& lista) {
            string nombre, apellido, usuario, contrasenia;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese usuario: "; cin >> usuario;
            cout << "Ingrese contrasenia: "; cin >> contrasenia;

            int nuevoId = Persona::generarId(lista); // Generar el ID basado en la lista
            return Administrador(nuevoId, nombre, apellido, usuario, contrasenia);
        }
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo nombre: "; cin >> p_nombre;
            cout << "Ingrese nuevo apellido: "; cin >> p_apellido;
            cout << "Ingrese nuevo usuario: "; cin >> p_usuario;
            cout << "Ingrese nueva contrasenia: "; cin >> p_contrasenia;
        }
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
        }
    };
#pragma endregion
#pragma region Profesional
    class Profesional : public Persona //Representacion del profesional (heredara de persona)
    {
        string                  p_dni,
                                p_especialidad,
                                p_telefono,
                                p_email;
        vector <DiaSemana>      p_diaLaboral;

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

        }
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
        }
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
        }
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

        }
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
        }
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
        }
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
        {

        }
        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "DNI: " 
                 << p_dni 
                 << "\nTelefono: " 
                 << p_telefono << "\nEmail: " 
                 << p_email << "\nFecha de Nacimiento: " 
                 << p_fechaNacimiento << "\n";
        }
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_nombre << "," << p_apellido << ","
                << p_dni << "," << p_telefono << "," << p_email << "," << p_fechaNacimiento;
            return ss.str();
        }
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
        }
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo nombre: "; cin >> p_nombre;
            cout << "Ingrese nuevo apellido: "; cin >> p_apellido;
            cout << "Ingrese nuevo DNI: "; cin >> p_dni;
            cout << "Ingrese nuevo telefono: "; cin >> p_telefono;
            cout << "Ingrese nuevo email: "; cin >> p_email;
            cout << "Ingrese nueva fecha de nacimiento (DD/MM/YEAR): "; cin >> p_fechaNacimiento;
        }
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
        }
    };
#pragma endregion
#pragma region Turnos
    class Turno //Representacion de los turnos
    {
        int                     p_id, 
                                p_idAdministrador,
                                p_idProfesional,
                                p_idPaciente,
                                p_periodicidad;                     
        string                  p_fechaTurno,
                                p_horaTurno,
                                p_estado;
                            

    public:
        Turno                  (int id,
                                int idAdministrador, 
                                int idProfesional, 
                                int idPaciente, 
                                int periodicidad, 
                                const string& fechaTurno, 
                                const string& horaTurno,
                                string estado)

            : p_id             (id), 
              p_idAdministrador(idAdministrador), 
              p_idProfesional  (idProfesional), 
              p_idPaciente     (idPaciente),
              p_periodicidad   (periodicidad), 
              p_fechaTurno     (fechaTurno),
              p_horaTurno      (horaTurno),
              p_estado         (estado)
        {
        }
        void mostrarDatos() const {
            cout << "ID Turno: " 
                 << p_id 
                 << "\nID Administrador: " 
                 << p_idAdministrador
                 << "\nID Profesional: " 
                 << p_idProfesional 
                 << "\nID Paciente: " 
                 << p_idPaciente
                 << "\nPeriodicidad: " 
                 << p_periodicidad 
                 << "\nEstado: " 
                 << p_estado
                 << "\n";
        }
        string toCsv() const {
            stringstream ss;
            ss << p_id << "," << p_idAdministrador << "," << p_idProfesional << ","
                << p_idPaciente << "," << p_periodicidad << "," << p_fechaTurno << ","
                << p_horaTurno << "," << p_estado;
            return ss.str();
        }
        int getId() const { return p_id; }
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
        }
        static Turno crearTurno(const vector<Turno>& lista) {
            int idAdministrador, idProfesional, idPaciente, periodicidad;
            string fechaTurno, horaTurno, estado;
            bool recurrente;

            cout << "Ingrese ID del administrador: "; cin >> idAdministrador;
            cout << "Ingrese ID del profesional: "; cin >> idProfesional;
            cout << "Ingrese ID del paciente: "; cin >> idPaciente;
            cout << "Ingrese periodicidad: "; cin >> periodicidad;
            cout << "Ingrese fecha del turno (YYYY-MM-DD): "; cin >> fechaTurno;
            cout << "Ingrese hora del turno (HH:MM): "; cin >> horaTurno;
            cout << "Ingrese estado del turno: "; cin >> estado;
            cout << "Es recurrente? (1 = Si, 0 = No): "; cin >> recurrente;

            int nuevoId = generarId(lista); // Generar el ID basado en la lista
            return Turno(nuevoId, idAdministrador, idProfesional, idPaciente, periodicidad, fechaTurno, horaTurno, estado);
        }
        void modificarDesdeConsola() {
            cout << "Ingrese nuevo ID del administrador: "; cin >> p_idAdministrador;
            cout << "Ingrese nuevo ID del profesional: "; cin >> p_idProfesional;
            cout << "Ingrese nuevo ID del paciente: "; cin >> p_idPaciente;
            cout << "Ingrese nueva periodicidad: "; cin >> p_periodicidad;
            cout << "Ingrese nueva fecha del turno (YYYY-MM-DD): "; cin >> p_fechaTurno;
            cout << "Ingrese nueva hora del turno (HH:MM): "; cin >> p_horaTurno;
            cout << "Ingrese nuevo estado del turno: "; cin >> p_estado;
        }
        void fromCsv(const string& csvLine) {
            stringstream ss(csvLine);
            char delim;
            ss >> p_id >> delim;
            ss >> p_idAdministrador >> delim;
            ss >> p_idProfesional >> delim;
            ss >> p_idPaciente >> delim;
            ss >> p_periodicidad >> delim;
            getline(ss, p_fechaTurno, ',');
            getline(ss, p_horaTurno, ',');
            getline(ss, p_estado, ',');
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
        }
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
        }
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
        }
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
        }
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
        }
        void VerificacionDeArchivo(const string& nombreArchivo, fstream& archivo)
        {
            archivo.open(nombreArchivo, ios::in);

            if (!archivo)
            {
                cout << "El archivo no existe, se creara: "  
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
                     << nombreArchivo << "\n";
            }
            else
            {
                cout << "Se abrio correctamente el archivo: " 
                     << nombreArchivo << "\n\n";
                archivo.close();
            }
        }
    };
#pragma endregion
#pragma endregion

int main()
{
    gestorCsvArchivos gestor; //Constructor de gestor: Verifica la creacion e integridad de los archivos
    std::vector<Turno> listaTurnos;
    std::vector<Profesional> listaProfesionales = gestor.cargarProfesionalesDesdeArchivo();
    std::vector<Paciente> listaPacientes = gestor.cargarPacientesDesdeArchivo();
    std::vector<Administrador> listaAdministradores = gestor.cargarAdministradoresDesdeArchivo();
    bool loginExitoso = false;
    int intentos = 3;
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
    int opcion;
    do {
        cout << "\n=== Menu Principal ===\n";
        cout << "1. Gestionar turnos\n";
        cout << "2. Gestionar administradores\n";
        cout << "3. Gestionar profecionales\n";
        cout << "4. Gestionar pacientes\n";
        cout << "0. Salir\n";
        cout << "\nIngrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {

            break;
        }
        case 4: {
            break;
        }
        case 0: {
            cout << "Saliendo del programa.\n";
            break;
        }
        default: {
            cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
        }
    } while (opcion != 0);

    return 0;
    /*
    listaAdministradores.push_back(Administrador::crearAdministrador(listaAdministradores));
    listaAdministradores.push_back(Administrador::crearAdministrador(listaAdministradores));
    gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Administrador.txt", listaAdministradores);\
    gestorCsvArchivos::mostrarAdministradores(listaAdministradores);
    listaProfesionales.push_back(Profesional::crearProfesional(listaProfesionales));
    gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Profesional.txt", listaProfesionales);
    cout << "Lista de Administradores:\n";
    }
    gestorCsvArchivos::mostrarProfesionales(listaProfesionales);
    listaPacientes.push_back(Paciente::crearPaciente(listaPacientes));
    gestor.ConvertirInformacionDeListaYGuardarlaEnElArchivo("Paciente.txt", listaPacientes);
    gestorCsvArchivos::mostrarPacientes(listaPacientes);
    */
    gestor.mostrarYmodificarPorId(listaAdministradores, "Administrador.txt");
    return 0;
}

