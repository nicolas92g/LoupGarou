/*****************************************************************//**
 * \file   jeux.h
 * \brief  des fonctions pour gérer la partie
 * 
 * \author Thibault GARCIA-MEGEVAND, Nicolas GUILLOT, david DEL CAMPO 
 * \date   May 2021
 *********************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include "fonction.h"
#include <assert.h>
/**
 * @brief cette fonction permet de remplir le tableau des roles a partir du nombre de joueurs
 * @param tableau des roles a remplir
 * @param nbr de joueurs qui jouent
 */
void attribution(Role* tabRoles, unsigned short nbrDeJoueurs);
/**
 * @brief permet a l'ensembles des joueurs de voter pour un capitaine
 * @param un pointeur vers l'interface graphique
 * @return le joueur qui deviens capitaine
 */
int voteCapitaine(GUI* input);
/**
 * @brief permet au joueurs vivant de voter pour un joueur qu'il souhaitent tuer
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 * @param le nbr de joueurs en vie
 * @param le joueur qui est capitaine
 * @return le joueur que le vote a désigné
 */
int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie, int caseCapitaine);
/**
 * @brief permet de d'effectuer ce que doit faire la voyante a chaque tours
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 */
void fVoyante(GUI* input, Role* tabRoles);
/**
 * @brief permet au loups de voter pour un joueur a tuer
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 * @param le nbr de joueurs en vie
 * @return le joueur que les loups ont tué
 */
int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie);
/**
 * @brief permet a cupidon d'effectuer ce qu'il doit faire a chaque tour
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 */
void fCupidon(GUI* input, Role* tabRoles, unsigned short tabCupidon[]);
/**
 * @brief montre a la petite fille les joueurs qui sont des loups garous
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 * @param le nbr de joueurs en vie
 */
void fPetiteFille(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie);
/**
 * @brief permet au voleur de choisir une des 2 des cartes qui n'a pas été distribuée
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 */
void fVoleur(GUI* input, Role* tabRoles);
/**
 * @brief permet a la sorciere de d'effectuer ce qu'elle doit faire a chaque tours
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 * @param un pointeur vers la variable qui stocke si elle a encore sa potion tuer
 * @param un pointeur vers la variable qui stocke si elle a encore sa potion sauver
 * @param le joueur qui a été tué par les loups garou
 * @param le nbr de joueurs enn vie
 * @param un pointeur pour indiquer le joueur que veut la sorciere veut tuer (ne modifie pas la variable pointée sinon)
 * @return si la sorciere souhaite sauver le joueurs tué par les loups garou
 */
bool fSorciere(GUI* input, Role* tabRoles, bool* peutTuer, bool* peutSauver, short joueurTuee, unsigned short nbrDeJoueurEnVie, unsigned short* joueursTueParLaSorciere);
/**
 * @brief c'est la fonction principale qui gere le déroulement d'une partie
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 */
void deroulementDeLaPartie(GUI* input, Role* roles);
/**
 * @brief permet au chasseur de choisir un joueur a tuer avant de mourrir
 * @param un pointeur vers l'interface graphique
 * @param un tableau de tous les roles
 * @return le joueur que le chasseur veut voir mourrir
 */
int fChasseur(GUI* input, Role* tabRoles);
/**
 * @brief permet de trouver un role dans le tableau des roles
 * @param un tableau de tous les roles 
 * @param la taille de ce tableau
 * @param le role que l'on souhaitent rechercher
 * @return le premier joueur qui a ce role ou 20 si le role n'est pas present dans le tableau
 */
unsigned short LeRoleExiste(Role* roles, unsigned short size, Role role);
