#include <iostream>
#include <iomanip>
#include<cstdlib>
#include <ctime>
using namespace std;

// ----------------- Estrutura para Pacotes Nacionais -----------------
struct PacoteNacional {
    double peso;
    double volume;
    double frete_internacional;
    double frete_total;
    bool extras;
    bool seguro;
    bool cupom;
    bool prioridade;
    int cupom_valido;
    int dias_entrega;
};


// ----------------- Fun��o para Calcular Custo Total Internacional -----------------
void CadastroInternacional(int &encomenda, PacoteNacional pacote[]) {
	cout<<"-----------------------------------------------"<<endl<<"            Cadastro Internacional           "<<endl<<endl;
    int custo_porto = 10, escolha = 0;
	cout << "Escolha um porto de origem: 1 - Asia (1000.00 - 14 dias), 2 - Europa (800.00 - 10 dias), 3 - America (500.00 - 7 dias)"<<endl;
	cin>>escolha;
	while(escolha != 1 && escolha != 2 && escolha != 3){
		cout << "Opcao invalida. Tente novamente." << endl;
		cin>>escolha;
	}
	if(escolha == 1) {
		custo_porto = 1000;
		pacote[encomenda].dias_entrega = 14;
	}
	else if (escolha == 2) {
		custo_porto = 800;
		pacote[encomenda].dias_entrega = 10;
	}
	else{
		custo_porto = 500;
		pacote[encomenda].dias_entrega = 7;
	}
	pacote[encomenda].frete_internacional = custo_porto;
	cout<<fixed<<setprecision(2);
	cout<<"Porto escolhido!"<<endl<<"Valor do frete: "<<pacote[encomenda].frete_internacional<<endl;
	cout<<fixed<<setprecision(0);
    cout << "Escolha a prioridade da carga:"<<endl;
    cout << "1 - Normal"<<endl;
    cout << "2 - Rapida (+10%, -2 dias)"<<endl;
    cout << "3 - Urgente (+25%, prazo reduzido 50%)"<<endl;
    cin >> escolha;
	while(escolha > 3 || escolha < 1){
		cout << "Opcao invalida. Tente novamente." << endl;
		cin>>escolha;
	}	
    if (escolha == 2) {
        pacote[encomenda].frete_internacional += pacote[encomenda].frete_internacional * 0.10;
        pacote[encomenda].dias_entrega = pacote[encomenda].dias_entrega - 2;
        pacote[encomenda].extras = true;
        pacote[encomenda].prioridade = true;
    } else if (escolha == 3) {
        pacote[encomenda].frete_internacional += pacote[encomenda].frete_internacional * 0.25;
        pacote[encomenda].dias_entrega = pacote[encomenda].dias_entrega / 2;
        pacote[encomenda].extras = true;
        pacote[encomenda].prioridade = true;
    }
    cout<<fixed<<setprecision(2);
	cout<<"Custo do Frete Internacional : "<<pacote[encomenda].frete_internacional<<endl;
	cout<<fixed<<setprecision(0);
	cout<<"Data de chegada ao Brasil : "<<pacote[encomenda].dias_entrega<<" dias"<<endl;
	
	
    return ;
}

// ----------------- Fun��o de Seguro (Internacional) -----------------
void seguro(double &valorTotal, int encomenda, PacoteNacional pacote[]) {
    double adicional = valorTotal * 0.05;
    valorTotal += adicional;
    pacote[encomenda].extras = true;
    pacote[encomenda].seguro = true;
}
// ----------------- Fun��o de Cupom -----------------
void cupom(int &encomenda , PacoteNacional pacote[]){
		int escolha;
		int cupom_digitado;
		cout<<"Digite o cupom: ";
		cin>>cupom_digitado;
		for(int i = 0 ; i <= encomenda ; i++){
			if(cupom_digitado == pacote[i].cupom_valido){
	//calculo do cupom
	    		pacote[encomenda].extras = true;
	    		pacote[encomenda].cupom = true;
				cout<<"Cupom encontrado! Aplicando desconto..."<<endl;
				pacote[encomenda].frete_total -= (pacote[encomenda].frete_total/100)*10;
				return;
			}
			else{
				cout<<"Cupom nao encontrado, tentar novamente?"<<endl<<"1 - Sim"<<endl<<"2 - Nao"<<endl;
				cin>>escolha;
				while(escolha != 1 && escolha != 2){
					cout<<"Digite um comando valido!"<<endl<<"1 - Sim"<<endl<<"2 - Nao"<<endl;;
					cin>>escolha;
			    }
				if(escolha == 2) return;				
			}
	   }	
}

// ----------------- Fun��o de Cadastro Nacional -----------------
void CadastroNacional(int &encomenda, PacoteNacional pacote[]) {
	cout<<"-----------------------------------------------"<<endl<<"            Cadastro Nacional           "<<endl<<endl;
    double peso_cubado = pacote[encomenda].volume / 300;
	double peso_final = 0;
	
    if (peso_cubado > pacote[encomenda].peso) peso_final = peso_cubado;
    else peso_final = pacote[encomenda].peso;

	
    double preco_kg;
    if (peso_final <= 50)
        preco_kg = 1.00;
    else if (peso_final <= 100)
        preco_kg = 0.90;
    else if (peso_final <= 200)
        preco_kg = 0.80;
    else
        preco_kg = 0.70;

    double valor_nacional = pacote[encomenda].frete_internacional + (preco_kg * peso_final);
    cout<<fixed<<setprecision(2);
    cout<<"Adicionando custo operacional por Peso x Volume = R$ "<<valor_nacional<<endl;
    cout<<fixed<<setprecision(0);
    int regiao;
    double custo_regiao;

    while (true) {
        cout << "Escolha a regiao de destino:" << endl;
        cout << "1 - Sudeste (R$50 - 3 dias)"<<endl;
        cout << "2 - Sul (R$100 - 5 dias)"<<endl;
        cout << "3 - Centro-Oeste (R$150 - 7 dias)"<<endl;
        cout << "4 - Nordeste (R$200 - 10 dias)"<<endl;
        cout << "5 - Norte (R$250 - 12 dias)"<<endl;
        cin >> regiao;

        if (regiao == 1) { custo_regiao = 50; pacote[encomenda].dias_entrega += 3; break; }
        if (regiao == 2) { custo_regiao = 100; pacote[encomenda].dias_entrega += 5; break; }
        if (regiao == 3) { custo_regiao = 150; pacote[encomenda].dias_entrega += 7; break; }
        if (regiao == 4) { custo_regiao = 200; pacote[encomenda].dias_entrega += 10; break; }
        if (regiao == 5) { custo_regiao = 250; pacote[encomenda].dias_entrega += 12; break; }
        cout << "Opcao invalida. Tente novamente." << endl;
    }

    double valor_total = valor_nacional + custo_regiao;


    pacote[encomenda].frete_total = valor_total;
    cout<<fixed<<setprecision(2);
    cout<<"Valor do Frete total = R$ "<<pacote[encomenda].frete_total<<endl;
    cout<<fixed<<setprecision(0);
    //Seguro
    int escolha;
    cout << "Deseja adicionar seguro? (5% extra)"<< " 1- Sim 2 - Nao"<<endl;
    cin >> escolha;

    if (escolha == 1) {
        seguro(pacote[encomenda].frete_total, encomenda, pacote);
    }
    cout<<fixed<<setprecision(2);
    cout<<"Valor do Frete total = R$ "<<pacote[encomenda].frete_total<<endl;
    cout<<fixed<<setprecision(0);
    //Cupom
	cout<<"Gostaria de adicionar algum cupom?"<<endl<<"1 - Sim"<<endl<<"2 - Nao"<<endl;
				cin>>escolha;
				while(escolha != 1 && escolha != 2){
					cout<<"Digite um comando valido!"<<endl<<"1 - Sim"<<endl<<"2 - Nao"<<endl;
					cin>>escolha;
				}
				if(escolha == 1){ 
					cupom(encomenda, pacote);
				}
    return;
}

// ----------------- Fun��o Principal -----------------
int main() {
    const int MAX_ENCOMENDAS = 100;
    PacoteNacional pacote[MAX_ENCOMENDAS];
    int escolha, encomenda = 0;
//puxei o struct "encomenda" para 'pacote'.
    //cout<<"\033[38;5;27m..............\033[38;5;52m| \033[38;5;130m)\033[38;5;27m............."<<endl<<"..............\033[38;5;52m|   \033[38;5;130m)\033[38;5;27m..........."<<endl<<"..............\033[38;5;52m|     \033[38;5;130m)\033[38;5;27m........."<<endl<<"..............\033[38;5;52m|\033[1;31mPorto\033[0m \033[38;5;130m)\033[38;5;27m........"<<endl<<"..............\033[38;5;52m|  \033[1;31ma\033[0m    \033[38;5;130m)\033[38;5;27m......."<<endl<<"..............\033[38;5;52m|\033[1;31mPorto\033[0m \033[38;5;130m)\033[38;5;27m........"<<endl<<"..............\033[38;5;52m|     \033[38;5;130m)\033[38;5;27m........."<<endl<<"..............\033[38;5;52m|   \033[38;5;130m)\033[38;5;27m..........."<<endl<<"...\033[38;5;52m_|\033[38;5;130m)\033[38;5;52m\033[38;5;27m.."<<endl<<"\033[38;5;17m..\033[38;5;52m<     ___        ___     /\033[38;5;17m.."<<endl<<"...\033[38;5;52m<    |\033[4m0\033[0m\033[38;5;52m\033[38;5;52m|        |\033[4m0\033[0m\033[38;5;52m|    /\033[38;5;17m..."<<endl<<"....\033[38;5;52m<\033[4mOnde o Mundo Embarca\033[0m\033[38;5;52m/\033[38;5;17m...."<<endl<<"..............................\033[0m"<<endl;
    cout<<"Bem-vindo ao sistema de cadastro de encomenda da Porto-a-Porto!"<<endl;
	do{
   	    pacote[encomenda].extras = false;
    	pacote[encomenda].seguro = false;
    	pacote[encomenda].cupom = false;
    	pacote[encomenda].prioridade = false;
        cout<<"   Escolha uma das opcoes: "<<endl<<"   1 - Cadastro Intercontinental"<<endl<<"   2 - Cadastro Nacional"<<endl<<"   3 - Sair"<<endl;
        cin>>escolha;
        switch(escolha){
            case 1:	
				cout << "Digite o peso (quilogramas): ";
    			cin >> pacote[encomenda].peso;
    			cout << "Digite o volume (metros cubicos): ";
    			cin >> pacote[encomenda].volume;
				//puxar Fun��o Internacional;
    			CadastroInternacional(encomenda, pacote);
				//Puxar Fun��o Nacional
 				CadastroNacional(encomenda, pacote);
            break;
            case 2:
   	   	//puxar fun��o CadastroNacional();
				cout << "Digite o peso (quilogramas): ";
    			cin >> pacote[encomenda].peso;
    			cout << "Digite o volume (metros cubicos): ";
    			cin >> pacote[encomenda].volume;

            	CadastroNacional(encomenda, pacote);
            break;
            case 3:
    	//termino do programa.
    			cout<<"Porto-a-Porto, onde o mundo embarca!";
  			return 0; 
		}
		//gera��o de cupom por finaliza��o de pedido
		cout<<"A Porto-a-Porto agradece a preferencia e disponibiliza um cupom de 10% de desconto para futuros cadastros"<<endl;
		pacote[encomenda].cupom_valido = (10000+rand());
	//Extras
        if(pacote[encomenda].extras == true) cout<<"Servicos adicionais:"<<endl;
		if(pacote[encomenda].prioridade == true) cout<<" - Prioridade"<<endl;
		if(pacote[encomenda].seguro == true) cout<<" - Seguro"<<endl;
		if(pacote[encomenda].cupom == true) cout<<" - Cupom"<<endl;
	//Resumo Final	
    cout << fixed << setprecision(2);
    cout << "Resumo final:\n";
    cout << "Frete total: R$ " << pacote[encomenda].frete_total << endl;
    cout << "Entrega em: " << pacote[encomenda].dias_entrega << " dias"<<endl;
    cout << "Cupom gerado: " << pacote[encomenda].cupom_valido << endl;
 		cout<<"Cadastro Finalizado!"<<endl<<endl;
		encomenda++;
        }while(true);
}