#pragma region Librerias
#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h> // Para crear directorios en Linux y Windows
#pragma endregion
using namespace std;
#pragma region Constantes
const string archivo1 = "Administrador.txt";
const string archivo1 = "Profesional.txt";
const string archivo1 = "Paciente.txt";
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
            cout << "ID: " << p_id << "\nNombre: " << p_nombre << "\nApellido: " << p_apellido << endl;
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
            cout << "Usuario: " << p_usuario << "\n";
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
            cout << "DNI: " << p_dni << "\nEspecialidad: " << p_especialidad << "\nTelefono: " << p_telefono << "\nEmail: " << p_email << "\n";
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
            cout << "DNI: " << p_dni << "\nTelefono: " << p_telefono << "\nEmail: " << p_email << "\nFecha de Nacimiento: " << p_fechaNacimiento << "\n";
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
            cout << "ID Turno: " << p_id << "\nID Administrador: " << p_idAdministrador
                << "\nID Profesional: " << p_idProfesional << "\nID Paciente: " << p_idPaciente
                << "\nPeriodicidad: " << p_periodicidad << "\nEstado: " << p_estado
                << "\nRecurrente: " << (p_recurrente ? "Si" : "No") << "\n";
        }
    };
    class gestorCsvArchivos // Gestor de archivos 
    {

    };
#pragma endregion

int main()
{

    Administrador admin(1, "Carlos", "Gómez", "carlosAdmin", "admin123");
    Profesional prof(2, "Ana", "Martínez", "12345678", "Psicología", "1122334455", "ana@email.com", { DiaSemana::Lunes, DiaSemana::Miercoles });
    Paciente paciente(3, "Luis", "Pérez", "87654321", "2233445566", "luis@email.com", "12/05/1995");

    // Llamar a mostrarDatos()
    admin.mostrarDatos();
    cout << endl;
    prof.mostrarDatos();
    cout << endl;
    paciente.mostrarDatos();
    return 0;
}

