#include <stdio.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

char sys[100];
int period = 1000;
int duty_cycle = 1000;
int pwm_port = 3;

int manual;
int valor_manual = 0;

FILE *fp;
int posEEPROM;
int posInicial = 1;

int adc;
char buffer[10];
char buffer2[10];
int feedback = 0;
int test = 0;
int posicao = 3500;
int pos = 0;
int posBefore = 0;
int modo;
int valor_modo = 0;

 int sockfd, clisockfd, portno;
 char * start = "hello";
 char * end = "bye";
 socklen_t clilen;
 char bufferAuto[256];
 char contentBuffer[255];
 struct sockaddr_in serv_addr, cli_addr;
 int  n;
 int test2 = 0;

void iniciandoPortasGerais();
void setupADC();
void escritaPortaGPIO();
void iniciandoPortasManual();
void posicaoManual();

int main(int argc, char *argv[]){

	iniciandoPortasGerais();
	setupADC();

	system("echo -n '27' > /sys/class/gpio/unexport");
	system("echo -n '27' > /sys/class/gpio/export");
	system("echo -n '25' > /sys/class/gpio/unexport");
	system("echo -n '25' > /sys/class/gpio/export");

	system("echo -n 'in' > /sys/class/gpio/gpio25/direction");
	system("echo -n 'in' > /sys/class/gpio/gpio27/direction");

	system("echo -n 'in' > /sys/class/gpio/gpio30/direction");
	

	system("echo -n 'in' > /sys/class/gpio/gpio26/direction");

	system("echo -n 'in' > /sys/class/gpio/gpio24/direction");

	//system("echo -n 'in' > /sys/class/gpio/gpio30/direction");

			sockfd = socket(AF_INET, SOCK_STREAM, 0);
		    if (sockfd < 0) 
		    {
		        perror("ERROR opening socket");
		        return(1);
		    }

		    /* Initialize socket structure */
		    bzero((char *) &serv_addr, sizeof(serv_addr));
		    portno = 7081;
		    serv_addr.sin_family = AF_INET;
		    serv_addr.sin_addr.s_addr = INADDR_ANY;
		    serv_addr.sin_port = htons(portno);


		    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		    {
		        perror("ERROR on binding");
		        return(1);
		    }

		    listen(sockfd,5);
		    clilen = (socklen_t) sizeof(cli_addr);

	if((fp = fopen(argv[1], "r"))==NULL) {
	    printf("Cannot open file.\n");
	    exit(1);
  	}

  	fscanf(fp, "%d", &posEEPROM);
  	printf("Posicao Salva Na EEPROM: %d", posEEPROM);
  	fclose(fp);
  	system("sleep 2");
  	pos = posEEPROM;
	while(posInicial == 1){
			adc = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY);
			//system("cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
			if (adc == -1) {
				perror ("open");
				return 2;
			}
			int s = read(adc, &buffer, 10);
			close(adc);

			feedback = atoi(buffer);

			if(posBefore > pos){
				if(feedback >= ((pos/220.0)*4000)){
					printf("Valor de feedback: %i \n", feedback);

					test = ( (( (float)feedback)/4095) * period );

					duty_cycle = test;

					printf("Valor de feedback: %i \n", feedback);
					printf("Ligado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);


					escritaPortaGPIO(1,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(1,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(0,42);
				}
				else if(feedback < ((pos/220.0)*4000)){
					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Parado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(0,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(1,42);
					posBefore = pos;
					pos = 0;
					posInicial = 0;
					
  					
				}
			}



			else if(posBefore <= pos){
				if(feedback >= ((pos/220.0)*4000)){

					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Parado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(0,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(1,42);
					posBefore = pos;
					printf("posbefore: %d\n", posBefore);
					pos = 0;
					posInicial = 0;
				}
				else if (feedback < ((pos/220.0)*4000)){
					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Ligado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(1,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(1,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(0,42);
				}
			}
	}

	while(1){
		modo = open("/sys/class/gpio/gpio25/value",O_RDONLY);
		int w = read(modo,&buffer2,10);
		close(modo);
		valor_modo = atoi(buffer2);
		printf("Modo: %d\n",valor_modo);
		if(valor_modo == 0)	{
			if(pos == 0){

				//Pino 6
				manual = open("/sys/class/gpio/gpio24/value",O_RDONLY);
				int t = read(manual,&buffer2,10);
				close(manual);
				valor_manual = atoi(buffer2);
				printf("%d\n", 128*valor_manual);
				pos = pos + 128*valor_manual;

				//Pino 8
				manual = open("/sys/class/gpio/gpio26/value",O_RDONLY);
				int v = read(manual,&buffer2,10);
				close(manual);
				valor_manual = atoi(buffer2);
				printf("%d\n", 64*valor_manual);
				pos = pos + 64*valor_manual;

				//Pino 7
				manual = open("/sys/class/gpio/gpio27/value",O_RDONLY);
				int x = read(manual,&buffer2,10);
				close(manual);
				valor_manual = atoi(buffer2);
				printf("%d\n", 32*valor_manual);
				pos = pos + 32*valor_manual;


				if(pos > 220){

					pos = 220;
				}

				system("usleep 100");
			}


			adc = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY);
			//system("cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
			if (adc == -1) {
				perror ("open");
				return 2;
			}
			int s = read(adc, &buffer, 10);
			close(adc);

			feedback = atoi(buffer);

			if(posBefore > pos){
				if(feedback >= ((pos/220.0)*4000)){
					printf("Valor de feedback: %i \n", feedback);

					test = ( (( (float)feedback)/4095) * period );

					duty_cycle = test;

					printf("Valor de feedback: %i \n", feedback);
					printf("Ligado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);


					escritaPortaGPIO(1,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(1,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(0,42);
				}
				else if(feedback < ((pos/220.0)*4000)){
					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Parado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(0,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(1,42);
					posBefore = pos;
					pos = 0;
					posEEPROM = posBefore;
					if((fp = fopen(argv[1], "w"))==NULL) {
					    printf("Cannot open file.\n");
					    exit(1);
  					}

					fprintf(fp, "%d",posEEPROM);
					fclose(fp);
				}
			}



			else if(posBefore <= pos){
				if(feedback >= ((pos/220.0)*4000)){

					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Parado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(0,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(0,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(1,42);
					posBefore = pos;
					printf("posbefore: %d\n", posBefore);
					pos = 0;
					posEEPROM = posBefore;
					if((fp = fopen(argv[1], "w"))==NULL) {
					    printf("Cannot open file.\n");
					    exit(1);
  					}

					fprintf(fp, "%d",posEEPROM);
					fclose(fp);
				}
				else if (feedback < ((pos/220.0)*4000)){
					duty_cycle = 0;

					printf("Valor de feedback: %i \n", feedback);
					printf("Ligado");

					sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
					system(sys);

					escritaPortaGPIO(0,17);
				//Porta 19 representa o sinal de controle da ponte a H.
					escritaPortaGPIO(1,19);
				//Porta 28 Led vermelho
					escritaPortaGPIO(1,28);
				//Porta 42 Led Verde
					escritaPortaGPIO(0,42);
				}
			}
		
		}
		else if(valor_modo == 1){
			
			clisockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

		    if (clisockfd < 0) 
		    {
		        perror("ERROR on accept");
		        return(1);
		    }

		    while (strcmp(end, contentBuffer) !=0)
		    {
		    	if(pos == 0){
			        bzero(bufferAuto,256);
			        bzero(contentBuffer,255);
			        /* If connection is established then start communicating */
			        n = read( clisockfd,bufferAuto,255 );
			        if (n < 0)
			        {
			            perror("ERROR reading from socket");
			            return(1);
			        }

			        strncpy(contentBuffer,bufferAuto,strlen(bufferAuto) - 1);  
			        if (strcmp(start, contentBuffer) ==0)
			        {
			            printf("command: %s\n",bufferAuto);
			         //   printf("\n");
			            write(clisockfd,"\n",3);
			            n = write(clisockfd,"\nRoger that\n",15);
			            if (n < 0)
			            {
			                perror("ERROR writing to socket");
			                return(1);
			            }
			        }
			        else 
			        {
			            printf("Unknown command: %s\n",bufferAuto);
			            write(clisockfd,"\n",3);
			            n = write(clisockfd,"\nERRCmd\n",11);
			            if (n < 0)
			            {
			                perror("ERROR writing to socket");
			                return(1);
			            }           
			        }
			        test2 = atoi(contentBuffer);
			        pos = test2;
			    }
			    adc = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY);
			//system("cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
				if (adc == -1) {
					perror ("open");
					return 2;
				}
				int s = read(adc, &buffer, 10);
				close(adc);

				feedback = atoi(buffer);

				if(posBefore > pos){
					if(feedback >= ((pos/220.0)*4000)){
						printf("Valor de feedback: %i \n", feedback);

						test = ( (( (float)feedback)/4095) * period );

						duty_cycle = test;

						printf("Valor de feedback: %i \n", feedback);
						printf("Ligado");

						sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
						system(sys);


						escritaPortaGPIO(1,17);
					//Porta 19 representa o sinal de controle da ponte a H.
						escritaPortaGPIO(0,19);
					//Porta 28 Led vermelho
						escritaPortaGPIO(1,28);
					//Porta 42 Led Verde
						escritaPortaGPIO(0,42);
					}
					else if(feedback < ((pos/220.0)*4000)){
						duty_cycle = 0;

						printf("Valor de feedback: %i \n", feedback);
						printf("Parado");

						sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
						system(sys);

						escritaPortaGPIO(0,17);
					//Porta 19 representa o sinal de controle da ponte a H.
						escritaPortaGPIO(0,19);
					//Porta 28 Led vermelho
						escritaPortaGPIO(0,28);
					//Porta 42 Led Verde
						escritaPortaGPIO(1,42);
						posBefore = pos;
						pos = 0;
						if((fp = fopen(argv[1], "w"))==NULL) {
						    printf("Cannot open file.\n");
						    exit(1);
  						}

						fprintf(fp, "%d",posEEPROM);
						fclose(fp);
					}	
				}
				else if(posBefore <= pos){
					if(feedback >= ((pos/220.0)*4000)){

						duty_cycle = 0;

						printf("Valor de feedback: %i \n", feedback);
						printf("Parado");

						sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
						system(sys);

						escritaPortaGPIO(0,17);
					//Porta 19 representa o sinal de controle da ponte a H.
						escritaPortaGPIO(0,19);
					//Porta 28 Led vermelho
						escritaPortaGPIO(0,28);
					//Porta 42 Led Verde
						escritaPortaGPIO(1,42);
						posBefore = pos;
						printf("posbefore: %d\n", posBefore);
						pos = 0;
						if((fp = fopen(argv[1], "w"))==NULL) {
						    printf("Cannot open file.\n");
						    exit(1);
  						}

						fprintf(fp, "%d",posEEPROM);
						fclose(fp);
					}
					else if (feedback < ((pos/220.0)*4000)){
						duty_cycle = 0;

						printf("Valor de feedback: %i \n", feedback);
						printf("Ligado");

						sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/duty_cycle", duty_cycle, pwm_port);
						system(sys);

						escritaPortaGPIO(0,17);
					//Porta 19 representa o sinal de controle da ponte a H.
						escritaPortaGPIO(1,19);
					//Porta 28 Led vermelho
						escritaPortaGPIO(1,28);
					//Porta 42 Led Verde
						escritaPortaGPIO(0,42);
					}
				}   

		    }
		    close(sockfd);
		}
	}
}

void iniciandoPortasGerais(){

	//Led Vermelho - 4
	//system("echo -n '28' > /sys/class/gpio/export");
	system("echo -n 'out' > /sys/class/gpio/gpio28/direction");

	//Led Verde - 10
	//system("echo -n '42' > /sys/class/gpio/export");
	system("echo -n 'out' > /sys/class/gpio/gpio42/direction");

	//Pino Digital de Controle da Ponte H - 9
	//system("echo -n '19' > /sys/class/gpio/export");
	system("echo -n 'out' > /sys/class/gpio/gpio19/direction");

    //Pino Digital de Controle 5
	system("echo -n 'out' > /sys/class/gpio/gpio17/direction");

	//Pino PWM de Controle da Ponte H
	//system("echo -n '3' > /sys/class/pwm/pwmchip0/export");  
	system("echo -n '3' > /sys/class/pwm/pwmchip0/pwm3/enable");
	sprintf(sys, "echo -n '%d' > /sys/class/pwm/pwmchip0/pwm%d/period", period, pwm_port);
	system(sys);
}

//Configurando o MUX para utilizar o ADC
void setupADC(){

	//system("echo -n '37' > /sys/class/gpio/export");
	system("echo -n 'out' > /sys/class/gpio/gpio37/direction");
	system("echo -n '0' > /sys/class/gpio/gpio37/value");
}

void escritaPortaGPIO(int valor, int porta){

	sprintf(sys,"echo -n '%d' > /sys/class/gpio/gpio%d/value",valor,porta);
	system(sys);
}

//Iniciando portas de controlen manual
void iniciandoPortasManual(){


	//bit 8 - 5
	//system("echo -n '17' > /sys/class/gpio/export");
	system("echo -n 'in' > /sys/class/gpio/gpio17/direction");

	//bit 16 - 4
	//system("echo -n '28' > /sys/class/gpio/export");
	system("echo -n 'in' > /sys/class/gpio/gpio28/direction");

	//bit 32 - 8
	//system("echo -n '26' > /sys/class/gpio/export");
	system("echo -n 'in' > /sys/class/gpio/gpio26/direction");

	//bit 64 - 7
	//system("echo -n '27' > /sys/class/gpio/export");
	system("echo -n 'in' > /sys/class/gpio/gpio27/direction");

	//bit 128 - 6
	//system("echo -n '24' > /sys/class/gpio/export");
	system("echo -n 'in' > /sys/class/gpio/gpio24/direction");

}

void posicaoManual(int porta, int bits){

	manual = open("/sys/class/gpio/gpio%d/value",porta,O_RDONLY);
	int t = read(manual,&buffer2,10);
	close(manual);

	valor_manual = atoi(buffer2);

	printf("%d\n", bits*valor_manual);

	pos = pos + bits*valor_manual;
}
