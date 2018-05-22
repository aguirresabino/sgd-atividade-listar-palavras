#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>

bool InTag(char c)
{
    static int bracket = 0;
    switch (c)
    {
    case '<':
        ++bracket;
        break;
    case '>':
        --bracket;
        return true;
    }
    return bracket > 0;
}

int main(int argc, char const *argv[])
{
	std::string url;
	std::cout << "Insira uma URL" << std::endl;
	std::cin >> url;

	std::string comando("curl " + url + " > pagina.txt");

	system(comando.c_str());

	//abrindo o arquivo
	std::ifstream ob_read("pagina.txt");
	std::ofstream ob_write("saida.txt");

	if(!ob_read.is_open() || !ob_write.is_open()){
		ob_read.clear();
		ob_write.clear();
	}

	std::string palavra;
	
	std::cout << "Imprimindo quebra de linha por string" << std::endl;
	std::cout << "========================================================" << std::endl;
	while(!ob_read.eof()){
		
		ob_read >> palavra; //quebro uma string ao encontrar um caractere de espaco

		std::ostringstream oss; //stream de saída
    	std::remove_copy_if(palavra.begin(), palavra.end(), std::ostream_iterator<char>(oss), InTag);

    	if(oss.str().size() > 0){
    		//std::cout << oss.str() << std::endl;
    		ob_write << oss.str() << std::endl;
    	}
	}

	ob_read.close();
	ob_write.close();

	return 0;

	//std::ofstream ob_write("pagina.txt", std::ios::out | std::ios::trunc);

	// if(ob_write.fail()){
	// 	std::cout << "Error na leitura do arquivo" << std::endl;
	// }
	// if(ob_write.is_open()){
	// 	ob_write << system(comando.c_str()) << std::endl;
	// 	ob_write.close();
	// }
}