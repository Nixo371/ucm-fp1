#include <iostream>

using namespace std;

double pedir_dato(char *dato);

int main()
{
	double sueldo_base, complemento_d, complemento_a, horas_extras, hijos, mayores, sueldo_bruto, porcentaje_irpf, retencion_irpf, sueldo_neto;

	sueldo_base = pedir_dato("Sueldo base");
	complemento_d = pedir_dato("Complemento de destino");
	complemento_a = pedir_dato("Complemento de cargo academico");
	horas_extras = pedir_dato("Horas extras realizadas");
	hijos = pedir_dato("Hijos");
	mayores = pedir_dato("Mayores dependientes");

	sueldo_bruto = sueldo_base + complemento_a + complemento_d + (horas_extras * 23);
	porcentaje_irpf = 24 - (hijos * 2) - (mayores);
	
	retencion_irpf = (sueldo_bruto * porcentaje_irpf) / 100;

	sueldo_neto = sueldo_bruto - retencion_irpf;

	cout << "Sueldo base: " << sueldo_base << "€" << endl;
	cout << "Complemento de destino: " << complemento_d << "€" << endl;
	cout << "Complemento de cargo academico: " << complemento_a << "€" << endl;
	cout << "Horas extras realizadas: " << horas_extras << endl;
	cout << "Hijos: " << hijos << endl;
	cout << "Mayores: " << mayores << endl;

	cout << "Calculo de la nomina -" << endl;

	cout << "Sueldo bruto: " << sueldo_bruto << "€" << endl;
	cout << "Porcentaje de IRPF: " << porcentaje_irpf << "%" << endl;
	cout << "Retencion de IRPF: " << retencion_irpf<< "€" << endl;
	cout << "Sueldo neto: " << sueldo_neto << "€" << endl;
}

double pedir_dato(char *dato)
{
	double num;
	cout << dato << ": ";
	cin >> num;
	return (num);
}