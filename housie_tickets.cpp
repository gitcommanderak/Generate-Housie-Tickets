#include<iostream> //Enabling basic I/O functions of C++
#include<cstdlib> //For pseudo-random number generation
#include<ctime> //For seeding random numbers
#include<algorithm> //For ticket sorting
#include<fstream> //For writing ticket to external CSV

#define ROWS 3
#define COLS 9
#define LINE 5

class Ticket
{
private:
    int ticket[ROWS*COLS]{};
public:
    Ticket();
    ~Ticket();
    void AllocateTicket()
    {
        //Allocate Numbered Spaces
        std::cout<<"\nAllocating numbered spaces...";
        srand(static_cast<unsigned int>(time(nullptr)));
        int randnum=0;
        for (int row = 0; row < ROWS; row++)
        {
            int use=0;
            int used[COLS]{};
            int line[LINE]{};
            if (row==2)
            {
                for (int i = 0; i < COLS; i++)
                {
                    if (used[i]==0)
                    {
                        line[use]=i;
                        ticket[i+row*COLS]=1;
                        use++;
                    }
                }  
            }
            for (int i = use; i < LINE; i++)
            {
                //Assign 5 column spaces for a given row
                bool unique=false;
                while (unique==false)
                {
                    randnum=rand() % 9; //Assign Column Numbers in [0-8]
                    unique=true;
                    for (int j = 0; j < i; j++)
                    {
                        if (line[j]==randnum)
                        {
                            unique=false;
                        }
                    }
                }
                line[i]=randnum;
                used[randnum]=1;
                ticket[randnum+row*COLS]=1;
            }
            std::cout<<'\n';  
        }
    }
    void GenerateTicket()
    {
        std::cout<<"Filling allocated spaces...\n\n";
        //Generate Housie Tickets
        for(int i = 0; i < COLS; i++)
        {
            int randnum{}, count{}, usednum[ROWS]{}; //Array to store used numbers to avoid repetition
            for (int j = 0; j < ROWS; j++)
            {   
                if (ticket[i+j*COLS]==1)
                {   
                    count++;         
                    bool unique=false;
                    while (unique==false)
                    {
                        if (i==0)
                        {
                            // First Column [1-9]
                            randnum=rand() % 9 + 1;
                        }
                        else if (i==8)
                        {
                            // Last Column 80 + [0-10]
                            randnum=10*i + rand() % 11;
                        }
                        else
                        {
                            // Last Column 10*i + [0-9]
                            randnum=10*i + rand() % 10;
                        }                
                        unique=true;
                        for (int row = 0; row < j; row++)
                        {
                            if (usednum[row]==randnum)
                            {
                                unique=false;
                            }
                        }
                    }
                    usednum[j]=randnum;
                }
            }
            std::sort(usednum, usednum + ROWS);
            for (int j = 0; j < ROWS; j++)
            {
                ticket[i+j*COLS]=usednum[j];
            }
        }
    }
    void PrintTicket()
    {
        //Generate and Store 2D ticket as 1D array in Row Major Order
        for(int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                std::cout<<ticket[j+i*COLS]<<'\t';
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
    }
    int* StoreTicket()
    {
        return ticket;
    }
};

Ticket::Ticket()
{
    std::cout<<"Constructing Ticket";
}

Ticket::~Ticket()
{
    std::cout<<"\nDestructing Ticket";  
}

int main()
{
    std::cout<<"!!Welcome to Housie Ticket Generator!!\n";
    std::cout<<"\nPress ENTER to start ticket generation...";
    std::cin.get();
    Ticket A;
    A.AllocateTicket();
    A.PrintTicket();
    A.GenerateTicket();
    A.PrintTicket();
    int *ptr;
    ptr=A.StoreTicket();
    std::cout<<"\nPress ENTER to print ticket to CSV file...";
    std::cin.get();
    std::ofstream fo;
    std::string fn="Tickets.csv";
    fo.open(fn,std::ios::app);
    fo<<"NEW TICKET\n";
    for(int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                fo<<ptr[j+i*COLS]<<',';
            }
            fo<<'\n';
        }
    fo<<'\n';
    fo.close();
    std::cout<<"\nSuccess: Ticket successfully printed to \"Tickets.csv\" file!\n\n";
    std::cout<<"\nPress ENTER key to exit...";
    std::cin.get();
    return 0;
}