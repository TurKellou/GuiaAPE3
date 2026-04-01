#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

int numEstu;
vector<string> nombre;
vector<string> paralelo;
vector<int> nota1;
vector<int> nota2;
vector<int> notaPra;
vector<int> asistencias;
vector<float> promedio;
vector<string> categoria;
vector<string> estadoFinal;

void numeroAlum(){
    do{
        cout<<"Ingrese el número de estudiantes: "<<endl;
        cin>>numEstu;

        if(numEstu <= 0){
            cout<<"Valor de número de estudiantes invalido."<<endl;
        }

        if(numEstu > 0){
            cout<<"Valor de estudiantes valido."<<endl;
        }
    }while(numEstu <= 0);
    nombre.resize(numEstu);
    paralelo.resize(numEstu);
    nota1.resize(numEstu);
    nota2.resize(numEstu);
    notaPra.resize(numEstu);
    asistencias.resize(numEstu);
    promedio.resize(numEstu);
    categoria.resize(numEstu);
    estadoFinal.resize(numEstu);
}

void datosEstu(){
    for(int i=0; i<numEstu; i++){
        cout<<"Estudiante "<<i+1<<": ";
        cout<<"Ingrese el nombre del estudiante: ";
        cin>>nombre[i];

        do{
        cout<<"Ingrese el paralelo (A/B/C...): ";
        cin>>paralelo[i];
        if(paralelo[i] != "A" && paralelo[i] != "B" && paralelo[i] != "C"){
            cout<<"Valor invalido. Ingrese nuevamente"<<endl;
        }


        }while(paralelo[i] != "A" && paralelo[i] != "B" && paralelo[i] != "C");

        //Nota 1
        do{
            cout<<"Ingrese la nota del parcial 1 (0-10): ";
            cin>>nota1[i];
            if(nota1[i] < 0 || nota1[i] > 10){
                cout<<"Valor invalido. Ingrese nuevamente"<<endl;
            }
        }while(nota1[i] < 0 || nota1[i] > 10);

        //Nota 2
        do{
            cout<<"Ingrese la nota del parcial 2 (0-10): ";
            cin>>nota2[i];
            if(nota2[i] < 0 || nota2[i] > 10){
                cout<<"Valor invalido. Ingrese nuevamente"<<endl;
            }
        }while(nota2[i] < 0 || nota2[i] > 10);

        //Practicas
        do{
            cout<<"Ingrese la nota de practicas (0-10): ";
            cin>>notaPra[i];
            if(notaPra[i] < 0 || notaPra[i] > 10){
                cout<<"Valor invalido. Ingrese nuevamente"<<endl;
            }
        }while(notaPra[i] < 0 || notaPra[i] > 10);

        //Asistencias
        do{
            cout<<"Ingrese porcentaje de asistencia (0-100): ";
            cin>>asistencias[i];
            if(asistencias[i] < 0 || asistencias[i] > 100){
                cout<<"Valor invalido. Ingrese nuevamente"<<endl;
            }
        }while(asistencias[i] < 0 || asistencias[i] > 100);
    }
}

void calcularPromediosYEstados() {
    for(int i = 0; i < numEstu; i++) {
        // Calcular promedio
        promedio[i] = (nota1[i] * 0.30) + (nota2[i] * 0.30) + (notaPra[i] * 0.40);

        // Determinar categoría por promedio
        if(promedio[i] >= 9.0) categoria[i] = "Excelente";
        else if(promedio[i] >= 8.0) categoria[i] = "Muy bueno";
        else if(promedio[i] >= 7.0) categoria[i] = "Bueno";
        else if(promedio[i] >= 6.0) categoria[i] = "En riesgo";
        else categoria[i] = "Reprobado";

        // Verificar condiciones especiales
        string estado = categoria[i];
        bool reprobadoAsistencia = asistencias[i] < 70;
        bool alertaInconsistencia = (promedio[i] >= 9.0 && asistencias[i] < 80);
        bool notasIguales = (nota1[i] == nota2[i] && nota2[i] == notaPra[i]);
        int notaMax = max({nota1[i], nota2[i], notaPra[i]});
        int notaMin = min({nota1[i], nota2[i], notaPra[i]});
        bool rendimientoInestable = (notaMax - notaMin > 4);

        if(reprobadoAsistencia) {
            estado = "Reprobado por asistencia";
        } else if(alertaInconsistencia) {
            estado += " *ALERTA: Inconsistencia*";
        } else if(notasIguales) {
            estado += " (Rendimiento estable)";
        } else if(rendimientoInestable) {
            estado += " (Rendimiento inestable)";
        }

        estadoFinal[i] = estado;
    }
}

void mostrarReporteIndividual() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "           REPORTE INDIVIDUAL DE ESTUDIANTES\n";
    cout << string(70, '=') << "\n";
    cout << left << setw(4) << "N°"
         << setw(15) << "Nombre"
         << setw(6) << "Paral."
         << setw(8) << "N1"
         << setw(8) << "N2"
         << setw(8) << "Prac."
         << setw(8) << "Asist."
         << setw(8) << "Prom."
         << setw(20) << "Estado Final" << endl;
    cout << string(70, '-') << "\n";

    for(int i = 0; i < numEstu; i++) {
        cout << left << setw(4) << (i+1)
             << setw(15) << nombre[i]
             << setw(6) << paralelo[i]
             << setw(8) << nota1[i]
             << setw(8) << nota2[i]
             << setw(8) << notaPra[i]
             << setw(8) << asistencias[i] << "%"
             << setw(8) << fixed << setprecision(2) << promedio[i]
             << setw(20) << estadoFinal[i] << endl;
    }
    cout << string(70, '=') << "\n";
}

void mostrarReporteGeneral() {
    // Contadores por categoría
    int contExcelente = 0, contMuyBueno = 0, contBueno = 0;
    int contEnRiesgo = 0, contReprobadoNota = 0, contReprobadoAsistencia = 0;
    int aprobados = 0;
    int rendimientoEstable = 0, rendimientoInestable = 0;

    // Contadores por paralelo
    vector<int> contParalelo(26, 0);

    float sumaPromedios = 0;
    float maxPromedio = -1;
    string mejorEstudiante;
    float minPromedio = 11;
    string peorEstudiante;
    float sumaPromediosParalelo[26] = {0};
    int contEstuParalelo[26] = {0};

    for(int i = 0; i < numEstu; i++) {
        sumaPromedios += promedio[i];

        // Contar por paralelo
        int idxParalelo = paralelo[i][0] - 'A';
        if(idxParalelo >= 0 && idxParalelo < 26) {
            contParalelo[idxParalelo]++;
            sumaPromediosParalelo[idxParalelo] += promedio[i];
            contEstuParalelo[idxParalelo]++;
        }

        // Contar categorías
        string estado = estadoFinal[i];
        if(estado.find("Excelente") != string::npos) contExcelente++;
        else if(estado.find("Muy bueno") != string::npos) contMuyBueno++;
        else if(estado.find("Bueno") != string::npos) contBueno++;
        else if(estado.find("En riesgo") != string::npos) contEnRiesgo++;
        else if(estado.find("Reprobado por asistencia") != string::npos) contReprobadoAsistencia++;
        else if(estado.find("Reprobado") != string::npos) contReprobadoNota++;

        // Aprobados
        if(estado.find("Reprobado") == string::npos &&
           estado.find("asistencia") == string::npos) {
            aprobados++;
        }

        // Rendimiento
        if(estado.find("estable") != string::npos) rendimientoEstable++;
        else if(estado.find("inestable") != string::npos) rendimientoInestable++;

        // Mejor y peor
        if(promedio[i] > maxPromedio) {
            maxPromedio = promedio[i];
            mejorEstudiante = nombre[i];
        }
        if(promedio[i] < minPromedio) {
            minPromedio = promedio[i];
            peorEstudiante = nombre[i];
        }
    }

    float promedioGeneral = sumaPromedios / numEstu;
    float porcAprobados = (float)aprobados / numEstu * 100;
    float porcEstable = (float)rendimientoEstable / numEstu * 100;
    float porcInestable = (float)rendimientoInestable / numEstu * 100;

    cout << "\n" << string(70, '=') << "\n";
    cout << "                 REPORTE GENERAL\n";
    cout << string(70, '=') << "\n";
    cout << "Total de estudiantes procesados: " << numEstu << "\n\n";

    cout << "CANTIDAD POR CATEGORIA:\n";
    cout << "Excelente: " << contExcelente << "\n";
    cout << "Muy bueno: " << contMuyBueno << "\n";
    cout << "Bueno: " << contBueno << "\n";
    cout << "En riesgo: " << contEnRiesgo << "\n";
    cout << "Reprobados por nota: " << contReprobadoNota << "\n";
    cout << "Reprobados por asistencia: " << contReprobadoAsistencia << "\n\n";

    cout << "ESTADISTICAS GENERALES:\n";
    cout << "Promedio general del curso: " << fixed << setprecision(2) << promedioGeneral << "\n";
    cout << "Porcentaje aprobados: " << porcAprobados << "%\n";
    cout << "Porcentaje rendimiento estable: " << porcEstable << "%\n";
    cout << "Porcentaje rendimiento inestable: " << porcInestable << "%\n\n";

    cout << "MEJOR Y PEOR RENDIMIENTO:\n";
    cout << "Mejor promedio: " << maxPromedio << " - " << mejorEstudiante << "\n";
    cout << "Menor promedio: " << minPromedio << " - " << peorEstudiante << "\n\n";

    cout << "DISTRIBUCION POR PARALELO:\n";
    for(int i = 0; i < 26; i++) {
        if(contParalelo[i] > 0) {
            char letra = 'A' + i;
            float promParalelo = contEstuParalelo[i] > 0 ?
                sumaPromediosParalelo[i] / contEstuParalelo[i] : 0;
            cout << "Paralelo " << letra << ": " << contParalelo[i]
                 << " est. (Prom: " << fixed << setprecision(2) << promParalelo << ")\n";
        }
    }

    cout << string(70, '=') << "\n";
}

int main() {
    cout << "=== SISTEMA DE GESTION ACADEMICA ===\n\n";

    numeroAlum();
    datosEstu();
    calcularPromediosYEstados();

    mostrarReporteIndividual();
    mostrarReporteGeneral();

    cout << "\nPresione Enter para finalizar...";
    cin.ignore();
    cin.get();

    return 0;
}
