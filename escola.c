#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_ALUNOS 100
#define TAM_PROFESSORES 50
#define TAM_DISCIPLINAS 20
#define MAX_ALUNOS_DISCIPLINA 50

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int matricula;
    char nome[100];
    char sexo;
    Data dataNascimento;
    char cpf[15];
    int ativo;
} Pessoa;

typedef struct {
    char nome[100];
    char codigo[10];
    int semestre;
    int matriculaProfessor;
    int alunos[MAX_ALUNOS_DISCIPLINA];
    int qtdAlunos;
    int ativo;
} Disciplina;

void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

int validarData(int d, int m, int a) {
    if (a < 1900 || a > 2100 || m < 1 || m > 12 || d < 1) return 0;
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) diasPorMes[2] = 29;
    return d <= diasPorMes[m];
}

int validarCPF(const char *cpf) {
    int digitos = 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) digitos++;
    }
    return digitos == 11;
}

int buscarPessoaPorMatricula(Pessoa lista[], int qtd, int matricula) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].ativo && lista[i].matricula == matricula) {
            return i;
        }
    }
    return -1;
}

int compararDatas(Data d1, Data d2) {
    if (d1.ano != d2.ano) return d1.ano - d2.ano;
    if (d1.mes != d2.mes) return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}


void cadastrarPessoa(Pessoa lista[], int *qtd, int limite, const char *tipo) {
    if (*qtd >= limite) {
        printf("Limite de %s atingido\n", tipo);
        return;
    }
    Pessoa p;
    p.ativo = 1;

    printf("Matrícula: ");
    scanf("%d", &p.matricula);
    getchar();

    if (buscarPessoaPorMatricula(lista, *qtd, p.matricula) != -1) {
        printf("Erro: Matrícula já cadastrada\n");
        return;
    }

    printf("Nome: ");
    lerString(p.nome, 100);

    do {
        printf("Sexo (M/F): ");
        scanf(" %c", &p.sexo);
        p.sexo = toupper(p.sexo);
    } while (p.sexo != 'M' && p.sexo != 'F');

    do {
        printf("Data Nasc. (DD MM AAAA): ");
        scanf("%d %d %d", &p.dataNascimento.dia, &p.dataNascimento.mes, &p.dataNascimento.ano);
        if (!validarData(p.dataNascimento.dia, p.dataNascimento.mes, p.dataNascimento.ano)) {
            printf("Data inválida. Tente novamente\n");
        }
    } while (!validarData(p.dataNascimento.dia, p.dataNascimento.mes, p.dataNascimento.ano));

    getchar();
    do {
        printf("CPF (11 dígitos): ");
        lerString(p.cpf, 15);
        if (!validarCPF(p.cpf)) {
            printf("CPF inválido. Deve possuir 11 dígitos numéricos\n");
        }
    } while (!validarCPF(p.cpf));

    lista[*qtd] = p;
    (*qtd)++;
    printf("%s cadastrado com sucesso\n", tipo);
}

void atualizarPessoa(Pessoa lista[], int qtd, const char *tipo) {
    int mat;
    printf("Digite a matrícula do %s que deseja atualizar: ", tipo);
    scanf("%d", &mat);
    getchar();

    int idx = buscarPessoaPorMatricula(lista, qtd, mat);
    if (idx == -1) {
        printf("%s não encontrado\n", tipo);
        return;
    }

    printf("Novo Nome: ");
    lerString(lista[idx].nome, 100);

    do {
        printf("Novo Sexo (M/F): ");
        scanf(" %c", &lista[idx].sexo);
        lista[idx].sexo = toupper(lista[idx].sexo);
    } while (lista[idx].sexo != 'M' && lista[idx].sexo != 'F');

    do {
        printf("Nova Data Nasc. (DD MM AAAA): ");
        scanf("%d %d %d", &lista[idx].dataNascimento.dia, &lista[idx].dataNascimento.mes, &lista[idx].dataNascimento.ano);
    } while (!validarData(lista[idx].dataNascimento.dia, lista[idx].dataNascimento.mes, lista[idx].dataNascimento.ano));

    getchar();
    do {
        printf("Novo CPF: ");
        lerString(lista[idx].cpf, 15);
    } while (!validarCPF(lista[idx].cpf));

    printf("%s atualizado(a) com sucesso\n", tipo);
}

void excluirPessoa(Pessoa lista[], int qtd, const char *tipo) {
    int mat;
    printf("Digite a matrícula do %s que deseja excluir: ", tipo);
    scanf("%d", &mat);
    getchar();

    int idx = buscarPessoaPorMatricula(lista, qtd, mat);
    if (idx == -1) {
        printf("%s não encontrado(a)\n", tipo);
        return;
    }

    lista[idx].ativo = 0;
    printf("%s excluído(a) com sucesso\n", tipo);
}

void listarPessoas(Pessoa lista[], int qtd, const char *tipo) {
    printf("\nLISTA DE %sS CADASTRADOS\n", tipo);
    int cadastrados = 0;
    for (int i = 0; i < qtd; i++) {
        if (lista[i].ativo) {
            printf("Matrícula: %d | Nome: %s | Sexo: %c | Data Nasc: %02d/%02d/%04d | CPF: %s\n",
                   lista[i].matricula, lista[i].nome, lista[i].sexo,
                   lista[i].dataNascimento.dia, lista[i].dataNascimento.mes, lista[i].dataNascimento.ano, lista[i].cpf);
            cadastrados++;
        }
    }
    if (cadastrados == 0) {
        printf("Nenhum %s ativo cadastrado\n", tipo);
    }
}


void listarDisciplinasSimples(Disciplina disciplinas[], int qtdDisciplinas) {
    printf("\nLISTA DE DISCIPLINAS CADASTRADAS\n");
    int cadastradas = 0;
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].ativo) {
            printf("Código: %s | Nome: %s | Semestre: %d | Prof. Matrícula: %d | Alunos Inscritos: %d\n",
                   disciplinas[i].codigo, disciplinas[i].nome, disciplinas[i].semestre, disciplinas[i].matriculaProfessor, disciplinas[i].qtdAlunos);
            cadastradas++;
        }
    }
    if (cadastradas == 0) {
        printf("Nenhuma disciplina ativa cadastrada\n");
    }
}

void inserirAlunoDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Pessoa alunos[], int qtdAlunos) {
    char codigo[10];
    int matAluno;

    printf("Código da Disciplina: ");
    lerString(codigo, 10);

    int idxDisc = -1;
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].ativo && strcmp(disciplinas[i].codigo, codigo) == 0) {
            idxDisc = i;
            break;
        }
    }

    if (idxDisc == -1) {
        printf("Disciplina não encontrada\n");
        return;
    }

    printf("Matrícula do Aluno: ");
    scanf("%d", &matAluno);

    if (buscarPessoaPorMatricula(alunos, qtdAlunos, matAluno) == -1) {
        printf("Aluno não encontrado ou inativo\n");
        return;
    }

    for (int i = 0; i < disciplinas[idxDisc].qtdAlunos; i++) {
        if (disciplinas[idxDisc].alunos[i] == matAluno) {
            printf("Aluno já matriculado nesta disciplina\n");
            return;
        }
    }

    if (disciplinas[idxDisc].qtdAlunos >= MAX_ALUNOS_DISCIPLINA) {
        printf("Disciplina lotada\n");
        return;
    }

    disciplinas[idxDisc].alunos[disciplinas[idxDisc].qtdAlunos] = matAluno;
    disciplinas[idxDisc].qtdAlunos++;
    printf("Aluno matriculado\n");
}

void excluirAlunoDisciplina(Disciplina disciplinas[], int qtdDisciplinas) {
    char codigo[10];
    int matAluno;

    printf("Código da Disciplina: ");
    lerString(codigo, 10);

    int idxDisc = -1;
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].ativo && strcmp(disciplinas[i].codigo, codigo) == 0) {
            idxDisc = i;
            break;
        }
    }

    if (idxDisc == -1) {
        printf("Disciplina não encontrada\n");
        return;
    }

    printf("Matrícula do Aluno a ser removido: ");
    scanf("%d", &matAluno);

    int idxAluno = -1;
    for (int i = 0; i < disciplinas[idxDisc].qtdAlunos; i++) {
        if (disciplinas[idxDisc].alunos[i] == matAluno) {
            idxAluno = i;
            break;
        }
    }

    if (idxAluno == -1) {
        printf("O Aluno não está matriculado nesta disciplina\n");
        return;
    }

    for (int i = idxAluno; i < disciplinas[idxDisc].qtdAlunos - 1; i++) {
        disciplinas[idxDisc].alunos[i] = disciplinas[idxDisc].alunos[i + 1];
    }
    disciplinas[idxDisc].qtdAlunos--;
    printf("Aluno removido\n");
}

//Menus
void menuAlunos(Pessoa alunos[], int *qtdAlunos) {
    int opcao;
    do {
        printf("\n--- GESTÃO DE ALUNOS ---\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Atualizar Aluno\n");
        printf("3. Excluir Aluno\n");
        printf("4. Listar Alunos\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarPessoa(alunos, qtdAlunos, TAM_ALUNOS, "Aluno"); break;
            case 2: atualizarPessoa(alunos, *qtdAlunos, "Aluno"); break;
            case 3: excluirPessoa(alunos, *qtdAlunos, "Aluno"); break;
            case 4: listarPessoas(alunos, *qtdAlunos, "Aluno"); break;
            case 0: break;
            default: printf("Opção inválida\n");
        }
    } while (opcao != 0);
}

void menuProfessores(Pessoa professores[], int *qtdProfessores) {
    int opcao;
    do {
        printf("\n--- GESTÃO DE PROFESSORES ---\n");
        printf("1. Cadastrar Professor\n");
        printf("2. Atualizar Professor\n");
        printf("3. Excluir Professor\n");
        printf("4. Listar Professores\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarPessoa(professores, qtdProfessores, TAM_PROFESSORES, "Professor"); break;
            case 2: atualizarPessoa(professores, *qtdProfessores, "Professor"); break;
            case 3: excluirPessoa(professores, *qtdProfessores, "Professor"); break;
            case 4: listarPessoas(professores, *qtdProfessores, "Professor"); break;
            case 0: break;
            default: printf("Opção inválida\n");
        }
    } while (opcao != 0);
}

void menuDisciplinas(Disciplina disciplinas[], int *qtdDisciplinas, Pessoa alunos[], int qtdAlunos, Pessoa professores[], int qtdProfessores) {
    int opcao;
    do {
        printf("\n--- GESTÃO DE DISCIPLINAS ---\n");
        printf("1. Cadastrar Disciplina\n");
        printf("2. Inserir Aluno em Disciplina\n");
        printf("3. Excluir Aluno de Disciplina\n");
        printf("4. Listar Disciplinas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (*qtdDisciplinas >= TAM_DISCIPLINAS) {
                    printf("Limite de disciplinas atingido\n");
                    break;
                }
                Disciplina d;
                d.ativo = 1;
                d.qtdAlunos = 0;

                printf("Nome da Disciplina: ");
                lerString(d.nome, 100);
                printf("Código: ");
                lerString(d.codigo, 10);
                printf("Semestre: ");
                scanf("%d", &d.semestre);
                printf("Matrícula do Professor: ");
                scanf("%d", &d.matriculaProfessor);

                if (buscarPessoaPorMatricula(professores, qtdProfessores, d.matriculaProfessor) == -1) {
                    printf("Aviso: Professor não encontrado\n");
                }

                disciplinas[*qtdDisciplinas] = d;
                (*qtdDisciplinas)++;
                printf("Disciplina cadastrada com sucesso\n");
                break;
            case 2:
                inserirAlunoDisciplina(disciplinas, *qtdDisciplinas, alunos, qtdAlunos);
                break;
            case 3:
                excluirAlunoDisciplina(disciplinas, *qtdDisciplinas);
                break;
            case 4:
                listarDisciplinasSimples(disciplinas, *qtdDisciplinas);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (opcao != 0);
}

//Relatorios
void menuRelatorios(Pessoa alunos[], int qtdAlunos, Pessoa professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int opcao;
    do {
        printf("\n--- RELATÓRIOS ---\n");
        printf("1. Listar Alunos\n");
        printf("2. Listar Professores\n");
        printf("3. Listar Disciplinas (sem alunos)\n");
        printf("4. Listar Uma Disciplina (com alunos)\n");
        printf("5. Listar Alunos por Sexo\n");
        printf("6. Listar Alunos Ordenados por Nome\n");
        printf("7. Listar Alunos Ordenados por Data de Nascimento\n");
        printf("8. Listar Professores por Sexo\n");
        printf("9. Listar Professores Ordenados por Nome\n");
        printf("10. Listar Professores Ordenados por Data de Nascimento\n");
        printf("11. Aniversariantes do Mês\n");
        printf("12. Buscar Pessoas por Nome (min. 3 letras)\n");
        printf("13. Alunos em menos de 3 disciplinas\n");
        printf("14. Disciplinas com mais de 40 alunos (com Prof.)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: listarPessoas(alunos, qtdAlunos, "Aluno"); break;
            case 2: listarPessoas(professores, qtdProfessores, "Professor"); break;
            case 3: listarDisciplinasSimples(disciplinas, qtdDisciplinas); break;
            case 4: {
                char cod[10];
                printf("Digite o código da disciplina: ");
                lerString(cod, 10);
                int achou = 0;
                for (int i = 0; i < qtdDisciplinas; i++) {
                    if (disciplinas[i].ativo && strcmp(disciplinas[i].codigo, cod) == 0) {
                        achou = 1;
                        printf("\nDisciplina: %s (%s) - Semestre %d\n", disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].semestre);
                        int idxProf = buscarPessoaPorMatricula(professores, qtdProfessores, disciplinas[i].matriculaProfessor);
                        if (idxProf != -1) printf("Professor Responsável: %s\n", professores[idxProf].nome);
                        else printf("Professor Responsável: Não atribuído\n");

                        printf("Alunos Matriculados (%d):\n", disciplinas[i].qtdAlunos);
                        for (int j = 0; j < disciplinas[i].qtdAlunos; j++) {
                            int idxAl = buscarPessoaPorMatricula(alunos, qtdAlunos, disciplinas[i].alunos[j]);
                            if (idxAl != -1) printf(" - %s (Matrícula: %d)\n", alunos[idxAl].nome, alunos[idxAl].matricula);
                        }
                        break;
                    }
                }
                if (!achou) printf("Disciplina não encontrada\n");
                break;
            }
            case 5: {
                char s;
                printf("Digite o sexo desejado (M/F): ");
                scanf(" %c", &s);
                s = toupper(s);
                printf("\n-- ALUNOS DO SEXO %c --\n", s);
                for (int i = 0; i < qtdAlunos; i++) {
                    if (alunos[i].ativo && alunos[i].sexo == s) printf("Matrícula: %d | Nome: %s\n", alunos[i].matricula, alunos[i].nome);
                }
                break;
            }
            case 6: {
                Pessoa temp[TAM_ALUNOS];
                int n = 0;
                for (int i = 0; i < qtdAlunos; i++) if (alunos[i].ativo) temp[n++] = alunos[i];
                for (int i = 0; i < n - 1; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if (strcmp(temp[i].nome, temp[j].nome) > 0) {
                            Pessoa aux = temp[i]; temp[i] = temp[j]; temp[j] = aux;
                        }
                    }
                }
                printf("\n-- ALUNOS ORDENADOS POR NOME --\n");
                for (int i = 0; i < n; i++) printf("%s (Matrícula: %d)\n", temp[i].nome, temp[i].matricula);
                break;
            }
            case 7: {
                Pessoa temp[TAM_ALUNOS];
                int n = 0;
                for (int i = 0; i < qtdAlunos; i++) if (alunos[i].ativo) temp[n++] = alunos[i];
                for (int i = 0; i < n - 1; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if (compararDatas(temp[i].dataNascimento, temp[j].dataNascimento) > 0) {
                            Pessoa aux = temp[i]; temp[i] = temp[j]; temp[j] = aux;
                        }
                    }
                }
                printf("\n-- ALUNOS ORDENADOS POR DATA DE NASCIMENTO --\n");
                for (int i = 0; i < n; i++) printf("%02d/%02d/%04d - %s\n", temp[i].dataNascimento.dia, temp[i].dataNascimento.mes, temp[i].dataNascimento.ano, temp[i].nome);
                break;
            }
            case 8: {
                char s;
                printf("Digite o sexo desejado (M/F): ");
                scanf(" %c", &s);
                s = toupper(s);
                printf("\n-- PROFESSORES DO SEXO %c --\n", s);
                for (int i = 0; i < qtdProfessores; i++) {
                    if (professores[i].ativo && professores[i].sexo == s) printf("Matrícula: %d | Nome: %s\n", professores[i].matricula, professores[i].nome);
                }
                break;
            }
            case 9: {
                Pessoa temp[TAM_PROFESSORES];
                int n = 0;
                for (int i = 0; i < qtdProfessores; i++) if (professores[i].ativo) temp[n++] = professores[i];
                for (int i = 0; i < n - 1; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if (strcmp(temp[i].nome, temp[j].nome) > 0) {
                            Pessoa aux = temp[i]; temp[i] = temp[j]; temp[j] = aux;
                        }
                    }
                }
                printf("\n-- PROFESSORES ORDENADOS POR NOME --\n");
                for (int i = 0; i < n; i++) printf("%s (Matrícula: %d)\n", temp[i].nome, temp[i].matricula);
                break;
            }
            case 10: {
                Pessoa temp[TAM_PROFESSORES];
                int n = 0;
                for (int i = 0; i < qtdProfessores; i++) if (professores[i].ativo) temp[n++] = professores[i];
                for (int i = 0; i < n - 1; i++) {
                    for (int j = i + 1; j < n; j++) {
                        if (compararDatas(temp[i].dataNascimento, temp[j].dataNascimento) > 0) {
                            Pessoa aux = temp[i]; temp[i] = temp[j]; temp[j] = aux;
                        }
                    }
                }
                printf("\n-- PROFESSORES ORDENADOS POR DATA DE NASCIMENTO --\n");
                for (int i = 0; i < n; i++) printf("%02d/%02d/%04d - %s\n", temp[i].dataNascimento.dia, temp[i].dataNascimento.mes, temp[i].dataNascimento.ano, temp[i].nome);
                break;
            }
            case 11: {
                int mes;
                printf("Digite o mês (1-12): ");
                scanf("%d", &mes);
                printf("\n-- ANIVERSARIANTES DO MÊS %d --\n", mes);
                for (int i = 0; i < qtdAlunos; i++) if (alunos[i].ativo && alunos[i].dataNascimento.mes == mes) printf("Aluno: %s (Dia %02d)\n", alunos[i].nome, alunos[i].dataNascimento.dia);
                for (int i = 0; i < qtdProfessores; i++) if (professores[i].ativo && professores[i].dataNascimento.mes == mes) printf("Professor: %s (Dia %02d)\n", professores[i].nome, professores[i].dataNascimento.dia);
                break;
            }
            case 12: {
                char busca[100];
                printf("Digite no mínimo 3 letras para busca: ");
                lerString(busca, 100);
                if (strlen(busca) < 3) {
                    printf("Termo de busca deve ter pelo menos 3 caracteres.\n");
                    break;
                }
                printf("\n-- RESULTADOS --\n");
                for (int i = 0; i < qtdAlunos; i++) if (alunos[i].ativo && strstr(alunos[i].nome, busca) != NULL) printf("Aluno: %s\n", alunos[i].nome);
                for (int i = 0; i < qtdProfessores; i++) if (professores[i].ativo && strstr(professores[i].nome, busca) != NULL) printf("Professor: %s\n", professores[i].nome);
                break;
            }
            case 13: {
                printf("\n-- ALUNOS MATRICULADOS EM MENOS DE 3 DISCIPLINAS --\n");
                for (int i = 0; i < qtdAlunos; i++) {
                    if (alunos[i].ativo) {
                        int cont = 0;
                        for (int d = 0; d < qtdDisciplinas; d++) {
                            if (disciplinas[d].ativo) {
                                for (int a = 0; a < disciplinas[d].qtdAlunos; a++) {
                                    if (disciplinas[d].alunos[a] == alunos[i].matricula) {
                                        cont++;
                                        break;
                                    }
                                }
                            }
                        }
                        if (cont < 3) printf("%s (Matrícula: %d) - %d disciplina(s)\n", alunos[i].nome, alunos[i].matricula, cont);
                    }
                }
                break;
            }
            case 14:
                printf("\n-- DISCIPLINAS QUE EXTRAPOLAM 40 ALUNOS --\n");
                for (int i = 0; i < qtdDisciplinas; i++) {
                    if (disciplinas[i].ativo && disciplinas[i].qtdAlunos > 40) {
                        int idxProf = buscarPessoaPorMatricula(professores, qtdProfessores, disciplinas[i].matriculaProfessor);
                        char nomeProf[100] = "Não atribuído";
                        if (idxProf != -1) strcpy(nomeProf, professores[idxProf].nome);
                        printf("Código: %s | Disciplina: %s | Prof: %s | Alunos: %d\n", disciplinas[i].codigo, disciplinas[i].nome, nomeProf, disciplinas[i].qtdAlunos);
                    }
                }
                break;
            case 0: break;
            default: printf("Opção inválida\n");
        }
    } while (opcao != 0);
}


int main() {
    Pessoa alunos[TAM_ALUNOS];
    Pessoa professores[TAM_PROFESSORES];
    Disciplina disciplinas[TAM_DISCIPLINAS];

    int qtdAlunos = 0;
    int qtdProfessores = 0;
    int qtdDisciplinas = 0;
    int opcao;

    do {
        printf("\n====================================\n");
        printf("    SISTEMA DE GESTÃO ACADÊMICA     \n");
        printf("====================================\n");
        printf("1. Gestão de Alunos\n");
        printf("2. Gestão de Professores\n");
        printf("3. Gestão de Disciplinas\n");
        printf("4. Relatórios\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuAlunos(alunos, &qtdAlunos);
                break;
            case 2:
                menuProfessores(professores, &qtdProfessores);
                break;
            case 3:
                menuDisciplinas(disciplinas, &qtdDisciplinas, alunos, qtdAlunos, professores, qtdProfessores);
                break;
            case 4:
                menuRelatorios(alunos, qtdAlunos, professores, qtdProfessores, disciplinas, qtdDisciplinas);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida. Tente novamente\n");
        }
    } while (opcao != 0);

    return 0;
}
