#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




double b_b = 0.2497;
double b_d = 5.16;
double a_d = 0.3105;
double a_h = 64.3;
double Vs[3][300];
double V[300];  

double velRad(double ra, double mbu, double mdi, double mha){
       return ra* mbu/pow(ra*ra + b_b*b_b ,0.75) + ra*mdi/pow(ra*ra +pow(b_d+a_d,2) ,0.75) + mha/pow(ra*ra+ a_h*a_h,0.25);
       
       }
       
double compa1(){
       double chi = 0;
       int k = 0;
       while(k<300){
                    chi -= pow((Vs[1][k]-V[k])/50000,2);
                    k+=1;
                    }
       return exp(chi);       
       }
       
double compa2(){
       double chi = 0;
       int k = 0;
       while(k<300){
                    chi -= pow((Vs[2][k]-V[k])/50000,2);
                    k+=1;
                    }
       return exp(chi);
       
       }
       
double ran(){
       return (double) rand() / RAND_MAX;
       }

double normal(double media, double sigma){
       double u1 = ran();
       double u2 = ran();
       double sam = sqrt(-2*log(u2))*sin(2*3.1415926*u1);
       return sigma*sam+media;
       
       }

int main(){
    
    time_t tiempo;
    srand((unsigned) time(&tiempo));

    double R[300];

    FILE *file = fopen("RadialVelocities.dat", "r");
    char linia[4096];

    char *prueba = fgets(linia, sizeof(linia), file);

    int i = 0;
    while(i<300)
    {
     prueba = fgets(linia, sizeof(linia), file);
        double r;
        double v;
     sscanf(prueba, "%lf %lf" , &r,&v);
     V[i] = v;
     R[i] = r;
     i+=1;

     }


    
    double MaB[3];
    double MaH[3];
    double MaD[3];
    double l[3];


    int j = 0;
    for(j=0;j<3;j+=1){
                      MaB[j] = 1./3;
                      MaD[j] = 1./3;
                      MaH[j] = 1./3;                      
                       }
    int veces = 8000;

                         int k = 0;
                         for(k = 0;k<300;k+=1){
                               Vs[1][k] = velRad(R[k], MaB[0], MaD[0], MaH[0]);
                              }
    l[0] = compa1();


    for(j = 0;j<veces;j+=1){

    double porcentaje = 0.15     ;     
                         MaB[2] = normal(MaB[1], porcentaje);
                         MaD[2] = normal(MaD[1], porcentaje);
                         MaH[2] = normal(MaH[1], porcentaje);
                         int k = 0;
                         for(k = 0;k<300;k+=1){
                               Vs[0][k] = velRad(R[k], MaB[0], MaD[0], MaH[0]);
                               Vs[1][k] = velRad(R[k], MaB[1], MaD[1], MaH[1]);
                               Vs[2][k] = velRad(R[k], MaB[2], MaD[2], MaH[2]);
                               }
                               

                       l[2] = compa2();
                       l[1] = compa1();
                       
                                   if(l[2] > l[0]){
                                             l[0] = l[2];
                                             MaB[0] = MaB[2];
                                             MaD[0] = MaD[2];
                                             MaH[0] = MaH[2];                                             
                                             }

                       
                       double alpha = l[2]/l[1];
                       
                       if(alpha>=1){
                                   MaB[1] = MaB[2];
                                   MaD[1] = MaD[2];
                                   MaH[1] = MaH[2];
                                   if(l[2] > l[0]){
                                             l[0] = l[2];
                                             MaB[0] = MaB[2];
                                             MaD[0] = MaD[2];
                                             MaH[0] = MaH[2];                                             
                                             }
                                   }
                       else{
                            double beta = ran();
                            if(beta>=alpha){
                                   MaB[1] = MaB[2];
                                   MaD[1] = MaD[2];
                                   MaH[1] = MaH[2];
                                            }                         
                            }
                       
                       
                       }
          
          
          
    FILE *imprimir = fopen("dato.dat", "w+");
    for(j=0;j<2000;j+=1){
                        fprintf(imprimir, "%f %f\n", j*300.0/2000., velRad(j*300.0/2000,MaB[0], MaD[0], MaH[0]));
                        }

 
    fclose(imprimir);   
    printf("las constantes son %f %f %f\n", MaB[0]*MaB[0], MaD[0]*MaD[0], MaH[0]*MaH[0]);
    FILE *bayf = fopen("bayfit.dat", "w+");
    fprintf(bayf,"%f %f %f", MaB[0], MaD[0], MaH[0]);
    fclose(bayf);

    
    
    
    
}


