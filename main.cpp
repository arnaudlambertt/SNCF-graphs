#include "sources/Graphe.h"
#include <windows.h>

bool menu(Graphe& a, std::string nomFichier);
int optionVulnerabilite(int& nb, int taille, std::string saisie, bool orientation);

///Varibale globale qui permet de mettre de la couleur sur le texte de la console
HANDLE texteConsole=GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
    bool continuer=true;
    do
    {
        std::string nomFichier;
        Graphe a(nomFichier);
        continuer=menu(a, nomFichier);
    }
    while(continuer);
    return 0;
}

///Menu d'options
bool menu (Graphe& a, std::string nomFichier)
{
    ///Variable de saisie, de choix et d'indice (pour afficher les indices dans le Svgfile)
    std::string saisie;
    char choix='0';
    bool indices=false;

    ///Tant qu'on ne quitte pas
    do
    {
        ///On dessine le graphe charg�
        a.dessiner(nomFichier, indices);

        ///Magnifique dessin de menu �crit en majuscule
        SetConsoleTextAttribute(texteConsole, 3);
        std::cout<<std::endl<<"  ____    _____     ___________     ____    ____     ____     ____ "<<std::endl
                 <<"/      \\/      \\   |    _______|   |    \\  |    |   |    |   |    |"<<std::endl
                 <<"|              |   |   |           |     \\ |    |   |    |   |    |"<<std::endl
                 <<"|   |\\    /|   |   |   |____       |      \\|    |   |    |   |    |"<<std::endl
                 <<"|   | \\__/ |   |   |    ____|      |            |   |    |   |    |"<<std::endl
                 <<"|   |      |   |   |   |           |    |\\      |   |    |___|    |"<<std::endl
                 <<"|   |      |   |   |   |_______    |    | \\     |   |             |"<<std::endl
                 <<"|___|      |___|   |___________|   |____|  \\____|   |_____________|"<<std::endl;

        ///On informe sur l'orientation du graphe
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<std::endl<<std::endl<<"Le graphe est ";
        SetConsoleTextAttribute(texteConsole, 3);
        if(a.getOrientation())
            std::cout<<"oriente";
        else
            std::cout<<"non oriente";
        std::cout<<std::endl;
        ///On affiche les diff�rentes options
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<std::endl<<std::endl<<"1. ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Charger";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" un graphe"<<std::endl<<std::endl<<"2. ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Changer";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" le systeme de ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"ponderations"<<std::endl;
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<std::endl<<"3. ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Calculer";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" et ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Sauvegarder";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" les differents ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"indices";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" de ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"centralite"<<std::endl;
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<std::endl<<"4. ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Tester";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" la ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"vulnerabilite";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" du graphe"<<std::endl;
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<std::endl<<"5. Etude de la ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"k-connexite ";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<"du graphe"<<std::endl;
        std::cout<<std::endl<<"6. Etude de ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"centralite intermediaire";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" avec ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"flots";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" (possibilite de ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"rupture";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" d'un ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"troncon";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<")"<<std::endl;
        std::cout<<std::endl<<"7. ";
        SetConsoleTextAttribute(texteConsole, 14);
        std::cout<<"Quitter";
        SetConsoleTextAttribute(texteConsole, 15);
        std::cout<<" l'application"<<std::endl<<std::endl;
        SetConsoleTextAttribute(texteConsole, 3);
        std::cout<<"> ";
        SetConsoleTextAttribute(texteConsole, 15);
        ///Blindage de la saisie
        std::cin>>saisie;
        if(saisie.length()>1)
        {
            choix='d';
        }
        else
            choix=saisie.front();
        std::cout<<std::endl;

        switch(choix)
        {

        ///On change de graphe
        case '1':
        {
            indices=false;

            return true;
        }
        break;

        ///On charge un nouveau fichier de pond�ration
        case '2':
        {
            indices=false;
            a.ponderation();
        }
        break;

        ///On calcule, affiche et sauvegarde les diff�rents indices de centralit�
        case '3':
        {
            std::vector<std::pair<int, double>> centralite_degres = a.centraliteDegre ();
            std::vector<std::pair<double, double>> vecteurPropre=a.vecteurPropre();
            std::vector<std::pair<double, double>> vecteurProximite=a.vecteurProximite();
            std::pair<std::vector<std::pair<double,double>>,std::vector<std::pair<Arete*,std::pair<double,double>>>> intermediarite=a.intermediarite();
            a.sauvegarder(centralite_degres, vecteurPropre, vecteurProximite, intermediarite, nomFichier);
            indices=true;
        }
        break;

        ///On test la vuln�rabilit� du graphe apr�s la suppression d'ar�te(s)
        case '4':
        {
            int nb=0;
            if(optionVulnerabilite(nb, a.getTaille(), saisie, a.getOrientation())=='1')
                ///Connexit�
                if(!a.getOrientation())
                    a.testConnexite(nb);
                ///Forte connexit�
                else
                    a.testForteConnexite(nb);
            ///Comparaison des indices avant et apr�s suppression
            else
                a.comparaisonIndices(nb);
        }
        break;

        ///On test la k_connexit�
        case '5':
            if(!a.getOrientation())
            {
                a.kAretesConnexe();
                a.kSommetsConnexite();
            }
            ///Si le graphe est orient�, on indique que cette option est impossible
            else
            {
                std::cout<<"Le graphe est ";
                SetConsoleTextAttribute(texteConsole, 3);
                std::cout<<"oriente";
                SetConsoleTextAttribute(texteConsole, 15);
                std::cout<<", cette option est ";
                SetConsoleTextAttribute(texteConsole, 12);
                std::cout<<"invalide"<<std::endl;
                SetConsoleTextAttribute(texteConsole, 15);
            }
            break;

        ///On compare les indices interm�diaires avec la m�thode de flot
        case '6':
        {
            std::vector<double> flotAvant=a.intermediariteFlots();
            std::vector<double> flotApres(a.getOrdre(), 0);
            a.comparaisonICIFlots(flotAvant, flotApres, saisie);
        }
        break;


        ///Magnifique dessin pour vous dire "A tr�s bientot !"
        case '7':
            SetConsoleTextAttribute(texteConsole, 3);
            std::cout<<" _________    ____     ____    __________ "<<std::endl
                     <<"/    _    \\   \\   \\   /   /   |   _______|"<<std::endl
                     <<"|   /_\\   |    \\   \\_/   /    |   |"<<std::endl
                     <<"|    _____/     \\       /     |   |____"<<std::endl
                     <<"|    __   \\      \\     /      |    ____|"<<std::endl
                     <<"|   /  \\   |      |   |       |   |"<<std::endl
                     <<"|   \\__/   |      |   |       |   |______"<<std::endl
                     <<"\\__________/      |___|       |__________|"<<std::endl<<std::endl;
            SetConsoleTextAttribute(texteConsole, 15);
            break;

        ///On indique que la saisie de l'utilisateur est invalide, et on lui demande de ressaisir
        default :
            std::cout<<"Saisie ";
            SetConsoleTextAttribute(texteConsole, 12);
            std::cout<<"invalide";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<", veuillez ";
            SetConsoleTextAttribute(texteConsole, 9);
            std::cout<<"ressaisir";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<" une option"<<std::endl;
            break;
        }

    }
    while(choix!='7');
    return false;
}

///On test les vuln�rabilit�s du graphe (suppression de d'ar�te(s))
int optionVulnerabilite(int& nb, int taille, std::string saisie, bool orientation)
{
    char option='0';
    ///On demande comment tester la vuln�rabilit�
    std::cout<<"Comment voulez vous ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"tester";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" la ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"vulnerabilite";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" du graphe ?"<<std::endl<<std::endl<<"    1. ";
    SetConsoleTextAttribute(texteConsole, 12);
    std::cout<<"Supprimer";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" une ou plusieurs";
    SetConsoleTextAttribute(texteConsole, 12);
    std::cout<<" aretes";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" et ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"tester";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" la ";
    SetConsoleTextAttribute(texteConsole, 14);
    ///En fonction de l'orientation du graphe, on propose diff�rentes options
    if(!orientation)
        std::cout<<"connexite";
    else
        std::cout<<"forte connexite";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" du graphe"<<std::endl<<std::endl<<"    2. ";
    SetConsoleTextAttribute(texteConsole, 12);
    std::cout<<"Supprimer";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" une ou plusieurs ";
    SetConsoleTextAttribute(texteConsole, 12);
    std::cout<<"aretes";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<", ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"recalculer";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" et ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"comparer";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" les ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"indices";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" de ";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"centralite"<<std::endl<<std::endl;
    SetConsoleTextAttribute(texteConsole, 15);
    SetConsoleTextAttribute(texteConsole, 3);
    std::cout<<"> ";
    SetConsoleTextAttribute(texteConsole, 15);
    ///Blindage de la saisie
    do
    {
        std::cin>>saisie;
        if(saisie.length()>1)//si on saisit plus d'un caract�re
        {
            option='d';//on attribut au choix une valeur default
        }
        else
            option=saisie.front();//le choix correspond au premier caract�re de la chaine
        ///On indique si la saisie de l'utilisateur est invalide
        if(option!='1' && option!='2')
        {
            std::cout<<std::endl<<"Cette option est ";
            SetConsoleTextAttribute(texteConsole, 12);
            std::cout<<"invalide";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<", veuillez ";
            SetConsoleTextAttribute(texteConsole, 9);
            std::cout<<"ressaisir";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<" : ";
        }
    }
    while(option!='1' && option!='2');

    ///On demande le nombre d'ar�te � supprimer
    std::cout<<std::endl<<"Combien d'";
    SetConsoleTextAttribute(texteConsole, 14);
    std::cout<<"aretes";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" voulez vous ";
    SetConsoleTextAttribute(texteConsole, 12);
    std::cout<<"supprimer";
    SetConsoleTextAttribute(texteConsole, 15);
    std::cout<<" ? ";

    ///On blinde la saisie
    do
    {
        ///On indique si la saisie est invalide, et on demande de ressaisir
        std::cin>>nb;
        if((nb<0)||(nb>taille))
        {
            std::cout<<std::endl<<"Vous avez saisie un nombre ";
            SetConsoleTextAttribute(texteConsole, 12);
            std::cout<<"trop important";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<" ou ";
            SetConsoleTextAttribute(texteConsole, 12);
            std::cout<<"negatif";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<", veuillez ";
            SetConsoleTextAttribute(texteConsole, 9);
            std::cout<<"ressaisir";
            SetConsoleTextAttribute(texteConsole, 15);
            std::cout<<" : ";
        }
    }
    while((nb<0)||(nb>taille));

    return option;
}
