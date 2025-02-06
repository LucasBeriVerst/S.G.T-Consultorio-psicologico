#pragma region Librerias
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h> // Para crear directorios en Linux y Windows
#include <direct.h> // Para _getcwd
#include <cstring>  // Para strlen
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
    public:
        int                     p_id;
        string                  p_nombre, 
                                p_apellido;

        Persona                (int id, 
                                string nombre, 
                                string apellido)

            :                   p_id       (id), 
                                p_nombre   (nombre),
                                p_apellido (apellido)
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
    };
    class Administrador : public Persona //Representacion del administrador (heredara de persona) 
    {
    public:
        string                  p_usuario, 
                                p_contrasenia;

        Administrador          (int id, 
                                string nombre, 
                                string apellido, 
                                string usuario, 
                                string contrasenia)

            : Persona          (id, 
                                nombre, 
                                apellido),
              p_usuario        (usuario),
              p_contrasenia    (contrasenia)
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
    public:
        string                  p_dni,
                                p_especialidad,
                                p_telefono,
                                p_email;
        vector <DiaSemana>      p_diaLaboral;

        Profesional            (int id, 
                                string nombre,
                                string apellido,
                                string dni,
                                string especialidad,
                                string telefono,
                                string email,
                                vector <DiaSemana> diaLaboral)

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
                 << "\n";
        }
    };
    class Paciente : public Persona //Representacion del paciente (heredara de persona)
    {
    public:
        string                  p_dni,
                                p_telefono,
                                p_email, 
                                p_fechaNacimiento;

        Paciente               (int id,
                                string nombre,
                                string apellido,
                                string dni,
                                string telefono,
                                string email,
                                string fechaNacimiento)

            : Persona          (id,nombre,apellido),
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
    class Turnos //Representacion de los turnos
    {
    public:
        int                     p_id, 
                                p_idAdministrador,
                                p_idProfesional,
                                p_idPaciente,
                                p_periodicidad;
        tm                      p_fechaTurno;
        string                  p_estado;
        bool                    p_recurrente;

        Turnos                 (int id, 
                                int idAdministrador, 
                                int idProfesional, 
                                int idPaciente, 
                                int periodicidad,
                                const tm& fechaTurno,
                                string estado, 
                                bool recurrente)

            : p_id             (id),
              p_idAdministrador(idAdministrador),
              p_idProfesional  (idProfesional),
              p_idPaciente     (idPaciente),
              p_periodicidad   (periodicidad),
              p_fechaTurno     (fechaTurno),
              p_estado         (estado),
              p_recurrente     (recurrente)
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
                 << "\nRecurrente: " 
                 << (p_recurrente ? "Si" : "No") << "\n";
        }
    };
    class gestorCsvArchivos // Gestor de archivos 
    {

        const string archivoAdministrador = "Administrador.txt";
        const string archivoProfesional = "Profesional.txt";
        const string archivoPaciente = "Paciente.txt";

        //archivos de escritura y lectura.
        fstream A_Administradores;
        fstream A_Profesionales;
        fstream A_Pacientes;
    public:
        gestorCsvArchivos()
        {
            VerificacionDeArchivo(archivoAdministrador,A_Administradores);
            VerificacionDeArchivo(archivoProfesional,A_Profesionales);
            VerificacionDeArchivo(archivoPaciente,A_Pacientes);
        }
        void VerificacionDeArchivo(const string& nombreArchivo, fstream& archivo)
        {
            archivo.open(nombreArchivo, ios::in);

            if (!archivo)
            {
                cout << "El archivo no existe, se creara: " << nombreArchivo << endl;
                archivo.open(nombreArchivo, ios::out);
                archivo.close();
            }
            else
            {
                archivo.close();
            }

            archivo.open(nombreArchivo, ios::in | ios::out | ios::app);

            if (!archivo)
            {
                cout << "Error al abrir o crear el archivo: " << nombreArchivo << "\n";
            }
            else
            {
                cout << "Se abrio correctamente el archivo: " << nombreArchivo << "\n";
            }
        }
    };
#pragma endregion

int main()
{

    gestorCsvArchivos gestor;
    cin.get();
    return 0;
}

