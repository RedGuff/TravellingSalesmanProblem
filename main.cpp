#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
//#include <filesystem> // C++17
//namespace fs = std::filesystem;
using namespace std;
// https://fr.wikipedia.org/wiki/Probl%C3%A8me_du_voyageur_de_commerce
// https://interstices.info/le-probleme-du-voyageur-de-commerce/
// https://fr.wikipedia.org/wiki/Scalable_Vector_Graphics

int factorielle ( int val )   //https://www.developpez.net/forums/d430474/c-cpp/cpp/codage-cpp-factoriel-d-nombre-entier/
{
    int result = 1;
    for ( int i = val; i > 0; --i )
        result *= i;
    return result;
}
void delInit(){
cout << "Attention : destruction de tous les points initiaux !" << endl;
}

void trop(){
           cout << "Attention : destruction des points initiaux \"en trop\" !" << endl;
}

void intro ( int nbPoint )
{
    cout << "M : Entrer des points manuellement. " ;
    delInit();

    cout << "L : Lire des points du SSD (ou du disque dur). " ;
delInit();
    cout << "H : Me laisser choisir des points au pseudo-hasard." << endl;
    cout << "A : Afficher les points." << endl;
     cout << "S : Sauvegarder les points sur le SSD (ou le disque dur)." << endl;

    /*cout << "F : Trier les points en force brute." << endl;
    cout << "    ATTENTION !" << endl;
    cout << "    Pour N points, il y a (1/2)*(N-1)! chemins possibles !" << endl;
    cout << "    Actuellement il y a " << nbPoint << " points." << endl;
    cout << "    ce qui fait " << ( factorielle ( nbPoint-1 ) ) *0.5 << " calculs !" << endl;
    */
    // cout << "P : Partir du premier point, et aller au suivant plus proche..." << endl;
    cout << "    Actuellement il y a " << nbPoint << " points." << endl; //
    cout << "N : Changer le nombre de points. ";

    if ( nbPoint>3 )
        {
trop();
        }
        else {
            cout << "" << endl;
        }

    cout << "P : Exporter vers PovRay." << endl;
    cout << "V : Exporter en SVG." << endl;
    cout << "Q : Quitter." << endl;
}

bool errBadVAlue ( string texteBadValue, auto min, auto max )
{
    cerr << "Min = "  << min << endl;
    cerr << "Max = "  << max << endl;
    cerr << texteBadValue << endl;
    return false;
}


auto inputNb ( auto max = 42, auto min = 0, string texteDemande = "How many?", string texteBadValue = "A good number!" )   // C++14 minimum.
{
    if ( max < min )   // En général, on donne le minimum avant le maximum, et parfois pas la valeur par défaut.
        {
        auto temp = max;
        max = min;
        min = temp;
        }

// Textes par défaut par fichier lgg ?

    auto a = max; // Valeur valide.
    string tentativeString = "";
    bool inputOk  = true;

    do
        {
        cout << texteDemande << endl;
        inputOk = true; // Pour autre demande éventuelle.

        try
            {
            getline ( cin, tentativeString ); // Pour éviter des bugs de non nombre.
            }
        catch ( const std::invalid_argument& e )
            {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }

        try
            {
            a = stoi ( tentativeString ); // cin.;
            }
        catch ( exception& e )     // Nombre dépassant la limite : 99999999999999999999999999999999 par exemple.
            {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }

        if ( ( a < min ) || ( a > max ) )
            {
            a = max; // Valeur valide.
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }
        }
    while ( inputOk == false );

    return a;
}


int FileAppend ( string file = "", string data = "" )   // And create new file if does not exist. // Slow.
{
    ofstream outfile ( file.c_str(), ios_base::app );

    if ( !outfile )
        {
        cerr << "Error Opening File " << file << "!" << endl;
        return -1; // Err!
        }
    else
        {
        outfile << data;
        outfile.close();
        }

    return 0; // Ok.
}

int FileAppend ( string file = "", int dataI = 0 )  // Surcharge ! // And create new file if does not exist. // Slow.
{
    return FileAppend ( file,  to_string ( dataI ) ) ;
}


void outtro()
{
    cout << "Au revoir." << endl;
}


int main()
{
    srand ( time ( NULL ) ); // No need for better init.
cout << "Bonjour." << endl;
    cout << "Le but de cet exercice du \"voyageur de commerce\" est de trouver le trajet le plus court reliant tous les points." << endl;
    cout << "Tous les points sont ici en 2D dans un plan parfait. Le sens n\'a ici pas d\'importance." << endl;
    cout << "Le menu se commande en majuscules ou en minuscules. Parfois, plusieurs commandes peuvent s\'entrer d\'un coup : HAP, par exemple." << endl;
    int nbPoints = 10;
    vector < vector < int > > Matrix ( 2, vector< int > ( nbPoints,0 ) ); // Matrix refuse de "passer" dans les fonctions en tant que variable globale.
    char choice='?';
    string file = "1.txt";
    string FileIn = "";
    string line1 = "";

    int minX=0;
    int minY=0;
    int maxX=1;
    int maxY=1;

    do
        {
        intro ( nbPoints );
        cin >> choice;

        switch ( choice )
            {
            case 'M':
            case 'm':
                for ( int p=0; p<Matrix[0].size(); p++ )
                    {
                    cout << "Nombre " << p << " : " << endl;
                    Matrix[0][p] = inputNb ( -100,100,"X ?", "Un bon nombre !" );
                    Matrix[1][p] = inputNb ( -100,100,"Y ?", "Un bon nombre !" );
                    }

                break;

            case 'h':
            case 'H':
                for ( int p=0; p<Matrix[0].size(); p++ )
                    {
                    Matrix[0][p] = rand() % ( 10 * Matrix[0].size() );
                    Matrix[1][p] = rand() % ( 10 * Matrix[0].size() );
                    }
                break;

            case 's':
            case 'S':
                cout << "Sauver les points sous quel fichier ? (Avec l\'extention, par exemple \".txt\". Ajout des points en bas du fichier si le fichier existe.) " << endl;
                cin >> file ;

                for ( int b=0; b<Matrix[0].size(); b++ )
                    {
                    FileAppend ( file, Matrix[0][b] );  //
                    FileAppend ( file," , " );
                    FileAppend ( file, Matrix[1][b] );  //
                    FileAppend ( file,"\n" );
                    }
                break;

            //////
            case 'l':
            case 'L':
{


NewFileIn:
                FileIn = "";

                while ( FileIn == "" )
                    {
                    // FileIn  = "In.txt";
                    cout << "FileIn?" << endl;
                    getline ( cin, FileIn );
                    }

                ifstream fileI ( FileIn.c_str(), ios::in );

                if ( !fileI )
                    {
                    cerr << "Impossible to open " << FileIn << "!" << endl;
                    goto NewFileIn;
                    }
                else
                    {
            int point = 0;
                    while ( getline ( fileI, line1 ) )
                        {
/*
// Les tests montrent que lire un fichier avec plus de points que la taille initiale de Matrix est bon.
// Au pire :

if (point>Matrix[0].size())
{
    push_back(Matrix[0],[0][0]); // ?
}
*/
// line1 = "2 , 42"
//                        cout << "Point number " << point <<": "<< line1 << endl; // Tests ok.
Matrix[0][point] = stoi(line1) ;
// cout << "  X = " << Matrix[0][point] << endl; // Tests ok.
line1=line1.substr(1 + line1.find(","));
Matrix[1][point] = stoi(line1) ;
// cout << "  Y = " << Matrix[1][point] << endl; // Tests ok.

point++;
                        }

                    }
                fileI.close();
                break;

            ////////////

            }


            case 'n':
            case 'N':
                nbPoints = inputNb ( 42, 3, "Combien de points voulez-vous ?", "Une bonne valeur !" );
                Matrix[0].resize ( nbPoints,0 );
                Matrix[1].resize ( nbPoints,0 );
                break;

            case 'p':
            case 'P':
                cout << "Sauver les points sous quel fichier ? (sans l\'extention \".pov\". Ajout des points et des lignes en bas du fichier si le fichier existe.) " << endl;
                cin >> file ;
                file = file + ".pov";

//fs::copy("pov.pov",file); //https://docs.w3cub.com/cpp/filesystem/copy/

                for ( int p=0; p<Matrix[0].size(); p++ )
                    {
//             "object {city translate<1,0,0> }"
                    FileAppend ( file,"object {city translate<" );
                    FileAppend ( file,Matrix[0][p] );
                    FileAppend ( file,"," );
                    FileAppend ( file,Matrix[1][p] );
                    FileAppend ( file,",0> }\n" );


                    if ( maxX<Matrix[0][p] )
                        {
                        maxX = Matrix[0][p];
                        }

                    if ( maxY<Matrix[1][p] )
                        {
                        maxY = Matrix[1][p];
                        }

                    if ( minX>Matrix[0][p] )
                        {
                        minX = Matrix[0][p];
                        }

                    if ( minY>Matrix[1][p] )
                        {
                        minY = Matrix[1][p];
                        }
                    }

                for ( int p=0; p<Matrix[0].size()-1; p++ )   // -1 because the last road loops on the last city with city0.
                    {
                    FileAppend ( file,"cylinder { <" );
                    FileAppend ( file,Matrix[0][p] );
                    FileAppend ( file, "," );
                    FileAppend ( file,Matrix[1][p] );

                    FileAppend ( file,",0>,<" );
                    FileAppend ( file,Matrix[0][p+1] );
                    FileAppend ( file, " ," );
                    FileAppend ( file,Matrix[1][p+1] );
                    FileAppend ( file,",0>,diameterRoad texture { textureRoad}}\n" );
                    }

                FileAppend ( file,"cylinder { <" );
                FileAppend ( file,Matrix[0][0] );
                FileAppend ( file,"," );
                FileAppend ( file,Matrix[1][0] );

                FileAppend ( file,",0>,<" );
                //  FileAppend ( file,Matrix[0][Matrix[0].size()-1] );
                FileAppend ( file,Matrix[0][nbPoints-1] );
                FileAppend ( file, " ," );
//                FileAppend ( file,Matrix[1][Matrix[0].size()-1] );
                FileAppend ( file,Matrix[1][nbPoints-1] );
                FileAppend ( file,",0>,diameterRoad texture { textureRoad}}\n" );


                FileAppend ( file,"camera{location <" );
                FileAppend ( file, ( min ( minX,0 )+maxX ) /2 );
                FileAppend ( file," ," );
                FileAppend ( file, ( min ( minY,0 )+maxY ) /2 );
                FileAppend ( file," ," );
                FileAppend ( file,- ( 5- min ( minY,minX ) + max ( maxX,maxY ) ) );
                FileAppend ( file,">}\n" );


                break;


            ///////////////////////////////
            case 'V':
            case 'v':
                cout << "Sauver les points sous quel fichier ? (sans l\'extention \".svg\". Erreur si le fichier existe.) " << endl;
                cin >> file ;
                file = file + ".svg";
                FileAppend ( file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!-- Created with TravellingSalesmanProblem (https://github.com/RedGuff/TravellingSalesmanProblem) -->\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" " );
                FileAppend ( file," width=\"110\" height=\"110\">\n" ); // ?
                FileAppend ( file,"  <title>Travelling salesman problem images with " );
                            FileAppend ( file,nbPoints);
                            FileAppend ( file," points.</title>\n  <desc>\n    ");
                            FileAppend ( file,nbPoints);
                            FileAppend ( file," cities and ");
                                        FileAppend ( file,nbPoints-1);
                            FileAppend ( file," roads, maybe optimized, or not.\n  </desc>\n" );

                for ( int p=0; p<Matrix[0].size(); p++ )
                    {
//             "<circle cx="90" cy="80" r="50" fill="blue" />"
                    FileAppend ( file,"<circle cx=\"" );
                    FileAppend ( file,Matrix[0][p] );
                    FileAppend ( file,"\" cy=\"" );
                    FileAppend ( file,Matrix[1][p] );
                    FileAppend ( file,"\" r=\"2\" fill=\"blue\" />\n" );




//   <line x1="5" y1="5" x2="250" y2="95" stroke="red" />
                    }

                for ( int p=0; p<Matrix[0].size()-1; p++ )   // -1 because the last loop on the last city with city0.
                    {
                    FileAppend ( file,"<line x1=\"" );
                    FileAppend ( file,Matrix[0][p] );
                    FileAppend ( file, "\" y1=\"" );
                    FileAppend ( file,Matrix[1][p] );
                    FileAppend ( file,"\" x2=\"" );
                    FileAppend ( file,Matrix[0][p+1] );
                    FileAppend ( file, "\" y2=\"" );
                    FileAppend ( file,Matrix[1][p+1] );
                    FileAppend ( file,"\" stroke=\"red\" />\n" );
                    }

                FileAppend ( file,"<line x1=\"" );
                FileAppend ( file,Matrix[0][0] );
                FileAppend ( file,"\" y1=\"" );
                FileAppend ( file,Matrix[1][0] );
                FileAppend ( file,"\" x2=\"" );
                //  FileAppend ( file,Matrix[0][Matrix[0].size()-1] );
                FileAppend ( file,Matrix[0][nbPoints-1] );
                FileAppend ( file, "\" y2=\"" );
//                FileAppend ( file,Matrix[1][Matrix[0].size()-1] );
                FileAppend ( file,Matrix[1][nbPoints-1] );
                FileAppend ( file,"\" stroke=\"red\" />\n" );
                FileAppend ( file,"</svg>" );


                break;


            ///////////////////////////


            case 'a':
            case 'A':

//                affiche(Matrix()):
                for ( int q=0; q<Matrix[0].size(); q++ )
                    {
                    cout << Matrix[0][q] << " , " << Matrix[1][q] << endl;
                    }

                break;

            case 'q':
            case 'Q':
                break;

            default:
                cerr << "Je n\'ai pas compris !" << endl;
                break;
            }
        }

    while (( choice != 'Q' ) && ( choice != 'q' ));

    outtro();
    return 0;
}
