#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>

using namespace std;


// flush
void flush()//L'usage de flush permet de garantir que le message sera affiché avant de passer à la suite du programme.
{
	while( getchar() != '\n' )
		continue;//De cette façon, vous pouvez tester que l'utilisateur n'appuiera pas sur "Entrée" sans avoir inséré numéro.
}

// programme principal


int main()
{
    int decalage = 0;
	char nom_fichier[256];
	char text[256];
	char choix = 'c';
	// choix
	cout<<"Code de Cesar\n";
	cout<<"\nSaisir le decalage ou la cle de votre texte a chriffrer: ";
	cin>> decalage;
	flush();//L'usage de flush permet de garantir que le message sera affiché avant de passer à la suite du programme.
	cout<<"\nSaisir le nom du fichier a chriffrer: ";// C'est ici que sera stocké le texte entre a écran ainsi que le résultat aprés opération.
	cin>> nom_fichier;
	flush();

	cout<< "\n vous voulez faire un Chiffrement [c] ou Dechiffrement [d] : ";//choix de operation de criptage
	cin>>choix;
	flush();




	cout<<"\nEntrer votre text: ";
	cin.getline(text,255);//C'est un moyen de lire une ligne entière d'entrée de console dans une variable. "getline est plus facile à utiliser pour lire des séquences d'entrées que d'autres fonctions telles que l'opérateur >>, qui est plus orienté vers les mots ou les caractères.
	// synthèse
	switch( choix )

	{
	case 'c' :
		cout<<"\n Vous avez demander le chiffrement du fichier "<<nom_fichier<< " avec un decalage de \n"<<decalage;
		{
			int index;
			int taille_fichier = 0;
			FILE * fichier_avant = NULL;
			FILE * fichier_apres = NULL;
			int taille_memoire_tamon = 1024;
			char * memoire_tampon = NULL;//Déclaratio du fichier trasitoire
			// allocation
			memoire_tampon = (char *)malloc(taille_memoire_tamon);//libere la memoire pour le fichier trasitoire
			if(text[0]!='\n')// verifier si l'utilisateur a entrer du text
            {

            strcpy(memoire_tampon, text);//Copier la chaîne  pointée par TEXT dans le tableau par memoire_tampon, y compris le caractère nul de fin (et s'arrête à ce point).
            taille_fichier = strlen(text);//Le strlen () prend comme argument une chaîne d'octets terminée par null et renvoie sa longueur. u
			}
			else{
			// mise en mémoire tampon
			fichier_avant = fopen( nom_fichier, "r" );
			taille_fichier = fread( memoire_tampon, 1, taille_memoire_tamon, fichier_avant );
			fclose( fichier_avant );
			}

			// chiffrement dans le mémoire tampon
			for( index = 0; index != taille_fichier; ++index )
			{
				// chiffrement des majuscules
				if( memoire_tampon[ index ] >=65 && memoire_tampon[ index ] < 91 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 65 ) + decalage ) % 26 + 65;//recherche code ASCII
				// chiffrement des minuscules
				if( memoire_tampon[ index ] >=97 && memoire_tampon[ index ] < 123 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 97 ) + decalage ) % 26 + 97;
			}
			// mise a jour du fichier
			fichier_apres = fopen( nom_fichier, "w" );
			fwrite( memoire_tampon, 1, taille_fichier, fichier_apres );
			cout<< "\nLe resultat du chiffrement est : "<<memoire_tampon;
			fclose( fichier_apres );
			// desallocation
			free( memoire_tampon);
		}
		return 0;
	case 'd' :
		cout<<"\nVous avez demander le dechiffrement du fichier " <<nom_fichier<< " avec un decalage de \n"<< decalage;
		{
			int index;
			int taille_fichier = 0;
			FILE * fichier_avant = NULL;
			FILE * fichier_apres = NULL;
			int taille_memoire_tamon = 1024;
			char * memoire_tampon = NULL;
			// allocation
			memoire_tampon = (char *)malloc(taille_memoire_tamon);
			if(text[0]!='\n')// verifier si l'utilisateur a entrer du text
            {

            strcpy(memoire_tampon, text);
            taille_fichier = strlen(text);
			}
			else{
			// mise en mémoire tampon
			fichier_avant = fopen( nom_fichier, "r" );
			taille_fichier = fread( memoire_tampon, 1, taille_memoire_tamon, fichier_avant );
			fclose( fichier_avant );
			}

			// chiffrement dans le mémoire tampon
			for( index = 0; index != taille_fichier; ++index )
			{
				// chiffrement des majuscules
				if( memoire_tampon[ index ] >=65 && memoire_tampon[ index ] < 91 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 65 ) - decalage ) % 26 + 65;//recherche code ASCII
				// chiffrement des minuscules
				if( memoire_tampon[ index ] >=97 && memoire_tampon[ index ] < 123 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 97 ) - decalage ) % 26 + 97;
			}
			// mise a jour du fichier
			fichier_apres = fopen( nom_fichier, "w" );
			fwrite( memoire_tampon, 1, taille_fichier, fichier_apres );
			cout<< "\nLe resultat du dechiffrement est : "<<memoire_tampon;
			fclose( fichier_apres );
			// desallocation
			free( memoire_tampon);
		}
		return 0;
	default:
		return -1;
	}

}
