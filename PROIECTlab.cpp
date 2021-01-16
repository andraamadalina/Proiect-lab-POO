#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
#define nr 6
string eroare;

//-----------SCRISORILE COPIILOR-----------
class Scrisori
{
private:
    string nume;
    string prenume;
    string varsta;
    string oras;
    string wishlist;
    string culoarePlic;

public:
    friend class Elfi;
    friend class Troli;

    Scrisori(string nm, string pr, string var, string ors, string wl, string cp)
    {
        this->nume = nm;
        this->prenume = pr;
        this->varsta = var;
        this->oras = ors;
        this->wishlist = wl;
        this->culoarePlic = cp;
    }

    Scrisori()
    {
    }

    ~Scrisori();
};
Scrisori::~Scrisori(void)
{
    //cout << "Obiectul a fost sters!" << endl;
}

//-----------STATUSURILE COPIILOR-----------
class StatusCopii
{
protected:
    string nume;
    string prenume;
    string status;
    int buget;

public:
    //setters
    void setNume(string nume)
    {
        this->nume = nume;
    }
    void setPrenume(string prenume)
    {
        this->nume = prenume;
    }
    void setStatus(string status)
    {
        this->status = status;
    }
    void setBuget(int buget)
    {
        this->buget = buget;
    }

    //getters
    string getNume()
    {
        return this->nume;
    }
    string getPrenume()
    {
        return this->prenume;
    }
    string getStatus()
    {
        return this->status;
    }
    int getBuget()
    {
        return this->buget;
    }

    friend class Elfi;
    friend class Troli;
    StatusCopii() {}
    StatusCopii(string nume, string prenume, string status, int buget)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->status = status;
        this->buget = buget;
    }

    //Verificare daca copiii au fost buni sau rai
    void VerificareCopii()
    {
        string l1;
        string l2;
        string l3;

        cout << " " << endl;
        cout << "Pentru a vedea ce buget i se aloca fiecarui copil trebuie ca elfii sa verifice lista" << endl;
        cout << "Ce copil verificam daca a fost bun sau rau? (Verificarea se face dupa nume si prenume) " << endl;
        cin >> nume >> prenume;

        ifstream status;
        status.open("status_copii.txt");
        while (!status.eof())
        {
            status >> l1;
            if (status.eof())
                break;
            status >> l2;
            status >> l3;

            if ((nume == l1) && (prenume == l2))
            {
                cout << "Copilul a fost gasit in lista!" << endl;
                if (l3 == "bun")
                    cout << "Pentru ca a fost un copil bun primeste o suma de 100$." << endl;
                else
                    cout << "Pentru ca a fost un copil rau primeste o suma de 10$." << endl;

                status.close();
                return;
            }
        }
        {
            eroare = "Copilul verificat nu a fost gasit!";
            throw eroare;
        }
        status.close();
    }
};

class CopiiBuni : public StatusCopii
{
public:
    void NumarB()
    {
        cout << " " << endl;
        cout << "Dupa verificarea listei, elfii au vazut ca anul acesta au fost:" << endl;
        ifstream status;
        status.open("status_copii.txt");
        while (!status.eof())
        {
            int nrCBuni = -1;
            string x;
            string cuv1 = "bun";

            while (status)
            {
                status >> x;
                if (x == cuv1)
                    nrCBuni++;
            }
            cout << nrCBuni << " copii buni" << endl;
        }
        status.close();
    }
};

class CopiiRai : public StatusCopii
{
public:
    void NumarR()
    {
        ifstream status;
        status.open("status_copii.txt");
        while (!status.eof())
        {
            int nrCRai = 0;
            string y;
            string cuv2 = "rau";

            while (status)
            {
                status >> y;
                if (y == cuv2)
                    nrCRai++;
            }
            cout << nrCRai << " copii rai" << endl;
        }
        status.close();
    }
};

//-----------INVENTAR-----------
class Inventar
{
private:
    string jucarie;
    string pret;

public:
    friend class Elfi;
    Inventar(string jucarie, string pret)
    {
        this->jucarie = jucarie;
        this->pret = pret;
    }
};

//-----------ELFI-----------
class Elfi : public StatusCopii
{
protected:
    vector<Scrisori> listaCopii;
    vector<StatusCopii> listaElfi;
    vector<Inventar> listaJucarii;

public:
    string linie1;
    string linie2;
    string linie3;
    string linie4;
    string linie5;
    string linie6;
    int totalAcadele = 0;
    friend class Troli;
    friend class DnaCraciun; //elfii ii trimit Doamnei Craciun numarul de acadele pe care trebuie sa le faca
    friend class MosCraciun; //elfii ii trimit lui Mos Craciun lista cu orasele copiilor

    //Citirea scrisorilor de la copii
    void CitireScrisori()
    {
        string nume;
        string prenume;
        string varsta;
        string oras;
        string wishlist;
        string culoarePlic;
        vector<string> cadouri;

        ifstream scrisori;
        scrisori.open("scrisori_copii.txt");
        if (scrisori.is_open())
        {
            while (getline(scrisori, linie1))
            {
                //cout << linie1 << endl;
                getline(scrisori, linie2);
                //cout << linie2 << endl;
                getline(scrisori, linie3);
                //cout << linie3 << endl;
                getline(scrisori, linie4);
                //cout << linie4 << endl;
                getline(scrisori, linie5);
                //cout << linie5 << endl;
                /*istringstream ss(linie5);
                int i = 0;
                string cadou;
                while (getline(ss, cadou, ','))
                {
                    cadouri.push_back(cadou);
                    cout << cadou << '\n';
                }*/
                getline(scrisori, linie6);
                //cout << linie6 << endl;

                Scrisori scrisori(linie1, linie2, linie3, linie4, linie5, linie6);
                listaCopii.push_back(scrisori);
            }
            scrisori.close();
        }
        else
        {
            eroare = "Fisierul scrisori_copii.txt nu poate fi deschis!";
            throw eroare;
        }
    }

    //Afisarea scrisorilor copiilor
    void AfisLista()
    {
        cout << " " << endl;
        cout << "Scrisorile au ajuns la Polul Nord, iar elfii se ocupa de ele" << endl;
        for (int i = 0; i < listaCopii.size(); i++)
        {
            cout << "Elfii incep sa citeasca scrisoarea " << i + 1 << ":" << endl;
            cout << listaCopii[i].nume << endl;
            cout << listaCopii[i].prenume << endl;
            cout << listaCopii[i].varsta << endl;
            cout << listaCopii[i].oras << endl;
            cout << listaCopii[i].wishlist << endl;
            cout << listaCopii[i].culoarePlic << endl;
        }
    }

    //Citirea statusurilor copiilor
    void CitireStatus()
    {
        ifstream stat("status_copii.txt");
        if (stat.is_open())
        {
            while (getline(stat, nume))
            {
                getline(stat, prenume);
                getline(stat, status);

                if (status == "bun")
                {
                    StatusCopii aux(nume, prenume, status, 100);
                    listaElfi.push_back(aux);
                }
                else
                {
                    StatusCopii aux(nume, prenume, status, 10);
                    listaElfi.push_back(aux);
                }
            }
            stat.close();
        }
        else
        {
            eroare = "Fisierul status_copii.txt nu poate fi deschis!";
            throw eroare;
        }
    }

    //Afisarea statusurilor copiilor
    void AfisStatus()
    {
        cout << " " << endl;
        cout << "Lista cu statusurile fircarui copil:\n";
        for (int i = 0; i < listaElfi.size(); i++)
        {
            cout << listaElfi[i].nume << endl;
            cout << listaElfi[i].prenume << endl;
            cout << listaElfi[i].status << endl;
            cout << listaElfi[i].buget << endl;
        }
    }

    //Citirea inventarului (jucariile + pretul acestora)
    void CitireJucarii()
    {
        ifstream juc("inventar.txt");
        if (juc.is_open())
        {
            string jucarie;
            string pret;
            while (getline(juc, jucarie))
            {
                getline(juc, pret);

                listaJucarii.push_back(Inventar(jucarie, pret));
            }
            juc.close();
        }
        else
        {
            eroare = "Fisierul inventar.txt nu poate fi deschis!";
            throw eroare;
        }
    }

    //Afisarea inventarului
    void AfisJucarii()
    {
        cout << " " << endl;
        cout << "Lista jucariilor si pretul acestora:\n";
        for (int i = 0; i < listaJucarii.size(); i++)
        {
            cout << listaJucarii[i].jucarie << endl;
            cout << listaJucarii[i].pret << endl;
        }
    }

    //Elfii distribuie cadourile
    void DistributieCadouri()
    {
        //cout << " " << endl;
        for (int i = 0; i < listaCopii.size(); i++)
        {
            vector<string> punga_de_cadouri;
            string adaugat = "";
            istringstream ss(listaCopii[i].wishlist);
            string cadou;
            string jucarie;
            string pret;
            int b;

            cout << " " << endl;
            cout << "Copilul " << listaCopii[i].nume << " " << listaCopii[i].prenume << " care a fost " << listaElfi[i].status;
            if (listaElfi[i].status == "bun")
                b = 100;
            else
                b = 10;
            cout << " are bugetul " << b << endl;
            while (getline(ss, cadou, ','))
            {
                //cadouri.push_back(cadou);
                //cout << cadou << '\n';
                ifstream inventar;
                inventar.open("inventar.txt");
                while (getline(inventar, jucarie)) //citeste jucariile pana se termina fisierul
                {
                    if (cadou == jucarie)
                    {
                        cout << "S-a gasit jucaria: " << cadou << " a copilului " << listaCopii[i].prenume << endl;
                        getline(inventar, pret);
                        int p = stoi(pret);

                        if (b < 0 || b == 0 || p > b)
                        {
                            cout << "Copilul nu are bani de jucarie!" << endl;
                            goto restart;
                        }

                        else
                        {
                            b = b - p;
                            adaugat = adaugat + " " + cadou;
                            cout << "Jucaria a fost adaugata in punga de cadouri!" << endl;
                            cout << "Bugetul dupa distribuirea cadoului este " << b << endl;
                        }
                    }
                }
                inventar.close();
            }
        restart:

            punga_de_cadouri.push_back(adaugat);
            if (adaugat == "" && listaElfi[i].status == "bun")
                cout << "Copilul primeste cadou default 100$, deci 0 acadele" << endl;
            else if (adaugat == "")
                cout << "Copilul primeste cadou default 10$, deci 0 acadele." << endl;
            else
            {
                cout << "=> Copilului i se adauga " << b << " acadele." << endl;
                totalAcadele += b;
            }
        }
    }

    //Elfii fac o lista cu orasele copiilor
    void OraseCopii()
    {
        vector<string> orase;
        ifstream maroc("lista_orase.txt");
        if (maroc.is_open())
        {
            string orasLista;
            while (getline(maroc, orasLista))
            {
                orase.push_back(orasLista);
                cout << " " << endl;
                for (int i = 0; i < listaCopii.size(); i++)
                {
                    if (orasLista == listaCopii[i].oras)
                    {
                        cout << "Orasul copilului " << listaCopii[i].nume << " " << listaCopii[i].prenume << " este " << orasLista;
                    }
                }
            }
            maroc.close();
        }
        else
        {
            eroare = "Fisierul lista_orase.txt nu poate fi deschis!";
            throw eroare;
        }
        cout << " " << endl;
    }
};

//-----------TROLI-----------
class Troli
{
public:
    int ambalajFete = 0;
    int ambalajBaieti = 0;
    int nrCarbuni = 0;
    friend class DnaCraciun; //trolii ii trimi numarul de carbuni folositi

    void ImpachetareCadouri(Elfi *elfi)
    {
        for (int i = 0; i < elfi->listaCopii.size(); i++)
        {
            if (elfi->listaElfi[i].status == "bun")
            {
                if (elfi->listaCopii[i].culoarePlic == "roz")
                    ambalajFete++;
                else
                    ambalajBaieti++;
            }
            else
            {
                if (elfi->listaCopii[i].culoarePlic == "roz")
                {
                    ambalajFete++;
                    nrCarbuni++;
                }
                else
                {
                    ambalajBaieti++;
                    nrCarbuni++;
                }
            }
        }
        cout << " " << endl;
        cout << "Trolii au folosit pentru impachetarea cadourilor " << ambalajFete << " ambalaje roz pentru fete." << endl;
        cout << "Trolii au folosit pentru impachetarea cadourilor " << ambalajBaieti << " ambalaje albastre pentru baieti." << endl;
        cout << "Pentru copiii rai, trolii au adaugat " << nrCarbuni << " in pungile acestora, cate unul pentru fiecare copil rau." << endl;
    }
};

class Abstractizare
{
public:
    virtual void Afisare() = 0;
};

//-----------DOAMNA CRACIUN-----------
class DnaCraciun : public Abstractizare
{
public:
    float bugetExtra;
    int acadele;
    int carbuni;
    float suma = 0;

    void Afisare()
    {
        cout << " " << endl;
        cout << "Clasa nu mai e abstracta!" << endl;
    }

    void AfisAcadele_Carbuni(Elfi *elfi, Troli *troli)
    {
        this->acadele = elfi->totalAcadele;
        this->carbuni = troli->nrCarbuni;
        cout << " " << endl;
        cout << "Acadele: " << elfi->totalAcadele << " (1$/buc)" << endl;
        cout << "Carbuni: " << troli->nrCarbuni << " (0.5$/buc)" << endl;
    }

    template <class X>
    float BugetExtra(int obiecte, X cost)
    {
        bugetExtra = obiecte * cost;
        return bugetExtra;
    }

    void extra(float pr_a, float pr_c)
    {
        suma = pr_a + pr_c;
        cout << "Bugetul extra: " << suma << endl;
        cout << " " << endl;
    }
};

//-----------MOS CRACIUN-----------
class MosCraciun
{
public:
    friend class DnaCraciun; // Mos Craciun impartaseste cu Doamna Craciun traseul acestuia

    int minDistance(float distanta[], bool sptSet[])
    {

        float m = __FLT_MAX__, index;

        for (int v = 0; v < nr; v++)
            if (sptSet[v] == false && distanta[v] <= m)
                m = distanta[v], index = v;

        return index;
    }

    void printSolution(float distanta[])
    {
        printf("Oras \t\t Distanta de la sursa\n");
        for (int i = 0; i < nr; i++)
            printf("%d \t\t %f\n", i, distanta[i]);
    }

    void dijkstra(float graf[nr][nr], int s, float distanta[])
    {

        bool sptSet[nr];
        for (int i = 0; i < nr; i++)
            distanta[i] = __FLT_MAX__, sptSet[i] = false;
        distanta[s] = 0;
        for (int count = 0; count < nr - 1; count++)
        {
            int x = minDistance(distanta, sptSet);

            sptSet[x] = true;

            for (int y = 0; y < nr; y++)
                if (!sptSet[y] && graf[x][y] && distanta[x] != __FLT_MAX__ && distanta[x] + graf[x][y] < distanta[y])
                    distanta[y] = distanta[x] + graf[x][y];
        }

        //printSolution(distanta); //legaturile intre orase
    }

    int urmatorul_nod(float distanta[], int vazut[])
    {
        float m = __FLT_MAX__;
        for (int i = 0; i < nr; i++)
        {
            if (distanta[i] < m && vazut[i] == 0)
                m = distanta[i];
        }
        for (int i = 0; i < nr; i++)

            if (distanta[i] == m)
                return i;
    }

    void Drum()
    {

        float distanta[nr];
        int vazut[nr] = {0};
        int parcurs[nr];

        float graf[nr][nr] = {
            {0.00, 3967.49, 4124.06, 4187.44, 4257.05, 4474.86},
            {3967.49, 0.00, 287.92, 457.35, 537.81, 659.38},
            {4124.06, 297.92, 0.00, 172.56, 250.15, 391.49},
            {4187.44, 457.35, 172.56, 0.00, 86.05, 287.56},
            {4257.05, 537.81, 250.15, 86.05, 0.00, 222.05},
            {4474.86, 659.38, 391.49, 287.56, 222.05, 0.00}};

        int src;
        float s = 0.00;
        for (int i = 0; i < nr; i++)
        {
            if (i == 0)
            {
                cout << "De unde incepem parcurgerea?" << endl;
                cin >> src;
                dijkstra(graf, src, distanta);
                parcurs[i] = src;
                vazut[src] = 1;
                i++;
            }
            int nod = urmatorul_nod(distanta, vazut);
            parcurs[i] = nod;
            s = s + distanta[nod];
            dijkstra(graf, nod, distanta);
            vazut[nod] = 1;
        }
        for (int i = 0; i < nr; i++)
        {
            cout << "orasul " << parcurs[i] << " -> ";
        }
        cout << s << " kilometri." << endl;
        cout << "orasul 0 = Rovaniemi -> orasul 1 = Oujda -> orasul 2 = Fes -> orasul 3 = Rabat -> orasul 4 = Casablanca -> orasul 5 = Marrakech" << endl;
    }
};

int main()
{
    Elfi elf;
    //Citirea scrisorilor de la copii, cand acestea ajung la Polul Nord elfii se ocupa de ele
    try
    {
        elf.CitireScrisori();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Afisarea scrisorilor de la copii
    try
    {
        elf.AfisLista();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Citirea statusurilor copiilor. Elfii trebuie sa vada daca copiii au fost buni sau rai pentru a sti ce buget i se aloca fiecaruia
    try
    {
        elf.CitireStatus();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Afisarea statusurilor copiilor
    try
    {
        elf.AfisStatus();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Citirea jucariilor din inventar. Elfii trebuie sa verifice inventarul sa vada daca jucariile pe care si le doresc copii exista la ei în atelier
    try
    {
        elf.CitireJucarii();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Afisarea jucariilor pe care elfii le au in inventar si pretul acestora
    try
    {
        elf.AfisJucarii();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    StatusCopii sts;
    //Elfii verifica fiecare copil daca a fost bun sau rau
    try
    {
        sts.VerificareCopii();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Numarul copiilor buni
    CopiiBuni bun;
    try
    {
        bun.NumarB();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Numarul copiilor rai
    CopiiRai rau;
    try
    {
        rau.NumarR();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Elfii distribuie cadourile copiilor si le pun in punga de cadouri astfel:
    //Daca exista le adauga in ordine in punga, dar cand bugetul nu permite si acesta urmeaza a fi depasit, elfii se opresc si nu mai adauga cadourile ce mai erau pe lista, dar in schimb, acestia adauga o acadea pentru fiecare dolar necheltuit
    //Daca cadoul pe care si-l doreste copilul nu exista in inventar, se va adauga un cadou default in functie de statusul acestuia. Copiii buni vor primi un cadou default de 100$, iar copiii un cadou default de 10$
    //Daca bugetul copilului este depasit din start, vor primi de asemenea si aici cadourile default de 100$ sau 10$
    try
    {
        elf.DistributieCadouri();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Elfii au facut o lista cu orasele copiilor pentru a i-o da lui Mos Craciun
    try
    {
        elf.OraseCopii();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    Troli trl;
    //Trolii primesc de la elfi lista cu cadouri si impacheteaza fiecare cadou cu un ambalaj specific, roz pentru fete si albastru pentru baieti
    //Trolii pun si cate un carbune in punga fiecarui copil rau
    try
    {
        trl.ImpachetareCadouri(&elf);
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    DnaCraciun dnacr;
    dnacr.Afisare();
    //Afisarea numarului de acadele si numarului de carbuni
    try
    {
        dnacr.AfisAcadele_Carbuni(&elf, &trl);
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }

    //Bugetul extra, care va fi calculat astfel acadele * 1 + carbuni * 0.5
    try
    {
        dnacr.extra(dnacr.BugetExtra<int>(dnacr.acadele, 1), dnacr.BugetExtra<float>(dnacr.carbuni, 0.5));
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }
    
    MosCraciun mos;
    //Mos Craciun pleaca din aeroportul Rovaniemi din Laponia(Finlanda) si cauta cel mai scurt drum pentru a livra tututor copiilor cadourile in toate orasele din Maroc
    try
    {
        mos.Drum();
    }
    catch (string eroare)
    {
        cout << eroare << endl;
    }
}
