#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

int perceptron(int operaciones,int valores,int entradas[operaciones][valores],int salida[operaciones],int pesos[valores],int umbral)
{
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    const int Mx = 600;
    const int My = 600;
    al_create_display(Mx,My);
    ALLEGRO_KEYBOARD_STATE estadoTeclado;

    short int error;
    int epocas=0;
    int resultado=0;

    int escala=50;

    al_clear_to_color(al_map_rgb(255,255,255));
    al_flip_display();
    while(1)
    {
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_line(0,My/2,Mx,My/2,al_map_rgb(0,0,0),1);
        al_draw_line(Mx/2,0,Mx/2,My,al_map_rgb(0,0,0),1);
        for(int x=escala;x<Mx;x+=escala)
        {
            al_draw_line(x,(My/2)+5,x,(My/2)-5,al_map_rgb(0,0,0),2);
            al_draw_line((Mx/2)-5,x,(Mx/2)+5,x,al_map_rgb(0,0,0),2);
        }

        for(int x=-200;x<200;x++)
        {
            if(pesos[0]!=0 && pesos[1]!=0)
            {

                    al_draw_pixel((Mx/2)+x,(My/2)+((float)pesos[0]/(float)pesos[1])*x-((float)umbral/(float)pesos[1])*escala,al_map_rgb(0,0,0));

            }
        }
          al_rest(0.01);

            for(int s=0;s<operaciones;s++)
            {
                if(salida[s]==1)
                {
                    al_draw_filled_circle((Mx/2)+entradas[s][0]*escala,(My/2)-entradas[s][1]*escala,4,al_map_rgb(255,0,0));
                }
                else
                {
                    al_draw_filled_circle((Mx/2)+entradas[s][0]*escala,(My/2)-entradas[s][1]*escala,4,al_map_rgb(0,0,255));
                }
            }
            al_flip_display();

            printf("----------%d----------",epocas);
            error=0;
            for(int x=0;x<operaciones;x++)
            {

                resultado=0;
                for(int i=0;i<valores;i++)
                {
                    resultado += entradas[x][i]*pesos[i];
                }

                if(resultado>umbral)
                {
                    resultado=1;
                }
                else
                {
                    resultado=0;
                }

                if( resultado==1 )
                {
                    printf("\nR=1\t");
                    if(salida[x]!=1)
                    {
                        error=1;
                        printf("%d %d| %d ... Mal\n",entradas[x][0],entradas[x][1],salida[x]);
                        umbral++;
                        for(int w=0;w<valores;w++)
                        {
                            pesos[w]+=(salida[x]-resultado)*entradas[x][w];
                        }
                    }
                    else
                    {
                        printf("%d %d| %d ... Bien\n",entradas[x][0],entradas[x][1],salida[x]);
                    }

                }
                else
                {
                    printf("\nR=0\t");
                    if(salida[x]!=0)
                    {
                        error=1;
                        printf("%d %d| %d ... Mal\n",entradas[x][0],entradas[x][1],salida[x]);
                        umbral--;
                        for(int w=0;w<valores;w++)
                        {
                            pesos[w]+=(salida[x]-resultado)*entradas[x][w];
                        }
                    }
                    else
                    {
                        printf("%d %d| %d ... Bien\n",entradas[x][0],entradas[x][1],salida[x]);
                    }
                }
            }

            printf("\nepocas: %d\n",epocas);
            printf("\numbral: %d\n",umbral);
            printf("\nPesos:\n");
            for(int y=0;y<valores;y++)
            {
                printf("\n\tW%d: %d\n",y,pesos[y]);
            }

            if(error==0)
            {
                printf("\nPerceptron entrenado\n");
                while(1)
                {
                    al_get_keyboard_state(&estadoTeclado);
                    if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE))
                    {
                        return 0;
                    }
                }
            }
            if(epocas>=10000)
            {
                printf("\nFin de 10 000 epocas\n");
                while(1)
                {
                    al_get_keyboard_state(&estadoTeclado);
                    if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE))
                    {
                        return -1;
                    }
                }
            }
            epocas++;
        //}
    }
}

int main(void)
{
    int entradas[4][2];
    entradas[0][0] = 0;
    entradas[0][1] = 0;

    entradas[1][0] = 0;
    entradas[1][1] = 1;

    entradas[2][0] = 1;
    entradas[2][1] = 0;

    entradas[3][0] = 1;
    entradas[3][1] = 1;
    int salida[4];
    int pesos[2];
    int umbral;
    char seleccion;
    printf("\na) Puerta AND\nb) Puerta OR\nc) Puerta NAND \nd) Puerta NOR\ne) Puerta XOR\n");
    seleccion = getchar();

    switch (seleccion)
    {
    case 'a':
        salida[0] = 0;
        salida[1] = 0;
        salida[2] = 0;
        salida[3] = 1;
        break;
    case 'b':
        salida[0] = 0;
        salida[1] = 1;
        salida[2] = 1;
        salida[3] = 1;
        break;
    case 'c':
        salida[0] = 1;
        salida[1] = 1;
        salida[2] = 1;
        salida[3] = 0;
        break;
    case 'd':
        salida[0] = 1;
        salida[1] = 0;
        salida[2] = 0;
        salida[3] = 0;
        break;
    case 'e':
        salida[0] = 0;
        salida[1] = 1;
        salida[2] = 1;
        salida[3] = 0;
        break;
    default:
        break;
    }
    printf("Introduce el peso 1:");
    scanf("%d",&pesos[0]);
    printf("Introduce el peso 2:");
    scanf("%d",&pesos[1]);
    printf("Introduce el valor umbral:");
    scanf("%d",&umbral);

    perceptron(4,2,entradas,salida,pesos,umbral);
    return 0;
}

