#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *f1;
	int i, c1, flag, total_prot, total_rna, curr_res_num, backbone = 0, sidechain = 0;
	float posi, nega, aro, neutpol, hydphob, pu, py; // positive, negative, aromatic, neutral polar, hydrophobic amino acids.
	char word[5], line[100], res_name[4], res_num[20000], atom_name[4], store_res_name[20000][4], store_atom_name[20000][4];
	float P, N, A, NP, H, PU, PY;

	f1 = fopen("1asy.pdb", "r");
	c1 = 0;
	flag = 0;
	posi = 0.0, nega = 0.0, aro = 0.0, neutpol = 0.0, hydphob = 0.0, pu = 0.0, py = 0.0, P = 0.0, N = 0.0, A = 0.0, NP = 0.0, H = 0.0, PU = 0.0, PY = 0.0;
	curr_res_num = 0;


	while(fgets(line, 100, f1)!=NULL)
	{
		for(i=0; i<4; i++)
		{
			word[i] = line[i];
			word[4] = '\0';
	 	}

		if(strcmp(word, "ATOM") == 0)
		{
			for(i=0; i<3; i++)
			{	
				res_name[i] = line[17+i];
				res_name[3] = '\0';
				strcpy(store_res_name[c1], res_name); //store residue name
			}

			for(i=0; i<4; i++)
			{
				res_num[i] = line[22+i];
				res_num[4] = '\0';
			}

			curr_res_num = atoi(res_num); // store residue number

			if(strcmp(res_name, "  A")!=0 && strcmp(res_name, "  U")!=0 && strcmp(res_name, "  C")!=0 && strcmp(res_name, "  G")!=0) //if atom is not from RNA
			{
				for(i=0; i<3; i++)
				{
					atom_name[i] = line[13+i];
					atom_name[4] = '\0';
					strcpy(store_atom_name[c1], atom_name);
				}
	

				if(strcmp(atom_name, "N  ") == 0 || strcmp(atom_name, "CA ") == 0 || strcmp(atom_name, "C  ") == 0 || strcmp(atom_name, "O  ") == 0)
				{
					backbone++;
				}
				else
				{
					sidechain++;
				}
				//if atom is N, CA, C, O it is a backbone atom, otherwise it is a sidechain atom.
			}


			if(flag!=curr_res_num)
			{
				flag = curr_res_num;

				if(strcmp(store_res_name[c1], "LYS") == 0 || strcmp(store_res_name[c1], "ARG") == 0)
					posi++;
				else if(strcmp(store_res_name[c1], "ASP") == 0 || strcmp(store_res_name[c1], "GLU") == 0)
					nega++;
				else if(strcmp(store_res_name[c1], "TYR") == 0 || strcmp(store_res_name[c1], "PHE") == 0 || strcmp(store_res_name[c1], "TRP") == 0)
					aro++;
				else if(strcmp(store_res_name[c1], "ASN") == 0 || strcmp(store_res_name[c1], "GLN") == 0 || strcmp(store_res_name[c1], "SER") == 0 || strcmp(store_res_name[c1], "THR") == 0 || strcmp(store_res_name[c1], "CYS") == 0 || strcmp(store_res_name[c1], "MET") == 0 || strcmp(store_res_name[c1], "HIS") == 0)
					neutpol++;
				else if(strcmp(store_res_name[c1], "GLY") == 0 || strcmp(store_res_name[c1], "ALA") == 0 || strcmp(store_res_name[c1], "VAL") == 0 || strcmp(store_res_name[c1], "LEU") == 0 || strcmp(store_res_name[c1], "ILE") == 0 || strcmp(store_res_name[c1], "PRO") == 0)
					hydphob++;
				else if(strcmp(store_res_name[c1], "  A") == 0 || strcmp(store_res_name[c1], "  G") == 0)
					pu++;
				else if(strcmp(store_res_name[c1], "  U") == 0 || strcmp(store_res_name[c1], "  C") == 0)
					py++;

				c1++;
			}
		}
	}
	
	P = ((posi/(posi+nega+aro+neutpol+hydphob))*100);
	N = ((nega/(posi+nega+aro+neutpol+hydphob))*100);
	A = ((aro/(posi+nega+aro+neutpol+hydphob))*100);
	NP = ((neutpol/(posi+nega+aro+neutpol+hydphob))*100);
	H = ((hydphob/(posi+nega+aro+neutpol+hydphob))*100);
      total_rna = (pu+py);
	PU = ((pu/total_rna)*100.0);
	PY = ((py/total_rna)*100.0);
	total_prot = (posi + nega + aro + hydphob + neutpol);
	
	printf("Total amino acids in protein chain is %d\n", total_prot);
	printf("Percentage of positively charged amino acid residues is %6.2f %%\n", P);
	printf("Percentage of negatively charged amino acid residues is %6.2f %%\n", N);
	printf("Percentage of aromatic amino acid residues is %6.2f %%\n", A);
	printf("Percentage of hydrophobic amino acid residues is %6.2f %%\n", H);
	printf("Percentage of neutral polar amino acid residues is %6.2f %%\n", NP);
	printf("Total nucleotide bases in RNA chain is %d\n", total_rna);
	printf("Percentage of purine bases is %6.2f %%\n", PU);
	printf("Percentage of pyrimidine bases is %6.2f %%\n", PY);
	printf("Total number of backbone atoms is %d\n", backbone);
	printf("Total number of sidechain atoms is %d\n", sidechain);
	printf("Percentage of backbone atoms is %6.2f %%\n", ((backbone*100.0)/(backbone+sidechain)));
	printf("Percentage of sidechain atoms is %6.2f %%\n", ((sidechain*100.0)/(backbone+sidechain)));
  
  return 0;
}
		


