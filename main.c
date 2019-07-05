#include "msp430f5529.h"       // Especificar dispositivo.
#include <intrinsics.h>     // Utilizar fun��es intr�nsecas de baixo n�vel j� definidas
#include "clock.h"          // Clock
#include "LEDs.h"           // Arquivo de prot�tipos de fun��es relacionadas aos LED�s.
#include "iso_rs_485.h"


//=============================================================================
//                           Defini��es
//=============================================================================

#define         true          0xff                // booleana 1
#define         false         0x00                // booleana 0

#define         F_CLK         20000000            // frequencia de clock do uC

//#define			F_SMCLK		  F_CLK/2
#define         BAUD_RATE     500000              // baud rate da UCA1  (isolador)

#define         VELOCIDADE    F_CLK/BAUD_RATE     // prescaler da uart (isolador)
// TIMES THAT IS NECESSARY TO SET THE OUTPUT'S DACS
#define			int_5k_Hz				0x07D0

#define         BOTAO_2_1           !(P2IN&BIT1)    // definicao para verificar se o botao 2.1 esta pressionado
#define         BOTAO_1_1           !(P1IN&BIT1)    // definicao para verificar se o botao 2.1 esta pressionado

#define         LIMITE_TEMPO_SAMPLE     19


unsigned char dado_r;
int aux = 0;

unsigned char som1[6] = {1,2,3,4,5,6};
unsigned char som2[6] = {1,3,5,2,4,6};
unsigned char som3[6] = {1,2,3,3,2,1};
unsigned char som4[6] = {1,6,1,6,1,6};
unsigned char som_custom [6];
unsigned char timer_sample = 0;
unsigned char i = 0;
unsigned char ready = 0;

unsigned char ctrl = 0;
unsigned char ctrl_2_5 = 0;
unsigned char ctrl_625 = 0;
unsigned char ctrl_1_25 = 0;
unsigned char ctrl_312 = 0;
unsigned char ctrl_156 = 0;

unsigned char freq_5k = 0;
unsigned char freq_2_5k = 0;
unsigned char freq_1_25k = 0;
unsigned char freq_625 = 0;
unsigned char freq_312_5 = 0;
unsigned char freq_156_25 = 0;

//void salva_som (void);

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  iniciar_leds();                           // Inicia os leds
   acende_led(LED1);   clock_setup_full(DCO,DCO,DCO);
   apaga_led(LED1);

   uart_init(VELOCIDADE);

// config pino de saida
    P2SEL &= (~BIT5); // Set P1.0 SEL for GPIO
    P2DIR |= BIT5; // Set P1.0 as Output
    P2OUT &= ~BIT5; // Set P1.0 DOWN
	
   
// configura interrupcao
	TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
	TA0CCR0 = int_5k_Hz;
	TA0CTL = TASSEL__SMCLK + MC__UP + TACLR;         // SMCLK, upmode, clear TAR

    TA1CTL = TASSEL__SMCLK + MC__CONTINUOUS + TACLR + ID__8;         // SMCLK, upmode, clear TAR


	__bis_SR_register(GIE);       // Enter LPM0, enable interrupts
	while(1);

}


// Timer0 A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	TA0CCTL0 &= 0xFFFE;     		// limpa a flag da interrupcao

	if(freq_5k == 1)
    {
		P2OUT ^= BIT5;
	}
	if((freq_2_5k == 1) && (ctrl_2_5 < 2))
    {
		ctrl_2_5++;
		if((freq_2_5k == 1) && (ctrl_2_5 == 2))
		{
			ctrl_2_5 = 0;
			P2OUT ^= BIT5;
		}
	}
	if((freq_1_25k==1) && (ctrl_1_25 < 4))
	{
		ctrl_1_25++;
		if((freq_1_25k==1) && (ctrl_1_25 == 4))
		{
			ctrl_1_25 = 0;
			P2OUT ^= BIT5;
		}	
	}
    if((freq_625==1) && (ctrl_625 < 8))
    {
        ctrl_625++;
        if((freq_625==1) && (ctrl_625 == 8))
        {
            ctrl_625 = 0;
            P2OUT ^= BIT5;
        }
    }
    if((freq_312_5==1) && (ctrl_312 < 16))
    {
        ctrl_312++;
        if((freq_312_5==1) && (ctrl_312 == 16))
        {
            ctrl_312 = 0;
            P2OUT ^= BIT5;
        }
    }
    if((freq_156_25==1) && (ctrl_156 < 32))
    {
        ctrl_156++;
        if((freq_156_25==1) && (ctrl_156 == 32))
        {
            ctrl_156 = 0;
            P2OUT ^= BIT5;
        }
    }
}

//  Interrupcao UART
#pragma vector=USCI_A0_VECTOR						//	configura o vetor da UART para interrupcao
__interrupt void USCI_A0_ISR(void)					//	funcao destinada para interrupcao da UART
{
    unsigned char       dado_r;             		//	variavel criada para resgatar o valor do RXBUF
    switch(__even_in_range(UCA0IV,4)){
        case 0:break;                                // Vector 0 - no interrupt
        case 2:                                      // Vector 2 - RXIFG
            dado_r = uart_rd();						// armazena valor recebido chamando funcao que recebe dado do isolador
			
			if(ctrl == 0)					// condicao que altera entre verificacao de caracter de controle 
			{								// ou modo de configuracao de sequencia;
				if(dado_r == '1')			// sequencia de if's que verifica o caracter enviado 
				{							// e ativam a determinada variavel de controle de frequencia
					freq_5k = 1;			// caso o dado seja alguns dos relacionados
				}
				if(dado_r == '2')					
				{
					freq_2_5k = 1;
				}
				if(dado_r == '3')					
				{
					freq_1_25k = 1;
				}
				if(dado_r == '4')						
				{
					freq_625 = 1;
				}
				if(dado_r == '5')					
				{
					freq_312_5 = 1;
				}
				if(dado_r == '6')					
				{
					freq_156_25 = 1;
				}
				if(dado_r == 'w')			// Estes sao condicoes de verificacao dos caracteres		
				{							// que desativam as variaveis de controle de frequencia
					freq_5k = 0;			// em adicional, o valor do pino de saida eh desativado
					P2OUT &= ~BIT5; 		// em caso do sistema estar executando apenas uma frequencia
				}							// para que pino fique setado como 0 V, e n�o como 5 V 
				if(dado_r == 's')			// evitando dissipacao termica no transistor que aciona o speaker	
				{
					freq_2_5k = 0;
					P2OUT &= ~BIT5; 
				}
				if(dado_r == 'x')					
				{
					freq_1_25k = 0;
					P2OUT &= ~BIT5;
				}
				if(dado_r == 'r')						
				{
					freq_625 = 0;
					P2OUT &= ~BIT5; 
				}
				if(dado_r == 'f')					
				{
					
					freq_312_5 = 0;
					P2OUT &= ~BIT5; 
				}
				if(dado_r == 'v')					
				{
					freq_156_25 = 0;
					P2OUT &= ~BIT5; 
				}
				if(dado_r == '7')					// sequencia de if's que associados as variaves de controle 
				{									// de ativacao dos sons pre-gravados no sistema 
					TA1CCTL0 = CCIE;                // estas condicoes ativam um interrupcao TIMER secundaria          
					ready = 0;						// que eh responsavel por reproduzir automaticamente a sequencias
				}									// e tambem altera a variavel que determina qual sequencia ira ser executada
				if(dado_r == '8')					// amabas as variaveis serao discutidas na funcao que as utiliza
				{
					TA1CCTL0 = CCIE;                          
					ready = 1;
				}
				if(dado_r == '9')					
				{
					TA1CCTL0 = CCIE;                          
					ready = 2;
				}
				if(dado_r == '0')					
				{
					TA1CCTL0 = CCIE;                          
					ready = 3;
				}				
				if(dado_r == 'i')					// esta condicao eh a que ativa a execucao automatica 
				{									// da sequencia configurada pelo usuario
					TA1CCTL0 = CCIE;                          
					ready = 4;
				}	
				if(dado_r == 'o')					// condicao de STOP do sistema					
				{									// desativa TIMER de controle de frequencias
					TA1CCTL0 &= ~CCIE;              // zera variaveis de controle para que n�o executem
					freq_5k = 0;
					freq_2_5k = 0;
					freq_1_25k = 0;
					freq_625 = 0;
					freq_312_5 = 0;					
					freq_156_25 = 0;				// seta pino para 0 V
					P2OUT &= ~BIT5; 				// evitando dissipacao termica no transistor que aciona o speaker	
				}
				if(dado_r == 'p')					// se nao, caso "P"
				{
					ctrl = 1;
				}
			}
			else if(ctrl == 1)
			{
				som_custom[aux] = dado_r - 48;
				aux++;
				
				if (aux>5)
				{
					aux = 0;
					ctrl = 0;
				}
			}
			
            break;
        case 4:break;                                // Vector 4 - TXIFG
        default: break;
    }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
	TA1CCTL0 &= 0xFFFE;     		// limpa a flag da interrupcao

	timer_sample++;

	if((timer_sample == LIMITE_TEMPO_SAMPLE) && (ready == 0))
	{
		timer_sample = 0;
		if(som1[i] == 1)
		{
			freq_5k = 1;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som1[i] == 2)
		{
			freq_5k = 0;
			freq_2_5k = 1;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som1[i] == 3)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 1;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som1[i] == 4)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 1;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som1[i] == 5)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 1;
			freq_156_25 = 0;
		}
		if(som1[i] == 6)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 1;
		}
		i++;
		
		if(i>6)
			i=0;
		
	}
	if((timer_sample == LIMITE_TEMPO_SAMPLE) && (ready == 1))
	{
		timer_sample = 0;
		if(som2[i] == 1)
		{
			freq_5k = 1;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som2[i] == 2)
		{
			freq_5k = 0;
			freq_2_5k = 1;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som2[i] == 3)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 1;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som2[i] == 4)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 1;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som2[i] == 5)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 1;
			freq_156_25 = 0;
		}
		if(som2[i] == 6)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 1;
		}
		i++;
		
		if(i>6)
			i=0;
		
	}
	if((timer_sample == LIMITE_TEMPO_SAMPLE) && (ready == 2))
	{
		timer_sample = 0;
		if(som3[i] == 1)
		{
			freq_5k = 1;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som3[i] == 2)
		{
			freq_5k = 0;
			freq_2_5k = 1;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som3[i] == 3)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 1;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som3[i] == 4)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 1;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som3[i] == 5)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 1;
			freq_156_25 = 0;
		}
		if(som3[i] == 6)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 1;
		}
		i++;
		
		if(i>6)
			i=0;
		
	}
	if((timer_sample == LIMITE_TEMPO_SAMPLE) && (ready == 3))
	{
		timer_sample = 0;
		if(som4[i] == 1)
		{
			freq_5k = 1;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som4[i] == 2)
		{
			freq_5k = 0;
			freq_2_5k = 1;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som4[i] == 3)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 1;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som4[i] == 4)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 1;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som4[i] == 5)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 1;
			freq_156_25 = 0;
		}
		if(som4[i] == 6)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 1;
		}
		i++;
		
		if(i>6)
			i=0;
		
	}
	if((timer_sample == LIMITE_TEMPO_SAMPLE) && (ready == 4))
	{
		timer_sample = 0;
		if(som_custom[i] == 1)
		{
			freq_5k = 1;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som_custom[i] == 2)
		{
			freq_5k = 0;
			freq_2_5k = 1;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som_custom[i] == 3)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 1;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som_custom[i] == 4)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 1;
			freq_312_5 = 0;
			freq_156_25 = 0;
		}
		if(som_custom[i] == 5)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 1;
			freq_156_25 = 0;
		}
		if(som_custom[i] == 6)
		{
			freq_5k = 0;
			freq_2_5k = 0;
			freq_1_25k = 0;
			freq_625 = 0;
			freq_312_5 = 0;
			freq_156_25 = 1;
		}
		i++;
		
		if(i>6)
			i=0;	
	}
}

