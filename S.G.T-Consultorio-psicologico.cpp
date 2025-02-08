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
        void mostrarDatos() const override {
            Persona::mostrarDatos();
            cout << "Usuario: " 
                 << p_usuario 
                 << "\n";
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
    cin.get();
    return 0;
}

