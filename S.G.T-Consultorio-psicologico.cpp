#pragma region Librerias
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h> // Para crear directorios en Linux y Windows
#include <direct.h> // Para _getcwd
#include <cstring>  // Para strlen
#include <chrono>
#include <sstream>
#pragma endregion
using namespace std;

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
        static int generarId(const string& archivo) {
            ifstream file(archivo);
            if (!file.is_open()) return 1;  // Si el archivo no existe, empezar desde 1

            int maxId = 0;
            string line;

            while (getline(file, line)) {
                stringstream ss(line);
                int id;

                // Validar si la línea tiene al menos un número entero válido
                if (ss >> id) {
                    maxId = max(maxId, id);
                }
            }
            return maxId + 1;  // Devolver el mayor ID encontrado + 1
        }
        int getId() const { return p_id; }
        string getNombre() const { return p_nombre; }
        string getApellido() const { return p_apellido; }

        // Setters
        void setNombre(const string& _nombre) { p_nombre = _nombre; }
        void setApellido(const string& _apellido) { p_apellido = _apellido; }
    };
    class Administrador : public Persona //Representacion del administrador (heredara de persona) 
    {
        string                  p_usuario, 
                                p_contrasenia;

    public:
        Administrador          (string nombre, 
                                string apellido, 
                                string usuario, 
                                string contrasenia)

            : Persona          (generarId("Administrador.txt"), 
                                nombre, 
                                apellido), 
              p_usuario         (usuario), 
              p_contrasenia     (contrasenia) 
        {

        }
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
        static Administrador crearAdministrador() {
            string               nombre, 
                                 apellido, 
                                 usuario, 
                                 contrasenia;
            cout << "Ingrese nombre: "; 
            cin >> nombre;
            cout << "Ingrese apellido: "; 
            cin >> apellido;
            cout << "Ingrese usuario: "; 
            cin >> usuario;
            cout << "Ingrese contrasenia: "; 
            cin >> contrasenia;
            return Administrador(nombre, 
                                 apellido, 
                                 usuario, 
                                 contrasenia);
        }
    };
    class Profesional : public Persona //Representacion del profesional (heredara de persona)
    {
        string                  p_dni,
                                p_especialidad,
                                p_telefono,
                                p_email;
        vector <DiaSemana>      p_diaLaboral;

    public:
        Profesional            (string nombre, 
                                string apellido, 
                                string dni, 
                                string especialidad, 
                                string telefono,
                                string email, 
                                vector<DiaSemana> diaLaboral)

            : Persona          (generarId("Profesional.txt"), 
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
                 << "\n";
        }
        static Profesional crearDesdeEntrada() {
            string nombre, apellido, dni, especialidad, telefono, email;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese DNI: "; cin >> dni;
            cout << "Ingrese especialidad: "; cin >> especialidad;
            cout << "Ingrese telefono: "; cin >> telefono;
            cout << "Ingrese email: "; cin >> email;
            return Profesional(nombre, apellido, dni, especialidad, telefono, email, {});
        }
    };
    class Paciente : public Persona //Representacion del paciente (heredara de persona)
    {
        string                  p_dni,
                                p_telefono,
                                p_email, 
                                p_fechaNacimiento;

    public:
        Paciente               (string nombre, 
                                string apellido, 
                                string dni, 
                                string telefono, 
                                string email, 
                                string fechaNacimiento)

            : Persona          (generarId("Paciente.txt"), 
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
        static Paciente crearDesdeEntrada() {
            string nombre, apellido, dni, telefono, email, fechaNacimiento;
            cout << "Ingrese nombre: "; cin >> nombre;
            cout << "Ingrese apellido: "; cin >> apellido;
            cout << "Ingrese DNI: "; cin >> dni;
            cout << "Ingrese telefono: "; cin >> telefono;
            cout << "Ingrese email: "; cin >> email;
            cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): "; cin >> fechaNacimiento;
            return Paciente(nombre, apellido, dni, telefono, email, fechaNacimiento);
        }
    };
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
        bool                    p_recurrente;

    public:
        Turno                  (int idAdministrador, 
                                int idProfesional, 
                                int idPaciente, 
                                int periodicidad, 
                                const string& fechaTurno, 
                                const string& horaTurno,
                                string estado, 
                                bool recurrente)

            : p_id(generarId   ("Turnos.txt")), 
              p_idAdministrador(idAdministrador), 
              p_idProfesional  (idProfesional), 
              p_idPaciente     (idPaciente),
              p_periodicidad   (periodicidad), 
              p_fechaTurno     (fechaTurno),
              p_horaTurno      (horaTurno),
              p_estado         (estado),
              p_recurrente     (recurrente) {
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
                 << "\nRecurrente: " 
                 << (p_recurrente ? "Si" : "No") << "\n";
        }
        static int generarId(const string& archivo) {
            ifstream file(archivo);
            if (!file.is_open()) return 1;

            int maxId = 0;
            string line;

            while (getline(file, line)) {
                stringstream ss(line);
                int id;

                if (ss >> id) {  // Solo procesar si el ID es válido
                    maxId = max(maxId, id);
                }
            }
            return maxId + 1;
        }
        static Turno crearTurno() {
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

            return Turno(idAdministrador, idProfesional, idPaciente, periodicidad, fechaTurno, horaTurno, estado, recurrente);
        }
    };
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
    public:
        gestorCsvArchivos()
        {
            VerificacionDeArchivo(archivoAdministrador,A_Administradores);
            VerificacionDeArchivo(archivoProfesional,A_Profesionales);
            VerificacionDeArchivo(archivoPaciente,A_Pacientes);
            VerificacionDeArchivo(archivoTurno, A_Turnos);
        }
        template <typename T>
        static void guardarEnArchivo(const string& nombreArchivo, const vector<T>& lista) {
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
                     << nombreArchivo << "\n";
                archivo.close();
            }
        }
    };
#pragma endregion

int main()
{
    gestorCsvArchivos gestor; //Constructor de gestor: Verifica la creacion e integridad de los archivos
    std::vector<Turno> listaTurnos;
    std::vector<Profesional> listaProfesionales;
    std::vector<Paciente> listaPacientes;
    std::vector<Administrador> listaAdministradores;

    listaAdministradores.push_back(Administrador::crearAdministrador());
    gestor.guardarEnArchivo("Administrador", listaAdministradores);
    listaAdministradores.push_back(Administrador::crearAdministrador());
    gestor.guardarEnArchivo("Administrador", listaAdministradores);

    cout << "Lista de Administradores:\n";
    for (const auto& administrador : listaAdministradores) {
        administrador.mostrarDatos(); // Llamamos a la función mostrarDatos()
    }
    cin.get();
    return 0;
}

