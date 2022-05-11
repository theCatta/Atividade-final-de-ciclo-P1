#include <iostream>
#include <iomanip>
#include<algorithm>
#include <string.h>
#include <time.h>
#include <sstream>
#include <locale.h>

using namespace std;

class Data
{
private:
	int dia;
	int mes;
	int ano;

public:
	Data(int dia, int mes, int ano)
	{
		this->dia = dia;
		this->mes = mes;
		this->ano = ano;
	}

	Data()
	{
		this->dia = 28;
		this->mes = 9;
		this->ano = 1962;
	}

	void setDia(int dia)
	{
		this->dia = dia;
	}

	void setMes(int mes)
	{
		this->mes = mes;
	}

	void setAno(int ano)
	{
		this->ano = ano;
	}

	int getDia()
	{
		return this->dia;
	}

	int getMes()
	{
		return this->mes;
	}

	int getAno()
	{
		return this->ano;
	}

	string getData()
	{
		return to_string(this->dia) + "/" +
			   to_string(this->mes) + "/" +
			   to_string(this->ano);
		
		//Caso "to_string" não funcione, aplique: 
	
		/*	
		stringstream stream;
		stream << this->dia;
		string saidaDia;
		stream >> saidaDia;
		
		stringstream stream2;
		stream2 << this->mes;
		string saidaMes;
		stream2 >> saidaMes;
		
		
		stringstream stream3;
		stream3 << this->ano;
		string saidaAno;
		stream3 >> saidaAno;
		
		return saidaDia.append("/").append(saidaMes).append("/").append(saidaAno);
		*/
		
	}
	

	Data* dia_seguinte()
	{
		Data *ds;
		int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		ds = new Data(this->dia, this->mes, this->ano);

		if (ds->ano % 4 == 0)
		{
			diasNoMes[1]++;
		}

		ds->dia++;
		if (ds->dia > diasNoMes[ds->mes - 1])
		{
			ds->dia = 1;
			ds->mes++;
			if(ds->mes > 12)
			{
				ds->mes = 1;
				ds->ano++;
			}
		}

		return ds;
	}

};

class Contato
{
private:
	string email;
	string nome;
	string tel;
	Data *dtnasc;
	
public:
	Contato(string nome, string email, string tel, int dia, int mes, int ano){
		this->email = email;
		this->nome = nome;
		this->tel = tel;
		this->dtnasc = new Data(dia, mes, ano);
	}
	
	void setNome(string nome){
		this->nome = nome;
	}
	
	void setEmail(string email){
		this->email = email;
	}
	
	void setTel(string tel){
		this->tel = tel;
	}
	
	void setNasc(int dia, int mes, int ano){
		this->dtnasc = new Data(dia, mes, ano);
	}
	
	string getNome(){
		return this->nome;
	}
	
	string getEmail(){
		return this->email;
	}
	
	string getTel(){
		return this->tel;
	}
	
	int getIdade(){
		time_t tempo;
	    tempo = time(NULL);
	    struct tm tm = *localtime(&tempo);
	    //printf("Data: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	    //int idade = (tm.tm_year + 1900) - this->dtnasc->getAno();
	    
  		int dtAt = (tm.tm_year + 1900) * 365 + (tm.tm_mon + 1) * 30 + tm.tm_mday;
		int dtN = this->dtnasc->getAno() * 365 + this->dtnasc->getMes() * 30 + this->dtnasc->getDia();
		
		int diferenca = dtAt - dtN;
		int idade = diferenca/365;
		
		return idade;
	}
	
	string getNasc(){
		return this->dtnasc->getData();
	}
	
};


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");
	int p = 10;
	string nome, email, tel;
	int dia, mes, ano;
	
	Contato *contatos[p];
	for(int i=0; i<p; i++){
		cout << "Contato " << i+1 << endl;
		cout << "Insira seu nome: " << endl;
		cin >> nome;

		
		cout << "Insira seu email: " << endl;
		cin >> email;

		
		cout << "Insira seu telefone: " << endl;
		cin >> tel;

		
		cout << "Insira sua data de nascimento: " << endl;
		cout << "Dia: ";
		cin >> dia;
		cout << "Mes: ";
		cin >> mes;
		cout << "Ano: ";
		cin >> ano;
		contatos[i] = new Contato(nome, email, tel, dia, mes, ano);
		
		cout << endl;
	}
	
	int *idades;
	float media;
	
	idades = new int[p];
	
	for(int i = 0; i < p; ++i){
		idades[i] = contatos[i]->getIdade();
		media += idades[i];
		if(i == (p - 1)){
			media /= p;	
	   	  	cout << "Média dos contatos: " << media << endl;
		}
	}
	cout << endl;
	int count = 0;
	for(int i = 0; i < p; ++i){
		if(idades[i] > media){
			cout << "Nome do contato com idade maior que a média: " << contatos[i]->getNome() << endl;
		}
		if(idades[i] > 18){
		    count++;
		}
	}
	
	cout << endl;
	
	cout << "Quantidade de contatos maiores de 18 anos: " << count << endl; //utilizando a data do pc dia, mes e ano para o calculo


    int maisVelho = 0;
	for(int i = 0; i < p; ++i){
	    if(maisVelho < idades[i]){
	        maisVelho = idades[i];
	    }
	}
	
	cout << endl;
	
	for(int i = 0; i < p; i++){
	    if(idades[i] == maisVelho){
	        cout << "Dados do contato mais velho: " << 	"Nome: " << contatos[i]->getNome() << ", " << "Email: " << contatos[i]->getEmail() << 
			", " << "Telefone: " << contatos[i]->getTel() << ", " << "Idade: " << contatos[i]->getIdade() << 
			", " << "Data de nascimento: " << contatos[i]->getNasc() << endl;
	    }
	}
	
	
	return 0;
}
