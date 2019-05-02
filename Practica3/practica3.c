#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

struct data {
    int *passenger_count;
    int *trip_time_in_secs;
};

int get_column_int(char* line, int num);
int get_data(struct data *data, FILE *file, int max);
void productor(char* filename);
void consumidor(void);
int fd[2], parent_pid, child_pid;

/*
Escollim N com la mida màxima del pipe dividit entre la mida de 2 enters.
Enviem arrays de dos enters (la mida d'un enter es 4Bytes).
Restem un perquè la primera dada que enviem és la mida dels blocs.
*/
int N = 65536/(sizeof(int)*2)-1;

void sigusr1(int signo)
{
    //printf("El pare ha rebut el SIGUSR1\n");
}

void sigusr2(int signo)
{
    //printf("El fill ha rebut el SIGUSR2\n");
}

int main(int argc, char *argv[])
{
    
    if(argc != 2)
    {
        printf("%s <file>\n", argv[0]);
        exit(1);
    }
    
    pipe(fd);
    int ret = fork();
    if (ret == 0){ // fill
        signal(SIGUSR2, sigusr2);
        parent_pid = getppid();
        consumidor();
    } else {
        signal(SIGUSR1, sigusr1);
        child_pid = ret;
        productor(argv[1]);
    }
}

////////////////////////////////////// PRODUCTOR //////////////////////////////////////

void productor(char *filename){
    FILE *file;
    struct data data;
    int i, j, temp, num_elements_block, num_elements, passenger_count, trip_time_in_secs;
    int *ptr;
    
    ptr = malloc(2 * sizeof(int));
    
    num_elements_block = 100000;
    passenger_count = 0;
    trip_time_in_secs = 0;

    file = fopen(filename, "r");
    if (!file) {
        printf("ERROR: could not open '%s'\n", filename);
        exit(1);
    }
    
    data.passenger_count   = malloc(sizeof(int) * num_elements_block);
    data.trip_time_in_secs = malloc(sizeof(int) * num_elements_block); 

    num_elements = get_data(&data, file, num_elements_block);
    
    for(i = 0; i < num_elements; i+=N)
    {
        ptr[0] = N; //La mida del bloc serà la N que hem calculat (l'últim bloc acabarà quan enviem un -1)
        ptr[1] = 0;
        //Enviem la mida del bloc que enviarem al consumidor
        write(fd[1], ptr, sizeof(int)*2); 
        for(j=0; j<N && i+j<num_elements; j++)
        {
            ptr[0] = data.passenger_count[i+j];
            ptr[1] = data.trip_time_in_secs[i+j];
            write(fd[1], ptr, sizeof(int)*2); //Enviem les dades en arrays de 2 posicions
        }
        if(i+j>=num_elements-1){ //Si hem acabat d'enviar tots els elements no enviarem un altre senyal
            break;
        }
        kill(child_pid, SIGUSR2); //Enviem un senyal al consumidor perquè comenci a llegir
        pause();
    }
    ptr[0] = -1; //Enviem un -1 indicant que hem acabat d'enviar dades
    write(fd[1], ptr, sizeof(int)*2);
    kill(child_pid, SIGUSR2);

    free(data.passenger_count);
    free(data.trip_time_in_secs);
    
    fclose(file);    
} // li passarem el fitxer


////////////////////////////////////// CONSUMIDOR //////////////////////////////////////
void consumidor(void){
    int passengers = 0;
    int trip_time = 0;
    int count = 0;
    int *read_data = malloc(2 * sizeof(int));
    int block_size;
    read_data[0]=0;
    read_data[1]=0;
    while(read_data[0]!=-1){
        pause(); //El consumidor espera fins que rep un senyal del productor
        read(fd[0],read_data,sizeof(int)*2); //Llegim la mida del bloc que rebrem
        block_size = read_data[0];
        for(int k=0; k<block_size; k++)
        {
            read(fd[0],read_data,sizeof(int)*2); //Llegim la parella de dades
            if(read_data[0]!=-1){ //Comprovem que la dada no sigui -1 (si és -1 vol dir que hem acabat)
                passengers+=read_data[0]; 
                trip_time+=read_data[1];
                count++;
            }else{
                break;
            }
        }
        if(read_data[0]==-1){ //Si hem rebut un -1, vol dir que el productor ja ha acabat d'enviar dades
            break;
        }
        kill(parent_pid, SIGUSR1);
    }
    
    float pc = 0, tt = 0;
    pc = (float)passengers/(float)count;	
    tt = (float)trip_time/(float)count;

    printf("Aplication read %d elements\n", count);
    printf("Mean of passengers: %f\n", pc);
    printf("Mean of trip time: %f secs\n", tt);
    
}


/////////////////////////////Codi donat per llegir el fitxer csv///////////////////////////////////

int get_column_int(char* line, int num)
{
    char new_line[256];
    char* tok;
    int retvalue;

    strncpy(new_line, line, 256);
    for (tok = strtok(new_line, ",\n"); tok; tok = strtok(NULL, ",\n"))
    {
        if (!--num) {
            retvalue = (int) strtol(tok, (char **)NULL, 10);
            return retvalue;
        }
    }

    printf("ERROR: get_column_int\n");
    exit(1); 
}

int get_data(struct data *data, FILE *file, int max)
{
    char line[256];
    int temp, pos;

    // If we are at the beginning of the file, we ignore
    // the header of the file.
    if (ftell(file) == 0)
        fgets(line, sizeof(line), file);

    pos = 0;
    while (pos < max && fgets(line, sizeof(line), file))
    {
        temp = get_column_int(line, 8);
        data->passenger_count[pos] = temp;
        temp = get_column_int(line, 9);
        data->trip_time_in_secs[pos] = temp;
        pos++;
    }

    return pos;
}
