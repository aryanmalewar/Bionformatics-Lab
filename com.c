#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int main(){

	char line[100], word[5], x[9], y[9], z[9], s1_num[6], atm_name[6], res_name[4], chain_id[20000], res_num[5], store_atm_name[20000][4], store_res_name[20000][4];
	float store_x[20000], store_y[20000], store_z[20000], total_x, total_y, total_z, cm_x, cm_y, cm_z;
	FILE *fpt1, *fpt2; 

	fpt1 = fopen("1asy.pdb", "r");
	fpt2 = fopen("out.pdb", "w");

	while(fgets(line, 100, fpt1) != NULL){
		
		for(i=0; i<4; i++) word[i] = line[i];
		word[4] = '\0'; //word array is read as string

		if(strcmp(word, "ATOM") == 0){ 
			//atom number
			for(i=0; i<5; i++){
				s1_num[i] = line[i+6];
			}
				s1_num[5] = '\0';
				store_atm_num[c1] = atoi(s1_num);//atoi = string to int
			
			//atom name
			for(i=0; i<3; i++){
				atm_name[i] = line[i+13];
			}
				atm_name[3] = '\0';
				strcpy(store_atm_name[c1], atm_name);
			
			//residue name
			for(i=0; i<3; i++){
				res_name[i] = line[i+17];
			}
				res_name[3] = '\0';
				strcopy(store_res_name[c1], res_name);
			
			//chain id
			chain_id[c1] = line[21];

			//residue number
			for(i=0; i<4; i++) res_num[i] = line[i+22];
			res_num[4] = '\0';
			store_res_num[c1] = atoi(res_num);

			//x coordinate
			for(i=0; i<8; i++) x[i] = line[i+30];
			x[8] = '\0';
			store_x[c1] = atof(x); //atof = string to float

			  
			//y coordinate
			for(i=0; i<8; i++) y[i] = line[i+38];
			y[8] = '\0';
			store_y[c1] = atof(y); //atof = string to float

			//z
			for(i=0; i<8; i++) z[i] = line[i+46];
			z[8] = '\0';
			store_z[c1] = atof(z); //atof = string to float

			c1++;
			}
			}

	for(i=0; i<c1; i++){
		fprintf(fpt2, "ATOM %5d %s %s %c%4d %8.3f%8.3f%8.3f\n", store_atm_num[i], store_atm_name[i], store_res_name[i], chain_id[i], store_res_num[i], store_x[i], store_y[i], store_z[i]);
	}

	// to find centre of mass
	total_x = total_y = total_z = 0.0;
	for(i=0; i<c; i++){
		total_x = total_x + store_x[i];
		total_y = total_y + store_y[i];
		total_z = total_z + store_z[i];
		
	}

	cm_x = total_x / c1;
	cm_y = total_y / c1;
	cm_z = total_z / c1;
	
        fprintf(
