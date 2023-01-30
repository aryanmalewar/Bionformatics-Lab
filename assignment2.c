#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


//Neutal polar - Asn, Gln, Ser, Thr, Cys, Met, His
//-ve charge - Asp, Glu
//+ve charge - Arg, Lys
//aromatic - Phe, Tyr, Trp
//hydrophobic - Gly, Alo, Val, Leu, Ile, Pro

int main(){
	
	FILE *fpt1;
	fpt1 = fopen("1asy.pdb", "r");
	char line[100], word[5], res_name[4], store_res_name[20000][4], res_num[5], atom_name[4], chain_id[20000], store_atom_name[20000][4];
	float p, P, n, N, a, A, np, NP, h, H, pu, PU, py, PY, current_res_num; 
	int i, c1, flag, total_rna, total_pro, store_res_num[20000];

	c1 = flag = 0;
	p = P = N = n = a = A = np = NP = h = H = PU = PY = 0.0;	

	while(fgets(line, 100, fpt1) != NULL){
			
		for(i=0; i<4; i++) word[i] = line[i];
		word[4] = '\0'; //word array is read as string

		if(strcmp(word, "ATOM") == 0){ 
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

			if(strcmp(res_name, "A") != 0 || strcmp(res_name, "U") != 0 || strcmp(res_name, "G") != 0 || strcmp(res_name, "C") != 0){
				
				for(i =0; i < 3; i++) atom_name[i] = line[13+i];
					
				atom_name[4] = '\0';
				strcpy(store_atom_name[c1], atom_name);
				if(strcmp(atom_name, "N  ") == 0 || (strcmp(atom_name, "CA  ") == 0 || (strcmp(atom_name, "C  ") == 0 || (strcmp(atom_name, "O  ") == 0))) backbone++;
				else sidechain++;
			}

			current_res_num = atoi(res_num);
			if(flag != current_res_num) 

				flag = current_res_num;
			
				if(strcmp(store_res_name[c1],"LYS") == 0 || strcmp(store_res_name[c1],"ARG") == 0) p++;
				else if(strcmp(store_res_name[c1],"ASP") == 0 || strcmp(store_res_name[c1],"GLU") == 0)  n++;
				else if(strcmp(store_res_name[c1],"PHE") == 0 || strcmp(store_res_name[c1],"TYR") == 0 || strcmp(store_res_name[c1],"TRP") == 0)  a++;
				else if(strcmp(store_res_name[c1],"GLY") == 0 || strcmp(store_res_name[c1],"ALO") == 0 || strcmp(store_res_name[c1],"VAL") == 0 || strcmp(store_res_name[c1],"LEU") == 0 || strcmp(store_res_name[c1],"ILE") == 0 || strcmp(store_res_name[c1],"PRO") == 0)  h++;
				else if(strcmp(store_res_name[c1],"ASN") == 0 || strcmp(store_res_name[c1],"GLN") == 0 || strcmp(store_res_name[c1],"SER") == 0 || strcmp(store_res_name[c1],"THR") == 0 || strcmp(store_res_name[c1],"CYS") == 0 || strcmp(store_res_name[c1],"MET") == 0 || strcmp(store_res_name[c1], "HIS"))  np++;
				//else if(strcmp(store_res_name[c1],"A") == 0 || strcmp(store_res_name[c1],"G") == 0) pu++;
				//else if(strcmp(store_res_name[c1],"C") == 0 || strcmp(store_res_name[c1],"u") == 0) py++;

				c1++;
		}

	}

	P = ((p/(p + n + a + np +h))* 100);
	N = ((n/(p + n + a + np +h))* 100);
	A = ((a/(p + n + a + np +h))* 100);
	NP = ((np/(p + n + a + np +h))* 100);
	H = ((h/(p + n + a + np +h))* 100);
	//PU = (pu/(pu + py))*100;
	//PY = (pu/(pu + py))*100;
	total_rna = pu + py;
	total_pro = p + n + a + np +h;

	return 0;
}

