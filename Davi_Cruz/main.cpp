

#include "calculator.cpp"


int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        try
        {
            ifstream inputfile{argv[1]};
            ofstream outputfile{"result.txt"};
            Calculator cal{inputfile, outputfile};
            cal.execute(); 
            inputfile.close();
            outputfile.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        Calculator cal{};

        cal.execute();
    }

    return 0;
}
