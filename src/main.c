/*******************************************************************************
 *  Trabalho de Estrutura de Dados I
 *  Periodo: 2024.2
 *  Alunos:
 *      - Bruno Costa Barreto (202310309411)
 *      - Otávio Pessanha Costa (202310310611)
 *      - João Pedro Meirelles Silva (202410302211)
*******************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#if !defined(ERROR_ALLOC_LIST_VALUE) && !defined(ERROR_ALLOC_LIST_TYPE)
#define ERROR_ALLOC_LIST_TYPE ((void*)1)
#define ERROR_ALLOC_LIST_VALUE 255
#endif

#ifndef LIMPAR_TELA
#ifdef _WIN32
#define LIMPAR_TELA_FUNC do { system("cls"); } while (0)
#else
#define LIMPAR_TELA_FUNC do { system("clear"); } while (0)
#endif
#endif

typedef struct data_s {
    unsigned char dia;
    unsigned char mes;
    unsigned long ano;
} data_t;

typedef struct telefonica_s {
    data_t data;
    char* nome;
    char* telefone;
    char* email;
} telefonica_t;

typedef struct elemento_lista_s {
    telefonica_t item;
    /*  Usamos struct elemento_lista_s pois o tipo elemento_lista_t não está
        totalmente definido nesse momento no código */
    struct elemento_lista_s *proximo;
    struct elemento_lista_s *anterior;
} elemento_lista_t;

typedef struct lista_s {
    elemento_lista_t* inicio;
    elemento_lista_t* final;
    unsigned long tamanho;
} lista_t;

char* domain_extensions[255] = {
    ".com", ".net", ".org", ".edu", ".gov", ".co", ".us", ".br", ".mx", 
    ".ca", ".uk", ".au", ".fr", ".de", ".ru", ".in", ".it", ".jp", ".cn", 
    ".za", ".tv", ".io", ".info", ".me", ".tech", ".app", ".dev", ".ai", 
    ".biz", ".mobi", ".name", ".pro", ".xyz", ".website", ".space", ".club", 
    ".store", ".online", ".top", ".news", ".today", ".design", ".agency", 
    ".digital", ".solutions", ".media", ".zone", ".center", ".world", 
    ".tools", ".life", ".network", ".web", ".expert", ".click", ".global", 
    ".fun", ".site", ".tech", ".cloud", ".support", ".help", ".shop", 
    ".blog", ".live", ".systems", ".company", ".works", ".city", ".events", 
    ".finance", ".services", ".law", ".bio", ".cafe", ".studio", ".ventures", 
    ".graphics", ".email", ".construction", ".finance", ".management", 
    ".recipes", ".social", ".tours", ".vacations", ".watch", ".community", 
    ".fitness", ".photos", ".house", ".rentals", ".properties", ".ltd", 
    ".ventures", ".enterprises", ".capital", ".holdings", ".investments", 
    ".partners", ".international", ".srl", ".limited", ".plc", ".gmbh", 
    ".llc", ".srl.br", ".gov.br", ".edu.br", ".com.br", ".net.br", ".org.br", 
    ".tur.br", ".com.mx", ".net.mx", ".org.mx", ".edu.mx", ".gov.mx", 
    ".co.uk", ".ac.uk", ".gov.uk", ".org.uk", ".edu.au", ".co.za", ".org.za", 
    ".net.za", ".co.in", ".net.in", ".org.in", ".edu.in", ".gov.in", ".co.jp", 
    ".or.jp", ".ne.jp", ".ac.jp", ".gov.jp", ".com.sg", ".net.sg", ".org.sg", 
    ".gov.sg", ".edu.sg", ".com.hk", ".org.hk", ".edu.hk", ".gov.hk", 
    ".net.hk", ".com.ph", ".net.ph", ".gov.ph", ".org.ph", ".edu.ph", 
    ".com.vn", ".edu.vn", ".gov.vn", ".org.vn", ".com.my", ".net.my", 
    ".org.my", ".edu.my", ".gov.my", ".id", ".pk", ".lk", ".com.tr", 
    ".com.sa", ".gov.sa", ".net.sa", ".com.eg", ".gov.eg", ".org.eg", 
    ".edu.eg", ".int", ".tel", ".mobi", ".archi", ".art", ".asia", ".associates", 
    ".auction", ".autos", ".bible", ".boutique", ".builders", ".camp", ".ceo", 
    ".charity", ".christmas", ".church", ".city", ".claims", ".cleaning", 
    ".clinic", ".college", ".community", ".computer", ".consulting", 
    ".contractors", ".cool", ".cruise", ".dance", ".dating", ".dental", 
    ".diet", ".directory", ".dog", ".eco", ".energy", ".engineering", ".exchange", 
    ".family", ".farm", ".fashion", ".foundation", ".furniture", ".gallery", 
    ".games", ".gives", ".golf", ".green", ".guitars", ".healthcare", 
    ".holiday", ".homes", ".horse", ".insurance", ".kitchen", ".limo", 
    ".maison", ".marketing", ".memorial", ".money", ".partners", ".photos", 
    ".place", ".plumbing", ".productions", ".repair", ".run", ".sale", 
    ".security", ".services", ".show", ".solar", ".storage", ".studio", 
    ".style", ".supplies", ".surgery", ".tax", ".tennis", ".theater", ".tires", 
    ".today", ".toys", ".training"
};

char* domain_names[255] = {
    "example", "sample", "demo", "testsite", "mywebsite", "webapp", "onlinehub", 
    "techworld", "codebase", "projecthub", "sitebuilder", "cloudplatform", 
    "websolution", "internetservices", "myportfolio", "personalblog", "devcorner", 
    "webdesign", "creativecorner", "enterprisenet", "digitalagency", "mediahub", 
    "techtalk", "connectnow", "solutionbase", "yourbusiness", "startuplabs", 
    "thefuture", "netconnect", "techsupport", "worldwideweb", "brandworld", 
    "ideahub", "globalaccess", "mycompany", "webportal", "quicklinks", 
    "launchsite", "visionweb", "innovationhub", "connectme", "onlinemarket", 
    "socialplace", "creativecode", "trendspot", "futuretech", "dreamworks", 
    "webfactory", "cloudmanager", "portfoliosite", "mybusiness", "digitalport", 
    "startupconnect", "solutionworks", "techexperts", "webgenius", "dreamspot", 
    "marketplace", "geniuslabs", "mediazone", "trendnetwork", "urbanlink", 
    "mycloud", "onlinespace", "digitalflow", "worldofideas", "buildhub", 
    "creativeminds", "techworldhub", "theinfluence", "projectportal", 
    "mindnetwork", "solutionfactory", "infoweb", "instantmarket", "futureidea", 
    "cloudlabs", "mediaaccess", "growthnetwork", "innovators", "futurelink", 
    "virtualconnect", "enterpriselink", "visionary", "ideacorner", "socialzone", 
    "websupport", "businessguide", "webradio", "contentmakers", "yourservices", 
    "cloudvision", "digitalinnovate", "ourweb", "projectgrid", "devlabs", 
    "medialink", "startupcity", "infiniteideas", "digitalagencyhub", 
    "webengine", "thewebapp", "innovatorshub", "creativework", "nextgenweb", 
    "techinsight", "connectionhub", "launchpoint", "webconnect", "mysolutions", 
    "futureconnect", "dreambase", "entrepreneurnetwork", "digitalsphere", 
    "socialworld", "openmind", "solutionlink", "worldoftech", "techwave", 
    "newgenweb", "discover", "networklabs", "cityconnect", "trendmakers", 
    "designerspace", "globalweb", "bizconnect", "ideaexchange", "infinitemedia", 
    "knowledgehub", "nextlevel", "mindplace", "cloudwork", "techhive", 
    "brandcenter", "linknow", "onlineworld", "futurescope", "webcity", 
    "creativelink", "mybusinesshub", "projectconnect", "dreamspotlight", 
    "solutionzone", "thinklab", "digitalplace", "webservices", "mylab", 
    "futurelabs", "teamwork", "socialfactory", "ourspace", "connectsphere", 
    "codeinnovators", "businessplace", "ideaengine", "networksphere", 
    "mindhub", "projectnetwork", "designhub", "digitalinspire", "techconnect", 
    "launchhub", "netgen", "dreamlab", "digitalhub", "visionlab", "projectideas", 
    "businessvision", "nextgenideas", "creativeworks", "globalmarket", 
    "ideasphere", "startuplink", "webtechnology", "digitalinsights", 
    "teamhub", "solutioncenter", "networkpro", "connectlab", "digitalfactory", 
    "socialmedia", "growthideas", "brandhub", "solutionlab", "urbanmedia", 
    "webconnectors", "netideas", "startupzone", "idealink", "nextweb", 
    "myhub", "urbanideas", "thetechlab", "createhub", "networkfactory", 
    "urbanconnect", "webinnovators", "citymedia", "dreamlabs", "brandzone", 
    "projectfactory", "myportfoliohub", "bizmedia", "thinkconnect", 
    "marketinsights", "digitalsolutions", "startupfactory", "visionnetwork", 
    "enterprisetech", "bizlab", "marketpro", "geniusideas", "growthlab", 
    "socialgenius", "launchnetwork", "webexchange", "connectlink", "mediacenter", 
    "projectlink", "trendlabs", "thinkfactory", "visionfactory", "urbanhub", 
    "nextmarket", "globalideas", "brandworks", "visionideas", "marketcenter", 
    "worldofbusiness", "citysphere", "solutiongenius", "launchconnect", 
    "cloudlabs", "creativevision", "mygenius", "ideaweb", "projectpro", 
    "startupworld", "digitalhubnet", "bizconnect", "connectfactory", 
    "launchzone", "inspirenetwork", "techworks", "solutionhub", "innovationspace", 
    "bizidea", "futurevision", "brandfactory", "dreamzone", "growthfactory", 
    "mindnetwork", "digitalweb", "mydreams"
};

char* last_names[255] = {
    "Castillo", "Brown", "Lee", "Wilson", "Green", "Gonzalez", "Garcia", 
    "Jones", "Smith", "Johnson", "Rodriguez", "Martinez", "Perez", "Taylor", 
    "Anderson", "Thomas", "Hernandez", "Moore", "Martin", "Lopez", "Gomez", 
    "White", "Diaz", "Clark", "Jackson", "Miller", "Lewis", "King", "Torres", 
    "Martinez", "Allen", "Wright", "Sanchez", "Rivera", "Long", "Morris", 
    "Ortiz", "Carter", "Young", "Flores", "Gonzalez", "Alexander", "James", 
    "Evans", "Thompson", "Sanders", "Gray", "Green", "Hill", "Torres", "Howard", 
    "Bailey", "Nelson", "Hall", "Cooper", "Barnes", "Turner", "Mitchell", 
    "Ramirez", "Edwards", "Brooks", "Powell", "Diaz", "Hughes", "Butler", 
    "Richardson", "Hernandez", "Clark", "Sanchez", "Roberts", "Patterson", 
    "Reyes", "Ramos", "Reyes", "Adams", "Stewart", "Peterson", "Garcia", 
    "Campbell", "Morales", "Phillips", "Rivera", "Richardson", "Flores", 
    "Hughes", "Parker", "Allen", "Bell", "Cruz", "Price", "Walker", "Barnes", 
    "Rivera", "Powell", "Butler", "Reyes", "Hughes", "Ortiz", "Gray", "Flores", 
    "Howard", "Morris", "Russell", "Garcia", "Ramirez", "James", "Diaz", "Garcia", 
    "Torres", "Gray", "Russell", "Diaz", "Garcia", "Perez", "Reyes", "Morris", 
    "Hughes", "Cooper", "Howard", "Ramos", "Russell", "Bailey", "Cruz", "Hughes", 
    "Garcia", "Sanders", "Howard", "James", "Flores", "Garcia", "Walker", 
    "Lopez", "Gomez", "Reyes", "Ortiz", "White", "Morris", "Diaz", "Rivera", 
    "Jackson", "Nelson", "King", "Howard", "Green", "Adams", "Gray", "Robinson", 
    "Perez", "Diaz", "Cruz", "Jackson", "Green", "Sanders", "Garcia", "Miller", 
    "Thompson", "Ramos", "Rivera", "Nelson", "Howard", "Patterson", "Cruz", 
    "Mitchell", "Edwards", "Diaz", "Rivera", "Ramirez", "Gomez", "Diaz", 
    "Martinez", "Richardson", "Cruz", "Garcia", "Martinez", "Rodriguez", 
    "Diaz", "Garcia", "Ramirez", "Ramos", "Rivera", "James", "Howard", "Hernandez", 
    "Martinez", "Gray", "Rivera", "Ramos", "Thompson", "Mitchell", "Nelson", 
    "Richardson", "Lopez", "Garcia", "Ramirez", "Perez", "Ramirez", "Martinez", 
    "Richardson", "Garcia", "Nelson", "Miller", "Howard", "Morris", "Perez", 
    "Garcia", "Thompson", "Gray", "Russell", "Ramirez", "Walker", "Howard", 
    "Mitchell", "Rivera", "Perez", "Gray", "Ramirez", "Russell", "Flores", 
    "Walker", "Adams", "Nelson", "Mitchell", "Walker", "Jackson", "James", 
    "Nelson", "Ramirez", "Ortiz", "Jackson", "Rivera", "Nelson", "Garcia", 
    "Howard", "Ramirez", "Ortiz", "Nelson", "Gray", "Howard"
};

char* surnames[255] = {
    "Souza", "Smith", "Lopez", "Johnson", "Silva", "Martinez", "Gomes", "Brown", 
    "Santos", "Taylor", "Ferreira", "Anderson", "Ribeiro", "Thomas", "Pereira", 
    "Jackson", "Costa", "White", "Melo", "Harris", "Rocha", "Martin", "Oliveira", 
    "Garcia", "Freitas", "Thompson", "Araujo", "Clark", "Batista", "Walker", 
    "Nunes", "Robinson", "Cavalcanti", "Young", "Machado", "Allen", "Campos", 
    "King", "Monteiro", "Wright", "Correia", "Lopez", "Moura", "Scott", "Alves", 
    "Torres", "Dias", "Hill", "Teixeira", "Green", "Andrade", "Adams", "Almeida", 
    "Baker", "Mendes", "Gonzalez", "Ramos", "Carter", "Duarte", "Mitchell", 
    "Reis", "Perez", "Cardoso", "Roberts", "Tavares", "Phillips", "Braga", 
    "Campbell", "Moreira", "Evans", "Xavier", "Turner", "Farias", "Rodriguez", 
    "Moraes", "Parker", "Sousa", "Collins", "Lima", "Edwards", "Henrique", 
    "Stewart", "Medeiros", "Flores", "Barros", "Morris", "Aguiar", "Nguyen", 
    "Queiroz", "Rivera", "Vasconcelos", "Cook", "Bezerra", "Morgan", "Siqueira", 
    "Bell", "Fonseca", "Murphy", "Valente", "Bailey", "Serra", "Cooper", "Rezende", 
    "Richardson", "Brito", "Cox", "Magalhães", "Howard", "Amaral", "Ward", 
    "Menezes", "Peterson", "Miranda", "Gray", "Cunha", "Ramirez", "Figueiredo", 
    "James", "Furtado", "Watson", "Pinto", "Brooks", "Mendes", "Sanders", 
    "Falcão", "Price", "Ramos", "Bennett", "Carvalho", "Wood", "Macedo", 
    "Barnes", "Leal", "Ross", "Sales", "Henderson", "Paiva", "Coleman", 
    "Neves", "Jenkins", "Oliveira", "Perry", "Teles", "Powell", "Nogueira", 
    "Long", "Lopes", "Patterson", "Assis", "Hughes", "Galvão", "Flores", 
    "Rocha", "Cruz", "Gonçalves", "Alexander", "Viana", "Russell", "Franco", 
    "Griffin", "Pedrosa", "Diaz", "Castro", "Hayes", "Campos", "Myers", 
    "Simões", "Ford", "Becker", "Schmidt", "Ferreira", "Stephens", "Soares", 
    "Watts", "Marques", "Butler", "Castro", "Barnes", "Pinto", "Parker", 
    "Azevedo", "Collins", "Santos", "Moore", "Vidal", "Morales", "Cunha", 
    "Bryant", "Valadares", "Perez", "César", "Walker", "Beltrán", "Morgan", 
    "Bastos", "Wilson", "Sousa", "Sullivan", "Pires", "Lewis", "Alves", 
    "Evans", "Duarte", "Howard", "Novaes", "Murphy", "Araújo", "Lee", 
    "Macedo", "Hernández", "Lima", "Bennett", "Prado", "Cruz", "Esteves", 
    "Hicks", "Vieira", "Fox", "Nóbrega", "Graham", "Mota", "Payne", "Serafim", 
    "Ramirez", "Amaral", "Gomez", "Rocha", "Gonzalez", "Oliva", "Jenkins", 
    "Arce", "Fernandez", "Silva", "Levine", "Zamora", "Paz", "Arias", "Herrera", 
    "Rojo", "Fiorini", "Solano", "Betancourt", "Meza", "Amaya", "Cordero", 
    "Sosa", "Quiroga", "Durán", "Paredes", "Alba", "Alvarado", "Gamboa", 
    "Chavarria", "Montoya", "Aguero"
};

char* second_names[255] = {
    "Oliveira", "Rodríguez", "Silva", "Martínez", "Almeida", "González", "Santos", 
    "Pérez", "Lima", "García", "Ferreira", "Sánchez", "Costa", "Flores", "Ramos", 
    "Moreno", "Melo", "Blanco", "Reyes", "Sousa", "Morales", "Gomes", "Ortega", 
    "Nunes", "Ortiz", "Moura", "Guerrero", "Pereira", "Mendoza", "Batista", "Castillo", 
    "Carvalho", "Vega", "Ribeiro", "Cruz", "Martins", "Herrera", "Campos", "Jiménez", 
    "Rocha", "Valdez", "Pinto", "Rivera", "Viana", "Salazar", "Monteiro", "Bautista", 
    "Mendes", "Romero", "Correia", "Cano", "Vieira", "Rojas", "Miranda", "Pacheco", 
    "Andrade", "Ochoa", "Nogueira", "Espinoza", "Barbosa", "Montes", "Teixeira", 
    "Aguilar", "Barros", "Chávez", "Alves", "Ramírez", "Cunha", "Acosta", "Freitas", 
    "Sandoval", "Farias", "Quintero", "Cardoso", "Ponce", "Barreto", "Soto", "Duarte", 
    "Navarro", "Queiroz", "Ramos", "Guzmán", "Maciel", "Morales", "Cavalcante", 
    "Iglesias", "Neves", "Barrera", "Castro", "Galindo", "Macedo", "Villarreal", 
    "Tavares", "Morales", "Cavalcanti", "Escobar", "Barroso", "Pineda", "Rangel", 
    "Salinas", "Lorenzo", "Azevedo", "Villanueva", "Machado", "Peña", "Díaz", 
    "Rico", "Olmos", "Valdivia", "Figueiredo", "Ventura", "Godoy", "Vergara", 
    "Paniagua", "Arruda", "Paz", "Quintana", "Santana", "Castañeda", "Araújo", 
    "Ramón", "Oliveira", "Bravo", "Soares", "León", "Aranda", "Carvalho", "Medina", 
    "Padilla", "Mejia", "Resende", "Arévalo", "Santiago", "Ferraz", "Camacho", 
    "Moraes", "Padua", "Villalobos", "Pardo", "Cordero", "Medrano", "Correa", 
    "Piedra", "Avila", "Torres", "Villanueva", "Escamilla", "Renteria", "Guevara", 
    "Meneses", "Vasquez", "Lucero", "Castaneda", "Bernal", "Chaparro", "Bermudez", 
    "Alarcon", "Valenzuela", "Benitez", "Peralta", "Mendoza", "Martinez", "Barron", 
    "Arias", "Ibanez", "Pizarro", "Lagos", "Muñoz", "Orozco", "Nieto", "Palacios", 
    "Suarez", "Osorio", "Tirado", "Marin", "Fleming", "Ortigoza", "Villegas", 
    "Torrico", "Serrano", "Rojo", "Caro", "Sotelo", "Gálvez", "Fuentes", "Pérez", 
    "Olmedo", "Bello", "Roque", "Carvajal", "Mayorga", "Jara", "Vera", "Espinosa", 
    "Quiroz", "Esparza", "Urbina", "Aguila", "Rivera", "Zamora", "Falcão", 
    "Maldonado", "Baeza", "Zapata", "Ramos", "Sarmiento", "Lobos", "Zárate", 
    "Nuñez", "Leal", "Córdova", "Mora", "Becerra", "Cáceres", "Rios", "Aguirre", 
    "Ballesteros", "Martins", "Ramirez", "Faria", "Rodrigues", "Romero", "Gomez", 
    "Lira", "Rubio", "Montiel", "Gutierrez", "Santamaría", "Armas", "Hidalgo", 
    "Cordero", "Zavala", "Delgado", "López", "Peña", "Salas", "Barajas", "Ulloa", 
    "Farfán", "Yañez", "Terán", "Guajardo", "Pineda", "Murillo", "Hernandez", 
    "Carrillo", "Arias", "Salazar", "Guerrero", "Cruz", "Méndez", "Zúñiga", "Bustos", 
    "Caro", "Figueroa"
};

char* first_names[255] = {
    "Miguel", "Sophia", "Mateo", "Emma", "Lucas", "Isabella", "Gabriel", "Sofia",
    "Arthur", "Julia", "Davi", "Mia", "Pedro", "Valentina", "Enzo", "Elena", 
    "Heitor", "Giovanna", "Samuel", "Victoria", "Bernardo", "Antonella", 
    "Benjamin", "Isabela", "Joaquim", "Ariana", "Leonardo", "Diana", "Liam", 
    "Renata", "Daniel", "Luisa", "Jorge", "Ana", "Eduardo", "Fernanda", 
    "Matheus", "Camila", "Rodrigo", "Gustavo", "Felipe", "Ricardo", "Fernando", 
    "Maria", "Raul", "Luis", "Adriana", "Santiago", "Paola", "Thiago", "Gabriela",
    "Juan", "Olivia", "Rafael", "Beatriz", "Tomás", "Nicole", "Manuel", "Sabrina",
    "Carlos", "Luciana", "Bruno", "Leticia", "Victor", "Laura", "Pablo", "Elisa",
    "Alejandro", "Andrea", "Sergio", "Lorena", "Mario", "Rosa", "David", "Carolina",
    "Alfredo", "Helena", "Ricardo", "Michele", "Alexandre", "Patricia", "Francisco",
    "Sandra", "André", "Cristina", "Erick", "Mariana", "Hugo", "Daniela", "Alberto",
    "Brenda", "Alonso", "Simone", "Rogério", "Alexis", "Marcos", "Rafael", "Monica",
    "Edson", "Alejandra", "Antonio", "Silvia", "Diego", "Júlia", "Alan", "Carmen",
    "Emerson", "Aline", "Humberto", "Fabiola", "Nicolas", "Carina", "Martin", 
    "Susana", "Julián", "Carla", "Everton", "Débora", "Lucas", "Paula", "João",
    "Angel", "Caio", "Mário", "Marlon", "Felipe", "Enrique", "César", "Alejandro",
    "Anderson", "José", "Vinícius", "Lucia", "Jean", "Geraldo", "Andrés", "Jéssica",
    "Roberto", "Celina", "Ricardo", "Adriana", "Igor", "Maurício", "Juliano", 
    "Martín", "Flavio", "Susana", "Luís", "Monica", "Ramon", "Julieta", "Mario",
    "Eliana", "Adriano", "Iván", "Renan", "Emilio", "Esteban", "Cristina", "Flávia",
    "Irving", "Sonia", "Alessandro", "Pedro", "Raquel", "Margarita", "Eliseo",
    "Regina", "Fernando", "Victoria", "Bruno", "Aline", "Bryan", "Josefa", "Juan",
    "Sara", "Nelson", "Diana", "Rodrigo", "Angelica", "Adriel", "Marisol", 
    "Cecilia", "Liliana", "Beto", "Karla", "Raúl", "Ismael", "Emilio", "Jacqueline",
    "Ulises", "Marta", "Ximena", "Pilar", "Jimena", "Violeta", "León", "Roberta",
    "Rodrigo", "Lilian", "Alex", "Gustavo", "Ignacio", "Lourdes", "Valerio", 
    "Flor", "Sebastián", "Rocío", "René", "Mariela", "Héctor", "César", "Alfonso",
    "Claudia", "Moisés", "Viviana", "Leonor", "Elias", "Alondra", "Benjamín", 
    "Aurora", "Ernesto", "Estela", "Ramón", "Hortensia", "Facundo", "Sol", 
    "Armando", "Cristobal", "Eduarda", "Eduardo", "Milena", "Flora", "Oscar", 
    "Isabela", "Emanuel", "Isadora", "David", "Inês", "Antônio", "Elisa", 
    "Ronaldo", "Rebeca", "Valentín", "Angélica", "Martina", "Paloma", "Octavio", 
    "Noelia", "Camilo", "Tania", "Gabriela", "Luana", "Eugenio", "Dayana"
};



void init(void);
lista_t* criar_lista(void);
void exibir_lista(lista_t* lista, unsigned char flags);
void menu_principal(void);
void print_input_box(unsigned long comprimento);
int snprintf(char *buffer, size_t buf_size, const char *format, ...);
int main(void);

char** generate_name(void);
char* generate_email(char** name);
char* generate_phone(void);
data_t generate_date(void);
telefonica_t generate_entry(void);


int snprintf(char *buffer, unsigned long buf_size, const char *format, ...) {
    int n;
    va_list args;
    if (buf_size == 0) {
        return 0;
    }

    va_start(args, format);
    n = vsprintf(buffer, format, args);
    va_end(args);

    if (n >= (int)buf_size) {
        buffer[buf_size - 1] = '\0';
        return buf_size - 1;
    }
    return n;
}

elemento_lista_t* criar_elemento(const telefonica_t* item) {
    elemento_lista_t* novo = (elemento_lista_t*)malloc(sizeof(elemento_lista_t));
    if (novo != NULL) {
        novo->item = *item;
        novo->proximo = NULL;
        novo->anterior = NULL;
    }
    return novo;
}

int lista_adicionar_inicio(lista_t* lista, const telefonica_t* item) {
    elemento_lista_t* novo = criar_elemento(item);
    if (novo == NULL) return 0;

    novo->proximo = lista->inicio;

    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
    } else {
        lista->final = novo;
    }

    lista->inicio = novo;
    lista->tamanho++;
    return 1;
}

int lista_adicionar_final(lista_t* lista, const telefonica_t* item) {
    elemento_lista_t* novo = criar_elemento(item);
    if (novo == NULL) return 0;

    novo->anterior = lista->final;

    if (lista->final != NULL) {
        lista->final->proximo = novo;
    } else {
        lista->inicio = novo;
    }

    lista->final = novo;
    lista->tamanho++;
    return 1;
}

int lista_adicionar_em(lista_t* lista, const telefonica_t* item, unsigned long index) {
    elemento_lista_t* novo;
    elemento_lista_t* atual;
    unsigned long i;

    if (index > lista->tamanho) return 0;

    if (index == 0) return lista_adicionar_inicio(lista, item);
    if (index == lista->tamanho) return lista_adicionar_final(lista, item);

    novo = criar_elemento(item);
    if (novo == NULL) return 0;

    atual = lista->inicio;
    for (i = 0; i < index - 1; i++) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    novo->anterior = atual;

    if (atual->proximo != NULL) {
        atual->proximo->anterior = novo;
    }

    atual->proximo = novo;
    lista->tamanho++;
    return 1;
}


char** generate_name(void) {
    char **fullname = (char**) malloc(4 * sizeof(char*));
    if (fullname == NULL) {
        return NULL;
    }

    fullname[0] = first_names[rand() % 255];
    fullname[1] = second_names[rand() % 255];
    fullname[2] = surnames[rand() % 255];
    fullname[3] = last_names[rand() % 255];

    return fullname;
}

char* generate_email(char** name) {
    static char* email;
    char *first = name[0];
    char *surname = name[2];
    char *domain = domain_names[rand() % 255];
    char *extension = domain_extensions[rand() % 255];

    snprintf(email, sizeof(email), "%s.%s@%s.%s", first, surname, domain, extension);
    return email;
}


telefonica_t generate_entry(void) {
    telefonica_t entry;
    char **nome_raw;
    char *nome;

    nome_raw = generate_name();
    nome = (char*) malloc(sizeof(nome_raw));
    if (nome == NULL) {
        free(nome_raw);
    }

    snprintf(nome, sizeof(nome), "%s %s %s %s", nome_raw[0], nome_raw[1], nome_raw[2], nome_raw[3]);

    entry.nome = nome;
    entry.telefone = generate_phone();
    entry.email = generate_email(nome_raw);
    entry.data = generate_date();

    free(nome_raw);

    return entry;
}

void init(void) {
    srand((unsigned) time(NULL));
}

char* generate_phone(void) {
    static char phone[21];
    snprintf(phone, sizeof(phone), "+%02d (%02d) %d-%04d-%04d",
             rand() % 100, rand() % 100, rand() % 10, rand() % 10000, rand() % 10000);
    return phone;
}

data_t generate_date(void) {
    data_t date;
    date.ano = 1900 + (rand() % 125);
    date.mes = 1 + (rand() % 12);

    switch (date.mes) {
        case 4: case 6: case 9: case 11: date.dia = 1 + (rand() % 30); break;
        case 2: date.dia = 1 + (rand() % 28); break;
        default: date.dia = 1 + (rand() % 31); break;
    }
    return date;
}


void exibir_item_lista(int index, telefonica_t* entry, unsigned char flags) {
    unsigned long i;
    unsigned long nome_len   = strlen(entry->nome);
    char* nome_upper = (char*)malloc(nome_len + 1);

    if (nome_upper == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (i = 0; i < nome_len; i++) {
        nome_upper[i] = (char)toupper(entry->nome[i]);
    }
    nome_upper[nome_len] = '\0';


    if ((flags & (1 << 0)) != 0) {
        printf("█▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
        printf("█  INDICE    █ %-60d█\n", index);
        printf("█            █%61s█\n", " ");
    }

    if ((flags & (1 << 1)) != 0) {
        printf("█▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
        printf("█  ENDEREÇO  █ %-60p█\n", (void*)entry);
        printf("█            █%61s█\n", " ");
    }

    printf("█▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
    printf("█  NOME      █ %-60s█\n", nome_upper);
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");

    printf("█            █%61s█\n", " ");
    printf("█  TELEFONE  █ %-60s█\n", entry->telefone);
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
    printf("█            █%61s█\n", " ");
    printf("█  EMAIL     █ %-60s█\n", entry->email);
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");
    printf("█            █%61s█\n", " ");
    printf("█  DATA      █ %02d/%02d/%04lu                                              █\n",
           entry->data.dia, entry->data.mes, entry->data.ano);
    printf("█▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");

    free(nome_upper);

}

lista_t* criar_lista(void) {
    lista_t* lista = (lista_t*)calloc(1, sizeof(lista_t));
    if (!lista) {
        fprintf(stderr, "Falha ao alocar espaço para lista\n");
        return ERROR_ALLOC_LIST_TYPE;
    }

    lista->inicio = NULL;
    lista->final = NULL;
    lista->tamanho = 0;
    return lista;
}

void print_input_box(unsigned long comprimento) {
    unsigned long i;

    printf("█");
    for (i = 0; i < comprimento - 2; i++) printf("▀");
    printf("█\n");

    printf("█ >");
    for (i = 0; i < comprimento - 4; i++) printf(" ");
    printf("█\n");

    printf("█");
    for (i = 0; i < comprimento - 2; i++) printf("▄");
    printf("█\n");

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    
    if (hConsole != INVALID_HANDLE_VALUE && GetConsoleMode(hConsole, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
    }

    COORD coord = {4, 2};
    SetConsoleCursorPosition(hConsole, coord);
#else
    printf("\033[A\033[A\033[C\033[C\033[C\033[C");
#endif
}

void menu_principal(void) {
    unsigned char escolha_geral = 0;
    unsigned char escolha_adicionar = 0;
    unsigned char escolha_remover = 0;
    unsigned char escolha_config_exibicao = 0;
    unsigned char config_exibicao = 0;
    do {
        LIMPAR_TELA_FUNC;

        switch (escolha_geral) {
            case 2:
                do {
                    switch (escolha_adicionar) {
                        case 0:
                            break;
                        default:
                            printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                            printf("█                                OPÇÃO INVÁLIDA                                █\n");
                            printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                            break;
                    }

                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                              SUB-MENU ADICIONAR                              █\n");
                    printf("█──────────────────────────────────────────────────────────────────────────────█\n");
                    printf("█                                                                              █\n");
                    printf("█ [1] - ADICIONAR AO INICIO                                                    █\n");
                    printf("█ [2] - ADICIONAR AO FINAL                                                     █\n");
                    printf("█ [3] - ADICIONAR EM POSIÇÃO                                                   █\n");
                    printf("█ [0] - VOLTAR                                                                 █\n");
                    printf("█                                                                              █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    print_input_box(80);
                    scanf("%hhu", &escolha_adicionar);
                    printf("\n");
                }while (escolha_adicionar != 0);
                break;
            case 3:
                do {
                    switch (escolha_remover) {
                        case 0:
                            break;
                        default:
                            printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                            printf("█                                OPÇÃO INVÁLIDA                                █\n");
                            printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                            break;
                    }

                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                               SUB-MENU REMOVER                               █\n");
                    printf("█──────────────────────────────────────────────────────────────────────────────█\n");
                    printf("█                                                                              █\n");
                    printf("█ [1] - REMOVER DO INICIO                                                      █\n");
                    printf("█ [2] - REMOVER DO FINAL                                                       █\n");
                    printf("█ [3] - REMOVER DA POSIÇÃO                                                     █\n");
                    printf("█ [0] - VOLTAR                                                                 █\n");
                    printf("█                                                                              █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    print_input_box(80);
                    scanf("%hhu", &escolha_remover);
                    printf("\n");
                }while (escolha_remover != 0);
                break;
            case 5:
                do {
                    switch (escolha_config_exibicao) {
                        case 1:
                            config_exibicao ^= (1 << 0);
                            break;
                        case 2:
                            config_exibicao ^= (1 << 1);
                            break;
                        case 3:
                            config_exibicao ^= (1 << 2);
                            break;
                        case 0:
                            break;
                        default:
                            printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                            printf("█                                OPÇÃO INVÁLIDA                                █\n");
                            printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                            break;
                    }

                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         SUB-MENU CONFIGURAR EXIBIÇÃO                         █\n");
                    printf("█──────────────────────────────────────────────────────────────────────────────█\n");
                    printf("█                                                                              █\n");
                    printf("█ [1] - EXIBIR ENDEREÇOS                                                       █\n");
                    printf("█ [2] - EXIBIR POSIÇÃO                                                         █\n");
                    printf("█ [3] - EXIBIR EM AÇÕES                                                        █\n");
                    printf("█ [0] - VOLTAR                                                                 █\n");
                    printf("█                                                                              █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    print_input_box(80);
                    scanf("%hhu", &escolha_remover);
                    printf("\n");
                }while (escolha_remover != 0);
                break;
            case 6:
                do {
                    switch (escolha_config_exibicao) {
                        case 0:
                            break;
                        default:
                            printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                            printf("█                                OPÇÃO INVÁLIDA                                █\n");
                            printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                            break;
                    }

                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                    printf("█                                 TELA DE AJUDA                                █\n");
                    printf("█──────────────────────────────────────────────────────────────────────────────█\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█                                                                              █\n");
                    printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
                    print_input_box(80);
                    scanf("%hhu", &escolha_remover);
                    printf("\n");
                }while (escolha_remover != 0);
                break;
            case 0:
                break;
            default:
                printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
                printf("█                                OPÇÃO INVÁLIDA                                █\n");
                printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
        }

        printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
        printf("█                         PROGRAMA DE LISTA TELEFÔNICA                         █\n");
        printf("█──────────────────────────────────────────────────────────────────────────────█\n");
        printf("█                                                                              █\n");
        printf("█ Escrito por                                                                  █\n");
        printf("█ ├─ Bruno Costa Barreto (202310309411)                                        █\n");
        printf("█ ├─ João Pedro Meirelles Silva (202410302211)                                 █\n");
        printf("█ └─ Otávio Pessanha Costa (202310310611)                                      █\n");
        printf("█                                                                              █\n");
        printf("█ Banca                                                                        █\n");
        printf("█ ├─ Disciplina de Estrutura de Dados I                                        █\n");
        printf("█ └─ Professor Maximiano Martins                                               █\n");
        printf("█                                                                              █\n");
        printf("█ Informações                                                                  █\n");
        printf("█ ├─ Linguagem C                                                               █\n");
        printf("█ └─ Padrão ANSI C89 (ANSI X3.159-1989)                                        █\n");
        printf("█                                                                              █\n");
        printf("█──────────────────────────────────────────────────────────────────────────────█\n");
        printf("█                                                                              █\n");
        printf("█ [1] - CRIAR LISTA                                                            █\n");
        printf("█ [2] - ADICIONAR                                                              █\n");
        printf("█ [3] - REMOVER                                                                █\n");
        printf("█ [4] - EXIBIR LISTA                                                           █\n");
        printf("█ [5] - CONFIGURAR EXIBIÇÃO                                                    █\n");
        printf("█ [9] - AJUDA                                                                  █\n");
        printf("█ [0] - SAIR                                                                   █\n");
        printf("█                                                                              █\n");
        printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
        print_input_box(80);

        scanf("%hhu", &escolha_geral);
        printf("\n");
    } while (escolha_geral != 0);
}

int main(void) {
    lista_t* lista;
    init();

    lista = criar_lista();
    if (lista == ERROR_ALLOC_LIST_TYPE) {
        printf("ERROR %ud\n", ERROR_ALLOC_LIST_VALUE);
        free(lista);
        exit(ERROR_ALLOC_LIST_VALUE);
    }

    menu_principal();
    free(lista);
    return EXIT_SUCCESS;
}
